set(PROJECT_NAME minimize)

################################################################################
# Source groups
################################################################################
set(Header_Files
    "common.h"
    "Constants.h"
    "Logger.hpp"
    "ProgramArguments.h"
)
source_group("Header Files" FILES ${Header_Files})

set(Header_Files__Common
    "CommonMachineAlgorithm.hpp"
    "MachineMinimizer.hpp"
)
source_group("Header Files\\Common" FILES ${Header_Files__Common})

set(Header_Files__Common__Abstract
    "AbstractState.h"
    "AbstractTransition.hpp"
    "Label.h"
)
source_group("Header Files\\Common\\Abstract" FILES ${Header_Files__Common__Abstract})

set(Header_Files__Mealy
    "MealyMachine.h"
    "MealyState.h"
    "MealyTransition.h"
)
source_group("Header Files\\Mealy" FILES ${Header_Files__Mealy})

set(Header_Files__Moore
    "MooreMachine.h"
    "MooreState.h"
    "MooreTransition.h"
)
source_group("Header Files\\Moore" FILES ${Header_Files__Moore})

set(Source_Files
    "AbstractState.cpp"
    "main.cpp"
    "ProgramArguments.cpp"
)
source_group("Source Files" FILES ${Source_Files})

set(Source_Files__Mealy
    "MealyMachine.cpp"
    "MealyState.cpp"
    "MealyTransition.cpp"
)
source_group("Source Files\\Mealy" FILES ${Source_Files__Mealy})

set(Source_Files__Moore
    "MooreMachine.cpp"
    "MooreState.cpp"
    "MooreTransition.cpp"
)
source_group("Source Files\\Moore" FILES ${Source_Files__Moore})

set(ALL_FILES
    ${Header_Files}
    ${Header_Files__Common}
    ${Header_Files__Common__Abstract}
    ${Header_Files__Mealy}
    ${Header_Files__Moore}
    ${Source_Files}
    ${Source_Files__Mealy}
    ${Source_Files__Moore}
)

################################################################################
# Target
################################################################################
add_executable(${PROJECT_NAME} ${ALL_FILES})

use_props(${PROJECT_NAME} "${CMAKE_CONFIGURATION_TYPES}" "${DEFAULT_CXX_PROPS}")
set(ROOT_NAMESPACE minimize)

set_target_properties(${PROJECT_NAME} PROPERTIES
    VS_GLOBAL_KEYWORD "Win32Proj"
)
if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64")
    set_target_properties(${PROJECT_NAME} PROPERTIES
        INTERPROCEDURAL_OPTIMIZATION_RELEASE "TRUE"
    )
elseif("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x86")
    set_target_properties(${PROJECT_NAME} PROPERTIES
        INTERPROCEDURAL_OPTIMIZATION_RELEASE "TRUE"
    )
endif()
################################################################################
# Compile definitions
################################################################################
if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64")
    target_compile_definitions(${PROJECT_NAME} PRIVATE
        "$<$<CONFIG:Debug>:"
            "_DEBUG"
        ">"
        "$<$<CONFIG:Release>:"
            "NDEBUG"
        ">"
        "_CONSOLE;"
        "UNICODE;"
        "_UNICODE"
    )
elseif("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x86")
    target_compile_definitions(${PROJECT_NAME} PRIVATE
        "$<$<CONFIG:Debug>:"
            "_DEBUG"
        ">"
        "$<$<CONFIG:Release>:"
            "NDEBUG"
        ">"
        "WIN32;"
        "_CONSOLE;"
        "UNICODE;"
        "_UNICODE"
    )
endif()

################################################################################
# Compile and link options
################################################################################
if(MSVC)
    if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64")
        target_compile_options(${PROJECT_NAME} PRIVATE
            $<$<CONFIG:Debug>:
                /std:c++17;
                /Y-
            >
            $<$<CONFIG:Release>:
                /Oi;
                /Gy
            >
            /permissive-;
            /sdl;
            /W3;
            ${DEFAULT_CXX_DEBUG_INFORMATION_FORMAT};
            ${DEFAULT_CXX_EXCEPTION_HANDLING}
        )
    elseif("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x86")
        target_compile_options(${PROJECT_NAME} PRIVATE
            $<$<CONFIG:Release>:
                /Oi;
                /Gy
            >
            /permissive-;
            /sdl;
            /W3;
            ${DEFAULT_CXX_DEBUG_INFORMATION_FORMAT};
            ${DEFAULT_CXX_EXCEPTION_HANDLING}
        )
    endif()
    if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64")
        target_link_options(${PROJECT_NAME} PRIVATE
            $<$<CONFIG:Debug>:
                /INCREMENTAL
            >
            $<$<CONFIG:Release>:
                /OPT:REF;
                /OPT:ICF;
                /INCREMENTAL:NO
            >
            /DEBUG;
            /SUBSYSTEM:CONSOLE
        )
    elseif("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x86")
        target_link_options(${PROJECT_NAME} PRIVATE
            $<$<CONFIG:Debug>:
                /INCREMENTAL
            >
            $<$<CONFIG:Release>:
                /OPT:REF;
                /OPT:ICF;
                /INCREMENTAL:NO
            >
            /DEBUG;
            /SUBSYSTEM:CONSOLE
        )
    endif()
endif()

