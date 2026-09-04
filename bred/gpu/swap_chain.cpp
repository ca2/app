// Created by camilo on 2025-06-10 <3ThomasBorregaardSørensen!!
#include "platform.h"
#include "command_buffer.h"
#include "context.h"
#include "device.h"
#include "window_attachment.h"
#include "fence.h"
#include "renderer.h"
#include "semaphore.h"
#include "swap_chain.h"
#include "texture.h"
#include "texture_site.h"
#include "texture_synchronization.h"
#include "aura/windowing/window.h"
#include "bred/gpu/binding.h"
#include "bred/gpu/model_buffer.h"


namespace gpu
{


   swap_chain::swap_chain()
   {

      m_iCurrentSwapChainFrame = 0;

      m_bWindowInitialized = false;

      m_bSwapChainInitialized = false;

   }
      
   
   swap_chain::~swap_chain()
   {

   }


   void swap_chain::on_new_frame()
   {



   }



   void swap_chain::do_output(::gpu::texture_site * pgputexturesite)
   {

      //if (eoutput == ::gpu::e_output_swap_chain)
      {

         //auto pgpuwindowattachment = ::gpu::window_attachment::get(m_pgpucontext);

         //auto pgpuswapchain = pgpuwindowattachment->m_pgpucontextWindow->get_swap_chain();

         //if (pgpuswapchain)
         {

            auto pgpucontextSwapChain = m_pgpurenderer->m_pgpucontext;

            if (!m_bSwapChainInitialized)
            {

               initialize_gpu_swap_chain(pgpucontextSwapChain->m_pgpurenderer);

            }

            //::cast<gpu::render_target> pgpurendertarget = pgpuswapchain;

            ////if (pgpurendertarget)
            //{

            //  // if (!pgpurendertarget->m_pgpurenderer)
            //   if (!m_pgpurenderer)
            //   {

            //      initialize_render_target(m, m_pgpucontext->size(), nullptr);

            //   }

            //}

            //::cast<renderer> pgpurendererSwapChain = pgpucontextSwapChain->m_pgpurenderer;
            ::cast<renderer> pgpurendererSwapChain = m_pgpurenderer;

            // pgpucontextSwapChain->start_frame();

            // pgpucontextSwapChain->start_layer();

            //::cast<command_buffer> pcommandbufferSwapChain =
            // pgpurendererSwapChain->getCurrentCommandBuffer2(::gpu::current_layer());
            {
            //::pointer<command_buffer> pcommandbufferSwapChain = pgpucontextSwapChain->beginSingleTimeCommands();
               auto pcommandbufferSwapChain = pgpucontextSwapChain->beginSingleTimeCommands();

            auto pgpuwindowattachment = ::gpu::window_attachment::get(pgpucontextSwapChain);

            // pcommandbuffer->begin_command_buffer(false);
            auto iSwapChainFrameIndex = swap_chain_frame_index();

            pcommandbufferSwapChain->m_iCommandBufferFrameIndex2 =
               pgpuwindowattachment->get_frame_index3();

            // if (defer_constructø(pgpucontextSwapChain->m_gpusemaphoreaPresentReady.atø(iSwapChainFrameIndex)))
            //{

            //   pgpucontextSwapChain->m_gpusemaphoreaPresentReady[iSwapChainFrameIndex]->initialize_gpu_semaphore(
            //      m_pgpucontext);
            //}

            auto & framesync = frame(iSwapChainFrameIndex);

            if (::is_set(framesync.m_pgpusemaphoreImageAvailable))
            {

               if (pcommandbufferSwapChain->m_semaphoreaWait.add_unique(framesync.m_pgpusemaphoreImageAvailable))
               {

                  pcommandbufferSwapChain->m_epipelinestageaWait.add(
                     e_pipeline_stage_color_attachment_output_bit);

               }

            }

            pcommandbufferSwapChain->m_pgpufence = framesync.m_pgpufenceInFlight;

            if (framesync.m_pgpusemaphoreRenderFinished)
            {

               pcommandbufferSwapChain->m_semaphoreaSignal.add_unique(framesync.m_pgpusemaphoreRenderFinished);

               m_gpusemaphoreaWait.add_unique(framesync.m_pgpusemaphoreRenderFinished);

            }

            //for (::collection::index i = 0; i < semaphoreaReady.get_count(); i++)
            //{

            if (pgputexturesite->gpu_texture()->synchronization())
            {

               auto pgpusemaphoreRenderFinished = pgputexturesite->gpu_texture()->synchronization()->m_pgpusemaphoreRenderFinished;

               if (pgpusemaphoreRenderFinished)
               {

                  if (pcommandbufferSwapChain->m_semaphoreaWait.add_unique(pgpusemaphoreRenderFinished))
                  {

                     pcommandbufferSwapChain->m_epipelinestageaWait.add(::gpu::e_pipeline_stage_fragment_shader_bit);

                  }

                  //if (semaphoreaReady.add_unique(pgpusemaphoreRenderFinished))
                  //{
                  //
                  //   epipelinestageaReady.add(::gpu::e_pipeline_stage_fragment_shader_bit);
                  //
                  //}

               }

            }


            //   if (pcommandbufferSwapChain->m_semaphoreaWait.add_unique(semaphoreaReady[i]))
            //   {

            //      pcommandbufferSwapChain->m_epipelinestageaWait.add(epipelinestageaReady[i]);

            //   }

            //}
            // pcommandbufferSwapChain->m_semaphoreaSignal.add_unique(
            //  pgpucontextSwapChain->m_gpusemaphoreaPresentReady.atø(iSwapChainFrameIndex));

            // pswapchain->m_pwindowSwapChain->_main_send([pswapchain, ptextureBackBuffer]()
            //  system()->acme_windowing()
            //  ->_main_send([pswapchain, ptextureBackBuffer]()
            //{


            present(pgputexturesite, pcommandbufferSwapChain);


            set_present_state(pcommandbufferSwapChain);
            // pgpucontextSwapChain->end_layer();

            // pgpucontextSwapChain->end_frame();
            //}

            // pcommandbuffer->m_semaphoreaWait.add_unique(pswapchain->m_fr->m_semaphoreaSignal);
            //}

            //});

            // prendererBackBuffer->frame_suffix();


            // #endif
            //          pcommandbuffer->submit_command_buffer(nullptr);

            framesync.m_pcommandbufferLastSwapChainPresentation = pcommandbufferSwapChain.operator gpu::command_buffer *();

            pcommandbufferSwapChain.commit();

         }

            //pgpucontextSwapChain->endSingleTimeCommands(pcommandbufferSwapChain);

            swap_buffers();



            // pswapchain->swap_buffers();

         }

      }

   }


