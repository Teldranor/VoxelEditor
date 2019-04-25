#include "MenuHandler.h"

MenuHandler::MenuHandler():Script(){}

std::string MenuHandler::getScriptName(){
    return "MenuHandler";
}

void MenuHandler::Start(){}

void MenuHandler::OnNewFrame(){

    InputManager* manager = InputManager::getInputManager();

    Input* inputMenu = manager->getInput("menu");

    if(inputMenu){
        InputKey* menu = dynamic_cast<InputKey*>(inputMenu);

        if(menu->getKeyState(SDLK_ESCAPE) == InputKey::KeyRelease){
            manager->changeMouseMode(!manager->getMouseMode());
        }
    }
}
