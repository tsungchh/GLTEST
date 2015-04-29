#include "textest.h"
#include "texture.h"
#include <QImage>
#include "MYMACRO.h"
#include "observer.h"
#define checkImageWidth 64
#define checkImageHeight 64

#define ARRAY_SIZE_IN_ELEMENTS(a) (sizeof(a)/sizeof(a[0]))

static GLuint g_TextureID;
static GLubyte checkImage[checkImageHeight][checkImageWidth][4];
void makeCheckImage(void)
{
int i, j, c;
   for (i = 0; i < checkImageHeight; i++) {
      for (j = 0; j < checkImageWidth; j++) {
         c = (((i&0x8)==0)^((j&0x8))==0)*255;
         checkImage[i][j][0] = (GLubyte) c;
         checkImage[i][j][1] = (GLubyte) c;
         checkImage[i][j][2] = (GLubyte) c;
         checkImage[i][j][3] = (GLubyte) 255;
} }
}

textest::textest(Subject* sub) : Observer(sub) {
    m_VBO = INVALID_OGL_VALUE;
    m_VAO = INVALID_OGL_VALUE;
    m_IBO = INVALID_OGL_VALUE;

    // ZERO_MEM(m_Buffers);
    init();
}

textest::~textest()
{
    clear();
}

void textest::clear()
{
    if(m_VBO!=INVALID_OGL_VALUE)
    {
        glDeleteBuffers(1, &m_VBO);
    }

    if(m_VAO!=INVALID_OGL_VALUE)
    {
        glDeleteBuffers(1, &m_VAO);
    }

    if(m_IBO!=INVALID_OGL_VALUE)
    {
        glDeleteBuffers(1, &m_IBO);
    }

//    if(m_Buffers[0]!=0) {
//        glDeleteBuffers(ARRAY_SIZE_IN_ELEMENTS(m_Buffers), m_Buffers);
//    }
}

void textest::init()
{
    unsigned int Indices[] = { 0, 3, 1,
                               1, 3, 2,
                               2, 3, 0,
                               1, 2, 0 };

    DEBUG_GL();
    glGenVertexArrays(1, &m_VAO);

    DEBUG_GL();
    glBindVertexArray(m_VAO);


    DEBUG_GL();
    CreateIndexBuffer( Indices, sizeof(Indices) );
    CreateVertexBuffer( Indices, ARRAY_SIZE_IN_ELEMENTS(Indices) );

    
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex_VT), 0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex_VT), (const GLvoid*)12);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex_VT), (const GLvoid*)20);

    myTex = new Texture(GL_TEXTURE_2D, "/Users/hsutsungchun/Desktop/QTGL/GL_2/images/brickwall.tga");


        DEBUG_GL();

    if(!myTex->Load()) {
            DEBUG_GL();

        printf("Loading Texture Error!\n");
        return;
    }

    glBindVertexArray(0);

}

void textest::CalcNormals(Vertex_VT* Vertices, const unsigned int* pIndices, unsigned int IndexCount, unsigned int VertexCount)
{
    for(int i=0 ;i< IndexCount; ++i)
    {
        unsigned int Index0 = pIndices[i];
        unsigned int Index1 = pIndices[i+1];
        unsigned int Index2 = pIndices[i+2];
        float* tmp;
        tmp = Vertices[Index0].m_Position;
        QVector3D v1 (tmp[0], tmp[1], tmp[2]);
        tmp = Vertices[Index1].m_Position;

        QVector3D v2 (tmp[0], tmp[1], tmp[2]);
        tmp = Vertices[Index2].m_Position;

        QVector3D v3 (tmp[0], tmp[1], tmp[2]);

        QVector3D va = v2 - v1;
        QVector3D vb = v3 - v1;
        QVector3D normal = QVector3D::crossProduct(va, vb);

        Vertices[Index0].m_Normal[0] += normal.x();
        Vertices[Index0].m_Normal[1] += normal.y();
        Vertices[Index0].m_Normal[2] += normal.z();
        Vertices[Index1].m_Normal[0] += normal.x();
        Vertices[Index1].m_Normal[1] += normal.y();
        Vertices[Index1].m_Normal[2] += normal.z();
        Vertices[Index2].m_Normal[0] += normal.x();
        Vertices[Index2].m_Normal[1] += normal.y();
        Vertices[Index2].m_Normal[2] += normal.z();
    }

    for (int i=0; i<VertexCount; ++i)
    {
        QVector3D tmp( Vertices[i].m_Normal[0], Vertices[i].m_Normal[1], Vertices[i].m_Normal[2] );
        tmp.normalize();
        Vertices[i].m_Normal[0] = tmp.x();
        Vertices[i].m_Normal[1] = tmp.y();
        Vertices[i].m_Normal[2] = tmp.z();
    }
}


void textest::CreateIndexBuffer( const unsigned int* pIndices, unsigned int SizeInBytes )
{
    glGenBuffers(1, &m_IBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, SizeInBytes, pIndices, GL_STATIC_DRAW);

}

void textest::CreateVertexBuffer(const unsigned int* pIndices, unsigned int IndexCount)
{
    float v1[] = {-1.0f, -1.0f, 0.5773f  };
    float t1[] = {0.0f, 0.0f};
    float n1[] = {0.0f, 0.0f};
    float v2[] = { 0.0f, -1.0f, -1.15475f}; float t2[] = {0.5f, 0.0f}; float n2[]={0.0f, 0.0f};
    float v3[] = { 1.0f, -1.0f, 0.5773f  }; float t3[] = {1.0f, 0.0f}; float n3[]={0.0f, 0.0f};
    float v4[] = { 0.0f,  1.0f, 0.0f     }; float t4[] = {0.5f, 1.0f}; float n4[]={0.0f, 0.0f};

    Vertices[0].set(v1, t1, n1);
    Vertices[1].set(v2, t2, n2);
    Vertices[2].set(v3, t3, n3);
    Vertices[3].set(v4, t4, n4);

    int VertexCount = ARRAY_SIZE_IN_ELEMENTS(Vertices);
    //CalcNormals(Vertices, pIndices, IndexCount, VertexCount);

    glGenBuffers(1, &m_VBO);

    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);

    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex_VT)*VertexCount, Vertices, GL_STATIC_DRAW);


}

void textest::printCoord() {
    QVector3D verts[4];
    float* tmp;
    tmp = Vertices[0].m_Position;
    verts[0] = QVector3D(tmp[0], tmp[1], tmp[2]);

    tmp = Vertices[1].m_Position;
    verts[1] = QVector3D(tmp[0], tmp[1], tmp[2]);

    tmp = Vertices[2].m_Position;
    verts[2] = QVector3D(tmp[0], tmp[1], tmp[2]);

    tmp = Vertices[3].m_Position;
    verts[3] = QVector3D(tmp[0], tmp[1], tmp[2]);

    printf("Before===\n");
    for(int i=0 ;i<4 ; ++i)
    {
        printf("  vertex %d %f %f %f\n", i+1, verts[i].x(), verts[i].y(), verts[i].z());
        verts[i] = matrix * verts[i];
    }



    printf("After===\n");
    for(int i=0 ;i<4 ; ++i)
    {
        printf("  vertex %d %f %f %f\n", i+1, verts[i].x(), verts[i].y(), verts[i].z());

    }



}


void textest::draw() {

    myTex->Bind(GL_TEXTURE0);
    glBindVertexArray(m_VAO);
    glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, (void*)0);
    glBindVertexArray(0);

}
