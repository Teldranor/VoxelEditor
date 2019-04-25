#ifndef CUBE_MODEL_H
#define CUBE_MODEL_H

#include <map>
#include <vector>

#include "tinyxml2.h"

#include "ShaderManager.h"
#include "Shader.h"
#include "Settings.h"
#include "Component.h"
#include "Cube.h"

/**
 * A CubeModel is a component used to render a voxel based 3D model stored inside an xml
 */
class CubeModel : public Component
{
private:
    //name of the xml file inside Assets/Model/ folder
    std::string _xml;

    //the size of the ridge of one cube it can't change inside the same model
    float _ridge;

    //the buffer inside which we update the model vbo
    unsigned int _modelVao;
    //the buffer inside which we store all the vertices of the model
    unsigned int _modelVbo;

    //the list of the materials in our model
    std::map<int, Material*> _materials;
    //the list of buffer we will render there is one by material
    std::map<int, unsigned int> _vaos;
    //the list of buffer that contains the index of the vertex used to form triangles. There is one by material
    std::map<int, unsigned int> _ibos;
    //the size of the buffer of each ibo
    std::map<int, int> _ibosSize;
    //the list of all vertices in the model
    std::map<int, Vertex*> _vertices;
    //the list of all the cubes in out model
    std::map<int, Cube*> _cubes;

public:
    /**
     * Constructor
     */
    CubeModel(std::string xml);

    /**
     * Initialize the model
     */
    void Init();

    /**
     * Getter for the xml file name
     */
    std::string getXml();

    /**
     * Override of the render method of the component
     * It will render the model
     */
    void render();

    /**
     * Add a cube next to the cube designed by the ID. The new cube will be added on the face designed and with the material designed
     * (see Cube.h for the face)
     */
    void addCube(int cubeId, int face, Material material);

private:
    /**
     * Load the cube model from the xml file
     */
    void load();

    /**
     * Save the model to the xml file
     */
    void save();

    /**
     * Create and initialize the vao for one material
     */
    void createMaterialVao(int id);

    /**
     * Bind the model vbo to the vao with this id
     */
    void bindVbo(int id);

    /**
     * Update the model vbo if we added vertices/cubes to the model
     */
    void updateVbo();

    /**
     * Update one color ibo (with this id) if we added a vertices/cubes of that color
     */
    void updateIbo(int id);
};

#endif
