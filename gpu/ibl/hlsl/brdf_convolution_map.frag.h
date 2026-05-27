// This file was automatically generated from a command line like:
// application_build_helper --inline-text "brdf_convolution_map.frag"
#pragma once


const ::i8 g_psz_brdf_convolution_map_frag[] = R"frag_text(// === HLSL Conversion of the OpenGL Shader ===

cbuffer Constants : register(b0)
{
    static const ::f32 PI = 3.14159265359;
    static const uint SAMPLE_COUNT = 1024;
}

struct PSInput
{
    f324 position : SV_POSITION;
    f322 texcoord : TEXCOORD0;
};


// regular output
struct PSOutput
{
    f322 brdfcolor : SV_Target0;
    //f324 BloomColor : SV_Target1; // output to be used by bloom shader
};

::f32 radicalInverseVanDerCorput(uint bits)
{
    bits = (bits << 16) | (bits >> 16);
    bits = ((bits & 0x55555555u) << 1) | ((bits & 0xAAAAAAAAu) >> 1);
    bits = ((bits & 0x33333333u) << 2) | ((bits & 0xCCCCCCCCu) >> 2);
    bits = ((bits & 0x0F0F0F0Fu) << 4) | ((bits & 0xF0F0F0F0u) >> 4);
    bits = ((bits & 0x00FF00FFu) << 8) | ((bits & 0xFF00FF00u) >> 8);
    return ::f32(bits) * 2.3283064365386963e-10;
}

f322 hammersley(uint i, uint N)
{
    return f322(::f32(i) / ::f32(N), radicalInverseVanDerCorput(i));
}

f323 importanceSampleGGX(f322 unitSquareSample, f323 N, ::f32 roughness)
{
    ::f32 alpha = roughness * roughness;

    ::f32 phi = 2.0 * PI * unitSquareSample.x;
    ::f32 cosTheta = sqrt((1.0 - unitSquareSample.y) /
                          (1.0 + (alpha * alpha - 1.0) * unitSquareSample.y));
    ::f32 sinTheta = sqrt(1.0 - cosTheta * cosTheta);

    f323 H;
    H.x = cos(phi) * sinTheta;
    H.y = sin(phi) * sinTheta;
    H.z = cosTheta;

    f323 up = abs(N.z) < 0.999 ? f323(0.0, 0.0, 1.0) : f323(1.0, 0.0, 0.0);
    f323 tangent = normalize(cross(up, N));
    f323 bitangent = cross(N, tangent);

    f323 sampleVector = tangent * H.x + bitangent * H.y + N * H.z;
    return normalize(sampleVector);
}

::f32 geometrySchlickGGX(f323 n, f323 v, ::f32 k)
{
    ::f32 nDotV = max(dot(n, v), 0.0);
    ::f32 numerator = nDotV;
    ::f32 denominator = nDotV * (1.0 - k) + k;
    return numerator / denominator;
}

::f32 geometrySmith(f323 n, f323 v, f323 l, ::f32 roughness)
{
    ::f32 k = (roughness * roughness) / 2.0;
    return geometrySchlickGGX(n, v, k) * geometrySchlickGGX(n, l, k);
}


PSOutput main(PSInput input)
{
    
    PSOutput output;
    ::f32 NdotV = input.texcoord.x;
    ::f32 roughness = 1.0 - input.texcoord.y;

    f323 N = f323(0.0, 0.0, 1.0);
    f323 V = f323(sqrt(1.0 - NdotV * NdotV), 0.0, NdotV);

    ::f32 F0Scale = 0.0;
    ::f32 F0Bias = 0.0;

    [loop]
    for (uint i = 0; i < SAMPLE_COUNT; i++)
    {
        f322 unitSquareSample = hammersley(i, SAMPLE_COUNT);
        f323 H = importanceSampleGGX(unitSquareSample, N, roughness);
        f323 L = normalize(2.0 * dot(V, H) * H - V);

        ::f32 NdotL = max(L.z, 0.0);
        ::f32 NdotH = max(H.z, 0.0);
        ::f32 VdotH = max(dot(V, H), 0.0);

        if (NdotL > 0.0)
        {
            ::f32 G = geometrySmith(N, V, L, roughness);
            ::f32 GVis = (G * VdotH) / (NdotH * NdotV);
            ::f32 partialFresnel = pow(1.0 - VdotH, 5.0);

            F0Scale += GVis * (1.0 - partialFresnel);
            F0Bias += GVis * partialFresnel;
        }
    }

    F0Scale /= SAMPLE_COUNT;
    F0Bias /= SAMPLE_COUNT;

    output.brdfcolor= f322(F0Scale, F0Bias);

    //output.brdfcolor= f322(0.5, 0.5);

    return output;

}



)frag_text";




