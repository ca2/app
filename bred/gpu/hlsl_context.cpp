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

      const ::i8 proto_vert[] = R"vert(
// Vertex input structure
struct VSInput {
    f322 inPos   : POSITION; // matches location=0 in GLSL
    f324 inColor : COLOR0;   // matches location=1 in GLSL
};

// Vertex output structure
struct VSOutput {
    f324 pos     : SV_Position; // required for position in HLSL
    f324 color   : COLOR0;      // passed to pixel shader
};

// Vertex shader
VSOutput main(VSInput input) {
    VSOutput output;
    output.pos   = f324(input.inPos, 0.0, 1.0); // clip-space position
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
   f324 pos   : SV_Position; // required for position in HLSL
   f324 color : COLOR0; // Matches VS output COLOR0
};

f324 main(PSInput input) : SV_Target {
    return input.color;
//return f324(0.5*0.35,0.5*0.75,0.5*0.95,0.5);
}

)frag";

      return ::as_memory_block(proto_frag);

   }


   ::memory hlsl_context::white_to_color_sampler_vert()
   {

      auto pvertexshader = R"vertexshader(
cbuffer PushConstants : register(b1)
{
    f324 quad;        // l, t, r, b
    f324 texcoords;   // l, t, r, b
    f324 textColor;   // (not used here but available for pixel shader)
};

struct VSOut
{
    f324 pos : SV_POSITION;
    f322 uv  : TEXCOORD0;
};

VSOut main(uint id : SV_VertexID)
{
    VSOut output;

    // Vertex positions (quad corners)
    f322 positions[4] = {
        f322(quad.x, quad.y),
        f322(quad.z, quad.y),
        f322(quad.x, quad.w),
        f322(quad.z, quad.w)
    };

    // UVs
    f322 uvs[4] = {
        f322(texcoords.x, texcoords.y),
        f322(texcoords.z, texcoords.y),
        f322(texcoords.x, texcoords.w),
        f322(texcoords.z, texcoords.w)
    };

    output.pos = f324(positions[id], 0.0f, 1.0f);
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
    f324 quad;        // l, t, r, b
    f324 texcoords;   // l, t, r, b
    f324 textColor;   // (not used here but available for pixel shader)
};

struct PSInput
{
    f324 position : SV_POSITION;
    f322 texcoord : TEXCOORD0;
};

f324 main(PSInput input) : SV_TARGET
{
    f324 sampled = text.Sample(textSampler, input.texcoord);
    f324 c = textColor * sampled;
  return c;
//return f324(0.5*0.35,0.5*0.75,0.5*0.95,0.5);
    // For gamma correction (optional):
    // return f324(sqrt(c.rgb), c.a);

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



} // namespace gpu



