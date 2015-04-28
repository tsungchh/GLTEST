#include "mesh.h"
#include "MYMACRO.h"
#include "texture.h"

Mesh::MeshEntry::MeshEntry() {

    NumIndices = 0;
    BaseIndex = 0;
    BaseVertex = 0;
    MaterialIndex = INVALID_MATERIAL;
}

Mesh::MeshEntry::~MeshEntry() {

}

Mesh::Mesh()
{
    ZERO_MEM(m_Buffers);
    VAO = 0;
}

Mesh::~Mesh()
{
    if(VAO != 0) {
        glDeleteVertexArrays(1, &VAO);
    }

    if(m_Buffers[0]!=0) {
        glDeleteBuffers(ARRAY_SIZE_IN_ELEMENTS(m_Buffers), m_Buffers);
    }
}


bool Mesh::LoadMesh(const std::string &Filename, QObject* parent) {


    //Create VAO
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    //Create VBOs
    glGenBuffers(ARRAY_SIZE_IN_ELEMENTS(m_Buffers), m_Buffers);

    bool Ret = false;
    Assimp::Importer Importer;

    const aiScene* pScene = Importer.ReadFile(Filename.c_str(), aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs);

    if (pScene) {
        Ret = InitFromScene(pScene, Filename);
    }else {
        printf("Error parsing '%s': '%s'\n", Filename.c_str(), Importer.GetErrorString());
    }
    DEBUG_GL();

    // Make sure the VAO is not changed from the outside
    glBindVertexArray(0);   

    return Ret;

}

// render index
void Mesh::RenderMouseIndex() {

}

// render triangle
void Mesh::RenderTriangle(PickingFBO::Pixelinfo) {

}

// normal render
void Mesh::Render() {

    glBindVertexArray(VAO);
    DEBUG_GL();

    for(unsigned int i=0; i<m_Entries.size(); ++i) {

        // bind texture;
        const unsigned int MaterialIndex = m_Entries[i].MaterialIndex;
        assert(MaterialIndex < m_Textures.size());  
        DEBUG_GL();

        if(m_Textures[MaterialIndex]) {
            m_Textures[MaterialIndex]->Bind(GL_TEXTURE0);
        }

        DEBUG_GL();

        glDrawElementsBaseVertex(GL_TRIANGLES, m_Entries[i].NumIndices,
                                 GL_UNSIGNED_INT, (void *)(sizeof(unsigned int)*m_Entries[i].BaseIndex),
                                 m_Entries[i].BaseVertex);

        //glDrawElements(GL_TRIANGLES, m_Entries[i].NumIndices, GL_UNSIGNED_INT, 0);
        DEBUG_GL();
    }

    glBindVertexArray(0);

}


bool Mesh::InitFromScene(const aiScene* pScene, const std::string& Filename){

    m_Entries.resize(pScene->mNumMeshes);
    m_Textures.resize(pScene->mNumMaterials);

    vector<Vector3f> Positions;
    vector<Vector3f> Normals;
    vector<Vector2f> TexCoords;
    std::vector<unsigned int> Indices;

    unsigned int NumVertices = 0;
    unsigned int NumIndices = 0;
    for(unsigned int i=0; i<m_Entries.size(); ++i) {

        m_Entries[i].MaterialIndex = pScene->mMeshes[i]->mMaterialIndex;
        m_Entries[i].NumIndices = pScene->mMeshes[i]->mNumFaces * 3;
        m_Entries[i].BaseVertex = NumVertices;
        m_Entries[i].BaseIndex  = NumIndices;

        NumVertices += pScene->mMeshes[i]->mNumVertices;
        NumIndices  += m_Entries[i].NumIndices;
    }

    Positions.reserve(NumVertices);
    Normals.reserve(NumVertices);
    Indices.reserve(NumIndices);
    TexCoords.reserve(NumVertices);



    // Initialize the meshes in the scene one by one
    for (unsigned int i = 0 ; i < m_Entries.size() ; i++) {
        const aiMesh* paiMesh = pScene->mMeshes[i];
        InitMesh(paiMesh, Positions, Normals, TexCoords, Indices);
    }

    if (!InitMaterials(pScene, Filename)) {
        return false;
    }

    DEBUG_GL();

    glBindBuffer(GL_ARRAY_BUFFER, m_Buffers[POS_VB]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Positions[0]) * Positions.size(), &Positions[0], GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);    


    DEBUG_GL();
    glBindBuffer(GL_ARRAY_BUFFER, m_Buffers[TEXCOORD_VB]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(TexCoords[0]) * TexCoords.size(), &TexCoords[0], GL_STATIC_DRAW);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);

    DEBUG_GL();

    glBindBuffer(GL_ARRAY_BUFFER, m_Buffers[NORMAL_VB]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Normals[0]) * Normals.size(), &Normals[0], GL_STATIC_DRAW);
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_Buffers[INDEX_BUFFER]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Indices[0]) * Indices.size(), &Indices[0], GL_STATIC_DRAW);

    return true;
}

