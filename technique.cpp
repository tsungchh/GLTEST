#include "technique.h"

technique::technique()
{
}
technique::~technique()
{
    myShader->release();
}
/*
bool technique::init(QObject *parent)
{

    myShader = new QOpenGLShaderProgram(parent);
    if(!myShader->addShaderFromSourceFile(QOpenGLShader::Vertex, "/Users/hsutsungchun/Desktop/QTGL/GL_2/vertex.vs"))
        return false;

    if(!myShader->addShaderFromSourceFile(QOpenGLShader::Fragment, "/Users/hsutsungchun/Desktop/QTGL/GL_2/fragment.fs"))
        return false;

    myShader->link();

    return true;
}*/

void technique::Enable()
{
    this->myShader->bind();
}

void technique::Disable()
{
    this->myShader->release();
}
