#include "include/Mouse.h"

float Mouse::calculateMouseAngle(float mouseX, float mouseY, float positionX, float positionY)
{
    //Calcualte the mouse angle with atan2.
    float angle = std::atan2(mouseY - positionY, mouseX - positionX);
    angle = angle * 180 / M_PI;
    if (angle < 0) {
        angle = 360 -(-angle);
    }
    return angle;
}

void Mouse::update(sf::Event &event, sf::Window &window) {
    if (event.type == sf::Event::MouseMoved) {
        //Calculate the mouse position every frame
        mouseX = sf::Mouse::getPosition(window).x;
        mouseY = sf::Mouse::getPosition(window).y;
    }
}

float Mouse::getMouseAngle()
{
    Player player;
    Config config;

    //Set the angle relative to the player
    mouseAngle = calculateMouseAngle(mouseX, mouseY, config.getScreenWidth() / 2 + player.size.x,
                                                   config.getScreenHeight() / 2 + player.size.y);

    return mouseAngle;
}
