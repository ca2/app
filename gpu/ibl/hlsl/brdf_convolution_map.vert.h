// This file was automatically generated from a command line like:
// application_build_helper --inline-text "brdf_convolution_map.vert"
#pragma once


const ::i8 g_psz_brdf_convolution_map_vert[] = R"vert_text(// fullscreenquad_vs.hlsl
// Converted from GLSL (version 330 core) to HLSL for DirectX 11

struct VSInput
{
    f322 aPos : POSITION;          // layout(location = 0)
    f322 aTextureCoordinates : TEXCOORD0; // layout(location = 1)
};

struct VSOutput
{
    f324 position : SV_POSITION;
    f322 textureCoordinates : TEXCOORD0;
};

VSOutput main(VSInput input)
{
    VSOutput output;

    // aPos is already in normalized device coordinates (NDC)
    output.position = f324(input.aPos, 0.0f, 1.0f);
    output.textureCoordinates = input.aTextureCoordinates;

    return output;
}
)vert_text";




