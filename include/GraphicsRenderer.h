#pragma once

#include <SFML/Graphics.hpp>

#include "World.h"
#include "SpaceObject.h"

class GraphicsRenderer
{
public:
    GraphicsRenderer();

    void render(const World& world); // render real simulation world

    bool isOpen() const; // check if window is open

    void processEvents(); // process window events

private:
    sf::RenderWindow window; // SFML render window

    sf::CircleShape droneShape; // reusable drone visual shape

    sf::CircleShape objectShape; // reusable object visual shape

    sf::Vector2f worldToScreen(const Vector2D& position) const; // convert world coordinates to screen

    sf::Color getObjectColor(ObjectType type) const; // choose color by object type

    sf::RectangleShape baseShape; // visual colony base
};