#include "Scene.h"
#include "WindowManager.h"

Scene::Scene(std::string xml){
    _xml = xml;
}

void Scene::Init(){
    _tags.insert(_tags.end(), "None");
    _tags.insert(_tags.end(), "MainCamera");
    _tags.insert(_tags.end(), "Player");
    _tags.insert(_tags.end(), "Environnement");

    loadScene();
}

void Scene::loadScene(){

    _camera = NULL;

    GameObjectFactory* gameObjectFactory = GameObjectFactory::getFactory();
    Settings* settings = Settings::getSettings();

    //xml file containing all gameObjects
    std::string file = settings->getSetting("assetFolder") + settings->getSetting("sceneFolder") + _xml;

    tinyxml2::XMLDocument xmlDoc;

    xmlDoc.LoadFile(file.c_str());

    tinyxml2::XMLNode * root = xmlDoc.FirstChild();

    if(root == NULL){
        return;
    }

    //loading gameObjects recursively
    //the scene load the main gameObject and a gameObject loads all his children
    tinyxml2::XMLElement * gameObject = root->FirstChildElement("GameObject");

    while(gameObject != NULL){

        const char* attr_name = NULL;
        const char* attr_tag = NULL;

        attr_name = gameObject->Attribute("name");
        attr_tag = gameObject->Attribute("tag");

        GameObject* newGameObject = gameObjectFactory->instantiate(attr_tag, attr_name);

        newGameObject->loadFromXmlElement(gameObject);

        addGameObject(newGameObject);

        gameObject = gameObject->NextSiblingElement("GameObject");
    }

    //fetch main Camera
    std::vector<GameObject*>::iterator it;
    for(it = _gameObjects.begin(); it != _gameObjects.end(); it++){

        if(Camera* camera = (*it)->getComponentRecursive<Camera*>()){
            _camera = camera;
            break;
        }
    }

	WindowManager::getWindowManager()->instanciate(WINSCENE , this);
    
	//TODO
    //Add a camera if there is no main camera in the scene
}

void Scene::save(){

    Settings* settings = Settings::getSettings();

    //xml file that will contain all gameObjects in the scene
    std::string file = settings->getSetting("assetFolder") + settings->getSetting("sceneFolder") + _xml;

    tinyxml2::XMLDocument xmlDoc;

    tinyxml2::XMLNode * root = xmlDoc.NewElement("Root");
    xmlDoc.InsertFirstChild(root);

    //save gameObject recursively
    //the scene save the main gameObject and a gameObject save all his children
    std::vector<GameObject*>::iterator itg;
    for(itg = _gameObjects.begin(); itg != _gameObjects.end(); ++itg){
        tinyxml2::XMLElement * gameObject = xmlDoc.NewElement("GameObject");
        (*itg)->saveToXmlElement(&xmlDoc, gameObject);
        root->InsertEndChild(gameObject);
    }

    xmlDoc.SaveFile(file.c_str());
}

void Scene::setMainCamera(Camera* camera){
    _camera = camera;
}

void Scene::onNewFrame(){
    //delegate the actualization to the gameObjects that contains the different scripts used
    std::vector<GameObject*>::iterator it;
    for(it = _gameObjects.begin(); it != _gameObjects.end(); it++){
        (*it)->OnNewFrame();
    }
}

void Scene::render(){

    //set the background color
    //Should be replace by a skybox
    glClearColor(0.0, 0.0, 0.5, 0.0);
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

    glm::mat4 view;

    if(_camera){
        view = _camera->getView();
    }

    glm::mat4 model;

    //set the view matrix which will be used by the shader to place to display
    //set the viewPos which will be used to calculate ligthning
    ShaderManager* shaderManager = ShaderManager::getShaderManager();
    shaderManager->setUniformMatrix4Float("view", view);
    shaderManager->setUniformVec3Float("viewPos", _camera->getGameObject()->getWorldPosition());

    //delegate the lights to the gameObjects that contains the different lights
    std::vector<GameObject*>::iterator it;
    for(it = _gameObjects.begin(); it != _gameObjects.end(); ++it){
        (*it)->light();
    }

    //delegate the render of 3D object to the gameObjects that know the Model to render²
    for(it = _gameObjects.begin(); it != _gameObjects.end(); ++it){
        (*it)->render();
    }
}

std::string Scene::addGameObject(GameObject* gameObject){
    //TODO check name which should be unique
    _gameObjects.push_back(gameObject);
    return gameObject->getName();
}

void Scene::removeGameObject(GameObject* gameObject){
    std::vector<GameObject*>::iterator it;
    for(it = _gameObjects.begin(); it != _gameObjects.end(); it++){
        if(*it == gameObject){
            delete (*it);
            _gameObjects.erase(it);
            break;
        }
    }
}

int Scene::getGetGameObjectSize(){
    //TODO add gameObjects children
    return _gameObjects.size();
}


std::vector<GameObject*> Scene::getGameObjects() {
  return _gameObjects;
}

GameObject* Scene::getGameObject(std::string name){
    std::vector<GameObject*>::iterator it;
    for(it = _gameObjects.begin(); it != _gameObjects.end(); it++){
        if((*it)->getName() == name){
            return *it;
        }
        //TODO search inside children
    }
    return NULL;
}
