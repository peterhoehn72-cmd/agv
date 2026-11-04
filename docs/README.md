# Project documentation

This is a work-in-progress record of the mecanum-wheel AGV. The [root README](../README.md) describes the intended software and firmware architecture; the documents here cover the hardware and development work.

- [Bill of materials](hardware/bill-of-materials.md)
- [Electronics and wiring](hardware/electronics/README.md)
- [Mechanical drawings and models](hardware/mechanics/README.md)
- [Pico motor driver test](../firmware/pico/examples/motor-driver-test/README.md)
- [Development progress](development/progress.md) — completed hardware milestones and pending bring-up work.

The current hardware baseline includes completed chassis construction, validated Pico-to-L298N pin assignments, and successful motor-driver bring-up on the robot. Test behavior and observations are documented in the motor driver example linked above; LiDAR and IMU bring-up and higher-level robot functionality remain pending.

The published pin mapping, wiring illustrations, mechanical drawings, and STL models are maintained here. The mechanical files are final for the current construction and will be updated as parts are added or revised. Build and test status is documented alongside each example as work progresses.

See [licensing](../LICENSING.md) for the scope of each project license and [third-party notices](../THIRD_PARTY_NOTICES.md) for upstream components and source artwork credits. The adapted wiring illustration is licensed under [CC BY-SA 4.0](https://creativecommons.org/licenses/by-sa/4.0/).
