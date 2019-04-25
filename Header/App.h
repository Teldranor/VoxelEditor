#ifndef APP_H
#define APP_H

#include "libG.h"
#include "Shader.h"
#include "Scene.h"
#include "Settings.h"
#include "InputManager.h"
#include "ScriptRegister.h"
#include "WindowManager.h"
#include "ShaderManager.h"

/**
 * App is a represention of the core of the program. It's the one will set all the graphic parameter and will contain the different scene of the program
 */

class App{

private:
    //App is  singleton as it may be called from different place
    static App* _app;

    //grapic attributes
    SDL_Window* _window;
    SDL_GLContext _context;
    //display attributes
    //height of the window
    int _height;
    //width of the window
    int _width;

    //matrix for rendering
    glm::mat4 _projection;

    //Time between two frame
    uint32_t _deltaTime;
    uint32_t _lastTime;

    //bool for ending program
    bool _end;

    //Scene List
    std::vector<Scene*> _scenes;
    short int _currentScene;

    /**
     * This method loads the basic settings from an .xml which must be called "Settings.xml"
     */
    void loadSettings();
    /**
     * This method loads the name and file of the different shader used by the program
     */
    void loadShader();
    /**
     * This method loads all the basic information of all the scene of the program
     */
    void loadScenes();

protected:
    /**
     * This method register the scripts used as compononts in the program
     * Must be override inside a project to register the corresponding scripts
     */
    virtual void loadScript();

public:
    /**
     * Constructor
     */
    App();

    /**
     * Destructor
     */
    ~App();

    /**
     * Allow to fetch the singleton of App
     */
    static App* getApp();

    /**
     * Initialization of the tha app (SDL and OpenGL settings)
     */
    void init();

	/**
	 * Load settings, shaders and scenes
	 */
	void load();

    /**
     * The main loop of the program. It should be called after init to start the program
     */
    void loop();

    /**
     * Actualize the time variables (called one time per frame)
     */
    void handleTime();

    /**
     * Read the input as configured in the settings to make them available in the InputManager (called ont time per frame)
     */
    void processInput();

    /**
     * This function ...
     */
    void onNewFrame();

    /**
     * This function display the different element in the scene
     */
    void render();

    /**
     * This function allow the user to quit the main loop and thus to qui the program
     */
    void setEndOfProgram(bool end);

    /**
     * This function is automatically called upon leaving the main loop
     */
    void quit();
};

#endif
