#ifndef MYMACRO_H
#define MYMACRO_H


#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <string.h>

#define DEBUG_GL()\
{                 \
    GLenum err;   \
    while ((err = glGetError()) != GL_NO_ERROR) { \
            printf("OpenGL error in %s:%d: %d\n", __FILE__, __LINE__, err);     \
            exit(0);\
    }             \
}                 \

#define PRINT_GLVERSION()       \
{\
    const GLubyte* openglVersion = glGetString(GL_VERSION);                   \
    const GLubyte* shaderVersion = glGetString(GL_SHADING_LANGUAGE_VERSION);  \
    printf(" Opengl= %s, GLSL= %s\n", (char*)openglVersion, shaderVersion);   \
}\

#define RANDOM random
#define ZERO_MEM(a) memset(a, 0, sizeof(a))
#define SAFE_DELETE(p) if(p) {delete p; p=NULL}
#define ARRAY_SIZE_IN_ELEMENTS(a) (sizeof(a)/sizeof(a[0]))
#define INVALID_OGL_VALUE 0xffffffff
#define INVALID_UNIFORM_LOCATION oxffffffff
#define INVALID_MATERIAL 0xFFFFFFFF

#endif // MYMACRO_H
