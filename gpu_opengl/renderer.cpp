#include "framework.h"
#include "approach.h"
#include "command_buffer.h"
#include "context.h"
#include "device.h"
#include "gpu_opengl/context.h"
#include "gpu_opengl/cpu_buffer.h"
#include "frame.h"
#include "frame_buffer.h"
#include "lock.h"
#include "offscreen_render_target.h"
#include "renderer.h"
#include "swap_chain.h"
#include "texture.h"
#include "bred/gpu/graphics.h"
#include "aura/graphics/image/target.h"
#include "aura/platform/application.h"
#include "bred/gpu/context_lock.h"
#include "bred/gpu/layer.h"
#include "bred/gpu/render_state.h"
#include "bred/user/user/graphics3d.h"
#include "aura/windowing/window.h"
#include <glad/glad.h>



const char* blend_vert = R"(
#version 330 core
layout(location = 0) in vec2 inPos;
layout(location = 1) in vec2 inUV;
out vec2 texCoord;
void main() {
   texCoord = inUV;
   gl_Position = vec4(inPos, 0.0, 1.0);
}
)";

const char* blend_frag = R"(
#version 330 core
in vec2 texCoord;
out vec4 fragColor;
uniform sampler2D uTexture;
void main() {
   fragColor = texture(uTexture, texCoord);
}
)";


namespace gpu_opengl
{

   //void vertex2f(const ::double_polygon& a, float fZ);


   renderer::renderer()
   {
      m_vaoQuadBlend = 0;
      m_vboQuadBlend = 0;
      //glEnable(GL_DEPTH_TEST);


      //glDepthFunc(GL_LESS);
   }

   renderer::~renderer()
   {
   }


   //int renderer::width()
   //{

   //   //auto rectangle = m_pgpucontext->m_pimpact->host_rectangle();

   //   //auto sizeHost = m_pgpucontext->m_pimpact->top_level()->raw_rectangle().size();

   //   //auto rectangleW = rectangle.width();

   //   //return rectangleW;

   //   return m_pgpucontext->width();


   //}


   //int renderer::height()
   //{

   //   //auto rectangle = m_pgpucontext->m_pimpact->host_rectangle();

   //   //auto sizeHost = m_pgpucontext->m_pimpact->top_level()->raw_rectangle().size();

   //   //auto rectangleH = rectangle.height();

   //   //return rectangleH;

   //   return m_pgpucontext->height();

   //}


   void renderer::on_context_resize()
   {

      //::gpu::renderer::set_placement(rectanglePlacement);

      ::cast < context > pgpucontext = m_pgpucontext;

      if (pgpucontext)
      {

         pgpucontext->update_framebuffer(pgpucontext->rectangle().size());

      }

   }


   ::pointer < ::gpu::frame > renderer::beginFrame()
   {

      //if (m_pgpucontext != m_pgpucontext->m_pgpudevice->current_context())
      //{

      //   throw ::exception(error_wrong_state);

      //}

      assert(!isFrameStarted && "Can't call beginFrame while already in progress");

      isFrameStarted = true;

      ::cast < context > pgpucontext = m_pgpucontext;

      auto etypeContext = pgpucontext->m_etype;

      auto eoutput = pgpucontext->m_eoutput;

      auto r = pgpucontext->rectangle();

      int left;

      int top;

      int width;

      int height;

      if (eoutput == ::gpu::e_output_cpu_buffer)
      {

         left = 0;

         top = 0;

         width = r.width();

         height = r.height();

         //glViewport(left, top, width, height);

         //m_pgpucontext->clear(::color::transparent);

      }
      else if (eoutput == ::gpu::e_output_swap_chain)
      {

         auto sizeHost = pgpucontext->m_sizeHost;


         left = r.left();

         top = sizeHost.cy() - r.height() - r.top();

         width = r.width();

         height = r.height();

      }
      else
      {

         left = 0;

         top = 0;

         width = r.width();

         height = r.height();

      }

      defer_update_renderer();

      if (!m_pgpurendertarget->m_pgpuframe)
      {

         __øconstruct(m_pgpurendertarget->m_pgpuframe);/* = __create_new < ::gpu_opengl::frame >()*/;

      }

      if (!m_pgpurendertarget->m_bRenderTargetInit)
      {

         m_pgpurendertarget->init();

      }

      //pgpucontext->_ensure_layer_framebuffer();

      return ::gpu::renderer::beginFrame();

   }


   //}


