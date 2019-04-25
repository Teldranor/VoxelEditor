#include "Material.h"

Material::Material(){}

void Material::setAmbient(float r, float g, float b){
    _ambient = glm::vec3(r, g, b);
}

glm::vec3 Material::getAmbient(){
    return _ambient;
}

void Material::setDiffuse(float r, float g, float b){
    _diffuse = glm::vec3(r, g, b);
}

glm::vec3 Material::getDiffuse(){
    return _diffuse;
}

void Material::setSpecular(float r, float g, float b){
    _specular = glm::vec3(r, g, b);
}

glm::vec3 Material::getSpecular(){
    return _specular;
}

void Material::setShininess(float shininess){
    _shininess = shininess;
}

float Material::getShininess(){
    return _shininess;
}

void Material::setAlpha(float alpha){
    _alpha = alpha;
}

float Material::getAlpha(){
    return _alpha;
}
