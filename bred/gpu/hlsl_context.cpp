// Created by camilo on 2025-07-05 07:15 <3ThomasBorregaardSørensen!!
#include "platform.h"
#include "hlsl_context.h"


namespace gpu
{


   hlsl_context::hlsl_context()
   {

   }


   hlsl_context::~hlsl_context()
   {

   }


   ::memory hlsl_context::rectangle_shader_vert()
   {

      const ::i8 proto_vert[] = R"vert(
// Vertex input structure
struct VSInput {
    float2 inPos   : POSITION; // matches location=0 in GLSL
    float4 inColor : COLOR0;   // matches location=1 in GLSL
};

// Vertex output structure
struct VSOutput {
    float4 pos     : SV_Position; // required for position in HLSL
    float4 color   : COLOR0;      // passed to pixel shader
};

// Vertex shader
VSOutput main(VSInput input) {
    VSOutput output;
    output.pos   = float4(input.inPos, 0.0, 1.0); // clip-space position
    output.color = input.inColor;
    return output;
}

)vert";

      return ::as_memory_block(proto_vert);

   }


   ::memory hlsl_context::rectangle_shader_frag()
   {

      const ::i8 proto_frag[] = R"frag(
struct PSInput {
   float4 pos   : SV_Position; // required for position in HLSL
   float4 color : COLOR0; // Matches VS output COLOR0
};

float4 main(PSInput input) : SV_Target {
    return input.color;
//return float4(0.5*0.35,0.5*0.75,0.5*0.95,0.5);
}

)frag";

      return ::as_memory_block(proto_frag);

   }


   ::memory hlsl_context::circle_shader_vert()
   {

      const ::i8 proto_vert[] = R"vert(

struct VertexInput
{
   float2 inputPosition      : POSITION;
   float2 inputLocalPosition : TEXCOORD0;
};

struct VertexOutput
{
   float4 position              : SV_Position;
   float2 fragmentLocalPosition : TEXCOORD0;
};

VertexOutput main(VertexInput input)
{
   VertexOutput output;

   output.position =
      float4(input.inputPosition, 0.0f, 1.0f);

   output.fragmentLocalPosition =
      input.inputLocalPosition;

   return output;
}

)vert";

      return ::as_memory_block(proto_vert);

   }


   ::memory hlsl_context::circle_shader_frag()
   {

      const ::i8 proto_frag[] = R"frag(
cbuffer CircleConstants : register(b1)
{
   float4 uniformFragmentColor;
   float radius;
   float thickness;
   float2 padding;
};

struct PixelInput
{
   float4 position              : SV_Position;
   float2 fragmentLocalPosition : TEXCOORD0;
};

float4 main(PixelInput input) : SV_Target
{
   float distanceFromCenter =
      length(input.fragmentLocalPosition);

   float signedDistance =
      abs(distanceFromCenter - radius)
      - thickness * 0.5f;

   float2 distanceGradient =
      float2(
         ddx(signedDistance),
         ddy(signedDistance));

   float pixelWidth =
      max(length(distanceGradient), 0.0001f);

   float coverage =
      clamp(
         0.5f - signedDistance / pixelWidth,
         0.0f,
         1.0f);

   return uniformFragmentColor * coverage;
}
)frag";

      return ::as_memory_block(proto_frag);

   }


   ::memory hlsl_context::white_to_color_sampler_vert()
   {

      auto pvertexshader = R"vertexshader(
cbuffer PushConstants : register(b1)
{
    float4 quad;        // l, t, r, b
    float4 texcoords;   // l, t, r, b
    float4 textColor;   // (not used here but available for pixel shader)
};

struct VSOut
{
    float4 pos : SV_POSITION;
    float2 uv  : TEXCOORD0;
};

VSOut main(uint id : SV_VertexID)
{
    VSOut output;

    // Vertex positions (quad corners)
    float2 positions[4] = {
        float2(quad.x, quad.y),
        float2(quad.z, quad.y),
        float2(quad.x, quad.w),
        float2(quad.z, quad.w)
    };

    // UVs
    float2 uvs[4] = {
        float2(texcoords.x, texcoords.y),
        float2(texcoords.z, texcoords.y),
        float2(texcoords.x, texcoords.w),
        float2(texcoords.z, texcoords.w)
    };

    output.pos = float4(positions[id], 0.0f, 1.0f);
    output.uv = uvs[id];
    return output;
}
)vertexshader";

      return ::as_block(pvertexshader);

   }


   ::memory hlsl_context::white_to_color_sampler_frag()
   {

      auto pfragmentshader = R"fragmentshader(Texture2D text : register(t0);
SamplerState textSampler : register(s0);

cbuffer TextColorBuffer : register(b1)
{
    float4 quad;        // l, t, r, b
    float4 texcoords;   // l, t, r, b
    float4 textColor;   // (not used here but available for pixel shader)
};

struct PSInput
{
    float4 position : SV_POSITION;
    float2 texcoord : TEXCOORD0;
};

float4 main(PSInput input) : SV_TARGET
{
    float4 sampled = text.Sample(textSampler, input.texcoord);
    float4 c = textColor * sampled;
  return c;
//return float4(0.5*0.35,0.5*0.75,0.5*0.95,0.5);
    // For gamma correction (optional):
    // return float4(sqrt(c.rgb), c.a);

}
)fragmentshader";

      return ::as_block(pfragmentshader);
   }


   //void hlsl_context::white_to_color_sampler_shader_setup(gpu::shader* pshader)
   //{

   //   //auto& bindingTextColor = pshader->m_propertiesPush["textColor"];
   //   //bindingTextColor.m_i1FragmentShader = 1;
   //   //bindingTextColor.m_i2FragmentShader = 1;

   //   //auto& bindingProjection = pshader->m_mapConstantBuffer["projection"];
   //   //bindingProjection.m_i1VertexShader = 0;
   //   //bindingProjection.m_i2VertexShader = 1;

   //}

   ::memory hlsl_context::_001ImageVertexShaderMemory()
   {



      auto pvertexshader = R"vertexshader(


cbuffer QuadBuffer : register(b1)
{
    float4 quad;
    // source UV: left, bottom, right, top
};

struct VSOutput
{
    float4 position : SV_POSITION;
    float2 uv       : TEXCOORD0;
};

VSOutput main(uint vertexId : SV_VertexID)
{
static const float2 pos[4] =
{
    float2(-1.0, -1.0),
    float2(-1.0,  1.0),
    float2( 1.0, -1.0),
    float2( 1.0,  1.0)
};

static const float2 tex[4] =
{
    float2(0.0, 1.0),
    float2(0.0, 0.0),
    float2(1.0, 1.0),
    float2(1.0, 0.0)
};

    VSOutput output;

    output.position =
        float4(pos[vertexId], 0.0, 1.0);

    float2 uvFull =
        tex[vertexId];

    output.uv = float2(
        lerp(quad.x, quad.z, uvFull.x),
        lerp(quad.y, quad.w, uvFull.y)
    );

    return output;
}


)vertexshader";

      return ::as_block(pvertexshader);

   }


   ::memory hlsl_context::_001ImageFragmentShaderMemory()
   {

      auto pfragmentshader = R"fragmentshader(

Texture2D uTexture : register(t0);
SamplerState uSampler : register(s0);

struct PSInput
{
    float4 position : SV_POSITION;
    float2 uv       : TEXCOORD0;
};

float4 main(PSInput input) : SV_TARGET
{
    float4 color =
        uTexture.Sample(uSampler, input.uv);

    // color =
    //     mul(colorMatrix, color) + colorOffset;

    return color;
}

)fragmentshader";
      return ::as_block(pfragmentshader);
   }


} // namespace gpu



