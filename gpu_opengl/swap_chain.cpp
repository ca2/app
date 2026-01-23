#include "framework.h"
#include "_gpu_opengl.h"
#include "command_buffer.h"
#include "context.h"
#include "device.h"
#include "frame_buffer.h"
#include "lock.h"
#include "model_buffer.h"
#include "renderer.h"
#include "swap_chain.h"
#include "texture.h"
#include "bred/gpu/binding.h"
#include "bred/gpu/context_lock.h"
#include "bred/gpu/device.h"
#include "bred/gpu/frame.h"
#include "bred/gpu/render_state.h"
#include "aura/user/user/interaction.h"
#include "aura/windowing/window.h"


namespace gpu_opengl
{


   swap_chain::swap_chain()
   {
      
      //m_iFbo = 0;
      //m_iFboTex = 0;

      //m_VAOFullScreenQuad = 0;
      //m_VBOFullScreenQuad = 0;
      
      m_pszCopyTextureVertexShader = R"vert(#version 410 core


layout(location = 0) in vec2 aPos;
layout(location = 1) in vec2 aTexCoord;

out vec2 TexCoord;

void main() {
gl_Position = vec4(aPos.xy, 0.0, 1.0);
TexCoord = aTexCoord;
}
)vert";
      
      
      m_pszCopyTextureFragmentShader = R"frag(#version 410 core

in vec2 TexCoord;
out vec4 FragColor;

uniform sampler2D uTexture;

void main() {
//if(TexCoord.x > 0.5)
//{
//FragColor=vec4(0.0, TexCoord.x *0.5, TexCoord.y *0.5 , 0.5);
//}
//else
{
FragColor = texture(uTexture, TexCoord);
}

}
)frag";
      


   }


   swap_chain::~swap_chain()
   {
      

   }


   void swap_chain::present(::gpu::texture* pgputexture)
   {

      if (!m_pgpucontext)
      {

         information("swap_chain::present No gpu::context");

         return;

      }

      if (!m_pgpucontext->m_pacmewindowingwindowWindowSurface)
      {

         information("swap_chain::present No window");

         return;

      }

      if (m_pgpucontext->m_pacmewindowingwindowWindowSurface->__x11_Display()
          &&
          m_pgpucontext->m_pacmewindowingwindowWindowSurface->m_lX11MapNotify != 1)
      {

         information("swap_chain::present m_lX11MapNotify != 1");

         return;

      }

      try
      {

         ::gpu::context_lock contextlock(m_pgpucontext);

         
         auto pshader = present_shader();

         auto r = m_pwindowSwapChain->get_window_rectangle();

         if (r.area() <= 0)
         {

            return;

         }

         glBindVertexArray(0);
         GLCheckError("");
         glUseProgram(0);
         GLCheckError("");
         
         ::cast < ::gpu_opengl::texture > ptexturePresent = m_ptexturePresent;

#if defined(__APPLE__)
         if(!ptexturePresent->m_gluFbo)
         {
            
            ptexturePresent->create_render_target();
            
         }
         glBindFramebuffer(GL_FRAMEBUFFER, ptexturePresent->m_gluFbo);
         //glBindFramebuffer(GL_FRAMEBUFFER, ptexturePresent->m_gluFbo);
         GLCheckError("");
#else
         glBindFramebuffer(GL_FRAMEBUFFER, 0);
         GLCheckError("");
         glDrawBuffer(GL_BACK);
         GLCheckError("");
#endif
         glDisable(GL_SCISSOR_TEST);
         GLCheckError("");
         glDisable(GL_BLEND);
         GLCheckError("");
         glDisable(GL_DEPTH_TEST);
         GLCheckError("");
         glDepthMask(GL_FALSE);
         GLCheckError("");
//#if 0
#if 1

         auto pcommandbuffer = m_pgpucontext->m_pgpurenderer->getCurrentCommandBuffer2(::gpu::current_frame());

         auto sizeContext = m_pgpucontext->m_rectangle.size();
         
         pcommandbuffer->begin_render(m_pshaderPresent, m_ptexturePresent);

         pcommandbuffer->set_viewport(sizeContext);

         //pcommandbuffer->set_scissor(sizeContext);
         
         glDisable(GL_SCISSOR_TEST);
         GLCheckError("");
         //pcommandbuffer->set_scissor(sizeContext);

         //glDisable(GL_BLEND);
         //GLCheckError("");
         //glEnable(GL_DEPTH_TEST);
         //GLCheckError("");
         //glDepthMask(GL_TRUE);
         //GLCheckError("");


         glClearColor(0.8f, 0.5f, 0.f, 0.8f);
         GLCheckError("");
         //glClearDepth(1.0f);
         //GLCheckError("");
         //glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
         glClear(GL_COLOR_BUFFER_BIT);
         GLCheckError("");
         //glDisable(GL_BLEND);
         //GLCheckError("");
         //glDisable(GL_DEPTH_TEST);
         //GLCheckError("");
         //glDepthMask(GL_FALSE);
         //GLCheckError("");

         if (1)
         {

            auto pmodelbufferFullscreenQuad =
               m_pgpucontext->sequence2_uv_fullscreen_quad_model_buffer(::gpu::current_frame());

            //m_pshaderCopyTextureOnEndDraw->_bind(pcommandbuffer, ::gpu::e_scene_none);

            m_pshaderPresent->bind_source(pcommandbuffer, pgputexture);

            pcommandbuffer->draw(pmodelbufferFullscreenQuad);

            //pmodelbufferFullscreenQuad->draw2(pcommandbuffer);

            pmodelbufferFullscreenQuad->unbind(pcommandbuffer);

         }

         pcommandbuffer->end_render();

         m_pgpucontext->defer_unbind_shader();

//#endif
#if defined(__APPLE__)
#else
         glBindFramebuffer(GL_FRAMEBUFFER, 0);
         GLCheckError("");
#endif
         
#endif

#if 0

         glClearColor(0.5f, 0.5f, 0.5f, 0.5f);
         GLCheckError("");
         glClear(GL_COLOR_BUFFER_BIT);
           //glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
         GLCheckError("");
          // glDisable(GL_BLEND);
          //GLCheckError("");
          // glDisable(GL_DEPTH_TEST);
          //GLCheckError("");

#endif

          //glDisable(GL_SCISSOR_TEST);

          // 1. Is a context current?
          if (!glGetString(GL_VERSION))
          {
             informationf("NO CURRENT GL CONTEXT\n");
          }
          //else
          //{
          //   informationf("GL VERSION: %s\n", glGetString(GL_VERSION));
          //}

          //// 2. Which framebuffer are we clearing?
          //GLint fb = -1;
          //glGetIntegerv(GL_DRAW_FRAMEBUFFER_BINDING, &fb);
          //informationf("DRAW FB = %d\n", fb);

          //// 3. Viewport
          //GLint vp[4];
          //glGetIntegerv(GL_VIEWPORT, vp);
          //informationf("VIEWPORT = %d %d %d %d\n", vp[0], vp[1], vp[2], vp[3]);
         //glClearColor(0, 0, 1, 1);
         //glClear(GL_COLOR_BUFFER_BIT);
         //glFinish(); // force GPU execution
         //::cast<device> pdevice = m_pgpurenderer->m_pgpucontext->m_pgpudevice;

         //pdevice->_swap_buffers();

         swap_buffers();

      }
      catch (...)
      {


      }


   }


