# Mars Colony Defense Simulator

Autonomous drone simulation written in modern C++.

## Project Overview

Mars Colony Defense Simulator is a robotics-inspired simulation that models autonomous drones operating around a remote Mars colony.

The project focuses on software architecture used in real robotic systems:

* Autonomous drone behavior
* Battery management
* LiDAR-based obstacle detection
* Mission planning
* Object scanning
* World simulation
* Logging system
* Real-time rendering using SFML

The main goal of the project is educational: learning modern C++, object-oriented design, robotics concepts, and simulation development.

---

## Features

### Drone System

* Multiple autonomous drones
* Individual drone states
* Battery monitoring
* Return-to-base behavior
* Recharge system (in development)

### Sensor System

* LiDAR simulation
* Obstacle detection
* Object scanning

### World Simulation

* Multiple objects in the environment
* Meteor detection
* Rescue capsule detection
* Alien drone tracking
* Colony base

### Graphics

* Real-time visualization using SFML
* Color-coded drones
* Interactive simulation window

### Software Engineering Concepts

* Smart pointers (`std::shared_ptr`)
* Object-oriented programming
* Modular architecture
* Separation of interface and implementation
* CMake build system
* Git and GitHub workflow

---

## Project Structure

```text
include/
    Drone.h
    World.h
    BatterySystem.h
    LidarSystem.h
    GraphicsRenderer.h
    Logger.h

src/
    Drone.cpp
    World.cpp
    BatterySystem.cpp
    LidarSystem.cpp
    GraphicsRenderer.cpp
    Logger.cpp

CMakeLists.txt
```

## Technologies

* C++17
* SFML
* CMake
* Git
* GitHub

---

## Current Development Status

Project is actively developed.

Implemented:

* Core drone architecture
* World simulation
* Battery system
* LiDAR system
* Graphics rendering
* Logging system
* Base station visualization

Planned:

* Advanced obstacle avoidance
* Dynamic battery charging
* Mission scheduling
* Smarter autonomous navigation
* Multithreaded sensor processing

---

## Author

Ruslan

Learning modern C++ through practical robotics and simulation projects.

