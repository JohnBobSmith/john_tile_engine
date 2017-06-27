#ifndef SOUNDMANAGER_H
#define SOUNDMANAGER_H

/*
    Manage our sounds.

    BASIC IDEAS:
    The sound manager manages banks containing our sounds
    A bank simply stores our sound and gives each sound a string ID.
    A bank can have one sound, or many sounds.
    Sound banks are going to be a std::vector<jteSound*>
    jteSound is a struct containing:
        -sf::Sound
        -sf::SoundBuffer
        -std::string id
        -Any other paramaters that I may need in the future
    Then for each new sound, simply vector.push_back(new jteSound).

    sounds are prefixed snd, banks are bnk.
*/

#include <SFML/Audio.hpp>
#include <string>

class SoundManager
{
    public:
        ~SoundManager();

        struct jteSound
        {
            sf::Sound snd;
            sf::SoundBuffer sndBuffer;
            std::string name;
        };

        //Load a new sound from path and store it in audio bank bnk.
        //Banks are simply std::vectors of type jteSound.
        void registerNewSound(std::vector<jteSound*> &bnk, std::string path, std::string sndName);

        //Footsteps
        std::vector<jteSound*> bnkFootsteps;

        //Play a random footstep sound
        void playFootsteps(int randomNumber);

    private:
        //How long to delay before playing the next footstep sound
        float footstepDelay = 35.0f;
};

#endif // SOUNDMANAGER_H
