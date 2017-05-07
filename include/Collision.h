#ifndef COLLISION_H
#define COLLISION_H

#include <SFML/Graphics.hpp>
#include <unordered_set>
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

        //Position our collision boxes that are on the
        //borders of the screen.
        void positionBoundaryCollisionBoxes();

        //Place the collision boxes at certain points in the level.
        void positionWorldCollisionBoxes(const std::vector<long int> &level,
                                         const std::unordered_set<int> &objectsToCollideWith);

        //Reset the collision boxes by placing them at 0,0.
        void resetCollision();

        //Store our collisions boxes in an std::vector
        std::vector<sf::RectangleShape*> collVector;

        //Cap our collisions boxes
        const int MAX_COLLISION_BOXES = 256;
};

#endif // COLLISIONBOX_H
