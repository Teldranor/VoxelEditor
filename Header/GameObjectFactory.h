#ifndef GO_FACTORY_H
#define GO_FACTORY_H

#include "GameObject.h"

/**
 * The GameObjectFactory is the factory used to instantate gameObject
 * The GameObjectFactory is a singleton
 */
class GameObjectFactory{

private:
    //singleton
    static GameObjectFactory* _factory;

public:
    /**
     * Constructor
     */
    GameObjectFactory();

    /**
     * Getter for the singleton
     */
    static GameObjectFactory* getFactory();

    /**
     * Instantiate a new gameObject
     */
    GameObject* instantiate(std::string tag = "None", std::string name = "gameObject");
};

#endif
