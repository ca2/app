// This file was automatically generated from a command line like:
// application_build_helper --inline-text "texture.frag"
#pragma once


const char g_psz_texture_frag[] = R"frag_text(struct PS_INPUT
{
    float4 position     : SV_POSITION;
    float2 fragTexCoord : TEXCOORD0;
};

struct PointLight
{
    float4 position;
    float4 color;
};

// ---------- Global UBO (set 0 binding 0) ----------
cbuffer GlobalUbo : register(b0)
{
    column_major float4x4 projection;
    column_major float4x4 view;
    column_major float4x4 invView;
    float4 ambientLightColor;
    float3 cameraPosition;
    PointLight pointLights[10];
    int numLights;
};

cbuffer ObjectMatrices : register(b1)
{
    column_major float4x4 modelMatrix;
};

Texture2D textureSampler : register(t0);
SamplerState textureSamplerState : register(s0);

float4 main(PS_INPUT input) : SV_TARGET0
{
    return textureSampler.Sample(
        textureSamplerState,
        input.fragTexCoord);
}
)frag_text";




