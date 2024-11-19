#pragma once
#include "Vector2d.h"

class AABBCollider
{
public:
    Vector2d ul;  
    Vector2d lr; 
    Vector2d position; 

    AABBCollider(Vector2d position = Vector2d(0, 0), Vector2d size = Vector2d(0, 0));

    void updatePosition(Vector2d newPosition, Vector2d size);

    bool checkCollision(AABBCollider& other);
};
