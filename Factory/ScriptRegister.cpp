#include "ScriptRegister.h"

ScriptRegister* ScriptRegister::_register = 0;

ScriptRegister::ScriptRegister(){}

ScriptRegister* ScriptRegister::getRegister(){
    if(!(_register)){
        _register = new ScriptRegister();
    }
    return _register;
}

void ScriptRegister::registerScript(std::string scriptName, Constructor constructor){
    if(_constructors.count(scriptName) == 0)
    _constructors[scriptName] = constructor;
}

void ScriptRegister::unregisterScript(std::string scriptName){
    std::map<std::string, Constructor>::iterator iter;
    for( iter = _constructors.begin(); iter != _constructors.end(); ++iter){
        if(iter->first == scriptName){
            _constructors.erase( iter );
        }
    }
}

Script* ScriptRegister::instantiateScript(std::string scriptName){
    if(_constructors.count(scriptName) == 1){
        return (_constructors[scriptName])();
    }
    else{
        return NULL;
    }
}
