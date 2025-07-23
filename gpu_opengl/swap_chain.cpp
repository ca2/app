#include "framework.h"
#include "command_buffer.h"
#include "context.h"
#include "device.h"
#include "frame_buffer.h"
#include "lock.h"
#include "model_buffer.h"
#include "renderer.h"
#include "swap_chain.h"
#include "texture.h"
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


   //GLuint createFullscreenQuad(GLuint& quadVBO);


//   void swap_chain::initialize_render_target(::gpu::renderer* prenderer, const ::int_size& size, ::pointer <::gpu::render_target>previous)
//   {
//
//      ::gpu_opengl::render_target::initialize_render_target(prenderer, size, previous);
//
//      __defer_construct_new(m_ptextureSwapChain);
//
//      prenderer->m_prenderstate->m_emode = ::gpu::e_render_mode_single_frame_state;
//
//      m_ptextureSwapChain->m_pgpurenderer = prenderer;
//
//      m_ptextureSwapChain->m_gluTextureID = 0;
//
//   }
//
//
//   void swap_chain::endDraw(::draw2d_gpu::graphics* pgraphics, ::user::interaction* puserinteraction, ::gpu::renderer* pgpurendererSrc)
//   {
//
//      ::gpu::swap_chain::endDraw(pgraphics, puserinteraction, pgpurendererSrc);
//
//      auto pwindow = puserinteraction->window();
//
//      if (!m_pgpucontextSwapChain)
//      {
//
//         m_pgpucontextSwapChain = pgpurendererSrc->m_pgpucontext->m_pgpudevice->create_window_context(pwindow);
//
//      }
//
//      auto rectanglePlacement = pwindow->get_window_rectangle();
//
//      m_pgpucontextSwapChain->set_placement(rectanglePlacement);
//
//      auto prendererOutput = m_pgpucontextSwapChain->get_gpu_renderer();
//
//      prendererOutput->defer_update_renderer();
//
//
//      ::cast<renderer>prendererSrc = pgpurendererSrc;
//
//
//      m_pgpucontextSwapChain->send_on_context([this, prendererSrc]()
//         {
//
//            m_pgpucontextSwapChain->m_pgpurenderer->do_on_frame([this, prendererSrc]()
//               {
//
//                  m_pgpucontextSwapChain->clear(::argb(127, 140 / 2, 220 / 2, 240 / 2));
//                  //m_pgpucontext->clear(::color::transparent);
//
//
//                  if (1)
//                  {
//
//
//                     //if (m_pimpact->global_ubo_block().size() > 0)
//                     //{
//
//                       // update_global_ubo(m_pgpucontext);
//
//                     //}
//
//                     //m_pscene->on_render(m_pgpucontext);
//
//                     //_blend_image(image, m_rectangle);
//
//            //         glDisable(GL_BLEND);
//            //         //glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
//
//
//                     if (!m_pshaderCopyTextureOnEndDraw)
//                     {
//
//                        auto pvertexshader = R"vert(#version 330 core
//layout(location = 0) in vec2 aPos;
//layout(location = 1) in vec2 aTexCoord;
//
//out vec2 TexCoord;
//
//void main() {
//   gl_Position = vec4(aPos.xy, 0.0, 1.0);
//   TexCoord = aTexCoord;
//}
//)vert";
//
//
//                        auto pfragmentshader = R"frag(#version 330 core
//in vec2 TexCoord;
//out vec4 FragColor;
//
//uniform sampler2D uTexture;
//
//void main() {
//   FragColor = texture(uTexture, TexCoord);
//}
//)frag";
//
//                        m_pshaderCopyTextureOnEndDraw = __create_new < ::gpu_opengl::shader >();
//
//                        m_pshaderCopyTextureOnEndDraw->initialize_shader_with_block(
//                           m_pgpucontextSwapChain->m_pgpurenderer,
//                           pvertexshader, pfragmentshader);
//
//
//                     }
//
//                     m_pshaderCopyTextureOnEndDraw->bind();
//
//                     if (1)
//                     {
//
//                        glActiveTexture(GL_TEXTURE0);
//
//                        int iGlError1 = glGetError();
//
//                        ::cast < context > pcontext = prendererSrc->m_pgpucontext;
//
//                        GLuint tex = pcontext->m_pframebuffer->m_tex;
//
//                        glBindTexture(GL_TEXTURE_2D, tex);
//
//                        int iGlError2 = glGetError();
//
//                        ::cast < ::gpu_opengl::shader > pshaderOnEndDraw = m_pshaderCopyTextureOnEndDraw;
//
//                        pshaderOnEndDraw->_set_int("uTexture", 0);
//
//                        if (!m_VAOFullScreenQuad)
//                        {
//
//                           m_VAOFullScreenQuad = createFullscreenQuad(m_VBOFullScreenQuad);
//
//                        }
//
//                        glBindVertexArray(m_VAOFullScreenQuad);
//
//                        int iGlError00 = glGetError();
//
//                        glDrawArrays(GL_TRIANGLES, 0, 6); // assuming 2 triangles (quad)
//
//                        int iGlError01 = glGetError();
//
//                        glBindVertexArray(0);
//
//                        int iGlErrorA = glGetError();
//
//                        glBindTexture(GL_TEXTURE_2D, 0);
//
//                        int iGlErrorB = glGetError();
//
//                        debug() << "gl error";
//
//                     }
//
//                     m_pshaderCopyTextureOnEndDraw->unbind();
//
//                  }
//
//               });
//
//
//         });
//
//
//   }
//

   //::gpu::texture* swap_chain::current_texture()
   //{

   //   return m_ptextureSwapChain;

   //}


   void swap_chain::present(::gpu::texture* pgputexture)
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
//{
 FragColor = texture(uTexture, TexCoord);
