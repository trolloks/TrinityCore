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

#ifndef SCRIPT_DEFINES_ALL_SCRIPTS_OBJECTS_H_
#define SCRIPT_DEFINES_ALL_SCRIPTS_OBJECTS_H_

// All*Script classes (global interceptors — fire for all objects, not DB-bound)
#include "AllBattlegroundScript.h"
#include "AllCommandScript.h"
#include "AllCreatureScript.h"
#include "AllGameObjectScript.h"
#include "AllItemScript.h"
#include "AllMapScript.h"
#include "AllSpellScript.h"

// Missing script types (stubs for AzerothCore module compatibility)
#include "ArenaScript.h"
#include "GameEventScript.h"
#include "GlobalScript.h"
#include "LootScript.h"
#include "MailScript.h"
#include "ModuleScript.h"
#include "PetScript.h"
#include "WorldObjectScript.h"

// Core ScriptMgr (includes ScriptObject, all base script types, ScriptRegistry)
#include "ScriptMgr.h"

#endif // SCRIPT_DEFINES_ALL_SCRIPTS_OBJECTS_H_
