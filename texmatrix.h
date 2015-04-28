#ifndef TEXMATRIX_H
#define TEXMATRIX_H

#include "patch.h"


class texMatrix
{
public:
    texMatrix();
    void draw();


private:

    GLuint g_Texture0_ID;
    Vertex_VT g_Quad[4];/*=
    {
        {{-1.5f, -1.5f, 0.0f}, {-1.0f, 2.0f}},
        {{-0.1f, -1.5f, 0.0f}, { 2.0f, 2.0f}},
        {{-1.5f, -0.1f, 0.0f}, {-1.0f,-1.0f}},
        {{-0.1f, -0.1f, 0.0f}, { 2.0f,-1.0f}}
    };*/
};

#endif // TEXMATRIX_H