   void renderer::_on_begin_render(::gpu::frame * pframe)
   {

      ::gpu::context_lock contextlock(m_pgpucontext);

      //m_pgpucontext->m_iTopicTexture = -1;

      auto escene = m_pgpucontext->m_escene;

      auto etype = m_pgpucontext->m_etype;

      auto eoutput = m_pgpucontext->m_eoutput;

      auto r = m_pgpucontext->rectangle();

      int width = r.width();

      int height = r.height();

      ::cast < texture > ptexture = m_pgpurendertarget->current_texture(pframe);

      if (!ptexture->m_gluFbo)
      {

         if (m_pgpucontext->m_escene == ::gpu::e_scene_3d)
         {

            ptexture->create_depth_resources();

         }

         ptexture->create_render_target();

      }

      ptexture->bind_render_target();

      auto pcommandbuffer = getCurrentCommandBuffer2(::gpu::current_frame());

      if (escene == ::gpu::e_scene_2d)
      {

         glDisable(GL_SCISSOR_TEST);
         //glFrontFace(GL_CW);      // Default
         glDisable(GL_CULL_FACE);   // Optional
         GLCheckError("");
         //glCullFace(GL_BACK);      // Cull back-facing

         glEnable(GL_BLEND);
         GLCheckError("");
         glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
         GLCheckError("");
         glBlendEquation(GL_FUNC_ADD); // default, can be omitted if unchanged
         GLCheckError("");
         glDisable(GL_DEPTH_TEST);
         GLCheckError("");
         //glDepthFunc(GL_LEQUAL);

         ///::opengl::resize(size, bYSwap);

         bool bYSwap = true;
         //double d = 200.0 / 72.0;

   //double d = 1.0;
   ////glViewport(0, 0, size.cx() * d, size.cy() * d);

         //if (m_pgpucontext == m_pgpucontext->m_pgpudevice->m_pgpucontextMain)
         //{
            pcommandbuffer->set_viewport(m_pgpucontext->m_rectangle.size());
         //}
         //else
         //{

         //   pcommandbuffer->set_viewport(m_pgpucontext->m_rectangle);
         //}
         //glViewport(0, 0, width, height);


         glDepthMask(GL_TRUE); // Enable writing to depth
         GLCheckError("");
         //if (etype == ::gpu::context::e_type_window)
         //{

         //   glClearColor(0.5f, 0.75f, .95f, 0.5f);

         //}
         //else
         //{
         //   glClearColor(0.95f, 0.75f, 0.5f, 0.5f);

         //}
         glClearColor(0.f, 0.f, 0.f, 0.f);
         GLCheckError("");
         glClearDepth(1.0f);
         GLCheckError("");
         glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
         GLCheckError("");
         glDepthMask(GL_FALSE); // Disable writing to depth
         GLCheckError("");



         GLCheckError("");
         //glMatrixMode(GL_PROJECTION);
         GLCheckError("");
         //glLoadIdentity();
         GLCheckError("");
         ////glOrtho(0, size.cx() * d, size.cy() * d, 0.0f, 000.0f, 1000.0f);
         ////glOrtho(0, size.cx() * d, size.cy() * d, 0.0f, 000.0f, 1000.0f);
         //////glOrtho(0, size.cx() * d, 0.0f, size.cy() * d, 000.0f, 1000.0f);
         ////glOrtho(0, size.cx(), size.cy(), 0.0f, -1000.0f, 1000.0f);
         //glOrtho(0.f, size.cx(), 0.f, -size.cy(), -1.0f, 1.0f);
         if (bYSwap)
         {
            //glOrtho(0.0f, width, height, 0, -1.0f, 1.0f);  // Flip Y
            GLCheckError("");
         }
         else
         {
            //glOrtho(0.0f, width, 0, height, -1.0f, 1.0f);  // Flip Y
            GLCheckError("");
         }
         //glMatrixMode(GL_MODELVIEW);
         GLCheckError("");
         //glLoadIdentity();
         GLCheckError("");

         //glMatrixMode(GL_MODELVIEW);
         //glLoadIdentity();


         //gluOrtho2D(0.f, size.cx(), 0.f, size.cy());
         //glMatrixMode(GL_MODELVIEW);
         //glLoadIdentity();

         // Clear

         //glDisable(GL_DEPTH_TEST);

         // Translate to inside of pixel (otherwise inaccuracies can occur on certain gl implementations)
         //if (OpenGL::accuracyTweak())
         ///glTranslatef(0.5f, 0.5f, 0);
         GLCheckError("");



         // Toggle wireframe mode
         //if (m_pgpucontext->m_pimpact->m_pengine->m_bWireframeMode) {
         //   glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // Enable wireframe mode
         //}
         //else {
         //   glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); // Enable solid mode
         //}


      }
      else if (m_pgpucontext->m_escene == ::gpu::e_scene_3d)
      {
         
         glDisable(GL_SCISSOR_TEST);

         glDepthMask(GL_TRUE); // Enable writing to depth
         glDisable(GL_BLEND);
         GLCheckError("");
         //glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
         //glBlendEquation(GL_FUNC_ADD); // default, can be omitted if unchanged
         glEnable(GL_DEPTH_TEST);
         GLCheckError("");
         glDepthFunc(GL_LESS);
         GLCheckError("");


         glFrontFace(GL_CCW);      // Default CCW
         GLCheckError("");
         //glEnable(GL_CULL_FACE);   // Optional
         glDisable(GL_CULL_FACE); // or make sure front face winding is correct
         GLCheckError("");
         glCullFace(GL_FRONT);
         //glCullFace(GL_BACK);
         GLCheckError("");

         bool bYSwap = true;
         //double d = 200.0 / 72.0;

   //double d = 1.0;
   ////glViewport(0, 0, size.cx() * d, size.cy() * d);
         //glViewport(0, 0, width, height);
         //if (m_pgpucontext == m_pgpucontext->m_pgpudevice->m_pgpucontextMain)
         //{
            pcommandbuffer->set_viewport(m_pgpucontext->m_rectangle.size());
         //}
         //else
         //{

         //   pcommandbuffer->set_viewport(m_pgpucontext->m_rectangle);
         //}
         GLCheckError("");
         //if (etype == ::gpu::context::e_type_window)
         //{

         //   glClearColor(0.5f, 0.75f, .95f, 0.5f);

         //}
         //else
         //{
         //   glClearColor(0.95f, 0.75f, 0.5f, 0.5f);

         //}
         glClearColor(0.f, 0.f, 0.f, 0.f);
         //glClearColor(0.95f * 0.5f, 0.95f * 0.5f, .8f * 0.5f, 0.5f); // light yellow
         GLCheckError("");
         glClearDepth(1.0f);
         GLCheckError("");
         glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
         GLCheckError("");

         GLCheckError("");
         ///glDepthMask(GL_FALSE); // Disable writing to depth
         GLCheckError("");
         //glMatrixMode(GL_PROJECTION);
         GLCheckError("");
         //glLoadIdentity();
         GLCheckError("");
         ////glOrtho(0, size.cx() * d, size.cy() * d, 0.0f, 000.0f, 1000.0f);
         ////glOrtho(0, size.cx() * d, size.cy() * d, 0.0f, 000.0f, 1000.0f);
         //////glOrtho(0, size.cx() * d, 0.0f, size.cy() * d, 000.0f, 1000.0f);
         ////glOrtho(0, size.cx(), size.cy(), 0.0f, -1000.0f, 1000.0f);
         //glOrtho(0.f, size.cx(), 0.f, -size.cy(), -1.0f, 1.0f);
         if (bYSwap)
         {
            //glOrtho(0.0f, width, height, 0, -1.0f, 1.0f);  // Flip Y
            GLCheckError("");
         }
         else
         {
            //glOrtho(0.0f, width, 0, height, -1.0f, 1.0f);  // Flip Y
            GLCheckError("");
         }
         ///glMatrixMode(GL_MODELVIEW);
         GLCheckError("");
         //glLoadIdentity();
         GLCheckError("");


      }
      else
      {

         debug() << "unknown scene type";

      }



   }


   void renderer::on_begin_render(::gpu::frame* pframe)
   {

      ::gpu::renderer::on_begin_render(pframe);

   }


   //int renderer::get_frame_count()
   //{

   //   return ::gpu::renderer::get_frame_count();

   //}


   //void renderer::Clear() const
   //{

   //   // Clear the screen 
   //   GLCheckError("");
   //   glClearColor(0.678f, 0.847f, 0.902f, 1.0f);
   //   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   //   GLCheckError("");
   //}

   //// sky_box
   //void renderer::DrawSkybox(const mesh* pskyboxMesh, ::gpu::shader* pshader) const
   //{
   //   GLCheckError("");
   //   // Disable depth writing for the skybox
   //   glDepthFunc(GL_LEQUAL);
   //   glEnable(GL_BLEND);
   //   glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
   //   pshader->bind();

   //   pskyboxMesh->Bind();
   //   glDrawElements(GL_TRIANGLES, pskyboxMesh->GetIndexCount(), GL_UNSIGNED_INT, nullptr);
   //   pskyboxMesh->Unbind();

   //   glDepthFunc(GL_LESS);
   //   pshader->unbind();
   //   GLCheckError("");
   //}


   //void renderer::DrawInstanced(const ::array<mesh*>& meshes, ::gpu::shader* pshader, unsigned int instanceCount) const
   //{

   //   GLCheckError("");

   //   for (const mesh* mesh : meshes) {
   //      mesh->Bind();
   //      glDrawElementsInstanced(GL_TRIANGLES, mesh->GetIndexCount(), GL_UNSIGNED_INT, (void*)(mesh->GetIndexOffset() * sizeof(unsigned int)), instanceCount);
   //      mesh->Unbind();
   //   }

   //   GLCheckError("");
   //}


   //void renderer::DrawModel(const ::array<mesh*>& mehses, ::gpu::shader* pshader)
   //{

   //}


   void renderer::endFrame()
   {

      ::gpu::context_lock contextlock(m_pgpucontext);

      //if (m_pgpucontext != m_pgpucontext->m_pgpudevice->current_context())
      //{

      //   throw ::exception(error_wrong_state);

      //}



      //glDisable(GL_DEPTH_TEST);


      //}

//            glDepthFunc(GL_LESS);

      //glPopAttrib();
      //glPopMatrix();


      //glClearColor(0.5f*0.5f, 0.75f * 0.5f, 0.95f * 0.5f, 0.5f); // RGBA
      //glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
      
      
      //glDisable(GL_DEPTH_TEST);
      //glDepthMask(GL_FALSE);
      //glEnable(GL_BLEND);
      //glDisable(GL_SCISSOR_TEST);
      glFlush();
      GLCheckError("");

      //GLint drawFboId = 0, readFboId = 0;

      //glGetIntegerv(GL_DRAW_FRAMEBUFFER_BINDING, &drawFboId);
      //glGetIntegerv(GL_READ_FRAMEBUFFER_BINDING, &readFboId);

      //int iGlError1 = glGetError();

      //int iGlError2 = -1;

      //if (drawFboId != 0)
      //{

      //   glBindFramebuffer(GL_FRAMEBUFFER, 0);

      //   iGlError2 = glGetError();

      //}

      auto eoutput = m_pgpucontext->m_eoutput;

      //if (eoutput == ::gpu::e_output_swap_chain)
      //{

      //   _swap();

      //}
      //else 
         if (eoutput == ::gpu::e_output_cpu_buffer)
      {

         do_sampling_to_cpu();

      }

      //if (m_pgpucontextUpper)
      //{

      //   m_pgpucontext->release_current();

      //   m_pgpucontextUpper->make_current();

      //}

      m_prenderstate->on_happening(::gpu::e_happening_end_frame);

      isFrameStarted = false;

   }


