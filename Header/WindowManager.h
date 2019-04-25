#ifndef WINDOW_FACTORY_H
#define WINDOW_FACTORY_H

#include "Window.h"
#include "imgui_internal.h"
#include "imgui.h"
#include "imgui_impl_sdl_gl3.h"
#include <SDL2/SDL.h>
#include <iostream>
#include <vector>

#define WINAPP 0
#define WINSCENE 1
#define WINGO 2
#define WINCOM 3

/**
 * The WindowManager manages all windows. All part of the code need to ask from
 * the windowManager to get a new window. WindowManager is a singleton.
 */
class WindowManager {

private:
	//Pointer of the WindowManager (needed for getWindowManager())
    static WindowManager* _factory;
	//Vector of all displayed windows
	std::vector<Window*> _windows;

public:
	/**
	 * Constructor
	 */
	WindowManager();

	/**
	 * Destructor
	 */
	~WindowManager();

	/**
	 * Getter for the singleton
	 */
    static WindowManager* getWindowManager();

	/**
	 * Instanciate a new window according an object and its type (App, ..)
	 */
	void instanciate(int tag, void* object);

	/**
	 * Free an object from the windowManager
	 */
	void free(void* object);

	/**
	 * Search if an object has a window (if yes return the index from the
	 * vector else -1)
	 */
	int search(void* object);

	
	/**
	 * Initialize the WindowManager and bind it to an SDL_Window
	 */
	void init(SDL_Window* w);

	/**
	 * Render all the windows into the SDL_Window
	 */
	void render(SDL_Window* w);
	
	/**
	 * Destroy the WindowManager
	 */
	void destroy();

	/**
	 * Retrieve inputs for the windows
	 */
	void event(SDL_Event* ev);

};

#endif
