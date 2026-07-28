# CMake minimum version
cmake_minimum_required(VERSION 3.15)

# Project name and languages
project(Mcu_basic LANGUAGES C CXX ASM)

# Specify the compiler toolchain for ARM Cortex-M4 (STM32F4)
set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR arm)
set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)

# Path to the ARM GCC toolchain (adjust if needed)
# You can set this via environment variable or directly here
# set(CMAKE_C_COMPILER "arm-none-eabi-gcc")
# set(CMAKE_CXX_COMPILER "arm-none-eabi-g++")
# set(CMAKE_ASM_COMPILER "arm-none-eabi-gcc")

# Enable debugging and optimization flags for MCU
set(COMMON_FLAGS "-mcpu=cortex-m4 -mthumb -Wall -Wextra -ffunction-sections -fdata-sections")
set(DEBUG_FLAGS "-g -Og")
set(RELEASE_FLAGS "-O2")

# Choose build type (Debug or Release). Default to Debug.
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif()

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(CMAKE_C_FLAGS "${COMMON_FLAGS} ${DEBUG_FLAGS}")
    set(CMAKE_CXX_FLAGS "${COMMON_FLAGS} ${DEBUG_FLAGS}")
else()
    set(CMAKE_C_FLAGS "${COMMON_FLAGS} ${RELEASE_FLAGS}")
    set(CMAKE_CXX_FLAGS "${COMMON_FLAGS} ${RELEASE_FLAGS}")
endif()

# Linker flags
set(LINKER_FLAGS "-T${CMAKE_SOURCE_DIR}/STM32F407VGTX_FLASH.ld -Wl,--gc-sections -Wl,-Map=${PROJECT_NAME}.map")
set(CMAKE_EXE_LINKER_FLAGS "${LINKER_FLAGS}")

# Include directories
include_directories(
    ${CMAKE_SOURCE_DIR}/Src
    ${CMAKE_SOURCE_DIR}/drivers
    ${CMAKE_SOURCE_DIR}/Startup
)

# Source files
file(GLOB_RECURSE SOURCES
    "${CMAKE_SOURCE_DIR}/Src/*.c"
    "${CMAKE_SOURCE_DIR}/Src/*.cpp"
    "${CMAKE_SOURCE_DIR}/drivers/*.c"
    "${CMAKE_SOURCE_DIR}/drivers/*.cpp"
    "${CMAKE_SOURCE_DIR}/Startup/*.s"
)

add_executable(${PROJECT_NAME}.elf ${SOURCES})

# Post-build actions: generate binary and hex files
add_custom_command(TARGET ${PROJECT_NAME}.elf POST_BUILD
    COMMAND ${CMAKE_OBJCOPY} -O binary $<TARGET_FILE:${PROJECT_NAME}.elf> ${PROJECT_NAME}.bin
    COMMAND ${CMAKE_OBJCOPY} -O ihex $<TARGET_FILE:${PROJECT_NAME}.elf> ${PROJECT_NAME}.hex
    COMMENT "Generating .bin and .hex files"
)

# Size information after build
add_custom_command(TARGET ${PROJECT_NAME}.elf POST_BUILD
    COMMAND ${CMAKE_SIZE} $<TARGET_FILE:${PROJECT_NAME}.elf>
    COMMENT "Printing size information"
)
