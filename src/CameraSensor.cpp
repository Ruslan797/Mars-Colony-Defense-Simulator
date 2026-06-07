#include "CameraSensor.h"

#include <iostream>

CameraSensor::CameraSensor(
    const Vector2D& localPosition,
    double detectionRadius
)
{
    this->localPosition = localPosition; // set local camera position

    this->worldPosition = localPosition; // initial world position

    this->detectionRadius = detectionRadius; // set detection radius
}

void CameraSensor::updateWorldPosition(
    const Vector2D& ownerPosition
)
{
    worldPosition =
        ownerPosition + localPosition; // calculate world position
}

bool CameraSensor::canDetect(
    const std::shared_ptr<SpaceObject>& object
)
{
    double distance =
        worldPosition.distanceTo(
            object->getPosition()
        );

    // object detected
    if (distance <= detectionRadius)
    {
        lastDetectedObject = object; // store weak reference

        return true;
    }

    return false;
}

Vector2D CameraSensor::getWorldPosition() const
{
    return worldPosition; // return camera world position
}

double CameraSensor::getDetectionRadius() const
{
    return detectionRadius; // return detection radius
}

void CameraSensor::printLastDetectedObject() const
{
    // convert weak_ptr -> shared_ptr temporarily
    std::shared_ptr<SpaceObject> object =
        lastDetectedObject.lock();

    // check if object still exists
    if (object)
    {
        Vector2D pos = object->getPosition();

        std::cout
            << "Last detected object at: ("
            << pos.getX()
            << ", "
            << pos.getY()
            << ")"
            << std::endl;

        std::cout
            << "Object type: "
            << SpaceObject::objectTypeToString(
                object->getType()
            )
            << std::endl;
    }
    else
    {
        std::cout
            << "No detected object"
            << std::endl;
    }
}