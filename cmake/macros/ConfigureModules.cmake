#
# This file is part of the TrinityCore Project. See AUTHORS file for Copyright information
#
# This file is free software; as a special exception the author gives
# unlimited permission to copy and/or distribute it, with or without
# modifications, as long as this notice is preserved.
#
# This program is distributed in the hope that it will be useful, but
# WITHOUT ANY WARRANTY, to the extent permitted by law; without even the
# implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
#

# Returns the base path to the modules directory
function(GetModulesBasePath variable)
  set(${variable} "${CMAKE_SOURCE_DIR}/modules" PARENT_SCOPE)
endfunction()

# Stores the absolute path of the given module's src/ in the variable
function(GetPathToModuleSource module variable)
  GetModulesBasePath(MODULE_BASE_PATH)
  set(${variable} "${MODULE_BASE_PATH}/${module}/src" PARENT_SCOPE)
endfunction()

# Stores the project name for a given module name
function(GetProjectNameOfModuleName module variable)
  string(TOLOWER "mod_${module}" GENERATED_NAME)
  set(${variable} "${GENERATED_NAME}" PARENT_SCOPE)
endfunction()

# Discovers all modules under modules/ that have a src/ subdirectory
function(GetModuleSourceList variable)
  GetModulesBasePath(BASE_PATH)
  file(GLOB LOCALE_MODULE_LIST RELATIVE ${BASE_PATH} ${BASE_PATH}/*)

  set(RESULT_LIST)
  foreach(SOURCE_MODULE ${LOCALE_MODULE_LIST})
    GetPathToModuleSource(${SOURCE_MODULE} MODULE_SOURCE_PATH)
    if(IS_DIRECTORY ${MODULE_SOURCE_PATH})
      list(APPEND RESULT_LIST ${SOURCE_MODULE})
    endif()
  endforeach()
  set(${variable} ${RESULT_LIST} PARENT_SCOPE)
endfunction()

# Converts a module name like mod-playerbots into its CMake variable MODULE_MOD_PLAYERBOTS
function(ModuleNameToVariable module variable)
  string(TOUPPER ${module} UPPER_MODULE)
  string(REPLACE "-" "_" UPPER_MODULE ${UPPER_MODULE})
  set(${variable} "MODULE_${UPPER_MODULE}" PARENT_SCOPE)
endfunction()

# Stores the absolute path of the given module's conf/ directory in the variable
function(GetPathToModuleConfig module variable)
  GetModulesBasePath(MODULE_BASE_PATH)
  set(${variable} "${MODULE_BASE_PATH}/${module}/conf" PARENT_SCOPE)
endfunction()

# Copies a module config file to the build output
function(CopyModuleConfig configFile)
  get_filename_component(CONFIG_FILENAME ${configFile} NAME)
  configure_file(${configFile} ${CMAKE_BINARY_DIR}/bin/${CONFIG_FILENAME} COPYONLY)
endfunction()
