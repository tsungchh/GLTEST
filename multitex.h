#ifndef MULTITEX_H
#define MULTITEX_H
#include "patch.h"


class multiTex
{
public:
    multiTex();
    void draw();


private:

    Vertex_VT g_Quad[4];/* =
    {
        {{-1.0f, -1.0f, 0.0f}, {0.0f, 1.0f}},
        {{ 1.0f, -1.0f, 0.0f}, {1.0f, 1.0f}},
        {{-1.0f,  1.0f, 0.0f}, {0.0f, 0.0f}},
        {{ 1.0f,  1.0f, 0.0f}, {1.0f, 0.0f}}
    };*/
    GLuint g_Texture0_ID;
    GLuint g_Texture1_ID;
};

#endif // MULTITEX_H
