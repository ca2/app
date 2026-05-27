// This file was automatically generated from a command line like:
// application_build_helper --inline-text "scene.frag"
#pragma once


const ::i8 g_psz_scene_frag[] = R"frag_text(// scene_ps.hlsl
// Shader Model 5.0

#define PI 3.14159265359


// ---------- Structures ----------

struct PointLight
{
    f324 position;
    f324 color;
};

// ---------- Global UBO (set 0 binding 0) ----------
cbuffer GlobalUbo : register(b0)
{
    f324x4 projection;
    f324x4 view;
    f324x4 invView;
    f324 ambientLightColor;
    f324 cameraPosition;
    PointLight pointLights[10];
    ::i32 numLights;
};

cbuffer PushConsts : register(b1)
{
    f324x4 modelMatrix;
    f324x4 normalMatrix;

    ::i32   useTextureAlbedo;
    ::i32   useTextureNormal;
    ::i32   useAlphaMask;

    f323 albedo;
    ::f32  metallic;
    ::f32  roughness;
    ::f32  ambientOcclusion;
    ::f32  alphaMaskCutoff;
    ::f32 prefilteredEnvMapMaxLod;
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
    f324 position : SV_POSITION;
    f323 worldPos : TEXCOORD0;
    f323 normal   : TEXCOORD1;
    f322 uv       : TEXCOORD2;
    f324 color    : COLOR0;
    f323 tangent  : TEXCOORD3;
    f323 bitangent: TEXCOORD4;
};

f323 fresnelSchlick(::f32 cosTheta, f323 F0)
{
    return F0 + (1.0 - F0) * pow(1.0 - cosTheta, 5.0);
}

f324 getAlbedo(PSInput IN)
{
    f324 a = f324(albedo, 1.0);
    if (useTextureAlbedo != 0)
        a = textureAlbedo.Sample(samplerMaterial, IN.uv);
    return a;
}

f324 main(PSInput IN) : SV_TARGET
{
    f324 texColor = getAlbedo(IN) * IN.color;

    if (useAlphaMask != 0 && texColor.a < alphaMaskCutoff)
        discard;

    f323 N = normalize(IN.normal);

    if (useTextureNormal != 0)
    {
        f323 nMap = textureNormal.Sample(samplerMaterial, IN.uv).xyz * 2.0 - 1.0;
        f323x3 TBN = f323x3(IN.tangent, IN.bitangent, IN.normal);
        N = normalize(mul(nMap, TBN));
    }

    f323 V = normalize(cameraPosition - IN.worldPos);
    ::f32 NdotV = saturate(dot(N, V));

    // ---------- Direct lighting ----------
    f323 lighting = 0;

    for (::i32 i = 0; i < numLights; ++i)
    {

        f323 lightPos = pointLights[i].position.xyz;
        f324 lightColor = pointLights[i].color;

        f323 L = normalize(lightPos - IN.worldPos);
        f323 H = normalize(L + V);

        ::f32 NdotL = saturate(dot(N, L));
        if (NdotL <= 0) continue;

        f323 lightCol = lightColor.rgb * lightColor.a;

        ::f32 spec = pow(saturate(dot(H, N)), 32.0);

        lighting += texColor.rgb * NdotL * lightCol + spec * lightCol;
    }

    // ---------- IBL ----------
    ::f32 metallicV  = metallic;
    ::f32 roughV    = saturate(roughness);
    ::f32 ao        = ambientOcclusion;

    f323 F0 = lerp(f323(0.04, 0.04, 0.04), texColor.rgb, metallicV);

    f323 irradiance = diffuseIrradianceMap.Sample(samplerIBL, N).rgb;
    f323 diffuseIBL = irradiance * texColor.rgb;

    f323 R = reflect(-V, N);

    //uint mipCount;
    //prefilteredEnvMap.GetDimensions(0, mipCount);
    //::f32 maxLod = max(0.0, mipCount - 1.0);

    f323 prefiltered =
        prefilteredEnvMap.SampleLevel(samplerIBL, R, roughV * prefilteredEnvMapMaxLod).rgb;

    f322 brdf =
        brdfConvolutionMap.Sample(samplerIBL, f322(NdotV, roughV)).rg;

    f323 F = fresnelSchlick(NdotV, F0);
    f323 kD = (1.0 - F) * (1.0 - metallicV);

    f323 ambientIBL =
        (diffuseIBL * kD + prefiltered * (F * brdf.x + brdf.y)) * ao;

    // NOTE: matches your current Vulkan output
    return f324(lighting, texColor.a);
}
)frag_text";




