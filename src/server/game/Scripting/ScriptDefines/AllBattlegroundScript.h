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

#ifndef SCRIPT_DEFINES_ALL_BATTLEGROUND_SCRIPT_H_
#define SCRIPT_DEFINES_ALL_BATTLEGROUND_SCRIPT_H_

#include "ScriptMgr.h"
#include "DBCEnums.h"
#include "ObjectGuid.h"
#include "SharedDefines.h"

class BattlegroundQueue;
struct GroupQueueInfo;
struct PvPDifficultyEntry;

class TC_GAME_API AllBattlegroundScript : public ScriptObject
{
protected:
    AllBattlegroundScript(char const* name, uint16 totalAvailableHooks = 0);

public:
    [[nodiscard]] bool IsDatabaseBound() const override { return false; }

    // Called before a battleground starts.
    virtual void OnBattlegroundStart(Battleground* /*bg*/) { }

    // Called for each player at end-of-battleground reward.
    virtual void OnBattlegroundEndReward(Battleground* /*bg*/, Player* /*player*/, TeamId /*winnerTeamId*/) { }

    // Called every battleground update tick.
    virtual void OnBattlegroundUpdate(Battleground* /*bg*/, uint32 /*diff*/) { }

    // Called when a player is added to a battleground.
    virtual void OnBattlegroundAddPlayer(Battleground* /*bg*/, Player* /*player*/) { }

    // Called just before a player is added to a battleground.
    virtual void OnBattlegroundBeforeAddPlayer(Battleground* /*bg*/, Player* /*player*/) { }

    // Called when a player leaves a battleground.
    virtual void OnBattlegroundRemovePlayerAtLeave(Battleground* /*bg*/, Player* /*player*/) { }

    // Called on BG queue update.
    virtual void OnQueueUpdate(BattlegroundQueue* /*queue*/, uint32 /*diff*/, BattlegroundTypeId /*bgTypeId*/,
        BattlegroundBracketId /*bracketId*/, uint8 /*arenaType*/, bool /*isRated*/, uint32 /*arenaRating*/) { }

    // Called on BG queue update - return false to skip the update.
    [[nodiscard]] virtual bool OnQueueUpdateValidity(BattlegroundQueue* /*queue*/, uint32 /*diff*/, BattlegroundTypeId /*bgTypeId*/,
        BattlegroundBracketId /*bracketId*/, uint8 /*arenaType*/, bool /*isRated*/, uint32 /*arenaRating*/) { return true; }

    // Called when a group is added to the BG queue.
    virtual void OnAddGroup(BattlegroundQueue* /*queue*/, GroupQueueInfo* /*ginfo*/, uint32& /*index*/,
        Player* /*leader*/, Group* /*group*/, BattlegroundTypeId /*bgTypeId*/,
        PvPDifficultyEntry const* /*bracketEntry*/, uint8 /*arenaType*/, bool /*isRated*/,
        bool /*isPremade*/, uint32 /*arenaRating*/, uint32 /*matchmakerRating*/,
        uint32 /*arenaTeamId*/, uint32 /*opponentsArenaTeamId*/) { }

    // Called to check if players can fill the BG.
    [[nodiscard]] virtual bool CanFillPlayersToBG(BattlegroundQueue* /*queue*/, Battleground* /*bg*/,
        BattlegroundBracketId /*bracketId*/) { return true; }

    // Called to check if a normal match should be done.
    [[nodiscard]] virtual bool IsCheckNormalMatch(BattlegroundQueue* /*queue*/, Battleground* /*bgTemplate*/,
        BattlegroundBracketId /*bracketId*/, uint32 /*minPlayers*/, uint32 /*maxPlayers*/) { return false; }

    // Called to check if a BG queue message can be sent.
    [[nodiscard]] virtual bool CanSendMessageBGQueue(BattlegroundQueue* /*queue*/, Player* /*leader*/,
        Battleground* /*bg*/, PvPDifficultyEntry const* /*bracketEntry*/) { return true; }

    // Called before the arena join message is sent.
    [[nodiscard]] virtual bool OnBeforeSendJoinMessageArenaQueue(BattlegroundQueue* /*queue*/, Player* /*leader*/,
        GroupQueueInfo* /*ginfo*/, PvPDifficultyEntry const* /*bracketEntry*/, bool /*isRated*/) { return true; }

    // Called before the arena exit message is sent.
    [[nodiscard]] virtual bool OnBeforeSendExitMessageArenaQueue(BattlegroundQueue* /*queue*/,
        GroupQueueInfo* /*ginfo*/) { return true; }

    // Called after a battleground ends.
    virtual void OnBattlegroundEnd(Battleground* /*bg*/, TeamId /*winnerTeamId*/) { }

    // Called before a battleground is destroyed.
    virtual void OnBattlegroundDestroy(Battleground* /*bg*/) { }

    // Called after a battleground is created.
    virtual void OnBattlegroundCreate(Battleground* /*bg*/) { }

    // Called to check if a group can be added to the matching pool.
    [[nodiscard]] virtual bool CanAddGroupToMatchingPool(BattlegroundQueue* /*queue*/, GroupQueueInfo* /*group*/,
        uint32 /*poolPlayerCount*/, Battleground* /*bg*/, BattlegroundBracketId /*bracketId*/) { return true; }

    // Called to get a player's matchmaking rating.
    [[nodiscard]] virtual bool GetPlayerMatchmakingRating(ObjectGuid /*playerGuid*/,
        BattlegroundTypeId /*bgTypeId*/, float& /*outRating*/) { return false; }
};

// Compatibility alias for AzerothCore modules
using BGScript = AllBattlegroundScript;

#endif // SCRIPT_DEFINES_ALL_BATTLEGROUND_SCRIPT_H_
