#include "LidarSystem.h"

#include <chrono>
#include <sstream>
#include <thread>

LidarSystem::LidarSystem(const std::shared_ptr<Logger>& logger)
{
    this->logger = logger; // store shared logger

    running = false; // LiDAR starts disabled

    lastScanDistance = 0.0; // default sensor value

    obstacleDetected = false; // no obstacle at start
}

LidarSystem::~LidarSystem()
{
    stop(); // safely stop LiDAR thread before destruction
}

void LidarSystem::start()
{
    if (running)
    {
        return; // do not start twice
    }

    running = true; // enable LiDAR loop

    lidarThread = std::thread(
        &LidarSystem::lidarLoop,
        this
    ); // start background thread
}

void LidarSystem::stop()
{
    running = false; // request LiDAR thread stop

    if (lidarThread.joinable())
    {
        lidarThread.join(); // wait for thread to finish
    }
}

double LidarSystem::getLastScanDistance() const
{
    std::lock_guard<std::mutex> lock(dataMutex);

    return lastScanDistance;
}

bool LidarSystem::isObstacleDetected() const
{
    std::lock_guard<std::mutex> lock(dataMutex);

    return obstacleDetected;
}

void LidarSystem::lidarLoop()
{
    double simulatedDistance = 10.0;

    while (running)
    {
        {
            std::lock_guard<std::mutex> lock(dataMutex);

            lastScanDistance = simulatedDistance;

            obstacleDetected =
                simulatedDistance < 3.0;
        }

        std::ostringstream message;

        message
            << "[LiDAR Thread] Distance: "
            << getLastScanDistance();

        logger->log(message.str());

        simulatedDistance -= 0.5;

        if (simulatedDistance <= 0.0)
        {
            simulatedDistance = 10.0;
        }

        std::this_thread::sleep_for(
            std::chrono::milliseconds(700)
        );
    }

    logger->log("[LiDAR Thread] Stopped");
}