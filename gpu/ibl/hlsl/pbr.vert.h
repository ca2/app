// This file was automatically generated from a command line like:
// application_build_helper --inline-text "pbr.vert"
#pragma once


const ::i8 g_psz_pbr_vert[] = R"vert_text(// pbr1.vert
// Converted from Vulkan GLSL to HLSL
// Matches the PBR fragment shader above
// by Camilo <3ThomasBorregaardSorensen!!
// Shader Model 5.0+ recommended

// ---------- Input vertex attributes ----------
struct VSInput
{
    f323 aPos               : POSITION;   // location = 0
    f323 aNormal            : NORMAL;     // location = 1
    f322 aTextureCoordinates: TEXCOORD0;  // location = 2
    f324 aColor             : COLOR;      // location = 3
    f324 aTangent           : TEXCOORD1;    // location = 4
};

// ---------- Outputs to fragment shader ----------
struct VSOutput
{
    f324 Position          : SV_Position;
    f323 worldCoordinates  : TEXCOORD0;
    f322 textureCoordinates: TEXCOORD1;
    f323 tangent           : TEXCOORD2;
    f323 bitangent         : TEXCOORD3;
    f323 normal            : TEXCOORD4;
};

// Must match fragment shader
struct PointLight
{
    f324 position;
    f324 color;
};

// ---------- Global UBO (set = 0, binding = 0) ----------
cbuffer GlobalUbo : register(b0)
{
    f324x4 projection;
    f324x4 view;
    f324x4 invView;
    f324 ambientLightColor;
    f324 cameraPosition;
    PointLight pointLights[10];
    ::i32 numLights;
    ::i32 padding1;
    ::i32 padding2;
    ::i32 padding3;
};

// ---------- Push constants (model transforms) ----------
// ---------- Push constants (converted to another cbuffer) ----------
cbuffer PushConsts : register(b1)
{
    f324x4 modelMatrix;
    f324x4 normalMatrix; // inverse-transpose of model

    ::i32 useTextureAlbedo;
    ::i32 useTextureMetallicRoughness;
    ::i32 useTextureNormal;
    ::i32 useTextureAmbientOcclusion;
    ::i32 useTextureEmissive;

    f323 albedo;
    ::f32 metallic;
    ::f32 roughness;
    ::f32 ambientOcclusion;
    f323 emissive;

//    f323 cameraPosition;
    ::f32 bloomBrightnessCutoff;
    f323 multiplier;
};

VSOutput main(VSInput input)
{
    VSOutput output;

    // Transform position to world space
    f324 worldPos = mul(f324(input.aPos, 1.0), modelMatrix);

    //worldPos.x = -worldPos.x;
    //worldPos.z = -worldPos.z;
    worldPos.y = -worldPos.y;

    output.worldCoordinates = worldPos.xyz;

    // Final clip-space position
    output.Position = mul(worldPos, view);
    output.Position = mul(output.Position, projection);

    // Pass through texture coordinates
    output.textureCoordinates = input.aTextureCoordinates;

    // Normal, tangent, bitangent in world space
    f323x3 normalMat = transpose((f323x3)normalMatrix);

    f323 N = normalize(mul(input.aNormal, normalMat));
    f323 T = normalize(mul(input.aTangent.xyz, normalMat));
    f323 B = normalize(cross(N, T)) * input.aTangent.w;

    output.normal = N;
    output.tangent = T;
    output.bitangent = B;

    return output;
}
)vert_text";




