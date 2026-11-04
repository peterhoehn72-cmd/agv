cmake_minimum_required(VERSION 3.13)

# Important: set project AFTER importing the Pico SDK
# Otherwise toolchain config breaks!
include(pico_sdk_import.cmake)

project(motor_controller_project C CXX ASM)

# Initialize the Pico SDK
pico_sdk_init()

# Add your main C file
add_executable(motor_controller
    motor_driver_bringup.c
)

# Link necessary libraries
target_link_libraries(motor_controller
    pico_stdlib
    hardware_pwm
)

# Enable commands like printf() to send print statements in the code via USB to Computer
pico_enable_stdio_usb(motor_controller 1)
pico_enable_stdio_uart(motor_controller 0)

# Enable additional output formats (e.g., .uf2)
pico_add_extra_outputs(motor_controller)

