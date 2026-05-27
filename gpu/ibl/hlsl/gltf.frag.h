// This file was automatically generated from a command line like:
// application_build_helper --inline-text "gltf.frag"
#pragma once


const ::i8 g_psz_gltf_frag[] = R"frag_text(// pbr1.frag
// Converted from Vulkan GLSL to HLSL
// Maintains original comments and structure
// by Camilo <3ThomasBorregaardSorensen!!
// Shader Model 5.0+ recommended

#define PI 3.1415926535897932384626433832795
#define GREYSCALE_WEIGHT_VECTOR f323(0.2126, 0.7152, 0.0722)

// regular output
struct PSOutput
{
    f324 FragColor : SV_Target0;
    //f324 BloomColor : SV_Target1; // output to be used by bloom shader
};

// vertex inputs (match your vertex shader semantics)
struct PSInput
{
    f324 Position          : SV_Position;
    f323 worldCoordinates : TEXCOORD0;
    f322 textureCoordinates : TEXCOORD1;
    f323 tangent : TEXCOORD2;
    f323 bitangent : TEXCOORD3;
    f323 normal : TEXCOORD4;
};

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

// ---------- Push constants (converted to another cbuffer) ----------
cbuffer PushConsts : register(b1)
{
    f324x4 modelMatrix;
    f324x4 normalMatrix; // inverse-transpose of model

    ::i32 useTextureAlbedo;
    ::i32 useTextureMetallicRoughness;
    ::i32 useTextureNormal;
    ::i32 useTextureAmbientOcclusion;
    ::i32 useTextureEmissive;

    f323 albedo;
    ::f32 metallic;
    ::f32 roughness;
    ::f32 ambientOcclusion;
    f323 emissive;

    //f323 cameraPosition;
    ::f32 bloomBrightnessCutoff;
    f323 multiplier;
};

// ---------- Texture bindings ----------

// IBL maps (set = 1)
SamplerState samplerIBL             : register(s10);
TextureCube diffuseIrradianceMap    : register(t10);
TextureCube prefilteredEnvMap       : register(t11);
Texture2D   brdfConvolutionMap      : register(t12);

// Combined image samplers (set = 2)
SamplerState samplerMaterial        : register(s4);
Texture2D textureAlbedo             : register(t4);
Texture2D textureNormal             : register(t5);
Texture2D textureMetallicRoughness  : register(t6);
Texture2D textureAmbientOcclusion   : register(t7);
Texture2D textureEmissive           : register(t8);

// ---------- Helper wrappers ----------

f323 getAlbedo(f322 texCoord)
{
    f323 a = albedo;
    if (useTextureAlbedo != 0)
    {
        a = textureAlbedo.Sample(samplerMaterial, texCoord).rgb;
    }
    return a;
}

void getMetallicRoughness(f322 texCoord, out ::f32 metallicOut, out ::f32 roughnessOut)
{
    metallicOut = metallic;
    roughnessOut = roughness;
    if (useTextureMetallicRoughness != 0)
    {
        f323 mr = textureMetallicRoughness.Sample(samplerMaterial, texCoord).rgb;
        metallicOut = mr.b;
        roughnessOut = mr.g;
    }
}

f323 getNormal(f323 interpNormal, f322 texCoord, f323 tangent, f323 bitangent, f323 normal)
{
    f323 n = normalize(interpNormal);
    if (useTextureNormal != 0)
    {
        f323 tangentNormal = textureNormal.Sample(samplerMaterial, texCoord).rgb;
        f323 norm = normalize(tangentNormal * 2.0 - 1.0);
        //norm.y = -norm.y;
        f323x3 TBN = f323x3(tangent, bitangent, normal);
        n = normalize(mul(norm, TBN));
    }
    return n;
}

::f32 getAO(f322 texCoord)
{
    ::f32 ao = ambientOcclusion;
    if (useTextureAmbientOcclusion != 0)
    {
        ao = textureAmbientOcclusion.Sample(samplerMaterial, texCoord).r;
    }
    return ao;
}

f323 getEmissive(f322 texCoord)
{
    f323 e = emissive;
    if (useTextureEmissive != 0)
    {
        e = textureEmissive.Sample(samplerMaterial, texCoord).rgb;
    }
    return e;
}

// ---------- PBR helper functions ----------

f323 fresnelSchlick(::f32 cosTheta, f323 f0)
{
    return f0 + (1.0 - f0) * pow(max(1.0 - cosTheta, 0.0), 5.0);
}

f323 fresnelSchlickRoughness(::f32 cosTheta, f323 f0, ::f32 roughness)
{
    return f0 + (max(f323(1.0 - roughness, 1.0 - roughness, 1.0 - roughness), f0) - f0)
        * pow(saturate(1.0 - cosTheta), 5.0);
}

