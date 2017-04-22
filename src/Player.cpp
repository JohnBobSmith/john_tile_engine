#include "Player.h"
#include <string>
#include <iostream>

//Initialize our base values
Player::Player()
{
    isActive = true;
    position.x = 0;
    position.y = 0;
    velocity.x = 0;
    velocity.y = 0;
    maxVelocity = 1;
    size.x = 32;
    size.y = 32;
    health = 100.0f;
    canMove = true;
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
    //Move our player.
    position.x = velocity.x;
    position.y = velocity.y;
    sprite.move(position);
}

void Player::handlePlayerEvents(sf::Event event)
{
    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Up) {
            velocity.y -= maxVelocity;
        }
        if (event.key.code == sf::Keyboard::Down) {
            velocity.y += maxVelocity;
        }
        if (event.key.code == sf::Keyboard::Left) {
            velocity.x -= maxVelocity;
        }
        if (event.key.code == sf::Keyboard::Right) {
            velocity.x += maxVelocity;
        }
    }
    //Stop moving when we release the key
    if (event.type == sf::Event::KeyReleased) {
        if (event.key.code == sf::Keyboard::Up) {
            velocity.y += maxVelocity;
        }
        if (event.key.code == sf::Keyboard::Down) {
            velocity.y -= maxVelocity;
        }
        if (event.key.code == sf::Keyboard::Left) {
            velocity.x += maxVelocity;
        }
        if (event.key.code == sf::Keyboard::Right) {
            velocity.x -= maxVelocity;
        }
    }
}