   //void renderer::defer_update_renderer()
   //{

   //   ::gpu::renderer::defer_update_renderer();

   //   //auto rectangleContext = m_pgpucontext->rectangle();

   //   //auto sizeContext = rectangleContext.size();

   //   //auto etypeContext = m_pgpucontext->m_etype;

   //   //if (m_sizeRenderer == sizeContext)
   //   //{

   //   //   if (m_pgpucontext->is_current_task())
   //   //   {

   //   //      if (!m_pgpurendertarget->m_bInit)
   //   //      {

   //   //         m_pgpurendertarget->init();

   //   //      }

   //   //   }

   //   //   return;

   //   //}

   //   //auto size = m_pgpucontext->rectangle().size();

   //   //m_sizeRenderer = size;

   //   //auto eoutput = m_pgpucontext->m_eoutput;

   //   //auto previous = m_pgpurendertarget;

   //   //if (eoutput == ::gpu::e_output_cpu_buffer
   //   //   || eoutput == ::gpu::e_output_gpu_buffer)
   //   //{

   //   //   auto poffscreenrendertargetview = __allocate offscreen_render_target();
   //   //   //#ifdef WINDOWS_DESKTOP
   //   //   //         poffscreenrendertargetview->m_formatImage = VK_FORMAT_B8G8R8A8_UNORM;
   //   //   //#else
   //   //   //         poffscreenrendertargetview->m_formatImage = VK_FORMAT_R8G8B8A8_UNORM;
   //   //   //#endif
   //   //   m_pgpurendertarget = poffscreenrendertargetview;
   //   //   //         //m_prendererResolve.release();
   //   //   //
   //   //}
   //   //else if (eoutput == ::gpu::e_output_swap_chain)
   //   //{
   //   //   auto poffscreenrendertargetview = __allocate offscreen_render_target();
   //   //   //#ifdef WINDOWS_DESKTOP
   //   //   //         poffscreenrendertargetview->m_formatImage = VK_FORMAT_B8G8R8A8_UNORM;
   //   //   //#else
   //   //   //         poffscreenrendertargetview->m_formatImage = VK_FORMAT_R8G8B8A8_UNORM;
   //   //   //#endif
   //   //   m_pgpurendertarget = poffscreenrendertargetview;

   //   //   //m_prendertargetview = __allocate swap_chain_render_target(this, size, m_prendertargetview);
   //   //   //m_prendererResolve.release();

   //   //}
   //   ////      else if (eoutput == ::gpu::e_output_gpu_buffer)
   //   ////      {
   //   ////
   //   ////         auto poffscreenrendertargetview = __allocate offscreen_render_target(this, m_extentRenderer, m_prendertargetview);
   //   ////#ifdef WINDOWS_DESKTOP
   //   ////         poffscreenrendertargetview->m_formatImage = VK_FORMAT_B8G8R8A8_UNORM;
   //   ////#else
   //   ////         poffscreenrendertargetview->m_formatImage = VK_FORMAT_R8G8B8A8_UNORM;
   //   ////#endif
   //   ////         m_prendertargetview = poffscreenrendertargetview;
   //   ////         //m_prendererResolve;
   //   ////
   //   ////      }
   //   ////      else if (eoutput == ::gpu::e_output_color_and_alpha_accumulation_buffers)
   //   ////      {
   //   ////
   //   ////         auto paccumulationrendertargetview = __allocate accumulation_render_target(this, m_extentRenderer, m_prendertargetview);
   //   ////         paccumulationrendertargetview->m_formatImage = VK_FORMAT_R32G32B32A32_SFLOAT;
   //   ////         paccumulationrendertargetview->m_formatAlphaAccumulation = VK_FORMAT_R32_SFLOAT;
   //   ////         m_prendertargetview = paccumulationrendertargetview;
   //   ////
   //   ////         //__construct_new(m_prendererResolve);
   //   ////
   //   ////         //m_prendererResolve->initialize_renderer(m_pgpucontext, ::gpu::e_output_resolve_color_and_alpha_accumulation_buffers);
   //   ////
   //   ////         //m_prendererResolve->set_placement(m_pgpucontext->rectangle);
   //   ////         //
   //   ////         //            auto poffscreenrendertargetview = __allocate offscreen_render_target(m_pgpucontext, m_extentRenderer, m_prendertargetviewResolve);
   //   ////         //#ifdef WINDOWS_DESKTOP
   //   ////         //            poffscreenrendertargetview->m_formatImage = VK_FORMAT_B8G8R8A8_UNORM;
   //   ////         //#else
   //   ////         //            poffscreenrendertargetview->m_formatImage = VK_FORMAT_R8G8B8A8_UNORM;
   //   ////         //#endif
   //   ////         //            m_prendertargetviewResolve = poffscreenrendertargetview;
   //   ////      }
   //   ////      else if (eoutput == ::gpu::e_output_resolve_color_and_alpha_accumulation_buffers)
   //   ////      {
   //   ////
   //   ////         auto poffscreenrendertargetview = __allocate offscreen_render_target(this, m_extentRenderer, m_prendertargetview);
   //   ////#ifdef WINDOWS_DESKTOP
   //   ////         poffscreenrendertargetview->m_formatImage = VK_FORMAT_B8G8R8A8_UNORM;
   //   ////#else
   //   ////         poffscreenrendertargetview->m_formatImage = VK_FORMAT_R8G8B8A8_UNORM;
   //   ////#endif
   //   ////         m_prendertargetview = poffscreenrendertargetview;
   //   ////
   //   ////      }
   //   ////      else
   //   ////      {
   //   ////
   //   ////         throw ::exception(error_wrong_state, "Unexpected gpu e_output");
   //   ////
   //   ////      }
   //   ////
   //   //if (!m_pgpurendertarget->has_ok_flag() && m_sizeRenderer.area() > 0)
   //   //{

   //   //   m_pgpurendertarget->initialize_render_target(this, size, previous);

   //   //   if (m_pgpucontext->is_current_task())
   //   //   {

   //   //      m_pgpurendertarget->init();

   //   //   }

   //   //}

   //}


   //::pointer < ::gpu::render_target > renderer::allocate_offscreen_render_target()
   //{

   //   auto poffscreenrendertarget = __allocate offscreen_render_target();

   //   return poffscreenrendertarget;

   //}


   //void renderer::on_defer_update_renderer_allocate_render_target(::gpu::enum_output eoutput, const ::int_size& size, ::gpu::render_target* previous)
   //{

   //   if (eoutput == ::gpu::e_output_cpu_buffer
   //      || eoutput == ::gpu::e_output_gpu_buffer)
   //   {

   //      auto poffscreenrendertarget = __allocate offscreen_render_target();

   //      m_pgpurendertarget = poffscreenrendertarget;

   //   }
   //   else if (eoutput == ::gpu::e_output_swap_chain)
   //   {

