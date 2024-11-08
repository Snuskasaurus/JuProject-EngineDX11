#include "MeshImporter.h"

// Highly inspired by http://www.opengl-tutorial.org/beginners-tutorials/tutorial-7-model-loading/

#define TRIGGER_ERROR() assert(false) // TODO Julien Rogel (06/11/2024): Replace with MessageBox

#include <assert.h>
#include <cstdio>
#include <cstring>

#define MAX_FACE_ELEMENT 4096

struct SFaceElement
{
    TVertexIndex Geometry = 0;
    TVertexIndex Texture = 0;
    TVertexIndex Normal = 0;
};

bool TryToImportMeshInfoFromOBJFile(_In_ const wchar_t* _fileName, _Out_ SMeshInfo* MeshInfo)
{
    FILE* fileStream = nullptr;

    const errno_t resultFOpen = _wfopen_s(&fileStream, _fileName, L"r");
    if(resultFOpen != 0 || fileStream == nullptr)
    {
        TRIGGER_ERROR(); // Failed to open file
        return false;
    }
    
    int nbVertexPos = 0;
    float3 tempVertexPos[MAX_VERTEX_BUFFER_VERTICES] = {};

    int nbVertexNorm = 0;
    float3 tempVertexNorm[MAX_VERTEX_BUFFER_VERTICES] = {};
    
    int nbVertexTex = 0;
    float2 tempVertexTex[MAX_VERTEX_BUFFER_VERTICES] = {};

    SFaceElement tempFaces[MAX_FACE_ELEMENT] = {};
    int nbFaces = 0;

    bool ReadingFile = true;
    while(ReadingFile)
    {
        char lineHeader[128] = {};
        const int resultScanfVertexStart = fscanf_s(fileStream, "%s", lineHeader, (unsigned int)sizeof(lineHeader));
        if (resultScanfVertexStart == EOF)
        {
            ReadingFile = false; // EOF = End Of File. Quit the loop.
        }
        
        if (strcmp(lineHeader, "v") == 0) // Read vertex position
        {
            const int matches = fscanf_s(fileStream, "%f %f %f\n",
                &tempVertexPos[nbVertexPos].x,
                &tempVertexPos[nbVertexPos].y,
                &tempVertexPos[nbVertexPos].z);
            nbVertexPos++;
            if (nbVertexPos >= MAX_VERTEX_BUFFER_VERTICES)
            {
                TRIGGER_ERROR();
                return false;
            }
        }
        else if (strcmp(lineHeader, "vn") == 0) // Read vertex normals
        {
            if (nbVertexNorm + 1 > MAX_VERTEX_BUFFER_VERTICES)
            {
                TRIGGER_ERROR();
                return false;
            }
            
            const int matches = fscanf_s(fileStream, "%f %f\n",
                &tempVertexNorm[nbVertexNorm].x,
                &tempVertexNorm[nbVertexNorm].y);
            nbVertexNorm++;
        }
        else if (strcmp(lineHeader, "vt") == 0) // Read vertex texture coordinates
        {
            if (nbVertexTex + 1 > MAX_VERTEX_BUFFER_VERTICES)
            {
                TRIGGER_ERROR();
                return false;
            }
            
            const int matches = fscanf_s(fileStream, "%f %f\n",
                &tempVertexTex[nbVertexTex].x,
                &tempVertexTex[nbVertexTex].y);
            nbVertexTex++;
        }
        else if (strcmp(lineHeader, "f") == 0) // Read faces informations
        {
            if (nbFaces + 3 > MAX_INDEX_BUFFER_INDEXES)
            {
                TRIGGER_ERROR();
                return false;
            }
            int matches = fscanf_s(fileStream, "%hu/%hu/%hu %hu/%hu/%hu %hu/%hu/%hu\n",
                &tempFaces[nbFaces ].Geometry,      &tempFaces[nbFaces].Texture,        &tempFaces[nbFaces].Normal,
                &tempFaces[nbFaces + 1].Geometry,   &tempFaces[nbFaces + 1].Texture,    &tempFaces[nbFaces + 1].Normal,
                &tempFaces[nbFaces + 2].Geometry,   &tempFaces[nbFaces + 2].Texture,    &tempFaces[nbFaces + 2].Normal);
            if (matches != 9)
            {
                TRIGGER_ERROR(); // TODO Julien Rogel (06/11/2024): Need to re-write this parser if it happens
                return false;
            }
            nbFaces += 3;
        }
    }
    int SuccessFClose = fclose(fileStream);
    if (SuccessFClose)
    {
        TRIGGER_ERROR();
        return false;
    }
    
    for (int i = 0; i < nbFaces; ++i)
    {
        const int iVertexPos = tempFaces[i].Geometry;
        assert(iVertexPos <= nbVertexPos);
        MeshInfo->VertexBuffer.Vertices[i].vp = tempVertexPos[iVertexPos];

		const int iVertexTex = tempFaces[i].Texture;
		assert(iVertexTex <= nbVertexTex);
        MeshInfo->VertexBuffer.Vertices[i].vt = tempVertexTex[iVertexTex];

		const int iVertexNorm = tempFaces[i].Normal;
		assert(iVertexNorm <= nbVertexNorm);
        MeshInfo->VertexBuffer.Vertices[i].vn = tempVertexNorm[iVertexNorm];

		MeshInfo->IndexBuffer.Indexes[i] = static_cast<TVertexIndex>(i);
    }
    MeshInfo->nbVertexBuffer = nbFaces;
    MeshInfo->nbIndexBuffer = nbFaces;
    
    return true;
}
