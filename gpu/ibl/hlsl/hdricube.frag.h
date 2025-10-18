// This file was automatically generated from a command line like:
// application_build_helper --inline-text "hdricube.frag"
#pragma once


const char g_psz_hdricube_frag[] = R"frag_text(//------------------------------------------------------------------------------
// Pixel Shader (HLSL) - Equivalent to your GLSL equirectangular HDRI shader
//------------------------------------------------------------------------------

// Input from vertex shader
struct PS_INPUT
{
    float4 position : SV_POSITION;
    float3 modelCoordinates : TEXCOORD0;
};

// Texture and sampler
Texture2D hdri        : register(t0);
SamplerState samLinear : register(s0);

// Constants
static const float2 inverseAtan = float2(0.1591, 0.3183);

float2 sphericalToCartesian(float3 v)
{
    // GLSL atan(y, x) -> HLSL atan2(y, x)
    float2 xy;
    xy.x = atan2(v.z, v.x);
    xy.y = asin(v.y);
    xy *= inverseAtan;
    xy += 0.5;
    return xy;
}

float4 main(PS_INPUT input) : SV_TARGET
{
    float3 sampleDirection = normalize(input.modelCoordinates);
    //sampleDirection.x = -sampleDirection.x;
    float2 uv = sphericalToCartesian(sampleDirection);

    // Sample the HDRI (equirectangular) texture
    float3 color = hdri.Sample(samLinear, uv).rgb;

    return float4(color, 1.0f);
}
)frag_text";




