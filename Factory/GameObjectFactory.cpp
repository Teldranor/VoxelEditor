#include "GameObjectFactory.h"

GameObjectFactory* GameObjectFactory::_factory = 0;

GameObjectFactory::GameObjectFactory(){}

GameObjectFactory* GameObjectFactory::getFactory(){
    if(!(_factory)){
        _factory = new GameObjectFactory();
    }
    return _factory;
}

GameObject* GameObjectFactory::instantiate(std::string tag, std::string name){
    return new GameObject(tag, name);
}
