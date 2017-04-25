#include "Collision.h"
#include <iostream>

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

void Collision::positionBoundaryCollisionBoxes()
{
    static int x = 0;
    static int y = 0;
    for (int i = 0; i < MAX_COLLISION_BOXES; ++i) {
        collVector[i]->setPosition(x, y);
        x += 32;
        if (i == 15) {
            x = 32;
            y = 480;
        }
    }
    //Reset our vertical position, to move up and down
    //instead of left or right
    y = 0;
    for (int i = 30; i < MAX_COLLISION_BOXES; ++i) {
        collVector[i]->setPosition(0, y);
        y += 32;

    }
    y = 0;
    for (int i = 46; i < MAX_COLLISION_BOXES; ++i) {
        collVector[i]->setPosition(480, y);
        y += 32;
    }
}

void Collision::positionWorldCollisionBoxes(const std::vector<long int> &level)
{
    resetCollision();
    int x = 0;
    int y = 0;
    for (int i = 0; i < MAX_COLLISION_BOXES; ++i) {
        x += 32;
        if (i % 16 == 0) {
            //Adjust our positions, we have gone
            //off the edge of the screen.
            x = 0;
            y += 32;
        }
        //The world objects we should collide with.
        if (level[i] == 3 || level[i] == 6 || level[i] == 7 || level[i] == 10 ||
                    level[i] == 11 || level[i] == 12) {

            collVector[i]->setPosition(x, y - 32);
        }
    }
}

void Collision::resetCollision()
{
    for (int i = 0; i < MAX_COLLISION_BOXES; ++i) {
        collVector[i]->setPosition(0, 0);
    }
}
