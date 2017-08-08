#include "include/SoundManager.h"
#include <memory>

void SoundManager::registerNewSound(std::vector<std::shared_ptr<jteSound>> &bnk, std::string path)
{
    //Initialize our sounds attributes.
    static int counter = 0;
    //Reset for a new bank.
    if (bnk.size() == 0) {
        counter = 0;
    }
    //Populate our sound bank.
    for (int i = counter; counter < i + 1; counter++) {
        bnk.push_back(std::make_shared<jteSound>());
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

void SoundManager::playRespawnSound()
{
    bnkSpawnEffects[0]->snd.play();
}

void SoundManager::playDeathSound()
{
    bnkSpawnEffects[1]->snd.play();
}

void SoundManager::playLmgFire()
{
   bnkWeaponEffects[0]->snd.play();
}





