#ifndef PATCH_H
#define PATCH_H

#include <QMatrix4x4>
#include <QVector3D>
#include <qmath.h>
#include <QtOpenGL>

struct Vertex_VT
{
    float m_Position[3]; // 頂點位置
    float m_Texcoord[2]; // 貼圖座標
    float m_Normal[3];   // Normal Coordinates.

    Vertex_VT() {

    }

    Vertex_VT(float pos[], float tex[], float nor[]) {
        m_Position[0] = pos[0];
        m_Position[1] = pos[1];
        m_Position[2] = pos[2];
        m_Texcoord[0] = tex[0];
        m_Texcoord[1] = tex[1];
        m_Normal[0]   = nor[0];
        m_Normal[1]   = nor[1];
        m_Normal[2]   = nor[2];
    }

    void set(float pos[], float tex[], float nor[]) {
        m_Position[0] = pos[0];
        m_Position[1] = pos[1];
        m_Position[2] = pos[2];
        m_Texcoord[0] = tex[0];
        m_Texcoord[1] = tex[1];
        m_Normal[0]   = nor[0];
        m_Normal[1]   = nor[1];
        m_Normal[2]   = nor[2];
    }

};

struct Color {
    unsigned char m_RGBA[4];
};
struct tex2d {
    float coor[2];
};

//! [0]
struct Geometry
{
    QVector<GLushort> faces;
    QVector<QVector3D> vertices;
    QVector<tex2d> texCoor;
    QVector<QVector3D> normals;
    //QVector<QVector4D> colors;
    Color* colors;
    void appendSmooth(const QVector3D &a, const QVector3D &n, int from);
    void appendFaceted(const QVector3D &a, const QVector3D &n);
    void finalize();
    void loadArrays() const;
};
//! [0]

//! [1]
class Patch
{
public:
    enum Smoothing { Faceted, Smooth };
    Patch(Geometry *);
    void setSmoothing(Smoothing s) { sm = s; }
    void translate(const QVector3D &t);
    void rotate(qreal deg, QVector3D axis);
    void draw() const;
    void addTri(const QVector3D &a, const QVector3D &b, const QVector3D &c, const QVector3D &n);
    void addQuad(const QVector3D &a, const QVector3D &b,  const QVector3D &c, const QVector3D &d);
    void addtex2d(const tex2d &n);
    void setColor(QColor c);

    GLushort start;
    GLushort count;
    GLushort initv;

    GLfloat faceColor[4];
    QMatrix4x4 mat;
    Smoothing sm;
    Geometry *geom;
};
//! [1]

#endif // PATCH_H
