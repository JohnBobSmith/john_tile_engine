#include "SoundManager.h"
#include <memory>

void SoundManager::registerNewSound(std::vector<std::shared_ptr<jteSound>> &bnk,
                                            std::string path, std::string sndName)
{
    static int counter = 0;
    for (int i = counter; counter <i+1; counter++) {
        bnk.push_back(std::make_shared<jteSound>());
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
