#ifndef SOUNDMANAGER_H
#define SOUNDMANAGER_H

#include <SFML/Audio.hpp>
#include <string>
#include <memory>

class SoundManager
{
    public:
        struct jteSound
        {
            sf::Sound snd;
            sf::SoundBuffer sndBuffer;
            std::string name;
        };

        //Load a new sound from path and store it in audio bank bnk.
        //Banks are simply std::vectors of type jteSound.
        void registerNewSound(std::vector<std::shared_ptr<jteSound>> &bnk,
                                    std::string path, std::string sndName);

        //Footsteps bank
        std::vector<std::shared_ptr<jteSound>> bnkFootsteps;

        //Play a random footstep sound
        /*
            0-2 is grass
            3-5 is shrubs/crops
            6-8 is gravel
        */
        void playFootsteps(int randomNumber);

    private:
        //How long to delay before playing the next footstep sound
        float footstepDelay = 35.0f;
};

#endif // SOUNDMANAGER_H
