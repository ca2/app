// This file was automatically generated from a command line like:
// application_build_helper --inline-text "wavefront.vert"
#pragma once


const char g_psz_wavefront_vert[] = R"vert_text(// Input structure from vertex buffer
struct VS_INPUT {
    float3 position : POSITION;
    float3 color    : COLOR;
    float3 normal   : NORMAL;
    float2 uv       : TEXCOORD0;
};

// Output structure to pixel shader
struct VS_OUTPUT {
    float4 pos             : SV_POSITION;
    float3 fragColor       : COLOR0;
    float3 fragPosWorld    : TEXCOORD1;
    float3 fragNormalWorld : TEXCOORD2;
};

// Match GLSL std140 layout (float4-aligned)
struct PointLight {
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

// Separate uniforms (can also be placed in their own cbuffer if needed)
cbuffer ObjectMatrices : register(b1)
{
    column_major float4x4 modelMatrix;
    column_major float4x4 normalMatrix; // Should be precomputed as the transpose(inverse(modelMatrix))
};

// Main vertex shader
VS_OUTPUT main(VS_INPUT input)
{
    VS_OUTPUT output;

    float3 inputPosition = input.position;

    //inputPosition.y = -inputPosition.y;

    float4 positionWorld = mul(float4(inputPosition, 1.0f), modelMatrix);      // model * vec
    output.pos = mul(mul(positionWorld, view), projection);                    // projection * view * model * vec
    output.fragNormalWorld = normalize(mul((float3x3)normalMatrix, input.normal));
    output.fragPosWorld = positionWorld.xyz;
    output.fragColor = input.color;

    return output;
}
)vert_text";




