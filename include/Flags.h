#ifndef FLAGS_H
#define FLAGS_H

#include "../include/Collision.h"
#include "../include/Camera.h"
#include "../include/Player.h"
#include "../include/Config.h"

class Flags
{
    public:
        //Position our flags collision boxes
        void positionFlags(Collision &collision);

        //Check for collisions
        void checkCollision(Collision &collision, Camera &camera, Player &player, Config &config);
};

#endif // FLAGS_H
