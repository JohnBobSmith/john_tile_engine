#include "../include/Audio.h"
#include <string>
#include <iostream>

sf::Sound Audio::loadNewSound(std::string path, sf::SoundBuffer &buffer)
{
    if (!buffer.loadFromFile(path)) {
        std::cerr << "Error: missing audio file " << path;
    }
    sf::Sound tempSound;
    tempSound.setBuffer(buffer);

    return tempSound;
}
