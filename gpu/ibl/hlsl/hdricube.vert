//------------------------------------------------------------------------------
// PBR Fragment Shader (HLSL)
// Converted from GLSL #version 330 core
//------------------------------------------------------------------------------

#define PI 3.14159265358979323846
#define GREYSCALE_WEIGHT_VECTOR float3(0.2126, 0.7152, 0.0722)
#define PREFILTERED_ENV_MAP_LOD 4.0

//------------------------------------------------------------------------------
// Texture and Samplers
//------------------------------------------------------------------------------
Texture2D textureAlbedo            : register(t0);
Texture2D textureMetallicRoughness : register(t1);
Texture2D textureNormal            : register(t2);
Texture2D textureAmbientOcclusion  : register(t3);
Texture2D textureEmissive          : register(t4);

TextureCube diffuseIrradianceMap   : register(t5);
TextureCube prefilteredEnvMap      : register(t6);
Texture2D brdfConvolutionMap       : register(t7);

SamplerState samplerLinear : register(s0);

//------------------------------------------------------------------------------
// Material Parameters
//------------------------------------------------------------------------------
cbuffer MaterialBuffer : register(b0)
{
    bool   useTextureAlbedo;
    bool   useTextureMetallicRoughness;
    bool   useTextureNormal;
    bool   useTextureAmbientOcclusion;
    bool   useTextureEmissive;

    float3 albedo;
    float  metallic;
    float  roughness;
    float  ambientOcclusion;
    float3 emissive;
    float  bloomBrightnessCutoff;
};

//------------------------------------------------------------------------------
// Camera and Lights
//------------------------------------------------------------------------------
cbuffer SceneBuffer : register(b1)
{
    float3 cameraPosition;
    float  _padding1;

    float3 lightPositions[4];
    float  _padding2;

    float3 lightColors[4];
    float  _padding3;
};

//------------------------------------------------------------------------------
// Vertex to Pixel Input
//------------------------------------------------------------------------------
struct PS_INPUT
{
    float4 position          : SV_POSITION;
    float3 worldCoordinates  : TEXCOORD1;
    float2 textureCoordinates: TEXCOORD0;
    float3 tangent           : TEXCOORD2;
    float3 bitangent         : TEXCOORD3;
    float3 normal            : TEXCOORD4;
};

//------------------------------------------------------------------------------
// Helper Functions
//------------------------------------------------------------------------------
float3 fresnelSchlick(float cosTheta, float3 f0)
{
    return f0 + (1.0f - f0) * pow(saturate(1.0f - cosTheta), 5.0f);
}

float3 fresnelSchlickRoughness(float cosTheta, float3 f0, float roughness)
{
    return f0 + (max(float3(1.0f - roughness), f0) - f0) * pow(saturate(1.0f - cosTheta), 5.0f);
}

float ndfTrowbridgeReitzGGX(float3 n, float3 h, float roughness)
{
    float a = roughness * roughness;
    float a2 = a * a;
    float nDotH = saturate(dot(n, h));
    float nDotH2 = nDotH * nDotH;

    float denom = PI * pow(nDotH2 * (a2 - 1.0f) + 1.0f, 2.0f);
    return a2 / max(denom, 0.0001f);
}

float geometrySchlickGGX(float nDotV, float k)
{
    return nDotV / (nDotV * (1.0f - k) + k);
}

float geometrySmith(float3 n, float3 v, float3 l, float roughness)
{
    float k = (roughness + 1.0f);
    k = (k * k) / 8.0f;

    float nDotV = saturate(dot(n, v));
    float nDotL = saturate(dot(n, l));

    return geometrySchlickGGX(nDotV, k) * geometrySchlickGGX(nDotL, k);
}

float3 calculateNormal(float3 tangentNormal, float3 tangent, float3 bitangent, float3 normal)
{
    float3 n = normalize(tangentNormal * 2.0f - 1.0f);
    float3x3 TBN = float3x3(tangent, bitangent, normal);
    return normalize(mul(n, TBN));
}

//------------------------------------------------------------------------------
// Pixel Shader Entry
//------------------------------------------------------------------------------
struct PS_OUTPUT
{
    float4 FragColor : SV_TARGET0;
    float4 BloomColor : SV_TARGET1;
};

