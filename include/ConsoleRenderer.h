#pragma once

#include <memory>
#include <vector>

#include "Drone.h"
#include "SpaceObject.h"

class ConsoleRenderer
{
public:
    void render(
        const std::vector<std::shared_ptr<Drone>>& drones,
        const std::vector<std::shared_ptr<SpaceObject>>& objects
    ) const; // draw world map in console

private:
    void clearScreen() const; // clear terminal screen

    bool isVisibleToAnyDrone(
        const Vector2D& position,
        const std::vector<std::shared_ptr<Drone>>& drones
    ) const; // check if object is visible to drones

    char getObjectSymbol(
        const std::shared_ptr<SpaceObject>& object
    ) const; // convert object to map symbol
};