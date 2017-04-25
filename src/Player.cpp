#include "Player.h"
#include "Camera.h"
#include "Collision.h"
#include <string>
#include <iostream>

//Initialize our base values
Player::Player()
{
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
}

bool Player::setTexture(std::string path)
{
    if (!texture.loadFromFile(path.c_str())) {
        std::cerr << "Error: Missing texture " << path.c_str();
        return false;
    }
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

//Keep track of how many keys are pressed.
static int keyCounter = 0;
void Player::handlePlayerEvents(sf::Event event)
{
    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Up) {
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
        if (keyCounter == 1) {
            isWalking = false;
        }
        sprite.setTextureRect(sf::IntRect(0, 0, 22, 32));
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
    for (int i = 0; i < collision.MAX_COLLISION_BOXES; ++i) {
        if (collision.checkAABBcollision(sprite.getPosition().x, sprite.getPosition().y, size.x, size.y,
                                         collision.collVector[i]->getPosition().x,
                                         collision.collVector[i]->getPosition().y,
                                         collision.collVector[i]->getSize().x,
                                         collision.collVector[i]->getSize().y)) {

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
            camera.setCamCenter(sf::Vector2f(sprite.getPosition().x, sprite.getPosition().y));
        }
    }
}
