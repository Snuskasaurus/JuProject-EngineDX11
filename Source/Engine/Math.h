#pragma once

#include <DirectXMath.h>

//---------------------------------------------------------------------------------------------------------------------------------------------------------
struct TVector2f
{
    float x = 0.0f;
    float y = 0.0f;

    __forceinline static float Dot(const TVector2f&  v1, const TVector2f&  v2)
    {
        return v1.x * v2.x + v1.y * v2.y;
    }
};
//---------------------------------------------------------------------------------------------------------------------------------------------------------
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
//---------------------------------------------------------------------------------------------------------------------------------------------------------
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
//---------------------------------------------------------------------------------------------------------------------------------------------------------
struct alignas(16) TMatrix4f
{
    TVector4f x;
    TVector4f y;
    TVector4f z;
    TVector4f w;

    static const TMatrix4f Identity;

    __forceinline static TMatrix4f MatrixTranslation(TVector3f translation);
    __forceinline static TMatrix4f MatrixRotationX(float angle); 
    __forceinline static TMatrix4f MatrixRotationY(float angle); 
    __forceinline static TMatrix4f MatrixRotationZ(float angle); 
    __forceinline static TMatrix4f MatrixScale(float scale);
    __forceinline static TMatrix4f MatrixScaleUniform(float scale);
    __forceinline static TMatrix4f MatrixLookAtRH(TVector3f cameraPosition, TVector3f lookAtPosition, TVector3f up);

    __forceinline static TMatrix4f Transpose(const TMatrix4f& m)
    {
        return
        {
           m.x.x,  m.y.x,  m.z.x,  m.w.x,
           m.x.y,  m.y.y,  m.z.y,  m.w.y,
           m.x.z,  m.y.z,  m.z.z,  m.w.z,
           m.x.w,  m.y.w,  m.z.w,  m.w.w,
       };
    }
    
    __forceinline TMatrix4f& operator*=(const TMatrix4f& rhs)
    {
        const TMatrix4f m1 = *this;
        const TMatrix4f m2 = TMatrix4f::Transpose(rhs);
        this->x = { TVector4f::Dot(m1.x, m2.x),    TVector4f::Dot(m1.x, m2.y),    TVector4f::Dot(m1.x, m2.z),    TVector4f::Dot(m1.x, m2.w) };
        this->y = { TVector4f::Dot(m1.y, m2.x),    TVector4f::Dot(m1.y, m2.y),    TVector4f::Dot(m1.y, m2.z),    TVector4f::Dot(m1.y, m2.w) };
        this->z = { TVector4f::Dot(m1.z, m2.x),    TVector4f::Dot(m1.z, m2.y),    TVector4f::Dot(m1.z, m2.z),    TVector4f::Dot(m1.z, m2.w) };
        this->w = { TVector4f::Dot(m1.w, m2.x),    TVector4f::Dot(m1.w, m2.y),    TVector4f::Dot(m1.w, m2.z),    TVector4f::Dot(m1.w, m2.w) };
        return *this;
    }
    __forceinline friend TMatrix4f operator*(TMatrix4f lhs, const TMatrix4f& rhs)
    {
        lhs *= rhs;
        return lhs;
    }
};
//---------------------------------------------------------------------------------------------------------------------------------------------------------
