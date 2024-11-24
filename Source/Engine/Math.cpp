#include "Math.h"
#include <cmath>

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
TMatrix4f TMatrix4f::MatrixLookAtRH(TVector3f cameraPosition, TVector3f lookAtPosition, TVector3f up)
{
    TVector3f t = cameraPosition;
    TVector3f v = TVector3f::Normalize(cameraPosition - lookAtPosition);
    TVector3f r = -TVector3f::Normalize(TVector3f::Cross(v, up)); // Right vector
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