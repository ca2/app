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
cbuffer PushConstants : register(b1)
{
    float4x4 projection;
    float4 quad;        // l, t, r, b
    float4 texcoords;   // l, t, r, b
    float4 textColor;   // (not used here but available for pixel shader)
};

struct VSOut
{
    float4 pos : SV_POSITION;
    float2 uv  : TEXCOORD0;
};

VSOut main(uint vid : SV_VertexID)
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

    output.pos = mul(projection, float4(positions[vid], 0.0f, 1.0f));
    output.uv = uvs[vid];
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

      //auto& bindingTextColor = pshader->m_propertiesPush["textColor"];
      //bindingTextColor.m_i1FragmentShader = 1;
      //bindingTextColor.m_i2FragmentShader = 1;

      //auto& bindingProjection = pshader->m_mapConstantBuffer["projection"];
      //bindingProjection.m_i1VertexShader = 0;
      //bindingProjection.m_i2VertexShader = 1;

   }



} // namespace gpu



