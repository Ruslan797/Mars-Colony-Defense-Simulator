#include "Vector2D.h"
#include <cmath>

Vector2D::Vector2D() 
{
    x = 0;
    y = 0;
}

Vector2D::Vector2D(double x, double y) 
{
    this->x = x;
    this->y = y;
}

double Vector2D::getX() const 
{
    return x;
}

double Vector2D::getY() const 
{
    return y;
}

void Vector2D::setX(double x) 
{
    this->x = x;
    
}

void Vector2D::setY(double y) 
{
    this->y = y;
    
}

double Vector2D::distanceTo(const Vector2D& other) const
{
    double dx = other.getX() - x;
    double dy = other.getY() - y;

    return std::sqrt(dx * dx + dy * dy);
}


double Vector2D::length() const
{
    return std::sqrt(x * x + y * y); // calculate length using Pythagoras
}

Vector2D Vector2D::normalized() const
{
    double len = length(); // get current vector length

    if (len == 0) // avoid division by zero
    {
        return Vector2D(0, 0); // zero vector has no direction
    }

    return Vector2D(x / len, y / len); // return vector with length 1
}

Vector2D Vector2D::operator+(const Vector2D& other) const
{
    return Vector2D(x + other.getX(), y + other.getY()); // add x and y values
}

Vector2D Vector2D::operator-(const Vector2D& other) const
{
    return Vector2D(x - other.getX(), y - other.getY()); // subtract x and y values
}

Vector2D Vector2D::operator*(double scalar) const
{
    return Vector2D(x * scalar, y * scalar); // multiply vector by number
}

