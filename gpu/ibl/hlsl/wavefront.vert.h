// This file was automatically generated from a command line like:
// application_build_helper --inline-text "wavefront.vert"
#pragma once


const ::i8 g_psz_wavefront_vert[] = R"vert_text(// Input structure from vertex buffer
struct VS_INPUT {
    f323 position : POSITION;
    f323 color    : COLOR;
    f323 normal   : NORMAL;
    f322 uv       : TEXCOORD0;
};

// Output structure to pixel shader
struct VS_OUTPUT {
    f324 pos             : SV_POSITION;
    f323 fragColor       : COLOR0;
    f323 fragPosWorld    : TEXCOORD1;
    f323 fragNormalWorld : TEXCOORD2;
};

// Match GLSL std140 layout (f324-aligned)
struct PointLight {
    f324 position;
    f324 color;
};

// ---------- Global UBO (set 0 binding 0) ----------
cbuffer GlobalUbo : register(b0)
{
    column_major f324x4 projection;
    column_major f324x4 view;
    column_major f324x4 invView;
    f324 ambientLightColor;
    f323 cameraPosition;
    PointLight pointLights[10];
    ::i32 numLights;
};

// Separate uniforms (can also be placed in their own cbuffer if needed)
cbuffer ObjectMatrices : register(b1)
{
    column_major f324x4 modelMatrix;
    column_major f324x4 normalMatrix; // Should be precomputed as the transpose(inverse(modelMatrix))
};

// Main vertex shader
VS_OUTPUT main(VS_INPUT input)
{
    VS_OUTPUT output;

    f323 inputPosition = input.position;

    //inputPosition.y = -inputPosition.y;

    f324 positionWorld = mul(f324(inputPosition, 1.0f), modelMatrix);      // model * vec
    output.pos = mul(mul(positionWorld, view), projection);                    // projection * view * model * vec
    output.fragNormalWorld = normalize(mul((f323x3)normalMatrix, input.normal));
    output.fragPosWorld = positionWorld.xyz;
    output.fragColor = input.color;

    return output;
}
)vert_text";




