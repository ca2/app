// This file was automatically generated from a command line like:
// application_build_helper --inline-text "scene.frag"
#pragma once


const char g_psz_scene_frag[] = R"frag_text(// scene_ps.hlsl
// Shader Model 5.0

#define PI 3.14159265359


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
    float4 cameraPosition;
    PointLight pointLights[10];
    int numLights;
};

cbuffer PushConsts : register(b1)
{
    float4x4 modelMatrix;
    float4x4 normalMatrix;

    int   useTextureAlbedo;
    int   useTextureNormal;
    int   useAlphaMask;

    float3 albedo;
    float  metallic;
    float  roughness;
    float  ambientOcclusion;
    float  alphaMaskCutoff;
    float prefilteredEnvMapMaxLod;
};

// ---------- IBL (set = 1) ----------
SamplerState samplerIBL           : register(s10);
TextureCube diffuseIrradianceMap  : register(t10);
TextureCube prefilteredEnvMap     : register(t11);
Texture2D   brdfConvolutionMap    : register(t12);


// Combined image samplers (set = 2)
SamplerState samplerMaterial        : register(s4);
Texture2D textureAlbedo             : register(t4);
Texture2D textureNormal             : register(t5);


struct PSInput
{
    float4 position : SV_POSITION;
    float3 worldPos : TEXCOORD0;
    float3 normal   : TEXCOORD1;
    float2 uv       : TEXCOORD2;
    float4 color    : COLOR0;
    float3 tangent  : TEXCOORD3;
    float3 bitangent: TEXCOORD4;
};

float3 fresnelSchlick(float cosTheta, float3 F0)
{
    return F0 + (1.0 - F0) * pow(1.0 - cosTheta, 5.0);
}

float4 getAlbedo(PSInput IN)
{
    float4 a = float4(albedo, 1.0);
    if (useTextureAlbedo != 0)
        a = textureAlbedo.Sample(samplerMaterial, IN.uv);
    return a;
}

float4 main(PSInput IN) : SV_TARGET
{
    float4 texColor = getAlbedo(IN) * IN.color;

    if (useAlphaMask != 0 && texColor.a < alphaMaskCutoff)
        discard;

    float3 N = normalize(IN.normal);

    if (useTextureNormal != 0)
    {
        float3 nMap = textureNormal.Sample(samplerMaterial, IN.uv).xyz * 2.0 - 1.0;
        float3x3 TBN = float3x3(IN.tangent, IN.bitangent, IN.normal);
        N = normalize(mul(nMap, TBN));
    }

    float3 V = normalize(cameraPosition - IN.worldPos);
    float NdotV = saturate(dot(N, V));

    // ---------- Direct lighting ----------
    float3 lighting = 0;

    for (int i = 0; i < numLights; ++i)
    {

        float3 lightPos = pointLights[i].position.xyz;
        float4 lightColor = pointLights[i].color;

        float3 L = normalize(lightPos - IN.worldPos);
        float3 H = normalize(L + V);

        float NdotL = saturate(dot(N, L));
        if (NdotL <= 0) continue;

        float3 lightCol = lightColor.rgb * lightColor.a;

        float spec = pow(saturate(dot(H, N)), 32.0);

        lighting += texColor.rgb * NdotL * lightCol + spec * lightCol;
    }

    // ---------- IBL ----------
    float metallicV  = metallic;
    float roughV    = saturate(roughness);
    float ao        = ambientOcclusion;

    float3 F0 = lerp(float3(0.04, 0.04, 0.04), texColor.rgb, metallicV);

    float3 irradiance = diffuseIrradianceMap.Sample(samplerIBL, N).rgb;
    float3 diffuseIBL = irradiance * texColor.rgb;

    float3 R = reflect(-V, N);

    //uint mipCount;
    //prefilteredEnvMap.GetDimensions(0, mipCount);
    //float maxLod = max(0.0, mipCount - 1.0);

    float3 prefiltered =
        prefilteredEnvMap.SampleLevel(samplerIBL, R, roughV * prefilteredEnvMapMaxLod).rgb;

    float2 brdf =
        brdfConvolutionMap.Sample(samplerIBL, float2(NdotV, roughV)).rg;

    float3 F = fresnelSchlick(NdotV, F0);
    float3 kD = (1.0 - F) * (1.0 - metallicV);

    float3 ambientIBL =
        (diffuseIBL * kD + prefiltered * (F * brdf.x + brdf.y)) * ao;

    // NOTE: matches your current Vulkan output
    return float4(lighting, texColor.a);
}
)frag_text";




