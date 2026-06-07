#include "World.h"

#include <iostream> // for console output
#include <limits>   // for numeric limits

World::World()
{
    logger = std::make_shared<Logger>(); // create shared logger

    sensorSystem = std::make_unique<SensorSystem>(logger); // create sensor system with shared logger

    logger->log("World created");
}

World::~World()
{
    stopSystems(); // safely stop world systems

    logger->log("World destroyed");
}

void World::startSystems()
{
    logger->log("Starting world systems");

    sensorSystem->start(); // start sensor thread
}

void World::stopSystems()
{
    if (sensorSystem)
    {
        sensorSystem->stop(); // stop sensor thread safely
    }
}

void World::addDrone(const std::shared_ptr<Drone>& drone)
{
    drones.push_back(drone); // store shared drone pointer

    logger->log("Drone added to world");
}

void World::addObject(const std::shared_ptr<SpaceObject>& object)
{
    objects.push_back(object); // store shared object pointer

    logger->log("Object added to world");
}

void World::update()
{
    // stop update if there are no drones or objects
    if (drones.empty() || objects.empty())
    {
        logger->log("World update skipped");

        return;
    }

    // update every drone in the world
    for (size_t i = 0; i < drones.size(); i++)
    {
        std::shared_ptr<Drone> drone = drones[i]; // get current drone

        for (size_t j = 0; j < drones.size(); j++)
        {
            if (i == j)
            {
                continue;
            }

            double distance =
                drone->getPosition().distanceTo(
                    drones[j]->getPosition()
                );

            if (distance < 1.5)
            {
                logger->log("Drone too close -> separating");

                drone->avoidDrone(drones[j]->getPosition());

                break;
            }
        }

        // battery low -> return home
        if (drone->isBatteryLow())
        {
            logger->log("Drone battery low -> returning home");

            drone->returnToHome();

            if (drone->hasArrived(drone->getHomePosition()))
            {
                logger->log("Drone reached base -> recharging");

                drone->recharge();
            }

            continue;
        }

        std::shared_ptr<SpaceObject> targetObject =
            findClosestObject(drone->getPosition()); // search nearest object

        if (targetObject == nullptr) // no valid target found
        {
            logger->log("Mission completed");

            drone->completeMission();

            continue;
        }

        Vector2D objectPosition =
            targetObject->getPosition();

        if (drone->canScan(objectPosition))
        {
            logger->log("Drone scanned object");

            drone->scan();

            targetObject->setStatus(ObjectStatus::Scanned);

            continue;
        }

        drone->moveTo(objectPosition);
    }
}


void World::printState() const
{
    renderer.render(drones, objects); // render world map

    std::cout << std::endl;

    std::cout
        << "LiDAR Distance: "
        << sensorSystem->getLidarDistance()
        << std::endl;

    std::cout
        << "Obstacle Detected: "
        << (sensorSystem->isObstacleDetected()
            ? "YES"
            : "NO")
        << std::endl;

    std::cout << std::endl;

    std::cout << "=== WORLD STATE ===" << std::endl;

    std::cout
        << "Drones: "
        << drones.size()
        << std::endl;

    std::cout
        << "Objects: "
        << objects.size()
        << std::endl;

    // print all drones
    for (size_t i = 0; i < drones.size(); i++)
    {
        Vector2D position = drones[i]->getPosition();

        Vector2D velocity = drones[i]->getVelocity();

        DroneState state = drones[i]->getState();

        std::cout
            << "Drone "
            << i
            << " position: ("
            << position.getX()
            << ", "
            << position.getY()
            << ")"
            << std::endl;

        std::cout
            << "Drone "
            << i
            << " velocity: ("
            << velocity.getX()
            << ", "
            << velocity.getY()
            << ")"
            << std::endl;

        std::cout
            << "Drone "
            << i
            << " battery: "
            << drones[i]->getBatteryPercent()
            << "%"
            << std::endl;

        std::cout
            << "Drone "
            << i
            << " state: "
            << droneStateToString(state)
            << std::endl;
    }
}

const char* World::droneStateToString(DroneState state) const
{
    switch (state)
    {
    case DroneState::Idle:
        return "Idle";

    case DroneState::Moving:
        return "Moving";

    case DroneState::Scanning:
        return "Scanning";

    case DroneState::ReturningHome:
        return "ReturningHome";

    case DroneState::MissionComplete:
        return "MissionComplete";

    case DroneState::AvoidingObstacle:
        return "AvoidingObstacle";

    default:
        return "Unknown";
    }
}

std::shared_ptr<SpaceObject> World::findClosestObject(
    const Vector2D& position
) const
{
    std::shared_ptr<SpaceObject> closestObject = nullptr;

    double closestDistance = std::numeric_limits<double>::max();

    for (size_t i = 0; i < objects.size(); i++)
    {
        // ignore already scanned objects
        if (objects[i]->getStatus() == ObjectStatus::Scanned)
        {
            continue;
        }

        Vector2D objectPosition = objects[i]->getPosition();

        double distance =
            position.distanceTo(objectPosition);

        if (distance < closestDistance)
        {
            closestDistance = distance;

            closestObject = objects[i];
        }
    }

    return closestObject;
}

bool World::isObstacleDetected() const
{
    return sensorSystem->isObstacleDetected();
}

const std::vector<std::shared_ptr<Drone>>& World::getDrones() const
{
    return drones; // return reference to drone list
}

const std::vector<std::shared_ptr<SpaceObject>>& World::getObjects() const
{
    return objects; // return reference to object list
}
