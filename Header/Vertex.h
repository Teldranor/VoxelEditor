#ifndef VERTEX_H
#define VERTEX_H

/**
 * A vertex is a representation a point in 3D space
 */
class Vertex
{
private:
    //vertex coordinate
    float _x;
    float _y;
    float _z;
    //vertex normal
    float _nx;
    float _ny;
    float _nz;
public:
    /**
     * Constructors
     */
    Vertex();
    Vertex(Vertex* vert);
    Vertex(float x, float y, float z, float nx, float ny, float nz);

    /**
     * Getter for x coordinate
     */
    float getX();

    /**
     * Getter for y coordinate
     */
    float getY();

    /**
     * Getter for z coordinate
     */
    float getZ();

    /**
     * Getter for x normal
     */
    float getNX();

    /**
     * Getter for y normal
     */
    float getNY();

    /**
     * Getter for z normal
     */
    float getNZ();

    /**
     * Override of the operator == to know when two vertices are equal
     */
    bool operator==(const Vertex other){return (_x == other._x && _y == other._y && _z == other._z && _nx == other._nx && _ny == other._ny && _nz == other._nz);}
};

#endif
