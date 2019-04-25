#ifndef WINDOW_H
#define WINDOW_H

#include "imgui.h"
#include <iostream>
#include <vector>


/**
 * Component type
 */
#define UNDEF	0
#define CUBM	1
#define CAM		2
#define DIRL	3
#define PNTL	4
#define SCR		5

/**
 * To avoid cyclal include
 */
class App;
class Scene;
class GameObject;
class Component;

/**
 * Window of the UI. The Window class is an abstract class. There is a window
 * class for each object (App, Scene, GameObject, Component)
 */
class Window {
	public:
		/**
		 * Constructor
		 */
		Window();

		/**
		 * Destructor
		 */
		virtual ~Window();
		
		/**
		 * When the window is created, run Start() to initialize all needed
		 * values
		 */
		virtual void Start();

		/**
		 * Define how the window have to be rendered
		 * Will be called by the WindowManager
		 */
		virtual void OnNewFrame();

		/**
		 * Return the object manilupated by the window
		 */
		virtual void* getObject();
};

class WindowApp : public Window {
	protected:
		App* _app;
	public:
		WindowApp(App* a);
		~WindowApp();
		void OnNewFrame();
		void* getObject();
};

class WindowScene : public Window {
	protected:
		Scene* _scene;
		bool bl[10];
	public:
		WindowScene(Scene* s);
		~WindowScene();
		void OnNewFrame();
		void* getObject();
};

class WindowGameObject : public Window {
	protected:
		GameObject* _gameObject;
		bool bl[10];
		
		/**
		 * Search the type of a compoenent attached to the GameObject
		 */
		int searchType(Component* c);
	public:
		WindowGameObject(GameObject* g);
		~WindowGameObject();
		void OnNewFrame();
		void* getObject();
};

class WindowComponent : public Window {
	protected:
		Component* _component;
		//Type of the component
		int _type;
		
		/**
		 * All those functions define how the window have to be rendered
		 * depending the type of th component
		 */
		void unknown();
		void cubeModel();
		void camera();
		void dirLight();
		void pntLight();
		void script();
	public:
		WindowComponent(Component* c);
		~WindowComponent();
		void Start();
		void OnNewFrame();
		void* getObject();

		/**
		 * Get the type of the component
		 */
		int getType();
};
#endif
