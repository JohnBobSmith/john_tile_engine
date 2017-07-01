#include "Shader.h"
#include "../include/Player.h"
#include <iostream>

Shader::Shader()
{
    Player player;

    deathShape.setRadius(50);
    deathShape.setPointCount(100);
    deathShape.setFillColor(sf::Color::Green);
    deathShape.setPosition(player.sprite.getPosition().x / 2, player.sprite.getPosition().y / 2);

    if (!deathShader.loadFromFile("shaders/deathShader.frag", sf::Shader::Fragment)) {
        std::cerr << "Error: Cannot load shader!\n";
    }
}
