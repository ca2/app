﻿// This file was automatically generated from a command line like:
// application_build_helper --inline-text "specularenv.vert"
#pragma once


const char g_psz_specularenv_vert[] = R"vert_text(// DirectX 11 HLSL Vertex Shader

cbuffer MatrixBuffer : register(b0)
{
    float4x4 model;
    float4x4 view;
    float4x4 projection;
};

// Vertex input structure (matches your input layout in C++)
struct VS_INPUT
{
    float3 position : POSITION;
};

// Vertex output structure (goes to the pixel shader)
struct VS_OUTPUT
{
    float4 position : SV_POSITION;
    float3 modelCoordinates : TEXCOORD0;
};

VS_OUTPUT main(VS_INPUT input)
{
    VS_OUTPUT output;

    // HLSL matrices are row-major by default, so we multiply in the reverse order
    float4 worldPosition = mul(float4(input.position, 1.0f), model);
    worldPosition = mul(worldPosition, view);
    worldPosition = mul(worldPosition, projection);

    output.position = worldPosition;
    output.modelCoordinates = input.position;

    return output;
}
)vert_text";




