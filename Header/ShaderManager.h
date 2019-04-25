#ifndef SHADER_MANAGER_H
#define SHADER_MANAGER_H

#include <map>

#include "libG.h"
#include "Shader.h"

/**
 * The shader manager groups all the shader used in the program
 * This class is a singleton
 */
class ShaderManager {

private:
    //singleton
    static ShaderManager* _shaderManager;

    //List of all shader depending on their name
    std::map<std::string, Shader*> _shaders;

    //the name of the current shader used
    std::string _currentShader;

public:
    /**
     * Constructor
     */
    ShaderManager();

    /**
     * Getter for the signleton
     */
    static ShaderManager* getShaderManager();

    /**
     * Add a shader
     */
    void addShader(std::string name, Shader* shader);

    /**
     * Getter for a shader
     */
    Shader* getShader(std::string name);

    /**
     * Inform the program that it should use a specific shader
     */
    void setCurrentShader(std::string name);

    /**
     * Getter for the current shader
     */
    Shader* getCurrentShader();

    /**
	 * Setter for uniforms component for all Shaders
	 * A uniform componenet is a component that is set for the shader for one or many rendering
	 */
    void setUniformFloat(std::string name, float value);
    void setUniformVec3Float(std::string name, glm::vec3 vec);
    void setUniformMatrix4Float(std::string name, glm::mat4 mat);
};

#endif
