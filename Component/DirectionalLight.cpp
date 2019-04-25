#include "DirectionalLight.h"

DirectionalLight::DirectionalLight(){
    //default directional light
    _direction = glm::vec3(-0.2, -1.0, -0.3);

    _ambient = glm::vec3(0.05, 0.05, 0.05);
    _diffuse = glm::vec3(0.4, 0.4, 0.4);
    _specular = glm::vec3(0.5, 0.5, 0.5);
}

void DirectionalLight::light(){
    //store the directional light in all shaders
    ShaderManager* shaderManager = ShaderManager::getShaderManager();

    shaderManager->setUniformVec3Float("dirLight.direction", _direction);
    shaderManager->setUniformVec3Float("dirLight.ambient", _ambient);
    shaderManager->setUniformVec3Float("dirLight.diffuse", _diffuse);
    shaderManager->setUniformVec3Float("dirLight.specular", _specular);
}

void DirectionalLight::setDirection(float x, float y, float z){
    _direction = glm::vec3(x,y,z);
}

glm::vec3 DirectionalLight::getDirection(){
    return _direction;
}

void DirectionalLight::setAmbient(float r, float g, float b){
    _ambient = glm::vec3(r,g,b);
}

glm::vec3 DirectionalLight::getAmbient(){
    return _ambient;
}

void DirectionalLight::setDiffuse(float r, float g, float b){
    _diffuse = glm::vec3(r,g,b);
}

glm::vec3 DirectionalLight::getDiffuse(){
    return _diffuse;
}

void DirectionalLight::setSpecular(float r, float g, float b){
    _specular = glm::vec3(r,g,b);
}

glm::vec3 DirectionalLight::getSpecular(){
    return _specular;
}
