# Motor driver test

Standalone C example for a Raspberry Pi Pico (RP2040) controlling four motors through two L298N driver modules. It exercises the wiring, power supply, and motor drivers as part of the AGV's active development. The CMake target builds [motor_driver_bringup.c](motor_driver_bringup.c). The pin assignments have been validated on the robot, and motor-driver bring-up has succeeded. The project enables C and C++, so later C++ development can coexist with this example.

See [pin mapping](../../../../docs/hardware/electronics/pin-mapping.md) for the GPIO assignments and the [wiring illustration](../../../../docs/hardware/electronics/pico-l298n-wiring.png).

## Motor-response findings

A short test series on a level surface showed that reducing PWM frequency to approximately **1.5–2 kHz** produced visibly similar motor responses with equal duty commands. The AGV drove straight ahead, and motor response to small duty changes was visibly more pronounced. The lower frequency also introduced audible humming.

PWM frequency therefore matters when establishing a baseline for comparable motor responses. The current straight-line trial applies the same duty command to all four motors. These findings describe observed behavior under the tested conditions; individual wheel speeds, motor currents, and switching waveforms were not measured, so the electrical cause of the improvement has not been established.

In normal free-running PWM mode, frequency is derived from:

```text
f_PWM = f_sys / (divider * (TOP + 1))
```

- `f_PWM`: PWM frequency in Hz.
- `f_sys`: system clock frequency in Hz.
- `divider`: PWM clock divider.
- `TOP`: configured counter wrap value; each cycle contains `TOP + 1` counter ticks.

The current clock, wrap, and divider configuration belongs in the source. The observed frequency range is recorded here so the findings remain understandable as that configuration evolves. See the [Pico PWM documentation](https://www.raspberrypi.com/documentation/pico-sdk/hardware.html#hardware_pwm) for the configuration API.

## Current behavior

`TEST_MODE` selects a straight-line trial or an individual motor duty sweep. The default is `STRAIGHT_LINE_TRIAL`:

- All four motors receive a short maximum-level startup burst, then the same fixed duty command, `STRAIGHT_LINE_BASE_DUTY`.
- PWM outputs remain active during `TRIAL_HOLD_MS`. The loop then repeats, including the startup burst.
- The burst is retained from earlier testing; whether it is still necessary at the lower PWM frequency remains to be checked separately.

`INDIVIDUAL_DUTY_SWEEP` exercises one motor at a time with the same sequence of commands. Every rising step includes a maximum-level burst, while falling steps have no added burst. Each motor is stopped by clearing its duty and direction pins before the next motor is exercised. USB logs identify the motor, sweep direction, and command; the straight-line trial does not print messages.

Duty ranges and timing parameters are defined in the source. This example has no command interface, encoder feedback, or automatic stop timeout.

## Dependencies

- CMake 3.13 or newer, a build tool such as Make, Python 3, and Git.
- An RP2040-compatible Arm GNU embedded toolchain (`arm-none-eabi-gcc` and `arm-none-eabi-g++`, with the embedded C/C++ runtime libraries).
- An external [Raspberry Pi Pico SDK](https://github.com/raspberrypi/pico-sdk), including its TinyUSB dependency for USB standard output. CMake links the SDK targets `pico_stdlib` and `hardware_pwm`.

The original SDK checkout was at commit `9a4113fbbae65ee82d8cd6537963bc3d3b14bcca` (two commits after tag `2.1.1`). That revision is recorded for reproducibility; compatibility with other revisions has not been verified. The SDK and generated build outputs are not included in this repository. The SDK may fetch/build `picotool` during configuration to generate the UF2 output, requiring network access on the first build if it is not already available.

## Build

Run these commands from the AGV repository root. To prepare a separate SDK checkout alongside the repository, if one is not already available:

```bash
git clone https://github.com/raspberrypi/pico-sdk.git ../pico-sdk
git -C ../pico-sdk checkout 9a4113fbbae65ee82d8cd6537963bc3d3b14bcca
git -C ../pico-sdk submodule update --init --recursive
```

Configure and build using the SDK's absolute path. Replace `/absolute/path/to/pico-sdk` with an existing checkout or the checkout prepared above:

```bash
cmake -S firmware/pico/examples/motor-driver-test \
  -B build/pico/motor-driver-test \
  -DPICO_SDK_PATH=/absolute/path/to/pico-sdk \
  -DPICO_BOARD=pico
cmake --build build/pico/motor-driver-test --parallel
```

The expected flashable output is `build/pico/motor-driver-test/motor_controller.uf2`. The root `build/` directory is ignored by Git. The bring-up firmware has been built and exercised on the robot; the findings above describe the author's hardware observations.

## Flash

Hold the Pico's **BOOTSEL** button while connecting it over USB, then release it. Copy `motor_controller.uf2` to the mounted **RPI-RP2** drive. The Pico restarts and runs the motor test immediately; arrange the robot so the powered wheels can turn freely before running it.

The build and BOOTSEL workflow follow the [official Pico C/C++ SDK documentation](https://www.raspberrypi.com/documentation/microcontrollers/c_sdk.html).

## Licensing

Original project code is covered by the root [MIT license](../../../../LICENSE). This README is covered by [CC BY 4.0](../../../../LICENSES/CC-BY-4.0.txt). The copied SDK import helper retains its upstream BSD-3-Clause notice. The external SDK and its dependencies retain their own licenses; see [third-party notices](../../../../THIRD_PARTY_NOTICES.md).