   void swap_chain::create_images()
   {


   }


   void swap_chain::defer_check_swap_chain()
   {

      if (::is_set(m_ptexturesiteaSwapChain) && m_iSwapSeed == m_iCurrentSwapSerial)
      {

         return;

      }

      m_iCurrentSwapSerial = m_iSwapSeed;

      on_new_swap_chain();

   }


   void swap_chain::on_new_swap_chain()
   {

      create_images();

   }


   void swap_chain::initialize_swap_chain_window(::gpu::context * pgpucontext, ::acme::windowing::window* pwindow)
   {

      ASSERT(pgpucontext && pgpucontext->m_etype == ::gpu::context::e_type_window);

      m_pgpurenderer = pgpucontext->get_gpu_renderer();

      m_pwindowSwapChain = pwindow;

      m_bWindowInitialized = true;

      ::string strType = ::type(pwindow->m_pacmeuserinteraction).name();

      const_char_pointer pszType = strType.c_str();

      information("initialize_swap_chain_window {}", pszType);

   }


   void swap_chain::initialize_gpu_swap_chain(::gpu::renderer * pgpurenderer)
   {

      if (!m_bWindowInitialized || !m_pwindowSwapChain)
      {

         throw ::exception(error_wrong_state);

      }

      if (pgpurenderer != m_pgpurenderer
      || pgpurenderer->m_pgpucontext->m_etype != ::gpu::context::e_type_window)
      {

         throw ::exception(error_wrong_state);

      }

      m_pgpurenderer = pgpurenderer;

      m_bSwapChainInitialized = true;

   }


