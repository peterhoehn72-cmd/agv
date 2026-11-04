# Licensing

This repository contains software, documentation, hardware designs, and third-party material. The root MIT license applies to original project code; it is not a blanket license for everything in the repository.

Copyright (c) 2026 Peter Höhn and contributors, for their respective original contributions. Existing third-party copyright notices remain applicable.

## Scope

The following defaults apply only to original material that project contributors have the right to license. Explicit third-party or file-specific notices take precedence over these defaults for the material they cover.

| Material | License | Scope |
| --- | --- | --- |
| Original project software, firmware, scripts, build configuration, and code examples | [MIT](LICENSE) | Project-owned code in `firmware/`, `ros2_ws/src/`, and `tools/`, including code examples in documentation; excludes submodules and other third-party code. |
| Original documentation prose, tables, and explanatory illustrations | [CC BY 4.0](LICENSES/CC-BY-4.0.txt) | Root Markdown documents, project README files under `firmware/`, and documentation under `docs/`, except the wiring illustration below, hardware design files, embedded code examples, third-party material, and unpublished working files under `docs/temp/`. |
| Original hardware design files | [CERN-OHL-P-2.0](LICENSES/CERN-OHL-P-2.0.txt) | Mechanical drawings in `docs/hardware/mechanics/drawings/`, models in `docs/hardware/mechanics/models/`, and `docs/hardware/electronics/power-distribution.png`; excludes third-party assets. Future hardware design files should identify this license explicitly. |
| Adapted Pico–L298N wiring illustration | [CC BY-SA 4.0](https://creativecommons.org/licenses/by-sa/4.0/) | `docs/hardware/electronics/pico-l298n-wiring.png`, including the project's added wiring, labels, and layout. Source artwork retains its respective licenses; see the credits below. |
| Third-party components and assets | Their respective licenses or permissions | Git submodules, their dependencies, borrowed images, embedded fonts, and any other identified third-party material. See [third-party notices](THIRD_PARTY_NOTICES.md). |

For attribution of original documentation, use “Peter Höhn and contributors, AGV project,” retain a link to its source in this repository and the license, and indicate changes as required by CC BY 4.0.

## Submodules and upstream code

Third-party components, Git submodules, and third-party assets are excluded from the project license defaults and remain subject to their respective licenses and copyright notices. This repository does not relicense those materials.

In particular, `ros2_ws/src/ldlidar_ros2/` and its nested `sdk/` each contain their own MIT license, with copyright notices identifying SHENZHEN LDROBOT CO., LTD. Those upstream license files and notices govern the corresponding upstream material and take precedence over the project defaults. Preserve them when copying, modifying, or redistributing that material. Project changes to upstream code must also comply with the applicable upstream terms.

The copied `firmware/pico/examples/motor-driver-test/pico_sdk_import.cmake` helper retains its upstream BSD-3-Clause notice and is excluded from the root MIT license. The external Pico SDK and its dependencies, including TinyUSB, retain their own licenses; see [third-party notices](THIRD_PARTY_NOTICES.md).

## Wiring illustration and attribution

The adapted [Pico–L298N wiring illustration](docs/hardware/electronics/pico-l298n-wiring.png) is published under **CC BY-SA 4.0**, including the original wiring, labels, and layout contributed by Peter Höhn and contributors (2026). This file-specific license satisfies the ShareAlike condition of the adapted L298N image and takes precedence over the default documentation and hardware design licenses for this PNG.

The Pico pinout graphic is by **raspberry.tips**, licensed under **CC BY 4.0**. The L298N artwork is adapted from **“Dosmotorsl298n.jpg” by Quel.soler**, licensed under **CC BY-SA 4.0**. Their original artwork remains subject to those respective terms. [Third-party notices](THIRD_PARTY_NOTICES.md#wiring-illustration) records the source links, license links, and modifications.

When redistributing or adapting the composite, retain appropriate credit and license references and identify modifications as required by [CC BY-SA 4.0](https://creativecommons.org/licenses/by-sa/4.0/legalcode.en). The wiring illustration's license does not change the licenses of unrelated code, documentation, or design files in this repository.

## License text sources

The unmodified CC BY 4.0 and CERN-OHL-P-2.0 texts in `LICENSES/` were obtained from the [SPDX License List data repository](https://github.com/spdx/license-list-data/tree/main/text). License references: [MIT](https://spdx.org/licenses/MIT.html), [CC BY 4.0](https://creativecommons.org/licenses/by/4.0/), and [CERN-OHL-P-2.0](https://spdx.org/licenses/CERN-OHL-P-2.0.html).
