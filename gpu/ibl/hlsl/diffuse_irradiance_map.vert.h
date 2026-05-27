// This file was automatically generated from a command line like:
// application_build_helper --inline-text "diffuse_irradiance_map.vert"
#pragma once


const ::i8 g_psz_diffuse_irradiance_map_vert[] = R"vert_text(// diffuseirradiance_vs.hlsl
// Converted from OpenGL GLSL (version 330 core) to HLSL for DirectX 11

cbuffer MatrixBuffer : register(b1)
{
    f324x4 mvp;
    //f324x4 view;
    //f324x4 projection;
};

struct VSInput
{
    f323 aPos : POSITION; // location = 0
};

struct VSOutput
{
    f324 position : SV_POSITION;
    f323 modelCoordinates : TEXCOORD0;
};

VSOutput main(VSInput input)
{
    VSOutput output;

    //f324 worldPosition = mul(f324(input.aPos, 1.0f), model);
    //f324 viewPosition = mul(worldPosition, view);
    //output.position = mul(viewPosition, projection);
    output.position =mul(f324(input.aPos,1), mvp);

    output.modelCoordinates = f323(input.aPos.x, -input.aPos.y, input.aPos.z);

    return output;
}
)vert_text";




