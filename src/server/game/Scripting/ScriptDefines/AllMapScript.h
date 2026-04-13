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

#ifndef SCRIPT_DEFINES_ALL_MAP_SCRIPT_H_
#define SCRIPT_DEFINES_ALL_MAP_SCRIPT_H_

#include "ScriptMgr.h"

class InstanceMap;
class MapInstanced;

class TC_GAME_API AllMapScript : public ScriptObject
{
protected:
    AllMapScript(char const* name, uint16 totalAvailableHooks = 0);

public:
    [[nodiscard]] bool IsDatabaseBound() const override { return false; }

    // Called when a player enters any map.
    virtual void OnPlayerEnterAll(Map* /*map*/, Player* /*player*/) { }

    // Called when a player leaves any map.
    virtual void OnPlayerLeaveAll(Map* /*map*/, Player* /*player*/) { }

    // Called before creating an instance script.
    virtual void OnBeforeCreateInstanceScript(InstanceMap* /*instanceMap*/, InstanceScript** /*instanceData*/, bool /*load*/, std::string /*data*/, uint32 /*completedEncounterMask*/) { }

    // Called before destroying an instance.
    virtual void OnDestroyInstance(MapInstanced* /*mapInstanced*/, Map* /*map*/) { }

    // Called when any map is created.
    virtual void OnCreateMap(Map* /*map*/) { }

    // Called when any map is destroyed.
    virtual void OnDestroyMap(Map* /*map*/) { }

    // Called on every map update tick.
    virtual void OnMapUpdate(Map* /*map*/, uint32 /*diff*/) { }
};

#endif // SCRIPT_DEFINES_ALL_MAP_SCRIPT_H_
