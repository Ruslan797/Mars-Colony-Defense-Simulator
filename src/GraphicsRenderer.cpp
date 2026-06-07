#include "GraphicsRenderer.h"

GraphicsRenderer::GraphicsRenderer()
    : window(
        sf::VideoMode({900, 700}),
        "RescueDrone - Mars Colony Defense Simulator"
    ),
    droneShape(12.f),
    objectShape(10.f),
    baseShape(sf::Vector2f(60.f, 60.f))
{
    droneShape.setFillColor(sf::Color::Green);

    objectShape.setFillColor(sf::Color::White);

    baseShape.setFillColor(sf::Color::Magenta);
}

bool GraphicsRenderer::isOpen() const
{
    return window.isOpen(); // return window state
}

void GraphicsRenderer::processEvents()
{
    while (const std::optional event = window.pollEvent())
    {
        if (event->is<sf::Event::Closed>())
        {
            window.close();
        }
    }
}

void GraphicsRenderer::render(const World& world)
{
    window.clear(sf::Color(10, 10, 20)); // dark space background

    // draw objects
    for (const auto& object : world.getObjects())
    {
        if (object->getType() == ObjectType::Base)
        {
            sf::Vector2f basePosition =
                worldToScreen(object->getPosition());

            baseShape.setPosition({
                basePosition.x - 30.f,
                basePosition.y - 30.f
            });

            window.draw(baseShape);
        }
        else
        {
            objectShape.setPosition(
                worldToScreen(object->getPosition())
            );

            if (object->getStatus() == ObjectStatus::Scanned)
            {
                objectShape.setFillColor(sf::Color(120, 120, 120));
            }
            else
            {
                objectShape.setFillColor(
                    getObjectColor(object->getType())
                );
            }

            window.draw(objectShape);
        }
    }

    const auto& drones = world.getDrones();

    // draw drones
    for (size_t i = 0; i < drones.size(); i++)
    {
        droneShape.setPosition(
            worldToScreen(drones[i]->getPosition())
        );

        if (i == 0)
        {
            droneShape.setFillColor(sf::Color::Green);
        }
        else if (i == 1)
        {
            droneShape.setFillColor(sf::Color::Blue);
        }
        else
        {
            droneShape.setFillColor(sf::Color::Yellow);
        }

        window.draw(droneShape);
    }

    window.display();
}

sf::Vector2f GraphicsRenderer::worldToScreen(const Vector2D& position) const
{
    const float scale = 25.0f;

    const float centerX = 450.0f;
    const float centerY = 350.0f;

    float screenX =
        centerX + static_cast<float>(position.getX()) * scale;

    float screenY =
        centerY - static_cast<float>(position.getY()) * scale;

    return {screenX, screenY};
}

sf::Color GraphicsRenderer::getObjectColor(ObjectType type) const
{
    switch (type)
    {
    case ObjectType::AlienDrone:
        return sf::Color::Red;

    case ObjectType::Meteor:
        return sf::Color(180, 120, 60);

    case ObjectType::RescueCapsule:
        return sf::Color::Cyan;

    case ObjectType::Base:
        return sf::Color::Magenta;

    default:
        return sf::Color::White;
    }
}