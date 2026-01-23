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
      
      m_iFbo = 0;
      m_iFboTex = 0;

      //m_VAOFullScreenQuad = 0;
      //m_VBOFullScreenQuad = 0;


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

      if (m_pgpucontext->m_pacmewindowingwindowWindowSurface->m_lX11MapNotify != 1)
      {

         information("swap_chain::present m_lX11MapNotify != 1");

         return;

      }

      try
      {

         ::gpu::context_lock contextlock(m_pgpucontext);

         if (!m_pshaderCopyTextureOnEndDraw)
         {

            auto pvertexshader = R"vert(#version 330 core
layout(location = 0) in vec2 aPos;
layout(location = 1) in vec2 aTexCoord;

out vec2 TexCoord;

void main() {
   gl_Position = vec4(aPos.xy, 0.0, 1.0);
   TexCoord = aTexCoord;
}
)vert";


            auto pfragmentshader = R"frag(#version 330 core
in vec2 TexCoord;
out vec4 FragColor;

uniform sampler2D uTexture;

void main() {
//if(TexCoord.x > 0.5)
//{
//FragColor=vec4(0.0, 0.0, 0.5, 0.5);
//}
//else
{
FragColor = texture(uTexture, TexCoord);
}

}
)frag";

            m_pshaderCopyTextureOnEndDraw = øcreate_new<::gpu_opengl::shader>();

            m_pshaderCopyTextureOnEndDraw->m_bEnableBlend = false;

            m_pshaderCopyTextureOnEndDraw->m_bDisableDepthTest = true;
            auto pbindingTexture = m_pshaderCopyTextureOnEndDraw->binding();
            pbindingTexture->m_ebinding = ::gpu::e_binding_sampler2d;
            pbindingTexture->m_iTextureUnit = 0;

            m_pshaderCopyTextureOnEndDraw->m_bDisableDepthTest = true;
            m_pshaderCopyTextureOnEndDraw->m_bEnableBlend = false;

            m_pshaderCopyTextureOnEndDraw->initialize_shader_with_block(
               m_pgpurenderer, pvertexshader, pfragmentshader, 
               //{}, {},
               m_pgpucontext->input_layout(::gpu_properties<::graphics3d::sequence2_uv>()));
            øconstruct_new(m_ptextureSwapChain);
            m_ptextureSwapChain->m_pgpurenderer = m_pgpucontext->m_pgpurenderer;
            m_ptextureSwapChain->m_gluTextureID = -1023;
            m_ptextureSwapChain->m_gluType = 0;
         }

         auto r = m_pwindowSwapChain->get_window_rectangle();

         if (r.area() <= 0)
         {

            return;

         }

         glBindVertexArray(0);
         GLCheckError("");
         glUseProgram(0);
         GLCheckError("");


         glBindFramebuffer(GL_FRAMEBUFFER, 0);
         GLCheckError("");
         glDrawBuffer(GL_BACK);
         GLCheckError("");
         glDisable(GL_SCISSOR_TEST);
         GLCheckError("");
         glDisable(GL_BLEND);
         GLCheckError("");
         glDisable(GL_DEPTH_TEST);
         GLCheckError("");
         glDepthMask(GL_FALSE);
         GLCheckError("");
#if 0
#if 1

         auto pcommandbuffer = m_pgpucontext->m_pgpurenderer->getCurrentCommandBuffer2(::gpu::current_frame());

         auto sizeContext = m_pgpucontext->m_rectangle.size();
         
         pcommandbuffer->begin_render(m_pshaderCopyTextureOnEndDraw, m_ptextureSwapChain);

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

            m_pshaderCopyTextureOnEndDraw->bind_source(pcommandbuffer, pgputexture);

            pcommandbuffer->draw(pmodelbufferFullscreenQuad);

            //pmodelbufferFullscreenQuad->draw2(pcommandbuffer);

            pmodelbufferFullscreenQuad->unbind(pcommandbuffer);

         }

         pcommandbuffer->end_render();

         m_pgpucontext->defer_unbind_shader();

#endif

         glBindFramebuffer(GL_FRAMEBUFFER, 0);
         GLCheckError("");
#endif

#if 1

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
   
   ::int_rectangle rectangleWindow(0, 0, w, h);
   
   if(m_pgpucontext->m_rectangle != rectangleWindow.size()
      || m_iFbo <= 0
      || m_iFboTex <= 0)
   {
      
      m_pgpucontext->on_resize(rectangleWindow.size());
      
      m_pgpucontext->m_rectangle.set_size(rectangleWindow.size());
      
      {
         
         ::gpu::context_lock contextlock(m_pgpucontext);
         
         if(m_iFbo != 0)
         {
            GLuint uFbo = m_iFbo;
            glDeleteFramebuffers(1, &uFbo);
            m_iFbo = 0;
         }
         if(m_iFboTex != 0)
         {
            GLuint uFboTex = m_iFboTex;
            glDeleteTextures(1, &uFboTex);
            
            m_iFboTex= 0;
         }
         
         if(m_iFbo == 0 && w > 0 && h > 0)
         {
            
            GLuint uFbo = 0;
            
            glGenFramebuffers(1, &uFbo);
            GLCheckError("");
            
            m_iFbo = uFbo;
            
            GLuint uTex = 0;
            
            glGenTextures(1, &uTex);
            GLCheckError("");
            
            
            m_iFboTex = uTex;
            
            
            glBindTexture(GL_TEXTURE_2D, uTex);
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, w, h, 0,
                         GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
            
            glFramebufferTexture2D(GL_FRAMEBUFFER,
                                   GL_COLOR_ATTACHMENT0,
                                   GL_TEXTURE_2D,
                                   uTex, 0);
            
         }
         
      }
      
      //m_pgpucontext->m_pacmewindowingwindowWindowSurface->_
      
   }
   glEnable(GL_BLEND);
   glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
   glViewport(0, 0, w, h);
   float alpha = 0.69;
   glClearColor(0.2f * alpha, 0.4f * alpha, 0.9f * alpha, 1.0f * alpha);
   glClear(GL_COLOR_BUFFER_BIT);
   
   
}

} // namespace gpu_opengl



