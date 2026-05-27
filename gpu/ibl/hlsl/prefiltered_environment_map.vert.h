// This file was automatically generated from a command line like:
// application_build_helper --inline-text "prefiltered_environment_map.vert"
#pragma once


const ::i8 g_psz_prefiltered_environment_map_vert[] = R"vert_text(// DirectX 11 HLSL Vertex Shader

cbuffer MatrixBuffer : register(b1)
{
    f324x4 mvp;
};

// Vertex input structure (matches your input layout in C++)
struct VS_INPUT
{
    f323 position : POSITION;
};

// Vertex output structure (goes to the pixel shader)
struct VS_OUTPUT
{
    f324 position : SV_POSITION;
    f323 modelCoordinates : TEXCOORD0;
};

VS_OUTPUT main(VS_INPUT input)
{
    VS_OUTPUT output;

    // HLSL matrices are row-major by default, so we multiply in the reverse order
//    f324 worldPosition = mul(f324(input.position, 1.0f), model);
//    worldPosition = mul(worldPosition, view);
//    worldPosition = mul(worldPosition, projection);
//
    //output.position = worldPosition;
    output.position =mul(f324(input.position,1), mvp);
    output.modelCoordinates = f323(input.position.x, -input.position.y, input.position.z);

    return output;
}
)vert_text";




