#ifndef COMPONENT_H
#define COMPONENT_H

#include <iostream>

/**
 * A component is a abstract class that represent a gameObject Component
 */
class Component
{
private:

public:
    /**
     * Constructor
     */
    Component();

    /**
     * Start method is called when the component is instantiate
     */
    virtual void Start();

    /**
     * onNewFrame method is called once per frame
     */
    virtual void OnNewFrame();

    /**
     * light method calculate the lights of the scene if it's a light component
     */
    virtual void light();

    /**
     * render method render the component if it's a graphic component
     */
    virtual void render();
};

#endif
