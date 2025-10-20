// This file was automatically generated from a command line like:
// application_build_helper --inline-text "pbr.frag"
#pragma once


const char g_psz_pbr_frag[] = R"frag_text(// pbr1.frag
// Converted from Vulkan GLSL to HLSL
// Maintains original comments and structure
// by Camilo <3ThomasBorregaardSorensen!!
// Shader Model 5.0+ recommended

#define PI 3.1415926535897932384626433832795
#define GREYSCALE_WEIGHT_VECTOR float3(0.2126, 0.7152, 0.0722)

// regular output
struct PSOutput
{
    float4 FragColor : SV_Target0;
    //float4 BloomColor : SV_Target1; // output to be used by bloom shader
};

// vertex inputs (match your vertex shader semantics)
struct PSInput
{
    float4 Position          : SV_Position;
    float3 worldCoordinates : TEXCOORD0;
    float2 textureCoordinates : TEXCOORD1;
    float3 tangent : TEXCOORD2;
    float3 bitangent : TEXCOORD3;
    float3 normal : TEXCOORD4;
};

// ---------- Structures ----------

struct PointLight
{
    float4 position;
    float4 color;
};

// ---------- Global UBO (set 0 binding 0) ----------
cbuffer GlobalUbo : register(b0)
{
    float4x4 projection;
    float4x4 view;
    float4x4 invView;
    float4 ambientLightColor;
    float4 viewPos;
    PointLight pointLights[10];
    int numLights;
    int padding1;
    int padding2;
    int padding3;
};

// ---------- Push constants (converted to another cbuffer) ----------
cbuffer PushConsts : register(b1)
{
    float4x4 modelMatrix;
    float4x4 normalMatrix; // inverse-transpose of model

    int useTextureAlbedo;
    int useTextureMetallicRoughness;
    int useTextureNormal;
    int useTextureAmbientOcclusion;
    int useTextureEmissive;

    float3 albedo;
    float metallic;
    float roughness;
    float ambientOcclusion;
    float3 emissive;

    float3 cameraPosition;
    float bloomBrightnessCutoff;
};

// ---------- Texture bindings ----------

// IBL maps (set = 1)
TextureCube diffuseIrradianceMap : register(t0);
TextureCube prefilteredEnvMap     : register(t1);
Texture2D   brdfConvolutionMap    : register(t2);
SamplerState samplerIBL           : register(s0);

// Combined image samplers (set = 2)
Texture2D textureAlbedo            : register(t3);
Texture2D textureMetallicRoughness : register(t4);
Texture2D textureNormal            : register(t5);
Texture2D textureAmbientOcclusion  : register(t6);
Texture2D textureEmissive          : register(t7);
SamplerState samplerMaterial       : register(s1);

// ---------- Helper wrappers ----------

float3 getAlbedo(float2 texCoord)
{
    float3 a = albedo;
    if (useTextureAlbedo != 0)
    {
        a = textureAlbedo.Sample(samplerMaterial, texCoord).rgb;
    }
    return a;
}

void getMetallicRoughness(float2 texCoord, out float metallicOut, out float roughnessOut)
{
    metallicOut = metallic;
    roughnessOut = roughness;
    if (useTextureMetallicRoughness != 0)
    {
        float3 mr = textureMetallicRoughness.Sample(samplerMaterial, texCoord).rgb;
        metallicOut = mr.b;
        roughnessOut = mr.g;
    }
}

float3 getNormal(float3 interpNormal, float2 texCoord, float3 tangent, float3 bitangent, float3 normal)
{
    float3 n = normalize(interpNormal);
    if (useTextureNormal != 0)
    {
        float3 tangentNormal = textureNormal.Sample(samplerMaterial, texCoord).rgb;
        float3 norm = normalize(tangentNormal * 2.0 - 1.0);
        //norm.y = -norm.y;
        float3x3 TBN = float3x3(tangent, bitangent, normal);
        n = normalize(mul(norm, TBN));
    }
    return n;
}

float getAO(float2 texCoord)
{
    float ao = ambientOcclusion;
    if (useTextureAmbientOcclusion != 0)
    {
        ao = textureAmbientOcclusion.Sample(samplerMaterial, texCoord).r;
    }
    return ao;
}

float3 getEmissive(float2 texCoord)
{
    float3 e = emissive;
    if (useTextureEmissive != 0)
    {
        e = textureEmissive.Sample(samplerMaterial, texCoord).rgb;
    }
    return e;
}

// ---------- PBR helper functions ----------

float3 fresnelSchlick(float cosTheta, float3 f0)
{
    return f0 + (1.0 - f0) * pow(max(1.0 - cosTheta, 0.0), 5.0);
}

float3 fresnelSchlickRoughness(float cosTheta, float3 f0, float roughness)
{
    return f0 + (max(float3(1.0 - roughness, 1.0 - roughness, 1.0 - roughness), f0) - f0)
        * pow(saturate(1.0 - cosTheta), 5.0);
}

