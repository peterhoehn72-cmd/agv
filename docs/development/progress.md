# Development progress

## Completed hardware baseline

- **Chassis construction:** the current chassis has been assembled. Final PDF drawings and printable STL models are available in the [mechanics documentation](../hardware/mechanics/README.md).
- **Electrical wiring:** the motor-driver wiring is complete, and the Pico-to-L298N pin assignments have been validated against the robot. The [electronics documentation](../hardware/electronics/README.md) records the wiring, power distribution, and pin mapping.
- **Motor-driver bring-up:** the Pico firmware has been built and tested on the robot, exercising the wiring, power supply, and all four motors. Tests at approximately 1.5–2 kHz PWM produced visibly similar motor responses with equal duty commands and straight travel on the tested level surface. See the [motor-driver example](../../firmware/pico/examples/motor-driver-test/README.md) for the test behavior and observations.

## Next bring-up work

LiDAR and IMU bring-up remain pending. Pico–Pi communication, feedback control, state estimation, and integration of the ROS 2 stack are planned work. Future entries will record implementation and validation results as development progresses.
