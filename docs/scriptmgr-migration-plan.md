# ScriptMgr Migration Plan: TC Cata → ACore Module Compatibility

## The Core Problem

TC Cata has a **monolithic** ScriptMgr (everything in one `ScriptMgr.h`/`.cpp`). ACore has a **modular** architecture with:
- Separate `ScriptDefines/*.h/.cpp` per script type
- `All*Script` global interceptor classes (the main thing modules use)
- A `modules/` directory with CMake auto-discovery
- Extended hooks (~200+ more than TC)

---

## Phase 1: Shim Layer (Module Compilation)

Make ACore modules compile against TC without rewriting the modules.

| Step | What | Scope |
|------|------|-------|
| 1.1 | Extend `ScriptObject` constructor to match ACore's `(name, totalAvailableHooks)` | ~20 lines |
| 1.2 | Create `ScriptMgrMacros.h` with `ExecuteScript<T>()`, `CALL_ENABLED_HOOKS` | ~150 lines |
| 1.3 | Extract `ScriptObject` into separate `ScriptObject.h` | mechanical move |
| 1.4 | **Create `All*Script` stub classes** — `AllCreatureScript`, `AllPlayerScript`, `AllGameObjectScript`, `AllItemScript`, `AllMapScript`, `AllSpellScript`, `AllBattlegroundScript`, `AllCommandScript` | ~1500 lines |
| 1.5 | Add missing script types (`GlobalScript`, `ModuleScript`, `PetScript`, `ArenaScript`, `GameEventScript`, `MailScript`, `LootScript`, etc.) | ~1000 lines |
| 1.6 | Extend existing types — `CreatureScript` needs gossip/quest hooks, `PlayerScript` needs ~80+ hooks, `UnitScript` needs ~25 hooks, `WorldScript` needs before/after config hooks | ~2000 lines |
| 1.7 | Add `RegisterCreatureAI` macro, `GenericCreatureScript<T>`, namespace aliases (`Acore` → `Trinity`, `AC_GAME_API` → `TC_GAME_API`) | ~100 lines |

---

## Phase 2: Core Wiring (Make Hooks Functional)

Phase 1 creates the classes, Phase 2 makes them actually fire.

| Step | What | Risk |
|------|------|------|
| 2.1 | Split `ScriptMgr.h` into `ScriptDefines/` — one `.h`/`.cpp` per type | Mechanical, low risk |
| 2.2 | Wire `AllCreatureScript` — add dispatch calls in `Creature::Update()`, `Map::AddToMap()`, `Creature::SaveToDB()`, etc. | Medium — must find exact callsites |
| 2.3 | Wire `AllGameObjectScript`, `AllItemScript`, `AllMapScript`, `AllSpellScript` | Medium |
| 2.4 | Wire extended `PlayerScript` hooks — ~80+ insertions across `Player.cpp`, `WorldSession`, combat code | High — largest surface area |
| 2.5 | Wire extended `UnitScript` hooks — aura apply/remove, combat enter/leave, death | Medium |
| 2.6 | Wire `GlobalScript`, `PetScript`, `GameEventScript`, `MailScript`, `LootScript` | Medium |

---

## Phase 3: Module Loader

| Step | What |
|------|------|
| 3.1 | Create `modules/` directory structure + `CMakeLists.txt` |
| 3.2 | Create `ConfigureModules.cmake` with auto-discovery |
| 3.3 | Generate `ModulesLoader.cpp` from template, wire into `ScriptMgr::Initialize()` |
| 3.4 | Config file auto-loading from `modules/<mod>/conf/*.conf.dist` |

---

## What Matters Most for ACore Modules

The **`All*Script` classes** are the #1 priority. Nearly every ACore module hooks into these:

- **mod-playerbots**: `AllCreatureScript::GetCreatureAI()` to intercept AI creation globally
- **mod-eluna**: `AllCreatureScript`, `AllGameObjectScript`, `PlayerScript`, `GlobalScript`
- **mod-autobalance**: `AllCreatureScript`, `AllMapScript`, `UnitScript`
- **Most modules**: `WorldScript::OnBeforeConfigLoad` / `OnAfterConfigLoad` for config, `ModuleScript` for lifecycle

### All*Script Classes Reference

