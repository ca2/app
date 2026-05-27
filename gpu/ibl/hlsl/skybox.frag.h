// This file was automatically generated from a command line like:
// application_build_helper --inline-text "skybox.frag"
#pragma once


const ::i8 g_psz_skybox_frag[] = R"frag_text(//------------------------------------------------------------------------------
// HLSL Fragment Shader (Pixel Shader) equivalent
//------------------------------------------------------------------------------

// Texture and sampler
TextureCube skybox       : register(t0);
SamplerState samplerLinear : register(s0);

// Scene constant buffer (matches GlobalUbo in GLSL)
struct PointLight
{
    f324 position;
    f324 color;
};



// register(b1) for "push constants"
cbuffer MatrixBuffer : register(b1)
{
    f323 multiplier;
};



cbuffer GlobalUbo : register(b0)
{
    f324x4 projection;
    f324x4 view;
    f324x4 invView;
    f324 ambientLightColor;
    f323 cameraPosition;
    PointLight pointLights[10];
    ::i32 numLights;
    ::i32 padding0;
    ::i32 padding1;
    ::i32 padding2; // padding to make struct size multiple of 16 bytes
};

// Pixel shader input
struct PS_INPUT
{
    f324 position     : SV_Position;
    f324 vDirection   : TEXCOORD0;
};



f324 main(PS_INPUT input)  : SV_TARGET
{

    // Normalize direction
    f323 dir = normalize(input.vDirection);

    // Flip Y if needed (to match OpenGL coordinates)
    //dir.y = -dir.y;
    dir *= multiplier;

    // Sample skybox cubemap
    f324 color = skybox.Sample(samplerLinear, dir);

    return color;
}
)frag_text";




