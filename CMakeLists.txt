cmake_minimum_required(VERSION 3.10)

project(RescueDrone)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)

find_package(SFML 3 COMPONENTS Graphics Window System REQUIRED)

add_executable(RescueDrone
    src/main.cpp
    src/Vector2D.cpp
    src/Drone.cpp
    src/World.cpp
    src/Game.cpp
    src/SpaceObject.cpp
    src/BatterySystem.cpp
    src/CameraSensor.cpp
    src/ConsoleRenderer.cpp
    src/InputSystem.cpp
    src/Logger.cpp
    src/SensorSystem.cpp
    src/LidarSystem.cpp
    src/GraphicsRenderer.cpp
)

target_link_libraries(RescueDrone
    SFML::Graphics
    SFML::Window
    SFML::System
)