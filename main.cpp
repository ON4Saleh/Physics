#include <SFML/Graphics.hpp>
#include "Renderer.h"
#include "PhysicsWorld.h"
#include "Particle.h"
#include "vector2d.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Particle Movement");

    Renderer renderer;
    PhysicsWorld physicsWorld;

    // Create particles
    Particle* particle1 = new Particle(Vector2d(100.0f, 100.0f), 1.0f, 0.3f);
    Particle* particle2 = new Particle(Vector2d(200.0f, 100.0f), 1.0f, 0.3f);

    particle1->velocity = Vector2d(50.0f, 0.0f); 
    particle2->velocity = Vector2d(-50.0f, 0.0f);

    physicsWorld.addParticle(particle1);
    physicsWorld.addParticle(particle2);
    renderer.AddDrawable(&particle1->circlshape);   
    renderer.AddDrawable(&particle1->recshape);    
    renderer.AddDrawable(&particle1->triangleShape);
    renderer.AddDrawable(&particle2->circlshape);   
    renderer.AddDrawable(&particle2->recshape);    // Add particle's rectangle shape
    renderer.AddDrawable(&particle2->triangleShape);


    sf::Clock clock;
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        float dt = clock.restart().asSeconds();

        physicsWorld.Update(dt);

        window.clear();
        renderer.Render(&window);
        window.display();
    }

    return 0;
}

