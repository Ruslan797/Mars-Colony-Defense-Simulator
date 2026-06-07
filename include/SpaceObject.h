#pragma once

#include "Vector2D.h"
#include <string>

// types of objects in the world
enum class ObjectType
{
    Unknown,
    AlienDrone,
    Meteor,
    RescueCapsule,
    Base   //  colony base
};

// current object state
enum class ObjectStatus
{
    Active,
    Disabled,
    Scanned
};

class SpaceObject
{
private:
    Vector2D position;      // object position in world
    ObjectType type;        // object type
    ObjectStatus status;    // current object status

public:
    SpaceObject(
        const Vector2D& position,
        ObjectType type
    );

    Vector2D getPosition() const;

    ObjectType getType() const;

    ObjectStatus getStatus() const;

    void setStatus(ObjectStatus status);

    static const char* objectTypeToString(ObjectType type);

    static const char* objectStatusToString(ObjectStatus status);
};