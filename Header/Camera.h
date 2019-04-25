#ifndef CAMERA_H
#define CAMERA_H

#include <math.h>

#include "libG.h"
#include "GameObject.h"

/**
 * A camera is a Component used to place the camera inside the world space
 */
class Camera : public Component
{
private:
	//the gameObject on which the camera is attached (to get the camera position and direction)
	GameObject* _gameObject;

	//define if the camera is the "main camera" which will be used to render most of the scene
	bool _main;
public:
	/**
	 * Constructor
	 */
	Camera();

	/**
	 * Setter of the gameObject
	 */
    void setGameObject(GameObject* gameObject);

	/**
	 * Getter of the gameObject
	 */
    GameObject* getGameObject();

	/**
	 * Setter for the main camera
	 */
	void setMain(bool main);

	/**
	 * Getter for the main camera
	 */
	bool isMain();

	/**
	 * Tis function returns the view based on the position and rotation on which the camera is attached
	 */
	glm::mat4 getView();
};

#endif
