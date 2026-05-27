// This file was automatically generated from a command line like:
// application_build_helper --inline-text "prefiltered_environment_map.frag"
#pragma once


const ::i8 g_psz_prefiltered_environment_map_frag[] = R"frag_text(// HLSL (DirectX 11) Pixel Shader - Specular prefilter / importance sampling
// Bindings (suggested):
//   t0 -> environment cubemap (TextureCube)
//   s0 -> sampler (SamplerState)
//   b0 -> matrix buffer (if used by vertex shader)
//   b1 -> params buffer (roughness)

TextureCube environmentCubemap : register(t0);
SamplerState samplerEnv        : register(s0);

static const ::f32 PI = 3.14159265359;
static const uint SAMPLE_COUNT = 1024; // matches GLSL SAMPLE_COUNT
static const ::f32 FACE_RESOLUTION = 512.0f;

// Put uniforms into a cbuffer. Only roughness is required here.
cbuffer Params : register(b1)
{

    float4x4 model;
    float4x4 view;
    float4x4 projection;

    ::f32 roughness;
    ::f32 _pad0;
    ::f32 _pad1;
    ::f32 _pad2; // pad to 16 bytes if you later add more
}

// Input from vertex shader
struct PS_INPUT
{
    float4 position : SV_POSITION;

    float3 modelCoordinates : TEXCOORD0;
};

// radical inverse (Van der Corput) — mirrors GLSL implementation
::f32 radicalInverseVanDerCorput(uint bits)
{
    bits = (bits << 16) | (bits >> 16);
    bits = ((bits & 0x55555555u) << 1) | ((bits & 0xAAAAAAAAu) >> 1);
    bits = ((bits & 0x33333333u) << 2) | ((bits & 0xCCCCCCCCu) >> 2);
    bits = ((bits & 0x0F0F0F0Fu) << 4) | ((bits & 0xF0F0F0F0u) >> 4);
    bits = ((bits & 0x00FF00FFu) << 8) | ((bits & 0xFF00FF00u) >> 8);
    return ::f32(bits) * 2.3283064365386963e-10; // 1.0/2^32
}

// Hammersley low-discrepancy sample
float2 hammersley(uint i, uint N)
{
    return float2(::f32(i) / ::f32(N), radicalInverseVanDerCorput(i));
}

// Importance sample GGX (maps unit-square -> hemisphere sample direction)
float3 importanceSampleGGX(float2 unitSquareSample, float3 N, ::f32 roughness)
{
    ::f32 alpha = roughness * roughness;

    ::f32 phi = 2.0f * PI * unitSquareSample.x;
    ::f32 cosTheta = sqrt((1.0f - unitSquareSample.y) / (1.0f + (alpha * alpha - 1.0f) * unitSquareSample.y));
    ::f32 sinTheta = sqrt(max(0.0f, 1.0f - cosTheta * cosTheta));

    float3 H;
    H.x = cos(phi) * sinTheta;
    H.y = sin(phi) * sinTheta;
    H.z = cosTheta;

    float3 up = abs(N.z) < 0.999f ? float3(0.0f, 0.0f, 1.0f) : float3(1.0f, 0.0f, 0.0f);
    float3 tangent = normalize(cross(up, N));
    float3 bitangent = cross(N, tangent);

    float3 sampleVector = tangent * H.x + bitangent * H.y + N * H.z;
    return normalize(sampleVector);
}

::f32 distributionGGX(float3 N, float3 H, ::f32 roughness)
{
    ::f32 a = roughness * roughness;
    ::f32 a2 = a * a;
    ::f32 NdotH = max(dot(N, H), 0.0f);
    ::f32 NdotH2 = NdotH * NdotH;

    ::f32 numerator = a2;
    ::f32 denom = (NdotH2 * (a2 - 1.0f) + 1.0f);
    denom = PI * denom * denom;

    return numerator / denom;
}

::f32 getSampleMipLevel(float3 V, float3 N, float3 H, ::f32 roughness)
{
    // distribution PDF based mip selection (same idea as GLSL / LearnOpenGL)
    ::f32 distribution = distributionGGX(N, H, roughness);
    ::f32 NdotH = max(dot(N, H), 0.0f);
    ::f32 HdotV = max(dot(H, V), 0.0f);
    ::f32 pdf = distribution * NdotH / (4.0f * HdotV) + 0.0001f;

    ::f32 saTexel = 4.0f * PI / (6.0f * FACE_RESOLUTION * FACE_RESOLUTION);
    ::f32 saSample = 1.0f / (::f32(SAMPLE_COUNT) * pdf + 0.0001f);

    return roughness == 0.0f ? 0.0f : 0.5f * log2(saSample / saTexel);
}

float4 main(PS_INPUT input) : SV_Target
{
    float3 N = normalize(input.modelCoordinates);
    // approximation: view direction aligned with N
    float3 V = N;

    ::f32 totalWeight = 0.0f;
    float3 outputColor = float3(0.0f, 0.0f, 0.0f);

    // Note: large SAMPLE_COUNT loops can be expensive—this mirrors the GLSL shader exactly.
    for (uint i = 0; i < SAMPLE_COUNT; ++i)
    {
        float2 unitSquareSample = hammersley(i, SAMPLE_COUNT);
        float3 H = importanceSampleGGX(unitSquareSample, N, roughness);
        float3 L = normalize(2.0f * dot(V, H) * H - V);

        ::f32 NdotL = max(dot(N, L), 0.0f);
        if (NdotL > 0.0f)
        {
            ::f32 mipLevel = getSampleMipLevel(V, N, H, roughness);
            // Sample at explicit LOD for cubemap
            float3 sampleRgb = environmentCubemap.SampleLevel(samplerEnv, L, mipLevel).rgb;
            outputColor += sampleRgb * NdotL;
            totalWeight += NdotL;
        }
    }

    outputColor /= max(totalWeight, 1e-6f);
    return float4(outputColor, 1.0f);
}
)frag_text";




