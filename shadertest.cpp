#include "shadertest.h"
#include "QGLShader"

static const char *vertexShaderSource =
    "attribute highp vec4 posAttr;\n"
    "attribute lowp vec4 colAttr;\n"
    "varying lowp vec4 col;\n"
    "uniform highp mat4 matrix;\n"
    "void main() {\n"
    "   col = colAttr;\n"
    "   gl_Position = matrix * posAttr;\n"
    "}\n";

GLuint VBO;
GLuint VAO;
GLuint IB = 0;

static void CreateVertexBuffer()
{
    GLfloat vertices[] = {
        0.0f, 0.707f, 0.5,
        -0.5f, -0.5f, 0.5,
        0.5f, -0.5f, 0.5
    };

    GLuint indices[] = {
        0, 1, 2
    };

    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, 9*sizeof(GLfloat), vertices, GL_STATIC_DRAW);

    glGenBuffers(1, &IB);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IB);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint)*3, indices, GL_STATIC_DRAW);

}

shadertest::shadertest()
{
    m_program = 0;
}

void shadertest::initialize(QObject* parent) {

    m_program = new QOpenGLShaderProgram(parent);
    m_program->addShaderFromSourceFile(QOpenGLShader::Vertex, "/Users/hsutsungchun/Desktop/QTGL/GL_2/vertex.vs");
    m_program->addShaderFromSourceFile(QOpenGLShader::Fragment, "/Users/hsutsungchun/Desktop/QTGL/GL_2/fragment.fs");
    if (!m_program->link()) {
        return;
    }

    m_posAttr = m_program->attributeLocation("Position");
    //m_colAttr = m_program->attributeLocation("colAttr");
    //m_matrixUniform = m_program->uniformLocation("matrix");

    CreateVertexBuffer();
}

void shadertest::render() {



    glClear(GL_COLOR_BUFFER_BIT);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IB);

    GLenum err;
        while ((err = glGetError()) != GL_NO_ERROR) {
            printf("OpenGL error:%d\n ", err);
        }

    if(!m_program->bind()) {
        return;
    }

    QMatrix4x4 matrix;
    matrix.perspective(60.0f, 4.0f/3.0f, 0.1f, 100.0f);
    matrix.translate(0, 0, -2);
    //matrix.rotate(100.0f * m_frame / screen()->refreshRate(), 0, 1, 0);

    //m_program->setUniformValue(m_matrixUniform, matrix);



    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(0);



    glBindVertexArray(VAO);

    //glDrawArrays(GL_TRIANGLES, 0, 3);
    glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glDisableVertexAttribArray(0);

    m_program->release();
}
