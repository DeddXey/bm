cmake_minimum_required(VERSION 3.12)

set(TOOLCHAIN_PREFIX "arm-none-eabi-")
set(TOOLCHAIN_POSTFIX ".exe")

set(CMAKE_C_COMPILER "${TOOLCHAIN_PREFIX}gcc${TOOLCHAIN_POSTFIX}")
set(CMAKE_CXX_COMPILER "${TOOLCHAIN_PREFIX}g++${TOOLCHAIN_POSTFIX}")

set(CMAKE_C_COMPILER_FORCED TRUE) # force compiler to avoid failing compiler tests
set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY) # It is important for test crosscompiling
set(CMAKE_CROSSCOMPILING TRUE)
set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR arm)

set(OBJCOPY "${TOOLCHAIN_PREFIX}objcopy${TOOLCHAIN_POSTFIX}")
set(SIZE ${TOOLCHAIN_PREFIX}size${TOOLCHAIN_POSTFIX})
set(OBJDUMP ${TOOLCHAIN_PREFIX}objdump${TOOLCHAIN_POSTFIX})

function(make_hex target)
add_custom_target(hex
            DEPENDS ${target}
            COMMAND ${OBJCOPY} -O ihex ${target} ${target}.hex
            WORKING_DIRECTORY ${CMAKE_BINARY_DIR})
endfunction()

function(make_size target)
    add_custom_target(size
            DEPENDS ${target}
            COMMAND ${SIZE} ${target}
            WORKING_DIRECTORY ${CMAKE_BINARY_DIR})
endfunction()

function(make_disassembly target)
    add_custom_target(disassembly
            DEPENDS ${target}
            COMMAND ${OBJDUMP} -S ${target} > ${target}.S
            WORKING_DIRECTORY ${CMAKE_BINARY_DIR})
endfunction()