   void swap_chain::dummy_model_buffer()
   {

      if (!m_pmodelbufferDummy)
      {

         defer_constructø(m_pmodelbufferDummy);

         m_pmodelbufferDummy->initialize_dummy_model(m_pgpurenderer, 3);

         //m_pmodelbufferDummy->m_iVertexCount = 3;

      }

   }


   void swap_chain::present_shader()
   {

      if (!m_pshaderPresent)
      {

         ::cast < renderer > pgpurenderer = ::gpu::swap_chain::m_pgpurenderer;

         ::cast < context > pgpucontext = pgpurenderer->m_pgpucontext;

         ::string strVert;
         ::string strFrag;
         ::string strGpuImplementation = system()->component_factory_implementation_name("gpu");

         if (strGpuImplementation == "opengl")
         {

            strVert = R"vert(

#version 330 core

uniform vec4 quad;
// left, bottom, right, top

out vec2 uv;

void main()
{

   const vec2 pos[3] = vec2[](
      vec2(-1.0, -1.0),
      vec2(-1.0,  3.0),
      vec2( 3.0, -1.0)
   );

   const vec2 tex[3] = vec2[](
      vec2(0.0, 0.0),
      vec2(0.0, 2.0),
      vec2(2.0, 0.0)
   );

   gl_Position = vec4(pos[gl_VertexID], 0.0, 1.0);

   vec2 uvFull = tex[gl_VertexID];

   uv = vec2(
      mix(quad.x, quad.z, uvFull.x),
      mix(quad.y, quad.w, uvFull.y)
   );

}

)vert";
            strFrag = R"frag(

#version 330 core

uniform sampler2D uTexture;

in vec2 uv;

out vec4 outColor;

void main()
{

   outColor = texture(uTexture, uv);

}

)frag";
         }
         else if (strGpuImplementation.begins("directx1"))
         {


            strVert = R"vert(
cbuffer QuadBuffer : register(b1)
{
   float4 quad;
   // uLeft, vTop, uRight, vBottom
};

struct VS_OUTPUT
{
   float4 position : SV_POSITION;
   float2 uv       : TEXCOORD0;
};

VS_OUTPUT main(uint vertexId : SV_VertexID)
{
   static const float2 pos[3] =
   {
      float2(-1.0f, -1.0f),
      float2(-1.0f,  3.0f),
      float2( 3.0f, -1.0f)
   };

   //
   // Direct3D top-left texture orientation.
   //
   static const float2 tex[3] =
   {
      float2(0.0f,  1.0f),
      float2(0.0f, -1.0f),
      float2(2.0f,  1.0f)
   };

   VS_OUTPUT output;

   output.position = float4(pos[vertexId], 0.0f, 1.0f);

   float2 uvFull = tex[vertexId];

   output.uv = float2(
      lerp(quad.x, quad.z, uvFull.x),
      lerp(quad.y, quad.w, uvFull.y)
   );

   return output;
}

)vert";

            strFrag = R"frag(

Texture2D uTexture : register(t0);

SamplerState uSampler : register(s0);

struct PS_INPUT
{

