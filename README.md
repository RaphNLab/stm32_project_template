# Introduction 
This template expose simple code for STM32L1 microcontroller.

* Used Library:
    * Libopencm3
    * FreeRTOS
* Build system:
    * CMake

# Getting Started

## Install necessary tools

    ### Install toolchain
        ```
            sudo apt-get update && apt-get install -y autoconf build-essential cmake  dialog gcc git git-lfs \
            make mtools nano net-tools ninja-build picocom rpcbind rsync ssh sshpass sudo texinfo tftp-hpa \
            tig tmux unzip vim gdb-multiarch usbutils libusb-1.0-0-dev stlink-tools udev wget gcc-arm-none-eabi \
            libnewlib-arm-none-eabi  build-essential 
            binutils-arm-none-eabi openocd python3
        ```

    ### Install ST-Link utilities
        ```
            git clone https://github.com/stlink-org/stlink.git
            cd stlink 
            make release
            cd build/Release
            make install 
            ldconfig
            cd ../.. 
            wget https://raw.githubusercontent.com/stlink-org/stlink/develop/config/udev/rules.d/49-stlinkv2.rules
            cp 49-stlinkv2.rules /etc/udev/rules.d/
        ```
## Update launch file
    * Open the launch.json file and update the executable name, openocd config and .svd file if necessary
    * Create new task if necessary
    * Update CMakeList.txt  target device if necessary
    * Init submodules libopencm3 and freeRTOS
        ```
        git submodule init
        git submodule update
        ```

# Build and Test
    1. Open a new terminal
    2. To create build directory with respective toolchain
        * Run ``` cmake -DCMAKE_TOOLCHAIN_FILE=cmake/arm-gcc-toolchain.cmake -B build -B build ```
    3. Configure FreeRTOS (FreeRTOSConfig.h) if nedded. 
    4.	On a terminal
        * Run cmake --build . --clean-first to clean an build the project
        * Run cmake --build . --target flash to flash the CPU
    5. On VS-Code 
        * Run "clean&build" task to compile
        * Run "flash" task to flash the CPU 
        * Press F5 to start debugging session
    6.	rum cmake... to flash the microcontroller

# Contribute
If you desire to contribute to this project, clone the code and feel free to modify 
and push your changes for improvement.
