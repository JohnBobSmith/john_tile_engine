#include "Collision.h"

Collision::Collision()
{
    //Populate our collision vector
    for (int i = 0; i < MAX_COLLISION_BOXES; ++i) {
        collVector.push_back(new sf::RectangleShape);
        collVector[i]->setSize(sf::Vector2f(32, 32));
        collVector[i]->setFillColor(sf::Color::Cyan);
        collVector[i]->setPosition(32, 0);
    }
}

Collision::~Collision()
{
    for (std::vector<sf::RectangleShape*>::iterator it = collVector.begin(); it != collVector.end(); ++it) {
        delete *it;
    }
}

bool Collision::checkAABBcollision(float xA, float yA, float wA, float hA,
                                   float xB, float yB, float wB, float hB)
{
    //Axis aligned bounding box collision detection.
    //Which side of the box are we on?
    float leftA, leftB;
    float rightA, rightB;
    float topA, topB;
    float bottomA, bottomB;

    //Assign the sides for A...
    leftA = xA;
    rightA = xA + wA;
    topA = yA;
    bottomA = yA + hA;

    //...and B
    leftB = xB;
    rightB = xB + wB;
    topB = yB;
    bottomB = yB + hB;

    //If bottomA intersects topB
    if(bottomA <= topB){
        return false;
    }

    //If topA intersects bottomB
    if(topA >= bottomB){
        return false;
    }

    //If rightA intersects leftB
    if(rightA <= leftB){
        return false;
    }

    //If leftA intersects rightB
    if(leftA >= rightB){
        return false;
    }

    //Not sure why this is required... RIP
    return true;
}

