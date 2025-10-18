// This file was automatically generated from a command line like:
// application_build_helper --inline-text "hdricube.vert"
#pragma once


const char g_psz_hdricube_vert[] = R"vert_text(//------------------------------------------------------------------------------
// Vertex Shader (HLSL)
// Equivalent of your GLSL shader
//------------------------------------------------------------------------------

// Input vertex
struct VS_INPUT
{
    float3 position : POSITION;   // layout(location = 0)
};

// Output to the pixel shader
struct VS_OUTPUT
{
    float4 position : SV_POSITION;
    float3 modelCoordinates : TEXCOORD0;
};

// Constant buffer (matches GLSL uniforms)
cbuffer MatrixBuffer : register(b1)
{
    float4x4 model;
    float4x4 view;
    float4x4 projection;
};

VS_OUTPUT main(VS_INPUT input)
{
    VS_OUTPUT output;

    // HLSL uses column-major matrices by default, just like GLSL,
    // so we can multiply in the same order.
    float4 worldPos = mul(float4(input.position, 1.0f), model);
    float4 viewPos  = mul(worldPos, view);
    output.position = mul(viewPos, projection);

    // Pass the model-space coordinates
    output.modelCoordinates = input.position;

    return output;
}
)vert_text";




