# AGV Repository Structure

This repository contains the software and firmware for a small autonomous mobile robot based on mecanum wheels.

The project is expected to evolve over time. This document therefore describes the **initial architecture and intended separation of responsibilities**, rather than a fixed final design. Update it whenever major architectural decisions change.

## 1. System Overview

The system is split across two main compute targets:

- **Raspberry Pi 3 B**
  - Runs ROS 2 Humble.
  - Interfaces with the LD19 LiDAR.
  - Receives IMU and low-level state information from the microcontroller.
  - Runs state estimation and higher-level robot software.

- **Raspberry Pi Pico**
  - Runs standalone embedded firmware.
  - Interfaces with the IMU.
  - Executes low-level motor control.
  - Communicates with the Raspberry Pi 3 through a custom protocol.
  - Does not depend on ROS 2.

Development and initial testing of the ROS stack is performed on an **Ubuntu 22.04 laptop with ROS 2 Humble**. The same ROS source tree should later be buildable directly on the Raspberry Pi.

The intended high-level architecture is:

```text
                     Raspberry Pi 3 B
                ┌─────────────────────────┐
                │        ROS 2 Humble     │
                │                         │
LD19 LiDAR ────►│  LiDAR Driver           │
                │          │              │
                │          ▼              │
                │   State Estimation      │
                │      ▲                  │
                │      │ IMU              │
                │      │                  │
                │  Hardware Interface     │
                └──────────┬──────────────┘
                           │
                    UART (planned)
                           │
                ┌──────────▼──────────────┐
                │    Raspberry Pi Pico    │
                │                         │
                │  IMU Acquisition        │
                │  Motor Control          │
                │  Communication Protocol │
                └──────────┬──────────────┘
                           │
                           ▼
                    Motor Drivers
                           │
                           ▼
                    Mecanum Wheels
```

UART is currently the preferred communication interface between the Raspberry Pi and Pico. I²C remains a possible alternative if future requirements justify it.

---

## 2. Repository Structure

The intended starting structure is:

```text
agv/
│
├── README.md
│
├── firmware/
│   └── pico/
│       ├── imu/
│       ├── motor_control/
│       ├── communication/
│       └── ...
│
├── ros2_ws/
│   └── src/
│       ├── ldlidar_ros2/
│       ├── agv_hardware/
│       ├── agv_state_estimation/
│       ├── agv_interfaces/
│       ├── agv_bringup/
│       └── ...
│
├── tools/
│   ├── analysis/
│   ├── calibration/
│   └── ...
│
└── docs/
    └── ...
```

Not all directories or packages need to exist immediately. They should be added when their functionality is implemented.

---

## 3. ROS 2 Workspace

```text
ros2_ws/
└── src/
```

contains the ROS 2 software intended to run primarily on the Raspberry Pi 3 B.

The same workspace is also used on the development laptop. Source code should therefore remain portable between the development machine and the Raspberry Pi.

### `ldlidar_ros2`

ROS 2 driver for the LDROBOT LD19 LiDAR.

Initial upstream source:

`ldrobotSensorTeam/ldlidar_ros2`

This package provides the interface between the physical LiDAR and ROS 2.

### `agv_hardware`

Hardware abstraction between ROS 2 and the Pico.

Responsibilities are expected to include:

- UART communication
- packet serialization/deserialization
- communication error handling
- receiving IMU measurements
- receiving motor/encoder state
- sending low-level commands
- converting embedded data into appropriate ROS messages

The goal is to isolate the custom Pi ↔ Pico protocol here.

Higher-level ROS nodes should not need to know how the Pico communication works.

### `agv_state_estimation`

Robot state-estimation package.

Expected inputs include:

- LiDAR-derived information
- IMU measurements
- potentially wheel odometry

The exact estimator architecture is still under development.

Initial investigations include probabilistic fusion of LiDAR and IMU measurements and analysis of the measurement/innovation distributions.

### `agv_interfaces`

Custom ROS messages, services, or actions that are specific to this robot.

This package should only be introduced where standard ROS interfaces are insufficient.

### `agv_bringup`

System-level configuration and launch files.

Eventually this package should provide convenient launch configurations for starting the robot stack, for example:

```bash
ros2 launch agv_bringup agv.launch.py
```

It may contain:

- launch files
- ROS parameters
- sensor configuration
- estimator configuration
- hardware configuration

---

## 4. Pico Firmware

```text
firmware/pico/
```

contains software running on the Raspberry Pi Pico.

The Pico is deliberately treated as an **independent embedded subsystem rather than as part of the ROS workspace**.

The initial responsibilities are:

### IMU acquisition

- configure the IMU
- acquire accelerometer/gyroscope measurements
- perform any required low-level preprocessing
- timestamp measurements where appropriate
- transmit measurements to the Raspberry Pi

### Motor control

The Pico handles time-critical, low-level motor functionality.

Expected responsibilities include:

- motor commands
- wheel-level control
- encoder acquisition
- control-loop execution
- basic low-level safety behavior

Higher-level motion decisions remain on the Raspberry Pi.

### Communication

The Pico and Raspberry Pi communicate using a custom protocol.

UART is currently preferred for the physical interface.

