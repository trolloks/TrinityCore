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

#ifndef SCRIPT_DEFINES_ALL_CREATURE_SCRIPT_H_
#define SCRIPT_DEFINES_ALL_CREATURE_SCRIPT_H_

#include "ScriptMgr.h"

class TC_GAME_API AllCreatureScript : public ScriptObject
{
protected:
    AllCreatureScript(char const* name, uint16 totalAvailableHooks = 0);

public:
    [[nodiscard]] bool IsDatabaseBound() const override { return false; }

    // Called from End of Creature Update.
    virtual void OnAllCreatureUpdate(Creature* /*creature*/, uint32 /*diff*/) { }

    // Called just before the level of the creature is set.
    virtual void OnBeforeCreatureSelectLevel(CreatureTemplate const* /*cinfo*/, Creature* /*creature*/, uint8& /*level*/) { }

    // Called from End of Creature SelectLevel.
    virtual void OnCreatureSelectLevel(CreatureTemplate const* /*cinfo*/, Creature* /*creature*/) { }

    // Called after creature is added to world.
    virtual void OnCreatureAddWorld(Creature* /*creature*/) { }

    // Called after creature is removed from world.
    virtual void OnCreatureRemoveWorld(Creature* /*creature*/) { }

    // Called after creature has been saved to DB.
    virtual void OnCreatureSaveToDB(Creature* /*creature*/) { }

    // Called when a player opens a gossip dialog with the creature.
    // Return false to continue, true to disable.
    [[nodiscard]] virtual bool CanCreatureGossipHello(Player* /*player*/, Creature* /*creature*/) { return false; }

    // Called when a player selects a gossip item in the creature's gossip menu.
    // Return false to continue, true to disable.
    [[nodiscard]] virtual bool CanCreatureGossipSelect(Player* /*player*/, Creature* /*creature*/, uint32 /*sender*/, uint32 /*action*/) { return false; }

    // Called when a player selects a gossip with a code in the creature's gossip menu.
    // Return false to continue, true to disable.
    [[nodiscard]] virtual bool CanCreatureGossipSelectCode(Player* /*player*/, Creature* /*creature*/, uint32 /*sender*/, uint32 /*action*/, char const* /*code*/) { return false; }

    // Called when a player accepts a quest from the creature.
    [[nodiscard]] virtual bool CanCreatureQuestAccept(Player* /*player*/, Creature* /*creature*/, Quest const* /*quest*/) { return false; }

    // Called when a player selects a quest reward.
    [[nodiscard]] virtual bool CanCreatureQuestReward(Player* /*player*/, Creature* /*creature*/, Quest const* /*quest*/, uint32 /*opt*/) { return false; }

    // Called when a CreatureAI object is needed for the creature.
    [[nodiscard]] virtual CreatureAI* GetCreatureAI(Creature* /*creature*/) const { return nullptr; }

    // Called whenever the UNIT_BYTE2_FLAG_FFA_PVP bit is set on the creature.
    virtual void OnFfaPvpStateUpdate(Creature* /*creature*/, bool /*inPvp*/) { }
};

#endif // SCRIPT_DEFINES_ALL_CREATURE_SCRIPT_H_
