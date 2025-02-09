﻿#include "Shaders.h"

#include <d3dcompiler.h>
#include <intsafe.h>

#include "HResultHandler.h"


void ShaderManager::CompileShader(LPCWSTR _fileName, const char* _target, ID3DBlob** _shaderOut)
{
    UINT flags1 = 0;
    UINT flags2 = 0;

    flags1 |= D3DCOMPILE_PACK_MATRIX_COLUMN_MAJOR;
    
#if _DEBUG
    flags1 |= D3DCOMPILE_DEBUG;
#endif
    
    // const D3D_SHADER_MACRO defines[] = 
    // {
    //     "EXAMPLE_DEFINE", "1",
    //     NULL, NULL
    // };
    
    ID3DBlob* ErrorBlob = nullptr;
    
    HRESULT HResult = D3DCompileFromFile(_fileName, nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE,
                                     "Main", _target,
                                     flags1, flags2, _shaderOut, &ErrorBlob);
    if (HResult != 0)
    {
        const char* errorMsg = (const char*)ErrorBlob->GetBufferPointer();
        
        MessageBoxA(nullptr, errorMsg, "Shader Compilation Error", MNC_IGNORE);
    }
}
