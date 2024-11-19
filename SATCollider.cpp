#include "SATCollider.h"
void SATCollider::updatePosition(Vector2d position) {
    this->position = position;

    for (auto& point : points) {
        point += position;
    }
}

std::vector<Vector2d> SATCollider::getNormals() {
    std::vector<Vector2d> normals;

    for (size_t i = 0; i < points.size(); ++i) {
        Vector2d p1 = points[i];
        Vector2d p2 = points[(i + 1) % points.size()];
        Vector2d edge = p2 - p1;

        normals.push_back(edge.getNormal());
    }

    return normals;
}
Vector2d SATCollider::SATShape(Vector2d axis) {
    float min = axis.Dot(points[0]);
    float max = min;
    for (size_t i = 1; i < points.size(); ++i) {
        float projection = axis.Dot(points[i]);
        min = std::min(min, projection);
        max = std::max(max, projection);
    }
    return Vector2d(min, max);  
}

bool SATCollider::checkCollision(SATCollider other) {
    std::vector<Vector2d> thisNormals = this->getNormals();
    std::vector<Vector2d> otherNormals = other.getNormals();

    thisNormals.insert(thisNormals.end(), otherNormals.begin(), otherNormals.end());

    for (const Vector2d& axis : thisNormals) {
        Vector2d thisProjection = this->SATShape(axis);
        Vector2d otherProjection = other.SATShape(axis);

        if (thisProjection.y < otherProjection.x || otherProjection.y < thisProjection.x) {
            return false;  
        }
    }
    return true;  
}