| Class | Purpose | Key Hooks |
|-------|---------|-----------|
| `AllCreatureScript` | Fires for ALL creatures | `OnAllCreatureUpdate`, `OnBeforeCreatureSelectLevel`, `OnCreatureSelectLevel`, `OnCreatureAddWorld`, `OnCreatureRemoveWorld`, `OnCreatureSaveToDB`, `CanCreatureGossipHello/Select/SelectCode`, `CanCreatureQuestAccept/Reward`, `GetCreatureAI`, `OnFfaPvpStateUpdate` |
| `AllGameObjectScript` | Fires for ALL game objects | `GetGameObjectAI`, `OnGameObjectAddWorld`, `OnGameObjectRemoveWorld`, `OnGameObjectSaveToDB`, `OnGameObjectUpdate` |
| `AllItemScript` | Fires for ALL items | `CanItemApplyEquipSpell`, `CanApplySoulboundFlag`, etc. |
| `AllMapScript` | Fires for ALL maps | `OnBeforeCreateInstanceScript`, `OnDestroyInstance` |
| `AllSpellScript` | Fires for ALL spell casts | `OnCalcMaxDuration`, `OnSpellCheckCast`, `CanPrepare`, `OnDummyEffect` (3 overloads), `OnSpellCast`, `OnSpellPrepare`, `OnSpellCastCancel` |
| `AllBattlegroundScript` | Fires for ALL BG events | `OnBattlegroundStart/End/Update`, `OnQueueUpdate`, `OnAddGroup`, etc. |
| `AllCommandScript` | Fires for ALL commands | `OnHandleDevCommand`, `OnTryExecuteCommand` |

---

## Cata-Specific Complications

- ACore is WotLK — some hooks reference WotLK-only systems (old talent trees, arena teams, glyphs). Need stubs or adaptation for Cata equivalents.
- Type differences: `BattlegroundQueueTypeId`, dungeon finder types, spell system changes between expansions.
- Some modules may reference WotLK spell IDs, creature entries, etc. that don't exist in Cata — that's a per-module porting issue, not a framework issue.

---

## Key Incompatibilities

1. **ScriptObject constructor**: ACore takes `(const char* name, uint16 totalAvailableHooks = 0)`. TC takes `(char const* name)`.
2. **Missing `All*Script` classes**: ACore modules overwhelmingly use these global interceptors. TC has none.
3. **Missing script types entirely**: `GlobalScript`, `DatabaseScript`, `ModuleScript`, `MiscScript`, `MovementHandlerScript`, `PetScript`, `ArenaScript`, `GameEventScript`, `MailScript`, `LootScript`, `WorldObjectScript`, `TicketScript`, `PlayerbotScript`.
4. **Hook signature differences**:
   - TC `CreatureScript::GetAI()` is pure virtual. ACore's is virtual with `nullptr` default.
   - TC `WorldScript::OnConfigLoad(bool)` vs ACore split into `OnBeforeConfigLoad(bool)` + `OnAfterConfigLoad(bool)`.
   - TC `CreatureScript` only has `GetAI()`. ACore adds `OnGossipHello`, `OnGossipSelect`, `OnQuestAccept`, `OnQuestComplete`, `OnQuestReward`, etc.
   - TC `UnitScript` has 5 hooks. ACore has ~30+.
   - TC `PlayerScript` has ~20 hooks. ACore has ~100+.
5. **ScriptRegistry API**: ACore uses `ScriptPointerList` (public static map), `EnabledHooks`. TC uses `Instance()->GetScripts()` singleton.
6. **Dispatch helpers**: ACore uses `ExecuteScript<T>()`, `CALL_ENABLED_HOOKS`. TC uses `FOREACH_SCRIPT`, `GET_SCRIPT`.
7. **Module loader**: ACore has CMake auto-discovery of `modules/` directory. TC has none.
8. **Namespace**: ACore uses `Acore::`, TC uses `Trinity::`.

---

## Estimated Total Scope

| Phase | New/Modified Lines | Risk |
|-------|-------------------|------|
| Phase 1 | ~5000 new, ~500 modified | Medium |
| Phase 2 | ~2000 new, ~3000 modified across core | High |
| Phase 3 | ~1500 new (mostly CMake) | Low |
| **Total** | **~12,000 lines** | |

---

## Recommended Order

Start with Phase 1.4 (`All*Script` stubs) + Phase 3 (module loader) — that alone gets you to "modules compile and register, hooks exist but many are no-ops." Then wire hooks incrementally in Phase 2 based on which modules you actually want to port first.

---

## Reference Files

### TrinityCore (to modify)
- `src/server/game/Scripting/ScriptMgr.h` — monolithic, all script type classes
- `src/server/game/Scripting/ScriptMgr.cpp` — ScriptRegistry, dispatch macros, all method implementations

### AzerothCore (reference)
- `src/server/game/Scripting/ScriptMgr.h` — slimmer, delegates to ScriptDefines/
- `src/server/game/Scripting/ScriptObject.h` — base class with extended constructor
- `src/server/game/Scripting/ScriptMgrMacros.h` — dispatch templates
- `src/server/game/Scripting/ScriptDefines/` — one `.h`/`.cpp` per script type
- `src/server/game/Scripting/ScriptDefines/AllScriptsObjects.h` — umbrella header
- `modules/CMakeLists.txt` — module loader CMake infrastructure