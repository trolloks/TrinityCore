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

include(ConfigureModules)

GetModuleSourceList(MODULES_MODULE_LIST)

if(USE_SCRIPTPCH)
  set(PRIVATE_PCH_HEADER ModulesPCH.h)
endif()

GroupSources(${CMAKE_CURRENT_SOURCE_DIR})

# Configures the script loader for a set of modules
function(ConfigureScriptLoader SCRIPTLOADER_NAME LOADER_OUT)
  unset(TC_SCRIPTS_FORWARD_DECL)
  unset(TC_SCRIPTS_INVOKE)

  set(TC_CURRENT_SCRIPT_PROJECT ${SCRIPTLOADER_NAME})
  set(TC_IS_DYNAMIC_SCRIPTLOADER OFF)

  foreach(LOCALE_SCRIPT_MODULE ${ARGN})
    string(REGEX REPLACE - "_" LOCALE_SCRIPT_MODULE ${LOCALE_SCRIPT_MODULE})
    set(LOADER_FUNCTION "Add${LOCALE_SCRIPT_MODULE}Scripts()")
    set(TC_SCRIPTS_FORWARD_DECL "${TC_SCRIPTS_FORWARD_DECL}void ${LOADER_FUNCTION};\n")
    set(TC_SCRIPTS_INVOKE       "${TC_SCRIPTS_INVOKE}    ${LOADER_FUNCTION};\n")
  endforeach()

  set(GENERATED_LOADER
    ${CMAKE_CURRENT_BINARY_DIR}/gen_scriptloader/${SCRIPTLOADER_NAME}/ModulesLoader.cpp)
  configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/ModulesLoader.cpp.in.cmake
    ${GENERATED_LOADER})
  set(${LOADER_OUT} ${GENERATED_LOADER} PARENT_SCOPE)
endfunction()

set(STATIC_SCRIPT_MODULES "")
set(MODULE_LIST "")
set(CONFIG_LIST "")

message(STATUS "* Modules configuration:")
message(STATUS "  |")

foreach(SOURCE_MODULE ${MODULES_MODULE_LIST})
  GetPathToModuleSource(${SOURCE_MODULE} MODULE_SOURCE_PATH)
  ModuleNameToVariable(${SOURCE_MODULE} MODULE_MODULE_VARIABLE)

  # Default to static if no explicit setting provided
  if(NOT DEFINED ${MODULE_MODULE_VARIABLE})
    set(${MODULE_MODULE_VARIABLE} "static")
  endif()

  if(${MODULE_MODULE_VARIABLE} STREQUAL "static")
    CollectSourceFiles(${MODULE_SOURCE_PATH} PRIVATE_SOURCES_MODULES)
    CollectIncludeDirectories(${MODULE_SOURCE_PATH} PUBLIC_INCLUDES)
    list(APPEND STATIC_SCRIPT_MODULES ${SOURCE_MODULE})
    set(MODULE_LIST "${MODULE_LIST}${SOURCE_MODULE},")
    message(STATUS "  +- ${SOURCE_MODULE} (static)")

    # Copy config files
    GetPathToModuleConfig(${SOURCE_MODULE} MODULE_CONFIG_PATH)
    file(GLOB MODULE_CONFIG_LIST RELATIVE ${MODULE_CONFIG_PATH} ${MODULE_CONFIG_PATH}/*.conf.dist)
    foreach(configFileName ${MODULE_CONFIG_LIST})
      CopyModuleConfig("${MODULE_CONFIG_PATH}/${configFileName}")
      string(REGEX REPLACE "\.dist$" "" configFileName ${configFileName})
      set(CONFIG_LIST "${CONFIG_LIST}${configFileName},")
      message(STATUS "  |  * ${configFileName}")
    endforeach()
  else()
    message(STATUS "  |  ${SOURCE_MODULE} (disabled)")
  endif()
endforeach()

message(STATUS "  |")
message(STATUS "")

ConfigureScriptLoader("static" SCRIPT_MODULE_PRIVATE_SCRIPTLOADER ${STATIC_SCRIPT_MODULES})

add_library(modules STATIC
  ModulesScriptLoader.h
  ${SCRIPT_MODULE_PRIVATE_SCRIPTLOADER}
  ${PRIVATE_SOURCES_MODULES})

target_link_libraries(modules
  PRIVATE
    trinity-core-interface
  PUBLIC
    game-interface)

target_include_directories(modules
  PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${PUBLIC_INCLUDES})

target_compile_options(modules
  INTERFACE
    -DAC_MODULES_LIST=$<1:"${MODULE_LIST}">
    -DCONFIG_FILE_LIST=$<1:"${CONFIG_LIST}">)

set_target_properties(modules
  PROPERTIES
    FOLDER "modules")

# Generate precompiled header
if(USE_SCRIPTPCH)
  add_cxx_pch(modules ${PRIVATE_PCH_HEADER})
endif()

# Allow each module to include its own optional cmake customisation
foreach(SOURCE_MODULE ${MODULES_MODULE_LIST})
  include("${CMAKE_SOURCE_DIR}/modules/${SOURCE_MODULE}/${SOURCE_MODULE}.cmake" OPTIONAL)
endforeach()
