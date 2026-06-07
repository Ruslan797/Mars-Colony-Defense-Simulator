#pragma once

#include <memory>

#include "LidarSystem.h"
#include "Logger.h"

class SensorSystem
{
private:
    std::unique_ptr<LidarSystem> lidarSystem; // LiDAR sensor module

    std::shared_ptr<Logger> logger; // shared logger

public:
    SensorSystem(const std::shared_ptr<Logger>& logger); // create sensor system

    ~SensorSystem(); // destroy sensor system safely

    void start(); // start all sensor modules

    void stop(); // stop all sensor modules

    double getLidarDistance() const; // read latest LiDAR distance

    bool isObstacleDetected() const; // check LiDAR obstacle state
};