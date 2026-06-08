// This file was automatically generated from a command line like:
// application_build_helper --inline-text "scene.vert"
#pragma once


const char g_psz_scene_vert[] = R"vert_text(// scene_vs.hlsl
// Shader Model 5.0

// ---------- Structures ----------

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
    float4 cameraPosition;
    PointLight pointLights[10];
    int numLights;
};


cbuffer PushConsts : register(b1)
{
    float4x4 modelMatrix;
    float4x4 normalMatrix;

    int   useTextureAlbedo;
    int   useTextureNormal;
    int   useAlphaMask;

    float3 albedo;
    float  metallic;
    float  roughness;
    float  ambientOcclusion;
    float  alphaMaskCutoff;
};

struct VSInput
{
    float3 position : POSITION;
    float3 normal   : NORMAL;
    float2 uv       : TEXCOORD0;
    float4 color    : COLOR0;
    float4 tangent  : TEXCOORD1; // xyz = tangent, w = sign
};

struct VSOutput
{
    float4 position : SV_POSITION;

    float3 worldPos : TEXCOORD0;
    float3 normal   : TEXCOORD1;
    float2 uv       : TEXCOORD2;
    float4 color    : COLOR0;
    float3 tangent  : TEXCOORD3;
    float3 bitangent: TEXCOORD4;
};

VSOutput main(VSInput IN)
{
    VSOutput OUT;

    float4 worldPos = mul(float4(IN.position, 1.0), modelMatrix);
    OUT.position = mul(mul(worldPos, view), projection);

    float3x3 normalMat = (float3x3)normalMatrix;

    float3 N = normalize(mul(IN.normal, normalMat));
    float3 T = normalize(mul(IN.tangent.xyz, normalMat));
    float3 B = cross(N, T) * IN.tangent.w;

    OUT.worldPos  = worldPos.xyz;
    OUT.normal    = N;
    OUT.uv        = IN.uv;
    OUT.color     = IN.color;
    OUT.tangent   = T;
    OUT.bitangent = B;

    return OUT;
}
)vert_text";




