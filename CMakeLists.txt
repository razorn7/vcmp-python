# CMakeList.txt: projeto de CMake para vcmp-python, incluir origem e definir
# lógica específica a um projeto aqui.
#
cmake_minimum_required (VERSION 3.8)

# Habilite a Recarga Dinâmica para compiladores MSVC, se houver suporte.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("vcmp-python")

set(MODULE_FILES
	core.cpp
	core.h

    vcmp/callbacks/callbacks.cpp
    vcmp/callbacks/callbacks.h

    vcmp/classes/entity/checkpoint.cpp
    vcmp/classes/entity/checkpoint.h
    vcmp/classes/entity/object.cpp
    vcmp/classes/entity/object.h
    vcmp/classes/entity/pickup.cpp
    vcmp/classes/entity/pickup.h
    vcmp/classes/entity/player.cpp
    vcmp/classes/entity/player.h
    vcmp/classes/entity/vehicle.cpp
    vcmp/classes/entity/vehicle.h

    vcmp/classes/generic/game.cpp
    vcmp/classes/generic/game.h
    vcmp/classes/generic/key.cpp
    vcmp/classes/generic/key.h
    vcmp/classes/generic/server.cpp
    vcmp/classes/generic/server.h
    vcmp/classes/generic/stream.cpp
    vcmp/classes/generic/stream.h

    vcmp/classes/utility/console.cpp
    vcmp/classes/utility/console.h
    vcmp/classes/utility/event_manager.cpp
    vcmp/classes/utility/event_manager.h
    vcmp/classes/utility/utility.cpp
    vcmp/classes/utility/utility.h
)

include_directories(${CMAKE_CURRENT_LIST_DIR}/vendor)
include_directories(C:\\Python\\Python311\\include)
link_directories(C:\\Python\\Python311\\libs)

add_library(vcmp-python SHARED ${MODULE_FILES})

# Don't prefix the module binary.
set_target_properties(vcmp-python PROPERTIES PREFIX "")
# Customize module binary name/
if(WIN32)
    if(CMAKE_SIZEOF_VOID_P EQUAL 8 AND NOT FORCE_32BIT_BIN)
        set_target_properties(vcmp-python PROPERTIES OUTPUT_NAME "python_64")
    else()
        set_target_properties(vcmp-python PROPERTIES OUTPUT_NAME "python_32")
    endif()
else(WIN32)
    if(CMAKE_SIZEOF_VOID_P EQUAL 8 AND NOT FORCE_32BIT_BIN)
        set_target_properties(vcmp-python PROPERTIES OUTPUT_NAME "python_64")
    else()
        set_target_properties(vcmp-python PROPERTIES OUTPUT_NAME "python_32")
    endif()
endif(WIN32)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET vcmp-python PROPERTY CXX_STANDARD 20)
endif()

# TODO: Adicione testes e instale destinos, se necessário.

if (${CMAKE_SYSTEM_NAME} MATCHES "Linux")
    set(CMAKE_POSITION_INDEPENDENT_CODE ON)
endif()