   //      auto pswapchain = m_pgpucontext->m_pgpudevice->get_swap_chain();

   //      m_pgpurendertarget = pswapchain;

   //   }

   //   //return poffscreenrendertarget;

   //}


   void renderer::do_sampling_to_cpu()
   {


      ::gpu::context_lock contextlock(m_pgpucontext);

      ::cast<context>pgpucontext = m_pgpucontext;

      if (pgpucontext)
      {

         auto pcpubuffer = pgpucontext->m_pcpubuffer;

         if (pcpubuffer)
         {

            pcpubuffer->set_size(pgpucontext->m_rectangle.size());

            pcpubuffer->gpu_read();

         }

      }

      //      //m_pixmap.map();
      //
      //      auto cx = m_pixmap.m_size.cx();
      //
      //      auto cy = m_pixmap.m_size.cy();
      //
      //      //auto sizeNeeded = cx * cy * 4;
      //
      //      //m_pixmap.create(m_memory, sizeNeeded);
      //
      //      auto data = m_memory.data();
      //
      //#if defined(__APPLE__) || defined(__ANDROID__)
      //
      //      if (data != nullptr)
      //      {
      //         glReadBuffer(GL_FRONT);
      //
      //         //if(0)
      //         {
      //            glReadPixels(
      //               0, 0,
      //               cx, cy,
      //               GL_RGBA,
      //               GL_UNSIGNED_BYTE,
      //               data);
      //
      //         }
      //
      //      }
      //
      //      //m_pixmap.mult_alpha();
      //      information() << "after glReadPixels cx,cy : " << cx << ", " << cy;
      //
      //      //::memory_set(m_pixmap.m_pimage32Raw, 127, cx * cy * 4);
      //
      //#elif defined(LINUX) || defined(__BSD__)
      //
      //      glReadBuffer(GL_FRONT);
      //
      //
      //      glReadPixels(
      //         0, 0,
      //         cx, cy,
      //         GL_BGRA,
      //         GL_UNSIGNED_BYTE,
      //         m_pixmap.m_pimage32Raw);
      //
      //      //m_pixmap.mult_alpha();
      //
      //#else
      //
      //
      //      glReadBuffer(GL_FRONT);
      //
      //      //if (m_pgpucontext->is_mesa())
      //      if (!glReadnPixels)
      //      {
      //
      //         glReadPixels(
      //            0, 0,
      //            cx, cy,
      //            GL_BGRA,
      //            GL_UNSIGNED_BYTE,
      //            m_pixmap.m_pimage32Raw);
      //
      //      }
      //      else
      //      {
      //
      //         glReadnPixels(
      //            0, 0,
      //            cx, cy,
      //            GL_BGRA,
      //            GL_UNSIGNED_BYTE,
      //            cx * cy * 4,
      //            data);
      //
      //      }
      //
      //      int iError = glGetError();
      //
      //      if (iError != 0)
      //      {
      //
      //         printf("glReadnPixels error");
      //
      //      }
      //
      //      //::memory_set(m_pixmap.m_pimage32Raw, 127, cx * cy * 4);
      //
      //#endif
      //
      //      {
      //
      //         auto dst = (unsigned char*)data;
      //         auto size = cx * cy;
      //
      //         while (size > 0)
      //         {
      //            dst[0] = byte_clip(((int)dst[0] * (int)dst[3]) / 255);
      //            dst[1] = byte_clip(((int)dst[1] * (int)dst[3]) / 255);
      //            dst[2] = byte_clip(((int)dst[2] * (int)dst[3]) / 255);
      //            dst += 4;
      //            size--;
      //         }
      //
      //      }
      //
   }


   //void renderer::_swap()
   //{

   //   m_pgpucontext->swap_buffers();

