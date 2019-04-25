#ifndef CUBE_H
#define CUBE_H

#include "libG.h"
#include "Vertex.h"
#include "Material.h"

/**
 * A cube is an element inside a cube model
 */
class Cube
{
private:
    //the material id of the material stored inside the cubeModel component
    int _material;

    //the ids of the vertices stored inside the cubeModel component
    int* _vertices;

    // the ids of the side cubes stored inside the cubeModel component
    int* _cubes;

public:
    //static vertex attributes
    static const int VERTEX_CBL_B = 0;  //close bottom left directed bottom
    static const int VERTEX_CBR_B = 1;  //close bottom right directed bottom
    static const int VERTEX_FBR_B = 2;  //far bottom right directed bottom
    static const int VERTEX_FBL_B = 3;  //far bottom left directed bottom

    static const int VERTEX_FTL_T = 4;  //far top left directed top
    static const int VERTEX_FTR_T = 5;  //far top right directed top
    static const int VERTEX_CTR_T = 6;  //close top right directed top
    static const int VERTEX_CTL_T = 7;  //close top left directed top

    static const int VERTEX_CBL_C = 8;  //close bottom left directed backward
    static const int VERTEX_CBR_C = 9;  //close bottom right directed backward
    static const int VERTEX_CTR_C = 10; //close top right directed backward
    static const int VERTEX_CTL_C = 11; //close top left directed backward

    static const int VERTEX_FTL_F = 12; //far top left directed forward
    static const int VERTEX_FTR_F = 13; //far top right directed forward
    static const int VERTEX_FBR_F = 14; //far bottom right directed forward
    static const int VERTEX_FBL_F = 15; //far bottom left directed forward

    static const int VERTEX_CBL_L = 16; //close bottom left directed left
    static const int VERTEX_FBL_L = 17; //far bottom left directed left
    static const int VERTEX_FTL_L = 18; //far top left directed left
    static const int VERTEX_CTL_L = 19; //close top left directed left

    static const int VERTEX_CBR_R = 20; //close bottom right directed right
    static const int VERTEX_FBR_R = 21; //far bottom right directed right
    static const int VERTEX_FTR_R = 22; //far top right directed right
    static const int VERTEX_CTR_R = 23; //close top right directed right

    //static face attributes
    static const int FACE_CLOSE  = 0; //face z neg
    static const int FACE_FAR    = 1; //face z pos
    static const int FACE_BOTTOM = 2; //face y neg
    static const int FACE_TOP    = 3; //face y pro
    static const int FACE_RIGHT  = 4; //face x pos
    static const int FACE_LEFT   = 5; //face x neg
    static const int EMPTY_FACE  = -1;

    /**
     * Constructor
     */
    Cube();

    /**
     * Setter for the material, take the id of the material inside the cubeModel
     */
    void setMaterial(int material);

    /**
     * Getter of the material, give the id of the material inside the cubeModel
     */
    int getMaterial();

    /**
     * Setter for one vertex
     * vertex_xxx is the location of the vertex define by the static vertex attributes
     * vertex is the id of the vertex inside the cubeModel
     */
    void setVertex(int vertex_xxx, int vertex);

    /**
     * Getter for one vertex
     * vertex_xxx is the location of the vertex define by the static vertex attributes
     */
    int getVertex(int vertex_xxx);

    /**
     * Return the number of side emplacement empty
     */
    int getNumCubes();

    /**
     * Setter for one cube
     * face_x is the location of the face define by the static face attributes
     * vertex is the id of the cube inside the cubeModel
     */
    void setCube(int face_x, int cube);

    /**
     * Getter for one cube
     * face_x is the location of the face define by the static face attributes
     */
    int getCube(int face_x);

    /**
     * Stores into ibo all the ids of the vertex to draw the given face
     * ibo must be pre-initialized as a int[6]
     */
    void getFaceIbo(int face_x,int* ibo);

    /**
     * Get the opposite face id from one face
     */
    static int getOppositeFace(int face);

    /**
     * Calculate the coordinate of a vertex depending of VERTEX_CBL
     * target is the location of the target vertex define by static vertex attributes (exept 0 which is a cbl)
     */
    static Vertex getVertexFromCBL(Vertex cbl, int target, float ridge);
};

#endif
