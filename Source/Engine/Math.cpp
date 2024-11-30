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
    TMatrix4f matrix;

    matrix.x.x = DirectX::XMVectorGetX(_matrix.r[0]);
    matrix.x.y = DirectX::XMVectorGetY(_matrix.r[0]);
    matrix.x.z = DirectX::XMVectorGetZ(_matrix.r[0]);
    matrix.x.w = DirectX::XMVectorGetW(_matrix.r[0]);
    
    matrix.y.x = DirectX::XMVectorGetX(_matrix.r[1]);
    matrix.y.y = DirectX::XMVectorGetY(_matrix.r[1]);
    matrix.y.z = DirectX::XMVectorGetZ(_matrix.r[1]);
    matrix.y.w = DirectX::XMVectorGetW(_matrix.r[1]);
    
    matrix.z.x = DirectX::XMVectorGetX(_matrix.r[2]);
    matrix.z.y = DirectX::XMVectorGetY(_matrix.r[2]);
    matrix.z.z = DirectX::XMVectorGetZ(_matrix.r[2]);
    matrix.z.w = DirectX::XMVectorGetW(_matrix.r[2]);
    
    matrix.w.x = DirectX::XMVectorGetX(_matrix.r[3]);
    matrix.w.y = DirectX::XMVectorGetY(_matrix.r[3]);
    matrix.w.z = DirectX::XMVectorGetZ(_matrix.r[3]);
    matrix.w.w = DirectX::XMVectorGetW(_matrix.r[3]);

    return matrix;
}
//----------------------------------------------------------------------------------------------------------------------
bool TMatrix4f::CompareMatrixToDirectXMatrix(const TVector3f& _m1, DirectX::XMMATRIX _m2)
{
    _m2:
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
        1.0f,            0.0f,          0.0f,           0.0f,
        0.0f,            Math::Cos(_angle),    -Math::Sin(_angle),   0.0f,
        0.0f,            Math::Sin(_angle),   Math::Cos(_angle),     0.0f,
        0.0f,            0.0f,          0.0f,           1.0f,
    };
}
//----------------------------------------------------------------------------------------------------------------------
TMatrix4f TMatrix4f::MatrixRotationY(float _angle)
{
    return
    {
        Math::Cos(_angle),      0.0f,          Math::Sin(_angle),    0.0f,
        0.0f,            1.0f,          0.0f,           0.0f,
        -Math::Sin(_angle),    0.0f,          Math::Cos(_angle),     0.0f,
        0.0f,            0.0f,          1.0f,           0.0f,
    };
}
//----------------------------------------------------------------------------------------------------------------------
TMatrix4f TMatrix4f::MatrixRotationZ(float _angle)
{
    return
    {
		Math::Cos(_angle),     -Math::Sin(_angle),     0.0f,           0.0f,
		Math::Sin(_angle),    Math::Cos(_angle),       0.0f,           0.0f,
		0.0f,            0.0f,              1.0f,           0.0f,
		0.0f,            0.0f,              0.0f,           1.0f,
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
