#include "GameObject.h"

#include "Scene.h"
#include "Camera.h"
#include "CubeModel.h"
#include "DirectionalLight.h"
#include "PointLight.h"
#include "SpotLight.h"
#include "Script.h"

GameObject::GameObject(std::string tag, std::string name){
    //default gameObject
    _pos = glm::vec3(0.0f, 0.0f, 0.0f);
    _rot = glm::vec3(0.0f, 0.0f, 0.0f);
    _scale = glm::vec3(1.0f, 1.0f, 1.0f);

    _tag = tag;
    _name = name;

    _parent = NULL;
}

GameObject::~GameObject(){
    //delete all components/children to avoid memory leak
    std::vector<GameObject*>::iterator itgo;
    for(itgo = _children.begin(); itgo != _children.end(); itgo++){
        delete (*itgo);
    }
    _children.clear();

    std::vector<Component*>::iterator itc;
    for(itc = _components.begin(); itc != _components.end(); itc++){
        delete (*itc);
    }

    _components.clear();
}

std::string GameObject::getName(){
    return _name;
}

void GameObject::loadFromXmlElement(tinyxml2::XMLElement* element){

    GameObjectFactory* gameObjectFactory = GameObjectFactory::getFactory();
    ScriptRegister* reg = ScriptRegister::getRegister();

    //get Position element
    tinyxml2::XMLElement * pos = element->FirstChildElement("Position");
    const char* attr_pos_x = NULL;
    const char* attr_pos_y = NULL;
    const char* attr_pos_z = NULL;
    attr_pos_x = pos->Attribute("xpos");
    attr_pos_y = pos->Attribute("ypos");
    attr_pos_z = pos->Attribute("zpos");
    setPosition(atof(attr_pos_x), atof(attr_pos_y), atof(attr_pos_z));

    //get Rotation element
    tinyxml2::XMLElement * rot = element->FirstChildElement("Rotation");
    const char* attr_rot_x = NULL;
    const char* attr_rot_y = NULL;
    const char* attr_rot_z = NULL;
    attr_rot_x = rot->Attribute("xrot");
    attr_rot_y = rot->Attribute("yrot");
    attr_rot_z = rot->Attribute("zrot");
    setRotation(atof(attr_rot_x), atof(attr_rot_y), atof(attr_rot_z));

    //get Scale element
    tinyxml2::XMLElement * scale = element->FirstChildElement("Scale");
    const char* attr_scale_x = NULL;
    const char* attr_scale_y = NULL;
    const char* attr_scale_z = NULL;
    attr_scale_x = scale->Attribute("xscale");
    attr_scale_y = scale->Attribute("yscale");
    attr_scale_z = scale->Attribute("zscale");
    setScale(atof(attr_scale_x), atof(attr_scale_y), atof(attr_scale_z));

    //get components element
    tinyxml2::XMLElement * component = element->FirstChildElement("Component");

    while(component != NULL){

        const char* attr_component = NULL;
        attr_component = component->Attribute("component");

        //instantiate the component depending on the attribute "component"
        std::string str(attr_component);

        if(str == "CubeModel"){

            const char* attr_model = NULL;
            attr_model = component->Attribute("model");

            attachComponent(new CubeModel(attr_model));
        }
        else if(str == "Camera"){

            const char* attr_main = NULL;
            attr_main = component->Attribute("main");

            Camera* camera = new Camera();
            if(attr_main == "true"){
                camera->setMain(true);
            }else{
                camera->setMain(false);
            }

            attachComponent(camera);
        }
        else if(str == "DirLight"){

            DirectionalLight* dirLight = new DirectionalLight();

            tinyxml2::XMLElement * direction = component->FirstChildElement("Direction");
            const char* attr_d_x = NULL;
            const char* attr_d_y = NULL;
            const char* attr_d_z = NULL;
            attr_d_x = direction->Attribute("x");
            attr_d_y = direction->Attribute("y");
            attr_d_z = direction->Attribute("z");
            dirLight->setDirection(atof(attr_d_x), atof(attr_d_y), atof(attr_d_z));

            tinyxml2::XMLElement * ambient = component->FirstChildElement("Ambient");
            const char* attr_a_r = NULL;
            const char* attr_a_g = NULL;
            const char* attr_a_b = NULL;
            attr_a_r = ambient->Attribute("r");
            attr_a_g = ambient->Attribute("g");
            attr_a_b = ambient->Attribute("b");
            dirLight->setAmbient(atof(attr_a_r), atof(attr_a_g), atof(attr_a_b));

            tinyxml2::XMLElement * diffuse = component->FirstChildElement("Diffuse");
            const char* attr_d_r = NULL;
            const char* attr_d_g = NULL;
            const char* attr_d_b = NULL;
            attr_d_r = diffuse->Attribute("r");
            attr_d_g = diffuse->Attribute("g");
            attr_d_b = diffuse->Attribute("b");
            dirLight->setDiffuse(atof(attr_d_r), atof(attr_d_g), atof(attr_d_b));

            tinyxml2::XMLElement * specular = component->FirstChildElement("Specular");
            const char* attr_s_r = NULL;
            const char* attr_s_g = NULL;
            const char* attr_s_b = NULL;
            attr_s_r = specular->Attribute("r");
            attr_s_g = specular->Attribute("g");
            attr_s_b = specular->Attribute("b");
            dirLight->setSpecular(atof(attr_s_r), atof(attr_s_g), atof(attr_s_b));

            attachComponent(dirLight);
        }
        else if(str == "PointLight"){

            PointLight* pointLight = new PointLight();
            const char* attr_id = NULL;
            attr_id = component->Attribute("id");
            pointLight->setId(attr_id);

            tinyxml2::XMLElement * ambient = component->FirstChildElement("Ambient");
            const char* attr_a_r = NULL;
            const char* attr_a_g = NULL;
            const char* attr_a_b = NULL;
            attr_a_r = ambient->Attribute("r");
            attr_a_g = ambient->Attribute("g");
            attr_a_b = ambient->Attribute("b");
            pointLight->setAmbient(atof(attr_a_r), atof(attr_a_g), atof(attr_a_b));

            tinyxml2::XMLElement * diffuse = component->FirstChildElement("Diffuse");
            const char* attr_d_r = NULL;
            const char* attr_d_g = NULL;
            const char* attr_d_b = NULL;
            attr_d_r = diffuse->Attribute("r");
            attr_d_g = diffuse->Attribute("g");
            attr_d_b = diffuse->Attribute("b");
            pointLight->setDiffuse(atof(attr_d_r), atof(attr_d_g), atof(attr_d_b));

            tinyxml2::XMLElement * specular = component->FirstChildElement("Specular");
            const char* attr_s_r = NULL;
            const char* attr_s_g = NULL;
            const char* attr_s_b = NULL;
            attr_s_r = specular->Attribute("r");
            attr_s_g = specular->Attribute("g");
            attr_s_b = specular->Attribute("b");
            pointLight->setSpecular(atof(attr_s_r), atof(attr_s_g), atof(attr_s_b));

            tinyxml2::XMLElement * attenuation = component->FirstChildElement("Attenuation");
            const char* attr_constant = NULL;
            const char* attr_linear = NULL;
            const char* attr_quadratic = NULL;
            attr_constant = attenuation->Attribute("constant");
            attr_linear = attenuation->Attribute("linear");
            attr_quadratic = attenuation->Attribute("quadratic");
            pointLight->setConstant(atof(attr_constant));
            pointLight->setLinear(atof(attr_linear));
            pointLight->setQuadratic(atof(attr_quadratic));

            attachComponent(pointLight);
        }
        else if(str == "SpotLight"){

            SpotLight* spotLight = new SpotLight();
            const char* attr_id = NULL;
            attr_id = component->Attribute("id");
            spotLight->setId(attr_id);

            tinyxml2::XMLElement * direction = component->FirstChildElement("Direction");
            const char* attr_d_x = NULL;
            const char* attr_d_y = NULL;
            const char* attr_d_z = NULL;
            attr_d_x = direction->Attribute("x");
            attr_d_y = direction->Attribute("y");
            attr_d_z = direction->Attribute("z");
            spotLight->setDirection(atof(attr_d_x), atof(attr_d_y), atof(attr_d_z));

            tinyxml2::XMLElement * ambient = component->FirstChildElement("Ambient");
            const char* attr_a_r = NULL;
            const char* attr_a_g = NULL;
            const char* attr_a_b = NULL;
            attr_a_r = ambient->Attribute("r");
            attr_a_g = ambient->Attribute("g");
            attr_a_b = ambient->Attribute("b");
            spotLight->setAmbient(atof(attr_a_r), atof(attr_a_g), atof(attr_a_b));

            tinyxml2::XMLElement * diffuse = component->FirstChildElement("Diffuse");
            const char* attr_d_r = NULL;
            const char* attr_d_g = NULL;
            const char* attr_d_b = NULL;
            attr_d_r = diffuse->Attribute("r");
            attr_d_g = diffuse->Attribute("g");
            attr_d_b = diffuse->Attribute("b");
            spotLight->setDiffuse(atof(attr_d_r), atof(attr_d_g), atof(attr_d_b));

            tinyxml2::XMLElement * specular = component->FirstChildElement("Specular");
            const char* attr_s_r = NULL;
            const char* attr_s_g = NULL;
            const char* attr_s_b = NULL;
            attr_s_r = specular->Attribute("r");
            attr_s_g = specular->Attribute("g");
            attr_s_b = specular->Attribute("b");
            spotLight->setSpecular(atof(attr_s_r), atof(attr_s_g), atof(attr_s_b));

            tinyxml2::XMLElement * attenuation = component->FirstChildElement("Attenuation");
            const char* attr_constant = NULL;
            const char* attr_linear = NULL;
            const char* attr_quadratic = NULL;
            attr_constant = attenuation->Attribute("constant");
            attr_linear = attenuation->Attribute("linear");
            attr_quadratic = attenuation->Attribute("quadratic");
            spotLight->setConstant(atof(attr_constant));
            spotLight->setLinear(atof(attr_linear));
            spotLight->setQuadratic(atof(attr_quadratic));

            tinyxml2::XMLElement * angle = component->FirstChildElement("Angle");
            const char* attr_cut_off = NULL;
            const char* attr_outer_cut_off = NULL;
            attr_cut_off = angle->Attribute("cutOff");
            attr_outer_cut_off = angle->Attribute("outerCutOff");
            spotLight->setCutOff(atof(attr_cut_off));
            spotLight->setOuterCutOff(atof(attr_outer_cut_off));

            attachComponent(spotLight);
        }
        else if(str == "Script"){

            const char* attr_script = NULL;
            attr_script = component->Attribute("script");

            //if the component is a script we instantiate it using the register
            attachComponent(reg->instantiateScript(attr_script));
        }

        component = component->NextSiblingElement("Component");
    }

    //get children element
    tinyxml2::XMLElement * gameObject = element->FirstChildElement("Child");

    while(gameObject != NULL){

        const char* attr_name = NULL;
        const char* attr_tag = NULL;

        attr_name = gameObject->Attribute("name");
        attr_tag = gameObject->Attribute("tag");

        GameObject* newGameObject = gameObjectFactory->instantiate(attr_tag, attr_name);

        newGameObject->loadFromXmlElement(gameObject);

        addChild(newGameObject);

        gameObject = gameObject->NextSiblingElement("Child");
    }
}

