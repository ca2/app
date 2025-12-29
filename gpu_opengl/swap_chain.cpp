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

      //m_VAOFullScreenQuad = 0;
      //m_VBOFullScreenQuad = 0;


   }


   swap_chain::~swap_chain()
   {
      

   }


   void swap_chain::present(::gpu::texture* pgputexture)
   {

      try
      {

         ::gpu::context_lock contextlock(m_pgpurenderer->m_pgpucontext);

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

            m_pshaderCopyTextureOnEndDraw->initialize_shader_with_block(
               m_pgpurenderer, pvertexshader, pfragmentshader, 
               //{}, {},
               m_pgpucontext->input_layout(::gpu_properties<::graphics3d::sequence2_uv>()));
            øconstruct_new(m_ptextureSwapChain);
            m_ptextureSwapChain->m_pgpurenderer = m_pgpucontext->m_pgpurenderer;
            m_ptextureSwapChain->m_gluTextureID = -1023;
            m_ptextureSwapChain->m_gluType = 0;
         }

         glBindFramebuffer(GL_FRAMEBUFFER, 0);
         GLCheckError("");
         glDrawBuffer(GL_BACK);
         GLCheckError("");

         auto pcommandbuffer = m_pgpucontext->m_pgpurenderer->getCurrentCommandBuffer2(::gpu::current_frame());

         auto sizeContext = m_pgpucontext->m_rectangle.size();
         
         pcommandbuffer->begin_render(m_pshaderCopyTextureOnEndDraw, m_ptextureSwapChain);

         pcommandbuffer->set_viewport(sizeContext);

         pcommandbuffer->set_scissor(sizeContext);

         glDisable(GL_BLEND);
         GLCheckError("");
         glEnable(GL_DEPTH_TEST);
         GLCheckError("");
         glDepthMask(GL_TRUE);
         GLCheckError("");

         glClearColor(0.8f, 0.5f, 0.f, 0.8f);
         GLCheckError("");
         glClearDepth(1.0f);
         GLCheckError("");
         glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
         GLCheckError("");
         glDisable(GL_BLEND);
         GLCheckError("");
         glDisable(GL_DEPTH_TEST);
         GLCheckError("");
         glDepthMask(GL_FALSE);
         GLCheckError("");

         if (1)
         {

            auto pmodelbufferFullscreenQuad =
               m_pgpucontext->sequence2_uv_fullscreen_quad_model_buffer(::gpu::current_frame());

            //m_pshaderCopyTextureOnEndDraw->_bind(pcommandbuffer, ::gpu::e_scene_none);

            m_pshaderCopyTextureOnEndDraw->bind_source(pcommandbuffer, pgputexture);

            pcommandbuffer->draw(pmodelbufferFullscreenQuad);

            //pmodelbufferFullscreenQuad->draw2(pcommandbuffer);

            pmodelbufferFullscreenQuad->unbind(pcommandbuffer);

            m_pgpucontext->defer_unbind_shader();

         }

         //  glClearColor(0.f, 0.5f, 0.f, 0.5f);
         // GLCheckError("");
         //  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
         // GLCheckError("");
         //  glDisable(GL_BLEND);
         // GLCheckError("");
         //  glDisable(GL_DEPTH_TEST);
         // GLCheckError("");

         ::cast<device> pdevice = m_pgpurenderer->m_pgpucontext->m_pgpudevice;

         pdevice->_swap_buffers();

      }
      catch (...)
      {


      }


   }

} // namespace gpu_opengl


