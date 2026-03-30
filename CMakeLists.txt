cmake_minimum_required(VERSION 3.15)

project(arm_cortex_m4_test)
set(EXECUTABLE ${PROJECT_NAME}.elf)

enable_language(C ASM)
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

set(CMAKE_LIBOPENCM3_DIR ${CMAKE_SOURCE_DIR}/libopencm3)
set(CMAKE_DRIVER_DIR ${CMAKE_SOURCE_DIR}/drivers)
# Specify the device type
add_definitions(-DSTM32F7)
set(CMAKE_TARGET_DEVICE stm32/f7)

# Use toolchain
set(CMAKE_TOOLCHAIN_FILE ${CMAKE_SOURCE_DIR}/cmake/arm-gcc-toolchain.cmake)

# C flags
#set(CMAKE_C_FLAGS "-Wall -Wextra -O2 -ffreestanding -nostartfiles -lm -mthumb -march=armv7-m -mtune=cortex-m4")

# ExternalProject: clone and build libopencm3
include(ExternalProject)
ExternalProject_Add(libopencm3_project
   SOURCE_DIR ${CMAKE_LIBOPENCM3_DIR}
   CONFIGURE_COMMAND ""
   BUILD_COMMAND make TARGETS=${CMAKE_TARGET_DEVICE} ARCH=cortex-m7 FP=hard
   BUILD_IN_SOURCE 1
   INSTALL_COMMAND ""
)

# Add include dir
include_directories(${CMAKE_LIBOPENCM3_INCLUDE_DIR})

# Executable target
add_executable(${EXECUTABLE} 
        ${CMAKE_SOURCE_DIR}/src/main.c
        ${CMAKE_DRIVER_DIR}/gpio/led_driver.c
        ${CMAKE_DRIVER_DIR}/memory/mamory.c
        ${CMAKE_DRIVER_DIR}/systick/systick.c    
)

# Add header path to target
target_include_directories(${EXECUTABLE}  PRIVATE 
    ${CMAKE_DRIVER_DIR}/global 
    ${CMAKE_DRIVER_DIR}/gpio
    ${CMAKE_DRIVER_DIR}/memory
    ${CMAKE_DRIVER_DIR}/systick
    ${CMAKE_LIBOPENCM3_DIR}/include
)

# Ensure libopencm3 is built first
add_dependencies(${EXECUTABLE} libopencm3_project)

# Link against pre-built libopencm3.a
target_link_libraries(${EXECUTABLE}
    ${CMAKE_LIBOPENCM3_DIR}/lib/libopencm3_stm32f7.a
)

# Compiler options
set(ARM_FLAGS -mcpu=cortex-m7
    -mfpu=fpv5-d16
    -mfloat-abi=hard
    -fdata-sections
    -ffunction-sections
    -O0
    -g3
    -Wall
    -Wextra
    -ffreestanding
    -nostartfiles
    -mthumb
    -lm
    -g
    -fverbose-asm
    -Wa,-adhln,-alms=${CMAKE_SOURCE_DIR}/src/main.S
)
target_compile_options(${EXECUTABLE} PRIVATE ${ARM_FLAGS})

# Linker options
set(LINKER_FLAGS -specs=nano.specs
    -specs=nosys.specs
    -lc
    -lgcc
    -lm
    -lnosys
    -Wl,-Map=${PROJECT_NAME}.map,--cref
    -Wl,--gc-sections
    -Xlinker -print-memory-usage -Xlinker
)

target_link_options(${EXECUTABLE} PRIVATE
        -T ${CMAKE_SOURCE_DIR}/stm32f7.ld
        ${ARM_FLAGS}
        ${LINKER_FLAGS}
)


# Optional: Print executable size as part of the post build process
add_custom_command(TARGET ${EXECUTABLE}
        POST_BUILD
        COMMAND ${CMAKE_SIZE_UTIL} ${EXECUTABLE}
)

# Optional: generate .bin and .hex
add_custom_command(TARGET ${EXECUTABLE} POST_BUILD
    COMMAND ${CMAKE_OBJCOPY} -O binary ${EXECUTABLE} ${PROJECT_NAME}.bin
    COMMAND ${CMAKE_OBJCOPY} -O ihex ${EXECUTABLE} ${PROJECT_NAME}.hex
)

# Optional: Flash executable to target
add_custom_target(flash
    DEPENDS ${EXECUTABLE}
    COMMAND st-flash write ${PROJECT_NAME}.bin 0x08000000
)