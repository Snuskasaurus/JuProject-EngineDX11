#pragma once

#include <DirectXMath.h>

struct TVector2f
{
    float x = 0.0f;
    float y = 0.0f;

    inline static float Dot(TVector2f v1, TVector2f v2);
};

struct TVector3f
{
    float x = 0.0f;
    float y = 0.0f;
    float z = 0.0f;

    inline static float Dot(TVector3f v1, TVector3f v2);
};

struct TVector4f
{
    float x = 0.0f;
    float y = 0.0f;
    float z = 0.0f;
    float w = 0.0f;

    inline static float Dot(TVector4f v1, TVector4f v2);
};

struct alignas(16) TMatrix4f
{
    TVector4f x;
    TVector4f y;
    TVector4f z;
    TVector4f w;

    static const TMatrix4f Identity;

    inline static TMatrix4f MatrixTranslation(TVector3f translation);
    inline static TMatrix4f MatrixRotationX(float x); 
    inline static TMatrix4f MatrixRotationY(float y); 
    inline static TMatrix4f MatrixRotationZ(float z); 
    inline static TMatrix4f MatrixScale(float scale);
    inline static TMatrix4f MatrixScaleUniform(float scale);

    inline static TMatrix4f Transpose(const TMatrix4f& m);
    inline static TMatrix4f Multiply(const TMatrix4f& m1, const TMatrix4f& m2);
};