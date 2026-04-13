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

#ifndef SCRIPTMGRMACROS_H_
#define SCRIPTMGRMACROS_H_

#include "ScriptMgr.h"
#include <functional>

// Execute a hook on all registered scripts of type ScriptName.
template<typename ScriptName>
inline void ExecuteScript(std::function<void(ScriptName*)> executeHook)
{
    auto& scripts = ScriptRegistry<ScriptName>::Instance()->GetScripts();
    if (scripts.empty())
        return;

    for (auto const& entry : scripts)
        executeHook(entry.second.get());
}

// Returns Optional<true> if any script returns true, Optional<false> if none did,
// empty Optional if no scripts are registered.
template<typename ScriptName>
inline Optional<bool> IsValidBoolScript(std::function<bool(ScriptName*)> executeHook)
{
    auto& scripts = ScriptRegistry<ScriptName>::Instance()->GetScripts();
    if (scripts.empty())
        return {};

    for (auto const& entry : scripts)
    {
        if (executeHook(entry.second.get()))
            return true;
    }

    return false;
}

// Returns the first non-null CreatureAI* (or T*) returned by any script.
template<typename ScriptName, class T>
inline T* GetReturnAIScript(std::function<T*(ScriptName*)> executeHook)
{
    auto& scripts = ScriptRegistry<ScriptName>::Instance()->GetScripts();
    if (scripts.empty())
        return nullptr;

    for (auto const& entry : scripts)
    {
        if (T* result = executeHook(entry.second.get()))
            return result;
    }

    return nullptr;
}

inline bool ReturnValidBool(Optional<bool> ret, bool need = false)
{
    return ret && *ret ? need : !need;
}

#endif // SCRIPTMGRMACROS_H_
