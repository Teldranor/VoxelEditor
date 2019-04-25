#include "CameraFPS.h"

CameraFPS::CameraFPS(){}

std::string CameraFPS::getScriptName(){
    return "CameraFPS";
}

void CameraFPS::Start(){}

void CameraFPS::OnNewFrame(){

    float speed = 0.1f;
    float mouseSensibility = 0.01f;

    InputManager* manager = InputManager::getInputManager();

    if(manager->getMouseMode()){
        Input* inputMovement = manager->getInput("movement");

        if(inputMovement){
            GameObject* gameObject = getGameObject();
            InputKey* movement = dynamic_cast<InputKey*>(inputMovement);

            int forward_movement = 0;
            int up_movement = 0;
            int side_movement = 0;

            if(movement->getKeyState(SDLK_z) == InputKey::KeyHeld || movement->getKeyState(SDLK_z) == InputKey::KeyPressed){
                forward_movement++;
            }
            if(movement->getKeyState(SDLK_s) == InputKey::KeyHeld || movement->getKeyState(SDLK_s) == InputKey::KeyPressed){
                forward_movement--;
            }
            if(movement->getKeyState(SDLK_a) == InputKey::KeyHeld || movement->getKeyState(SDLK_a) == InputKey::KeyPressed){
                up_movement++;
            }
            if(movement->getKeyState(SDLK_w) == InputKey::KeyHeld || movement->getKeyState(SDLK_w) == InputKey::KeyPressed){
                up_movement--;
            }
            if(movement->getKeyState(SDLK_q) == InputKey::KeyHeld || movement->getKeyState(SDLK_q) == InputKey::KeyPressed){
                side_movement++;
            }
            if(movement->getKeyState(SDLK_d) == InputKey::KeyHeld || movement->getKeyState(SDLK_d) == InputKey::KeyPressed){
                side_movement--;
            }

            glm::vec3 deltaDir = glm::vec3(side_movement, up_movement, forward_movement);
            if(deltaDir.x != 0 || deltaDir.y != 0 || deltaDir.z != 0)
            deltaDir = glm::normalize(deltaDir);

            gameObject->translate(deltaDir, speed);
        }

        Input* inputMouseMotion = manager->getInput("mouseMotion");

        if(inputMouseMotion){

            InputMouseMotion* mouseMotion = dynamic_cast<InputMouseMotion*>(inputMouseMotion);

            GameObject* gameObject = getGameObject();

            gameObject->rotate(glm::vec3(0.0f, 1.0f, 0.0f), mouseSensibility*mouseMotion->getRelX());
        }
    }
}
