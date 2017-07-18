#include "../include/Player.h"
#include "../include/Camera.h"
#include "../include/Collision.h"
#include <string>
#include <iostream>

Player::Player()
{
    //Initialize our base values
    keyCounter = 0;
    isActive = true;
    isWalking = false;
    position.x = 32;
    position.y = 32;
    velocity.x = 0;
    velocity.y = 0;
    maxVelocity = 1;
    size.x = 22;
    size.y = 22;
    health = 100.0f;
    boundingBox.setSize(sf::Vector2f(size.x, size.y));
    boundingBox.setFillColor(sf::Color::White);

    //Setup our spawn points.
    for (int i = 0; i < MAX_SPAWN_POINTS; ++i) {
        spawnPoints.push_back(sf::Vector2f(0, 0));
    }
    spawnPoints[0].x = 50;
    spawnPoints[0].y = 50;
    spawnPoints[1].x = 230;
    spawnPoints[1].y = -460;
    spawnPoints[2].x = 774;
    spawnPoints[2].y = -284;
    spawnPoints[3].x = 945;
    spawnPoints[3].y = -50;
    spawnPoints[4].x = 870;
    spawnPoints[4].y = 280;
    spawnPoints[5].x = 776;
    spawnPoints[5].y = 320;
    spawnPoints[6].x = 175;
    spawnPoints[6].y = 400;
    spawnPoints[7].x = 328;
    spawnPoints[7].y = -99;
    spawnPoints[8].x = 517;
    spawnPoints[8].y = 5;
    spawnPoints[9].x = 867;
    spawnPoints[9].y = -441;

    //Initialize our leg sprite.
    legs.setTextureRect(sf::IntRect(0, 0, 22, 32));
    legs.setOrigin(11, 22);
}

bool Player::loadTexture()
{
    //If we cannot load the texture, error out.
    if (!bodyTexture.loadFromFile("textures/entity/player.anim.png")) {
        std::cerr << "Error: Missing required texture file...";
        return false;
    }

    if (!legsTexture.loadFromFile("textures/entity/player.anim.legs.png")) {
        std::cerr << "Error: Missing required texture file...";
        return false;
    }

    body.setTexture(bodyTexture);
    legs.setTexture(legsTexture);

    return true;
}

bool Player::loadAudio()
{
    //Our respawn sound
    if(!respawnSoundBuffer.loadFromFile("audio/effects/respawn.wav")) {
        std::cerr << "ERROR: Missing sound file...\n";
        return false;
    }
    respawnSound.setBuffer(respawnSoundBuffer);

    //Our death sound
    if(!deathSoundBuffer.loadFromFile("audio/effects/death.wav")){
        std::cerr << "ERROR: Missing sound file...\n";
        return false;
    }
    deathSound.setBuffer(deathSoundBuffer);

    return true;
}

void Player::movePlayer()
{
    position.x = velocity.x;
    position.y = velocity.y;
    boundingBox.move(position);
    body.setPosition(boundingBox.getPosition().x + 11, boundingBox.getPosition().y + 11);
}

void Player::handlePlayerEvents(sf::Event event)
{
    //If key is pressed...
    if (event.type == sf::Event::KeyPressed) {
        //...Look for the keycode, and then...
        if (event.key.code == sf::Keyboard::W) {
            //...Do stuff
            velocity.y -= maxVelocity;
            keyCounter += 1;
            isWalking = true;
        }
        if (event.key.code == sf::Keyboard::S) {
            velocity.y += maxVelocity;
            keyCounter += 1;
            isWalking = true;
        }
        if (event.key.code == sf::Keyboard::A) {
            velocity.x -= maxVelocity;
            keyCounter += 1;
            isWalking = true;
        }
        if (event.key.code == sf::Keyboard::D) {
            velocity.x += maxVelocity;
            keyCounter += 1;
            isWalking = true;
        }
    }
    //Stop moving when we release the key
    if (event.type == sf::Event::KeyReleased) {
        if (keyCounter == 1) {
            isWalking = false;
        }
        //Reset our texture rect when we stop walking
        body.setTextureRect(sf::IntRect(0, 0, 22, 32));
        if (event.key.code == sf::Keyboard::W) {
            velocity.y += maxVelocity;
            keyCounter -= 1;
        }
        if (event.key.code == sf::Keyboard::S) {
            velocity.y -= maxVelocity;
            keyCounter -= 1;
        }
        if (event.key.code == sf::Keyboard::A) {
            velocity.x += maxVelocity;
            keyCounter -= 1;
        }
        if (event.key.code == sf::Keyboard::D) {
            velocity.x -= maxVelocity;
            keyCounter -= 1;
        }
    }
}

void Player::animate()
{
    static int counter = 0;
    static float timer = 5.0f;
    if (isWalking) {
        timer -= 1.0f;
        if (timer == 0.0f) {
            //Cycle through our body sheet
            legs.setTextureRect(sf::IntRect(counter, 0, 22, 32));
            timer = 5.0f;
        }
        counter += 22; //22 is the width of one sprite on the sheet
        //If we reached the end of the sheet, reset.
        if (counter == 88) {
            counter = 0;
        }
    }
}

bool Player::checkCollision(Collision &collision, Camera &camera)
{
    //If there is a collision, move the player back.
    for (int i = 0; i < collision.MAX_COLLISION_BOXES; ++i) {
        if (collision.checkAABBcollision(boundingBox.getPosition().x,
                                         boundingBox.getPosition().y,
                                         size.x, size.y, //Players size
                                         collision.collVector[i]->bbox.getPosition().x,
                                         collision.collVector[i]->bbox.getPosition().y,
                                         collision.collVector[i]->bbox.getSize().x,
                                         collision.collVector[i]->bbox.getSize().y)) {

            collision.collVector[i]->isTouching = true;
            if (position.x == -1) {
                boundingBox.move(1, 0);
            }
            if (position.x == 1) {
                boundingBox.move(-1, 0);
            }
            if (position.y == 1) {
                boundingBox.move(0, -1);
            }
            if (position.y == -1) {
                boundingBox.move(0, 1);
            }
            //Update the camera
            camera.setCamCenter(sf::Vector2f(boundingBox.getPosition().x,
                                           boundingBox.getPosition().y));

            //Collided
            return true;
        } else {
            //Reset isTouching
            collision.collVector[i]->isTouching = false;
        }
    }
    //Did not collide
    return false;
}

bool Player::checkAudioCollsion(Collision &collision)
{
    for (int i = 0; i < collision.MAX_COLLISION_BOXES; ++i) {
        if (collision.checkAABBcollision(boundingBox.getPosition().x,
                                         boundingBox.getPosition().y,
                                         size.x, size.y, //Players size
                                         collision.collVector[i]->bbox.getPosition().x,
                                         collision.collVector[i]->bbox.getPosition().y,
                                         collision.collVector[i]->bbox.getSize().x,
                                         collision.collVector[i]->bbox.getSize().y)) {
            //Collided
            return true;
        }
    }
    //Did not collide
    return false;
}

void Player::applyDamage(int ammount)
{
    health -= ammount;
    if (health <= 0) {
        killPlayer();
    }
}

void Player::killPlayer()
{
    deathSound.play();

    health = -999;
    isActive = false;
}

void Player::respawn(Camera &camera, int randomNumber)
{
    respawnSound.play();

    health = 100;
    isActive = true;

    //Randomly spawn the player, then update the camera.
    boundingBox.setPosition(spawnPoints[randomNumber]);
    camera.setCamCenter(sf::Vector2f(boundingBox.getPosition().x, boundingBox.getPosition().y));
}
