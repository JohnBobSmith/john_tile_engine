#include "../include/Flags.h"
#include "../include/Collision.h"
#include "../include/Camera.h"
#include "../include/Player.h"
#include "../include/Config.h"

void Flags::positionFlags(Collision &collision)
{
    //Position the collision boxes for our flags
    for (int i = 0; i < collision.MAX_COLLISION_BOXES; ++i) {
        collision.collVector[i]->setPosition(0, 0);
    }
    //Top flag
    collision.collVector[0]->setPosition(224, 32);
    //Left flag
    collision.collVector[1]->setPosition(32, 224);
    //Right flag
    collision.collVector[2]->setPosition(448, 224);
    //Bottom flag
    collision.collVector[3]->setPosition(224, 448);
}

void Flags::checkCollision(Collision &collision, Camera &camera, Player &player, Config &config)
{
    //Did the player touch a flag?
    //If so, change levels.
    static bool isLevelChanged = false;
    for (int i = 0; i < collision.MAX_COLLISION_BOXES; ++i) {
        if (collision.checkAABBcollision(player.sprite.getPosition().x, player.sprite.getPosition().y,
                                         player.size.x - 8, player.size.y,
                                         collision.collVector[i]->getPosition().x,
                                         collision.collVector[i]->getPosition().y,
                                         collision.collVector[i]->getSize().x,
                                         collision.collVector[i]->getSize().y)) {
            //Change levels
            changeLevel(config);

            //Position our player depending on which the player hit
            //Left Flag
            if (player.sprite.getPosition().x < 80) {
                player.sprite.setPosition(400, 224);
            }
            //Right flag
            if (player.sprite.getPosition().x > 410) {
                player.sprite.setPosition(85, 224);
            }
            //Top flag
            if (player.sprite.getPosition().y < 80) {
                player.sprite.setPosition(224, 400);
            }
            //Bottom flag
            if (player.sprite.getPosition().y > 410) {
                player.sprite.setPosition(224, 85);
            }
            //Update the camera
            camera.setCamCenter(sf::Vector2f(player.sprite.getPosition().x,
                                           player.sprite.getPosition().y));
        }
    }
}

void Flags::changeLevel(Config &config)
{
    //Change levels
    if (config.LEVEL_STRING == "grassland" && !isLevelChanged) {
        config.LEVEL_STRING = "farmland";
        isLevelChanged = true;
    }
    if (config.LEVEL_STRING == "farmland" && !isLevelChanged) {
        config.LEVEL_STRING = "grassland";
        isLevelChanged = true;
    }

    //Reset
    if (isLevelChanged) {
        isLevelChanged = false;
    }
}

