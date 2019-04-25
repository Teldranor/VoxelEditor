#ifndef DIRECTIONAL_LIGHT_H
#define DIRECTIONAL_LIGHT_H

#include "libG.h"
#include "ShaderManager.h"
#include "Component.h"

/**
 * A directionnal light is a model of light that can be compared to a sun, the light is supposedly far away so only its direction matter
 */
class DirectionalLight : public Component{

private:
    //light attributes
    //the global direction from light the light come
    glm::vec3 _direction;

    //ambient light is the minimum of the light that should attain the object  so it's not completely dark
    glm::vec3 _ambient;
    //diffuse light is the directionnal impact of the light on a given object
    glm::vec3 _diffuse;
    //specular light is the shiny point that appear on an object. 
    glm::vec3 _specular;
public:
    /**
     * Constructor
     */
    DirectionalLight();

    /**
     * Override of the light method of the component
     * It will store light inside the shader
     */
    void light();

    /**
     * Setter for direcion of the light
     */
    void setDirection(float x, float y, float z);

    /**
     * Getter for the direction
     */
    glm::vec3 getDirection();

    /**
     * Setter for ambient component of light
     */
    void setAmbient(float r, float g, float b);

    /**
     * Getter for ambient component of light
     */
    glm::vec3 getAmbient();

    /**
     * Setter for the diffuse component of light
     */
    void setDiffuse(float r, float g, float b);

    /**
     * Getter for the diffuse component of light
     */
    glm::vec3 getDiffuse();

    /**
     * Setter for the specular component of light
     */
    void setSpecular(float r, float g, float b);

    /**
     * Getter for the specular component of dirLight
     */
    glm::vec3 getSpecular();
};

#endif
