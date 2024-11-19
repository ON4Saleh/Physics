#pragma once
#include "Vector2d.h"
#include <SFML/Graphics.hpp>
#include "Collider.h"
#include "AABBCollider.h"
#include "SATCollider.h"

class Particle
{
public:
    // Constructor
    Particle(Vector2d position, float mass = 5, float drag = 0.3f);

    // Public methods
    void Update(float dt);
    void addForce(Vector2d force);
    void updateTrianglePosition();
    void applyDrag();       
    void updateSATPoints();   

public:
    Vector2d postion;        
    Vector2d velocity;       
    Vector2d acceleration;   
    Vector2d forces;          
    float mass;               
    float drag;            
   
    sf::CircleShape circlshape;      
    sf::RectangleShape recshape;    
    sf::ConvexShape triangleShape;  

    Collider collider;              
    AABBCollider aabbCollider;      
    SATCollider satCollider;       
};
