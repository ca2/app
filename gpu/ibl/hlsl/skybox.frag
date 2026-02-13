//------------------------------------------------------------------------------
// HLSL Fragment Shader (Pixel Shader) equivalent
//------------------------------------------------------------------------------

// Texture and sampler
TextureCube skybox       : register(t0);
SamplerState samplerLinear : register(s0);

// Scene constant buffer (matches GlobalUbo in GLSL)
struct PointLight
{
    float4 position;
    float4 color;
};



// register(b1) for "push constants"
cbuffer MatrixBuffer : register(b1)
{
    float3 multiplier;
};



cbuffer GlobalUbo : register(b0)
{
    float4x4 projection;
    float4x4 view;
    float4x4 invView;
    float4 ambientLightColor;
    float3 cameraPosition;
    PointLight pointLights[10];
    int numLights;
    int padding0;
    int padding1;
    int padding2; // padding to make struct size multiple of 16 bytes
};

// Pixel shader input
struct PS_INPUT
{
    float4 position     : SV_Position;
    float4 vDirection   : TEXCOORD0;
};



float4 main(PS_INPUT input)  : SV_TARGET
{

    // Normalize direction
    float3 dir = normalize(input.vDirection);

    // Flip Y if needed (to match OpenGL coordinates)
    //dir.y = -dir.y;
    dir *= multiplier;

    // Sample skybox cubemap
    float4 color = skybox.Sample(samplerLinear, dir);

    return color;
}
