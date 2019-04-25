#ifndef SHADER_H
#define SHADER_H


#include "libG.h"

/**
 * A shader is a program used by graphic enviroment to convert the 3D world created to a 2D screen-displayable window
 * A shader contains at least to file a vertex shader and a fragment shader
 * Our shader are stored inside Shader/ folder
 *
 * the final shader used for our program use cubeShader.vs as vertex shader and cubeShader.fs as fragment shader
 * A vertex shader transform an object in 3D space into the 2D space of the screen
 * A fragment shader define the color of each point
 *
 * The vertex shader is always used first and thus all parameters are send to this shader with the layout
 * A parameter can be send from the vertex shader to the fragment shader using key word out (from vertex) and in (from fragment)
 * Uniform parameters are like global variable inside one shader
 */
class Shader
{
private:
	void init(const char* vertexPath, const char* fragmentPath);

public:
	//program ID
	unsigned int ID;

	/**
	 * Constructors
	 * Normally it should take a vertex path and a fragment path or it is unusable
	 */
	Shader();
	Shader(const char* vertexPath, const char* fragmentPath);

	/**
	 * Notify the graphic environment to use this shader for the next render actions
	 */
	void use();

	/**
	 * Setter for uniforms component of the Shader
	 * A uniform componenet is a component that is set for the shader for one or many rendering
	 */
	void setUniformBool(const std::string &name, bool value);
	void setUniformInt(const std::string &name, int value);
	void setUniformFloat(const std::string &name, float value);
	void setUniformVec3Float(const std::string &name, glm::vec3 value);
	void setUniformVec4Float(const std::string &name, glm::vec4 color);
	void setUniformMatrix4Float(const std::string &name, glm::mat4 transform);
};

#endif
