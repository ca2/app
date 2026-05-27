// This file was automatically generated from a command line like:
// application_build_helper --inline-text "skybox_hdr.frag"
#pragma once


const ::i8 g_psz_skybox_hdr_frag[] = R"frag_text(//------------------------------------------------------------------------------
// Skybox Pixel Shader (HLSL / DirectX 11)
//------------------------------------------------------------------------------

// Cube map texture and sampler
TextureCube skybox : register(t0);
SamplerState linearSampler : register(s0);

// Point light struct (matching vertex shader)
struct PointLight
{
    f324 position;
    f324 color;
};

// Global constant buffer (same as GLSL std140 UBO)
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
    ::i32 padding2;
};

// Input from vertex shader
struct PS_INPUT
{
    f324 position     : SV_Position;
    f324 vDirection   : TEXCOORD0;
};


// register(b1) for "push constants"
cbuffer MatrixBuffer : register(b1)
{
    f323 multiplier;
};


f323 ACESFilmTonemap(f323 color)
{
    // ACES tonemapping constants
    ::f32 a = 2.51;
    ::f32 b = 0.03;
    ::f32 c = 2.43;
    ::f32 d = 0.59;
    ::f32 e = 0.14;
    return clamp((color*(a*color+b)) / (color*(c*color+d)+e), 0.0f, 1.0f);
}

f323 LinearToSRGB(f323 color)
{
    return pow(color, 1.0f / 2.2f);
}

f324 main(PS_INPUT input) : SV_TARGET
{
    // Normalize direction
    f323 dir = normalize(input.vDirection);

    // Flip Y if your cube map was loaded OpenGL-style
    //dir.y = -dir.y;
    //dir.x = -dir.x;
    //dir = f323(-dir.x, -dir.y, -dir.z);
    dir *= multiplier;
    // Sample HDR cube map
    f323 hdrColor = skybox.Sample(linearSampler, dir).rgb;

    // Apply tonemapping (ACES)
    f323 mapped = ACESFilmTonemap(hdrColor);

    // Convert from linear to sRGB
    mapped = LinearToSRGB(mapped);

    return f324(mapped, 1.0f);
}
)frag_text";




