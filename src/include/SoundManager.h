#ifndef SOUNDMANAGER_H
#define SOUNDMANAGER_H

#include <SFML/Audio.hpp>
#include <memory>
#include <string>

class SoundManager
{
    public:
        //Store our sounds and sound buffers
        struct jteSound
        {
            sf::Sound snd;
            sf::SoundBuffer sndBuffer;
        };

        //Load a new sound from path and store it in audio bank bnk.
        //Banks are simply std::vectors of type jteSound.
        void registerNewSound(std::vector<std::shared_ptr<jteSound>> &bnk, std::string path);

        //Our sound banks
        std::vector<std::shared_ptr<jteSound>> bnkFootsteps;
        std::vector<std::shared_ptr<jteSound>> bnkSpawnEffects;


        //Play a random footstep sound
        /*
            0-2 is grass
            3-5 is shrubs/crops
            6-8 is gravel
        */
        void playFootsteps(int randomNumber);

        //Play our respawn/death sounds
        void playRespawnSound();
        void playDeathSound();

    private:
        //How long to delay before playing the next footstep sound
        float footstepDelay = 35.0f;
};

#endif // SOUNDMANAGER_H
