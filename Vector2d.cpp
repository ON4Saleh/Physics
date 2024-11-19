#include "vector2d.h"
#include <iostream>

Vector2d::Vector2d() : x(0), y(0) {}
Vector2d::Vector2d(float x, float y) : x(x), y(y) {}

Vector2d Vector2d::operator+(Vector2d other) {
    return Vector2d(x + other.x, y + other.y);
}

Vector2d Vector2d::operator+=(Vector2d other) {
    x += other.x;
    y += other.y;
    return *this;
}
Vector2d Vector2d::operator-(Vector2d other) {
    return Vector2d(x - other.x, y - other.y);
}

Vector2d Vector2d::operator-=(Vector2d other) {
    x -= other.x;
    y -= other.y;
    return *this;
}

Vector2d Vector2d::operator/(float scalar)
{
    return Vector2d(x / scalar, y / scalar);
}
Vector2d operator*(float a, Vector2d vector) {
    return Vector2d(vector.x * a, vector.y * a);
}
Vector2d Vector2d::operator*(float a) const {
    return Vector2d(x * a, y * a);
}
float Vector2d::getMagnitude() {
    return sqrt(x * x + y * y);
}

Vector2d Vector2d::getNormalized() {
    float magnitude = getMagnitude();
    if (magnitude != 0)
        return Vector2d(x / magnitude, y / magnitude);
    else
        return Vector2d(0, 0);
}float Vector2d::Dot(Vector2d& other) {
    return x * other.x + y * other.y;
}
Vector2d Vector2d::getNormal() {
    return Vector2d(-y, x);  
}

