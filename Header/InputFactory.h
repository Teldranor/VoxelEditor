#ifndef INPUT_FACTORY_H
#define INPUT_FACTORY_H

/**
 * The InputFactory is the factory used to instantate inputs
 * The InputFactory is a singleton
 */
#include "Input.h"

class InputFactory{

private:
    //singleton
    static InputFactory* _factory;

public:
    /**
     * Constructor
     */
    InputFactory();

    /**
     * Getter for the singleton
     */
    static InputFactory* getFactory();

    /**
     * Instantiate a input that will affect the keypad
     */
    InputKey* instantiateKeys();

    /**
     * Instantiate a input that will affect the mouse button
     */
    InputMouseButton* instantiateMouseButton();

    /**
     * Instantiate a input that will affect the mouse motion
     */
    InputMouseMotion* instantiateMouseMotion();
};

#endif
