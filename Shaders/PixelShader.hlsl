Texture2D texColor : register(t0);

SamplerState samplerState;

float4 main(float2 tc : TexCoord) : SV_Target
{
    return texColor.Sample(samplerState, tc);
}