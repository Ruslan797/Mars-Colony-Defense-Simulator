#pragma once

#include <memory>

#include "Vector2D.h"
#include "SpaceObject.h"

class CameraSensor
{
private:
    Vector2D localPosition; // camera position relative to owner
    Vector2D worldPosition; // camera position in world coordinates

    double detectionRadius; // radius where camera can detect objects

    std::weak_ptr<SpaceObject> lastDetectedObject; // weak reference to detected object

public:
    CameraSensor(
        const Vector2D& localPosition,
        double detectionRadius
    );

    void updateWorldPosition(const Vector2D& ownerPosition); // update camera world position from owner

    bool canDetect(
        const std::shared_ptr<SpaceObject>& object
    ); // check if camera can detect object

    Vector2D getWorldPosition() const; // return camera world position

    double getDetectionRadius() const; // return detection radius

    void printLastDetectedObject() const; // print last detected object
};