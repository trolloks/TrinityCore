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

#ifndef SCRIPT_DEFINES_PET_SCRIPT_H_
#define SCRIPT_DEFINES_PET_SCRIPT_H_

#include "ScriptMgr.h"

class Guardian;
class Pet;

class TC_GAME_API PetScript : public ScriptObject
{
protected:
    PetScript(char const* name, uint16 totalAvailableHooks = 0);

public:
    [[nodiscard]] bool IsDatabaseBound() const override { return false; }

    // Called when a guardian/pet initializes stats for a given level.
    virtual void OnInitStatsForLevel(Guardian* /*guardian*/, uint8 /*petLevel*/) { }

    // Called when calculating max talent points for a pet level.
    virtual void OnCalculateMaxTalentPointsForLevel(Pet* /*pet*/, uint8 /*level*/, uint8& /*points*/) { }

    // Called when checking if a pet can unlearn a set spell.
    [[nodiscard]] virtual bool CanUnlearnSpellSet(Pet* /*pet*/, uint32 /*level*/, uint32 /*spell*/) { return true; }

    // Called when checking if a pet can unlearn a default spell.
    [[nodiscard]] virtual bool CanUnlearnSpellDefault(Pet* /*pet*/, SpellInfo const* /*spellInfo*/) { return true; }

    // Called when checking if a pet can reset talents.
    [[nodiscard]] virtual bool CanResetTalents(Pet* /*pet*/) { return true; }

    // Called after a pet is added to the world.
    virtual void OnPetAddToWorld(Pet* /*pet*/) { }
};

#endif // SCRIPT_DEFINES_PET_SCRIPT_H_
