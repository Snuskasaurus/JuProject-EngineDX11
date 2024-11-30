#include "Test.h"

#include "Engine/Math.h"

void TestValidation::RunTest_Matrix()
{
    // Testing MatrixTranslation
    {
        TVector3f Translation = { 10.0f, 5.0f, 3.0f };
        TMatrix4f MatrixTranslation = TMatrix4f::MatrixTranslation(Translation);
        DirectX::XMMATRIX matrixDirectX = DirectX::XMMatrixTranslation(Translation.x, Translation.y, Translation.z);
        TMatrix4f XMMatrixTranslation = TMatrix4f::Transpose(TMatrix4f::FromDirectXMatrix(matrixDirectX));
        assert(MatrixTranslation.x == XMMatrixTranslation.x);
        assert(MatrixTranslation.y == XMMatrixTranslation.y);
        assert(MatrixTranslation.z == XMMatrixTranslation.z);
        assert(MatrixTranslation.w == XMMatrixTranslation.w);
    }
    
    // Testing MatrixRotationX
    {
        float Rotation = 99.0f;
        TMatrix4f MatrixRotationX = TMatrix4f::MatrixRotationX(Rotation);
        DirectX::XMMATRIX matrixDirectX = DirectX::XMMatrixRotationX(Rotation);
        TMatrix4f XMMatrixRotationX = TMatrix4f::Transpose(TMatrix4f::FromDirectXMatrix(matrixDirectX));
        assert(MatrixRotationX.x == XMMatrixRotationX.x);
        assert(MatrixRotationX.y == XMMatrixRotationX.y);
        assert(MatrixRotationX.z == XMMatrixRotationX.z);
        assert(MatrixRotationX.w == XMMatrixRotationX.w);
    }
    
    // Testing MatrixRotationY
    {
        float Rotation = 187.0f;
        TMatrix4f MatrixRotationY = TMatrix4f::MatrixRotationY(Rotation);
        DirectX::XMMATRIX matrixDirectX = DirectX::XMMatrixRotationY(Rotation);
        TMatrix4f XMMatrixRotationY = TMatrix4f::Transpose(TMatrix4f::FromDirectXMatrix(matrixDirectX));
        assert(MatrixRotationY.x == XMMatrixRotationY.x);
        assert(MatrixRotationY.y == XMMatrixRotationY.y);
        assert(MatrixRotationY.z == XMMatrixRotationY.z);
        assert(MatrixRotationY.w == XMMatrixRotationY.w);
    }

    // Testing MatrixRotationZ
    {
        float Rotation = 166.0f;
        TMatrix4f MatrixRotationZ = TMatrix4f::MatrixRotationZ(Rotation);
        DirectX::XMMATRIX matrixDirectX = DirectX::XMMatrixRotationZ(Rotation);
        
        TMatrix4f XMMatrixRotationZ = TMatrix4f::Transpose(TMatrix4f::FromDirectXMatrix(matrixDirectX));
        assert(MatrixRotationZ.x == XMMatrixRotationZ.x);
        assert(MatrixRotationZ.y == XMMatrixRotationZ.y);
        assert(MatrixRotationZ.z == XMMatrixRotationZ.z);
        assert(MatrixRotationZ.w == XMMatrixRotationZ.w);
    }
    
    // Testing MatrixScale
    {
        float scale = 166.0f;
        TMatrix4f MatrixScale = TMatrix4f::MatrixScale(scale);
        DirectX::XMMATRIX matrixDirectX = DirectX::XMMatrixScaling(scale, scale, scale);
        
        TMatrix4f XMMatrixScaling = TMatrix4f::Transpose(TMatrix4f::FromDirectXMatrix(matrixDirectX));
        assert(MatrixScale.x == XMMatrixScaling.x);
        assert(MatrixScale.y == XMMatrixScaling.y);
        assert(MatrixScale.z == XMMatrixScaling.z);
        assert(MatrixScale.w == XMMatrixScaling.w);
    }

    // Testing MatrixLookAtRH
    {
        const TVector3f cameraPosition = { 12.0f, 36.0f, 25.0f };
        const TVector3f lookAtPosition = { 0.0f, 100.0f, 1.0f };
        const TVector3f up = { 0.0f, 0.0f, 1.0f };
        TMatrix4f MatrixLookAtRH = TMatrix4f::MatrixLookAtRH(cameraPosition, lookAtPosition, up);
        DirectX::XMMATRIX matrixDirectX = DirectX::XMMatrixLookAtRH(cameraPosition.ToDXVec(), lookAtPosition.ToDXVec(), up.ToDXVec());
        
        TMatrix4f XMMatrixLookAtRH = TMatrix4f::Transpose(TMatrix4f::FromDirectXMatrix(matrixDirectX));
        assert(MatrixLookAtRH.x == XMMatrixLookAtRH.x);
        assert(MatrixLookAtRH.y == XMMatrixLookAtRH.y);
        assert(MatrixLookAtRH.z == XMMatrixLookAtRH.z);
        assert(MatrixLookAtRH.w == XMMatrixLookAtRH.w);
    }
}
