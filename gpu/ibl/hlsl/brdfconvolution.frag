// prefilter_brdf_ps.hlsl
// Converted from GLSL (version 330 core) to HLSL for DirectX 11

static const float PI = 3.14159265359f;
static const uint SAMPLE_COUNT = 1024u;

// Radical inverse of Van der Corput sequence
float radicalInverseVanDerCorput(uint bits)
{
    bits = (bits << 16) | (bits >> 16);
    bits = ((bits & 0x55555555) << 1) | ((bits & 0xAAAAAAAA) >> 1);
    bits = ((bits & 0x33333333) << 2) | ((bits & 0xCCCCCCCC) >> 2);
    bits = ((bits & 0x0F0F0F0F) << 4) | ((bits & 0xF0F0F0F0) >> 4);
    bits = ((bits & 0x00FF00FF) << 8) | ((bits & 0xFF00FF00) >> 8);
    return float(bits) * 2.3283064365386963e-10f;
}

// Hammersley sequence on [0,1)^2
float2 hammersley(uint i, uint N)
{
    return float2(float(i) / float(N), radicalInverseVanDerCorput(i));
}

// Importance sample GGX
float3 importanceSampleGGX(float2 Xi, float3 N, float roughness)
{
    float alpha = roughness * roughness;

    float phi = 2.0f * PI * Xi.x;
    float cosTheta = sqrt((1.0f - Xi.y) / (1.0f + (alpha * alpha - 1.0f) * Xi.y));
    float sinTheta = sqrt(1.0f - cosTheta * cosTheta);

    // Spherical to Cartesian
    float3 H;
    H.x = cos(phi) * sinTheta;
    H.y = sin(phi) * sinTheta;
    H.z = cosTheta;

    // Tangent space to world
    float3 up = abs(N.z) < 0.999f ? float3(0.0f, 0.0f, 1.0f) : float3(1.0f, 0.0f, 0.0f);
    float3 tangent = normalize(cross(up, N));
    float3 bitangent = cross(N, tangent);

    float3 sampleVec = tangent * H.x + bitangent * H.y + N * H.z;
    return normalize(sampleVec);
}

// Geometry functions
float geometrySchlickGGX(float nDotV, float k)
{
    return nDotV / (nDotV * (1.0f - k) + k);
}

float geometrySmith(float3 N, float3 V, float3 L, float roughness)
{
    float k = (roughness * roughness) / 2.0f;
    float nDotV = max(dot(N, V), 0.0f);
    float nDotL = max(dot(N, L), 0.0f);
    return geometrySchlickGGX(nDotV, k) * geometrySchlickGGX(nDotL, k);
}

struct PSInput
{
    float4 position : SV_POSITION;
    float2 textureCoordinates : TEXCOORD0;
};

float2 main(PSInput input) : SV_TARGET
{
    float NdotV = input.textureCoordinates.x;
    float roughness = input.textureCoordinates.y;

    float3 N = float3(0.0f, 0.0f, 1.0f);
    float3 V = float3(sqrt(1.0f - NdotV * NdotV), 0.0f, NdotV);

    float F0Scale = 0.0f;
    float F0Bias = 0.0f;

    [loop]
    for (uint i = 0u; i < SAMPLE_COUNT; i++)
    {
        float2 Xi = hammersley(i, SAMPLE_COUNT);
        float3 H = importanceSampleGGX(Xi, N, roughness);
        float3 L = normalize(2.0f * dot(V, H) * H - V);

        float NdotL = max(L.z, 0.0f);
        float NdotH = max(H.z, 0.0f);
        float VdotH = max(dot(V, H), 0.0f);

        if (NdotL > 0.0f)
        {
            float G = geometrySmith(N, V, L, roughness);
            float GVis = (G * VdotH) / (NdotH * NdotV);
            float partialFresnel = pow(1.0f - VdotH, 5.0f);

            F0Scale += GVis * (1.0f - partialFresnel);
            F0Bias += GVis * partialFresnel;
        }
    }

    F0Scale /= SAMPLE_COUNT;
    F0Bias /= SAMPLE_COUNT;

    return float2(F0Scale, F0Bias);
}
