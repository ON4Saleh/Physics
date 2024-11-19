#ifndef SATCOLLIDER_H
#define SATCOLLIDER_H
#include <vector>
#include "Vector2d.h"  

class SATCollider {
public:
    Vector2d position;
     std::vector<Vector2d> points;

    void updatePosition(Vector2d position);

    std::vector<Vector2d> getNormals();
    Vector2d SATShape(Vector2d axis);
    bool checkCollision(SATCollider other);
    SATCollider() : position(0, 0) {}

    
     SATCollider(const std::vector<Vector2d>& points) : points(points) {}
};

#endif 
