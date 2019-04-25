#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include <vector>
#include <typeinfo>

#include "libG.h"
#include "tinyxml2.h"

#include "ShaderManager.h"

#include "Component.h"

/**
 * A GameObject is a basic object of all scenes, it contains a position, multiples components, and children gameObjects
 */
class GameObject
{
private:
    //position of the gameObject in local space
    glm::vec3 _pos;
    //rotation of the gameObject in local space (in radians)
    glm::vec3 _rot;
    //scale of the gameObject in local space
    glm::vec3 _scale;

    //tag of the gameObject
    std::string _tag;
    //name of the gameObject
    std::string _name;

    //list of component contained by he gameObject
    std::vector<Component*> _components;

    //parent gameObject (if null then the gameObject is directly inside the scene)
    GameObject* _parent;
    //list of child gameObjects
    std::vector<GameObject*> _children;

public:
    /**
     * Constructor
     */
    GameObject(std::string tag, std::string name);

    /**
     * Destructor
     */
    virtual ~GameObject();

    /**
     * Getter for the name of the gameObject
     */
    std::string getName();

    /**
     * load the gameObject from it's XMLElement and all his compoenents and children
     */
    void loadFromXmlElement(tinyxml2::XMLElement* element);

    /**
     * save the gameObject to a XMLElement and all his components and children
     */
    void saveToXmlElement(tinyxml2::XMLDocument* xmlDoc, tinyxml2::XMLElement* element);

    /**
     * Setter for the position
     */
    void setPosition(float x, float y, float z);

    /**
     * Getter for the position
     */
    glm::vec3 getPosition();

    /**
     * Getter for the world position
     */
    glm::vec3 getWorldPosition();

    /**
     * Setter for the rotation
     * pitch represent the rotation around x axis
     * yaw represent the rotation around y axis (up)
     * roll represent the rotation around z axis (forward)
     */
    void setRotation(float pitch, float yaw, float roll);

    /**
     * Getter for the rotation
     */
    glm::vec3 getRotation();

    /**
     * Getter for the world rotation
     */
    glm::vec3 getWorldRotation();

    /**
     * Setter for the scale
     */
    void setScale(float x, float y, float z);

    /**
     * Getter for the scale
     */
    glm::vec3 getScale();

    /**
     * Getter for the world scale
     */
    glm::vec3 getWorldScale();

    /**
     * This method operate a basic translation in the given direction at the given speed
     */
    void translate(glm::vec3 direction, float speed);

    /**
     * This method operate a basic rotation around the given axis at the given speed
     */
    void rotate(glm::vec3 axis, float speed);

    /**
     * This method calculate the model matrix used to place a gameObject from local space to world space
     */
    glm::mat4 getModel();

    /**
     * This method attaches the given component to the gameObject
     */
    void attachComponent(Component* component);

    /**
     * This method detaches a component from the gameObject
     */
    void detachComponent(Component* component);

    /**
     * This method returns the list of component attach to the gameObject
     */
    std::vector<Component*> getComponents();

    /**
     * This method search for a component of the given class T inside the gameObject
     * implemented in GameObject.tpp
     */
    template<class T> T getComponent();

    /**
     * This method search for a component of the given class T inside the gameObject and his children
     * implemented in GameObject.tpp
     */
    template<class T> T getComponentRecursive();

    /**
     * Setter for the parent of the gameObject
     */
    void setParent(GameObject* gameObject);

    /**
     * Getter for the parent of the gameObject (returns NULL if no parent)
     */
    GameObject* getParent();

    /**
     * The method adds a child to the gameObject
     */
    void addChild(GameObject* child);

    /**
     * This method removes a child to the gameObject
     */
    void removeChild(GameObject* child);

    /**
     * This method returns the list of children of the gameObject
     */
    std::vector<GameObject*> getChildren();

    /**
     * This method is called once per frame and calls the OnNewFrame method of the components/children contained by the gameObject
     */
    void OnNewFrame();

    /**
     * This method is called once per frame and calls the light method of the components/children contained by the gameObject
     */
    void light();

    /**
     * This method is called once per frame and calls the render method of the components/children contained by the gameObject
     */
    void render();
};

//implementation of the generic method
#include "GameObject.tpp"

#endif
