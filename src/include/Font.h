#ifndef FONT_H
#define FONT_H

#include <SFML/Graphics.hpp>
#include "Weapon.h"

class Font
{
    public:
        //Our texts
        sf::Text respawnText;
        sf::Text ammoCounterText;
        sf::Text maxAmmoCounterText;
        sf::Text hpBarText;

        //Load our fonts.
        bool load();
        
       	//Update everything
       	void update(Weapon &weapon);

    private:
        //Our fonts
        sf::Font squarefont;
};

#endif // FONT_H
