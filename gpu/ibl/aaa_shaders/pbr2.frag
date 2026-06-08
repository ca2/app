// pbr2.frag
// ======================================================
// HLSL Fragment Shader (PBR) - Vulkan GLSL -> HLSL
// ======================================================

#define PI 3.1415926535897932384626433832795
static const float3 GREYSCALE_WEIGHT_VECTOR = float3(0.2126, 0.7152, 0.0722);

// Vertex outputs
struct PSInput
{
float4 position         : SV_Position; // clip-space
    float3 worldCoordinates : TEXCOORD0;
    float2 texCoord         : TEXCOORD1;
    float3 tangent          : TEXCOORD2;
    float3 bitangent        : TEXCOORD3;
    float3 normal           : TEXCOORD4;
};

// ---------- Point light struct ----------
struct PointLight
{
    float4 position;
    float4 color;
};

// ---------- Global UBO (b0) ----------
cbuffer GlobalUbo : register(b0)
{
    float4x4 projection;
    float4x4 view;
    float4x4 invView;
    float4   ambientLightColor;
    float4   viewPos;
    PointLight pointLights[10];
    int numLights;
    int padding1;
    int padding2;
    int padding3;
};

// ---------- Samplers / textures ----------
TextureCube diffuseIrradianceMap       : register(t0);
TextureCube prefilteredEnvMap          : register(t1);
Texture2D   brdfConvolutionMap         : register(t2);

Texture2D textureAlbedo                : register(t3);
Texture2D textureMetallicRoughness     : register(t4);
Texture2D textureNormal                : register(t5);
Texture2D textureAmbientOcclusion      : register(t6);
Texture2D textureEmissive              : register(t7);

SamplerState samplerLinear             : register(s0);

// ---------- Push constants / small UBO (b1) ----------
cbuffer PushConsts : register(b1)
{
    float4x4 modelMatrix;
    float4x4 normalMatrix;

    int useTextureAlbedo;
    int useTextureMetallicRoughness;
    int useTextureNormal;
    int useTextureAmbientOcclusion;
    int useTextureEmissive;

    float3 albedo;
    float  metallic;
    float  roughness;
    float  ambientOcclusion;
    float3 emissive;

    float3 cameraPosition;
    float  bloomBrightnessCutoff;
}

// ---------- Helper functions ----------
float3 getAlbedo(PSInput input)
{
    float3 a = albedo;
    if (useTextureAlbedo != 0)
    {
        a = textureAlbedo.Sample(samplerLinear, input.texCoord).rgb;
    }
    return a;
}

void getMetallicRoughness(PSInput input, out float m, out float r)
{
    m = metallic;
    r = roughness;
    if (useTextureMetallicRoughness != 0)
    {
        float3 mr = textureMetallicRoughness.Sample(samplerLinear, input.texCoord).rgb;
        m = mr.b;
        r = mr.g;
    }
}

float3 getNormal(PSInput input)
{
    float3 n = input.normal;
    if (useTextureNormal != 0)
    {
        float3 tangentNormal = textureNormal.Sample(samplerLinear, input.texCoord).rgb;
        float3 norm = normalize(tangentNormal * 2.0f - 1.0f);
        float3x3 TBN = float3x3(input.tangent, input.bitangent, input.normal);
        n = normalize(mul(TBN, norm));
    }
    return n;
}

float getAO(PSInput input)
{
    float ao = ambientOcclusion;
    if (useTextureAmbientOcclusion != 0)
    {
        ao = textureAmbientOcclusion.Sample(samplerLinear, input.texCoord).r;
    }
    return ao;
}

float3 getEmissive(PSInput input)
{
    float3 e = emissive;
    if (useTextureEmissive != 0)
    {
        e = textureEmissive.Sample(samplerLinear, input.texCoord).rgb;
    }
    return e;
}

// PBR helper functions
float3 fresnelSchlick(float cosTheta, float3 f0)
{
    return f0 + (1.0f - f0) * pow(1.0f - cosTheta, 5.0f);
}

