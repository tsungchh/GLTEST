#ifndef LIGHTTEST_H
#define LIGHTTEST_H

#include "patch.h"
#include "mathBase.h"
#include "observer.h"
class Texture;
class Subject;

class textest : public Observer
{
public:
    textest(Subject* sub);
    ~textest();

    void draw();
    void init();
    QMatrix4x4 matrix;
    void printCoord();

    void update()
    {
        draw();
    }

private:

    Vertex_VT Vertices[4];
    Vector3f Positions[4];
    Vector3f Normals[4];
    Vector2f TexCoords[4];
    
    void CalcNormals(Vertex_VT* Vertices, const unsigned int* pIndices, unsigned int IndexCount, unsigned int VertexCount);
    void CreateVertexBuffer(const unsigned int* pIndices, unsigned int IndexCount);
    void CreateIndexBuffer( const unsigned int* pIndices, unsigned int SizeInBytes );


    void clear();
    GLuint m_VBO;
    GLuint m_IBO;
    GLuint m_VAO;

    // GLuint m_Buffers[4];


    Texture* myTex;

};

#endif // LIGHTTEST_H
