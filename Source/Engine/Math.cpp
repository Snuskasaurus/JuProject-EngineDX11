#include "Math.h"

#include <cmath>
#include <cassert>

//---------------------------------------------------------------------------------------------------------------------------------------------------------
float Math::Square(const float _f)
{
    return sqrtf(_f);
}
//---------------------------------------------------------------------------------------------------------------------------------------------------------
float Math::Sin(const float _f)
{
    return sinf(_f);
}
//---------------------------------------------------------------------------------------------------------------------------------------------------------
float Math::Cos(const float _f)
{
    return cosf(_f);
}
//---------------------------------------------------------------------------------------------------------------------------------------------------------
const TMatrix4f TMatrix4f::Identity =
{
    { 1.0f, 0.0f, 0.0f, 0.0f },
    { 0.0f, 1.0f, 0.0f, 0.0f },
    { 0.0f, 0.0f, 1.0f, 0.0f },
    { 0.0f, 0.0f, 0.0f, 1.0f },
};
//---------------------------------------------------------------------------------------------------------------------------------------------------------
TMatrix4f TMatrix4f::MatrixTranslation(const TVector3f& _translation)
{
    return
    {
        1.0f,            0.0f,           0.0f,          _translation.x,
        0.0f,            1.0f,           0.0f,          _translation.y,
        0.0f,            0.0f,           1.0f,          _translation.z,
        0.0f,            0.0f,           0.0f,          1.0f,
    };
}
//---------------------------------------------------------------------------------------------------------------------------------------------------------
TMatrix4f TMatrix4f::MatrixRotationX(float _angle)
{
    return
    {
        1.0f,            0.0f,          0.0f,           0.0f,
        0.0f,            cos(_angle),    -sinf(_angle),   0.0f,
        0.0f,            sinf(_angle),   cos(_angle),     0.0f,
        0.0f,            0.0f,          0.0f,           1.0f,
    };
}
//---------------------------------------------------------------------------------------------------------------------------------------------------------
TMatrix4f TMatrix4f::MatrixRotationY(float _angle)
{
    return
    {
        cos(_angle),      0.0f,          sinf(_angle),    0.0f,
        0.0f,            1.0f,          0.0f,           0.0f,
        -sinf(_angle),    0.0f,          cos(_angle),     0.0f,
        0.0f,            0.0f,          1.0f,           0.0f,
    };
}
//---------------------------------------------------------------------------------------------------------------------------------------------------------
TMatrix4f TMatrix4f::MatrixRotationZ(float _angle)
{
    return
    {
        cos(_angle),      -sinf(_angle),  0.0f,           0.0f,
        sinf(_angle),     cos(_angle),    0.0f,           0.0f,
        0.0f,            0.0f,          1.0f,           0.0f,
        0.0f,            0.0f,          0.0f,           1.0f,
    };
}
//---------------------------------------------------------------------------------------------------------------------------------------------------------
TMatrix4f TMatrix4f::MatrixScale(float _scale)
{
    return
    {                                                                  
        _scale,           0.0f,          0.0f,           0.0f ,
        0.0f,            _scale,         0.0f,           0.0f ,
        0.0f,            0.0f,          _scale,          0.0f ,
        0.0f,            0.0f,          0.0f,           1.0f ,
    };
}
//---------------------------------------------------------------------------------------------------------------------------------------------------------
TMatrix4f TMatrix4f::MatrixScaleUniform(float _scale)
{
    return
    {                                                                  
        0.0f,            0.0f,          0.0f,           0.0f ,
        0.0f,            0.0f,          0.0f,           0.0f ,
        0.0f,            0.0f,          0.0f,           0.0f ,
        0.0f,            0.0f,          0.0f,           1.0f / _scale ,
    };
}

TMatrix4f TMatrix4f::MatrixLookAtRH(const TVector3f& _cameraPosition, const TVector3f& _lookAtPosition, const TVector3f& _up)
{
    TVector3f t = _cameraPosition;
    TVector3f v = TVector3f::Normalize(_cameraPosition - _lookAtPosition);
    TVector3f r = -TVector3f::Normalize(TVector3f::Cross(v, _up)); // Right vector
    TVector3f u = TVector3f::Cross(v, r); // Guarantee that we have a vector pointing up

    assert(v.IsNormalized());
    assert(r.IsNormalized());
    assert(u.IsNormalized());

    return
    {
        r.x,            r.y,           r.z,          TVector3f::Dot(-t, r),
        u.x,            u.y,           u.z,          TVector3f::Dot(-t, u),
        v.x,            v.y,           v.z,          TVector3f::Dot(-t, v),
        0.0f,            0.0f,           0.0f,          1.0f,
    };
}
//---------------------------------------------------------------------------------------------------------------------------------------------------------