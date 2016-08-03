#include "Player.h"
#include "Camera.h"
#include <iostream>

Player::Player()
{
    if (!playerTexture.loadFromFile("textures/characters/player.png")) {
        std::cout << "Error: Missing player texture...\n";
    }

    player.setTexture(playerTexture);

    //Set players position.
    //Hopefully this is somewhere in our level...
    player.setPosition(250, 250);
}

void Player::handleEvents(sf::Event &event)
{
    //Keydown events.
    if (event.type == sf::Event::KeyPressed) {
        switch (event.key.code)
        {
            case sf::Keyboard::Left:
                velocity.x -= PLAYER_VELOCITY;
                break;

            case sf::Keyboard::Right:
                velocity.x += PLAYER_VELOCITY;
                break;

            case sf::Keyboard::Up:
                velocity.y -= PLAYER_VELOCITY;
                break;

            case sf::Keyboard::Down:
                velocity.y += PLAYER_VELOCITY;
                break;
        }
    }

    //Keyup events.
    if (event.type == sf::Event::KeyReleased) {
        switch (event.key.code)
        {
            case sf::Keyboard::Left:
                velocity.x += PLAYER_VELOCITY;
                break;

            case sf::Keyboard::Right:
                velocity.x -= PLAYER_VELOCITY;
                break;

            case sf::Keyboard::Up:
                velocity.y += PLAYER_VELOCITY;
                break;

            case sf::Keyboard::Down:
                velocity.y -= PLAYER_VELOCITY;
                break;
        }
    }
}

void Player::move(float deltaTime)
{
    position.x += velocity.x * deltaTime;
    position.y += velocity.y * deltaTime;

    player.move(position);
}


