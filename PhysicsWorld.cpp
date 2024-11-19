#include "PhysicsWorld.h"
#include "Particle.h"

const Vector2d PhysicsWorld::gravity = Vector2d(0.0f, 9.81f);

void PhysicsWorld::addParticle(Particle* particle)
{
    particles.push_back(particle);
}
void PhysicsWorld::ElasticCollision(Particle* particle1, Particle* particle2)
{
    Vector2d normal = (particle2->postion - particle1->postion).getNormalized();

    Vector2d relativeVelocity = particle1->velocity - particle2->velocity;

    float velocityAlongNormal = relativeVelocity.Dot(normal);

    if (velocityAlongNormal > 0)
        return;
    float e = 1.0f;

    float impulse = -(1 + e) * velocityAlongNormal / (1 / particle1->mass + 1 / particle2->mass);

    Vector2d impulseVector = impulse * normal;
    particle1->velocity += impulseVector / particle1->mass;
    particle2->velocity -= impulseVector / particle2->mass;

    // --- Position Correction ---
    float overlap = (particle1->circlshape.getRadius() + particle2->circlshape.getRadius()) -
        (particle2->postion - particle1->postion).getMagnitude();

    Vector2d correction = (overlap / 2.0f) * normal;
    particle1->postion -= correction;
    particle2->postion += correction;
}



void PhysicsWorld::Update(float deltaTime)
{
    for (Particle* particle : particles)
    {
        particle->addForce(gravity * particle->mass);  
        particle->addForce(Vector2d(100.0f, 0.0f));   
        particle->applyDrag();  
        particle->Update(deltaTime);
        particle->forces = Vector2d(0, 0);

        // Check for collisions between particles
        for (auto it = particles.begin(); it != particles.end(); ++it)
        {
            Particle* particle1 = *it;
            for (auto jt = next(it); jt != particles.end(); ++jt)
            {
                Particle* particle2 = *jt;

                //Circle Collision Check (Regular Collision)
                float distance = (particle1->postion - particle2->postion).getMagnitude();
                float combinedRadii = particle1->circlshape.getRadius() + particle2->circlshape.getRadius();
                if (distance < combinedRadii)
                {
                    std::cout << "2 circles collided!" << std::endl; 
                    // Elastic collision logic for circles
                    ElasticCollision(particle1, particle2);
                }

                // **AABB Collision Check**
                if (particle1->aabbCollider.checkCollision(particle2->aabbCollider))
                {
                    std::cout << "2 rectangles collided!" << std::endl;  
                }
                // SAT Collision
                if (particle1->satCollider.checkCollision(particle2->satCollider)) {
                    std::cout << "2 triangles collided!" << std::endl;
                }

            }
        }
    }
}
