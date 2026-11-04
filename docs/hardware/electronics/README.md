# Electronics

The current design connects a Raspberry Pi Pico to two L298N motor drivers. A Raspberry Pi 3 B is the intended ROS 2 host; host integration and LiDAR/IMU bring-up remain pending. See the [bill of materials](../bill-of-materials.md) for the recorded components.

- [Pin mapping](pin-mapping.md) — validated GPIO and physical header pin assignments for all four motors.
- [Pico–L298N wiring illustration](pico-l298n-wiring.png) — CC BY-SA 4.0; see [artwork credits](../../../THIRD_PARTY_NOTICES.md#wiring-illustration).
- [Power distribution (PNG)](power-distribution.png)
- [Image sources and credits](image-sources.txt)
- [Motor driver test](../../../firmware/pico/examples/motor-driver-test/README.md) — migrated C experiment, dependencies, and build/flash instructions.

The Pico-to-L298N pin assignments have been validated against the robot's physical wiring, and motor-driver bring-up has succeeded. The [motor driver example](../../../firmware/pico/examples/motor-driver-test/README.md) records the current test behavior and hardware observations. Feedback control and integration with the ROS 2 host remain planned work.

The wiring illustration combines a Pico graphic by raspberry.tips (CC BY 4.0) with L298N artwork adapted from “Dosmotorsl298n.jpg” by Quel.soler (CC BY-SA 4.0). The composite is licensed under CC BY-SA 4.0. The [third-party notices](../../../THIRD_PARTY_NOTICES.md#wiring-illustration) record the sources and modifications. The power-distribution diagram is provided as a PNG and remains licensed under CERN-OHL-P-2.0. See [licensing](../../../LICENSING.md) for the distinction between documentation, hardware designs, and third-party assets.