   //}
//   GLuint createFullscreenQuad(GLuint& quadVBO) {
//      // Vertex data: (x, y, u, v)
//#if 1
//      float quadVertices[] = {
//         //  Position   TexCoords
//         -1.0f,  1.0f,  0.0f, 1.0f, // Top-left
//         -1.0f, -1.0f,  0.0f, 0.0f, // Bottom-left
//          1.0f, -1.0f,  1.0f, 0.0f, // Bottom-right
//
//         -1.0f,  1.0f,  0.0f, 1.0f, // Top-left
//          1.0f, -1.0f,  1.0f, 0.0f, // Bottom-right
//          1.0f,  1.0f,  1.0f, 1.0f  // Top-right
//      };
//#else
//      float quadVertices[] = {
//         //  Position   TexCoords
//         0.0f,  1.0f,  0.0f, 1.0f, // Top-left
//         0.0f, 0.0f,  0.0f, 0.0f, // Bottom-left
//          1.0f, 0.0f,  1.0f, 0.0f, // Bottom-right
//
//         0.0f,  1.0f,  0.0f, 1.0f, // Top-left
//          1.0f, 0.0f,  1.0f, 0.0f, // Bottom-right
//          1.0f,  1.0f,  1.0f, 1.0f  // Top-right
//      };
//#endif
//      GLuint quadVAO = 0;
//
//      glGenVertexArrays(1, &quadVAO);
//      glGenBuffers(1, &quadVBO);
//
//      glBindVertexArray(quadVAO);
//      glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
//      glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), quadVertices, GL_STATIC_DRAW);
//
//      // Position attribute (location = 0)
//      glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
//      glEnableVertexAttribArray(0);
//
//      // Texture Coord attribute (location = 1)
//      glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
//      glEnableVertexAttribArray(1);
//
//      // Unbind for safety
//      glBindVertexArray(0);
//      return quadVAO;
//
//   }


//   void renderer::endDraw(::draw2d_gpu::graphics* pgraphics, ::user::interaction* puserinteraction)
//   {
//
//      ::cast < ::gpu_opengl::renderer > prenderer = this;
//
//      ::cast < ::gpu_opengl::swap_chain > pswapchain = m_pgpucontext->m_pgpudevice->get_swap_chain();
//
//      pswapchain->endDraw(pgraphics, puserinteraction, this);
//
//      //auto rectangle = prenderer->m_pgpucontext->rectangle();
//
//      //m_pgpucontext->set_placement(rectangle);
//
//      //VkImage image = prenderer->m_pvkcrenderpass->m_images[prenderer->get_frame_index()];
//
//      //on_new_frame();
//
//      //if (1)
//      //{
//      //   //auto cmdBuffer = m_pgpucontext->beginSingleTimeCommands();
//
//      //   //VkImageMemoryBarrier barrier = {
//      //   //    .sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER,
//      //   //    .srcAccessMask = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT,
//      //   //    .dstAccessMask = VK_ACCESS_SHADER_READ_BIT,
//      //   //    .oldLayout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL,
//      //   //    .newLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL,
//      //   //    .srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED,
//      //   //    .dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED,
//      //   //    .image = image,
//      //   //    .subresourceRange = {
//      //   //        .aspectMask = VK_IMAGE_ASPECT_COLOR_BIT,
//      //   //        .baseMipLevel = 0,
//      //   //        .levelCount = 1,
//      //   //        .baseArrayLayer = 0,
//      //   //        .layerCount = 1
//      //   //    },
//      //   //};
//
//      //   //vkCmdPipelineBarrier(
//      //   //   cmdBuffer,
//      //   //   VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT,
//      //   //   VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT,
//      //   //   0,
//      //   //   0, NULL,
//      //   //   0, NULL,
//      //   //   1, &barrier
//      //   //);
//
//      //   //VkSubmitInfo submitInfo = {};
//      //   //submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
//
//      //   //VkSemaphore waitSemaphores[] = { prendererSrc->m_pvkcrenderpass->renderFinishedSemaphores[prendererSrc->m_pvkcrenderpass->currentFrame] };
//      //   //VkPipelineStageFlags waitStages[] = { VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT };
//      //   //submitInfo.waitSemaphoreCount = 1;
//      //   //submitInfo.pWaitSemaphores = waitSemaphores;
//      //   //submitInfo.pWaitDstStageMask = waitStages;
//
//      //   //submitInfo.commandBufferCount = 1;
//      //   //submitInfo.pCommandBuffers = &cmdBuffer;
//
//      //   //m_pgpucontext->endSingleTimeCommands(cmdBuffer, 1, &submitInfo);
//      //   auto cmdBuffer = m_pgpucontext->beginSingleTimeCommands();
//
//
//      //   insertImageMemoryBarrier(cmdBuffer,
//      //      image,
//      //      0,
//      //      VK_ACCESS_TRANSFER_WRITE_BIT,
//      //      VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL,
//      //      VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL,
//      //      VK_PIPELINE_STAGE_TRANSFER_BIT,
//      //      VK_PIPELINE_STAGE_TRANSFER_BIT,
//      //      VkImageSubresourceRange{ VK_IMAGE_ASPECT_COLOR_BIT, 0, 1, 0, 1 });
//
//
//
//      //   VkSubmitInfo submitInfo{};
//      //   submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
//      //   submitInfo.commandBufferCount = 1;
//      //   submitInfo.pCommandBuffers = &cmdBuffer;
//      //   ::array<VkSemaphore> waitSemaphores;
//      //   ::array<VkPipelineStageFlags> waitStages;
//      //   waitStages.add(VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT);
//      //   waitSemaphores.add(prenderer->m_pvkcrenderpass->renderFinishedSemaphores[prenderer->get_frame_index()]);
//      //   submitInfo.waitSemaphoreCount = waitSemaphores.size();
//      //   submitInfo.pWaitSemaphores = waitSemaphores.data();
//      //   submitInfo.pWaitDstStageMask = waitStages.data();
//      //   m_pgpucontext->endSingleTimeCommands(cmdBuffer, 1, &submitInfo);
//
//      //   //m_prendererResolve->m_pvkcrenderpass->m_semaphoreaWaitToSubmit.add(
//      //   //   m_pvkcrenderpass->renderFinishedSemaphores[iPassCurrentFrame]
//      //   //);
//
//
//      //}
//
////      m_pgpucontext->send([this, prenderer]()
////         {
////
////            if (auto pframe = beginFrame())
////            {
////
////               //m_pvkcrenderpass->m_semaphoreaSignalOnSubmit.add(prendererSrc->m_pvkcrenderpass->imageAvailableSemaphores[prendererSrc->get_frame_index()]);
////
////
////               //on_begin_frame();
////               // render
////               on_begin_render(pframe);
////
////               m_pgpucontext->clear(::argb(127, 140 / 2, 220 / 2, 240 / 2));
////               //m_pgpucontext->clear(::color::transparent);
////
////
////               if (1)
////               {
////
////
////                  //if (m_pimpact->global_ubo_block().size() > 0)
////                  //{
////
////                    // update_global_ubo(m_pgpucontext);
////
////                  //}
////
////                  //m_pscene->on_render(m_pgpucontext);
////
////                  //_blend_image(image, m_rectangle);
////
////         //         glDisable(GL_BLEND);
////         //         //glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
////
////
////                  if (!m_pshaderCopyTextureOnEndDraw)
////                  {
////
////                     auto pvertexshader = R"vert(#version 330 core
////layout(location = 0) in vec2 aPos;
////layout(location = 1) in vec2 aTexCoord;
////
////out vec2 TexCoord;
////
////void main() {
////   gl_Position = vec4(aPos.xy, 0.0, 1.0);
////   TexCoord = aTexCoord;
////}
////)vert";
////
////
////                     auto pfragmentshader = R"frag(#version 330 core
////in vec2 TexCoord;
////out vec4 FragColor;
////
////uniform sampler2D uTexture;
////
////void main() {
////   FragColor = texture(uTexture, TexCoord);
////}
////)frag";
////
////                     m_pshaderCopyTextureOnEndDraw = __create_new < ::gpu_opengl::shader >();
////
////                     m_pshaderCopyTextureOnEndDraw->initialize_shader_with_block(
////                        this,
////                        pvertexshader, pfragmentshader);
////
////
////                  }
////
////                  m_pshaderCopyTextureOnEndDraw->bind();
////
////                  if (1)
////                  {
////
////                     glActiveTexture(GL_TEXTURE0);
////
////                     int iGlError1 = glGetError();
////
////                     ::cast < context > pcontext = prenderer->m_pgpucontext;
////
////                     GLuint tex = pcontext->m_pframebuffer->m_tex;
////
////                     glBindTexture(GL_TEXTURE_2D, tex);
////
////                     int iGlError2 = glGetError();
////
////                     ::cast < ::gpu_opengl::shader > pshaderOnEndDraw = m_pshaderCopyTextureOnEndDraw;
////
////                     pshaderOnEndDraw->_set_int("uTexture", 0);
////
////                     if (!m_VAOFullScreenQuad)
////                     {
////
////                        m_VAOFullScreenQuad = createFullscreenQuad(m_VBOFullScreenQuad);
////
////                     }
////
////                     glBindVertexArray(m_VAOFullScreenQuad);
////
////                     int iGlError00 = glGetError();
////
////                     glDrawArrays(GL_TRIANGLES, 0, 6); // assuming 2 triangles (quad)
////
////                     int iGlError01 = glGetError();
////
////                     glBindVertexArray(0);
////
////                     int iGlErrorA = glGetError();
////
////                     glBindTexture(GL_TEXTURE_2D, 0);
////
////                     int iGlErrorB = glGetError();
////
////                     debug() << "gl error";
////
////                  }
////
////                  m_pshaderCopyTextureOnEndDraw->unbind();
////
////               }
////
////               on_end_render(pframe);
////
////               endFrame();
////
////
////            }
////
////         });
//
//
//   }


   //void renderer::on_start_layer(::gpu::layer* player)
   //{

   //   _ensure_renderer_framebuffer();

   //   //if (player->texture())
   //   //{

   //   //   if (!m_iFrameBufferRenderer)
   //   //   {

   //   //      GLuint fboSrc, fboDst;
   //   //      glGenFramebuffers(1, &m_iFrameBufferRenderer);
   //   //      GLCheckError("");

   //   //   }

   //   //   glBindFramebuffer(GL_DRAW_FRAMEBUFFER, m_iFrameBufferRenderer);
   //   //   GLCheckError("");

   //      ::cast < texture > ptexture = player->m_pgpurenderer->m_pgpurendertarget->current_texture();
   //      ::cast < context > pcontext = player->m_pgpurenderer->m_pgpucontext;
   //   //   int textureID = ptexture->m_gluTextureID;

   //   //   glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER, GL_COLOR_ATTACHMENT0,
   //   //      GL_TEXTURE_2D, textureID, 0);
   //   //   GLCheckError("");

   //      auto escene = pcontext->m_escene;

   //   //   auto etype = m_pgpucontext->m_etype;

   //   //   auto eoutput = m_pgpucontext->m_eoutput;

   //      auto r = pcontext->rectangle();

   //      int width = r.width();

   //      int height = r.height();

   //   //   //clear(player->m_pgputextureSource);

   //   //   //_on_begin_render();


   //   //}