PS_OUTPUT main(PS_INPUT input)
{
    PS_OUTPUT output;

    // Material values
    float3 albedoValue = albedo;
    if (useTextureAlbedo)
        albedoValue = textureAlbedo.Sample(samplerLinear, input.textureCoordinates).rgb;

    float metallicValue = metallic;
    float roughnessValue = roughness;
    if (useTextureMetallicRoughness)
    {
        float3 mr = textureMetallicRoughness.Sample(samplerLinear, input.textureCoordinates).rgb;
        metallicValue = mr.b;
        roughnessValue = mr.g;
    }

    float3 n = normalize(input.normal);
    if (useTextureNormal)
    {
        float3 normalMap = textureNormal.Sample(samplerLinear, input.textureCoordinates).rgb;
        n = calculateNormal(normalMap, input.tangent, input.bitangent, input.normal);
    }

    float ao = ambientOcclusion;
    if (useTextureAmbientOcclusion)
        ao = textureAmbientOcclusion.Sample(samplerLinear, input.textureCoordinates).r;

    float3 emissiveValue = emissive;
    if (useTextureEmissive)
        emissiveValue = textureEmissive.Sample(samplerLinear, input.textureCoordinates).rgb;

    float3 v = normalize(cameraPosition - input.worldCoordinates);
    float3 r = reflect(-v, n);

    float3 f0 = float3(0.04f, 0.04f, 0.04f);
    f0 = lerp(f0, albedoValue, metallicValue);

    float3 Lo = float3(0.0f, 0.0f, 0.0f);

    // Direct lighting
    [unroll]
    for (int i = 0; i < 4; ++i)
    {
        float3 l = normalize(lightPositions[i] - input.worldCoordinates);
        float3 h = normalize(v + l);

        float distance = length(lightPositions[i] - input.worldCoordinates);
        float attenuation = 1.0f / (distance * distance);
        float3 radiance = lightColors[i] * attenuation;

        float D = ndfTrowbridgeReitzGGX(n, h, roughnessValue);
        float3 F = fresnelSchlick(saturate(dot(h, v)), f0);
        float G = geometrySmith(n, v, l, roughnessValue);

        float3 numerator = D * F * G;
        float denominator = 4.0f * saturate(dot(v, n)) * saturate(dot(l, n)) + 0.001f;
        float3 specular = numerator / denominator;

        float3 kSpecular = F;
        float3 kDiffuse = (1.0f - kSpecular) * (1.0f - metallicValue);

        float3 diffuse = kDiffuse * albedoValue / PI;
        float nDotL = saturate(dot(n, l));

        Lo += (diffuse + specular) * radiance * nDotL;
    }

    // Indirect lighting (IBL)
    float3 F = fresnelSchlickRoughness(saturate(dot(n, v)), f0, roughnessValue);
    float3 kDiffuse = (1.0f - F) * (1.0f - metallicValue);

    float3 irradiance = diffuseIrradianceMap.Sample(samplerLinear, n).rgb;
    float3 diffuse = irradiance * albedoValue;

    float3 prefilteredColor = prefilteredEnvMap.SampleLevel(samplerLinear, r, roughnessValue * PREFILTERED_ENV_MAP_LOD).rgb;
    float NdotV = saturate(dot(n, v));
    float2 brdf = brdfConvolutionMap.Sample(samplerLinear, float2(NdotV, roughnessValue)).rg;

    float3 specular = prefilteredColor * (F * brdf.x + brdf.y);
    float3 ambient = (kDiffuse * diffuse + specular) * ao;

    float3 color = emissiveValue + ambient + Lo;

    // Main color output
    output.FragColor = float4(color, 1.0f);

    // Bloom output
    float greyscaleBrightness = dot(output.FragColor.rgb, GREYSCALE_WEIGHT_VECTOR);
    output.BloomColor = (greyscaleBrightness > bloomBrightnessCutoff)
        ? float4(emissiveValue, 1.0f)
        : float4(0.0f, 0.0f, 0.0f, 1.0f);

    return output;
}
