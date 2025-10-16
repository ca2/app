// HLSL Pixel Shader equivalent of your GLSL version
// Converts an equirectangular (HDRI) texture into a cubemap sample

Texture2D hdri : register(t0);
SamplerState hdriSampler : register(s0);

static const float2 inverseAtan = float2(0.1591f, 0.3183f);

struct PS_INPUT
{
    float3 modelCoordinates : TEXCOORD0; // from vertex shader
};

float2 sphericalToCartesian(float3 v)
{
    float2 xy;
    xy.x = atan2(v.z, v.x);
    xy.y = asin(v.y);
    xy *= inverseAtan;
    xy += 0.5f;
    return xy;
}

float4 main(PS_INPUT input) : SV_TARGET
{
    float3 sampleDirection = normalize(input.modelCoordinates);
    float2 uv = sphericalToCartesian(sampleDirection);
    float3 color = hdri.Sample(hdriSampler, uv).rgb;

    return float4(color, 1.0f);
}
