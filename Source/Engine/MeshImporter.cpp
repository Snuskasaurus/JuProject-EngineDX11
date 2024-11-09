#include "MeshImporter.h"

// Highly inspired by http://www.opengl-tutorial.org/beginners-tutorials/tutorial-7-model-loading/


#define MAX_NB_V 1024
#define MAX_NB_VN 1024
#define MAX_NB_VT 4096
#define MAX_NB_F 4096

#define TRIGGER_ERROR() assert(false) // TODO Julien Rogel (06/11/2024): Replace with MessageBox

#include <assert.h>
#include <cstdio>
#include <cstring>

struct SFaceElement
{
    TVertexIndex Geometry = 0;
    TVertexIndex Texture = 0;
    TVertexIndex Normal = 0;
};


void AddToVertexBuffer(_Out_ SMeshInfo* MeshInfo, const float3 vp, const float2 vt, const float3 vn)
{
    MeshInfo->VertexBuffer.Vertices[MeshInfo->nbVertexBuffer].vp = vp;
    MeshInfo->VertexBuffer.Vertices[MeshInfo->nbVertexBuffer].vt = vt;
    MeshInfo->VertexBuffer.Vertices[MeshInfo->nbVertexBuffer].vn = vn;
    
    MeshInfo->nbVertexBuffer++;
}

void AddToIndexBuffer(_Out_ SMeshInfo* MeshInfo, TVertexIndex Index)
{
    MeshInfo->IndexBuffer.Indexes[MeshInfo->nbIndexBuffer] = Index;
    MeshInfo->nbIndexBuffer++;
}

bool TryToImportMeshInfoFromOBJFile(_In_ const wchar_t* _fileName, _Out_ SMeshInfo* MeshInfo)
{
    FILE* fileStream = nullptr;

    const errno_t resultFOpen = _wfopen_s(&fileStream, _fileName, L"r");
    if(resultFOpen != 0 || fileStream == nullptr)
    {
        TRIGGER_ERROR(); // Failed to open file
        return false;
    }
    
    int countV = 0;
    float3 arrayV[MAX_NB_V] = {};
    
    int countVN = 0;
    float3 arrayVN[MAX_NB_VN] = {};
    
    int countVT = 0;
    float2 arrayVT[MAX_NB_VT] = {};
    
    int countF = 0;
    SFaceElement arrayF[MAX_NB_F] = {};
    
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
                &arrayV[countV].x,
                &arrayV[countV].y,
                &arrayV[countV].z);
            arrayV[countV].z = arrayV[countV].z * -1.0f;

            countV++;
            assert(countV < MAX_NB_V);
        }
        else if (strcmp(lineHeader, "vn") == 0) // Read vertex normals
        {
            const int matches = fscanf_s(fileStream, "%f %f %f\n",
                &arrayVN[countVN].x,
                &arrayVN[countVN].y,
                &arrayVN[countVN].z);
            arrayVN[countVN].z = arrayVN[countVN].z * -1.0f;

            countVN++;
            assert(countVN < MAX_NB_VN);
        }
        else if (strcmp(lineHeader, "vt") == 0) // Read vertex texture coordinates
        {
            const int matches = fscanf_s(fileStream, "%f %f\n",
                &arrayVT[countVT].y,
                &arrayVT[countVT].x);
            arrayVT[countVT].y = 1.0f - arrayVT[countVT].y;

            countVT++;
            assert(countVT < MAX_NB_VT);
        }
        else if (strcmp(lineHeader, "f") == 0) // Read faces informations
        {
            const int matches = fscanf_s(fileStream, "%hu/%hu/%hu %hu/%hu/%hu %hu/%hu/%hu\n",
                  &arrayF[countF + 2].Geometry, &arrayF[countF + 2].Texture, &arrayF[countF + 2].Normal,
                  &arrayF[countF + 1].Geometry, &arrayF[countF + 1].Texture, &arrayF[countF + 1].Normal,
                  &arrayF[countF + 0].Geometry, &arrayF[countF + 0].Texture, &arrayF[countF + 0].Normal);

            countF += 3;
            assert(countF < MAX_NB_F);
            
            if (matches != 9)
            {
                TRIGGER_ERROR(); // TODO Julien Rogel (06/11/2024): Need to re-write this parser if it happens
                return false;
            }
        }
    }
    int SuccessFClose = fclose(fileStream);
    if (SuccessFClose)
    {
        TRIGGER_ERROR();
        return false;
    }

    struct SUniqueFaceElement
    {
        int VertexPos = 0;
        int VertexTex = 0;
        int VertexNorm = 0;
        bool IsSame(int InVertexPos, int InVertexTex, int InVertexNorm) const { return InVertexPos == VertexPos && InVertexTex == VertexTex && InVertexNorm == VertexNorm; }
    };
    SUniqueFaceElement arrayUniqueF[MAX_NB_F] = {};
    
    int LastVertexIndex = 0;
    for (int iFace = 0; iFace < countF; ++iFace)
    {
        const int iVertexPos = arrayF[iFace].Geometry - 1;
        assert(iVertexPos < countV);
        
		const int iVertexTex = arrayF[iFace].Texture - 1;
		assert(iVertexTex < countVT);
        
		const int iVertexNorm = arrayF[iFace].Normal - 1;
		assert(iVertexNorm < countVN);

        bool AllReadyExist = false;
        for (int iCheck = 0; iCheck <= LastVertexIndex; ++iCheck)
        {
            if (arrayUniqueF[iCheck].IsSame(iVertexPos, iVertexTex, iVertexNorm) == true)
            {
                AddToIndexBuffer(MeshInfo, static_cast<TVertexIndex>(iCheck));
                AllReadyExist = true;
                break;
            }
        }
        if (AllReadyExist == false)
        {
            AddToVertexBuffer(MeshInfo, arrayV[iVertexPos], arrayVT[iVertexTex], arrayVN[iVertexNorm]);
            arrayUniqueF[LastVertexIndex] = { iVertexPos, iVertexTex, iVertexNorm };
            AddToIndexBuffer(MeshInfo, static_cast<TVertexIndex>(LastVertexIndex));
            LastVertexIndex++;
        }
    }
    
    return true;
}