#ifndef MESH_H
#define MESH_H

#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>
#include "pickingfbo.h"
#include "mathbase.h"


using namespace std;

class Texture;

class Mesh
{
    struct Vertex_VT
    {
        float m_Position[3]; // 頂點位置
        float m_Texcoord[2]; // 貼圖座標
        float m_Normal[3];   // Normal Coordinates.

        Vertex_VT() {}

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

public:
    Mesh();
    ~Mesh();
    bool LoadMesh(const std::string& FileName, QObject* parent);
    void Render();
    // render index
    void RenderMouseIndex();
    // render triangle
    void RenderTriangle(PickingFBO::Pixelinfo);

private:
    bool InitFromScene(const aiScene* pScene, const std::string& Filename);
    bool InitMaterials(const aiScene* pScene, const std::string& Filename);
    void InitMesh(const aiMesh* paiMesh,
                       vector<Vector3f>& Positions,
                       vector<Vector3f>& Normals,                  
                       vector<Vector2f>& TexCoords,
                       vector<unsigned int>& Indices);

#define INDEX_BUFFER 0
#define POS_VB       1
#define NORMAL_VB    2
#define TEXCOORD_VB  3

    GLuint VAO;
    GLuint m_Buffers[4];

    struct MeshEntry {
        MeshEntry();
        ~MeshEntry();
        unsigned int NumIndices;
        unsigned int BaseIndex;
        unsigned int BaseVertex;
        unsigned int MaterialIndex;

    };

    std::vector<Vertex_VT> vertices;
    std::vector<unsigned int> indices;
    std::vector<MeshEntry> m_Entries;
    std::vector<Texture*> m_Textures;

};

#endif // MESH_H
