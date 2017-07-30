#ifndef FONT_H
#define FONT_H

#include <SFML/Graphics.hpp>

class Font
{
    public:
        //Our texts
        sf::Text respawnText;

        //Load our fonts.
        bool load();

    private:
        //Our fonts
        sf::Font squarefont;
};

#endif // FONT_H
