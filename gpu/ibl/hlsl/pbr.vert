// HLSL Vertex Shader equivalent of your GLSL version

cbuffer MatrixBuffer : register(b0)
{
    float4x4 model;
    float4x4 view;
    float4x4 projection;
};

struct VS_INPUT
{
    float3 position  : POSITION;   // layout(location = 0)
    float3 normal    : NORMAL;     // layout(location = 1)
    float2 texcoord  : TEXCOORD0;  // layout(location = 2)
    float3 tangent   : TANGENT;    // layout(location = 3)
    float3 bitangent : BINORMAL;   // layout(location = 4)
};

struct VS_OUTPUT
{
    float4 position          : SV_POSITION;
    float2 textureCoordinates: TEXCOORD0;
    float3 worldCoordinates  : TEXCOORD1;
    float3 tangent           : TEXCOORD2;
    float3 bitangent         : TEXCOORD3;
    float3 normal            : TEXCOORD4;
};

VS_OUTPUT main(VS_INPUT input)
{
    VS_OUTPUT output;

    // Convert to homogeneous coordinates
    float4 worldPos = mul(float4(input.position, 1.0f), model);
    output.worldCoordinates = worldPos.xyz;

    // Row-major multiplication order in HLSL
    float4 viewPos = mul(worldPos, view);
    output.position = mul(viewPos, projection);

    output.textureCoordinates = input.texcoord;

    // Build normal matrix (inverse-transpose of upper-left 3x3 of model)
    float3x3 normalMatrix = (float3x3)model;
    normalMatrix = transpose(invert(normalMatrix));

    output.tangent   = normalize(mul(input.tangent, normalMatrix));
    output.bitangent = normalize(mul(input.bitangent, normalMatrix));
    output.normal    = normalize(mul(input.normal, normalMatrix));

    return output;
}
