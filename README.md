# RMdevBoard_ChibiOS  

HKUST RoboMaster ENTERPRIZE team embedded development environment

## Dependency
- compiler: arm-none-eabi-gcc
- debugger: openocd for ST-Link / J-Link Ozone
- development OS: Ubuntu / MacOS / Windows

## Software Architecture
- os
- hw
- driver
- dev
- module
- task
- tools
- docs

Architecture explained:Ma
- os:   chibiOS / RT, real time operating system;
- hw:  hardware, board related documentation;
- dev: devices, drivers, and external libraries;
- driver: register map and basic functions for external hardwares;
- module: estimator, controller, system identification, and other math related algorithm;
- task: application layers, defining the tasks independent to the hardware.

## Initial calibration and turning
See 6_tool/README.md for detailed procedure

## Dependency
MacOS use homebrew to install the embedded toolchain
```
brew tap PX4/px4
brew install px4-dev
```

Ubuntu 
```
sudo apt-get install gcc-arm-none-eabi openocd -y
```

