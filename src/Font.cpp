#include "Font.h"
#include <iostream>

bool Font::load()
{
    if (!squarefont.loadFromFile("fonts/Square.ttf")) {
        std::cerr << "ERROR: Missing font file!\n";
        return false;
    }
    respawnText.setFont(squarefont);
    respawnText.setCharacterSize(24);
    respawnText.setString("Respawning...");

    return true;
}
