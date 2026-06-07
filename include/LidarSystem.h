#pragma once

#include <atomic>
#include <memory>
#include <mutex>
#include <thread>

#include "Logger.h"

class LidarSystem
{
private:
    std::thread lidarThread; // background LiDAR thread

    std::atomic<bool> running; // thread running state

    mutable std::mutex dataMutex; // protects shared sensor data

    double lastScanDistance; // latest LiDAR scan distance

    bool obstacleDetected; // current obstacle detection state

    std::shared_ptr<Logger> logger; // shared thread-safe logger

public:
    LidarSystem(const std::shared_ptr<Logger>& logger); // create LiDAR system

    ~LidarSystem(); // destroy LiDAR system safely

    void start(); // start LiDAR thread

    void stop(); // stop LiDAR thread

    double getLastScanDistance() const; // safely read scan result

    bool isObstacleDetected() const; // check obstacle state

private:
    void lidarLoop(); // LiDAR update loop
};