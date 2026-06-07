#pragma once

#include "Vector2D.h"      // use Vector2D for position and velocity
#include "BatterySystem.h" // use BatterySystem for drone energy

enum class DroneState
{
    Idle,              // drone is waiting and doing nothing
    Moving,            // drone is moving toward a target
    Scanning,          // drone is scanning an object or area
    ReturningHome,     // drone is returning to base
    MissionComplete,    // all mission targets completed
    AvoidingObstacle  // drone is avoiding an obstacle
};

class Drone
{
private:
    Vector2D position; // current drone position
    Vector2D velocity; // current movement vector

    Vector2D homePosition; // drone base position

    double speed;      // movement speed
    double scanRadius; // distance where drone can scan objects

    BatterySystem battery; // drone battery system

    DroneState state; // current drone AI state

public:
    Drone(const Vector2D& startPosition, double speed); // create drone

    void moveTo(const Vector2D& target); // move drone one step to target

    void returnToHome(); // move drone toward home position

    void scan(); // switch drone into scanning state

    void completeMission(); // switch drone into mission complete state

    bool canScan(const Vector2D& target) const; // check if target is inside scan radius

    Vector2D getPosition() const; // return current position

    Vector2D getVelocity() const; // return current velocity

    Vector2D getHomePosition() const; // return home position

    double getScanRadius() const; // return scan radius

    double getBatteryPercent() const; // return battery percentage

    bool isBatteryLow() const; // check if drone battery is low

    DroneState getState() const; // return current drone state

    bool hasArrived(const Vector2D& target) const; // check if drone reached target

    void avoidObstacle(); // switch drone into obstacle avoidance state

    void recharge(); // recharge drone battery

    void avoidDrone(const Vector2D& anotherPosition); //avoid another drone
};