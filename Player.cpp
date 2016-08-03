#include "Player.h"
#include "Camera.h"
#include <iostream>

Player::Player()
{
    if (!playerTexture.loadFromFile("textures/errors/errortex.png")) {
        std::cout << "Error: Missing player texture...\n";
    }

    player.setTexture(playerTexture);

    //Set players position.
    //Hopefully this is somewhere in our level...
    player.setPosition(250, 250);
}

void Player::handleEvents(sf::Event &event)
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        velocity.x -= PLAYER_VELOCITY;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        velocity.x += PLAYER_VELOCITY;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
        velocity.y -= PLAYER_VELOCITY;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
        velocity.y += PLAYER_VELOCITY;
    }
}

void Player::move(float deltaTime)
{
    //Move our camera
    Camera camera;

    position.x += velocity.x * deltaTime;
    position.y += velocity.y * deltaTime;

    player.move(position.x, position.y);

    camera.moveCam(position.x, position.y);
}