void GameObject::saveToXmlElement(tinyxml2::XMLDocument* xmlDoc, tinyxml2::XMLElement* element){

    //put basic information of the gameObject
    element->SetAttribute("name", _name.c_str());
    element->SetAttribute("tag", _tag.c_str());

    //put position in the xml file
    tinyxml2::XMLElement* pos = xmlDoc->NewElement("Position");
    pos->SetAttribute("xpos", _pos.x);
    pos->SetAttribute("ypos", _pos.y);
    pos->SetAttribute("zpos", _pos.z);
    element->InsertEndChild(pos);

    //put rotation in the xml file
    tinyxml2::XMLElement* rot = xmlDoc->NewElement("Rotation");
    rot->SetAttribute("xrot", _rot.x);
    rot->SetAttribute("yrot", _rot.y);
    rot->SetAttribute("zrot", _rot.z);
    element->InsertEndChild(rot);

    //put scale in the xml file
    tinyxml2::XMLElement* scale = xmlDoc->NewElement("Scale");
    scale->SetAttribute("xscale", _scale.x);
    scale->SetAttribute("yscale", _scale.y);
    scale->SetAttribute("zscale", _scale.z);
    element->InsertEndChild(scale);

    //put components in the xml file
    std::vector<Component*>::iterator itc;
    for(itc = _components.begin(); itc != _components.end(); itc++){

        tinyxml2::XMLElement* component = xmlDoc->NewElement("Component");

        bool found = false;

        //try to dynamic cast them, if it works, set the right attributes for this type of component
        CubeModel* cubeModel = dynamic_cast<CubeModel*>(*itc);
        if(cubeModel){
            found = true;
            component->SetAttribute("component", "CubeModel");
            component->SetAttribute("model", cubeModel->getXml().c_str());
        }

        Camera* camera = dynamic_cast<Camera*>(*itc);
        if(camera){
            found = true;
            component->SetAttribute("component", "Camera");
            component->SetAttribute("main", camera->isMain());
        }

        DirectionalLight* dirLight = dynamic_cast<DirectionalLight*>(*itc);
        if(dirLight){
            found = true;
            component->SetAttribute("component", "DirLight");

            tinyxml2::XMLElement * direction = xmlDoc->NewElement("Direction");
            direction->SetAttribute("r", dirLight->getDirection().x);
            direction->SetAttribute("g", dirLight->getDirection().y);
            direction->SetAttribute("b", dirLight->getDirection().z);
            component->InsertEndChild(direction);

            tinyxml2::XMLElement * ambient = xmlDoc->NewElement("Ambient");
            ambient->SetAttribute("r", dirLight->getAmbient().x);
            ambient->SetAttribute("g", dirLight->getAmbient().y);
            ambient->SetAttribute("b", dirLight->getAmbient().z);
            component->InsertEndChild(ambient);

            tinyxml2::XMLElement * diffuse = xmlDoc->NewElement("Diffuse");
            diffuse->SetAttribute("r", dirLight->getDiffuse().x);
            diffuse->SetAttribute("g", dirLight->getDiffuse().y);
            diffuse->SetAttribute("b", dirLight->getDiffuse().z);
            component->InsertEndChild(diffuse);

            tinyxml2::XMLElement * specular = xmlDoc->NewElement("Specular");
            specular->SetAttribute("r", dirLight->getSpecular().x);
            specular->SetAttribute("g", dirLight->getSpecular().y);
            specular->SetAttribute("b", dirLight->getSpecular().z);
            component->InsertEndChild(specular);
        }

        PointLight* pointLight = dynamic_cast<PointLight*>(*itc);
        if(pointLight){
            found = true;
            component->SetAttribute("component", "PointLight");
            component->SetAttribute("id", pointLight->getId().c_str());

            tinyxml2::XMLElement * ambient = xmlDoc->NewElement("Ambient");
            ambient->SetAttribute("r", pointLight->getAmbient().x);
            ambient->SetAttribute("g", pointLight->getAmbient().y);
            ambient->SetAttribute("b", pointLight->getAmbient().z);
            component->InsertEndChild(ambient);

            tinyxml2::XMLElement * diffuse = xmlDoc->NewElement("Diffuse");
            diffuse->SetAttribute("r", pointLight->getDiffuse().x);
            diffuse->SetAttribute("g", pointLight->getDiffuse().y);
            diffuse->SetAttribute("b", pointLight->getDiffuse().z);
            component->InsertEndChild(diffuse);

            tinyxml2::XMLElement * specular = xmlDoc->NewElement("Specular");
            specular->SetAttribute("r", pointLight->getSpecular().x);
            specular->SetAttribute("g", pointLight->getSpecular().y);
            specular->SetAttribute("b", pointLight->getSpecular().z);
            component->InsertEndChild(specular);

            tinyxml2::XMLElement * attenuation = xmlDoc->NewElement("Attenuation");
            attenuation->SetAttribute("constant", pointLight->getConstant());
            attenuation->SetAttribute("linear", pointLight->getLinear());
            attenuation->SetAttribute("quadratic", pointLight->getQuadratic());
            component->InsertEndChild(attenuation);
        }

        Script* script = dynamic_cast<Script*>(*itc);
        if(script){
            found = true;
            component->SetAttribute("component", "Script");
            component->SetAttribute("script", script->getScriptName().c_str());
        }

        if(!found){
            component->SetAttribute("component", "Error");
        }

        element->InsertEndChild(component);
    }

    //put children in the xml file
    std::vector<GameObject*>::iterator itg;
    for(itg = _children.begin(); itg != _children.end(); ++itg){
        tinyxml2::XMLElement * gameObject = xmlDoc->NewElement("Child");
        (*itg)->saveToXmlElement(xmlDoc, gameObject);
        element->InsertEndChild(gameObject);
    }
}

