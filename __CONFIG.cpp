//see __CONFIG.h for additional configuration variables.
#include "__CONFIG.h"

sf::Color __CONFIG::setWindowClearColor(sf::Color color)
{
    WIN_CLEAR_COLOR = color;
    return WIN_CLEAR_COLOR;
}
