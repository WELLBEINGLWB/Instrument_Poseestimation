#pragma once
// glew
#include <GL/glew.h>

#include <iostream>
#include <map>
#include <vector>
// assimp
#include <assimp/Importer.hpp>      // C++ importer interface
#include <assimp/scene.h>       // Output data structure
#include <assimp/postprocess.h> // Post processing flags
// Eigen
#include <Eigen/Core>
#include <Eigen/Dense>
// std
#include <string>
// cuda
#include <vector_types.h>

// image magick
#define MAGICKCORE_EXCLUDE_DEPRECATED
#include <Magick++.h>

#define INVALID_OGL_VALUE 0xffffffff
#define SAFE_DELETE(p) if (p) { delete p; p = NULL; }

using namespace Eigen;
using namespace std;

struct Vertex {
    float3 m_pos;
    float2 m_tex;
    float3 m_normal;
};

class Texture {
public:
    Texture(GLenum TextureTarget, const std::string &FileName);

    bool Load();

    void Bind(GLenum TextureUnit);

private:
    std::string m_fileName;
    GLenum m_textureTarget;
    GLuint m_textureObj;
    Magick::Image m_image;
    Magick::Blob m_blob;
};

class Mesh {
public:
    Mesh();

    ~Mesh();

    bool LoadMesh(const std::string &Filename);
    bool LoadMesh(const std::string &Filename, VectorXf &pose);

    void Render();

    string name = "default name";

    Matrix4f ModelMatrix;

    std::vector<Vertex> Vertices;

private:
    bool InitFromScene(const aiScene *pScene, const std::string &Filename);

    void InitMesh(unsigned int Index, const aiMesh *paiMesh);

    bool InitMaterials(const aiScene *pScene, const std::string &Filename);

    void Clear();

#define INVALID_MATERIAL 0xFFFFFFFF

    struct MeshEntry {
        MeshEntry();

        ~MeshEntry();

        void Init(const std::vector<Vertex> &Vertices,
                  const std::vector<unsigned int> &Indices);

        GLuint VB;
        GLuint IB;
        unsigned long NumIndices;
        unsigned long NumVertices;
        unsigned int MaterialIndex;
    };

public:
    std::vector<MeshEntry> m_Entries;
    std::vector<Texture *> m_Textures;
};
