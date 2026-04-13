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

#ifndef SCRIPT_DEFINES_GAME_EVENT_SCRIPT_H_
#define SCRIPT_DEFINES_GAME_EVENT_SCRIPT_H_

#include "ScriptMgr.h"

class TC_GAME_API GameEventScript : public ScriptObject
{
protected:
    GameEventScript(char const* name, uint16 totalAvailableHooks = 0);

public:
    [[nodiscard]] bool IsDatabaseBound() const override { return false; }

    // Called when a game event starts.
    virtual void OnStart(uint16 /*eventId*/) { }

    // Called when a game event stops.
    virtual void OnStop(uint16 /*eventId*/) { }

    // Called when a game event is checked.
    virtual void OnEventCheck(uint16 /*eventId*/) { }
};

#endif // SCRIPT_DEFINES_GAME_EVENT_SCRIPT_H_
