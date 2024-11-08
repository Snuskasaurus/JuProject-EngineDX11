struct VSOut
{
    float3 position : Position;
    float3 normal : Normal;
    float2 texCoord : TexCoord0;
};

struct VSOut
{
    float2 texCoord : TexCoord0;
    float4 position : SV_Position;
};

cbuffer CBuffer
{
    matrix transform;
}

VSOut main(float3 position : Position, float3 normal : Normal, float2 texCoord : TexCoord0)
{
    VSOut vso;
    vso.texCoord = texCoord;
    vso.position = mul(float4(position, 1.0f), transform);
    return vso;
}