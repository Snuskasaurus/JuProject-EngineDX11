#include "Math.h"

namespace dx = DirectX;

//---------------------------------------------------------------------------------------------------------------------------------------------------------
const TMatrix4f TMatrix4f::Identity =
{
    {1.0f, 0.0f, 0.0f, 0.0f},
    {0.0f, 1.0f, 0.0f, 0.0f},
    {0.0f, 0.0f, 1.0f, 0.0f},
    {0.0f, 0.0f, 0.0f, 1.0f},
};
//---------------------------------------------------------------------------------------------------------------------------------------------------------
TMatrix4f TMatrix4f::MatrixRotationX(float x)
{
    return {};
}
//---------------------------------------------------------------------------------------------------------------------------------------------------------
TMatrix4f TMatrix4f::MatrixRotationY(float y)
{
    return {};
}
//---------------------------------------------------------------------------------------------------------------------------------------------------------
TMatrix4f TMatrix4f::MatrixRotationZ(float z)
{
    return {};
}
//---------------------------------------------------------------------------------------------------------------------------------------------------------
TMatrix4f TMatrix4f::MatrixTranslation(TVector3f translation)
{
    return {};
}
//---------------------------------------------------------------------------------------------------------------------------------------------------------
TMatrix4f TMatrix4f::MatrixScale(float scale)
{
    return {};
}
//---------------------------------------------------------------------------------------------------------------------------------------------------------
TMatrix4f TMatrix4f::MatrixLookAtRH(TVector3f EyePosition, TVector3f FocusPosition, TVector3f UpDirection)
{
    return {};
}
//---------------------------------------------------------------------------------------------------------------------------------------------------------
TMatrix4f TMatrix4f::MatrixPerspectiveFovRH(float FovAngleY, float AspectRatio, float NearZ, float FarZ)
{
    return {};
}
//---------------------------------------------------------------------------------------------------------------------------------------------------------
TMatrix4f TMatrix4f::Transpose(const TMatrix4f _matrix)
{
    return{
        _matrix.x.x, _matrix.y.x, _matrix.z.x, _matrix.w.x,
    _matrix.x.y, _matrix.y.y, _matrix.z.y, _matrix.w.y,
    _matrix.x.z, _matrix.y.z, _matrix.z.z, _matrix.w.z,
    _matrix.x.w, _matrix.y.w, _matrix.z.w, _matrix.w.w,
    };
}
//---------------------------------------------------------------------------------------------------------------------------------------------------------
dx::XMMATRIX TMatrix4f::ToDirectXMatrix(const TMatrix4f _matrix)
{
    return DirectX::XMMATRIX(
        _matrix.x.x, _matrix.x.y, _matrix.x.z, _matrix.x.w,
        _matrix.y.x, _matrix.y.y, _matrix.y.z, _matrix.y.w,
        _matrix.z.x, _matrix.z.y, _matrix.z.z, _matrix.z.w,
        _matrix.w.x, _matrix.w.y, _matrix.w.z, _matrix.w.w
        );
}
//---------------------------------------------------------------------------------------------------------------------------------------------------------
TMatrix4f TMatrix4f::FromDirectXMatrix(const dx::XMMATRIX _matrix)
{
    TMatrix4f matrix;

    matrix.x.x = dx::XMVectorGetX(_matrix.r[0]);
    matrix.x.y = dx::XMVectorGetY(_matrix.r[0]);
    matrix.x.z = dx::XMVectorGetZ(_matrix.r[0]);
    matrix.x.w = dx::XMVectorGetW(_matrix.r[0]);
    
    matrix.y.x = dx::XMVectorGetX(_matrix.r[1]);
    matrix.y.y = dx::XMVectorGetY(_matrix.r[1]);
    matrix.y.z = dx::XMVectorGetZ(_matrix.r[1]);
    matrix.y.w = dx::XMVectorGetW(_matrix.r[1]);
    
    matrix.z.x = dx::XMVectorGetX(_matrix.r[2]);
    matrix.z.y = dx::XMVectorGetY(_matrix.r[2]);
    matrix.z.z = dx::XMVectorGetZ(_matrix.r[2]);
    matrix.z.w = dx::XMVectorGetW(_matrix.r[2]);
    
    matrix.w.x = dx::XMVectorGetX(_matrix.r[3]);
    matrix.w.y = dx::XMVectorGetY(_matrix.r[3]);
    matrix.w.z = dx::XMVectorGetZ(_matrix.r[3]);
    matrix.w.w = dx::XMVectorGetW(_matrix.r[3]);

    return matrix;
}
//---------------------------------------------------------------------------------------------------------------------------------------------------------
