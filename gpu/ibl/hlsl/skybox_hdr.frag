//------------------------------------------------------------------------------
// Skybox Pixel Shader (HLSL / DirectX 11)
//------------------------------------------------------------------------------

// Cube map texture and sampler
TextureCube skybox : register(t0);
SamplerState linearSampler : register(s0);

// Point light struct (matching vertex shader)
struct PointLight
{
    float4 position;
    float4 color;
};

// Global constant buffer (same as GLSL std140 UBO)
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
    int padding2;
};

// Input from vertex shader
struct PS_INPUT
{
    float4 position     : SV_Position;
    float4 vDirection   : TEXCOORD0;
};


// register(b1) for "push constants"
cbuffer MatrixBuffer : register(b1)
{
    float3 multiplier;
};


float3 ACESFilmTonemap(float3 color)
{
    // ACES tonemapping constants
    float a = 2.51;
    float b = 0.03;
    float c = 2.43;
    float d = 0.59;
    float e = 0.14;
    return clamp((color*(a*color+b)) / (color*(c*color+d)+e), 0.0f, 1.0f);
}

float3 LinearToSRGB(float3 color)
{
    return pow(color, 1.0f / 2.2f);
}

float4 main(PS_INPUT input) : SV_TARGET
{
    // Normalize direction
    float3 dir = normalize(input.vDirection);

    // Flip Y if your cube map was loaded OpenGL-style
    //dir.y = -dir.y;
    //dir.x = -dir.x;
    //dir = float3(-dir.x, -dir.y, -dir.z);
    dir *= multiplier;
    // Sample HDR cube map
    float3 hdrColor = skybox.Sample(linearSampler, dir).rgb;

    // Apply tonemapping (ACES)
    float3 mapped = ACESFilmTonemap(hdrColor);

    // Convert from linear to sRGB
    mapped = LinearToSRGB(mapped);

    return float4(mapped, 1.0f);
}