   //}
   
   
   void renderer::blend(::gpu::renderer* prendererSource)
   {

      ::gpu::context_lock contextlock(m_pgpucontext);
   
      auto rectangleHost = m_pgpucontext->rectangle();

      int wHost = rectangleHost.width();

      int hHost = rectangleHost.height();

      //glPopAttrib();
      //glPopMatrix();

      glViewport(0, 0, wHost, hHost);

      glDisable(GL_DEPTH_TEST);
      glDepthMask(GL_FALSE);

      glEnable(GL_BLEND);



      //glMatrixMode(GL_PROJECTION);
      //glLoadIdentity();
      ////glOrtho(0, size.cx() * d, size.cy() * d, 0.0f, 000.0f, 1000.0f);
      ////glOrtho(0, size.cx() * d, size.cy() * d, 0.0f, 000.0f, 1000.0f);
      //////glOrtho(0, size.cx() * d, 0.0f, size.cy() * d, 000.0f, 1000.0f);
      ////glOrtho(0, size.cx(), size.cy(), 0.0f, -1000.0f, 1000.0f);
      //glOrtho(0.f, size.cx(), 0.f, -size.cy(), -1.0f, 1.0f);
      auto bYSwap = true;
      if (bYSwap)
      {
         //glOrtho(0.0f, wHost, hHost, 0, -1.0f, 1.0f);  // Flip Y
      }
      else
      {
         //glOrtho(0.0f, wHost, 0, hHost, -1.0f, 1.0f);  // Flip Y
      }
      //glMatrixMode(GL_MODELVIEW);
      //glLoadIdentity();

      if (!m_pshaderBlend)
      {

         __øconstruct(m_pshaderBlend);

         const char* quad_vertex_shader = "#version 330 core\n"
            "layout(location = 0) in vec2 pos;\n"
            "layout(location = 1) in vec2 texCoord;\n"
            "out vec2 uv;\n"
            "void main() {\n"
            "    uv = texCoord;\n"
            "    gl_Position = vec4(pos, 0.0, 1.0);\n"
            "}";

         const char* blend_fragment_shader = "#version 330 core\n"
            "in vec2 uv;\n"
            "uniform sampler2D tex;\n"
            "out vec4 FragColor;\n"
            "void main() {\n"
            "    FragColor = texture(tex, uv);\n"
            "}";


         m_pshaderBlend->initialize_shader_with_block(
            this,
            quad_vertex_shader,
            blend_fragment_shader);

         glGenVertexArrays(1, &m_vaoQuadBlend);
         glGenBuffers(1, &m_vboQuadBlend);
         glBindVertexArray(m_vaoQuadBlend);
         glBindBuffer(GL_ARRAY_BUFFER, m_vboQuadBlend);
         glBufferData(GL_ARRAY_BUFFER, 4 * 4 * sizeof(float), NULL, GL_DYNAMIC_DRAW);
         glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
         glEnableVertexAttribArray(0);
         glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
         glEnableVertexAttribArray(1);

      }

      float WIDTH = (float)wHost;
      float HEIGHT = (float)hHost;

      auto rectangle = prendererSource->m_pgpucontext->rectangle();

      float w = (float)rectangle.width();
      float h = (float)rectangle.height();
      float x = (float)rectangle.left();
      float y = (float)(hHost - rectangle.bottom());

      // 3. Composite scene texture at 1:1 into UI FBO at position (200, 150)
      //float x = 200.0f, y = 150.0f, w = SCENE_W, h = SCENE_H;

      float l, r, b, t;

      if (1)
      {
         l = (x / WIDTH) * 2.0f - 1.0f;
         r = ((x + w) / WIDTH) * 2.0f - 1.0f;
         b = (y / HEIGHT) * 2.0f - 1.0f;
         t = ((y + h) / HEIGHT) * 2.0f - 1.0f;
      }
      else
      {
         l = (float)rectangle.left();
         r = (float)rectangle.right();
         b = (float)rectangle.bottom();
         t = (float)rectangle.top();
      }
      float quad[] = {
             l, b,  0.0f, 0.0f,
             r, b,  1.0f, 0.0f,
             l, t,  0.0f, 1.0f,
             r, t,  1.0f, 1.0f
      };

      if (1)
      {

         ::cast < ::gpu_opengl::context > pcontextSource = prendererSource->m_pgpucontext;

         //glUseProgram(blendShader);
         m_pshaderBlend->bind();
         glActiveTexture(GL_TEXTURE0);
         auto texture = pcontextSource->m_pframebuffer->m_tex;
         glBindTexture(GL_TEXTURE_2D, texture);
         //glUniform1i(glGetUniformLocation(blendShader, "tex"), 0);
         ::cast < gpu_opengl::shader > pshader = m_pshaderBlend;
         pshader->_set_int("tex", 0);

         glBindBuffer(GL_ARRAY_BUFFER, m_vboQuadBlend);
         glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(quad), quad);
         glBindVertexArray(m_vaoQuadBlend);
         glEnable(GL_BLEND);
         glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
         glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
         m_pshaderBlend->unbind();
         //}

      }

   }


   void renderer::clear(::gpu::texture* ptextureParam)
   {

      ::gpu::context_lock contextlock(m_pgpucontext);

      ::cast < texture > ptexture = ptextureParam;


      GLuint framebuffer;
      glGenFramebuffers(1, &framebuffer);
      glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);

      // Bind the destination texture (textures[textureSrc]) as the framebuffer color attachment
      glFramebufferTexture2D(
         GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D,
         ptexture->m_gluTextureID,
         0);

      if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
         printf("Framebuffer not complete!\n");
         glDeleteFramebuffers(1, &framebuffer);
         return;
      }



      // Set viewport size (match texture dimensions)
      glViewport(0, 0, ptexture->size().cx(), ptexture->size().cy());

      // Clear destination texture before blending
      glClearColor(0, 0, 0, 0); // Transparent
      glClear(GL_COLOR_BUFFER_BIT);

      glBindFramebuffer(GL_FRAMEBUFFER, 0); // Return to default framebuffer

      glDeleteFramebuffers(1, &framebuffer);

   }


   void renderer::__blend(::gpu::texture* ptextureTarget, ::gpu::texture* ptextureSource)
   {

      ::gpu::context_lock contextlock(m_pgpucontext);

      ::cast < ::gpu_opengl::texture > ptextureDst = ptextureTarget;
      ::cast < ::gpu_opengl::texture > ptextureSrc = ptextureSource;


      if (!m_pshaderBlend2)
      {

         __construct_new(m_pshaderBlend2);

         m_pshaderBlend2->initialize_shader_with_block(
            this,
            blend_vert,
            blend_frag);

      }

      float quadVertices[] = {
         // pos      // uv
         -1.0f, -1.0f,  0.0f, 0.0f,
          1.0f, -1.0f,  1.0f, 0.0f,
         -1.0f,  1.0f,  0.0f, 1.0f,
          1.0f,  1.0f,  1.0f, 1.0f,
      };


      auto rectangleTarget = ptextureSource->m_rectangleTarget;

      int iTopH = ptextureDst->size().cy();
      int rectangleBottom = rectangleTarget.bottom();
      int iY = iTopH - rectangleBottom;

      glViewport(
         rectangleTarget.left(),
          iY,
         rectangleTarget.width(),
         rectangleTarget.height());

      // Optional: scissor if you want to limit drawing region
      glEnable(GL_SCISSOR_TEST);
      glScissor(
         rectangleTarget.left(),
         iY,
         rectangleTarget.width(),
         rectangleTarget.height()
      );

      glDepthMask(FALSE);
      glDisable(GL_DEPTH_TEST);

      glEnable(GL_BLEND);
      glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
      glBlendEquation(GL_FUNC_ADD); // default, can be omitted if unchanged

      // VAO/VBO setup
      GLuint& vao = m_vaoQuadBlend2;
      GLuint& vbo = m_vboQuadBlend2;

      if (!vao)
      {

         glGenVertexArrays(1, &vao);
         glGenBuffers(1, &vbo);
         glBindVertexArray(vao);
         glBindBuffer(GL_ARRAY_BUFFER, vbo);
         glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), quadVertices, GL_STATIC_DRAW);
         glEnableVertexAttribArray(0); // position
         glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
         glEnableVertexAttribArray(1); // texcoord
         glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));

      }
      else
      {

         glBindVertexArray(vao);

      }

      m_pshaderBlend2->bind();

      glActiveTexture(GL_TEXTURE0);
      glBindTexture(GL_TEXTURE_2D, ptextureSrc->m_gluTextureID);
      m_pshaderBlend2->_set_int("uTexture", 0);

      // Optional: if each texture should be rendered to a specific portion of the screen
      // set a model/view/projection matrix or glViewport/scissor here.

      glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
      //}

      m_pshaderBlend2->unbind();