void swap_chain::on_gpu_context_render_frame(int w, int h)
{
   
   auto pshaderRender = render_shader(w, h);
   
   auto r = m_pwindowSwapChain->get_window_rectangle();

   if (r.area() <= 0)
   {

      return;

   }
   
#if 1
   auto t = ::time::now().floating_second();
   float fGreen = ::sin(t * 0.5  * 2.0 * 3.1415) * 0.25 + 0.5;
   //glEnable(GL_BLEND);
   //glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
   glViewport(0, 0, w, h);
   float alpha = 0.69;
   glClearColor(0.2f * alpha, fGreen * alpha, 0.5f * alpha, 1.0f * alpha);
   glClear(GL_COLOR_BUFFER_BIT);
#endif

   
   //auto pcommandbuffer = m_pgpucontext->beginSingleTimeCommands(nullptr);

   //glBindVertexArray(0);
   //GLCheckError("");
   //glUseProgram(0);
   //GLCheckError("");


   //glBindFramebuffer(GL_FRAMEBUFFER, 0);
   //GLCheckError("");
   //glDrawBuffer(GL_BACK);
   GLCheckError("");
   glDisable(GL_SCISSOR_TEST);
   GLCheckError("");
   glDisable(GL_BLEND);
   GLCheckError("");
   glDisable(GL_DEPTH_TEST);
   GLCheckError("");
   glDepthMask(GL_FALSE);
   GLCheckError("");
//#if 0
#if 1


//   auto pcommandbuffer = m_pgpucontext->m_pgpurenderer->getCurrentCommandBuffer2(::gpu::current_frame());

///   auto sizeContext = m_pgpucontext->m_rectangle.size();
   ///
   ::cast < ::gpu_opengl::shader > pshader = pshaderRender;
   
   auto iProgram = pshader->m_ProgramID;
   
   GLint currentProgram = 0;
   glGetIntegerv(GL_CURRENT_PROGRAM, &currentProgram);
   GLCheckError("");
   
   if(currentProgram != iProgram)
   {
      glUseProgram(iProgram);
      GLCheckError("");
   }
   
   glDisable(GL_DEPTH_TEST);
   GLCheckError("");
   glDisable(GL_BLEND);
   GLCheckError("");

   glViewport(0, 0, w, h);
   GLCheckError("");

   glDisable(GL_SCISSOR_TEST);
   GLCheckError("");
   
   if(!m_pmodelbufferRender)
   {
      
      m_pmodelbufferRender = m_pgpucontext->create_sequence2_uv_fullscreen_quad_model_buffer(nullptr);
      
   }

   pshaderRender->bind_source(nullptr, m_ptextureaSwapChain->element_at(m_iCurrentSwapChainFrame));

   
   //pmodelbufferFullscreenQuad->draw2(nullptr);
   m_pmodelbufferRender->bind2(nullptr);
   m_pmodelbufferRender->draw2(nullptr);
   m_pmodelbufferRender->unbind(nullptr);

      //pmodelbufferFullscreenQuad->draw2(pcommandbuffer);

   //pmodelbufferFullscreenQuad->unbind(pcommandbuffer);

   //pcommandbuffer->end_render();

   glUseProgram(0);
   GLCheckError("");
   
   //glFlush();
   //m_pgpucontext->defer_unbind_shader();

//#endif

   //glBindFramebuffer(GL_FRAMEBUFFER, 0);
   //GLCheckError("");
#endif

#if 0
   //glEnable(GL_BLEND);
   //glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
   glViewport(0, 0, w, h);
   float alpha = 0.69;
   glClearColor(0.2f * alpha, 0.5f * alpha, 1.0f * alpha, 1.0f * alpha);
   glClear(GL_COLOR_BUFFER_BIT);
#endif
   
}

