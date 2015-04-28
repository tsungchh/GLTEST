#include "picktechnique.h"

pickTechnique::pickTechnique()
{
}


pickTechnique::~pickTechnique() {

}

bool pickTechnique::init(QObject* parent) {

    myShader = new QOpenGLShaderProgram(parent);
    myShader->addShaderFromSourceFile(QOpenGLShader::Vertex, "/Users/hsutsungchun/Desktop/QTGL/GL_2/vertex.vs");
    myShader->addShaderFromSourceFile(QOpenGLShader::Fragment, "/Users/hsutsungchun/Desktop/QTGL/GL_2/fragment.fs");
    myShader->link();

    m_WVPLocation = myShader->uniformLocation("gWVP");
    m_objectIndexLocation = myShader->uniformLocation("gObjectIndex");
    m_drawIndexLocation = myShader->uniformLocation("gDrawIndex");


    return true;
}

void pickTechnique::SetWVP(const QMatrix4x4 WVP){
    glUniformMatrix4fv( m_WVPLocation, 1, GL_TRUE, WVP.constData()  );
}

void pickTechnique::SetObjectIndex(uint ObjectIndex){
    glUniform1ui(m_objectIndexLocation, ObjectIndex);
}

void pickTechnique::DrawStartCB(uint DrawIndex) {
    glUniform1ui(m_drawIndexLocation, DrawIndex);
}