void Mesh::InitMesh(const aiMesh* paiMesh,
                vector<Vector3f>& Positions,
                vector<Vector3f>& Normals,
                vector<Vector2f>& TexCoords,
                vector<unsigned int>& Indices) {

    const aiVector3D Zero3D(0.0f, 0.0f, 0.0f);

    for (unsigned int i = 0 ; i < paiMesh->mNumVertices ; i++) {
        const aiVector3D* pPos      = &(paiMesh->mVertices[i]);
        const aiVector3D* pNormal   = &(paiMesh->mNormals[i]);
        const aiVector3D* pTexCoord = paiMesh->HasTextureCoords(0) ? &(paiMesh->mTextureCoords[0][i]) : &Zero3D;


        Positions.push_back(Vector3f(pPos->x+1.5, pPos->y, pPos->z));
        Normals.push_back(Vector3f(pNormal->x, pNormal->y, pNormal->z));
        TexCoords.push_back(Vector2f(pTexCoord->x, pTexCoord->y));

    }

    for (unsigned int i = 0 ; i < paiMesh->mNumFaces ; i++) {
        const aiFace& Face = paiMesh->mFaces[i];
        assert(Face.mNumIndices == 3);
        Indices.push_back(Face.mIndices[0]);
        Indices.push_back(Face.mIndices[1]);
        Indices.push_back(Face.mIndices[2]);
    }

}

bool Mesh::InitMaterials(const aiScene* pScene, const std::string& Filename)
{
    // Extract the directory part from the file name
    std::string::size_type SlashIndex = Filename.find_last_of("/");
    std::string Dir;

    if (SlashIndex == std::string::npos) {
        Dir = ".";
    }
    else if (SlashIndex == 0) {
        Dir = "/";
    }
    else {
        Dir = Filename.substr(0, SlashIndex);
        SlashIndex = Dir.find_last_of("/");
        Dir = Dir.substr(0, SlashIndex);
    }

    bool Ret = true;

    // Initialize the materials
    for (unsigned int i = 0 ; i < pScene->mNumMaterials ; i++) {
        const aiMaterial* pMaterial = pScene->mMaterials[i];

        m_Textures[i] = NULL;

        if (pMaterial->GetTextureCount(aiTextureType_DIFFUSE) > 0) {
            aiString Path;

            if (pMaterial->GetTexture(aiTextureType_DIFFUSE, 0, &Path, NULL, NULL, NULL, NULL, NULL) == AI_SUCCESS) {
                std::string FullPath = Dir + "/images/" + Path.data;

                DEBUG_GL();
                m_Textures[i] = new Texture(GL_TEXTURE_2D, FullPath.c_str());

                DEBUG_GL();

                if (!m_Textures[i]->Load()) {
                    printf("Error loading texture '%s'\n", FullPath.c_str());
                    delete m_Textures[i];
                    m_Textures[i] = NULL;
                    Ret = false;
                }
                else {
                    printf("Loaded texture '%s'\n", FullPath.c_str());
                }
            }
        }


        DEBUG_GL();
        // Load a white texture in case the model does not include its own texture
        if (!m_Textures[i]) {
            m_Textures[i] = new Texture(GL_TEXTURE_2D, "/Users/hsutsungchun/Desktop/QTGL/GL_2/images/white.png");

            Ret = m_Textures[i]->Load();
        }

        DEBUG_GL();
    }

    return Ret;
}