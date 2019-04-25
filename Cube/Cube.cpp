#include "Cube.h"

Cube::Cube(){
    //initialize the arrays
    _vertices = (int*)::operator new[](24*sizeof(int));
    _cubes = (int*)::operator new[](6*sizeof(int));
    for(int i=0; i<6; i++){
        _cubes[i] = Cube::EMPTY_FACE;
    }
}

void Cube::setMaterial(int material){
    _material = material;
}

int Cube::getMaterial(){
    return _material;
}

void Cube::setVertex(int vertex_xxx, int vertex){
    if(vertex_xxx < 24 && vertex_xxx >= 0){
        _vertices[vertex_xxx] = vertex;
    }
}

int Cube::getVertex(int vertex_xxx){
    if(vertex_xxx < 24 && vertex_xxx >= 0){
        return _vertices[vertex_xxx];
    }
    else{
        return -1;
    }
}

int Cube::getNumCubes(){
    int result = 0;
    for(int i=0; i<6; i++){
        if(_cubes[i] == Cube::EMPTY_FACE)
        result++;
    }
    return result;
}

void Cube::setCube(int face_x, int cube){
    if(face_x < 6 && face_x >= 0){
        _cubes[face_x] = cube;
    }
}

int Cube::getCube(int face_x){
    if(face_x < 6 && face_x >= 0){
        return _cubes[face_x];
    }
    else{
        return Cube::EMPTY_FACE;
    }

}

void Cube::getFaceIbo(int face_x, int* ibo){
    //for each face we need to draw 2 triangles
    //the first one will be index by 0,1,2 and the second one 3,4,5
    switch(face_x){
        case Cube::FACE_CLOSE :
        ibo[0] = getVertex(Cube::VERTEX_CBL_C);
        ibo[1] = getVertex(Cube::VERTEX_CBR_C);
        ibo[2] = getVertex(Cube::VERTEX_CTL_C);
        ibo[3] = getVertex(Cube::VERTEX_CTL_C);
        ibo[4] = getVertex(Cube::VERTEX_CTR_C);
        ibo[5] = getVertex(Cube::VERTEX_CBR_C);
        break;
        case Cube::FACE_FAR :
        ibo[0] = getVertex(Cube::VERTEX_FBL_F);
        ibo[1] = getVertex(Cube::VERTEX_FBR_F);
        ibo[2] = getVertex(Cube::VERTEX_FTL_F);
        ibo[3] = getVertex(Cube::VERTEX_FTL_F);
        ibo[4] = getVertex(Cube::VERTEX_FTR_F);
        ibo[5] = getVertex(Cube::VERTEX_FBR_F);
        break;
        case Cube::FACE_BOTTOM :
        ibo[0] = getVertex(Cube::VERTEX_CBL_B);
        ibo[1] = getVertex(Cube::VERTEX_CBR_B);
        ibo[2] = getVertex(Cube::VERTEX_FBL_B);
        ibo[3] = getVertex(Cube::VERTEX_FBL_B);
        ibo[4] = getVertex(Cube::VERTEX_FBR_B);
        ibo[5] = getVertex(Cube::VERTEX_CBR_B);
        break;
        case Cube::FACE_TOP :
        ibo[0] = getVertex(Cube::VERTEX_CTL_T);
        ibo[1] = getVertex(Cube::VERTEX_CTR_T);
        ibo[2] = getVertex(Cube::VERTEX_FTL_T);
        ibo[3] = getVertex(Cube::VERTEX_FTL_T);
        ibo[4] = getVertex(Cube::VERTEX_FTR_T);
        ibo[5] = getVertex(Cube::VERTEX_CTR_T);
        break;
        case Cube::FACE_LEFT :
        ibo[0] = getVertex(Cube::VERTEX_CBL_L);
        ibo[1] = getVertex(Cube::VERTEX_CTL_L);
        ibo[2] = getVertex(Cube::VERTEX_FBL_L);
        ibo[3] = getVertex(Cube::VERTEX_FBL_L);
        ibo[4] = getVertex(Cube::VERTEX_FTL_L);
        ibo[5] = getVertex(Cube::VERTEX_CTL_L);
        break;
        case Cube::FACE_RIGHT :
        ibo[0] = getVertex(Cube::VERTEX_CBR_R);
        ibo[1] = getVertex(Cube::VERTEX_CTR_R);
        ibo[2] = getVertex(Cube::VERTEX_FBR_R);
        ibo[3] = getVertex(Cube::VERTEX_FBR_R);
        ibo[4] = getVertex(Cube::VERTEX_FTR_R);
        ibo[5] = getVertex(Cube::VERTEX_CTR_R);
        break;

        default:
        break;
    }
}

int Cube::getOppositeFace(int face){
    switch (face) {
        case Cube::FACE_TOP:
        return Cube::FACE_BOTTOM;
        case Cube::FACE_BOTTOM:
        return Cube::FACE_TOP;
        case Cube::FACE_CLOSE:
        return Cube::FACE_FAR;
        case Cube::FACE_FAR:
        return Cube::FACE_CLOSE;
        case Cube::FACE_LEFT:
        return FACE_RIGHT;
        case Cube::FACE_RIGHT:
        return Cube::FACE_LEFT;
        default :
        return Cube::EMPTY_FACE;
    }
}