#if SHOW_DEBUG_DRAWING

      {


         {

            ///glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);


            glEnable(GL_BLEND);
            glBlendFunc(GL_ONE, GL_ZERO); // Source Copy mode
            //glBlendEquation(GL_FUNC_ADD); // default, can be omitted if unchanged

            {
               float fOpacity = 0.5;
               float fRed = 0.5;
               float fGreen = 0.75;
               float fBlue = 0.95;
               auto f32Opacity = (float)fOpacity;
               auto f32Red = (float)(fRed * fOpacity);
               auto f32Green = (float)(fGreen * fOpacity);
               auto f32Blue = (float)(fBlue * fOpacity);
               ::glColor4f(f32Red, f32Green, f32Blue, f32Opacity);
            }

            ::double_polygon polygon;

            ::double_rectangle rectangle(500, 100, 550, 150);

            polygon = rectangle;

            glBegin(GL_QUADS);


            vertex2f(polygon, 0.f);

            glEnd();

         }
      }
#endif // SHOW_DEBUG_DRAWING


   }


   void renderer::blend(::gpu::texture* ptextureTarget, ::gpu::texture* ptextureSource)
   {

      ::gpu::context_lock contextlock(m_pgpucontext);

      ::cast < texture > ptextureDst = ptextureTarget;
      ::cast < texture > ptextureSrc = ptextureSource;

      GLuint framebuffer;
      glGenFramebuffers(1, &framebuffer);
      glBindFramebuffer(GL_DRAW_FRAMEBUFFER, framebuffer);

      // Bind the destination texture (textures[textureSrc]) as the framebuffer color attachment
      glFramebufferTexture2D(
         GL_DRAW_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D,
         ptextureDst->m_gluTextureID,
         0);

      if (glCheckFramebufferStatus(GL_DRAW_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
         printf("Framebuffer not complete!\n");
         glDeleteFramebuffers(1, &framebuffer);
         return;
      }

      if (!m_pshaderBlend2)
      {

         __construct_new(m_pshaderBlend2);

         m_pshaderBlend2->initialize_shader_with_block(
            this,
            blend_vert,
            blend_frag);

      }

      float quadVertices[] = {
         // pos      // uv
         -1.0f, -1.0f,  0.0f, 0.0f,
          1.0f, -1.0f,  1.0f, 0.0f,
         -1.0f,  1.0f,  0.0f, 1.0f,
          1.0f,  1.0f,  1.0f, 1.0f,
      };


      auto rectangleTarget = ptextureSource->m_rectangleTarget;

      glViewport(
         rectangleTarget.left(),
         ptextureDst->size().cy() - rectangleTarget.bottom(),
         rectangleTarget.width(),
         rectangleTarget.height());

      // Optional: scissor if you want to limit drawing region
      glEnable(GL_SCISSOR_TEST);
      glScissor(
         rectangleTarget.left(),
         ptextureDst->size().cy() - rectangleTarget.bottom(),
         rectangleTarget.width(),
         rectangleTarget.height()
      );

      glDepthMask(FALSE);
      glDisable(GL_DEPTH_TEST);

      glEnable(GL_BLEND);
      glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
      glBlendEquation(GL_FUNC_ADD); // default, can be omitted if unchanged

      // VAO/VBO setup
      GLuint vao, vbo;
      glGenVertexArrays(1, &vao);
      glGenBuffers(1, &vbo);
      glBindVertexArray(vao);
      glBindBuffer(GL_ARRAY_BUFFER, vbo);
      glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), quadVertices, GL_STATIC_DRAW);
      glEnableVertexAttribArray(0); // position
      glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
      glEnableVertexAttribArray(1); // texcoord
      glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));

      m_pshaderBlend2->bind();

      GLint uTexture = glGetUniformLocation(m_pshaderBlend2->m_ProgramID, "uTexture");

      glActiveTexture(GL_TEXTURE0);
      glBindTexture(GL_TEXTURE_2D, ptextureSrc->m_gluTextureID);
      glUniform1i(uTexture, 0);

      // Optional: if each texture should be rendered to a specific portion of the screen
      // set a model/view/projection matrix or glViewport/scissor here.

      glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
      //}

      m_pshaderBlend2->unbind();


#if SHOW_DEBUG_DRAWING
      {


         {

            glBindFramebuffer(GL_FRAMEBUFFER, 0);


            glEnable(GL_BLEND);
            glBlendFunc(GL_ONE, GL_ZERO); // Source Copy mode
            //glBlendEquation(GL_FUNC_ADD); // default, can be omitted if unchanged

            {
               float fOpacity = 0.5;
               float fRed = 0.5;
               float fGreen = 0.75;
               float fBlue = 0.95;
               auto f32Opacity = (float)fOpacity;
               auto f32Red = (float)(fRed * fOpacity);
               auto f32Green = (float)(fGreen * fOpacity);
               auto f32Blue = (float)(fBlue * fOpacity);
               ::glColor4f(f32Red, f32Green, f32Blue, f32Opacity);
            }

            ::double_polygon polygon;

            ::double_rectangle rectangle(500, 100, 550, 150);

            polygon = rectangle;

            glBegin(GL_QUADS);


            vertex2f(polygon, 0.f);

            glEnd();

         }
      }

