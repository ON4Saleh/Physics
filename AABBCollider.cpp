#include "AABBCollider.h"

AABBCollider::AABBCollider(Vector2d position, Vector2d size)
{
    updatePosition(position, size);  
}

void AABBCollider::updatePosition(Vector2d newPosition, Vector2d size)
{
    position = newPosition;
    ul = position - size / 2.0f;  
    lr = position + size / 2.0f;  
}

bool AABBCollider::checkCollision( AABBCollider& other) 
{
    if (lr.x < other.ul.x || ul.x > other.lr.x || lr.y < other.ul.y || ul.y > other.lr.y)
    {
        return false; 
    }
    return true;  
}