Vertex Cube::getVertexFromCBL(Vertex cbl, int target, float ridge){
    Vertex result;
    //for each case, we will calculate the new coordinate of the vector and it's new normal
    switch (target) {
        case VERTEX_CBL_B:
        result = Vertex(cbl.getX(), cbl.getY(), cbl.getZ(), 0.0, -1.0, 0.0);
        break;

        case VERTEX_CBR_B:
        result = Vertex(cbl.getX() + ridge, cbl.getY(), cbl.getZ(), 0.0, -1.0, 0.0);
        break;

        case VERTEX_FBR_B:
        result = Vertex(cbl.getX() + ridge, cbl.getY(), cbl.getZ() + ridge, 0.0, -1.0, 0.0);
        break;

        case VERTEX_FBL_B:
        result = Vertex(cbl.getX(), cbl.getY(), cbl.getZ() + ridge, 0.0, -1.0, 0.0);
        break;

        case VERTEX_FTL_T:
        result = Vertex(cbl.getX(), cbl.getY() + ridge, cbl.getZ() + ridge, 0.0, 1.0, 0.0);
        break;

        case VERTEX_FTR_T:
        result = Vertex(cbl.getX() + ridge, cbl.getY() + ridge, cbl.getZ() + ridge, 0.0, 1.0, 0.0);
        break;

        case VERTEX_CTR_T:
        result = Vertex(cbl.getX() + ridge, cbl.getY() + ridge, cbl.getZ(), 0.0, 1.0, 0.0);
        break;

        case VERTEX_CTL_T:
        result = Vertex(cbl.getX(), cbl.getY() + ridge, cbl.getZ(), 0.0, 1.0, 0.0);
        break;

        case VERTEX_CBL_C:
        result = Vertex(cbl.getX(), cbl.getY(), cbl.getZ(), 0.0, 0.0, -1.0);
        break;

        case VERTEX_CBR_C:
        result = Vertex(cbl.getX() + ridge, cbl.getY(), cbl.getZ(), 0.0, 0.0, -1.0);
        break;

        case VERTEX_CTR_C:
        result = Vertex(cbl.getX() + ridge, cbl.getY() + ridge, cbl.getZ(), 0.0, 0.0, -1.0);
        break;

        case VERTEX_CTL_C:
        result = Vertex(cbl.getX(), cbl.getY() + ridge, cbl.getZ(), 0.0, 0.0, -1.0);
        break;

        case VERTEX_FTL_F:
        result = Vertex(cbl.getX(), cbl.getY() + ridge, cbl.getZ() + ridge, 0.0, 0.0, 1.0);
        break;

        case VERTEX_FTR_F:
        result = Vertex(cbl.getX() + ridge, cbl.getY() + ridge, cbl.getZ() + ridge, 0.0, 0.0, 1.0);
        break;

        case VERTEX_FBR_F:
        result = Vertex(cbl.getX() + ridge, cbl.getY(), cbl.getZ() + ridge, 0.0, 0.0, 1.0);
        break;

        case VERTEX_FBL_F:
        result = Vertex(cbl.getX(), cbl.getY(), cbl.getZ() + ridge, 0.0, 0.0, 1.0);
        break;

        case VERTEX_CBL_L:
        result = Vertex(cbl.getX(), cbl.getY(), cbl.getZ(), -1.0, 0.0, 0.0);
        break;

        case VERTEX_FBL_L:
        result = Vertex(cbl.getX(), cbl.getY(), cbl.getZ() + ridge, -1.0, 0.0, 0.0);
        break;

        case VERTEX_FTL_L:
        result = Vertex(cbl.getX(), cbl.getY() + ridge, cbl.getZ() + ridge, -1.0, 0.0, 0.0);
        break;

        case VERTEX_CTL_L:
        result = Vertex(cbl.getX(), cbl.getY() + ridge, cbl.getZ(), -1.0, 0.0, 0.0);
        break;

        case VERTEX_CBR_R:
        result = Vertex(cbl.getX() + ridge, cbl.getY(), cbl.getZ(), 1.0, 0.0, 0.0);
        break;

        case VERTEX_FBR_R:
        result = Vertex(cbl.getX() + ridge, cbl.getY(), cbl.getZ() + ridge, 1.0, 0.0, 0.0);
        break;

        case VERTEX_FTR_R:
        result = Vertex(cbl.getX() + ridge, cbl.getY() + ridge, cbl.getZ() + ridge, 1.0, 0.0, 0.0);
        break;

        case VERTEX_CTR_R:
        result = Vertex(cbl.getX() + ridge, cbl.getY() + ridge, cbl.getZ(), 1.0, 0.0, 0.0);
        break;
    }

    return result;
}
