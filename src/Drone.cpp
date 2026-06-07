#include "Drone.h"

Drone::Drone(const Vector2D& startPosition, double speed)
    : battery(100.0) // initialize battery with 100 energy
{
    this->position = startPosition; // set start position

    this->homePosition = startPosition; // initial position becomes home position

    this->velocity = Vector2D(0, 0); // drone is not moving yet

    this->speed = speed; // set movement speed

    this->scanRadius = 3.0; // set scan distance

    this->state = DroneState::Idle; // drone starts in idle state
}

void Drone::moveTo(const Vector2D& target)
{
    // stop movement if battery is empty
    if (battery.getCurrentEnergy() <= 0)
    {
        velocity = Vector2D(0, 0);

        state = DroneState::Idle;

        return;
    }

    state = DroneState::Moving; // drone is now moving

    Vector2D direction = target - position; // calculate direction to target

    double distance = direction.length(); // calculate distance to target

    if (distance <= speed) // if target is close enough
    {
        position = target; // snap drone exactly to target

        velocity = Vector2D(0, 0); // stop movement

        state = DroneState::Idle; // drone stops moving

        return;
    }

    direction = direction.normalized(); // make direction length 1

    velocity = direction * speed; // calculate movement for one step

    position = position + velocity; // update drone position

    battery.consume(0.5); // movement consumes battery energy
}

void Drone::returnToHome()
{
    state = DroneState::ReturningHome; // switch AI state

    moveTo(homePosition); // move drone toward home position
}

void Drone::scan()
{
    velocity = Vector2D(0, 0); // stop drone while scanning

    state = DroneState::Scanning; // drone is now scanning

    battery.consume(0.2); // scanning also consumes energy
}

void Drone::completeMission()
{
    velocity = Vector2D(0, 0); // stop drone movement

    state = DroneState::MissionComplete; // mission finished
}

bool Drone::canScan(const Vector2D& target) const
{
    double distance = position.distanceTo(target); // calculate distance to target

    return distance <= scanRadius; // true if target is inside scan radius
}

Vector2D Drone::getPosition() const
{
    return position; // return current position
}

Vector2D Drone::getVelocity() const
{
    return velocity; // return current velocity
}

Vector2D Drone::getHomePosition() const
{
    return homePosition; // return drone home position
}

double Drone::getScanRadius() const
{
    return scanRadius; // return scan radius
}

double Drone::getBatteryPercent() const
{
    return battery.getEnergyPercent(); // return battery percentage
}

bool Drone::isBatteryLow() const
{
    return battery.isLow(); // check low battery state
}

DroneState Drone::getState() const
{
    return state; // return current drone state
}

bool Drone::hasArrived(const Vector2D& target) const
{
    return position.distanceTo(target) == 0; // true if drone is exactly at target
}

void Drone::avoidObstacle()
{
    state = DroneState::AvoidingObstacle; // obstacle avoidance mode

    Vector2D avoidanceDirection(0, 1); // move upward to avoid obstacle

    velocity = avoidanceDirection * speed; // calculate avoidance movement

    position = position + velocity; // update drone position

    battery.consume(0.3); // avoidance consumes energy
}

void Drone::recharge()
{
    battery.recharge(); // restore battery energy

    velocity = Vector2D(0, 0); // stop drone at base

    state = DroneState::Idle; // drone is ready for next mission
}

void Drone::avoidDrone(const Vector2D& otherPosition)
{
    Vector2D direction = position - otherPosition; // direction away from other drone

    if (direction.length() == 0)
    {
        direction = Vector2D(1, 0); // fallback direction if drones are exactly overlapping
    }

    direction = direction.normalized(); // make direction length equal to 1

    velocity = direction * speed; // calculate avoidance movement

    position = position + velocity; // move away from other drone

    state = DroneState::AvoidingObstacle; // reuse avoidance state

    battery.consume(0.2); // avoidance consumes battery
}