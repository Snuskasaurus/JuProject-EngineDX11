#pragma once

#include <DirectXMath.h>

struct TVector2f
{
    float x = 0.0f;
    float y = 0.0f;
};

struct TVector3f
{
    float x = 0.0f;
    float y = 0.0f;
    float z = 0.0f;
};

struct TVector4f
{
    float x = 0.0f;
    float y = 0.0f;
    float z = 0.0f;
    float w = 0.0f;
};

struct alignas(16) TMatrix4f
{
    TVector4f x;
    TVector4f y;
    TVector4f z;
    TVector4f w;
    
    static const TMatrix4f Identity;

    static TMatrix4f MatrixTranslation(TVector3f translation);
    static TMatrix4f MatrixRotationX(float x); 
    static TMatrix4f MatrixRotationY(float y); 
    static TMatrix4f MatrixRotationZ(float z); 
    static TMatrix4f MatrixScale(float scale);
    
    static inline TMatrix4f Transpose(const TMatrix4f _matrix);
};