#include "Script.h"

Script::Script(){}

void Script::setGameObject(GameObject* gameObject){
    _gameObject = gameObject;
}

GameObject* Script::getGameObject(){
    return _gameObject;
}

std::string Script::getScriptName(){
    return "Script";
}

void Script::Start(){}

void Script::OnNewFrame(){}
