#include "SensorSystem.h"

SensorSystem::SensorSystem(const std::shared_ptr<Logger>& logger)
{
    this->logger = logger; // store shared logger

    lidarSystem = std::make_unique<LidarSystem>(
        logger
    ); // create LiDAR module
}

SensorSystem::~SensorSystem()
{
    stop(); // safely stop all sensor modules
}

void SensorSystem::start()
{
    lidarSystem->start(); // start LiDAR thread
}

void SensorSystem::stop()
{
    if (lidarSystem)
    {
        lidarSystem->stop(); // stop LiDAR thread safely
    }
}

double SensorSystem::getLidarDistance() const
{
    return lidarSystem->getLastScanDistance(); // read LiDAR data
}

bool SensorSystem::isObstacleDetected() const
{
    return lidarSystem->isObstacleDetected(); // read obstacle state
}