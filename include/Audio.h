#ifndef AUDIO_H
#define AUDIO_H

#include <SFML/Audio.hpp>
#include <string>

class Audio
{
    public:
        //Load all our buffers first to prevent segfaulting.
        sf::SoundBuffer footsteps01Buffer;
        sf::SoundBuffer footsteps02Buffer;
        sf::SoundBuffer footsteps03Buffer;
        sf::SoundBuffer footsteps04Buffer;
        sf::SoundBuffer footsteps05Buffer;
        sf::SoundBuffer footsteps06Buffer;
        sf::SoundBuffer footsteps07Buffer;
        sf::SoundBuffer footsteps08Buffer;
        sf::SoundBuffer footsteps09Buffer;

        //Load all of our sounds here
        sf::Sound footsteps01 = loadNewSound("audio/footsteps01.wav", footsteps01Buffer);
        sf::Sound footsteps02 = loadNewSound("audio/footsteps02.wav", footsteps02Buffer);
        sf::Sound footsteps03 = loadNewSound("audio/footsteps03.wav", footsteps03Buffer);
        sf::Sound footsteps04 = loadNewSound("audio/footsteps04.wav", footsteps04Buffer);
        sf::Sound footsteps05 = loadNewSound("audio/footsteps05.wav", footsteps05Buffer);
        sf::Sound footsteps06 = loadNewSound("audio/footsteps06.wav", footsteps06Buffer);
        sf::Sound footsteps07 = loadNewSound("audio/footsteps07.wav", footsteps07Buffer);
        sf::Sound footsteps08 = loadNewSound("audio/footsteps08.wav", footsteps08Buffer);
        sf::Sound footsteps09 = loadNewSound("audio/footsteps09.wav", footsteps09Buffer);

        //Play our footsteps
        void playFootsteps();

    private:
        //Function for loading sounds, for use interally only!
        sf::Sound loadNewSound(std::string path, sf::SoundBuffer &buffer);
};

#endif // AUDIO_H
