cmake_minimum_required(VERSION 3.15)

project(RE46C109_Programmer)
set(EXECUTABLE ${PROJECT_NAME}.elf)

enable_language(C ASM)
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

set(CMAKE_LIBOPENCM3_DIR ${CMAKE_SOURCE_DIR}/libopencm3)
set(CMAKE_DRIVER_DIR ${CMAKE_SOURCE_DIR}/drivers)
set(CMAKE_FREERTOS_DIR ${CMAKE_SOURCE_DIR}/freeRTOS)

# Specify the device type
add_definitions(-DSTM32L1)
set(CMAKE_TARGET_DEVICE stm32/l1)

# Use toolchain
set(CMAKE_TOOLCHAIN_FILE ${CMAKE_SOURCE_DIR}/cmake/arm-gcc-toolchain.cmake)


# C flags
set(CMAKE_C_FLAGS "-Wall -Wextra -O2 -ffreestanding -nostartfiles -lm -mthumb -march=armv7-m -mtune=cortex-m3")

# ExternalProject: clone and build libopencm3
include(ExternalProject)
ExternalProject_Add(libopencm3_project
   SOURCE_DIR ${CMAKE_LIBOPENCM3_DIR}
   CONFIGURE_COMMAND ""
   BUILD_COMMAND make TARGETS=${CMAKE_TARGET_DEVICE}
   BUILD_IN_SOURCE 1
   INSTALL_COMMAND ""
)


# Set FreeRTOS sources
set(FREERTOS_SRC
    ${CMAKE_FREERTOS_DIR}/source/croutine.c
    ${CMAKE_FREERTOS_DIR}/source/event_groups.c
    ${CMAKE_FREERTOS_DIR}/source/list.c
    ${CMAKE_FREERTOS_DIR}/source/queue.c
    ${CMAKE_FREERTOS_DIR}/source/tasks.c
    ${CMAKE_FREERTOS_DIR}/source/timers.c
    
    ${CMAKE_FREERTOS_DIR}/portable/MemMang/heap_4.c
    ${CMAKE_FREERTOS_DIR}/portable/GCC/ARM_CM3/port.c
)

add_library(freertos ${FREERTOS_SRC})

include_directories(${CMAKE_SOURCE_DIR})
target_include_directories(freertos PUBLIC
    ${CMAKE_FREERTOS_DIR}/config
    ${CMAKE_FREERTOS_DIR}/include
    ${CMAKE_FREERTOS_DIR}/portable/GCC/ARM_CM3
)

#target_compile_definitions(freertos PUBLIC
#    -DportUSE_STARTUP_HOOK=1   # example if needed
#)

# Add include dir
include_directories(${CMAKE_LIBOPENCM3_INCLUDE_DIR})

# Executable target
add_executable(${EXECUTABLE} 
    ${CMAKE_SOURCE_DIR}/src/main.c
    ${CMAKE_DRIVER_DIR}/gpio/led_driver.c
    ${CMAKE_DRIVER_DIR}/memory/mamory.c
    ${CMAKE_DRIVER_DIR}/task_manager/task_manager.c
    ${CMAKE_DRIVER_DIR}/uart/uart_drv.c        
)

# Add header path to target
target_include_directories(${EXECUTABLE}  PRIVATE 
    ${CMAKE_DRIVER_DIR}/global 
    ${CMAKE_DRIVER_DIR}/gpio
    ${CMAKE_DRIVER_DIR}/memory
    ${CMAKE_DRIVER_DIR}/task_manager
    ${CMAKE_DRIVER_DIR}/uart
    ${CMAKE_LIBOPENCM3_DIR}/include
)

# Ensure libopencm3 is built first
add_dependencies(${EXECUTABLE} libopencm3_project)

# Link against pre-built libopencm3.a
target_link_libraries(${EXECUTABLE}
    freertos
    ${CMAKE_LIBOPENCM3_DIR}/lib/libopencm3_stm32l1.a
)

# Compiler options
target_compile_options(${EXECUTABLE} PRIVATE
        -mtune=cortex-m3
        -mthumb

        -fdata-sections
        -ffunction-sections
        -Wall
        -O0
        -g3
)

# Linker options
target_link_options(${EXECUTABLE} PRIVATE
        -T ${CMAKE_SOURCE_DIR}/stm32l152re.ld
        -mtune=cortex-m3
        -mthumb
        -specs=nano.specs
        -specs=nosys.specs
        -lc
        -lgcc
        -lm
        -lnosys
        -Wl,-Map=${PROJECT_NAME}.map,--cref
        -Wl,--gc-sections
        -Xlinker -print-memory-usage -Xlinker
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