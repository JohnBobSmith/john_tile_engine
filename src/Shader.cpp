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

void Shader::animate(bool isAnimated)
{
    static float counter = 0.0f;
    if (isAnimated) {
        counter += 0.1f;
        deathShape.setScale(sf::Vector2f(counter, counter));
    } else {
        //Reset
        if (deathShape.getScale().x > 0.0f) {
            counter -= 1.0f;
            deathShape.setScale(sf::Vector2f(counter, counter));
            if (counter < 0.1f) {
                counter = 0.1f;
            }
        }
    }
}
