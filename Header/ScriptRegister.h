#ifndef SCRIPT_REGISTER_H
#define SCRIPT_REGISTER_H

#include <map>

#include "Script.h"

/**
 * The script register allow to register script by name and to instantiate them by name
 * The script register is a singleton
 */
class ScriptRegister{
    //type of script constructor
    typedef Script* (*Constructor)(void);

private:
    //singleton
    static ScriptRegister* _register;

    //list of all script registered
    std::map<std::string, Constructor> _constructors;
public:
    /**
     * Constructor
     */
    ScriptRegister();

    /**
     * Getter of the singleton
     */
    static ScriptRegister* getRegister();

    /**
     * Register a new script using createInstance generique method below
     */
    void registerScript(std::string scriptName, Constructor constructor);

    /**
     * Unregister a script
     */
    void unregisterScript(std::string scriptName);

    /**
     * Instantiate a new script with this name
     */
    Script* instantiateScript(std::string scriptName);
};

template<typename T>
Script* createInstance(){
    return new T;
}

#endif
