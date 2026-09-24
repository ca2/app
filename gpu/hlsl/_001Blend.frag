Texture2D uTexture : register(t0);
SamplerState uSampler : register(s0);

struct PSInput
{
    float4 position : SV_POSITION;
    float2 uv       : TEXCOORD0;
};

float4 main(PSInput input) : SV_TARGET
{
    return uTexture.Sample(uSampler, input.uv);
}