//
//::gpu::shader * swap_chain::present_shader()
//{
//   if (!m_pshaderCopyTextureOnEndDraw2)
//   {
//      
//
//      pshaderCopyTexture2 = øcreate_new<::gpu_opengl::shader>();
//      
//      m_pshaderCopyTextureOnEndDraw2 = pshaderCopyTexture2;
//      
//      pshaderCopyTexture2->m_bEnableBlend = false;
//      
//      pshaderCopyTexture2->m_bDisableDepthTest = true;
//      auto pbindingTexture = pshaderCopyTexture2->binding();
//      pbindingTexture->m_ebinding = ::gpu::e_binding_sampler2d;
//      pbindingTexture->m_iTextureUnit = 0;
//      
//      pshaderCopyTexture2->m_bDisableDepthTest = true;
//      pshaderCopyTexture2->m_bEnableBlend = false;
//      
//      pshaderCopyTexture2->initialize_shader_with_block(
//                                                                  m_pgpurenderer, pvertexshader, pfragmentshader,
//                                                                  //{}, {},
//                                                                  m_pgpucontext->input_layout(::gpu_properties<::graphics3d::sequence2_uv>()));
//      øconstruct_new(m_ptextureSwapChain);
//      m_ptextureSwapChain->m_pgpurenderer = m_pgpucontext->m_pgpurenderer;
//      m_ptextureSwapChain->m_gluTextureID = -1023;
//      m_ptextureSwapChain->m_gluType = 0;
//   }
//   
//   return m_pshaderCopyTextureOnEndDraw2;
//   
//}

::pointer<::gpu::shader > swap_chain::create_copy_texture_shader()
{
  auto pshaderCopyTexture2 = øcreate_new<::gpu_opengl::shader>();
      
      pshaderCopyTexture2->m_bEnableBlend = false;
      
      pshaderCopyTexture2->m_bDisableDepthTest = true;
      auto pbindingTexture = pshaderCopyTexture2->binding();
      pbindingTexture->m_ebinding = ::gpu::e_binding_sampler2d;
      pbindingTexture->m_iTextureUnit = 0;
      
      pshaderCopyTexture2->m_bDisableDepthTest = true;
      pshaderCopyTexture2->m_bEnableBlend = false;
      
      pshaderCopyTexture2->initialize_shader_with_block(
         m_pgpurenderer,
         m_pszCopyTextureVertexShader,
         m_pszCopyTextureFragmentShader,
                                                                  //{}, {},
                                                                  m_pgpucontext->input_layout(::gpu_properties<::graphics3d::sequence2_uv>()));
   
   return pshaderCopyTexture2;
   
}


