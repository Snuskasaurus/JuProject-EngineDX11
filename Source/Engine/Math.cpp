#include "Math.h"
#include <cmath>

//---------------------------------------------------------------------------------------------------------------------------------------------------------
float TVector2f::Dot(TVector2f v1, TVector2f v2)
{
    return v1.x * v2.x + v1.y * v2.y;
}
//---------------------------------------------------------------------------------------------------------------------------------------------------------
float TVector3f::Dot(TVector3f v1, TVector3f v2)
{
    return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}
//---------------------------------------------------------------------------------------------------------------------------------------------------------
float TVector4f::Dot(TVector4f v1, TVector4f v2)
{
    return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z + v1.w * v2.w;
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
TMatrix4f TMatrix4f::MatrixTranslation(TVector3f translation)
{
    return
    {
        1.0f,            0.0f,           0.0f,          translation.x,
        0.0f,            1.0f,           0.0f,          translation.y,
        0.0f,            0.0f,           1.0f,          translation.z,
        0.0f,            0.0f,           0.0f,          1.0f,
    };
}
//---------------------------------------------------------------------------------------------------------------------------------------------------------
TMatrix4f TMatrix4f::MatrixRotationX(float angle)
{
    return
    {
        1.0f,            0.0f,          0.0f,           0.0f,
        0.0f,            cos(angle),    -sinf(angle),   0.0f,
        0.0f,            sinf(angle),   cos(angle),     0.0f,
        0.0f,            0.0f,          0.0f,           1.0f,
    };
}
//---------------------------------------------------------------------------------------------------------------------------------------------------------
TMatrix4f TMatrix4f::MatrixRotationY(float angle)
{
    return
    {
        cos(angle),      0.0f,          sinf(angle),    0.0f,
        0.0f,            1.0f,          0.0f,           0.0f,
        -sinf(angle),    0.0f,          cos(angle),     0.0f,
        0.0f,            0.0f,          1.0f,           0.0f,
    };
}
//---------------------------------------------------------------------------------------------------------------------------------------------------------
TMatrix4f TMatrix4f::MatrixRotationZ(float angle)
{
    return
    {
        cos(angle),      -sinf(angle),  0.0f,           0.0f,
        sinf(angle),     cos(angle),    0.0f,           0.0f,
        0.0f,            0.0f,          1.0f,           0.0f,
        0.0f,            0.0f,          0.0f,           1.0f,
    };
}
//---------------------------------------------------------------------------------------------------------------------------------------------------------
TMatrix4f TMatrix4f::MatrixScale(float scale)
{
    return
    {                                                                  
        scale,           0.0f,          0.0f,           0.0f ,
        0.0f,            scale,         0.0f,           0.0f ,
        0.0f,            0.0f,          scale,          0.0f ,
        0.0f,            0.0f,          0.0f,           1.0f ,
    };
}
//---------------------------------------------------------------------------------------------------------------------------------------------------------
TMatrix4f TMatrix4f::MatrixScaleUniform(float scale)
{
    return
    {                                                                  
        0.0f,            0.0f,          0.0f,           0.0f ,
        0.0f,            0.0f,          0.0f,           0.0f ,
        0.0f,            0.0f,          0.0f,           0.0f ,
        0.0f,            0.0f,          0.0f,           1.0f / scale ,
    };
}
//---------------------------------------------------------------------------------------------------------------------------------------------------------
TMatrix4f TMatrix4f::Transpose(const TMatrix4f& m)
{
    return
    {
        m.x.x,  m.y.x,  m.z.x,  m.w.x,
        m.x.y,  m.y.y,  m.z.y,  m.w.y,
        m.x.z,  m.y.z,  m.z.z,  m.w.z,
        m.x.w,  m.y.w,  m.z.w,  m.w.w,
    };
}
//---------------------------------------------------------------------------------------------------------------------------------------------------------
TMatrix4f TMatrix4f::Multiply(const TMatrix4f& m1, const TMatrix4f& m2)
{
    TMatrix4f tm2 = TMatrix4f::Transpose(m2);
    return
    {
        TVector4f::Dot(m1.x, tm2.x),    TVector4f::Dot(m1.x, tm2.y),    TVector4f::Dot(m1.x, tm2.z),    TVector4f::Dot(m1.x, tm2.w),
        TVector4f::Dot(m1.y, tm2.x),    TVector4f::Dot(m1.y, tm2.y),    TVector4f::Dot(m1.y, tm2.z),    TVector4f::Dot(m1.y, tm2.w),
        TVector4f::Dot(m1.z, tm2.x),    TVector4f::Dot(m1.z, tm2.y),    TVector4f::Dot(m1.z, tm2.z),    TVector4f::Dot(m1.z, tm2.w),
        TVector4f::Dot(m1.w, tm2.x),    TVector4f::Dot(m1.w, tm2.y),    TVector4f::Dot(m1.w, tm2.z),    TVector4f::Dot(m1.w, tm2.w),
    };
}
