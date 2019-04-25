#include "ShaderManager.h"

ShaderManager* ShaderManager::_shaderManager = 0;

ShaderManager::ShaderManager(){}

ShaderManager* ShaderManager::getShaderManager(){
    if(!(_shaderManager)){
        _shaderManager = new ShaderManager();
    }
    return _shaderManager;
}

void ShaderManager::addShader(std::string name, Shader* shader){
    _shaders[name] = shader;
}

Shader* ShaderManager::getShader(std::string name){
    if(_shaders.count(name) == 1){
        return _shaders[name];
    }
    return NULL;
}

void ShaderManager::setCurrentShader(std::string name){
    if(_shaders.count(name) == 1){
        _currentShader = name;
        getCurrentShader()->use();
    }
}

Shader* ShaderManager::getCurrentShader(){
    return getShader(_currentShader);
}

void ShaderManager::setUniformFloat(std::string name, float value){
    std::map<std::string, Shader*>::iterator it;
    for(it = _shaders.begin(); it != _shaders.end(); ++it){
        it->second->setUniformFloat(name, value);
    }
}

void ShaderManager::setUniformVec3Float(std::string name, glm::vec3 vec){
    std::map<std::string, Shader*>::iterator it;
    for(it = _shaders.begin(); it != _shaders.end(); ++it){
        it->second->setUniformVec3Float(name, vec);
    }
}

void ShaderManager::setUniformMatrix4Float(std::string name, glm::mat4 mat){
    std::map<std::string, Shader*>::iterator it;
    for(it = _shaders.begin(); it != _shaders.end(); ++it){
        it->second->setUniformMatrix4Float(name, mat);
    }
}