   float4 position : SV_POSITION;
   float2 uv       : TEXCOORD0;

};

float4 main(PS_INPUT input) : SV_TARGET
{

   return uTexture.Sample(uSampler, input.uv);

}

)frag";

         }
         else
         {

            throw ::exception(todo, "missing vertex and fragment shaders for this gpu component implementation?!?!");

         }

         defer_constructø(m_pshaderPresent);

         //m_pshaderPresent->m_bEnableBlend = true;
         m_pshaderPresent->m_bEnableBlend = false;
         //m_pshaderPresent->m_bindingSampler.set();
         m_pshaderPresent->m_bDisableDepthTest = true;

         auto pbindingSampler = m_pshaderPresent->binding();
         pbindingSampler->m_ebinding = ::gpu::e_binding_sampler2d;
         pbindingSampler->m_iTextureUnit = 0;
         //m_pshaderPresent->m_bT
         //m_pshaderPresent->m_pgpurenderer = this;
         //m_pshaderPresent->m_setbindingSampler = 0;
         // Image Blend descriptors
         //if (!m_psetdescriptorlayoutImageBlend)
         m_pshaderPresent->m_propertiesPushShared.set_properties(::gpu_properties<::gpu::quad>());

         pgpucontext->layout_push_constants(m_pshaderPresent->m_propertiesPushShared, false);

         //m_pshaderPresent->m_bClearColor = true;
         //m_pshaderPresent->m_colorClear = ::color::transparent;

         //m_pshaderPresent->m_bClearColor = false;
         //m_pshaderPresent->m_colorClear = ::color::transparent;

         m_pshaderPresent->initialize_shader_with_block(
            m_pgpurenderer,
            strVert,
            strFrag,
            {},
            //{},
            //{},
            // this means the vertex input layout will be null/empty
            // the full screen shader is embed in the shader code
            ::gpu::shader::e_flag_clear_default_bindings_and_attributes_descriptions

         );

      }


   }


   void swap_chain::present(::gpu::texture_site * pgputexturesite, ::gpu::command_buffer * pgpucommandbuffer)
   {

      dummy_model_buffer();

      present_shader();

      // 2. Set viewport

//      if (!m_pshaderPresent)
//      {
//
//         construct_newø(m_pshaderPresent);
//
//         auto pbindingSampler = m_pshaderPresent->binding();
//         pbindingSampler->m_ebinding = ::gpu::e_binding_sampler2d;
//         m_pshaderPresent->m_bDisableDepthTest = true;
//         m_pshaderPresent->m_ecullmode = ::gpu::e_cull_mode_none;
//         const char* fullscreen_vertex_shader = R"shader(// fullscreen_vs.hlsl
//      struct VSOut {
//         float4 pos : SV_POSITION;
//         float2 uv : TEXCOORD0;
//      };
//
//      VSOut main(uint vid : SV_VertexID) {
//         float2 verts[3] = {
//             float2(-1, -1),
//             float2(-1, +3),
//             float2(+3, -1)
//         };
//         float2 uvs[3] = {
//             float2(0, 1),
//             float2(0, -1),
//             float2(2, 1)
//         };
//
//         VSOut o;
//         o.pos = float4(verts[vid], 0, 1);
//         o.uv = 0.5 * (verts[vid] + 1.0);
//         return o;
//      }
//)shader";
//
//         const char* fullscreen_pixel_shader = R"shader(// fullscreen_ps.hlsl
//Texture2D tex : register(t0);
//SamplerState samp : register(s0);
//
//float4 main(float4 pos : SV_POSITION, float2 uv : TEXCOORD0) : SV_Target {
//    
////if(uv.x >0.5)
////{
//// return float4(0.1*0.5, 0.8*0.5, 0.98*0.5, 0.5); // test if the shader pipeline is running
////}
////else
//{
//return tex.Sample(samp, float2(uv.x, 1.0 - uv.y));
//}
//}
//)shader";
//
//         m_pshaderPresent->initialize_shader_with_block(
//            pgpurenderer,
//            as_block(fullscreen_vertex_shader),
//            as_block(fullscreen_pixel_shader));
//
//      }

      //::cast < command_buffer > pcommandbuffer = pgpurenderer->getCurrentCommandBuffer2(::gpu::current_layer());

      ::cast<command_buffer> pcommandbuffer = pgpucommandbuffer;

      //auto pcommandlist = pcommandbuffer->m_pcommandlist;

      defer_construct_newø(m_ptexturesiteaSwapChain);

      auto & ptexturesiteSwapChain = m_ptexturesiteaSwapChain->atø(m_iSwapChainIndex);

      defer_construct_newø(ptexturesiteSwapChain);

      auto ptextureSwapChain = ptexturesiteSwapChain->gpu_texture();

      if (::is_null(ptexturesiteSwapChain))
      {

         throw ::exception(error_wrong_state);

      }


      ptextureSwapChain->set_state(pcommandbuffer, ::gpu::e_texture_state_color_attachment);

      //if (!ptextureSwapChain->m_pheapRenderTargetView)
      //{

      //   ptextureSwapChain->create_render_target();
      //}

      //{
      //   FLOAT colorRGBA2[] = { 0.5f * 0.5f,0.75f * 0.5f, 0.95f * 0.5f, 0.5f };
      //   D3D12_RECT r[1];
      //   r[0].left = 100;
      //   r[0].top = 100;
      //   r[0].right = 200;
      //   r[0].bottom = 200;
      //   pcommandlist->ClearRenderTargetView(ptextureSwapChain->m_handleRenderTargetView,
      //      colorRGBA2, 1, r);

      //}

      //::cast<::gpu_directx12::texture> ptextureSrc = pgputexturesite->gpu_texture();

      auto ptextureSrc = pgputexturesite->gpu_texture();

      // ptextureSrc->set_state(pcommandbuffer, ::gpu::e_texture_state_color_attachment);

      //{

      //   FLOAT colorRGBA2[] = {0.5f * 0.5f, 0.95f * 0.5f, 0.75f * 0.5f, 0.5f};

      //   D3D12_RECT r[1];

      //   r[0].left = 500;
      //   r[0].top = 100;


      //   r[0].right = r[0].left + 100;
      //   r[0].bottom = 100 + 100;

      //   pcommandlist->ClearRenderTargetView(ptextureSrc->current_layer().m_handleRenderTargetView, colorRGBA2, 1,
      //                                       r);
      //}

      ptextureSrc->set_state(pcommandbuffer, ::gpu::e_texture_state_shader_read);

      _present(ptexturesiteSwapChain, pgputexturesite, pgpucommandbuffer);

      //     //m_pshaderPresent->bind(pcommandbuffer, ptextureSwapChain, ptextureSrc);
      //     m_pshaderPresent->bind(pcommandbuffer, ptexturesiteSwapChain);
      //     m_pshaderPresent->bind_source(pcommandbuffer, pgputexturesite, 0);
      //     //pgpucontext->m_pcontext->VSSetShader(m_pvertexshaderFullscreen, nullptr, 0);
      //     //pgpucontext->m_pcontext->PSSetShader(m_ppixelshaderFullscreen, nullptr, 0);

      //     //pgpucontext->m_pcontext->PSSetShaderResources(
      //     //   0, 1, m_ptextureSwapChain->m_pshaderresourceview.pp());
      //     //pgpucontext->m_pcontext->PSSetSamplers(
      //     //   0, 1, m_ptextureSwapChain->m_psamplerstate.pp());

      ///*     D3D11_VIEWPORT vp = {};
      //     vp.TopLeftX = 0;
      //     vp.TopLeftY = 0;
      //     vp.Width = static_cast<float>(m_size.cx);
      //     vp.Height = static_cast<float>(m_size.cy);
      //     vp.MinDepth = 0.0f;
      //     vp.MaxDepth = 1.0f;
      //     pgpucontext->m_pcontext->RSSetViewports(1, &vp);*/

      //     D3D12_VIEWPORT viewport = {};
      //     viewport.TopLeftX = 0;
      //     viewport.TopLeftY = 0;
      //     viewport.Width = static_cast<float>(m_size.cx);
      //     viewport.Height = static_cast<float>(m_size.cy);
      //     viewport.MinDepth = 0.0f;
      //     viewport.MaxDepth = 1.0f;

      //     D3D12_RECT scissorRect = {};
      //     scissorRect.left = 0;
      //     scissorRect.top = 0;
      //     scissorRect.right = m_size.cx;
      //     scissorRect.bottom = m_size.cy;

      //     //::cast < renderer > prenderer = m_pgpurenderer;


      //     //// 4. Set the viewport and scissor
      //     pcommandlist->RSSetViewports(1, &viewport);
      //     pcommandlist->RSSetScissorRects(1, &scissorRect);
      //     pcommandlist->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
      //     pcommandlist->DrawInstanced(3, 1, 0, 0);


      //     m_pshaderPresent->unbind(pcommandbuffer);


           //FLOAT colorRGBA2[] = { 0.5f * 0.5f,0.75f * 0.5f, 0.95f * 0.5f, 0.5f };

           //pcommandlist->ClearRenderTargetView(ptextureSwapChain->m_handleRenderTargetView, 
           //   colorRGBA2, 0, nullptr);

           //{

           //   FLOAT colorRGBA2[] = { 0.5f * 0.5f,0.75f * 0.5f, 0.95f * 0.5f, 0.5f };

           //   D3D12_RECT r[1];

           //   r[0].left = 200;
           //   r[0].top = 100;


           //   r[0].right = 200 + 100;
           //   r[0].bottom = 100 + 100;

           //   pcommandlist->ClearRenderTargetView(ptextureSwapChain->current_layer().m_handleRenderTargetView,
           //      colorRGBA2, 1, r);

           //}

   }


   void swap_chain::_present(::gpu::texture_site * pgputexturesiteSwapChain, ::gpu::texture_site * pgputexturesite, ::gpu::command_buffer * pgpucommandbuffer)
   {

      ::cast < renderer > pgpurenderer = ::gpu::swap_chain::m_pgpurenderer;

      ::cast < context > pgpucontext = pgpurenderer->m_pgpucontext;

      pgpucontext->clear(pgputexturesiteSwapChain->gpu_texture(), ::color::transparent);

      //m_pshaderPresent->bind(pcommandbuffer, ptextureSwapChain, ptextureSrc);
      m_pshaderPresent->bind(pgpucommandbuffer, pgputexturesiteSwapChain);
      m_pshaderPresent->bind_source(pgpucommandbuffer, pgputexturesite, 0);
      //pgpucontext->m_pcontext->VSSetShader(m_pvertexshaderFullscreen, nullptr, 0);
      //pgpucontext->m_pcontext->PSSetShader(m_ppixelshaderFullscreen, nullptr, 0);

      //pgpucontext->m_pcontext->PSSetShaderResources(
      //   0, 1, m_ptextureSwapChain->m_pshaderresourceview.pp());
      //pgpucontext->m_pcontext->PSSetSamplers(
      //   0, 1, m_ptextureSwapChain->m_psamplerstate.pp());

   /*     D3D11_VIEWPORT vp = {};
        vp.TopLeftX = 0;
        vp.TopLeftY = 0;
        vp.Width = static_cast<float>(m_size.cx);
        vp.Height = static_cast<float>(m_size.cy);
        vp.MinDepth = 0.0f;
        vp.MaxDepth = 1.0f;
        pgpucontext->m_pcontext->RSSetViewports(1, &vp);*/

        //D3D12_VIEWPORT viewport = {};
        //viewport.TopLeftX = 0;
        //viewport.TopLeftY = 0;
        //viewport.Width = static_cast<float>(m_size.cx);
        //viewport.Height = static_cast<float>(m_size.cy);
        //viewport.MinDepth = 0.0f;
        //viewport.MaxDepth = 1.0f;

        //D3D12_RECT scissorRect = {};
        //scissorRect.left = 0;
        //scissorRect.top = 0;
        //scissorRect.right = m_size.cx;
        //scissorRect.bottom = m_size.cy;

        ////::cast < renderer > prenderer = m_pgpurenderer;


        ////// 4. Set the viewport and scissor
        //pcommandlist->RSSetViewports(1, &viewport);
        //pcommandlist->RSSetScissorRects(1, &scissorRect);
        //pcommandlist->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
        //pcommandlist->DrawInstanced(3, 1, 0, 0);


        //m_pshaderPresent->unbind(pcommandbuffer);

      auto rectangleImpact = pgpucontext->output_placement();

      auto sizeRaw = pgpucontext->raw_size();

      auto size = rectangleImpact.size();

      pgpucommandbuffer->set_viewport(size, size);

      pgpucommandbuffer->set_scissor(size, size);



      m_pshaderPresent->set_impact_quad(rectangleImpact, sizeRaw);

      m_pshaderPresent->push_properties(pgpucommandbuffer);

      pgpucommandbuffer->draw(m_pmodelbufferDummy);


      pgpucontext->defer_unbind_shader();


   }


   void swap_chain::set_present_state(::gpu::command_buffer *pgpucommandbuffer)
   {


   }


   void swap_chain::swap_buffers()
   {


   }


   ::i32 swap_chain::swap_chain_frame_index()
   {

      return m_iCurrentSwapChainFrame;

   }


      ::i32 swap_chain::swap_chain_image_index() { return m_iCurrentSwapChainImage; }


   ::i32 swap_chain::swap_chain_frame_count()
   {

      return -1;

   }


   ::gpu::texture_site* swap_chain::current_swap_chain_texture()
   {

      defer_check_swap_chain();

      return m_ptexturesiteaSwapChain->element_at(m_iCurrentSwapChainImage);

   }



