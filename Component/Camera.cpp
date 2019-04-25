#include "Camera.h"

Camera::Camera(){
    _main = false;
}

void Camera::setGameObject(GameObject* gameObject){
    _gameObject = gameObject;
}

GameObject* Camera::getGameObject(){
    return _gameObject;
}

void Camera::setMain(bool main){
    _main = main;
}

bool Camera::isMain(){
    return _main;
}

glm::mat4 Camera::getView(){
    glm::vec3 bindingPos = glm::vec3();
    glm::vec3 bindingRot = glm::vec3();
    if(getGameObject() != NULL){
        bindingPos = getGameObject()->getWorldPosition();
        bindingRot = getGameObject()->getWorldRotation();
    }

    //calcul of the translation matrix to get position
    glm::mat4 translate = glm::mat4();
    translate = glm::translate(translate, bindingPos);

    //calcul of the rotation matrix to get direction
    glm::mat4 rotate = glm::mat4();
    rotate = glm::rotate(rotate, bindingRot.x, glm::vec3(1.0f, 0.0f, 0.0f));
    rotate = glm::rotate(rotate, bindingRot.y, glm::vec3(0.0f, 1.0f, 0.0f));
    rotate = glm::rotate(rotate, bindingRot.z, glm::vec3(0.0f, 0.0f, 1.0f));

    //translate the camera from origin to its actual position
    glm::vec4 cameraPos4 = translate * glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
    //calcul the front direction based on gameObject rotation (front is basically Z axis)
    glm::vec4 cameraFront4 = rotate * glm::vec4(glm::vec3(0.0f, 0.0f, 1.0f), 0.0f);
    //calculate the un direction based on gameObject rotation (up is basically Y axis)
    glm::vec4 cameraUp4 = rotate * glm::vec4(glm::vec3(0.0f, 1.0f, 0.0f), 0.0f);

    glm::vec3 cameraPos = glm::vec3(cameraPos4.x, cameraPos4.y, cameraPos4.z);
    glm::vec3 cameraFront = glm::vec3(cameraFront4.x, cameraFront4.y, cameraFront4.z);
    glm::vec3 cameraUp = glm::vec3(cameraUp4.x, cameraUp4.y, cameraUp4.z);

    //calculate the view matrix from camera pos, camera front and camera up
    return glm::lookAt(cameraPos, (cameraPos + cameraFront), cameraUp);
}