//}

}
)frag";

         m_pshaderCopyTextureOnEndDraw = __create_new < ::gpu_opengl::shader >();

         m_pshaderCopyTextureOnEndDraw->m_bEnableBlend = false;

         m_pshaderCopyTextureOnEndDraw->m_bDisableDepthTest = true;

         m_pshaderCopyTextureOnEndDraw->initialize_shader_with_block(
            m_pgpurenderer,
            pvertexshader, pfragmentshader,
            {},
            {},
            {},
            m_pgpucontext->input_layout(::gpu_properties <::graphics3d::sequence2_uv>())
         );


      }

      glBindFramebuffer(GL_FRAMEBUFFER, 0);

      auto pcommandbuffer = m_pgpucontext->m_pgpurenderer->getCurrentCommandBuffer2(::gpu::current_frame());

      pcommandbuffer->set_viewport(m_pgpucontext->m_rectangle.size());

      pcommandbuffer->set_scissor(m_pgpucontext->m_rectangle.size());

      glDrawBuffer(GL_BACK);

      glClearColor(0.f, 0.5f, 0.f, 0.5f);
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
      glDisable(GL_BLEND);
      glDisable(GL_DEPTH_TEST);

      if (1)
      {

   /*      if (!m_VAOFullScreenQuad)
         {

            m_VAOFullScreenQuad = createFullscreenQuad(m_VBOFullScreenQuad);

         }*/


         auto pmodelbufferFullscreenQuad = m_pgpucontext->sequence2_uv_fullscreen_quad_model_buffer(::gpu::current_frame());

         m_pshaderCopyTextureOnEndDraw->bind();

         m_pshaderCopyTextureOnEndDraw->bind_source(pgputexture);

         pmodelbufferFullscreenQuad->bind(pcommandbuffer);

         pmodelbufferFullscreenQuad->draw(pcommandbuffer);

         pmodelbufferFullscreenQuad->unbind(pcommandbuffer);

         //int iGlError00 = glGetError();

         //glDrawArrays(GL_TRIANGLES, 0, 6); // assuming 2 triangles (quad)

         //int iGlError01 = glGetError();

         //glBindVertexArray(0);

         //int iGlErrorA = glGetError();

         //debug() << "gl error";


         //glActiveTexture(GL_TEXTURE0);

         //int iGlError1 = glGetError();

         //::cast < texture > ptexture = pgputexture;

         //GLuint tex = ptexture->m_gluTextureID;

         //glBindTexture(GL_TEXTURE_2D, tex);

         //int iGlError2 = glGetError();

         //::cast < ::gpu_opengl::shader > pshaderOnEndDraw = m_pshaderCopyTextureOnEndDraw;

         //pshaderOnEndDraw->_set_int("uTexture", 0);

         //if (!m_VAOFullScreenQuad)
         //{

         //   m_VAOFullScreenQuad = createFullscreenQuad(m_VBOFullScreenQuad);

         //}

         //glBindVertexArray(m_VAOFullScreenQuad);

         //int iGlError00 = glGetError();

         //glDrawArrays(GL_TRIANGLES, 0, 6); // assuming 2 triangles (quad)

         //int iGlError01 = glGetError();

         //glBindVertexArray(0);

         //int iGlErrorA = glGetError();

         //glBindTexture(GL_TEXTURE_2D, 0);

         //int iGlErrorB = glGetError();

         //debug() << "gl error";

         m_pshaderCopyTextureOnEndDraw->unbind();


      }


      ::cast < device > pdevice = m_pgpurenderer->m_pgpucontext->m_pgpudevice;

      pdevice->_swap_buffers();


   }

} // namespace gpu_opengl


