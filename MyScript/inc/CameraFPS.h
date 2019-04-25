#ifndef CAMERA_FPS_H
#define CAMERA_FPS_H

#include "Script.h"
#include "GameObject.h"
#include "Camera.h"
#include "InputManager.h"
#include "Input.h"

class CameraFPS : public Script{

public:
    CameraFPS();

    std::string getScriptName();

    void Start();

    void OnNewFrame();
};

#endif