float ndfTrowbridgeReitzGGX(float3 n, float3 h, float roughness)
{
    float alpha = roughness * roughness;
    float alphaSquared = alpha * alpha;
    float nDotH = max(dot(n, h), 0.0);
    float nDotHSquared = nDotH * nDotH;
    float innerTerms = nDotHSquared * (alphaSquared - 1.0) + 1.0;
    float numerator = alphaSquared;
    float denominator = PI * innerTerms * innerTerms;
    denominator = max(denominator, 0.0001);
    return numerator / denominator;
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
    float k = (roughness + 1.0) * (roughness + 1.0) / 8.0;
    return geometrySchlickGGX(n, v, k) * geometrySchlickGGX(n, l, k);
}

// ---------- main ----------

PSOutput main(PSInput input)
{
    PSOutput output;

    float3 worldPos = input.worldCoordinates;
    float3 albedoVal = getAlbedo(input.textureCoordinates);

    float metallicVal;
    float roughnessVal;
    getMetallicRoughness(input.textureCoordinates, metallicVal, roughnessVal);

    float3 n = getNormal(input.normal, input.textureCoordinates, input.tangent, input.bitangent, input.normal);
    float ao = getAO(input.textureCoordinates);
    float3 emissiveVal = getEmissive(input.textureCoordinates);

    // camera position: prefer push constant, fallback to globalUbo.viewPos.xyz
    float3 cameraPos = cameraPosition;
    // If you don't use push constants, you can use globalUbo.viewPos.xyz instead.
    // float3 cameraPos = viewPos.xyz;

    float3 v = normalize(cameraPos - worldPos);
    float3 r = reflect(-v, n);

    float3 f0 = float3(0.04, 0.04, 0.04);
    f0 = lerp(f0, albedoVal, metallicVal);

    float3 Lo = float3(0.0, 0.0, 0.0);

    // Direct lights: use up to 4 (your loop used 4). Use min with provided numLights.
    int maxDirect = min(4, numLights);
    [loop]
    for (int i = 0; i < maxDirect; ++i)
    {
        float3 lightPos = pointLights[i].position.xyz;
        float3 lightColor = pointLights[i].color.rgb;

        float3 l = normalize(lightPos - worldPos);
        float3 h = normalize(v + l);

        float distance = length(lightPos - worldPos);
        float attenuation = 1.0 / max(distance * distance, 0.0001);
        float3 radiance = lightColor * attenuation;

        float dTerm = ndfTrowbridgeReitzGGX(n, h, roughnessVal);
        float3 fTerm = fresnelSchlick(max(dot(h, v), 0.0), f0);
        float gTerm = geometrySmith(n, v, l, roughnessVal);

        float3 numerator = dTerm * fTerm * gTerm;
        float denominator = 4.0 * max(dot(v, n), 0.0) * max(dot(l, n), 0.0);
        float3 specular = numerator / max(denominator, 0.001);

        float3 kSpecular = fTerm;
        float3 kDiffuse = (1.0 - kSpecular) * (1.0 - metallicVal);

        float3 diffuse = kDiffuse * albedoVal / PI;
        float3 cookTorranceBrdf = diffuse + specular;
        float nDotL = max(dot(n, l), 0.0);

        Lo += cookTorranceBrdf * radiance * nDotL;
    }

    // Indirect lighting (IBL)
    float3 kSpecular = fresnelSchlickRoughness(max(dot(n, v), 0.0), f0, roughnessVal);
    float3 kDiffuse = (1.0 - kSpecular) * (1.0 - metallicVal);

    float3 irradiance = diffuseIrradianceMap.Sample(samplerIBL, n).rgb;
    float3 diffuseIBL = irradiance * albedoVal;

    float3 prefilteredEnvMapColor = prefilteredEnvMap.SampleLevel(samplerIBL, r, roughnessVal * 4.0).rgb; // PREFILTERED_ENV_MAP_LOD = 4.0
    float NdotV = max(dot(n, v), 0.0);
    float2 brdf = brdfConvolutionMap.Sample(samplerIBL, float2(NdotV, roughnessVal)).rg;
    float3 specularIBL = prefilteredEnvMapColor * (kSpecular * brdf.x + brdf.y);

    float3 ambient = (kDiffuse * diffuseIBL + specularIBL) * ao;

    float3 color = emissiveVal + ambient + Lo;

    output.FragColor = float4(color, 1.0);
    //output.FragColor = float4(albedoVal, 1.0);
    //output.FragColor = float4(input.tangent * 0.5 + 0.5, 1.0); // visualize tangent

    //float greyscaleBrightness = dot(output.FragColor.rgb, GREYSCALE_WEIGHT_VECTOR);
    //output.BloomColor = greyscaleBrightness > bloomBrightnessCutoff ? output.FragColor : float4(0.0, 0.0, 0.0, 0.0);

    return output;
}
)frag_text";




