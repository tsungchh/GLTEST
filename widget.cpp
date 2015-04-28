#include "widget.hpp"
#include "solarsystem.h"
#include "textest.h"
#include "multitex.h"
#include "texmatrix.h"
#include "shadertest.h"
#include <QtWidgets>
#include "QGLShader"
#include <QColor>
#include "stdio.h"
#include "MYMACRO.h"




Widget::Widget( const QGLFormat& format, QWidget* parent )
    : QGLWidget( format, parent )
{
    stepsize = 0.2;
    scalefactor = 1.0;
    this->updateGL();
}

Widget::~Widget()
{

}

void Widget::traslateTexCoor() {
    printf("tex matrix move\n");
    texmatrix.translate(QVector3D(0.1f, 0.0f,0.0f));
    this->updateGL();
}

void Widget::initializeGL()
{
    PRINT_GLVERSION();
    printf("Curr dir = %s\n", qApp->applicationDirPath().toStdString().c_str());
    myTechnique.init(this);

    myMesh = new Mesh();
    myMesh->LoadMesh("/Users/hsutsungchun/Desktop/QTGL/GL_2/models/bunny.obj", this);
    DEBUG_GL();
    //shader_test.initialize(this);
    myTexTest.init();
    
    DEBUG_GL();

    glEnable(GL_DEPTH_TEST);
    //glEnable(GL_CULL_FACE);

  //glEnable(GL_BLEND);
  //glEnable(GL_POLYGON_SMOOTH);
  //glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    myTechnique.Enable();
    DirectionalLight m_directionalLight;
    m_directionalLight.Color = QVector3D(1.0f, 1.0f, 1.0f);
    m_directionalLight.AmbientIntensity = 0.5f;
    m_directionalLight.DiffuseIntensity = 0.8f;
    m_directionalLight.Direction = QVector3D(1.0f, -1.0, 0.0);
    myTechnique.SetDirectionalLight(m_directionalLight);
    
  //glShadeModel(GL_SMOOTH);


    projection.setToIdentity();
    projection.perspective(90.0f, 1.0f, 1.0f, 100.0f);
    //glOrtho(-10,10,-50,50, 0,20);
    eye = QVector3D(0.0f, 0.0f, -5.0f);
    center = QVector3D(0.0f, 0.0f, 0.0f);
    g_up = QVector3D(0.0f, 1.0f, 0.0f);

    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

    //texmatrix.setToIdentity();

}

void Widget::resizeGL(int w, int h) {
    glViewport(0, 0, w, h);


    // Calculate aspect ratio
    qreal aspect = (qreal)w / ((qreal)h?h:1);

    // Set near plane to 3.0, far plane to 7.0, field of view 45 degrees
    const qreal zNear = 3.0, zFar = 7.0, fov = 45.0;

    // Reset projection
    projection.setToIdentity();
    // Set perspective projection
    projection.perspective(fov, aspect, zNear, zFar);
    //projection.perspective(90.0f, 1.0f, f, 100.0f);

}

// red->x axis, green->y axis, blue->z axis
void Widget::drawAxis() {
    glDisable(GL_LIGHT0);
    glDisable(GL_LIGHTING);
    glBegin(GL_LINES);
        glColor3f(1.0f,0.0f,0.0f);
        glVertex3f(0.0f,0.0f,0.0f);
        glVertex3f(100.0f,0.0f,0.0f);
        glColor3f(0.0f,1.0f,0.0f);
        glVertex3f(0.0f,0.0f,0.0f);
        glVertex3f(0.0f,100.0f,0.0f);
        glColor3f(0.0f,0.0f,1.0f);
        glVertex3f(0.0f,0.0f,0.0f);
        glVertex3f(0.0f,0.0f,100.0f);
    glEnd();
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHTING);

}

void Widget::setupMatrix()
{
    view.setToIdentity();
    model.setToIdentity();
    view.lookAt(eye, center, g_up);

    model.rotate(xRot / 16.0f, 1.0f, 0.0f, 0.0f);
    model.rotate(yRot / 16.0f, 0.0f, 1.0f, 0.0f);
    model.rotate(zRot / 16.0f, 0.0f, 0.0f, 1.0f);
    model.scale(scalefactor, scalefactor, -scalefactor);
    model.translate(-1.5, 0, 0);


    QMatrix4x4 gwvp = projection*view*model;

    myTechnique.SetWVP(gwvp);
    myTechnique.SetWorldMatrix(model);

}

void Widget::paintGL()
{

    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

    myTechnique.Enable();
    setupMatrix();


    /** Render method applied below */
    myTechnique.SetTextureUnit(0);
    myTexTest.draw();
    //myTexTest.matrix = projection*modelview;

    //shader_test.render();
    myMesh->Render();


    //textest* texture = new textest();
    //multiTex* texture = new multiTex();
    //texMatrix* texture = new texMatrix();
    //texture->draw();

    //drawAxis();

    myTechnique.Disable();
}

// Todo
void Widget::drawTriangle() {

    // picking shader program enable

    // render the triangle
        // render the index
        // get mouse location
        // render triangle

    // render the normal scene

}


void Widget::keyPressEvent(QKeyEvent* keyevent) {
    QVector3D g_lookat = center - eye;
    g_lookat.normalize();

    if(keyevent->key()==Qt::Key_A) {
        QVector3D right = QVector3D::crossProduct(g_up, g_lookat);
        eye += right*stepsize;
    }else if (keyevent->key()==Qt::Key_W){
        //eye += g_lookat*stepsize;
        scalefactor *= stepsize*10;
    }else if (keyevent->key()==Qt::Key_S){
        //eye -= g_lookat*stepsize;
        scalefactor /= stepsize*10;
    }else if (keyevent->key()==Qt::Key_D){
        QVector3D right = QVector3D::crossProduct(g_lookat, g_up);
        eye += right*stepsize;
        printf("eye = %f, %f, %f\n", eye.x(), eye.y(), eye.z());
        printf("right = %f, %f, %f\n", right.x(), right.y(), right.z());

    }else if (keyevent->key()==Qt::Key_Up){
        rotateBy(50.0f,0.0f,0.0f);
    }else if (keyevent->key()==Qt::Key_Down){
        rotateBy(-50.0f,0.0f,0.0f);
    }else if (keyevent->key()==Qt::Key_Left){
        rotateBy(0.0f,50.0f,0.0f);
    }else if (keyevent->key()==Qt::Key_Right){
        rotateBy(0.0f,-50.0f,0.0f);
    }

    center =  eye + g_lookat;
    this->updateGL();
}

void Widget::rotateBy(int xAngle, int yAngle, int zAngle)
{
    xRot += xAngle;
    yRot += yAngle;
    zRot += zAngle;
    updateGL();
}

void Widget::mousePressEvent(QMouseEvent *event) {
    lastPos = event->pos();
}

void Widget::mouseMoveEvent(QMouseEvent *event)
{
    //int dx = event->x() - lastPos.x();
    //int dy = event->y() - lastPos.y();

    int dx = lastPos.x() - event->x();
    int dy = lastPos.y() - event->y();


    if (event->buttons() & Qt::LeftButton) {
        rotateBy(8 * dy, 8 * dx, 0);
    } else if (event->buttons() & Qt::RightButton) {
        rotateBy(8 * dy, 0, 8 * dx);
    }
    lastPos = event->pos();
}
