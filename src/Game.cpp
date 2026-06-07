#include "Game.h"

#include <chrono>
#include <memory>
#include <thread>

#include "Drone.h"
#include "SpaceObject.h"
#include "Vector2D.h"

void Game::setup()
{
    auto scoutDrone = std::make_shared<Drone>(
        Vector2D(0, 0),
        1.0
    );

    auto defenderDrone = std::make_shared<Drone>(
        Vector2D(-10, -5),
        1.5
    );

    auto supportDrone = std::make_shared<Drone>(
        Vector2D(8, -8),
        0.8
    );

    auto alienDrone = std::make_shared<SpaceObject>(
        Vector2D(10, 5),
        ObjectType::AlienDrone
    );

    auto meteor = std::make_shared<SpaceObject>(
        Vector2D(-6, 3),
        ObjectType::Meteor
    );

    auto rescueCapsule = std::make_shared<SpaceObject>(
        Vector2D(15, -4),
        ObjectType::RescueCapsule
    );

    auto colonyBase = std::make_shared<SpaceObject>(
        Vector2D(0, 0),
        ObjectType::Base
    );

    world.addObject(colonyBase);

    world.addDrone(scoutDrone);
    world.addDrone(defenderDrone);
    world.addDrone(supportDrone);

    world.addObject(alienDrone);
    world.addObject(meteor);
    world.addObject(rescueCapsule);
    world.addObject(colonyBase);
}

void Game::run()
{
    world.startSystems(); // start background systems

    setup(); // create drones and objects

    while (renderer.isOpen())
    {
        renderer.processEvents(); // handle window events

        world.update(); // update simulation

        renderer.render(world); // render real world

        std::this_thread::sleep_for(
            std::chrono::milliseconds(16)
        ); // roughly 60 FPS
    }

    world.stopSystems(); // stop background systems
}