float3 fresnelSchlickRoughness(float cosTheta, float3 f0, float rough)
{
    return f0 + (max(float3(1.0f - rough, 1.0f - rough, 1.0f - rough), f0) - f0) * pow(saturate(1.0f - cosTheta), 5.0f);
}

float ndfTrowbridgeReitzGGX(float3 n, float3 h, float rough)
{
    float alpha = rough * rough;
    float alpha2 = alpha * alpha;
    float nDotH = max(dot(n,h),0);
    float denom = nDotH*nDotH*(alpha2-1.0f)+1.0f;
    denom = PI * denom * denom;
    denom = max(denom,0.0001f);
    return alpha2 / denom;
}

float geometrySchlickGGX(float3 n, float3 v, float k)
{
    float nDotV = max(dot(n,v),0);
    return nDotV / (nDotV*(1.0f - k) + k);
}

float geometrySmith(float3 n, float3 v, float3 l, float rough)
{
    float k = (rough+1)*(rough+1)/8.0f;
    return geometrySchlickGGX(n,v,k) * geometrySchlickGGX(n,l,k);
}

// ---------- Main Pixel Shader ----------
float4 main(PSInput input) : SV_Target
{
    float3 worldPos = input.worldCoordinates;
    float3 albedoCol = getAlbedo(input);

    float m, r;
    getMetallicRoughness(input, m, r);

    float3 n = getNormal(input);
    float ao = getAO(input);
    float3 e = getEmissive(input);

    float3 camPos = cameraPosition;
    float3 v = normalize(camPos - worldPos);
    float3 rVec = reflect(-v, n);

    float3 f0 = float3(0.04f,0.04f,0.04f);
    f0 = lerp(f0, albedoCol, m);

    float3 Lo = float3(0,0,0);

    int maxDirect = min(4, numLights);
    for (int i=0;i<maxDirect;++i)
    {
        float3 lightPos = pointLights[i].position.xyz;
        float3 lightCol = pointLights[i].color.rgb;

        float3 l = normalize(lightPos - worldPos);
        float3 h = normalize(v + l);

        float dist = length(lightPos - worldPos);
        float atten = 1.0f / max(dist*dist, 0.0001f);
        float3 radiance = lightCol * atten;

        float dTerm = ndfTrowbridgeReitzGGX(n,h,r);
        float3 fTerm = fresnelSchlick(max(dot(h,v),0), f0);
        float gTerm = geometrySmith(n,v,l,r);

        float3 numerator = dTerm * fTerm * gTerm;
        float denominator = 4.0f * max(dot(n,v),0) * max(dot(n,l),0);
        float3 spec = numerator / max(denominator,0.001f);

        float3 kSpec = fTerm;
        float3 kDiff = (1.0f - kSpec) * (1.0f - m);

        float3 diff = kDiff * albedoCol / PI;
        float3 brdf = diff + spec;
        float nDotL = max(dot(n,l),0);

        Lo += brdf * radiance * nDotL;
    }

    // IBL
    float3 kSpec = fresnelSchlickRoughness(max(dot(n,v),0), f0, r);
    float3 kDiff = (1.0f - kSpec)*(1.0f - m);

    float3 irradiance = diffuseIrradianceMap.Sample(samplerLinear, n).rgb;
    float3 diffuseIBL = irradiance * albedoCol;

    float3 prefilterColor = prefilteredEnvMap.SampleLevel(samplerLinear, rVec, r*4.0).rgb;
    float NdotV = max(dot(n,v),0);
    float2 brdf = brdfConvolutionMap.Sample(samplerLinear, float2(NdotV,r)).rg;
    float3 specularIBL = prefilterColor * (kSpec * brdf.x + brdf.y);

    float3 ambient = (kDiff*diffuseIBL + specularIBL) * ao;

    float3 finalColor = e + ambient + Lo;

    return float4(finalColor,1.0f);
}
