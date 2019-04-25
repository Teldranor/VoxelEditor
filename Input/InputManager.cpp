#include "InputManager.h"
#include "WindowManager.h"
#include "App.h"

InputManager* InputManager::_inputManager = 0;

InputManager::InputManager(){
    changeMouseMode(false);
}

InputManager* InputManager::getInputManager(){
    if(!(_inputManager)){
        _inputManager = new InputManager();
    }
    return _inputManager;
}

void InputManager::addInput(std::string name, Input* input){
    _inputs[name] = input;
}

Input* InputManager::getInput(std::string name){
    if(_inputs.count(name) == 1){
        return _inputs[name];
    }
    return NULL;
}

void InputManager::changeMouseMode(bool relativeMode){
    if(relativeMode){
        SDL_SetRelativeMouseMode(SDL_TRUE);
        _mouseMode = true;
    }
    else{
        SDL_SetRelativeMouseMode(SDL_FALSE);
        _mouseMode = false;
    }
}

bool InputManager::getMouseMode(){
    return _mouseMode;
}

void InputManager::processInput(){
    SDL_Event event;

    InputFactory* factory = InputFactory::getFactory();
    WindowManager* wf = WindowManager::getWindowManager();

    //Release all inputs from the last frame
    for (std::map<std::string, Input*>::iterator it = _inputs.begin(); it != _inputs.end(); ++it)
    {
        InputKey* inputKey = dynamic_cast<InputKey*>(it->second);
        if(inputKey != NULL)
        inputKey->releaseKeys();
        InputMouseButton* inputMouseButton = dynamic_cast<InputMouseButton*>(it->second);
        if(inputMouseButton != NULL)
        inputMouseButton->resetButton();
        InputMouseMotion* inputMouseMotion = dynamic_cast<InputMouseMotion*>(it->second);
        if(inputMouseMotion != NULL){
            inputMouseMotion->resetOffset();
            inputMouseMotion->resetRel();
        }
    }

    //SDL_PollEvent will send all the events SDL detects for this frame
    while( SDL_PollEvent( &event ) ){
        //apply event of UI
        wf->event(&event);
        switch( event.type ){
            //if the event is SDL_QUIT we set the end of program to true to end it
            case SDL_QUIT:
            (App::getApp())->setEndOfProgram(true);
            break;
            //If the event come from the keyboard, we notify all the InputKey
            case SDL_KEYUP:
            case SDL_KEYDOWN:
            for (std::map<std::string, Input*>::iterator it = _inputs.begin(); it != _inputs.end(); ++it)
            {
                InputKey* input = dynamic_cast<InputKey*>(it->second);
                if(input != NULL)
                input->changeKeyState(event.key.keysym.sym, event.type);
            }
            break;
            //if the event is a click on the mouse, we notify all the InputMouseButton
            case SDL_MOUSEBUTTONDOWN:
            for (std::map<std::string, Input*>::iterator it = _inputs.begin(); it != _inputs.end(); ++it)
            {
                InputMouseButton* input = dynamic_cast<InputMouseButton*>(it->second);
                if(input != NULL)
                input->addButtonClick(event.button.button, event.button.clicks);
            }
            break;
            //if the event is a mouse motion, we notify all the InputMouseMotion
            case SDL_MOUSEMOTION:
            for (std::map<std::string, Input*>::iterator it = _inputs.begin(); it != _inputs.end(); ++it)
            {
                InputMouseMotion* input = dynamic_cast<InputMouseMotion*>(it->second);
                if(input != NULL){
                    input->moveMouse(event.motion.x, event.motion.y);
                    input->moveMouseRel(event.motion.xrel, event.motion.yrel);
                }
            }
            break;
            default:break;
        }
    }
}
