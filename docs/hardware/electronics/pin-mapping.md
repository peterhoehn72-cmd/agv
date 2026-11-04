# Pico–L298N pin mapping

This table documents the four motor definitions in the [motor driver test](../../../firmware/pico/examples/motor-driver-test/motor_driver_bringup.c). The Pico is a Raspberry Pi Pico with an RP2040. GPIO numbers in the source are **GP numbers, not physical header pin numbers**.

The [wiring illustration](pico-l298n-wiring.png) shows the same four GPIO groups. Driver 1 is the module on the left of the image; driver 2 is on the right. Channels A and B refer to the corresponding enable pins and motor outputs shown in the image.

## Motor signals

| Motor | Motor name in source | Driver / channel in illustration | DIR1: GPIO / physical pin | DIR2: GPIO / physical pin | PWM: GPIO / physical pin |
| --- | --- | --- | --- | --- | --- |
| Front-left | `"front-left"` | Driver 2 / B | GP11 / pin 15 | GP12 / pin 16 | GP10 / pin 14 |
| Front-right | `"front-right"` | Driver 2 / A | GP14 / pin 19 | GP15 / pin 20 | GP13 / pin 17 |
| Rear-right | `"rear-right"` | Driver 1 / A | GP6 / pin 9 | GP7 / pin 10 | GP8 / pin 11 |
| Rear-left | `"rear-left"` | Driver 1 / B | GP3 / pin 5 | GP4 / pin 6 | GP2 / pin 4 |

DIR1 and DIR2 refer to the source fields `dir_pin_1` and `dir_pin_2`; trace these signals to the module's logic inputs as drawn rather than assuming DIR1 always means IN1. PWM connects to the corresponding A Enable or B Enable input. Physical Pico pin numbers follow the [official Pico pinout](https://pip-assets.raspberrypi.com/categories/610-raspberry-pi-pico/documents/RP-008309-DS-1-Pico-R3-A4-Pinout.pdf).


## Signal legend

- Green: DIR1.
- Magenta: DIR2.
- Dark blue: PWM to the channel's enable input.
- Background colors group the three signals for each motor.

The active test sets DIR1 high and DIR2 low for every motor. The physical direction of rotation also depends on the motor output wiring and mounting.

## Power and ground reference

The wiring illustration covers logic signals and omits supply wiring. Pico GND and both driver power grounds share the system reference at battery negative. Pico physical pin 38 is one of its GND pins.

See [power distribution](power-distribution.png) for the separate supply diagram. The planned Pico supply connection is physical pin 39 (**VSYS**) from the 5 V converter; VSYS is a power input, not a motor-control GPIO. The motor-test code does not configure power distribution.

These pin assignments have been validated against the physical wiring during successful motor-driver bring-up on the robot. See the [motor driver example](../../../firmware/pico/examples/motor-driver-test/README.md) for the test behavior and hardware observations.
