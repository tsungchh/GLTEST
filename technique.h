#ifndef TECHNIQUE_H
#define TECHNIQUE_H

#include "QOpenGLShaderProgram"

class technique
{
public:
    technique();
    virtual ~technique();
    void Enable();
    void Disable();
    virtual bool init(QObject* parent)=0;

protected:
    //virtual bool addShader(GLenum ShaderType, const char* Filename)=0;

    QOpenGLShaderProgram* myShader;
};

#endif // TECHNIQUE_H
