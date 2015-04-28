#ifndef PICKINGFBO_H
#define PICKINGFBO_H

#include"qgl.h"

class PickingFBO
{
public:
    PickingFBO();
    ~PickingFBO();

    /**
     * Initiate frame buffer object which used to be renderd with Index info.
     * And also initiate texture object which stored index info.
     */
    bool init(unsigned int width, unsigned int height);

    void enable();
    void disable();

    struct Pixelinfo {

        float x;
        float y;
        float z;

    };

    Pixelinfo ReadPixel(unsigned int, unsigned int);

private:

    // FBO
    GLuint m_fbo;

    // Two texture object, first used to store index. Second one used to store depth info.
    GLuint m_pickingTexture;
    GLuint m_depthTexture;
};

#endif // PICKINGFBO_H
