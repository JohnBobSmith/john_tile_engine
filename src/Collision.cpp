#include "include/Collision.h"
#include <iostream>
#include <cmath>
#include "include/Config.h"

Collision::Collision(sf::Color color)
{
    //Populate our collision vector
    for (int i = 0; i < MAX_COLLISION_BOXES; ++i) {
        collVector.push_back(std::make_shared<bbox>());
        collVector[i]->bbox.setSize(sf::Vector2f(32, 32));
        collVector[i]->bbox.setFillColor(color);
        collVector[i]->bbox.setPosition(-999, 0);
        collVector[i]->isTouching = false;
        collVector[i]->isActive = false;
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
    
    return true;
}

bool Collision::checkCircleCollision(sf::CircleShape circle, sf::Vector2f rectPosition, float width, float height)
{ 
    float Radius1 = (circle.getRadius() + circle.getRadius()) / 4;
    float Radius2 = (width + height) / 4;
    float xd = rectPosition.x - circle.getPosition().x;// - rectPosition.x;
    float yd = rectPosition.y - circle.getPosition().y;// - rectPosition.y;
    
    std::cout << std::sqrt(xd * xd + yd * yd) << "\n";
    std::cout << Radius1 + Radius2 << "\n";
    
    return std::sqrt(xd * xd + yd * yd) <= Radius1 + Radius2;
}

void Collision::positionCollisionBoxes(const std::vector<long int> &level,
                      const std::unordered_set<int> &objectsToCollideWith,
                                                 int offsetX, int offsetY)
{
    //For our unordered sets
    Config config;

    //Reset the world
    resetCollision();
    int x = offsetX;
    int y = offsetY;
    for (int i = 0; i < MAX_COLLISION_BOXES; ++i) {
        x += 32;
        if (i % 16 == 0) {
            //Adjust our positions, we have gone
            //off the edge of the screen.
            x = offsetX;
            y += 32;
        }
        //The world objects we should collide with per map basis.
        if (objectsToCollideWith.count(level[i])) {
            collVector[i]->isActive = true;
            collVector[i]->bbox.setPosition(x, y - 32);
        }
    }
}

void Collision::resetCollision()
{
    //Reset our collision vector by moving
    //everything off screen.
    for (int i = 0; i < MAX_COLLISION_BOXES; ++i) {
        collVector[i]->isActive = false;
        collVector[i]->bbox.setPosition(-999, 0);
    }
}
