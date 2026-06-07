#pragma once

#include <vector>
#include <memory>

#include "Drone.h"
#include "SpaceObject.h"
#include "Logger.h"
#include "SensorSystem.h"
#include "ConsoleRenderer.h"

class World
{
private:
    std::vector<std::shared_ptr<Drone>> drones; // all drones in world

    std::vector<std::shared_ptr<SpaceObject>> objects; // all objects in world

    std::shared_ptr<Logger> logger; // thread-safe logger

    std::unique_ptr<SensorSystem> sensorSystem; // background sensor system

    ConsoleRenderer renderer; // console rendering system

    const char* droneStateToString(DroneState state) const;

    std::shared_ptr<SpaceObject> findClosestObject(
        const Vector2D& position
    ) const;

public:
    World();

    ~World();

    void startSystems();

    void stopSystems();

    void addDrone(const std::shared_ptr<Drone>& drone);

    void addObject(const std::shared_ptr<SpaceObject>& object);

    void update();

    void printState() const;

    bool isObstacleDetected() const; // check sensor obstacle state

    const std::vector<std::shared_ptr<Drone>>& getDrones() const;

    const std::vector<std::shared_ptr<SpaceObject>>& getObjects() const;
};