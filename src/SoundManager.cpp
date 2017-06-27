#include "SoundManager.h"
#include <stdlib.h>

SoundManager::~SoundManager()
{
    //Cleanup each sound bank that we use.
    for (std::vector<jteSound*>::iterator it = bnkFootsteps.begin(); it != bnkFootsteps.end(); ++it) {
        delete *it;
    }
}

void SoundManager::registerNewSound(std::vector<jteSound*> &bnk, std::string path, std::string sndName)
{
    //Keep track of how many times this funciton is called,
    //for bounds checking purposes.
    static int counter = 0;
    for (int i = counter; counter <i+1; counter++) {
        bnk.push_back(new jteSound);
        bnk[i]->name = sndName;
        bnk[i]->sndBuffer.loadFromFile(path);
        bnk[i]->snd.setBuffer(bnk[i]->sndBuffer);
    }
}

void SoundManager::playFootsteps(int randomNumber)
{
    static int timer = footstepDelay;
    timer -= 0.01f;
    if (timer == 0) {
        bnkFootsteps[randomNumber]->snd.play();
        timer = footstepDelay;
    }
}
