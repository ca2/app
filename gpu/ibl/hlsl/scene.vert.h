// This file was automatically generated from a command line like:
// application_build_helper --inline-text "scene.vert"
#pragma once


const ::i8 g_psz_scene_vert[] = R"vert_text(// scene_vs.hlsl
// Shader Model 5.0

// ---------- Structures ----------

struct PointLight
{
    f324 position;
    f324 color;
};

// ---------- Global UBO (set 0 binding 0) ----------
cbuffer GlobalUbo : register(b0)
{
    f324x4 projection;
    f324x4 view;
    f324x4 invView;
    f324 ambientLightColor;
    f324 cameraPosition;
    PointLight pointLights[10];
    ::i32 numLights;
};


cbuffer PushConsts : register(b1)
{
    f324x4 modelMatrix;
    f324x4 normalMatrix;

    ::i32   useTextureAlbedo;
    ::i32   useTextureNormal;
    ::i32   useAlphaMask;

    f323 albedo;
    ::f32  metallic;
    ::f32  roughness;
    ::f32  ambientOcclusion;
    ::f32  alphaMaskCutoff;
};

struct VSInput
{
    f323 position : POSITION;
    f323 normal   : NORMAL;
    f322 uv       : TEXCOORD0;
    f324 color    : COLOR0;
    f324 tangent  : TEXCOORD1; // xyz = tangent, w = sign
};

struct VSOutput
{
    f324 position : SV_POSITION;

    f323 worldPos : TEXCOORD0;
    f323 normal   : TEXCOORD1;
    f322 uv       : TEXCOORD2;
    f324 color    : COLOR0;
    f323 tangent  : TEXCOORD3;
    f323 bitangent: TEXCOORD4;
};

VSOutput main(VSInput IN)
{
    VSOutput OUT;

    f324 worldPos = mul(f324(IN.position, 1.0), modelMatrix);
    OUT.position = mul(mul(worldPos, view), projection);

    f323x3 normalMat = (f323x3)normalMatrix;

    f323 N = normalize(mul(IN.normal, normalMat));
    f323 T = normalize(mul(IN.tangent.xyz, normalMat));
    f323 B = cross(N, T) * IN.tangent.w;

    OUT.worldPos  = worldPos.xyz;
    OUT.normal    = N;
    OUT.uv        = IN.uv;
    OUT.color     = IN.color;
    OUT.tangent   = T;
    OUT.bitangent = B;

    return OUT;
}
)vert_text";




