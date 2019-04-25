#ifndef SCRIPT_H
#define SCRIPT_H

#include "Component.h"
#include "GameObject.h"

/**
 * A script is a basic class that provide an interface to the end user script
 */
class Script : public Component{
private:
    //the gameObject containing the script
    GameObject* _gameObject;
public:
    /**
     * Constructor
     */
    Script();

    /**
     * Setter for the gameObject
     */
    void setGameObject(GameObject* gameObject);

    /**
     * Getter for the gameObject
     */
    GameObject* getGameObject();

    /**
     * Return the exact script name
     */
    virtual std::string getScriptName();

    /**
     * Override of the start method of the component
     * can be used to initialize the variable of the script
     */
    virtual void Start();

    /**
     * Override of the onNewFrame method of the component
     */
    virtual void OnNewFrame();
};

#endif
