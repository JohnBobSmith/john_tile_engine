#include "../include/Font.h"
#include <iostream>

bool Font::load()
{
    if (!squarefont.loadFromFile("../fonts/Square.ttf")) {
        std::cerr << "ERROR: Missing font file!\n";
        return false;
    }
    respawnText.setFont(squarefont);
    respawnText.setCharacterSize(24);
    respawnText.setString("Respawning...");
    
    ammoCounterText.setFont(squarefont);
    ammoCounterText.setCharacterSize(20);
    ammoCounterText.setString("NULL"); //Error string
    
    maxAmmoCounterText.setFont(squarefont);
    maxAmmoCounterText.setCharacterSize(15);
    maxAmmoCounterText.setString("NULL"); //Error string

    return true;
}