::gpu::shader * swap_chain::present_shader()
{
   if (::is_null(m_pshaderPresent))
   {
      
      m_pshaderPresent = create_copy_texture_shader();
      
   }
   
   auto size = m_pgpucontext->m_pacmewindowingwindowWindowSurface->get_window_rectangle().size();
   
   if(::is_null(m_ptexturePresent) ||
      m_ptexturePresent->size() != size
      )
   {
      
      øconstruct_new(m_ptexturePresent);
#if defined(__APPLE__)
      defer_update_swap_chain_textures(size);
//      m_ptexturePresent = m_p
//      ::gpu::texture_attributes textureattributes;
//      
//      textureattributes.m_rectangleTarget.top_left() = ::int_point();
//      textureattributes.m_rectangleTarget.set_size(m_pgpucontext->m_pacmewindowingwindowWindowSurface->get_window_rectangle().size());
//      
//      m_ptexturePresent->initialize_texture(m_pgpucontext->m_pgpurenderer, textureattributes);
                                          
#else
   
      m_ptextureSwapChain->m_pgpurenderer = m_pgpucontext->m_pgpurenderer;

      m_ptextureSwapChain->m_gluTextureID = -1023;
      m_ptextureSwapChain->m_gluType = 0;
                                                   
#endif
      
   }
   
#if defined(__APPLE__)
   m_ptexturePresent = m_ptextureaSwapChain->element_at(m_iCurrentSwapChainFrame);

#endif
   
   return m_pshaderPresent;
   
}


void swap_chain::defer_update_swap_chain_textures(const ::int_size & size)
{
   
   if(::is_null(m_ptextureaSwapChain)
      || m_ptextureaSwapChain->size() != 3
      || m_ptextureaSwapChain->first()->size() != size)
   {
      øconstruct_new(m_ptextureaSwapChain);

      for(int i = 0; i < 3; i++)
      {
         auto & ptextureSwapChain = m_ptextureaSwapChain->ø(i);
         øconstruct(ptextureSwapChain);
         ::gpu::texture_attributes textureattributes(size);
         ptextureSwapChain->initialize_texture(m_pgpucontext->m_pgpurenderer, textureattributes);

      }
      
//         textureattributes.m_rectangleTarget.top_left() = ::int_point();
//         textureattributes.m_rectangleTarget.set_size(size);
      
      
   }
   //         if(m_iFbo != 0)
   //         {
   //            GLuint uFbo = m_iFbo;
   //            glDeleteFramebuffers(1, &uFbo);
   //            m_iFbo = 0;
   //         }
   //         if(m_iFboTex != 0)
   //         {
   //            GLuint uFboTex = m_iFboTex;
   //            glDeleteTextures(1, &uFboTex);
   //
   //            m_iFboTex= 0;
   //         }
   //
   //         if(m_iFbo == 0 && w > 0 && h > 0)
   //         {
   //
   //            GLuint uFbo = 0;
   //
   //            glGenFramebuffers(1, &uFbo);
   //            GLCheckError("");
   //
   //            m_iFbo = uFbo;
   //
   //            GLuint uTex = 0;
   //
   //            glGenTextures(1, &uTex);
   //            GLCheckError("");
   //
   //
   //            m_iFboTex = uTex;
   //
   //
   //            glBindTexture(GL_TEXTURE_2D, uTex);
   //            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, w, h, 0,
   //                         GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
   //
   //            glFramebufferTexture2D(GL_FRAMEBUFFER,
   //                                   GL_COLOR_ATTACHMENT0,
   //                                   GL_TEXTURE_2D,
   //                                   uTex, 0);
   //
   //         }
   //
   //}
   
}


::gpu::shader * swap_chain::render_shader(int w, int h)
{
   
   ::int_size size(w, h);
   
   if(m_pgpucontext->m_rectangle.size() != size
      || ::is_null(m_ptextureaSwapChain)
      || m_ptextureaSwapChain->size() != 3
      || m_ptextureaSwapChain->first()->size() != size
      || ::is_null(m_pshaderRender))
   {
      
      m_pgpucontext->on_resize(size);
      
      m_pgpucontext->m_rectangle.set_size(size);
      
      //{
      
      //::gpu::context_lock contextlock(m_pgpucontext);
      
      if(::is_null(m_pshaderRender))
      {
         
         m_pshaderRender = create_copy_texture_shader();
         
      }
      
      defer_update_swap_chain_textures(size);
      
      
      //m_pgpucontext->m_pacmewindowingwindowWindowSurface->_
      
   }
      
      return m_pshaderRender;
   
}


} // namespace gpu_opengl



