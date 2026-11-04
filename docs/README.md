# Project documentation

This is a work-in-progress record of the mecanum-wheel AGV. The [root README](../README.md) describes the intended software and firmware architecture; the documents here cover the hardware and development work.

- [Bill of materials](hardware/bill-of-materials.md)
- [Electronics and wiring](hardware/electronics/README.md)
- [Mechanical drawings and models](hardware/mechanics/README.md)
- [Pico motor driver test](../firmware/pico/examples/motor-driver-test/README.md)
- [Development progress](development/progress.md) — reserved for future entries; currently empty.

The current verified hardware baseline covers Pico-to-L298N pin assignments and successful motor-driver bring-up on the robot. Test behavior and observations are documented in the motor driver example linked above; higher-level robot functionality remains under development.

The hardware documentation originated in the working material under `docs/temp`. The published pin mapping and wiring illustration are maintained here; mechanical drawings and models retain their original contents. These are design references under development; build and test status is documented alongside each example as work progresses.

See [licensing](../LICENSING.md) for the scope of each project license and [third-party notices](../THIRD_PARTY_NOTICES.md) for upstream components and source artwork credits. The adapted wiring illustration is licensed under [CC BY-SA 4.0](https://creativecommons.org/licenses/by-sa/4.0/).
