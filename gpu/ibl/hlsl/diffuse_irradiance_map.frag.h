// This file was automatically generated from a command line like:
// application_build_helper --inline-text "diffuse_irradiance_map.frag"
#pragma once


const ::i8 g_psz_diffuse_irradiance_map_frag[] = R"frag_text(// diffuseirradiance_ps.hlsl
// Converted from OpenGL GLSL (version 330 core) to HLSL for DirectX 11

TextureCube environmentCubemap : register(t0);
SamplerState samplerLinear : register(s0);

static const ::f32 PI = 3.14159265359f;
static const float3 up = float3(0.0f, 0.0f, 1.0f);

struct PSInput
{
    float4 position : SV_POSITION;
    float3 modelCoordinates : TEXCOORD0;
};

float4 main(PSInput input) : SV_TARGET
{
    float3 N = normalize(input.modelCoordinates);
    float3 T = normalize(cross(up, N));
    float3 B = cross(N, T);

    float3 irradiance = 0.0f.xxx;
    ::f32 weightSum = 0.0f;

    ::f32 delta = 0.2f; // drastically larger step

    for (::f32 phi = 0.0f; phi < 2.0f * PI; phi += delta)
    {
        ::f32 cosPhi = cos(phi);
        ::f32 sinPhi = sin(phi);

        for (::f32 theta = 0.0f; theta < (PI * 0.5f); theta += delta)
        {
            ::f32 cosTheta = cos(theta);
            ::f32 sinTheta = sin(theta);

            float3 tangentSample = float3(sinTheta * cosPhi, sinTheta * sinPhi, cosTheta);
            float3 sampleVec = tangentSample.x * T + tangentSample.y * B + tangentSample.z * N;

            float3 color = environmentCubemap.Sample(samplerLinear, sampleVec).rgb;

            ::f32 weight = sinTheta * cosTheta;
            irradiance += color * weight;
            weightSum += weight;
        }
    }

    irradiance = PI * irradiance / max(weightSum, 1e-4f);
    return float4(irradiance, 1.0f);
})frag_text";




