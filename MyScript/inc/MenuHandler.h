#ifndef MENU_HANDLER_H
#define MENU_HANDLER_H

#include "Script.h"
#include "InputManager.h"
#include "Input.h"

class MenuHandler : public Script{

public:
    MenuHandler();

    std::string getScriptName();

    void Start();

    void OnNewFrame();
};

#endif
