#include "Shaders.h"

#include <d3dcompiler.h>
#include <intsafe.h>

#include "HResultHandler.h"


void CompileShader(LPCWSTR FileName, ID3DBlob* ShaderOut)
{
    UINT flags1 = 0;
    UINT flags2 = 0;
    
#ifdef _DEBUG
    flags1 |= D3DCOMPILE_DEBUG;
#endif
    
    // const D3D_SHADER_MACRO defines[] = 
    // {
    //     "EXAMPLE_DEFINE", "1",
    //     NULL, NULL
    // };
    
    ID3DBlob* ErrorBlob = nullptr;
    
    HRESULT HResult = D3DCompileFromFile(FileName, nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE,
                                     "Main", "cs_5_0",
                                     flags1, flags2, &ShaderOut, &ErrorBlob);
    if (HResult != 0)
    {
        const char* errorMsg = (const char*)ErrorBlob->GetBufferPointer();
        size_t size = strlen(errorMsg) + 1;  
        wchar_t* errorMsgWide = new wchar_t[size]; 
        size_t outSize;
        mbstowcs_s(&outSize, errorMsgWide, size, errorMsg, size-1);
        
        MessageBox(nullptr, errorMsgWide, L"Shader Compilation Error", MNC_IGNORE);
    }
}
