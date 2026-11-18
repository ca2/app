// This file was automatically generated from a command line like:
// application_build_helper --inline-text "texture.vert"
#pragma once


const char g_psz_texture_vert[] = R"vert_text(struct VS_INPUT
{
    float3 position : POSITION;
    float3 color    : COLOR0;
    float3 normal   : NORMAL;
    float2 uv       : TEXCOORD0;
};

struct VS_OUTPUT
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
    float4x4 projection;
    float4x4 view;
    float4x4 invView;
    float4 ambientLightColor;
    float3 cameraPosition;
    PointLight pointLights[10];
    int numLights;
};

cbuffer ObjectMatrices : register(b1)
{
    float4x4 modelMatrix;
};

VS_OUTPUT main(VS_INPUT input)
{
    VS_OUTPUT output;

    float4 worldPosition =
        mul(float4(input.position, 1.0f), modelMatrix);

    output.position =
        mul(mul(worldPosition, view), projection);

    // ca2 model UVs and DirectX texture UVs both use a top-left origin.
    output.fragTexCoord = input.uv;

    return output;
})vert_text";




