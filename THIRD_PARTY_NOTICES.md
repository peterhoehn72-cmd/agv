# Third-party notices

This file records known third-party components and assets. Their own licenses and copyright notices apply to the corresponding material and take precedence over the project defaults in [LICENSING.md](LICENSING.md). An attribution entry alone does not grant reuse rights.

## LDROBOT ROS 2 driver and SDK

| Component | Location | Upstream | License |
| --- | --- | --- | --- |
| LDROBOT ROS 2 driver | `ros2_ws/src/ldlidar_ros2/` | [ldrobotSensorTeam/ldlidar_ros2](https://github.com/ldrobotSensorTeam/ldlidar_ros2) | [Upstream MIT license](ros2_ws/src/ldlidar_ros2/LICENSE) |
| LDROBOT SDK | `ros2_ws/src/ldlidar_ros2/sdk/` | Nested dependency of the driver | [Upstream MIT license](ros2_ws/src/ldlidar_ros2/sdk/LICENSE) |

Both checked-out license files contain the notice `Copyright (c) 2020 SHENZHEN LDROBOT CO., LTD. All rights`. Preserve the full license files and notices with redistributed copies or substantial portions of the upstream software. Repository revisions are recorded by Git submodule commits; this notice does not replace upstream files or a dependency audit.

## Raspberry Pi Pico SDK and import helper

The [motor driver test](firmware/pico/examples/motor-driver-test/README.md) uses an external [Raspberry Pi Pico SDK](https://github.com/raspberrypi/pico-sdk) checkout. The original checkout revision is `9a4113fbbae65ee82d8cd6537963bc3d3b14bcca`. The SDK is not vendored in this repository.

The copied [pico_sdk_import.cmake](firmware/pico/examples/motor-driver-test/pico_sdk_import.cmake) is an unmodified upstream helper, licensed under BSD-3-Clause. Its complete copyright notice, conditions, and disclaimer remain in the file, identifying Raspberry Pi (Trading) Ltd. (2020). These terms take precedence over the root MIT license for this helper. See the [SDK license at the recorded revision](https://github.com/raspberrypi/pico-sdk/blob/9a4113fbbae65ee82d8cd6537963bc3d3b14bcca/LICENSE.TXT).

USB standard output uses the SDK's TinyUSB dependency. The original local TinyUSB checkout was at `86ad6e56c1700e85f1c5678607a762cfe3aa2f47`; its [MIT license](https://github.com/hathach/tinyusb/blob/86ad6e56c1700e85f1c5678607a762cfe3aa2f47/LICENSE) identifies `Copyright (c) 2018, hathach (tinyusb.org)`. The SDK and its bundled third-party components retain their own license notices. Preserve applicable notices when redistributing their source or firmware binaries incorporating them. The copied helper's notice is not a replacement for those dependency notices.

## Wiring illustration

Affected file: [pico-l298n-wiring.png](docs/hardware/electronics/pico-l298n-wiring.png).

The updated [image source notes](docs/hardware/electronics/image-sources.txt) record the artwork used in the composite:

| Material | Creator | Source | License | Modifications in the composite |
| --- | --- | --- | --- | --- |
| Raspberry Pi Pico pinout graphic | raspberry.tips | [Raspberry Pi Pico pinout graphic](https://raspberry.tips/en/raspberry-pi-pico-pinout) | [CC BY 4.0](https://creativecommons.org/licenses/by/4.0/) | Resized and incorporated into the wiring layout, with connection lines and annotations added. |
| L298N motor driver artwork from “Dosmotorsl298n.jpg” | Quel.soler (2018) | [Original file and attribution on Wikimedia Commons](https://commons.wikimedia.org/wiki/File:Dosmotorsl298n.jpg) | [CC BY-SA 4.0](https://creativecommons.org/licenses/by-sa/4.0/) | Module cropped from the original image, resized, and used twice, with new wiring and annotations added. |

The composite, including added wiring, labels, and layout by Peter Höhn and contributors (2026), is licensed under **CC BY-SA 4.0** in accordance with the adapted L298N artwork's ShareAlike requirement. The Pico graphic retains its underlying CC BY 4.0 license. See the [full CC BY-SA 4.0 license](https://creativecommons.org/licenses/by-sa/4.0/legalcode.en) and [project licensing scope](LICENSING.md#wiring-illustration-and-attribution).

Credit the source creators and the AGV project, preserve the source and license links, and indicate further changes when redistributing or adapting this illustration.

## Recursive typeface

Affected diagram: [power-distribution.png](docs/hardware/electronics/power-distribution.png).

The power-distribution diagram uses the Recursive typeface:

> Copyright 2019 The Recursive Project Authors (github.com/arrowtype/recursive)

The typeface is licensed under the SIL Open Font License, Version 1.1. The current PNG is a raster image and does not embed font software. This credit records the typeface used in the diagram; the original diagram content remains under the project's hardware design license.

Upstream project: [Recursive](https://github.com/arrowtype/recursive). License reference: [SIL Open Font License 1.1](https://openfontlicense.org/open-font-license-official-text/).
