#include "App.h"
#include "WindowManager.h"

App* App::_app = 0;

App::App(){}

App::~App(){
    //clean the scenes
    std::vector<Scene*>::iterator it;
    for(it = _scenes.begin(); it != _scenes.end(); it++){
        delete (*it);
    }
    _scenes.clear();
}

App* App::getApp(){
    if(!(App::_app)){
        _app = new App();
    }
    return _app;
}

void App::init(){
    //load all basic settings and store them in the Settings
    loadSettings();

    Settings* settings = Settings::getSettings();

    //Initialization of all the graphic environment (SDL and OpenGL)
    SDL_Init( SDL_INIT_VIDEO );
    SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, 1 );
    SDL_GL_SetAttribute( SDL_GL_ACCELERATED_VISUAL, 1 );
    SDL_GL_SetAttribute( SDL_GL_RED_SIZE, 8 );
    SDL_GL_SetAttribute( SDL_GL_GREEN_SIZE, 8 );
    SDL_GL_SetAttribute( SDL_GL_BLUE_SIZE, 8 );
    SDL_GL_SetAttribute( SDL_GL_ALPHA_SIZE, 8 );

    SDL_GL_SetAttribute( SDL_GL_CONTEXT_MAJOR_VERSION, 3 );
    SDL_GL_SetAttribute( SDL_GL_CONTEXT_MINOR_VERSION, 2 );
    SDL_GL_SetAttribute( SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE );

    //set width and height of screen
    _width = atoi(settings->getSetting("width").c_str());
    _height = atoi(settings->getSetting("height").c_str());

    _window = SDL_CreateWindow( settings->getSetting("window").c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, _width, _height, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN );
    _context = SDL_GL_CreateContext( _window );
    glEnable( GL_DEPTH_TEST );

    WindowManager::getWindowManager()->init( _window );
    WindowManager::getWindowManager()->instanciate(WINAPP, this);
    
	glViewport( 0, 0, _width, _height );

    //load the rest of the application
    loadShader();
    loadScript();
    loadScenes();
}

void App::loadSettings(){

    Settings* settings = Settings::getSettings();
    InputManager* inptuManager = InputManager::getInputManager();
    InputFactory* factory = InputFactory::getFactory();

    // settings/inputs xml file
    std::string file("Settings.xml");

    tinyxml2::XMLDocument xmlDoc;

    xmlDoc.LoadFile(file.c_str());

    tinyxml2::XMLNode * root = xmlDoc.FirstChild();

    if(root == NULL){
        return;
    }

    //fetch the different settings in the xml file
    tinyxml2::XMLElement * setting = root->FirstChildElement("Setting");

    while(setting != NULL){

        const char* attr_name = NULL;
        const char* attr_value = NULL;

        attr_name = setting->Attribute("name");
        attr_value = setting->Attribute("value");

        settings->addSetting(attr_name, attr_value);

        setting = setting->NextSiblingElement("Setting");
    }

    //fetch the different inputs in the xml file
    tinyxml2::XMLElement * input = root->FirstChildElement("Input");

    while(input != NULL){

        const char* attr_name = NULL;
        const char* attr_type = NULL;

        attr_name = input->Attribute("name");
        attr_type = input->Attribute("type");

        std::string str(attr_type);

        if(str == "keypad"){

            InputKey* newInput = factory->instantiateKeys();

            tinyxml2::XMLElement * key = input->FirstChildElement("Key");
            while(key != NULL){
                const char* attr_value = NULL;
                attr_value = key->Attribute("value");
                newInput->addKey(atoi(attr_value));
                key = key->NextSiblingElement("Key");
            }

            inptuManager->addInput(attr_name, newInput);
        }
        else if (str == "mouseButton"){

            InputMouseButton* newInput = factory->instantiateMouseButton();
            newInput->resetButton();
            inptuManager->addInput(attr_name, newInput);
        }
        else if (str == "mouseMotion"){

            InputMouseMotion* newInput = factory->instantiateMouseMotion();
            inptuManager->addInput(attr_name, newInput);
        }

        input = input->NextSiblingElement("Input");
    }
}

