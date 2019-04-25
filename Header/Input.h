#ifndef INPUT_H
#define INPUT_H

#include <map>

#include "libG.h"

/**
 * Basic Class for Input
 */
class Input
{
public:
    Input();
    virtual ~Input(){}
};

/**
 * Input for KeyBoard
 */
class InputKey : public Input{
private:
    //List of key used for this input
    std::map<int, int> _keys;
public:
    //State available for each key
    static const int KeyIdle = 0;
    static const int KeyPressed = 1;
    static const int KeyHeld = 2;
    static const int KeyRelease = 3;

    /**
     * Constructor
     */
    InputKey();

    /**
     * Add a key to the input
     */
    void addKey(int key);

    /**
     * Change the key state of a key
     */
    void changeKeyState(int key, int sdl_state);

    /**
     * Relesase all keys
     */
    void releaseKeys();

    /**
     * Get the state of one key
     */
    int getKeyState(int key);
};

/**
 * Input for Mouse Button
 */
class InputMouseButton : public Input{
private:
    //mouse button
    int _buttonLeft;
    int _buttonMiddle;
    int _buttonRight;
public:
    /**
     * Constructor
     */
    InputMouseButton();

    /**
     * Add a click to a button for the last fram
     * sdl_button : button to add a key to
     * clicks : number of click to add
     */
    void addButtonClick(int sdl_button, int clicks);

    /**
     * Reset all the buttons
     */
    void resetButton();

    /**
     * Get the number of clicks on a button for the last frame
     */
    int getButton(int sdl_button);
};

/**
 * Input for Mouse Motion
 * Normal Mode of mouse indicate a mouse clamped inside the main window
 * Relative Mode allow for unlimited movement without being clamped inside a window
 */
class InputMouseMotion : public Input{
private:
    //position of the mouse
    int _last_x;
    int _last_y;
    //change of position from last frame
    int _offset_x;
    int _offset_y;
    //change of position when relative mode is active
    int _x_rel;
    int _y_rel;
public:
    /**
     * Constructor
     */
    InputMouseMotion();

    /**
     * Move the mouse to the x/y position
     */
    void moveMouse(int x, int y);

    /**
     * indicate the movmenent of the mouse in relative move
     */
    void moveMouseRel(int x, int y);

    /**
     * reset the offset in normal mode for the last frame
     */
    void resetOffset();

    /**
     * reset the relative movmeent of the move for the last frame
     */
    void resetRel();

    /**
     * Getter for X position of the mouse
     */
    int getPosX();

    /**
     * Getter for the Y position of the mouse
     */
    int getPosY();

    /**
     * Getter for the X offset the last frame
     */
    int getOffsetX();

    /**
     * Getter for the Y offset fo the last frame
     */
    int getOffsetY();

    /**
     * Getter for the relative X position of the last frame
     */
    int getRelX();

    /**
     * Getter for the relative Y position of the last fram
     */
    int getRelY();
};

#endif
