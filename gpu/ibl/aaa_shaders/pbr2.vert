// pbr2.vert
// ======================================================
// Unified Vertex Shader — Vulkan + Direct3D Compatible
// Based on GLSL #version 450 source
// ======================================================

// Vertex input layout
struct VSInput
{
    float3 aPos     : POSITION;   // location = 0
    float3 aNormal  : NORMAL;     // location = 1
    float2 aTexCoord: TEXCOORD0;  // location = 2
    float4 aColor   : COLOR0;     // location = 3
    float4 aTangent : TEXCOORD1;    // location = 4
};

// Vertex → Fragment outputs
struct VSOutput
{
    float4 position         : SV_Position; // clip-space
    float3 worldCoordinates : TEXCOORD0;
    float2 texCoord         : TEXCOORD1;
    float3 tangent          : TEXCOORD2;
    float3 bitangent        : TEXCOORD3;
    float3 normal           : TEXCOORD4;
};

// ------------------------------------------------------
// Common structures
// ------------------------------------------------------
struct PointLight
{
    float4 position;
    float4 color;
};

// ------------------------------------------------------
// Global UBO  (set = 0, binding = 0  for Vulkan / b0 for D3D)
// ------------------------------------------------------
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

// ------------------------------------------------------
// Push Constants (Vulkan) / small transform buffer (D3D)
// ------------------------------------------------------
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

// ------------------------------------------------------
// Main vertex shader
// ------------------------------------------------------
VSOutput main(VSInput input)
{
    VSOutput output;

    // Transform position to world space
    float4 worldPos = mul(modelMatrix, float4(input.aPos, 1.0f));
    output.worldCoordinates = worldPos.xyz;

    // Clip-space position
    output.position = mul(projection, mul(view, worldPos));

    // Pass texture coordinates
    output.texCoord = input.aTexCoord;

    // Build normal, tangent, bitangent in world space
    float3x3 normalMat = transpose((float3x3)normalMatrix);

    float3 N = normalize(mul(normalMat, input.aNormal));
    float3 T = normalize(mul(normalMat, input.aTangent.xyz));
    float3 B = normalize(cross(N, T) * input.aTangent.w);

    output.normal   = N;
    output.tangent  = T;
    output.bitangent= B;

    return output;
}
