#ifndef FONT_H
#define FONT_H

#include <SFML/Graphics.hpp>

class Font
{
    public:
        sf::Text respawnText;

        bool load();

    private:
        sf::Font squarefont;
};

#endif // FONT_H
