// This file was automatically generated from a command line like:
// application_build_helper --inline-text "brdf_convolution_map.frag"
#pragma once


const char g_psz_brdf_convolution_map_frag[] = R"frag_text(// === HLSL Conversion of the OpenGL Shader ===

cbuffer Constants : register(b0)
{
    static const float PI = 3.14159265359;
    static const uint SAMPLE_COUNT = 1024;
}

struct PSInput
{
    float4 position : SV_POSITION;
    float2 texcoord : TEXCOORD0;
};


// regular output
struct PSOutput
{
    float2 brdfcolor : SV_Target0;
    //float4 BloomColor : SV_Target1; // output to be used by bloom shader
};

float radicalInverseVanDerCorput(uint bits)
{
    bits = (bits << 16) | (bits >> 16);
    bits = ((bits & 0x55555555u) << 1) | ((bits & 0xAAAAAAAAu) >> 1);
    bits = ((bits & 0x33333333u) << 2) | ((bits & 0xCCCCCCCCu) >> 2);
    bits = ((bits & 0x0F0F0F0Fu) << 4) | ((bits & 0xF0F0F0F0u) >> 4);
    bits = ((bits & 0x00FF00FFu) << 8) | ((bits & 0xFF00FF00u) >> 8);
    return float(bits) * 2.3283064365386963e-10;
}

float2 hammersley(uint i, uint N)
{
    return float2(float(i) / float(N), radicalInverseVanDerCorput(i));
}

float3 importanceSampleGGX(float2 unitSquareSample, float3 N, float roughness)
{
    float alpha = roughness * roughness;

    float phi = 2.0 * PI * unitSquareSample.x;
    float cosTheta = sqrt((1.0 - unitSquareSample.y) /
                          (1.0 + (alpha * alpha - 1.0) * unitSquareSample.y));
    float sinTheta = sqrt(1.0 - cosTheta * cosTheta);

    float3 H;
    H.x = cos(phi) * sinTheta;
    H.y = sin(phi) * sinTheta;
    H.z = cosTheta;

    float3 up = abs(N.z) < 0.999 ? float3(0.0, 0.0, 1.0) : float3(1.0, 0.0, 0.0);
    float3 tangent = normalize(cross(up, N));
    float3 bitangent = cross(N, tangent);

    float3 sampleVector = tangent * H.x + bitangent * H.y + N * H.z;
    return normalize(sampleVector);
}

float geometrySchlickGGX(float3 n, float3 v, float k)
{
    float nDotV = max(dot(n, v), 0.0);
    float numerator = nDotV;
    float denominator = nDotV * (1.0 - k) + k;
    return numerator / denominator;
}

float geometrySmith(float3 n, float3 v, float3 l, float roughness)
{
    float k = (roughness * roughness) / 2.0;
    return geometrySchlickGGX(n, v, k) * geometrySchlickGGX(n, l, k);
}


PSOutput main(PSInput input)
{
    
    PSOutput output;
    float NdotV = input.texcoord.x;
    float roughness = 1.0 - input.texcoord.y;

    float3 N = float3(0.0, 0.0, 1.0);
    float3 V = float3(sqrt(1.0 - NdotV * NdotV), 0.0, NdotV);

    float F0Scale = 0.0;
    float F0Bias = 0.0;

    [loop]
    for (uint i = 0; i < SAMPLE_COUNT; i++)
    {
        float2 unitSquareSample = hammersley(i, SAMPLE_COUNT);
        float3 H = importanceSampleGGX(unitSquareSample, N, roughness);
        float3 L = normalize(2.0 * dot(V, H) * H - V);

        float NdotL = max(L.z, 0.0);
        float NdotH = max(H.z, 0.0);
        float VdotH = max(dot(V, H), 0.0);

        if (NdotL > 0.0)
        {
            float G = geometrySmith(N, V, L, roughness);
            float GVis = (G * VdotH) / (NdotH * NdotV);
            float partialFresnel = pow(1.0 - VdotH, 5.0);

            F0Scale += GVis * (1.0 - partialFresnel);
            F0Bias += GVis * partialFresnel;
        }
    }

    F0Scale /= SAMPLE_COUNT;
    F0Bias /= SAMPLE_COUNT;

    output.brdfcolor= float2(F0Scale, F0Bias);

    //output.brdfcolor= float2(0.5, 0.5);

    return output;

}



)frag_text";




