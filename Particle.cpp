#include "Particle.h"

Particle::Particle(Vector2d position, float mass, float drag)
    : postion(position), mass(mass), drag(drag), forces(0.0f, 0.0f)
{
    // Circle setup
    circlshape.setRadius(10.0f);
    circlshape.setFillColor(sf::Color::Green);
    circlshape.setOrigin(circlshape.getRadius(), circlshape.getRadius());
    circlshape.setPosition(position.x, position.y);

    // Rectangle setup
    recshape.setSize(sf::Vector2f(20.0f, 20.0f));
    recshape.setFillColor(sf::Color(255, 0, 0, 100));
    recshape.setOrigin(recshape.getSize() / 2.0f);
    recshape.setPosition(position.x, position.y);

    // Triangle setup
    triangleShape.setPointCount(3);
    triangleShape.setPoint(0, sf::Vector2f(0, 0));
    triangleShape.setPoint(1, sf::Vector2f(50, 0));
    triangleShape.setPoint(2, sf::Vector2f(25, 50)); triangleShape.setOrigin(25.0f, 25.0f); // Center origin for rotation
    triangleShape.setPosition(position.x, position.y);

    // Collider setup
    collider.r = circlshape.getRadius();
    collider.center = position;

    aabbCollider.updatePosition(position, Vector2d(20.0f, 20.0f));
    updateSATPoints();
}

void Particle::updateSATPoints() {
    satCollider.points = {
        Vector2d(postion.x - 10.0f, postion.y - 10.0f),
        Vector2d(postion.x + 10.0f, postion.y - 10.0f),
        Vector2d(postion.x + 10.0f, postion.y + 10.0f),
        Vector2d(postion.x - 10.0f, postion.y + 10.0f)
    };
}


void Particle::Update(float dt)
{
    applyDrag();

    velocity += acceleration * dt;
    postion += velocity * dt;

    circlshape.setPosition(postion.x + 100, postion.y + 100);
    collider.center = postion;
    recshape.setPosition(postion.x + 150, postion.y + 150);
    aabbCollider.updatePosition(postion, Vector2d(20.0f, 20.0f));
    triangleShape.setPosition(postion.x + 200, postion.y + 200); 

    updateSATPoints();
   
    forces = Vector2d(0.0f, 0.0f);
}

void Particle::addForce(Vector2d force)
{
    forces += force;
    if (mass != 0) {
        acceleration = forces / mass;
    }
}
void Particle::updateTrianglePosition()
{
    triangleShape.setPosition(postion.x, postion.y);
}
void Particle::applyDrag() {
    if (velocity.getMagnitude() > 0) {
        Vector2d dragForce = -drag * velocity.getNormalized() * velocity.getMagnitude();
        forces += dragForce;
    }
}
