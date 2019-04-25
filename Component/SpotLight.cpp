#include "SpotLight.h"

SpotLight::SpotLight(){
    //default spot light
    _id = "-1";

    _direction = glm::vec3(0.0, -1.0, 0.0);

    _cutOff = glm::cos(glm::radians(12.5f));
    _outerCutOff = glm::cos(glm::radians(15.0f));

    _ambient = glm::vec3(1.0, 1.0, 1.0);
    _diffuse = glm::vec3(1.0, 1.0, 1.0);
    _specular = glm::vec3(1.0, 1.0, 1.0);

    _constant = 1.0f;
    _linear = 0.09f;
    _quadratic = 0.032f;
}

void SpotLight::setGameObject(GameObject* gameObject){
    _gameObject = gameObject;
}

GameObject* SpotLight::getGameObject(){
    return _gameObject;
}

void SpotLight::light(){

    ShaderManager* shaderManager = ShaderManager::getShaderManager();

    //store the spot light if it's id is not the default id
    if(_id != "-1"){
        shaderManager->setUniformVec3Float("spotLights["+_id+"].position", getGameObject()->getWorldPosition());
        shaderManager->setUniformVec3Float("spotLights["+_id+"].direction", _direction);
        shaderManager->setUniformFloat("spotLights["+_id+"].cutOff", _cutOff);
        shaderManager->setUniformFloat("spotLights["+_id+"].outerCutOff", _outerCutOff);
        shaderManager->setUniformVec3Float("spotLights["+_id+"].ambient", _ambient);
        shaderManager->setUniformVec3Float("spotLights["+_id+"].diffuse", _diffuse);
        shaderManager->setUniformVec3Float("spotLights["+_id+"].specular", _specular);
        shaderManager->setUniformFloat("spotLights["+_id+"].constant", _constant);
        shaderManager->setUniformFloat("spotLights["+_id+"].linear", _linear);
        shaderManager->setUniformFloat("spotLights["+_id+"].quadratic", _quadratic);
    }
}

void SpotLight::setId(std::string id){
    _id = id;
}

std::string SpotLight::getId(){
    return _id;
}

void SpotLight::setDirection(float x, float y, float z){
    _direction = glm::vec3(x,y,z);
}

glm::vec3 SpotLight::getDirection(){
    return _direction;
}

void SpotLight::setCutOff(float cutOff){
    _cutOff = cutOff;
}

float SpotLight::getCutOff(){
    return _cutOff;
}

void SpotLight::setOuterCutOff(float outerCuttOff){
    _outerCutOff = outerCuttOff;
}

float SpotLight::getOuterCutOff(){
    return _outerCutOff;
}

void SpotLight::setAmbient(float r, float g, float b){
    _ambient = glm::vec3(r,g,b);
}

glm::vec3 SpotLight::getAmbient(){
    return _ambient;
}

void SpotLight::setDiffuse(float r, float g, float b){
    _diffuse = glm::vec3(r,g,b);
}

glm::vec3 SpotLight::getDiffuse(){
    return _diffuse;
}

void SpotLight::setSpecular(float r, float g, float b){
    _specular = glm::vec3(r,g,b);
}

glm::vec3 SpotLight::getSpecular(){
    return _specular;
}

void SpotLight::setConstant(float constant){
    _constant = constant;
}

float SpotLight::getConstant(){
    return _constant;
}

void SpotLight::setLinear(float linear){
    _linear = linear;
}

float SpotLight::getLinear(){
    return _linear;
}

void SpotLight::setQuadratic(float quadratic){
    _quadratic = quadratic;
}

float SpotLight::getQuadratic(){
    return _quadratic;
}
