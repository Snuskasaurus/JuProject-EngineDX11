#pragma once

#include <DirectXMath.h>

struct TVector2f
{
    float x = 0.0f;
    float y = 0.0f;

    __forceinline static float Dot(const TVector2f&  v1, const TVector2f&  v2)
    {
        return v1.x * v2.x + v1.y * v2.y;
    }
};

struct TVector3f
{
    float x = 0.0f;
    float y = 0.0f;
    float z = 0.0f;

    __forceinline bool IsNormalized()
    {
        float squareLength = TVector3f::SquareLength(*this);
        return squareLength <= 1.0f - FLT_EPSILON && squareLength >= 1.0f + FLT_EPSILON;
    }
    __forceinline static float Dot(const TVector3f&  v1, const TVector3f&  v2)
    {
        return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
    }
    __forceinline static TVector3f Cross(const TVector3f&  v1, const TVector3f&  v2)
    {
        return { };
    }
    __forceinline static float SquareLength(const TVector3f&  v1)
    {
        return v1.x + v1.y + v1.z;
    }
    __forceinline static float Length(const TVector3f&  v1)
    {
        return sqrtf(SquareLength(v1));
    }
    __forceinline static TVector3f Normalize(const TVector3f&  v1)
    {
        float Length = TVector3f::Length(v1);
        return {v1.x / Length, v1.y / Length, v1.z / Length };
    }
     __forceinline TVector3f operator-() const
    {
        return { -x, -y, -z };
    }
    __forceinline TVector3f& operator+=(const TVector3f& rhs)
    {
        this->x += rhs.x;
        this->y += rhs.y;
        this->z += rhs.z;
        return *this;
    }
    __forceinline TVector3f& operator-=(const TVector3f& rhs)
    {
        this->x -= rhs.x;
        this->y -= rhs.y;
        this->z -= rhs.z;
        return *this;
    }
    __forceinline friend TVector3f operator+(TVector3f lhs, const TVector3f& rhs)
    {
        lhs += rhs;
        return lhs;
    }
    __forceinline friend TVector3f operator-(TVector3f lhs, const TVector3f& rhs)
    {
        lhs += rhs;
        return lhs;
    }
};

struct TVector4f
{
    float x = 0.0f;
    float y = 0.0f;
    float z = 0.0f;
    float w = 0.0f;

    inline static float Dot(TVector4f v1, TVector4f v2)
    {
        return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z + v1.w * v2.w;
    }
};

struct alignas(16) TMatrix4f
{
    TVector4f x;
    TVector4f y;
    TVector4f z;
    TVector4f w;

    static const TMatrix4f Identity;

    inline static TMatrix4f MatrixTranslation(TVector3f translation);
    inline static TMatrix4f MatrixRotationX(float angle); 
    inline static TMatrix4f MatrixRotationY(float angle); 
    inline static TMatrix4f MatrixRotationZ(float angle); 
    inline static TMatrix4f MatrixScale(float scale);
    inline static TMatrix4f MatrixScaleUniform(float scale);
    inline static TMatrix4f MatrixLookAtRH(TVector3f CameraPosition, TVector3f LookAtPosition, TVector3f UpVector);

    inline static TMatrix4f Transpose(const TMatrix4f& m);
    inline static TMatrix4f Multiply(const TMatrix4f& m1, const TMatrix4f& m2);
};