void GameObject::setPosition(float x, float y, float z){
    _pos = glm::vec3(x, y, z);
}

glm::vec3 GameObject::getPosition(){
    return _pos;
}

glm::vec3 GameObject::getWorldPosition(){
    if(_parent != NULL){
        glm::vec4 tmp = glm::vec4(_pos.x, _pos.y, _pos.z, 1.0);
        glm::vec4 result = _parent->getModel() * tmp;
        return glm::vec3(result.x, result.y, result.z);
    }
    return getPosition();
}

void GameObject::setRotation(float pitch, float yaw, float roll){
    _rot = glm::vec3(pitch, yaw, roll);
}

glm::vec3 GameObject::getRotation(){
    return _rot;
}

glm::vec3 GameObject::getWorldRotation(){
    if(_parent != NULL){
        glm::vec4 tmp = glm::vec4(_rot.x, _rot.y, _rot.z, 0.0);
        glm::vec4 result = _parent->getModel() * tmp;
        return glm::vec3(result.x, result.y, result.z);
    }
    return getRotation();
}

void GameObject::setScale(float x, float y, float z){
    _scale = glm::vec3(x, y, z);
}

glm::vec3 GameObject::getScale(){
    return _scale;
}

glm::vec3 GameObject::getWorldScale(){
    if(_parent != NULL){
        glm::vec3 result = _parent->getWorldScale() * _scale;
        return glm::vec3(result.x, result.y, result.z);
    }
    return getScale();
}