#endif

      glBindFramebuffer(GL_FRAMEBUFFER, 0); // Return to default framebuffer

      glDeleteFramebuffers(1, &framebuffer);

   }


   //void vertex2f(const ::double_polygon& a, float fZ)
   //{
   //   for (auto& p : a)
   //   {

   //      glVertex3f((GLfloat)p.x(), (GLfloat)p.y(), fZ);

   //   }

   //}


   void renderer::copy(::gpu::texture* pgputextureTarget, ::gpu::texture* pgputextureSource)
   {

      ::gpu::context_lock contextlock(m_pgpucontext);

      //glBindFramebuffer(GL_FRAMEBUFFER, 0);


      //glEnable(GL_BLEND);
      //glBlendFunc(GL_ONE, GL_ZERO); // Source Copy mode
      ////glBlendEquation(GL_FUNC_ADD); // default, can be omitted if unchanged

      //glBegin(GL_QUADS);

      //{
      //   float fOpacity = 0.5;
      //   float fRed = 0.5;
      //   float fGreen = 0.75;
      //   float fBlue = 0.95;
      //   auto f32Opacity = (float)fOpacity;
      //   auto f32Red = (float)(fRed * fOpacity);
      //   auto f32Green = (float)(fGreen * fOpacity);
      //   auto f32Blue = (float)(fBlue * fOpacity);
      //   ::glColor4f(f32Red, f32Green, f32Blue, f32Opacity);
      //}

      //::double_polygon polygon;

      //::double_rectangle rectangle(100, 100, 200, 200);

      //polygon = rectangle;


      //vertex2f(polygon, 0.f);

      //glEnd();


      //return;

      ::cast < texture > ptextureDst = pgputextureTarget;
      ::cast < texture > ptextureSrc = pgputextureSource;

      if (ptextureDst->m_pgpurenderer->m_pgpucontext->m_etype == ::gpu::context::e_type_window)
      {

         ptextureDst->m_pgpurenderer->m_pgpucontext->copy(pgputextureSource);

         return;

      }

      GLuint framebuffer;
      glGenFramebuffers(1, &framebuffer);
      glBindFramebuffer(GL_DRAW_FRAMEBUFFER, framebuffer);

      // Bind the destination texture (textures[textureSrc]) as the framebuffer color attachment
      glFramebufferTexture2D(
         GL_DRAW_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D,
         ptextureDst->m_gluTextureID,
         0);

      if (glCheckFramebufferStatus(GL_DRAW_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
         printf("Framebuffer not complete!\n");
         glDeleteFramebuffers(1, &framebuffer);
         return;
      }

      if (!m_pshaderBlend2)
      {

         __construct_new(m_pshaderBlend2);

         m_pshaderBlend2->initialize_shader_with_block(
            this,
            blend_vert,
            blend_frag);

      }

      float quadVertices[] = {
         // pos      // uv
         -1.0f, -1.0f,  0.0f, 0.0f,
          1.0f, -1.0f,  1.0f, 0.0f,
         -1.0f,  1.0f,  0.0f, 1.0f,
          1.0f,  1.0f,  1.0f, 1.0f,
      };


      auto rectangleTarget = ptextureSrc->m_rectangleTarget;

      glViewport(
         rectangleTarget.left(),
         rectangleTarget.top(),
         rectangleTarget.width(),
         rectangleTarget.height());

      // Optional: scissor if you want to limit drawing region
      glEnable(GL_SCISSOR_TEST);
      glScissor(
         0,
         0,
         rectangleTarget.width(),
         rectangleTarget.height()
      );

      glDisable(GL_BLEND);
      // glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
      //glBlendEquation(GL_FUNC_ADD); // default, can be omitted if unchanged
      glDisable(GL_DEPTH_TEST);
      glDepthMask(FALSE);


      // VAO/VBO setup
      GLuint vao, vbo;
      glGenVertexArrays(1, &vao);
      glGenBuffers(1, &vbo);
      glBindVertexArray(vao);
      glBindBuffer(GL_ARRAY_BUFFER, vbo);
      glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), quadVertices, GL_STATIC_DRAW);
      glEnableVertexAttribArray(0); // position
      glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
      glEnableVertexAttribArray(1); // texcoord
      glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));

      m_pshaderBlend2->bind();

      GLint uTexture = glGetUniformLocation(m_pshaderBlend2->m_ProgramID, "uTexture");

      glActiveTexture(GL_TEXTURE0);
      glBindTexture(GL_TEXTURE_2D, ptextureSrc->m_gluTextureID);
      glUniform1i(uTexture, 0);

      // Optional: if each texture should be rendered to a specific portion of the screen
      // set a model/view/projection matrix or glViewport/scissor here.

      glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
      //}

      m_pshaderBlend2->unbind();


      {

         glBindFramebuffer(GL_FRAMEBUFFER, 0);


         glEnable(GL_BLEND);
         glBlendFunc(GL_ONE, GL_ZERO); // Source Copy mode
         //glBlendEquation(GL_FUNC_ADD); // default, can be omitted if unchanged

         {
            float fOpacity = 0.5;
            float fRed = 0.5;
            float fGreen = 0.75;
            float fBlue = 0.95;
            auto f32Opacity = (float)fOpacity;
            auto f32Red = (float)(fRed * fOpacity);
            auto f32Green = (float)(fGreen * fOpacity);
            auto f32Blue = (float)(fBlue * fOpacity);
            ///::glColor4f(f32Red, f32Green, f32Blue, f32Opacity);
         }

         ::double_polygon polygon;

         ::double_rectangle rectangle(100, 100, 200, 200);

         polygon = rectangle;

         //glBegin(GL_QUADS);


         //vertex2f(polygon, 0.f);

         //glEnd();

      }

      glBindFramebuffer(GL_FRAMEBUFFER, 0); // Return to default framebuffer

      glDeleteFramebuffers(1, &framebuffer);


   }


//   void renderer::on_end_layer(::gpu::layer* player)
//   {
//
//      ::gpu::context_lock contextlock(m_pgpucontext);
//
//      ::cast < texture > ptextureDst = player->texture();
//
//      ::cast < texture > ptextureSrc = m_pgpurendertarget->current_texture();
//
//      auto textureSrc = ptextureSrc->m_gluTextureID;
//
//      auto textureDst = ptextureDst->m_gluTextureID;
//
//      glFlush();
//      GLCheckError("");
//
//      GLuint fboSrc, fboDst;
//      glGenFramebuffers(1, &fboSrc);
//      GLCheckError("");
//      glGenFramebuffers(1, &fboDst);
//      GLCheckError("");
//
//      // Attach source texture to fboSrc
//      glBindFramebuffer(GL_READ_FRAMEBUFFER, fboSrc);
//      GLCheckError("");
//      glFramebufferTexture2D(GL_READ_FRAMEBUFFER, GL_COLOR_ATTACHMENT0,
//         GL_TEXTURE_2D, textureSrc, 0);
//      GLCheckError("");
//
//      // Attach dest texture to fboDst
//      glBindFramebuffer(GL_DRAW_FRAMEBUFFER, fboDst);
//      GLCheckError("");
//      glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER, GL_COLOR_ATTACHMENT0,
//         GL_TEXTURE_2D, textureDst, 0);
//      GLCheckError("");
//
//      auto sizeSrc = ptextureSrc->size();
//      auto sizeDst = ptextureDst->size();
//
//      // Blit from source to destination
//      glBlitFramebuffer(
//         0, 0, sizeSrc.cx(), sizeSrc.cy(),
//         0, 0, sizeDst.cx(), sizeDst.cy(),
//         GL_COLOR_BUFFER_BIT, GL_NEAREST
//      );
//      GLCheckError("");
//#ifdef SHOW_DEBUG_DRAWING
//      {
//
//         //glBindFramebuffer(GL_FRAMEBUFFER, 0);
//
//
//         glEnable(GL_BLEND);
//         glBlendFunc(GL_ONE, GL_ZERO); // Source Copy mode
//         //glBlendEquation(GL_FUNC_ADD); // default, can be omitted if unchanged
//
//         {
//            float fOpacity = 0.5;
//            float fRed = 0.5;
//            float fGreen = 0.75;
//            float fBlue = 0.95;
//            auto f32Opacity = (float)fOpacity;
//            auto f32Red = (float)(fRed * fOpacity);
//            auto f32Green = (float)(fGreen * fOpacity);
//            auto f32Blue = (float)(fBlue * fOpacity);
//            ::glColor4f(f32Red, f32Green, f32Blue, f32Opacity);
//         }
//
//         ::double_polygon polygon;
//
//         ::double_rectangle rectangle(300, 300, 400, 400);
//
//         polygon = rectangle;
//
//         glBegin(GL_QUADS);
//
//
//         vertex2f(polygon, 0.f);
//
//         glEnd();
//
//      }
//#endif
//
//      // Cleanup
//      glBindFramebuffer(GL_FRAMEBUFFER, 0);
//      GLCheckError("");
//      glDeleteFramebuffers(1, &fboSrc);
//      GLCheckError("");
//      glDeleteFramebuffers(1, &fboDst);
//      GLCheckError("");
//
//
//   }


} // namespace gpu_opengl





