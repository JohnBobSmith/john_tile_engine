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
    respawnText.setOutlineThickness(2);
    respawnText.setOutlineColor(sf::Color::Black);
    
    ammoCounterText.setFont(squarefont);
    ammoCounterText.setCharacterSize(20);
    ammoCounterText.setString("NULL"); //Error string
    ammoCounterText.setOutlineThickness(2);
    ammoCounterText.setOutlineColor(sf::Color::Black);
    
    maxAmmoCounterText.setFont(squarefont);
    maxAmmoCounterText.setCharacterSize(15);
    maxAmmoCounterText.setString("NULL"); //Error string
    maxAmmoCounterText.setOutlineThickness(2);
    maxAmmoCounterText.setOutlineColor(sf::Color::Black);

	hpBarText.setFont(squarefont);
	hpBarText.setCharacterSize(20);
	hpBarText.setString("HP:");
	hpBarText.setOutlineThickness(2);
	hpBarText.setOutlineColor(sf::Color::Black);
	
    return true;
}

void Font::update(Weapon &weapon)
{
	ammoCounterText.setString(std::to_string(weapon.ammoInMagazine));
	maxAmmoCounterText.setString("/" + std::to_string(weapon.maxAmmo)); 
}

