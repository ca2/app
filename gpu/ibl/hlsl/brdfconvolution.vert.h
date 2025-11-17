// This file was automatically generated from a command line like:
// application_build_helper --inline-text "brdfconvolution.vert"
#pragma once


const char g_psz_brdfconvolution_vert[] = R"vert_text(// fullscreenquad_vs.hlsl
// Converted from GLSL (version 330 core) to HLSL for DirectX 11

struct VSInput
{
    float2 aPos : POSITION;          // layout(location = 0)
    float2 aTextureCoordinates : TEXCOORD0; // layout(location = 1)
};

struct VSOutput
{
    float4 position : SV_POSITION;
    float2 textureCoordinates : TEXCOORD0;
};

VSOutput main(VSInput input)
{
    VSOutput output;

    // aPos is already in normalized device coordinates (NDC)
    output.position = float4(input.aPos, 0.0f, 1.0f);
    output.textureCoordinates = input.aTextureCoordinates;

    return output;
}
)vert_text";




