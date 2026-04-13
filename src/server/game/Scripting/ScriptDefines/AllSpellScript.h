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

#ifndef SCRIPT_DEFINES_ALL_SPELL_SCRIPT_H_
#define SCRIPT_DEFINES_ALL_SPELL_SCRIPT_H_

#include "ScriptMgr.h"
#include "SharedDefines.h"

class Aura;
class AuraEffect;

class TC_GAME_API AllSpellScript : public ScriptObject
{
protected:
    AllSpellScript(char const* name, uint16 totalAvailableHooks = 0);

public:
    [[nodiscard]] bool IsDatabaseBound() const override { return false; }

    // Called when calculating the max duration of an aura.
    virtual void OnCalcMaxDuration(Aura const* /*aura*/, int32& /*maxDuration*/) { }

    // Called when a spell checks its cast result.
    virtual void OnSpellCheckCast(Spell* /*spell*/, bool /*strict*/, SpellCastResult& /*res*/) { }

    // Called when a spell is being prepared to cast.
    [[nodiscard]] virtual bool CanPrepare(Spell* /*spell*/, SpellCastTargets const* /*targets*/, AuraEffect const* /*triggeredByAura*/) { return true; }

    // Called after a spell dummy effect fires on a game object target.
    virtual void OnDummyEffect(WorldObject* /*caster*/, uint32 /*spellID*/, SpellEffIndex /*effIndex*/, GameObject* /*gameObjTarget*/) { }

    // Called after a spell dummy effect fires on a creature target.
    virtual void OnDummyEffect(WorldObject* /*caster*/, uint32 /*spellID*/, SpellEffIndex /*effIndex*/, Creature* /*creatureTarget*/) { }

    // Called after a spell dummy effect fires on an item target.
    virtual void OnDummyEffect(WorldObject* /*caster*/, uint32 /*spellID*/, SpellEffIndex /*effIndex*/, Item* /*itemTarget*/) { }

    // Called when a spell cast is cancelled.
    virtual void OnSpellCastCancel(Spell* /*spell*/, Unit* /*caster*/, SpellInfo const* /*spellInfo*/, bool /*bySelf*/) { }

    // Called when a spell is cast.
    virtual void OnSpellCast(Spell* /*spell*/, Unit* /*caster*/, SpellInfo const* /*spellInfo*/, bool /*skipCheck*/) { }

    // Called when a spell is prepared.
    virtual void OnSpellPrepare(Spell* /*spell*/, Unit* /*caster*/, SpellInfo const* /*spellInfo*/) { }

    // Called to check if a spell can scale everything (ACore compat).
    [[nodiscard]] virtual bool CanScalingEverything(Spell* /*spell*/) { return false; }

    // Called to check if a spell can select spec talent (ACore compat).
    [[nodiscard]] virtual bool CanSelectSpecTalent(Spell* /*spell*/) { return true; }

    // Called before selecting the aura rank for a given level.
    virtual void OnBeforeAuraRankForLevel(SpellInfo const* /*spellInfo*/, SpellInfo const* /*latestSpellInfo*/, uint8 /*level*/) { }
};

// Compatibility alias for AzerothCore modules
using SpellSC = AllSpellScript;

#endif // SCRIPT_DEFINES_ALL_SPELL_SCRIPT_H_
