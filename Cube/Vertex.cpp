#include "Vertex.h"

Vertex::Vertex(){}

Vertex::Vertex(Vertex* vert){
    _x = vert->_x;
    _y = vert->_y;
    _z = vert->_z;
    _nx = vert->_nx;
    _ny = vert->_ny;
    _nz = vert->_nz;
}

Vertex::Vertex(float x, float y, float z, float nx, float ny, float nz){
    _x = x;
    _y = y;
    _z = z;
    _nx = nx;
    _ny = ny;
    _nz = nz;
}

float Vertex::getX(){
    return _x;
}

float Vertex::getY(){
    return _y;
}

float Vertex::getZ(){
    return _z;
}

float Vertex::getNX(){
    return _nx;
}

float Vertex::getNY(){
    return _ny;
}

float Vertex::getNZ(){
    return _nz;
}
