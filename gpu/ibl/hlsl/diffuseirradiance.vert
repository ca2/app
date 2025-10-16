// diffuseirradiance_vs.hlsl
// Converted from OpenGL GLSL (version 330 core) to HLSL for DirectX 11

cbuffer MatrixBuffer : register(b0)
{
    float4x4 model;
    float4x4 view;
    float4x4 projection;
};

struct VSInput
{
    float3 aPos : POSITION; // location = 0
};

struct VSOutput
{
    float4 position : SV_POSITION;
    float3 modelCoordinates : TEXCOORD0;
};

VSOutput main(VSInput input)
{
    VSOutput output;

    float4 worldPosition = mul(float4(input.aPos, 1.0f), model);
    float4 viewPosition = mul(worldPosition, view);
    output.position = mul(viewPosition, projection);

    output.modelCoordinates = input.aPos;

    return output;
}
