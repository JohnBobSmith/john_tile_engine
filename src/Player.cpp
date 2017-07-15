#include "../include/Player.h"
#include "../include/Camera.h"
#include "../include/Collision.h"
#include <string>
#include <iostream>

//Initialize our base values
Player::Player()
{
    keyCounter = 0;
    isActive = true;
    isWalking = false;
    position.x = 0;
    position.y = 0;
    velocity.x = 0;
    velocity.y = 0;
    maxVelocity = 1;
    size.x = 32;
    size.y = 32;
    health = 100.0f;

    //Setup our spawn points.
    for (int i = 0; i < MAX_SPAWN_POINTS; ++i) {
        spawnPoints.push_back(sf::Vector2f(0, 0));
    }
    spawnPoints[0].x = 50;
    spawnPoints[0].y = 50;
    spawnPoints[1].x = 230;
    spawnPoints[1].y = -460;
    spawnPoints[2].x = 774;
    spawnPoints[2].y = -284;
    spawnPoints[3].x = 945;
    spawnPoints[3].y = -50;
    spawnPoints[4].x = 870;
    spawnPoints[4].y = 280;
    spawnPoints[5].x = 776;
    spawnPoints[5].y = 320;
    spawnPoints[6].x = 175;
    spawnPoints[6].y = 400;
    spawnPoints[7].x = 328;
    spawnPoints[7].y = -99;
    spawnPoints[8].x = 517;
    spawnPoints[8].y = 5;
    spawnPoints[9].x = 867;
    spawnPoints[9].y = -441;
}

bool Player::setTexture(std::string path)
{
    //If we cannot load the texture, error out.
    if (!texture.loadFromFile(path.c_str())) {
        std::cerr << "Error: Missing texture " << path.c_str();
        return false;
    }
    //Otherwise, set the texture and return success.
    sprite.setTexture(texture);
    return true;
}

void Player::movePlayer()
{
    //Move our player
    position.x = velocity.x;
    position.y = velocity.y;
    sprite.move(position);
}

void Player::handlePlayerEvents(sf::Event event)
{
    //If key is pressed...
    if (event.type == sf::Event::KeyPressed) {
        //...Look for the keycode, and then...
        if (event.key.code == sf::Keyboard::Up) {
            //...Do stuff
            velocity.y -= maxVelocity;
            keyCounter += 1;
            isWalking = true;
        }
        if (event.key.code == sf::Keyboard::Down) {
            velocity.y += maxVelocity;
            keyCounter += 1;
            isWalking = true;
        }
        if (event.key.code == sf::Keyboard::Left) {
            velocity.x -= maxVelocity;
            keyCounter += 1;
            isWalking = true;
        }
        if (event.key.code == sf::Keyboard::Right) {
            velocity.x += maxVelocity;
            keyCounter += 1;
            isWalking = true;
        }
    }
    //Stop moving when we release the key
    if (event.type == sf::Event::KeyReleased) {
        //If only one key is pressed...
        if (keyCounter == 1) {
            //...Do stuff
            isWalking = false;
        }
        //Reset our texture rect when we stop walking
        sprite.setTextureRect(sf::IntRect(0, 0, 22, 32));

        //When we release a key, adjust player attributes
        if (event.key.code == sf::Keyboard::Up) {
            velocity.y += maxVelocity;
            keyCounter -= 1;
        }
        if (event.key.code == sf::Keyboard::Down) {
            velocity.y -= maxVelocity;
            keyCounter -= 1;
        }
        if (event.key.code == sf::Keyboard::Left) {
            velocity.x += maxVelocity;
            keyCounter -= 1;
        }
        if (event.key.code == sf::Keyboard::Right) {
            velocity.x -= maxVelocity;
            keyCounter -= 1;
        }
    }
}

void Player::animate()
{
    /* TODO:
    A future version of this algorithm
    should use SFML's clock and time features.
    This works fine currently and I'm not going to
    bother changing it (for now).
    */
    //Animate the player
    static int counter = 0;
    static float timer = 5.0f;
    if (isWalking) {
        timer -= 1.0f;
        if (timer == 0.0f) {
            //Cycle through our sprite sheet
            sprite.setTextureRect(sf::IntRect(counter, 0, 22, 32));
            timer = 5.0f;
        }
        counter += 22; //22 is the width of one sprite on the sheet
        //If we reached the end of the sheet, reset.
        if (counter == 88) {
            counter = 0;
        }
    }
}

bool Player::checkCollision(Collision &collision, Camera &camera)
{
    //If there is a collision...
    for (int i = 0; i < collision.MAX_COLLISION_BOXES; ++i) {
        if (collision.checkAABBcollision(sprite.getPosition().x, sprite.getPosition().y,
                                         size.x - 8, size.y, //Players size
                                         collision.collVector[i]->bbox.getPosition().x,
                                         collision.collVector[i]->bbox.getPosition().y,
                                         collision.collVector[i]->bbox.getSize().x,
                                         collision.collVector[i]->bbox.getSize().y)) {
            //We touched a collision box
            collision.collVector[i]->isTouching = true;

            //...Move the sprite back
            if (position.x == -1) {
                sprite.move(1, 0);
            }
            if (position.x == 1) {
                sprite.move(-1, 0);
            }
            if (position.y == 1) {
                sprite.move(0, -1);
            }
            if (position.y == -1) {
                sprite.move(0, 1);
            }
            //Update the camera
            camera.setCamCenter(sf::Vector2f(sprite.getPosition().x, sprite.getPosition().y));

            //Collided
            return true;
        } else {
            //Reset the collision
            collision.collVector[i]->isTouching = false;
        }
    }
    //Did not collide
    return false;
}

bool Player::checkAudioCollsion(Collision &collision)
{
    for (int i = 0; i < collision.MAX_COLLISION_BOXES; ++i) {
        if (collision.checkAABBcollision(sprite.getPosition().x, sprite.getPosition().y,
                                         size.x - 8, size.y, //Players size
                                         collision.collVector[i]->bbox.getPosition().x,
                                         collision.collVector[i]->bbox.getPosition().y,
                                         collision.collVector[i]->bbox.getSize().x,
                                         collision.collVector[i]->bbox.getSize().y)) {
            //Collided
            return true;
        }
    }
    //Did not collide
    return false;
}

void Player::applyDamage(int ammount)
{
    health -= ammount;
    if (health <= 0) {
        killPlayer();
    }
}

void Player::killPlayer()
{
    health = -999;
    isActive = false;
}

void Player::respawn(Camera &camera, int randomNumber)
{
    health = 100;
    isActive = true;

    sprite.setPosition(spawnPoints[randomNumber]);
    camera.setCamCenter(sf::Vector2f(sprite.getPosition().x, sprite.getPosition().y));
}
