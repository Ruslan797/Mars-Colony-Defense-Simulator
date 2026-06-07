#include "ConsoleRenderer.h"

#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>

void ConsoleRenderer::render(
    const std::vector<std::shared_ptr<Drone>>& drones,
    const std::vector<std::shared_ptr<SpaceObject>>& objects
) const
{
    clearScreen(); // clear previous frame

    const int width = 31;
    const int height = 21;

    const int minX = -15;
    const int maxY = 10;

    std::vector<std::string> grid(
        height,
        std::string(width, ' ')
    );

    // draw fog of war
    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            grid[y][x] = '#'; // unexplored area
        }
    }

    // draw visible objects
    for (const auto& object : objects)
    {
        Vector2D position = object->getPosition();

        if (!isVisibleToAnyDrone(position, drones))
        {
            continue;
        }

        int x = static_cast<int>(position.getX()) - minX;

        int y = maxY - static_cast<int>(position.getY());

        if (x >= 0 && x < width &&
            y >= 0 && y < height)
        {
            grid[y][x] =
                getObjectSymbol(object);
        }
    }

    // draw drones and reveal nearby fog
    for (const auto& drone : drones)
    {
        Vector2D position = drone->getPosition();

        int centerX =
            static_cast<int>(position.getX()) - minX;

        int centerY =
            maxY - static_cast<int>(position.getY());

        // reveal nearby area
        for (int dy = -4; dy <= 4; dy++)
        {
            for (int dx = -4; dx <= 4; dx++)
            {
                int x = centerX + dx;
                int y = centerY + dy;

                if (x >= 0 && x < width &&
                    y >= 0 && y < height)
                {
                    if (grid[y][x] == '#')
                    {
                        grid[y][x] = '.';
                    }
                }
            }
        }

        if (centerX >= 0 && centerX < width &&
            centerY >= 0 && centerY < height)
        {
            grid[centerY][centerX] = 'D';
        }
    }

    std::cout
        << "=== RESCUE DRONE SIMULATOR ==="
        << std::endl;

    for (const std::string& row : grid)
    {
        std::cout << row << std::endl;
    }

    std::cout << std::endl;

    std::cout
        << "Legend: "
        << "D=Drone "
        << "A=Alien "
        << "M=Meteor "
        << "R=Rescue "
        << "s=Scanned "
        << "#=Fog"
        << std::endl;
}

void ConsoleRenderer::clearScreen() const
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

bool ConsoleRenderer::isVisibleToAnyDrone(
    const Vector2D& position,
    const std::vector<std::shared_ptr<Drone>>& drones
) const
{
    for (const auto& drone : drones)
    {
        double distance =
            drone->getPosition().distanceTo(position);

        if (distance <= 6.0)
        {
            return true;
        }
    }

    return false;
}

char ConsoleRenderer::getObjectSymbol(
    const std::shared_ptr<SpaceObject>& object
) const
{
    if (object->getStatus() ==
        ObjectStatus::Scanned)
    {
        return 's';
    }

    switch (object->getType())
    {
    case ObjectType::AlienDrone:
        return 'A';

    case ObjectType::Meteor:
        return 'M';

    case ObjectType::RescueCapsule:
        return 'R';

    default:
        return '?';
    }
}