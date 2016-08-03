#include "Camera.h"
#include "Player.h"

Camera::Camera()
{
    //Player object
    Player player;

    camera.setSize(sf::Vector2f(200, 200));

    //Always center our camera on the player,
    //by default for now.

    camera.setCenter(player.getPlayerPosition().x, player.getPlayerPosition().y);
}
