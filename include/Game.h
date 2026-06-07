#pragma once

#include "World.h"
#include "GraphicsRenderer.h"

class Game
{
private:
    World world; // main simulation world

    GraphicsRenderer renderer; // graphics renderer

    void setup(); // create drones and objects

public:
    void run(); // start game loop
};