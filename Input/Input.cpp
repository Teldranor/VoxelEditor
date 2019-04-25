#include "Input.h"

Input::Input(){}

InputKey::InputKey(){}

void InputKey::addKey(int key){
    _keys[key] = InputKey::KeyIdle;
}

void InputKey::changeKeyState(int key, int sdl_state){
    //check if is inside the current key input
    if(_keys.count(key) != 1){
        return;
    }

    //depending of the state send by sdl we changed the state of the key
    switch(sdl_state){
        case SDL_KEYDOWN:
        if (_keys[key] == InputKey::KeyIdle){
            _keys[key] = InputKey::KeyPressed;
        }
        else if(_keys[key] == InputKey::KeyPressed){
            _keys[key] = InputKey::KeyHeld;
        }
        break;

        case SDL_KEYUP:
        _keys[key] = InputKey::KeyRelease;
        break;

        default:break;
    }
}

void InputKey::releaseKeys(){
    for (std::map<int, int>::iterator it = _keys.begin(); it != _keys.end(); ++it)
    {
        if(it->second == InputKey::KeyRelease){
            it->second = InputKey::KeyIdle;
        }
    }
}

int InputKey::getKeyState(int key){
    //check if the key is inside the current key input
    if(_keys.count(key) == 1){
        return _keys[key];
    }
    return -1;
}

InputMouseButton::InputMouseButton(){}

void InputMouseButton::addButtonClick(int sdl_button, int clicks){
    switch (sdl_button) {
        case SDL_BUTTON_LEFT:
        _buttonLeft += clicks;
        break;
        case SDL_BUTTON_RIGHT:
        _buttonRight += clicks;
        break;
        case SDL_BUTTON_MIDDLE:
        _buttonMiddle += clicks;
        break;
        default:
        break;
    }
}

void InputMouseButton::resetButton(){
    _buttonLeft = 0;
    _buttonRight = 0;
    _buttonMiddle = 0;
}

int InputMouseButton::getButton(int sdl_button){
    switch (sdl_button) {
        case SDL_BUTTON_LEFT:
        return _buttonLeft;
        case SDL_BUTTON_RIGHT:
        return _buttonRight;
        case SDL_BUTTON_MIDDLE:
        return _buttonMiddle;
        default:
        return 0;
    }
}

InputMouseMotion::InputMouseMotion(){}

void InputMouseMotion::moveMouse(int x, int y){
    _offset_x = x - _last_x;
    _offset_y = y - _last_y;

    _last_x = x;
    _last_y = y;
}

void InputMouseMotion::moveMouseRel(int x, int y){
    //check the value (when changing mode a huge pseudo deplacement can be send by sql)
    if(x < 100 && x > -100)
    _x_rel = - x;
    if(y < 100 && y > -100)
    _y_rel = y;
}

void InputMouseMotion::resetOffset(){
    _offset_x = 0;
    _offset_y = 0;
}

void InputMouseMotion::resetRel(){
    _x_rel = 0;
    _y_rel = 0;
}

int InputMouseMotion::getPosX(){
    return _last_x;
}

int InputMouseMotion::getPosY(){
    return _last_y;
}

int InputMouseMotion::getOffsetX(){
    return _offset_x;
}

int InputMouseMotion::getOffsetY(){
    return _offset_y;
}

int InputMouseMotion::getRelX(){
    return _x_rel;
}

int InputMouseMotion::getRelY(){
    return _y_rel;
}
