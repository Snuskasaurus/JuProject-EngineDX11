#include "Math.h"

#include <cmath>
#include <cassert>

//----------------------------------------------------------------------------------------------------------------------
float Math::Square(const float _f)
{
    return sqrtf(_f);
}
//----------------------------------------------------------------------------------------------------------------------
float Math::Sin(const float _f)
{
    return sinf(_f);
}
//----------------------------------------------------------------------------------------------------------------------
float Math::Cos(const float _f)
{
    return cosf(_f);
}

float Math::Abs(const float _f)
{
    return fabsf(_f);
}

//----------------------------------------------------------------------------------------------------------------------
const TMatrix4f TMatrix4f::Identity =
{
    { 1.0f, 0.0f, 0.0f, 0.0f },
    { 0.0f, 1.0f, 0.0f, 0.0f },
    { 0.0f, 0.0f, 1.0f, 0.0f },
    { 0.0f, 0.0f, 0.0f, 1.0f },
};
TMatrix4f TMatrix4f::FromDirectXMatrix(const DirectX::XMMATRIX _matrix)
{
#define DX_GET_X(v) DirectX::XMVectorGetX(_matrix.r[v])
#define DX_GET_Y(v) DirectX::XMVectorGetY(_matrix.r[v])
#define DX_GET_Z(v) DirectX::XMVectorGetZ(_matrix.r[v])
#define DX_GET_W(v) DirectX::XMVectorGetW(_matrix.r[v])
    return
	{
		DX_GET_X(0),   DX_GET_Y(0),   DX_GET_Z(0),   DX_GET_W(0),
		DX_GET_X(1),   DX_GET_Y(1),   DX_GET_Z(1),   DX_GET_W(1),
		DX_GET_X(2),   DX_GET_Y(2),   DX_GET_Z(2),   DX_GET_W(2),
		DX_GET_X(3),   DX_GET_Y(3),   DX_GET_Z(3),   DX_GET_W(3),
	};
#undef DX_GET_X
#undef DX_GET_Y
#undef DX_GET_Z
#undef DX_GET_W
}
//----------------------------------------------------------------------------------------------------------------------
bool TMatrix4f::CompareMatrixToDirectXMatrix(const TMatrix4f& _m1, DirectX::XMMATRIX _m2)
{
    TMatrix4f MatrixDirectX = FromDirectXMatrix(_m2);
    TMatrix4f MatrixDirectXTransposed = Transpose(MatrixDirectX);
    return _m1 == MatrixDirectXTransposed;
}
//----------------------------------------------------------------------------------------------------------------------
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
//----------------------------------------------------------------------------------------------------------------------
TMatrix4f TMatrix4f::MatrixRotationX(float _angle)
{
    return
    {
        1.0f,            0.0f,                  0.0f,                   0.0f,
        0.0f,            Math::Cos(_angle),    -Math::Sin(_angle),   0.0f,
        0.0f,            Math::Sin(_angle),   Math::Cos(_angle),     0.0f,
        0.0f,            0.0f,                  0.0f,               1.0f,
    };
}
//----------------------------------------------------------------------------------------------------------------------
TMatrix4f TMatrix4f::MatrixRotationY(float _angle)
{
    return
    {
        Math::Cos(_angle),      0.0f,          Math::Sin(_angle),    0.0f,
        0.0f,                   1.0f,          0.0f,                 0.0f,
        -Math::Sin(_angle),    0.0f,          Math::Cos(_angle),     0.0f,
        0.0f,                 0.0f,          0.0f,                  1.0f,
    };
}
//----------------------------------------------------------------------------------------------------------------------
TMatrix4f TMatrix4f::MatrixRotationZ(float _angle)
{
    return
    {
		Math::Cos(_angle),   -Math::Sin(_angle),     0.0f,           0.0f,
		Math::Sin(_angle),   Math::Cos(_angle),       0.0f,           0.0f,
		0.0f,               0.0f,                   1.0f,           0.0f,
		0.0f,               0.0f,                   0.0f,           1.0f,
    };
}
//----------------------------------------------------------------------------------------------------------------------
TMatrix4f TMatrix4f::MatrixScale(float _scale)
{
    return
    {                                                                  
		_scale,           0.0f,         0.0f,           0.0f ,
		0.0f,            _scale,        0.0f,           0.0f ,
        0.0f,            0.0f,          _scale,         0.0f ,
        0.0f,            0.0f,          0.0f,           1.0f ,
    };
}
//----------------------------------------------------------------------------------------------------------------------
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
//----------------------------------------------------------------------------------------------------------------------
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
//----------------------------------------------------------------------------------------------------------------------
TMatrix4f TMatrix4f::MatrixPerspectiveFovRH(float _fovAngleY, float _aspectRatio, float _nearZ, float _farZ)
{
    return
	{
		0.0f,            0.0f,           0.0f,          0.0f,
		0.0f,            0.0f,           0.0f,          0.0f,
		0.0f,            0.0f,           0.0f,          0.0f,
		0.0f,            0.0f,           0.0f,          1.0f,
	};
}
//----------------------------------------------------------------------------------------------------------------------
