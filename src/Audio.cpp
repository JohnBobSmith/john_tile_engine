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

void Audio::playFootsteps()
{
    static int footstepsNumber = 1;

    static float timer = 2.5f;
    timer -= 0.1;

    std::cerr << timer << "\n";

    if (timer <= 0) {
        switch (footstepsNumber)
        {
        case 1:
            footsteps01.play();
            break;
        case 2:
            footsteps02.play();
            break;
        case 3:
            footsteps03.play();
            break;
        }
        footstepsNumber += 1;
        if (footstepsNumber > 3) {
            footstepsNumber = 1;
        }
        timer = 2.5f;
    }
}