void GameObject::translate(glm::vec3 direction, float speed){

    if(direction.x != 0 || direction.y != 0 || direction.z != 0)
    direction = glm::normalize(direction);

    glm::vec3 deltaPos;
    deltaPos.x = direction.x*cos(_rot.y) + direction.z*sin(_rot.y);
    deltaPos.y = direction.y;
    deltaPos.z = direction.z*cos(_rot.y) - direction.x*sin(_rot.y);

    deltaPos *= speed;

    setPosition(_pos.x + deltaPos.x, _pos.y + deltaPos.y, _pos.z + deltaPos.z);
}

void GameObject::rotate(glm::vec3 axis, float speed){
    glm::vec3 deltaRot = speed*axis;
    setRotation(_rot.x + deltaRot.x, _rot.y + deltaRot.y, _rot.z + deltaRot.z);
}

glm::mat4 GameObject::getModel(){
    glm::mat4 model;
    if(_parent != NULL){
        model = _parent->getModel();
    }
    model = glm::scale(model, _scale);
    model = glm::rotate(model, _rot.y, glm::vec3(0.0f, 1.0f, 0.0f));
    model = glm::rotate(model, _rot.x, glm::vec3(1.0f, 0.0f, 0.0f));
    model = glm::rotate(model, _rot.z, glm::vec3(0.0f, 0.0f, 1.0f));
    model = glm::translate(model, _pos);
    return model;
}

