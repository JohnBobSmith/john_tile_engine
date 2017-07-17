#define _USE_MATH_DEFINES
#include <cmath>
#include "../include/Mouse.h"
#include "../include/Player.h"
#include "../include/Config.h"
#include <iostream>

Player player;
Config config;

float Mouse::calculateMouseAngle(float mouseX, float mouseY, float positionX, float positionY)
{
    float angle = std::atan2(mouseY - positionY, mouseX - positionX);
    angle = angle * 180 / M_PI;
    if (angle < 0) {
        angle = 360 -(-angle);
    }
    return angle;
}

void Mouse::handleMouseEvents(sf::Event &event, sf::Window &window) {
    if (event.type == sf::Event::MouseMoved) {
        //Calculate the mouse position every frame
        mouseX = sf::Mouse::getPosition(window).x;
        mouseY = sf::Mouse::getPosition(window).y;

        //Set the angle relative to the player
        mouseAngle = calculateMouseAngle(mouseX, mouseY, config.getScreenWidth() / 2 + player.size.x,
                                                       config.getScreenHeight() / 2 + player.size.y);
    }
}
