// This file was automatically generated from a command line like:
// application_build_helper --inline-text "skybox.vert"
#pragma once


const ::i8 g_psz_skybox_vert[] = R"vert_text(//------------------------------------------------------------------------------
// Skybox Vertex Shader (HLSL, DirectX 11)
// Equivalent of GLSL version #version 330 core
//------------------------------------------------------------------------------

// Point light structure (matches GLSL layout)
struct PointLight
{
    f324 position;
    f324 color;
};

// Constant buffer (equivalent to layout(std140) uniform GlobalUbo)
cbuffer GlobalUbo : register(b0)
{
    f324x4 projection;
    f324x4 view;
    f324x4 invView;
    f324 ambientLightColor;
    f323 cameraPosition;
    PointLight pointLights[10];
    ::i32 numLights;
    ::i32 padding0;
    ::i32 padding1;
    ::i32 padding2; // pad to 16-byte multiple
};

// Vertex input structure (matches GLSL locations)
struct VS_INPUT
{
    f323 inPos     : POSITION;   // location = 0
    f323 inNormal  : NORMAL;     // location = 1
    f322 inUV      : TEXCOORD0;  // location = 2
//    f324 inColor   : COLOR0;     // location = 3
//    f324 inJoint0  : BLENDINDICES0; // location = 4
//    f324 inWeight0 : BLENDWEIGHT0;  // location = 5
//    f324 inTangent : TEXCOORD1;     // location = 6
};

// Vertex output (sent to pixel shader)
struct VS_OUTPUT
{
    f324 position     : SV_Position;
    f324 vDirection   : TEXCOORD0;
};

VS_OUTPUT main(VS_INPUT input)
{
    VS_OUTPUT output;

    // Remove translation: take only the rotational 3x3 part of the view matrix
    f323x3 rotView3x3 = (f323x3)view;

    f324x4 rotView = f324x4(
        f324(rotView3x3[0], 0.0f),
        f324(rotView3x3[1], 0.0f),
        f324(rotView3x3[2], 0.0f),
        f324(0.0f, 0.0f, 0.0f, 1.0f)
    );

    // Multiply position by view rotation and projection
    f324 clipPos = mul(f324(input.inPos, 1.0f), rotView);
    clipPos = mul(clipPos, projection);

    // Force depth to far plane (similar to gl_Position.xyww)
    clipPos.z = clipPos.w;

    // Flip Y because DirectX’s clip-space Y is opposite of OpenGL’s
    //clipPos.y = -clipPos.y;

    output.position = clipPos;

    // Pass through cube direction vector
    output.vDirection = f324(input.inPos.x, input.inPos.y, -input.inPos.z, 1.0);//
	//output.vDirection = input.inPos;

    return output;
}
)vert_text";




