#ifndef SCENE_H
#define SCENE_H

#include <vector>

#include "libG.h"
#include "GameObject.h"
#include "GameObjectFactory.h"
#include "Shader.h"
#include "Camera.h"
#include "CubeModel.h"
#include "ScriptRegister.h"
#include "ShaderManager.h"

#include "MyScript.h"

/**
 * A scene is a cluster of gameObject. A program can contain more than one scene but can render only one at a time.
 */
class Scene{

private:
    //xml file where a reference to all the gameObject in the scene will be store
    std::string _xml;

    //a list of all gameObject present into the scene
    std::vector<GameObject*> _gameObjects;

    //the main camera
    Camera* _camera;

    //a list of tags available for gameObject
    std::vector<std::string> _tags;
public:
    /**
     * Constructor
     */
    Scene(std::string xml);

    /**
     * Initialization of the scene
     */
    void Init();

    /**
     * load all the gameObjects and their components/child gameObject into the scene
     */
    void loadScene();

    /**
     * Save the current state of the scene in the xml file
     */
    void save();

    /**
     * Set the main camera
     */
    void setMainCamera(Camera* camera);

    /**
     * This function actualize the state of the scene depending of the scripts
     */
    void onNewFrame();

    /**
     * This function render all the gameObjects in the scene
     */
    void render();

    /**
     * Add a gameObject to the scene
     */
    std::string addGameObject(GameObject* gameObject);

    /**
     * Remove a gameObject to the scene
     */
    void removeGameObject(GameObject* gameObject);

    /**
     * Give the number of gameObjects in the scene
     */
    int getGetGameObjectSize();

    /**
     * This function return all gameObjects of the scene
     */
    std::vector<GameObject*> getGameObjects();

    /**
     * Tis function returns a gameObject based on his name
     */
    GameObject* getGameObject(std::string name);
};

#endif