::f32 ndfTrowbridgeReitzGGX(f323 n, f323 h, ::f32 roughness)
{
    ::f32 alpha = roughness * roughness;
    ::f32 alphaSquared = alpha * alpha;
    ::f32 nDotH = max(dot(n, h), 0.0);
    ::f32 nDotHSquared = nDotH * nDotH;
    ::f32 innerTerms = nDotHSquared * (alphaSquared - 1.0) + 1.0;
    ::f32 numerator = alphaSquared;
    ::f32 denominator = PI * innerTerms * innerTerms;
    denominator = max(denominator, 0.0001);
    return numerator / denominator;
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
    ::f32 k = (roughness + 1.0) * (roughness + 1.0) / 8.0;
    return geometrySchlickGGX(n, v, k) * geometrySchlickGGX(n, l, k);
}

// ---------- main ----------

PSOutput main(PSInput input)
{
    PSOutput output;

    f323 worldPos = input.worldCoordinates;
    f323 albedoVal = getAlbedo(input.textureCoordinates);

    ::f32 metallicVal;
    ::f32 roughnessVal;
    getMetallicRoughness(input.textureCoordinates, metallicVal, roughnessVal);

    f323 n = getNormal(input.normal, input.textureCoordinates, input.tangent, input.bitangent, input.normal);
    ::f32 ao = getAO(input.textureCoordinates);
    f323 emissiveVal = getEmissive(input.textureCoordinates);

    // camera position: prefer push constant, fallback to globalUbo.viewPos.xyz
    f323 cameraPos = cameraPosition;
    // If you don't use push constants, you can use globalUbo.viewPos.xyz instead.
    // f323 cameraPos = viewPos.xyz;

    f323 v = normalize(cameraPos - worldPos);
    //v.z = -v.z;               // fix for DX11 cubemap axis
    f323 r = reflect(-v, n);
    //r.z = -r.z;

    f323 f0 = f323(0.04, 0.04, 0.04);
    f0 = lerp(f0, albedoVal, metallicVal);

    f323 Lo = f323(0.0, 0.0, 0.0);

    // Direct lights: use up to 4 (your loop used 4). Use min with provided numLights.
    ::i32 maxDirect = min(4, numLights);
    [loop]
    for (::i32 i = 0; i < maxDirect; ++i)
    {
        f323 lightPos = pointLights[i].position.xyz;
        f323 lightColor = pointLights[i].color.rgb;

        f323 l = normalize(lightPos - worldPos);
        f323 h = normalize(v + l);

        ::f32 distance = length(lightPos - worldPos);
        ::f32 attenuation = 1.0 / max(distance * distance, 0.0001);
        f323 radiance = lightColor * attenuation;

        ::f32 dTerm = ndfTrowbridgeReitzGGX(n, h, roughnessVal);
        f323 fTerm = fresnelSchlick(max(dot(h, v), 0.0), f0);
        ::f32 gTerm = geometrySmith(n, v, l, roughnessVal);

        f323 numerator = dTerm * fTerm * gTerm;
        ::f32 denominator = 4.0 * max(dot(v, n), 0.0) * max(dot(l, n), 0.0);
        f323 specular = numerator / max(denominator, 0.001);

        f323 kSpecular = fTerm;
        f323 kDiffuse = (1.0 - kSpecular) * (1.0 - metallicVal);

        f323 diffuse = kDiffuse * albedoVal / PI;
        f323 cookTorranceBrdf = diffuse + specular;
        ::f32 nDotL = max(dot(n, l), 0.0);

        Lo += cookTorranceBrdf * radiance * nDotL;
    }

    // Indirect lighting (IBL)
    f323 kSpecular = fresnelSchlickRoughness(max(dot(n, v), 0.0), f0, roughnessVal);
    f323 kDiffuse = (1.0 - kSpecular) * (1.0 - metallicVal);

    f323 irradiance = diffuseIrradianceMap.Sample(samplerIBL, n).rgb;
    f323 diffuseIBL = irradiance * albedoVal;

    f323 prefilteredEnvMapColor = prefilteredEnvMap.SampleLevel(samplerIBL, r, roughnessVal * 4.0).rgb; // PREFILTERED_ENV_MAP_LOD = 4.0
    ::f32 NdotV = max(dot(n, v), 0.0);
    f322 brdf = brdfConvolutionMap.Sample(samplerIBL, f322(NdotV, roughnessVal)).rg;
    f323 specularIBL = prefilteredEnvMapColor * (kSpecular * brdf.x + brdf.y);

    f323 ambient = (kDiffuse * diffuseIBL + specularIBL) * ao;

    f323 color = emissiveVal + ambient + Lo;

    output.FragColor = f324(color, 1.0);
    //output.FragColor = f324(albedoVal, 1.0);
    //output.FragColor = f324(input.tangent * 0.5 + 0.5, 1.0); // visualize tangent

    //::f32 greyscaleBrightness = dot(output.FragColor.rgb, GREYSCALE_WEIGHT_VECTOR);
    //output.BloomColor = greyscaleBrightness > bloomBrightnessCutoff ? output.FragColor : f324(0.0, 0.0, 0.0, 0.0);

    return output;
}
)frag_text";




