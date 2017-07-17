#define _USE_MATH_DEFINES
#include <cmath>
#include "../include/Mouse.h"
#include "../include/Player.h"
#include "../include/Camera.h"
Player player;
Camera camera;

float Mouse::calculateMouseAngle(float mouseX, float mouseY, float positionX, float positionY)
{
    float angle = std::atan2(mouseY - positionY, mouseX - positionX);
    angle = angle * 180 / M_PI;
    if (angle < 0) {
        angle = 360 -(-angle);
    }
    return angle;
}

void Mouse::handleMouseEvents(sf::Event &event) {
    if (event.type == sf::Event::MouseMoved) {
        //Calculate the mouse position every frame
        mouseX = event.mouseMove.x;
        mouseY = event.mouseMove.y;
        //Center of the screen
        float xCenter = player.sprite.getPosition().x - camera.getCamera().getCenter().x;
        float yCenter = player.sprite.getPosition().y - camera.getCamera().getCenter().y;
        //Set the angle relative to the player
        mouseAngle = calculateMouseAngle(mouseX, mouseY, xCenter, yCenter);
    }
}
