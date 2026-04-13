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

#ifndef SCRIPT_DEFINES_ARENA_SCRIPT_H_
#define SCRIPT_DEFINES_ARENA_SCRIPT_H_

#include "ScriptMgr.h"
#include "ObjectGuid.h"

// Note: ArenaTeam does not exist in Cataclysm (replaced by rated BG teams / new arena system).
// These hooks are provided for compatibility with AzerothCore modules; they will not fire
// if the ArenaTeam system is absent. Stub implementations are provided.

class TC_GAME_API ArenaScript : public ScriptObject
{
protected:
    ArenaScript(char const* name, uint16 totalAvailableHooks = 0);

public:
    [[nodiscard]] bool IsDatabaseBound() const override { return false; }

    // Called to check if a player can be added to an arena team.
    [[nodiscard]] virtual bool CanAddMember(void* /*team*/, ObjectGuid /*playerGuid*/) { return true; }

    // Called when arena points are calculated.
    virtual void OnGetPoints(void* /*team*/, uint32 /*memberRating*/, float& /*points*/) { }

    // Called before the arena win condition is checked.
    [[nodiscard]] virtual bool OnBeforeArenaCheckWinConditions(Battleground* const /*bg*/) { return true; }

    // Called to check if an arena team can be saved to DB.
    [[nodiscard]] virtual bool CanSaveToDB(void* /*team*/) { return true; }

    // Called when an arena starts.
    virtual void OnArenaStart(Battleground* /*bg*/) { }
};

#endif // SCRIPT_DEFINES_ARENA_SCRIPT_H_
