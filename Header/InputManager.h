#ifndef INPUT_MANAGER_H
#define INPUT_MANAGER_H

#include <map>

#include "libG.h"
#include "Input.h"
#include "InputFactory.h"

/**
 * This class manageed the inputs for the program
 * This class is a singleton
 */
class InputManager{

private:
    //Singleton
    static InputManager* _inputManager;

    //List of all inputs
    std::map<std::string, Input*> _inputs;

    //the current mode of the mouse
    bool _mouseMode;

public:
    /**
     * Constructor
     */
    InputManager();

    /**
     * Getter for the singleton
     */
    static InputManager* getInputManager();

    /**
     * Add an nput to the manager
     */
    void addInput(std::string name, Input* input);

    /**
     * Getter for an input with a definite name
     */
    Input* getInput(std::string name);

    /**
     * Allow the user to change the mouse mode between normal and relative
     * true for relative mode
     * false for normal mode
     */
    void changeMouseMode(bool relativeMode);

    /**
     * Getter for the mouse mode
     */
    bool getMouseMode();

    /**
     * Function called each frame to actualize the current value of the inputs
     */
    void processInput();
};

#endif
