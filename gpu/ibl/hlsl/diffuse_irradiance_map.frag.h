// This file was automatically generated from a command line like:
// application_build_helper --inline-text "diffuseirradiance.frag"
#pragma once


const char g_psz_diffuseirradiance_frag[] = R"frag_text(// diffuseirradiance_ps.hlsl
// Converted from OpenGL GLSL (version 330 core) to HLSL for DirectX 11

TextureCube environmentCubemap : register(t0);
SamplerState samplerLinear : register(s0);

static const float PI = 3.14159265359f;
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
    float weightSum = 0.0f;

    float delta = 0.2f; // drastically larger step

    for (float phi = 0.0f; phi < 2.0f * PI; phi += delta)
    {
        float cosPhi = cos(phi);
        float sinPhi = sin(phi);

        for (float theta = 0.0f; theta < (PI * 0.5f); theta += delta)
        {
            float cosTheta = cos(theta);
            float sinTheta = sin(theta);

            float3 tangentSample = float3(sinTheta * cosPhi, sinTheta * sinPhi, cosTheta);
            float3 sampleVec = tangentSample.x * T + tangentSample.y * B + tangentSample.z * N;

            float3 color = environmentCubemap.Sample(samplerLinear, sampleVec).rgb;

            float weight = sinTheta * cosTheta;
            irradiance += color * weight;
            weightSum += weight;
        }
    }

    irradiance = PI * irradiance / max(weightSum, 1e-4f);
    return float4(irradiance, 1.0f);
})frag_text";




