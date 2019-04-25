#ifndef MATERIAL_H
#define MATERIAL_H

#include "libG.h"

/**
 * A material is a representation of a material of an object, it defines how the object should be colorised
 */
class Material{
private:
    //ambient is the minimum color of an object as we suppose that something is casting light upon it
    glm::vec3 _ambient;
    //diffuse is the result color of a light casting light in the direction of the cube
    glm::vec3 _diffuse;
    //specular is the shiny point of a light on a material
    glm::vec3 _specular;
    //shininess of the material
    float _shininess;
    //alpha channel of the material
    float _alpha;
public:
    /**
     * Constructor
     */
    Material();

    /**
     * Setter of the ambient
     */
    void setAmbient(float r, float g, float b);

    /**
     * Getter of the ambient
     */
    glm::vec3 getAmbient();

    /**
     * Setter of the diffuse
     */
    void setDiffuse(float r, float g, float b);

    /**
     * Getter of the diffuse
     */
    glm::vec3 getDiffuse();

    /**
     * Setter of the specular
     */
    void setSpecular(float r, float g, float b);

    /**
     * Getter of the specular
     */
    glm::vec3 getSpecular();

    /**
     * Setter of the shininess
     */
    void setShininess(float shininess);

    /**
     * Getter of the shininess
     */
    float getShininess();

    /**
     * Setter of the alpha
     */
    void setAlpha(float alpha);

    /**
     * Getter of the alpha
     */
    float getAlpha();

    /**
     * Override of the operator == to know when two materials are equal
     */
    bool operator==(const Material other){
        return (
            _ambient.x == other._ambient.x &&
            _ambient.y == other._ambient.y &&
            _ambient.z == other._ambient.z &&
            _diffuse.x == other._diffuse.x &&
            _diffuse.y == other._diffuse.y &&
            _diffuse.z == other._diffuse.z &&
            _specular.x == other._specular.x &&
            _specular.y == other._specular.y &&
            _specular.z == other._specular.z &&
            _shininess == other._shininess &&
            _alpha == other._alpha
        );
    }
};

#endif