void App::loadShader(){

    Settings* settings = Settings::getSettings();
    ShaderManager* shaderManager = ShaderManager::getShaderManager();

    //shader xml file
    std::string file = settings->getSetting("assetFolder") + "Shader.xml";

    tinyxml2::XMLDocument xmlDoc;

    xmlDoc.LoadFile(file.c_str());

    tinyxml2::XMLNode * root = xmlDoc.FirstChild();

    if(root == NULL){
        return;
    }

    //load the different shader in the xml file
    tinyxml2::XMLElement * shader = root->FirstChildElement("Shader");

    while(shader != NULL){

        const char* attr_name = NULL;
        const char* attr_vs = NULL;
        const char* attr_fs = NULL;
        const char* attr_default= NULL;

        attr_name = shader->Attribute("name");
        attr_vs = shader->Attribute("vs");
        attr_fs = shader->Attribute("fs");
        attr_default = shader->Attribute("default");

        shaderManager->addShader(attr_name, new Shader(attr_vs, attr_fs));

        if(attr_default != NULL && std::string(attr_default) == "true"){
            shaderManager->setCurrentShader(attr_name);
        }

        shader = shader->NextSiblingElement("Shader");
    }
}

void App::loadScenes(){

    _currentScene = -1;

    Settings* settings = Settings::getSettings();

    //scene xml file
    std::string file = settings->getSetting("assetFolder") + settings->getSetting("sceneFolder") + "Scenes.xml";

    tinyxml2::XMLDocument xmlDoc;

    xmlDoc.LoadFile(file.c_str());

    tinyxml2::XMLNode * root = xmlDoc.FirstChild();

    if(root == NULL){
        return;
    }

    //load the different scene in the xml file
    tinyxml2::XMLElement * scene = root->FirstChildElement("Scene");

    int i = 0;
    while(scene != NULL){

        const char* attr_xml = NULL;
        const char* attr_entry = NULL;
        attr_xml = scene->Attribute("xml");
        attr_entry = scene->Attribute("entry");

        Scene* newScene = new Scene(attr_xml);
        newScene->Init();
        _scenes.insert(_scenes.end(), newScene);

        if(attr_entry != NULL && attr_entry == "true"){
            _currentScene = i;
        }

        scene = scene->NextSiblingElement("Scene");
        i++;
    }

    if(_currentScene == -1){
        _currentScene = 0;
    }
}

void App::loop(){
    _end = false;
    _lastTime = 0;
    _deltaTime = 0;

    //start the main loop of the program
    while(!_end){
        handleTime();
        processInput();
        onNewFrame();
        render();
		WindowManager::getWindowManager()->render( _window );
        SDL_GL_SwapWindow( _window );
    }
    //leave the program
    quit();
}

void App::loadScript(){
    //register the scripts, as we must instantiate them from their name inside the xml
    ScriptRegister* reg = ScriptRegister::getRegister();

    //test scripts
    reg->registerScript("CameraFPS", &createInstance<CameraFPS>);
    reg->registerScript("MenuHandler", &createInstance<MenuHandler>);
}

void App::handleTime(){
    uint32_t now = SDL_GetTicks();
    _deltaTime = now - _lastTime;
    _lastTime = now;
}

void App::processInput(){
    //delegate input processing
    InputManager* manager = InputManager::getInputManager();

    manager->processInput();
}

void App::onNewFrame(){
    //delegate to the scene
    _scenes.at(_currentScene)->onNewFrame();
}

void App::render(){
    //set the projection matrix which will be used in the shader
    _projection = glm::perspective(glm::radians(90.0f), (float)( _width / _height), 1.0f, 100.0f);

    //set the projection matrix to the shader
    ShaderManager* shaderManager = ShaderManager::getShaderManager();
    shaderManager->setUniformMatrix4Float("projection", _projection);

    //delegate to the scene
    _scenes.at(_currentScene)->render();
}

void App::setEndOfProgram(bool end){
    _end = end;
}

void App::quit(){
    //terminate all graphic elements
	WindowManager::getWindowManager()->destroy();
    SDL_GL_DeleteContext( _context );
    SDL_DestroyWindow( _window );
    SDL_Quit();
}
