#include "Player.h"
#include "Camera.h"
#include <iostream>

Player::Player()
{
    if (!playerTexture.loadFromFile("textures/entity/player.png")) {
        std::cout << "Error: Missing player texture...\n";
    }

    player.setTexture(playerTexture);

    //Set players position.
    //Hopefully this is somewhere in our level...
    player.setPosition(0, 0);
}

void Player::handleEvents(sf::Event &event)
{
    if (event.type == sf::Event::KeyPressed) {
        switch (event.key.code)
        {
            case sf::Keyboard::Left:
                position.x -= 1;
                break;

            case sf::Keyboard::Right:
                position.x += 1;
                break;

            case sf::Keyboard::Up:
                position.y -= 1;
                break;

            case sf::Keyboard::Down:
                position.y += 1;
                break;
        }
    }

    if (event.type == sf::Event::KeyReleased) {
        switch (event.key.code)
        {
            case sf::Keyboard::Left:
                position.x += 1;
                break;

            case sf::Keyboard::Right:
                position.x -= 1;
                break;

            case sf::Keyboard::Up:
                position.y += 1;
                break;

            case sf::Keyboard::Down:
                position.y -= 1;
                break;
        }
    }
}

void Player::move(float deltaTime)
{
    player.move(position.x, position.y);
}


