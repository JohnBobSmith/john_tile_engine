#ifndef CAMERA_H
#define CAMERA_H

#include <SFML/Graphics.hpp>

class Camera
{
    public:
        Camera();

        //Grab our active camera
        sf::View getCamera () { return camera; }

        //Move camera
        void moveCam(float x, float y) {camera.move(x, y); }

        //Rotate camera
        void rotateCam(float angle) { camera.rotate(angle); }

        //Zoom camera
        void zoomCam(float ammount) { camera.zoom(ammount); }

    private:
        sf::View camera;
};

#endif // CAMERA_H
