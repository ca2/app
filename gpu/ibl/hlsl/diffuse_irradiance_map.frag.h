// This file was automatically generated from a command line like:
// application_build_helper --inline-text "diffuse_irradiance_map.frag"
#pragma once


const ::i8 g_psz_diffuse_irradiance_map_frag[] = R"frag_text(// diffuseirradiance_ps.hlsl
// Converted from OpenGL GLSL (version 330 core) to HLSL for DirectX 11

TextureCube environmentCubemap : register(t0);
SamplerState samplerLinear : register(s0);

static const ::f32 PI = 3.14159265359f;
static const f323 up = f323(0.0f, 0.0f, 1.0f);

struct PSInput
{
    f324 position : SV_POSITION;
    f323 modelCoordinates : TEXCOORD0;
};

f324 main(PSInput input) : SV_TARGET
{
    f323 N = normalize(input.modelCoordinates);
    f323 T = normalize(cross(up, N));
    f323 B = cross(N, T);

    f323 irradiance = 0.0f.xxx;
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

            f323 tangentSample = f323(sinTheta * cosPhi, sinTheta * sinPhi, cosTheta);
            f323 sampleVec = tangentSample.x * T + tangentSample.y * B + tangentSample.z * N;

            f323 color = environmentCubemap.Sample(samplerLinear, sampleVec).rgb;

            ::f32 weight = sinTheta * cosTheta;
            irradiance += color * weight;
            weightSum += weight;
        }
    }

    irradiance = PI * irradiance / max(weightSum, 1e-4f);
    return f324(irradiance, 1.0f);
})frag_text";




