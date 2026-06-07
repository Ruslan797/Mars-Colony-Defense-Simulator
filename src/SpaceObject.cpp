#include "SpaceObject.h"

SpaceObject::SpaceObject(
    const Vector2D& position,
    ObjectType type
)
{
    this->position = position; // set object position

    this->type = type; // set object type

    this->status = ObjectStatus::Active; // object starts as active
}

Vector2D SpaceObject::getPosition() const
{
    return position; // return object position
}

ObjectType SpaceObject::getType() const
{
    return type; // return object type
}

ObjectStatus SpaceObject::getStatus() const
{
    return status; // return object status
}

void SpaceObject::setStatus(ObjectStatus status)
{
    this->status = status; // change object status
}

const char* SpaceObject::objectTypeToString(ObjectType type)
{
    switch (type)
    {
    case ObjectType::Unknown:
        return "Unknown";

    case ObjectType::AlienDrone:
        return "AlienDrone";

    case ObjectType::Meteor:
        return "Meteor";

    case ObjectType::RescueCapsule:
        return "RescueCapsule";

    default:
        return "InvalidObjectType";
    }
}

const char* SpaceObject::objectStatusToString(ObjectStatus status)
{
    switch (status)
    {
    case ObjectStatus::Active:
        return "Active";

    case ObjectStatus::Disabled:
        return "Disabled";

    case ObjectStatus::Scanned:
        return "Scanned";

    default:
        return "InvalidObjectStatus";
    }
}