A likely conceptual packet structure is:

```text
Pico → Pi

IMU / STATE packet
├── packet type
├── sequence number
├── timestamp
├── accelerometer
├── gyroscope
├── encoder/wheel state
├── status
└── checksum / CRC
```

and:

```text
Pi → Pico

COMMAND packet
├── packet type
├── sequence number
├── wheel/motor targets
├── control flags
└── checksum / CRC
```

The actual protocol has **not yet been defined**.

The protocol should eventually document:

- byte order
- packet framing
- data types
- units
- timestamps
- sequence numbers
- CRC/checksum
- timeout behavior
- handling of corrupted packets
- communication rates

---

## 5. Development and Deployment

### Laptop

Development environment:

```text
Ubuntu 22.04
ROS 2 Humble
```

ROS 2 is installed system-wide and acts as the ROS underlay:

```bash
source /opt/ros/humble/setup.bash
```

The project workspace forms the overlay:

```bash
source ~/.../agv/ros2_ws/install/setup.bash
```

ROS packages should normally use the standard ROS/Ubuntu dependency mechanisms (`apt`, `rosdep`, CMake, etc.).

Python environments such as Miniforge or `venv` can be used where appropriate, but ROS itself does not need to be installed inside these environments.

### Raspberry Pi 3 B

The ROS source tree should eventually be cloned/deployed onto the Raspberry Pi and built **on the target platform**.

Do not copy x86 build artifacts from the laptop to the ARM Raspberry Pi.

Conceptually:

```text
                 Git Repository
                       │
             ┌─────────┴─────────┐
             │                   │
             ▼                   ▼
       Development Laptop    Raspberry Pi 3
          x86 build             ARM build
```

Both systems use the same source tree but generate their own:

```text
build/
install/
log/
```

directories.

### Raspberry Pi Pico

Pico firmware is built independently from ROS using the appropriate embedded toolchain/Pico SDK.

The resulting firmware binary is flashed onto the Pico.

---

## 6. Dependency Strategy

The current dependency strategy is:

```text
ROS / ROS-related dependency
        │
        ├── ROS package available?
        │       └── apt / rosdep
        │
        ├── C++ library?
        │       └── apt, CMake, or vendored dependency
        │
        └── ROS Python dependency?
                └── system Python / compatible venv


Offline analysis / experimentation
        │
        └── Miniforge environment
            ├── NumPy
            ├── SciPy
            ├── Pandas
            ├── Matplotlib
            ├── Jupyter
            └── etc.
```

The objective is to avoid unnecessary system-wide project dependencies while also avoiding conflicts between Conda's userspace and the Ubuntu/ROS 2 environment.

---

## 7. Design Principles

### Separate by deployment target

The main architectural boundary is:

```text
Raspberry Pi Pico firmware
          ↕
communication protocol
          ↕
Raspberry Pi ROS stack
```

This is more important than creating separate ROS workspaces for individual functionality.

### Separate ROS functionality using packages

LiDAR, state estimation, hardware communication, interfaces, and bringup should normally be separate **ROS packages inside one workspace**, rather than separate workspaces.

### Keep embedded firmware independent of ROS

The Pico should expose measurements and accept commands through a documented communication protocol.

It should not matter to the Pico whether the host software uses ROS.

Likewise, ROS nodes above `agv_hardware` should not depend on the implementation details of the Pico communication.

### Keep source portable

The ROS source tree should be usable both on the development laptop and Raspberry Pi.

Architecture-specific build artifacts should not be committed to Git.

---

## 8. Current Project Status

Initial phase:

- [ ] Create repository structure
- [ ] Set up ROS 2 workspace
- [ ] Integrate LD19 ROS 2 driver
- [ ] Test LD19 locally on development laptop
- [ ] Investigate LiDAR measurements and filtering
- [ ] Integrate IMU
- [ ] Design Pico ↔ Pi communication protocol
- [ ] Implement Pico IMU acquisition
- [ ] Implement low-level motor control
- [ ] Implement ROS hardware interface
- [ ] Implement state estimation
- [ ] Deploy ROS stack to Raspberry Pi 3 B
- [ ] Integrate complete AGV

---

## 9. Open Architectural Decisions

The following decisions are intentionally left open:

- exact IMU model and interface
- final Pi ↔ Pico physical interface (UART currently preferred)
- communication packet format
- timestamp synchronization strategy
- wheel encoder interface
- motor-control architecture
- state-estimation architecture
- LiDAR preprocessing/filtering
- measurement outlier handling
- Gaussian vs. heavy-tailed measurement models
- final ROS topic/interface structure
- deployment/startup mechanism on Raspberry Pi
- dependency management for additional Python/C++ libraries

These should be resolved based on experiments and actual system requirements rather than fixed prematurely.

---

## 10. Maintenance Note

This document is intended as a **living architecture reference**.

When returning to the project after a longer break, start here to recover the intended system structure.

Update this README when:

- responsibilities move between the Pi and Pico,
- ROS packages are added or removed,
- the communication protocol changes,
- deployment strategy changes,
- major hardware is replaced, or
- an architectural decision listed above is finalized.

The repository structure should reflect the actual system rather than forcing the system to follow an outdated initial design.