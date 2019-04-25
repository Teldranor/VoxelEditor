#include "PointLight.h"

PointLight::PointLight(){
    //default point light
    _id = "-1";

    _ambient = glm::vec3(1.0, 1.0, 1.0);
    _diffuse = glm::vec3(1.0, 1.0, 1.0);
    _specular = glm::vec3(1.0, 1.0, 1.0);

    _constant = 1.0f;
    _linear = 0.09f;
    _quadratic = 0.032f;
}

void PointLight::setGameObject(GameObject* gameObject){
    _gameObject = gameObject;
}

GameObject* PointLight::getGameObject(){
    return _gameObject;
}

void PointLight::light(){

    ShaderManager* shaderManager = ShaderManager::getShaderManager();

    //store the point light if it's id is not the default id
    if(_id != "-1"){
        shaderManager->setUniformVec3Float("pointLights["+_id+"].position", getGameObject()->getWorldPosition());
        shaderManager->setUniformVec3Float("pointLights["+_id+"].ambient", _ambient);
        shaderManager->setUniformVec3Float("pointLights["+_id+"].diffuse", _diffuse);
        shaderManager->setUniformVec3Float("pointLights["+_id+"].specular", _specular);
        shaderManager->setUniformFloat("pointLights["+_id+"].constant", _constant);
        shaderManager->setUniformFloat("pointLights["+_id+"].linear", _linear);
        shaderManager->setUniformFloat("pointLights["+_id+"].quadratic", _quadratic);
    }
}

void PointLight::setId(std::string id){
    _id = id;
}

std::string PointLight::getId(){
    return _id;
}

void PointLight::setAmbient(float r, float g, float b){
    _ambient = glm::vec3(r,g,b);
}

glm::vec3 PointLight::getAmbient(){
    return _ambient;
}

void PointLight::setDiffuse(float r, float g, float b){
    _diffuse = glm::vec3(r,g,b);
}

glm::vec3 PointLight::getDiffuse(){
    return _diffuse;
}

void PointLight::setSpecular(float r, float g, float b){
    _specular = glm::vec3(r,g,b);
}

glm::vec3 PointLight::getSpecular(){
    return _specular;
}

void PointLight::setConstant(float constant){
    _constant = constant;
}

float PointLight::getConstant(){
    return _constant;
}

void PointLight::setLinear(float linear){
    _linear = linear;
}

float PointLight::getLinear(){
    return _linear;
}

void PointLight::setQuadratic(float quadratic){
    _quadratic = quadratic;
}

float PointLight::getQuadratic(){
    return _quadratic;
}
