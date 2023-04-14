set(BM_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/..)
option(USE_DEBUG "Use debug messaging in console port" 1)

if (USE_DEBUG)
    set(DBG 1)
else ()
    set(DBG 0)
endif (USE_DEBUG)

if (NOT BM_CHIP)
    message("chip type should be defined")
    set(BM_CHIP "NO_CHIP")
endif ()

set(CORTEX_M3
        stm32f103
        )

set(CORTEX_M4
        stm32f429
        )

if (BM_CHIP IN_LIST CORTEX_M3)
    set (CORTEX cortex-m3)
    set (FPU 0)
endif ()

if (BM_CHIP IN_LIST CORTEX_M4)
    set (CORTEX cortex-m4)
    set (FPU 1)
endif ()

#include("${BM_DIRECTORY}/cmake/crosstools_arm.cmake")
include("${BM_DIRECTORY}/cmake/${BM_CHIP}.cmake")

file(GLOB BM_SRCS
        ${BM_DIRECTORY}/mcu/${BM_CHIP}/*.cpp
        ${BM_DIRECTORY}/sys/*.cpp
        )

include_directories(
        ${BM_DIRECTORY}/sys/
        ${BM_DIRECTORY}/core/${CORTEX}/
        ${BM_DIRECTORY}/mcu/${BM_CHIP}/include
        ${BM_DIRECTORY}
)

add_definitions(-DUSE_DEBUG=${DBG} -DFPU=${FPU} )

# Warnings
string(CONCAT BLD_OPT_FLAGS_CXX
        "-fno-rtti "
        "-Wctor-dtor-privacy "
        "-Wnon-virtual-dtor "
        "-Woverloaded-virtual "
        "-Wsign-promo "
        "-Wduplicated-branches "
        "-Wduplicated-cond "
        "-Wfloat-equal "
        "-Wshadow=compatible-local "
        "-Wcast-qual "
        "-Wconversion "
        "-Wzero-as-null-pointer-constant "
        "-Wextra-semi "
        "-Wsign-conversion "
        "-Wlogical-op   "
        )
set(BLD_DEBUG_FLAGS "-Og -g3 -ggdb3 -gdwarf-3 -femit-class-debug-always -g -ggnu-pubnames -femit-struct-debug-detailed=any")
set(BLD_OPT_FLAGS "-ffunction-sections -fdata-sections -ffreestanding -Og -fno-unwind-tables -fno-exceptions" )
set(CHECK_FLAGS "-Wall -Wpedantic -Wextra ")


string(CONCAT FLAGS_CXX
        " ${BLD_PLATFORM_FLAGS} "
        " ${CHECK_FLAGS} "
        " ${BLD_DEBUG_FLAGS} "
        " ${BLD_OPT_FLAGS} "
        " ${USER_OPTIMIZATION_FLAGS} "
        " ${BLD_OPT_FLAGS_CXX} "
        )

string(CONCAT FLAGS_C
        " ${BLD_PLATFORM_FLAGS} "
        " ${CHECK_FLAGS} "
        " ${BLD_DEBUG_FLAGS} "
        " ${BLD_OPT_FLAGS} "
        " ${USER_OPTIMIZATION_FLAGS} "
        )

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${FLAGS_C}")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${FLAGS_CXX}")
add_link_options(--specs=nano.specs
        --specs=nosys.specs
        -T ${BM_DIRECTORY}/mcu/${BM_CHIP}/ld/ld.ld
        -Wl,-Map,${PROJECT_NAME}.map
        -ffunction-sections
        -fdata-sections
        )