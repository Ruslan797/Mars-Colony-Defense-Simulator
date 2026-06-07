#pragma once


class Vector2D 
{
private:
    double x;
    double y;

public:
    Vector2D();
    Vector2D(double x, double y);

    double getX() const;
    double getY() const;

    void setX(double x);
    void setY(double y);

    double distanceTo(const Vector2D& other) const;
    
    double length() const;          // calculate vector length
    
    
    Vector2D normalized() const;                 // return unit direction vector

    Vector2D operator+(const Vector2D& other) const; // add two vectors
    Vector2D operator-(const Vector2D& other) const; // subtract two vectors
    Vector2D operator*(double scalar) const;          // multiply vector by number
};

    