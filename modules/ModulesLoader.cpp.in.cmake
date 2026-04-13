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

// This file was generated automatically from your module configuration.
// Use CMake to reconfigure this file, never change it manually.

#cmakedefine TC_IS_DYNAMIC_SCRIPTLOADER

#include "Define.h"
#include <vector>
#include <string>

// Forward declarations of module loader functions
@TC_SCRIPTS_FORWARD_DECL@
#ifdef TC_IS_DYNAMIC_SCRIPTLOADER
#  include "revision.h"
#  define TC_MODULES_API TC_API_EXPORT
extern "C" {

TC_MODULES_API char const* GetScriptModule()
{
    return "@TC_CURRENT_SCRIPT_PROJECT@";
}

TC_MODULES_API char const* GetModulesBuildDirective()
{
    return _BUILD_DIRECTIVE;
}

#else
#  include "ModulesScriptLoader.h"
#  define TC_MODULES_API
#endif

TC_MODULES_API void AddModulesScripts()
{
@TC_SCRIPTS_INVOKE@}

#ifdef TC_IS_DYNAMIC_SCRIPTLOADER
} // extern "C"
#endif
