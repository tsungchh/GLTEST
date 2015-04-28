#include "multitex.h"
#include <QImage>

multiTex::multiTex()
{
    float vertex[4][3]= {{-1.5f, -1.5f, 0.0f}, {-0.1f, -1.5f, 0.0f}, {-1.5f, -0.1f, 0.0f}, {-0.1f, -0.1f, 0.0f}};
    float tex[4][2] = {{-1.0f, 2.0f}, {2.0f, 2.0f}, {-1.0f, -1.0f}, {2.0f, -1.0f}};
    float normal[4][3] = {{0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}};
    g_Quad[0].set(vertex[0], tex[0], normal[0]);
    g_Quad[1].set(vertex[1], tex[1], normal[1]);
    g_Quad[2].set(vertex[2], tex[2], normal[2]);
    g_Quad[3].set(vertex[3], tex[3], normal[3]);


    QImage brickwall = QGLWidget::convertToGLFormat(QImage(":images/brickwall.tga"));
    QImage graffiti = QGLWidget::convertToGLFormat(QImage(":images/graffiti_happy.tga"));


    glGenTextures( 1, &g_Texture0_ID);
    glBindTexture(GL_TEXTURE_2D, g_Texture0_ID);
    glTexParameteri( GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER, GL_LINEAR );
    glTexParameteri( GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER, GL_LINEAR );
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA,
        brickwall.size().width(), brickwall.size().height(), 0,
        GL_RGBA, GL_UNSIGNED_BYTE, brickwall.bits() );


    glGenTextures( 1, &g_Texture1_ID);
    glBindTexture(GL_TEXTURE_2D, g_Texture1_ID);
    glTexParameteri( GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER, GL_LINEAR );
    glTexParameteri( GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER, GL_LINEAR );
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA,
        graffiti.size().width(), graffiti.size().height(), 0,
        GL_RGBA, GL_UNSIGNED_BYTE, graffiti.bits() );
}

void multiTex::draw() {

    // `清除畫面`
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
    // `把正向跟反向的面都畫出來`
    glDisable(GL_CULL_FACE);
    // `設定要用陣列的方式傳入頂點位置跟顏色`
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, sizeof(Vertex_VT), &g_Quad[0].m_Position);

    // `打開第0層貼圖`
    glActiveTexture(GL_TEXTURE0_ARB);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, g_Texture0_ID);
    // `指定第0層貼圖的貼圖座標`
    glClientActiveTexture(GL_TEXTURE0_ARB);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    glTexCoordPointer(2, GL_FLOAT, sizeof(Vertex_VT), &g_Quad[0].m_Texcoord);
    // `打開第1層貼圖`
    glActiveTexture(GL_TEXTURE1_ARB);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, g_Texture1_ID);
    // `設定兩張貼圖相加`
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_ADD);
    // `指定第1層貼圖的貼圖座標`
    glClientActiveTexture(GL_TEXTURE1_ARB);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    glTexCoordPointer(2, GL_FLOAT, sizeof(Vertex_VT), &g_Quad[0].m_Texcoord);

    // `畫出看板`
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

    glDisable(GL_TEXTURE_2D);

}
