#ifndef WIDGET_H
#define WIDGET_H

//#include "patch.h"
#include "mesh.h"
#include "shadertest.h"
#include <QMatrix4x4>

#include "QGLShaderProgram"
#include "textest.h"
#include "rendertechnique.h"

class GLWidget;


#include <QGLWidget>
class Widget : public QGLWidget
{
    Q_OBJECT

public:
    Widget( const QGLFormat& format, QWidget* parent = 0 );
    ~Widget();

private slots:
    void traslateTexCoor();


private:
    QMatrix4x4 projection;
    QMatrix4x4 view;
    QMatrix4x4 model;
    QMatrix4x4 texmatrix;
    Mesh* myMesh;
    //shadertest shader_test;
    textest myTexTest;

    /** Take care of matrix, lighting and shader settings. */
    rendertechnique myTechnique;

    QVector3D eye;
    QVector3D center;
    QVector3D g_up;
    QPoint lastPos;
    int xRot;
    int yRot;
    int zRot;

    /** sensitifity of mouse */
    double stepsize;
    double scalefactor;

    /** Events handeling functions */
    void rotateBy(int xAngle, int yAngle, int zAngle);
    void keyPressEvent(QKeyEvent*);
    void mousePressEvent(QMouseEvent*);
    void mouseMoveEvent(QMouseEvent*);

    /** Setup model view and projection matrix */
    void setupMatrix();

    /** QTGLWidget callback functions */
    void initializeGL();
    void paintGL();
    void resizeGL(int w, int h);

    /** other draw functions */
    void drawAxis();

    // test
    void drawTriangle();
};

#endif // WIDGET_H
