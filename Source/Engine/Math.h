﻿#pragma once

#define FORCE_INLINE __forceinline
#define EPSILON_FLOAT 1.19209290E-07F

//---------------------------------------------------------------------------------------------------------------------------------------------------------
namespace Math // To avoid having CMath included everywhere
{
    FORCE_INLINE float Square(const float _f);
    FORCE_INLINE float Sin(const float _f);
    FORCE_INLINE float Cos(const float _f);
}
//---------------------------------------------------------------------------------------------------------------------------------------------------------
struct TVector2f
{
    float x = 0.0f;
    float y = 0.0f;

    FORCE_INLINE static float Dot(const TVector2f& _v1, const TVector2f& _v2)
    {
        return _v1.x * _v2.x + _v1.y * _v2.y;
    }
};
//---------------------------------------------------------------------------------------------------------------------------------------------------------
struct TVector3f
{
    float x = 0.0f;
    float y = 0.0f;
    float z = 0.0f;

    FORCE_INLINE bool IsNormalized()
    {
        const float squareLength = TVector3f::SquareLength(*this);
        return squareLength <= 1.0f - EPSILON_FLOAT && squareLength >= 1.0f + EPSILON_FLOAT;
    }
    FORCE_INLINE static float Dot(const TVector3f& _v1, const TVector3f& _v2)
    {
        return _v1.x * _v2.x + _v1.y * _v2.y + _v1.z * _v2.z;
    }
    FORCE_INLINE static TVector3f Cross(const TVector3f& _v1, const TVector3f& _v2)
    {
        return
        {
            _v1.y * _v2.z - _v1.z * _v2.y,
            _v1.x * _v2.z - _v1.z * _v2.x,
            _v1.x * _v2.y - _v1.y * _v2.x,
        };
    }
    FORCE_INLINE static float SquareLength(const TVector3f& _v)
    {
        return _v.x + _v.y + _v.z;
    }
    FORCE_INLINE static float Length(const TVector3f& _v)
    {
        return Math::Square(SquareLength(_v));
    }
    FORCE_INLINE static TVector3f Normalize(const TVector3f& _v)
    {
        const float length = TVector3f::Length(_v);
        return {_v.x / length, _v.y / length, _v.z / length };
    }
     FORCE_INLINE TVector3f operator-() const
    {
        return { -x, -y, -z };
    }
    FORCE_INLINE TVector3f& operator+=(const TVector3f& _v)
    {
        this->x += _v.x;
        this->y += _v.y;
        this->z += _v.z;
        return *this;
    }
    FORCE_INLINE TVector3f& operator-=(const TVector3f& _v)
    {
        this->x -= _v.x;
        this->y -= _v.y;
        this->z -= _v.z;
        return *this;
    }
    FORCE_INLINE friend TVector3f operator+(TVector3f _v1, const TVector3f& _v2)
    {
        _v1 += _v2;
        return _v1;
    }
    FORCE_INLINE friend TVector3f operator-(TVector3f _v1, const TVector3f& _v2)
    {
        _v1 += _v2;
        return _v1;
    }
};
//---------------------------------------------------------------------------------------------------------------------------------------------------------
struct TVector4f
{
    float x = 0.0f;
    float y = 0.0f;
    float z = 0.0f;
    float w = 0.0f;

    FORCE_INLINE static float Dot(TVector4f _v1, TVector4f _v2)
    {
        return _v1.x * _v2.x + _v1.y * _v2.y + _v1.z * _v2.z + _v1.w * _v2.w;
    }
};
//---------------------------------------------------------------------------------------------------------------------------------------------------------
struct alignas(16) TMatrix4f
{
    TVector4f x = { 0.0f, 0.0f, 0.0f, 0.0f };
    TVector4f y = { 0.0f, 0.0f, 0.0f, 0.0f };
    TVector4f z = { 0.0f, 0.0f, 0.0f, 0.0f };
    TVector4f w = { 0.0f, 0.0f, 0.0f, 0.0f };

    static const TMatrix4f Identity;

    FORCE_INLINE static TMatrix4f MatrixTranslation(const TVector3f& _translation);
    FORCE_INLINE static TMatrix4f MatrixRotationX(float _angle); 
    FORCE_INLINE static TMatrix4f MatrixRotationY(float _angle); 
    FORCE_INLINE static TMatrix4f MatrixRotationZ(float _angle); 
    FORCE_INLINE static TMatrix4f MatrixScale(float _scale);
    FORCE_INLINE static TMatrix4f MatrixScaleUniform(float _scale);
    FORCE_INLINE static TMatrix4f MatrixLookAtRH(const TVector3f& _cameraPosition, const TVector3f& _lookAtPosition, const TVector3f& _up);

    FORCE_INLINE static TMatrix4f Transpose(const TMatrix4f& _m)
    {
        return
        {
           _m.x.x,  _m.y.x,  _m.z.x,  _m.w.x,
           _m.x.y,  _m.y.y,  _m.z.y,  _m.w.y,
           _m.x.z,  _m.y.z,  _m.z.z,  _m.w.z,
           _m.x.w,  _m.y.w,  _m.z.w,  _m.w.w,
       };
    }
    
    FORCE_INLINE TMatrix4f& operator*=(const TMatrix4f& _m)
    {
        const TMatrix4f mt = TMatrix4f::Transpose(_m);
        this->x = { TVector4f::Dot(this->x, mt.x),    TVector4f::Dot(this->x, mt.y),    TVector4f::Dot(this->x, mt.z),    TVector4f::Dot(this->x, mt.w) };
        this->y = { TVector4f::Dot(this->y, mt.x),    TVector4f::Dot(this->y, mt.y),    TVector4f::Dot(this->y, mt.z),    TVector4f::Dot(this->y, mt.w) };
        this->z = { TVector4f::Dot(this->z, mt.x),    TVector4f::Dot(this->z, mt.y),    TVector4f::Dot(this->z, mt.z),    TVector4f::Dot(this->z, mt.w) };
        this->w = { TVector4f::Dot(this->w, mt.x),    TVector4f::Dot(this->w, mt.y),    TVector4f::Dot(this->w, mt.z),    TVector4f::Dot(this->w, mt.w) };
        return *this;
    }
    FORCE_INLINE friend TMatrix4f operator*(TMatrix4f _m1, const TMatrix4f& _m2)
    {
        _m1 *= _m2;
        return _m1;
    }
};
//---------------------------------------------------------------------------------------------------------------------------------------------------------