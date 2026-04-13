/*
 * This file is part of the TrinityCore Project. See AUTHORS file for Copyright information
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2 of the License, or (at your
 * option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef SCRIPT_DEFINES_GLOBAL_SCRIPT_H_
#define SCRIPT_DEFINES_GLOBAL_SCRIPT_H_

#include "ScriptMgr.h"
#include "ObjectGuid.h"
#include "DatabaseEnvFwd.h"
#include <list>
#include <map>

class ArenaTeam;
class LootStoreItem;
class SpellModifier;
struct Loot;
struct LootStore;
struct DungeonEncounter;

enum Difficulty : uint8;
enum EncounterCreditType : uint8;

// Global scripts fire for all events and are not database-bound.
class TC_GAME_API GlobalScript : public ScriptObject
{
protected:
    GlobalScript(char const* name, uint16 totalAvailableHooks = 0);

public:
    [[nodiscard]] bool IsDatabaseBound() const override { return false; }

    // Called when an item is deleted from the character database.
    virtual void OnItemDelFromDB(CharacterDatabaseTransaction /*trans*/, ObjectGuid::LowType /*itemGuid*/) { }

    // Called when a mirror image displays an item.
    virtual void OnMirrorImageDisplayItem(Item const* /*item*/, uint32& /*display*/) { }

    // Called after a loot ref count is updated.
    virtual void OnAfterRefCount(Player const* /*player*/, LootStoreItem* /*lootStoreItem*/, Loot& /*loot*/, bool /*canRate*/,
        uint16 /*lootMode*/, uint32& /*maxcount*/, LootStore const& /*store*/) { }

    // Called after a loot group amount is calculated.
    virtual void OnAfterCalculateLootGroupAmount(Player const* /*player*/, Loot& /*loot*/, uint16 /*lootMode*/,
        uint32& /*groupAmount*/, LootStore const& /*store*/) { }

    // Called before a drop item is added.
    virtual void OnBeforeDropAddItem(Player const* /*player*/, Loot& /*loot*/, bool /*canRate*/, uint16 /*lootMode*/,
        LootStoreItem* /*lootStoreItem*/, LootStore const& /*store*/) { }

    // Called when an item roll occurs.
    virtual bool OnItemRoll(Player const* /*player*/, LootStoreItem const* /*lootStoreItem*/, float& /*chance*/,
        Loot& /*loot*/, LootStore const& /*store*/) { return true; }

    // Called before equal-chance loot is evaluated.
    virtual bool OnBeforeLootEqualChanced(Player const* /*player*/, std::list<LootStoreItem*> /*equalChanced*/,
        Loot& /*loot*/, LootStore const& /*store*/) { return true; }

    // Called when dungeon locks are initialized for a player.
    virtual void OnInitializeLockedDungeons(Player* /*player*/, uint8& /*level*/, uint32& /*lockData*/) { }

    // Called after dungeon locks are initialized for a player.
    virtual void OnAfterInitializeLockedDungeons(Player* /*player*/) { }

    // Called before arena points are updated for a team.
    virtual void OnBeforeUpdateArenaPoints(ArenaTeam* /*at*/, std::map<ObjectGuid, uint32>& /*ap*/) { }

    // Called when a dungeon encounter state is updated.
    virtual void OnAfterUpdateEncounterState(Map* /*map*/, uint8 /*creditType*/, uint32 /*creditEntry*/,
        Unit* /*source*/, Difficulty /*difficulty*/, std::list<DungeonEncounter const*> const* /*encounters*/,
        uint32 /*dungeonCompleted*/, bool /*updated*/) { }

    // Called before the phase mask of a WorldObject is set.
    virtual void OnBeforeWorldObjectSetPhaseMask(WorldObject const* /*worldObject*/, uint32& /*oldPhaseMask*/,
        uint32& /*newPhaseMask*/, bool& /*useCombinedPhases*/, bool& /*update*/) { }

    // Called when checking if an aura spell is affected by a mod.
    virtual bool OnIsAffectedBySpellModCheck(SpellInfo const* /*affectSpell*/, SpellInfo const* /*checkSpell*/,
        SpellModifier const* /*mod*/) { return true; }

    // Called when checking negative healing bonus modifiers on a target.
    virtual bool OnSpellHealingBonusTakenNegativeModifiers(Unit const* /*target*/, Unit const* /*caster*/,
        SpellInfo const* /*spellInfo*/, float& /*val*/) { return false; }

    // Called after loading spell custom attributes.
    virtual void OnLoadSpellCustomAttr(SpellInfo* /*spell*/) { }

    // Called when checking if a player is allowed to see creature loot.
    virtual bool OnAllowedForPlayerLootCheck(Player const* /*player*/, ObjectGuid /*source*/) { return false; }

    // Called when checking if a player is allowed to loot a container.
    virtual bool OnAllowedToLootContainerCheck(Player const* /*player*/, ObjectGuid /*source*/) { return false; }

    // Called when an instance ID is removed from the database.
    virtual void OnInstanceIdRemoved(uint32 /*instanceId*/) { }

    // Called when a raid boss state is updated.
    virtual void OnBeforeSetBossState(uint32 /*id*/, uint32 /*newState*/, uint32 /*oldState*/,
        Map* /*instance*/) { }

    // Called when a GameObject is created by an instance script.
    virtual void AfterInstanceGameObjectCreate(Map* /*instance*/, GameObject* /*go*/) { }
};

#endif // SCRIPT_DEFINES_GLOBAL_SCRIPT_H_
