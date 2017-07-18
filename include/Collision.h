#ifndef COLLISION_H
#define COLLISION_H

#include <SFML/Graphics.hpp>
#include <unordered_set>
#include <vector>
#include <string>
#include <memory>

class Collision
{
    public:
        //Allow our collision boxes to have a color,
        //for debugging purposes.
        Collision(sf::Color color = sf::Color::Cyan);
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

        //Place the collision boxes at certain points in the level.
        void positionCollisionBoxes(const std::vector<long int> &level,
                                    const std::unordered_set<int> &objectsToCollideWith,
                                    int offsetX, int offsetY);

        //Reset the collision boxes by placing them at 0,0.
        void resetCollision();

        //Store our collisions boxes in an std::vector
        struct bbox
        {
            sf::RectangleShape bbox;
            int id;
            bool isTouching;
        };

        //Store our structs in an std::vector
        std::vector<std::shared_ptr<bbox>> collVector;

        //Cap our collisions boxes
        const int MAX_COLLISION_BOXES = 256;
};

#endif // COLLISIONBOX_H
