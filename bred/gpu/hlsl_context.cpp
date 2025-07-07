// Created by camilo on 2025-07-05 07:15 <3ThomasBorregaardSørensen!!
#include "framework.h"
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
      throw ::error_not_implemented;
      return {};
   }


   ::memory hlsl_context::rectangle_shader_frag()
   {
      throw ::error_not_implemented;
      return {};

   }


   ::memory hlsl_context::white_to_color_sampler_vert()
   {

      auto pvertexshader = R"vertexshader(
cbuffer ProjectionBuffer : register(b0)
{
    float4x4 projection;
};

struct VSInput
{
    float2 pos : POSITION;
    float2 tex : TEXCOORD0;
};

struct VSOutput
{
    float4 position : SV_POSITION;
    float2 texcoord : TEXCOORD0;
};

VSOutput main(VSInput input)
{
    VSOutput output;
    output.position = mul(projection, float4(input.pos, 0.0, 1.0));
    output.texcoord = float2(input.tex.x, 1.0 - input.tex.y); // Flip Y if needed
    return output;
})vertexshader";

      return ::as_block(pvertexshader);

   }


   ::memory hlsl_context::white_to_color_sampler_frag()
   {

      auto pfragmentshader = R"fragmentshader(Texture2D text : register(t0);
SamplerState textSampler : register(s0);

cbuffer TextColorBuffer : register(b1)
{
    float4 textColor;
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
    // For gamma correction (optional):
    // return float4(sqrt(c.rgb), c.a);
}
)fragmentshader";

      return ::as_block(pfragmentshader);
   }


   void hlsl_context::white_to_color_sampler_shader_setup(gpu::shader* pshader)
   {

      auto& bindingTextColor = pshader->m_mapConstantBuffer["textColor"];
      bindingTextColor.m_i1FragmentShader = 1;
      bindingTextColor.m_i2FragmentShader = 1;

      auto& bindingProjection = pshader->m_mapConstantBuffer["projection"];
      bindingProjection.m_i1VertexShader = 0;
      bindingProjection.m_i2VertexShader = 1;

   }


} // namespace gpu



