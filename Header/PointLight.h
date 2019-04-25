#ifndef POINT_LIGHT_H
#define POINT_LIGHT_H

#include "libG.h"
#include "ShaderManager.h"

#include "GameObject.h"
#include "Component.h"

/**
 * A point light is a light that goes on every direction
 */
class PointLight : public Component{

private:
    //id inside shader
    std::string _id;

    //gameObject containing the light
    GameObject* _gameObject;

    //light attributes
    //ambient light is the minimum of the light that should attain the object  so it's not completely dark
    glm::vec3 _ambient;
    //diffuse light is the directionnal impact of the light on a given object
    glm::vec3 _diffuse;
    //specular light is the shiny point that appear on an object.
    glm::vec3 _specular;

    //constant is the attenuation use for object close to the light
    float _constant;
    //linear is the attenuation use for object at mi distance of the light
    float _linear;
    //quadratic is the attenuation use for object far from the light
    float _quadratic;
public:
    /**
     * Constructor
     */
    PointLight();

    /**
     * Setter for the gameObject
     */
    void setGameObject(GameObject* gameObject);

    /**
     * Getter for the gameObject
     */
    GameObject* getGameObject();

    /**
     * Override of the light method of the component
     * It will store light inside the shader
     */
    void light();

    /**
     * Setter for id
     */
    void setId(std::string id);

    /**
     * Getter for id
     */
    std::string getId();

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

    /**
     * Setter for the constant component of light
     */
    void setConstant(float constant);

    /**
     * Getter for the constant component of light
     */
    float getConstant();

    /**
     * Setter for the linear component of light
     */
    void setLinear(float linear);

    /**
     * Getter for the linear component of light
     */
    float getLinear();

    /**
     * Setter for the quadratic constant of light
     */
    void setQuadratic(float quadratic);

    /**
     * Getter for the quadratic component of light
     */
    float getQuadratic();
};

#endif