void swap_chain::on_gpu_context_render_frame(::i32 w, ::i32 h)
{
   
   
}


   bool swap_chain::create_frame_sync(frame_sync &frame)
{

   auto pcontext = m_pgpurenderer->m_pgpucontext;
   //;
   //;
   //auto vkdevice = pcontext->logicalDevice();
   // ----------------------------------------------------
   // Fence (CPU → GPU)
   // ----------------------------------------------------

   defer_constructø(frame.m_pgpufenceInFlight);

   frame.m_pgpufenceInFlight->initialize_gpu_fence(m_pgpurenderer->m_pgpucontext, true);

   // VkFenceCreateInfo fenceInfo{};
   // fenceInfo.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;

   //// Start signaled so first frame doesn't stall
   // fenceInfo.flags = VK_FENCE_CREATE_SIGNALED_BIT;

   // if (vkCreateFence(
   //         vkdevice,
   //         &fenceInfo,
   //         nullptr,
   //         &frame.m_vkfenceInFlight) != VK_SUCCESS)
   //{
   //    return false;
   // }

   // ----------------------------------------------------
   // Semaphores (GPU → GPU)
   // ----------------------------------------------------

   defer_constructø(frame.m_pgpusemaphoreImageAvailable);

   frame.m_pgpusemaphoreImageAvailable->initialize_gpu_semaphore(m_pgpurenderer->m_pgpucontext);

   defer_constructø(frame.m_pgpusemaphoreRenderFinished);

   frame.m_pgpusemaphoreRenderFinished->initialize_gpu_semaphore(m_pgpurenderer->m_pgpucontext);

   // VkSemaphoreCreateInfo semaphoreInfo{};
   // semaphoreInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;

   // if (vkCreateSemaphore(
   //         vkdevice,
   //         &semaphoreInfo,
   //         nullptr,
   //         &frame.m_vksemaphoreImageAvailable) != VK_SUCCESS)
   //{
   //    return false;
   // }

   // if (vkCreateSemaphore(
   //         vkdevice,
   //         &semaphoreInfo,
   //         nullptr,
   //         &frame.m_vksemaphoreRenderFinished) != VK_SUCCESS)
   //{
   //    return false;
   // }

   return true;
}