void GameObject::attachComponent(Component* component){
    _components.insert(_components.end(), component);

    //if the component needs to know the gameObject then we set it
    Script* script = dynamic_cast<Script*>(component);
    if(script){
        script->setGameObject(this);
    }
    Camera* camera = dynamic_cast<Camera*>(component);
    if(camera){
        camera->setGameObject(this);
    }
    PointLight* pointLight = dynamic_cast<PointLight*>(component);
    if(pointLight){
        pointLight->setGameObject(this);
    }
    SpotLight* spotLight = dynamic_cast<SpotLight*>(component);
    if(spotLight){
        spotLight->setGameObject(this);
    }
}

void GameObject::detachComponent(Component* component){
    std::vector<Component*>::iterator it;
    for(it = _components.begin(); it != _components.end(); it++){
        if(*it == component){
            delete (*it);
            _components.erase(it);
            break;
        }
    }
}

std::vector<Component*> GameObject::getComponents(){
    return _components;
}

void GameObject::setParent(GameObject* parent){
    _parent = parent;
}

GameObject* GameObject::getParent(){
    return _parent;
}

void GameObject::addChild(GameObject* child){
    _children.insert(_children.end(), child);
    child->setParent(this);
}

void GameObject::removeChild(GameObject* child){
    std::vector<GameObject*>::iterator it;
    for(it = _children.begin(); it != _children.end(); it++){
        if(*it == child){
            delete (*it);
            _children.erase(it);
            break;
        }
    }
}

std::vector<GameObject*> GameObject::getChildren(){
    return _children;
}

void GameObject::OnNewFrame(){
    std::vector<Component*>::iterator itc;
    for(itc = _components.begin(); itc != _components.end(); itc++){
        (*itc)->OnNewFrame();
    }

    std::vector<GameObject*>::iterator itg;
    for(itg = _children.begin(); itg != _children.end(); itg++){
        (*itg)->OnNewFrame();
    }
}

void GameObject::light(){
    std::vector<Component*>::iterator itc;
    for(itc = _components.begin(); itc != _components.end(); itc++){
        (*itc)->light();
    }

    std::vector<GameObject*>::iterator itg;
    for(itg = _children.begin(); itg != _children.end(); itg++){
        (*itg)->light();
    }
}

void GameObject::render(){
    ShaderManager* shaderManager = ShaderManager::getShaderManager();
    Shader* myShader = shaderManager->getCurrentShader();
    myShader->setUniformMatrix4Float("model", getModel());
    std::vector<Component*>::iterator itc;
    for(itc = _components.begin(); itc != _components.end(); itc++){
        (*itc)->render();
    }

    std::vector<GameObject*>::iterator itg;
    for(itg = _children.begin(); itg != _children.end(); itg++){
        (*itg)->render();
    }
}
