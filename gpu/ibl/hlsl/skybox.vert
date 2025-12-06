//------------------------------------------------------------------------------
// Skybox Vertex Shader (HLSL, DirectX 11)
// Equivalent of GLSL version #version 330 core
//------------------------------------------------------------------------------

// Point light structure (matches GLSL layout)
struct PointLight
{
    float4 position;
    float4 color;
};

// Constant buffer (equivalent to layout(std140) uniform GlobalUbo)
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
    int padding2; // pad to 16-byte multiple
};

// Vertex input structure (matches GLSL locations)
struct VS_INPUT
{
    float3 inPos     : POSITION;   // location = 0
    float3 inNormal  : NORMAL;     // location = 1
    float2 inUV      : TEXCOORD0;  // location = 2
//    float4 inColor   : COLOR0;     // location = 3
//    float4 inJoint0  : BLENDINDICES0; // location = 4
//    float4 inWeight0 : BLENDWEIGHT0;  // location = 5
//    float4 inTangent : TEXCOORD1;     // location = 6
};

// Vertex output (sent to pixel shader)
struct VS_OUTPUT
{
    float4 position     : SV_Position;
    float4 vDirection   : TEXCOORD0;
};

VS_OUTPUT main(VS_INPUT input)
{
    VS_OUTPUT output;

    // Remove translation: take only the rotational 3x3 part of the view matrix
    float3x3 rotView3x3 = (float3x3)view;

    float4x4 rotView = float4x4(
        float4(rotView3x3[0], 0.0f),
        float4(rotView3x3[1], 0.0f),
        float4(rotView3x3[2], 0.0f),
        float4(0.0f, 0.0f, 0.0f, 1.0f)
    );

    // Multiply position by view rotation and projection
    float4 clipPos = mul(float4(input.inPos, 1.0f), rotView);
    clipPos = mul(clipPos, projection);

    // Force depth to far plane (similar to gl_Position.xyww)
    clipPos.z = clipPos.w;

    // Flip Y because DirectX’s clip-space Y is opposite of OpenGL’s
    //clipPos.y = -clipPos.y;

    output.position = clipPos;

    // Pass through cube direction vector
    output.vDirection = float4(input.inPos.x, input.inPos.y, -input.inPos.z, 1.0);//
	//output.vDirection = input.inPos;

    return output;
}
