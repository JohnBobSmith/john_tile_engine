#ifndef AUDIO_H
#define AUDIO_H

#include <SFML/Audio.hpp>
#include <string>

class Audio
{
    public:
        //Load all our buffers first to prevent segfaulting.
        sf::SoundBuffer testBuffer;

        //Load all of our sounds here
        sf::Sound test = loadNewSound("audio/test.wav", testBuffer);

    private:
        //Function for loading sounds, for use interally only!
        sf::Sound loadNewSound(std::string path, sf::SoundBuffer &buffer);
};

#endif // AUDIO_H
