#ifndef COLLISION_H
#define COLLISION_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

class Collision
{
    public:
        Collision();
        ~Collision();
        /*
            bool checkAABBcollision(float xA, float yA, float wA, float hA,
                            float xB, float yB, float wB, float hB);
            xA = object A's x position
            yA = object A's y position
            wA = width of A
            hA = height of A
            Repeat for B values
        */
        bool checkAABBcollision(float xA, float yA, float wA, float hA,
                                float xB, float yB, float wB, float hB);

        //Store our collisions boxes in an std::vector
        std::vector<sf::RectangleShape*> collVector;

        //Cap our collisions boxes
        const int MAX_COLLISION_BOXES = 256;
};

#endif // COLLISIONBOX_H
