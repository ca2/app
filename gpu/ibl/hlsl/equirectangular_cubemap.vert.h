// This file was automatically generated from a command line like:
// application_build_helper --inline-text "equirectangular_cubemap.vert"
#pragma once


const char g_psz_equirectangular_cubemap_vert[] = R"vert_text(struct VS_INPUT
{
    float3 position : POSITION;
    float3 normal   : NORMAL;
    float2 uv       : TEXCOORD0;
};

struct VS_OUTPUT
{
    float4 position : SV_POSITION;
    float3 modelCoordinates : TEXCOORD0;
};

// register(b1) for "push constants"
cbuffer MatrixBuffer : register(b1)
{
    float4x4 model;
    float4x4 view;
    float4x4 projection;
};

VS_OUTPUT main(VS_INPUT input)
{
    VS_OUTPUT output;

    float4 worldPos = mul(float4(input.position,1), model);
    float4 viewPos  = mul(worldPos, view);
    output.position = mul(viewPos, projection);

    output.modelCoordinates = input.position; // for HDRI lookup
    return output;
}
)vert_text";