void swap_chain::destroy_frame_sync(frame_sync &frame)
{

   //::cast<::gpu_vulkan::context> pcontext = m_pgpucontextSwapChain;
   //auto vkdevice = pcontext->logicalDevice();

   // if (frame.m_vkfenceInFlight != VK_NULL_HANDLE)
   //    vkDestroyFence(vkdevice, frame.m_vkfenceInFlight, nullptr);

   // if (frame.m_vksemaphoreImageAvailable != VK_NULL_HANDLE)
   //    vkDestroySemaphore(vkdevice, frame.m_vksemaphoreImageAvailable, nullptr);

   // if (frame.m_vksemaphoreRenderFinished != VK_NULL_HANDLE)
   //    vkDestroySemaphore(vkdevice, frame.m_vksemaphoreRenderFinished, nullptr);

   frame = {};
}


swap_chain::frame_sync &swap_chain::frame(::collection::index iFrameIndex)
{

   if (iFrameIndex < 0 || iFrameIndex > 16)
   {

      throw ::exception(error_failed, "invalid frame index!");
   }

   auto &framesync = m_framesynca.atø(iFrameIndex);

   if (!framesync.m_pgpufenceInFlight)
   {

      create_frame_sync(framesync);
   }

   return framesync;
}

} // namespace direct2d



