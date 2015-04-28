#ifndef SHADERTEST_H
#define SHADERTEST_H
#include "QOpenGLShaderProgram"


class shadertest
{
public:
    shadertest();

    void initialize(QObject*);
    void render();
private:

    QOpenGLShaderProgram * m_program;
    GLuint m_posAttr;
    GLuint m_colAttr;
    GLuint m_matrixUniform;

};

#endif // SHADERTEST_H
