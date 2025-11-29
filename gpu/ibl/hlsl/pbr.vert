// pbr1.vert
// Converted from Vulkan GLSL to HLSL
// Matches the PBR fragment shader above
// by Camilo <3ThomasBorregaardSorensen!!
// Shader Model 5.0+ recommended

// ---------- Input vertex attributes ----------
struct VSInput
{
    float3 aPos               : POSITION;   // location = 0
    float3 aNormal            : NORMAL;     // location = 1
    float2 aTextureCoordinates: TEXCOORD0;  // location = 2
    float4 aColor             : COLOR;      // location = 3
    float4 aTangent           : TEXCOORD1;    // location = 4
};

// ---------- Outputs to fragment shader ----------
struct VSOutput
{
    float4 Position          : SV_Position;
    float3 worldCoordinates  : TEXCOORD0;
    float2 textureCoordinates: TEXCOORD1;
    float3 tangent           : TEXCOORD2;
    float3 bitangent         : TEXCOORD3;
    float3 normal            : TEXCOORD4;
};

// Must match fragment shader
struct PointLight
{
    float4 position;
    float4 color;
};

// ---------- Global UBO (set = 0, binding = 0) ----------
cbuffer GlobalUbo : register(b0)
{
    float4x4 projection;
    float4x4 view;
    float4x4 invView;
    float4 ambientLightColor;
    float4 cameraPosition;
    PointLight pointLights[10];
    int numLights;
    int padding1;
    int padding2;
    int padding3;
};

// ---------- Push constants (model transforms) ----------
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

//    float3 cameraPosition;
    float bloomBrightnessCutoff;
    float3 multiplier;
};

VSOutput main(VSInput input)
{
    VSOutput output;

    // Transform position to world space
    float4 worldPos = mul(float4(input.aPos, 1.0), modelMatrix);

    //worldPos.x = -worldPos.x;
    //worldPos.z = -worldPos.z;

    output.worldCoordinates = worldPos.xyz;

    // Final clip-space position
    output.Position = mul(worldPos, view);
    output.Position = mul(output.Position, projection);

    // Pass through texture coordinates
    output.textureCoordinates = input.aTextureCoordinates;

    // Normal, tangent, bitangent in world space
    float3x3 normalMat = transpose((float3x3)normalMatrix);

    float3 N = normalize(mul(input.aNormal, normalMat));
    float3 T = normalize(mul(input.aTangent.xyz, normalMat));
    float3 B = normalize(cross(N, T)) * input.aTangent.w;

    output.normal = N;
    output.tangent = T;
    output.bitangent = B;

    return output;
}
