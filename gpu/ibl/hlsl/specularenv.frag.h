// This file was automatically generated from a command line like:
// application_build_helper --inline-text "specularenv.frag"
#pragma once


const char g_psz_specularenv_frag[] = R"frag_text(// HLSL (DirectX 11) Pixel Shader - Specular prefilter / importance sampling
// Bindings (suggested):
//   t0 -> environment cubemap (TextureCube)
//   s0 -> sampler (SamplerState)
//   b0 -> matrix buffer (if used by vertex shader)
//   b1 -> params buffer (roughness)

TextureCube environmentCubemap : register(t0);
SamplerState samplerEnv        : register(s0);

static const float PI = 3.14159265359;
static const uint SAMPLE_COUNT = 1024; // matches GLSL SAMPLE_COUNT
static const float FACE_RESOLUTION = 512.0f;

// Put uniforms into a cbuffer. Only roughness is required here.
cbuffer Params : register(b1)
{
    float roughness;
    float _pad0;
    float _pad1;
    float _pad2; // pad to 16 bytes if you later add more
}

// Input from vertex shader
struct PS_INPUT
{
    float3 modelCoordinates : TEXCOORD0;
};

// radical inverse (Van der Corput) — mirrors GLSL implementation
float radicalInverseVanDerCorput(uint bits)
{
    bits = (bits << 16) | (bits >> 16);
    bits = ((bits & 0x55555555u) << 1) | ((bits & 0xAAAAAAAAu) >> 1);
    bits = ((bits & 0x33333333u) << 2) | ((bits & 0xCCCCCCCCu) >> 2);
    bits = ((bits & 0x0F0F0F0Fu) << 4) | ((bits & 0xF0F0F0F0u) >> 4);
    bits = ((bits & 0x00FF00FFu) << 8) | ((bits & 0xFF00FF00u) >> 8);
    return float(bits) * 2.3283064365386963e-10; // 1.0/2^32
}

// Hammersley low-discrepancy sample
float2 hammersley(uint i, uint N)
{
    return float2(float(i) / float(N), radicalInverseVanDerCorput(i));
}

// Importance sample GGX (maps unit-square -> hemisphere sample direction)
float3 importanceSampleGGX(float2 unitSquareSample, float3 N, float roughness)
{
    float alpha = roughness * roughness;

    float phi = 2.0f * PI * unitSquareSample.x;
    float cosTheta = sqrt((1.0f - unitSquareSample.y) / (1.0f + (alpha * alpha - 1.0f) * unitSquareSample.y));
    float sinTheta = sqrt(max(0.0f, 1.0f - cosTheta * cosTheta));

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

float distributionGGX(float3 N, float3 H, float roughness)
{
    float a = roughness * roughness;
    float a2 = a * a;
    float NdotH = max(dot(N, H), 0.0f);
    float NdotH2 = NdotH * NdotH;

    float numerator = a2;
    float denom = (NdotH2 * (a2 - 1.0f) + 1.0f);
    denom = PI * denom * denom;

    return numerator / denom;
}

float getSampleMipLevel(float3 V, float3 N, float3 H, float roughness)
{
    // distribution PDF based mip selection (same idea as GLSL / LearnOpenGL)
    float distribution = distributionGGX(N, H, roughness);
    float NdotH = max(dot(N, H), 0.0f);
    float HdotV = max(dot(H, V), 0.0f);
    float pdf = distribution * NdotH / (4.0f * HdotV) + 0.0001f;

    float saTexel = 4.0f * PI / (6.0f * FACE_RESOLUTION * FACE_RESOLUTION);
    float saSample = 1.0f / (float(SAMPLE_COUNT) * pdf + 0.0001f);

    return roughness == 0.0f ? 0.0f : 0.5f * log2(saSample / saTexel);
}

float4 main(PS_INPUT input) : SV_Target
{
    float3 N = normalize(input.modelCoordinates);
    // approximation: view direction aligned with N
    float3 V = N;

    float totalWeight = 0.0f;
    float3 outputColor = float3(0.0f, 0.0f, 0.0f);

    // Note: large SAMPLE_COUNT loops can be expensive—this mirrors the GLSL shader exactly.
    for (uint i = 0; i < SAMPLE_COUNT; ++i)
    {
        float2 unitSquareSample = hammersley(i, SAMPLE_COUNT);
        float3 H = importanceSampleGGX(unitSquareSample, N, roughness);
        float3 L = normalize(2.0f * dot(V, H) * H - V);

        float NdotL = max(dot(N, L), 0.0f);
        if (NdotL > 0.0f)
        {
            float mipLevel = getSampleMipLevel(V, N, H, roughness);
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




