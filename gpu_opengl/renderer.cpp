#include "framework.h"
#include "approach.h"
#include "context.h"
#include "device.h"
#include "gpu_opengl/context.h"
#include "gpu_opengl/cpu_buffer.h"
#include "frame.h"
#include "frame_buffer.h"
#include "glad.h"
//#include "GLFW/glfw3.h"
#include <vector>
#include <map>
//#include "GLError.h"
#include "renderer.h"
//#include "mesh.h"
#include "aura/graphics/image/target.h"
#include "aura/platform/application.h"
#include "aura/user/user/graphics3d.h"
#include "aura/windowing/window.h"


namespace gpu_opengl
{


   renderer::renderer()
   {
      m_VAOFullScreenQuad = 0;
      m_VBOFullScreenQuad = 0;
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

      //if(m_pgpucontext->m_eoutput == ::gpu::e_output_swap_chain)
      //{
      //   
      //   set_placement(m_pgpucontext->size());

      //}  

      //context_guard guard(this);

      m_pgpucontext->make_current();
      //glEnable(GL_DEPTH_TEST);
      //glDepthMask(GL_TRUE);
      //glDisable(GL_BLEND);
      //glDepthFunc(GL_LESS);

      //glClear(GL_DEPTH_BUFFER_BIT);





      //glPushMatrix();
      //glPushAttrib(GL_ALL_ATTRIB_BITS);






      //auto rectangle = m_pgpucontext->m_pimpact->host_rectangle();

      ::cast < context > pgpucontext = m_pgpucontext;

      //auto sizeHost = m_pgpucontext->size();

      auto r = pgpucontext->rectangle();

      //glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
      //glBlendFunc(GL_SRC_ALPHA, GL_SRC_ALPHA);
      //glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
      //glBlendFunc(GL_ZERO, GL_SRC_ALPHA);
      //glBlendEquationSeparate(GL_FUNC_ADD, GL_FUNC_ADD);
      // glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ZERO);
      //glEnable(GL_BLEND);


      int left;

      int top;

      int width;

      int height;

      if (m_pgpucontext->m_eoutput == ::gpu::e_output_cpu_buffer)
      {

         left = 0;

         top = 0;

         width = r.width();

         height = r.height();

         //glViewport(left, top, width, height);

         //m_pgpucontext->clear(::color::transparent);

      }
      else if (m_pgpucontext->m_eoutput == ::gpu::e_output_swap_chain)
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

      if (!m_pframe)
      {

         m_pframe = __create_new < ::gpu_opengl::frame >();

      }

      return ::gpu::renderer::beginFrame();

   }


   void renderer::on_begin_render(::gpu::frame* pframe)
   {

      if (m_escene == ::gpu::e_scene_2d)
      {

         auto r = m_pgpucontext->rectangle();

         int width = r.width();

         int height = r.height();


         //::cast < ::gpu_opengl::context >pgpucontext = m_pgpucontext;

//pgpucontext->m_size = size;

//pgpucontext->m_sizeNew = size;

//pgpucontext->m_sizeHost = size;

//pgpucontext->make_current();

//m_pframe = prenderer->beginFrame();

//prenderer->on_begin_render(m_pframe);
//glEnable(GL_BLEND);
//glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
//glEnable(GL_BLEND);
//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
         glDepthMask(GL_TRUE); // Enable writing to depth
         glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
         glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
         glDepthMask(GL_FALSE); // Disable writing to depth

         glEnable(GL_BLEND);
         glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
         glBlendEquation(GL_FUNC_ADD); // default, can be omitted if unchanged
         glDisable(GL_DEPTH_TEST);
         //glDepthFunc(GL_LEQUAL);

         ///::opengl::resize(size, bYSwap);

         bool bYSwap = true;
         //double d = 200.0 / 72.0;

   //double d = 1.0;
   ////glViewport(0, 0, size.cx() * d, size.cy() * d);
         glViewport(0, 0, width, height);
         glMatrixMode(GL_PROJECTION);
         glLoadIdentity();
         ////glOrtho(0, size.cx() * d, size.cy() * d, 0.0f, 000.0f, 1000.0f);
         ////glOrtho(0, size.cx() * d, size.cy() * d, 0.0f, 000.0f, 1000.0f);
         //////glOrtho(0, size.cx() * d, 0.0f, size.cy() * d, 000.0f, 1000.0f);
         ////glOrtho(0, size.cx(), size.cy(), 0.0f, -1000.0f, 1000.0f);
         //glOrtho(0.f, size.cx(), 0.f, -size.cy(), -1.0f, 1.0f);
         if (bYSwap)
         {
            glOrtho(0.0f, width, height, 0, -1.0f, 1.0f);  // Flip Y
         }
         else
         {
            glOrtho(0.0f, width, 0, height, -1.0f, 1.0f);  // Flip Y
         }
         glMatrixMode(GL_MODELVIEW);
         glLoadIdentity();
         //auto left = 0.;
         //auto right = (double) size.cx();
         //auto bottom = 0.;
         //auto top = (double)size.cy();
         //double dFar = 1.0;
         //double dNear = -1.0;
         //double tx = -(right + left) / (right - left);
         //double ty = -(top + bottom) / (top - bottom);
         //double tz = -(dFar + dNear) / (dFar - dNear);
         //double a[] =
         //{
         //   2.0/(right - left),0.0,0.0,tx,
         //   0.0,2.0/(top - bottom),0.0,ty,
         //   0.0,0.0,-2.0/(dFar-dNear),tz,
         //   0.0,0.0,0.0,1.0
         //};
         //glMultMatrixd(a);

         //glMatrixMode(GL_MODELVIEW);
         //glLoadIdentity();


         //gluOrtho2D(0.f, size.cx(), 0.f, size.cy());
         //glMatrixMode(GL_MODELVIEW);
         //glLoadIdentity();

         // Clear
         //glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
         //glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

         //glDisable(GL_DEPTH_TEST);

         // Translate to inside of pixel (otherwise inaccuracies can occur on certain gl implementations)
         //if (OpenGL::accuracyTweak())
         glTranslatef(0.5f, 0.5f, 0);



         //m_z = 0.0f;

         //glLoadIdentity();
         //glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
         //glClear(GL_COLOR_BUFFER_BIT);
         //glEnable(GL_BLEND);
         //glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
         //::memory_copy(&m_pgpucontext->m_pbuffer->m_pixmap, (::pixmap *)m_pimage, sizeof(::pixmap));

         //glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

         //m_pgpucontext->start_drawing();

         ///glEnable(GL_DEPTH_TEST);



            //glScissor(left, top, width, height);
            //glEnable(GL_SCISSOR_TEST);
            //glViewport(left, top, width, height);

            //glOrtho(0.0f, width, height, 0, -1.0f, 1.0f);  // Flip Y

            //m_pgpucontext->clear(color::transparent);

            //glMatrixMode(GL_MODELVIEW);
            //glMatrixMode(GL_PROJECTION);
            //glLoadIdentity();

            //glOrtho(0.0f, width, 0, height, -1.0f, 1.0f);  // Flip Y


      //m_pgpucontext->clear(argb(0.5f, 0.2f, 0.4f, 0.5f));

      //glScissor(left, top, width, height);
      //glEnable(GL_SCISSOR_TEST);

    /*     glMatrixMode(GL_PROJECTION);
         glLoadIdentity();

         glMatrixMode(GL_MODELVIEW);
         glLoadIdentity();
*/


//if (m_pgpucontext->m_eoutput == ::gpu::e_output_cpu_buffer)
//{

////   glOrtho(0.0f, r.width(), 0, r.height(), -1.0f, 1.0f);  // Flip Y

//}
//else
//{

 //glOrtho(0.0f, r.width()/3, r.height()/3, 0, -1.0f, 1.0f);  // Flip Y

//}


//// Frame Logic
//float currentFrame = ::time::now().floating_second();
//float deltaTime = currentFrame - lastFrame;
//lastFrame = currentFrame;

//deltaTime = minimum_maximum(deltaTime, 0.001, 0.016666666);

//ProcessInput(deltaTime);

// Toggle wireframe mode
//if (m_pgpucontext->m_pimpact->m_pengine->m_bWireframeMode) {
//   glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // Enable wireframe mode
//}
//else {
//   glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); // Enable solid mode
//}


      }

   }


   int renderer::get_frame_count() const
   {

      return 0;

   }


   //void renderer::Clear() const
   //{

   //   // Clear the screen 
   //   GLCheckError();
   //   glClearColor(0.678f, 0.847f, 0.902f, 1.0f);
   //   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   //   GLCheckError();
   //}

   //// sky_box
   //void renderer::DrawSkybox(const mesh* pskyboxMesh, ::gpu::shader* pshader) const
   //{
   //   GLCheckError();
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
   //   GLCheckError();
   //}


   //void renderer::DrawInstanced(const ::array<mesh*>& meshes, ::gpu::shader* pshader, unsigned int instanceCount) const
   //{

   //   GLCheckError();

   //   for (const mesh* mesh : meshes) {
   //      mesh->Bind();
   //      glDrawElementsInstanced(GL_TRIANGLES, mesh->GetIndexCount(), GL_UNSIGNED_INT, (void*)(mesh->GetIndexOffset() * sizeof(unsigned int)), instanceCount);
   //      mesh->Unbind();
   //   }

   //   GLCheckError();
   //}


   //void renderer::DrawModel(const ::array<mesh*>& mehses, ::gpu::shader* pshader)
   //{

   //}


   void renderer::endFrame()
   {


      //glDisable(GL_DEPTH_TEST);


      //}

//            glDepthFunc(GL_LESS);

      //glPopAttrib();
      //glPopMatrix();


      //glDisable(GL_DEPTH_TEST);
      //glDepthMask(GL_FALSE);
      //glEnable(GL_BLEND);
      //glDisable(GL_SCISSOR_TEST);
      glFlush();

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

      if (eoutput == ::gpu::e_output_swap_chain)
      {

         _swap();

      }
      else if (eoutput == ::gpu::e_output_cpu_buffer)
      {

         _sample();

      }

      m_pgpucontext->release_current();

   }


   //void renderer::endDraw(::user::interaction * puserinteraction)
   //{
   //   //prenderer->_blend_image(vkimage, rectangle);

   //   if (m_eoutputOnEndDraw == ::gpu::e_output_swap_chain)
   //   {

   //      //m_pgpucontext->swap_buffers();

   //      //m_pwindow->m_timeLastDrawGuard1.Now();


   //   //VkImage vkimage = prenderer->m_pvkcrenderpass->m_images[prenderer->currentImageIndex];

   //      ::int_rectangle rectangle;

   //      if (puserinteraction && !puserinteraction->host_rectangle().size().is_empty())
   //      {

   //         rectangle = puserinteraction->host_rectangle();

   //      }
   //      else
   //      {

   //         rectangle = { 0, 0, 1920, 1080 };

   //      }

   //      ::cast < ::windowing::window > pwindow = puserinteraction->m_pacmewindowingwindow;

   //      if (!m_pgpucontextOutput)
   //      {

   //         __øconstruct(m_pgpucontextOutput);

   //         m_pgpucontextOutput = m_papplication->get_gpu()->get_device(pwindow, pwindow->get_window_rectangle())->start_swap_chain_context(this, pwindow);

   //         //m_pgpucontextOutput->create_window_buffer(pwindow);

   //      }

   //      ::cast < ::gpu_opengl::renderer > prendererOutput = m_pgpucontextOutput->get_renderer();

   //      auto rectanglePlacement = pwindow->get_window_rectangle();

   //      m_pgpucontextOutput->set_placement(rectanglePlacement);

   //      //m_pgpucontextOutput->m_size = rectanglePlacement.size();

   //      ::cast < ::gpu_opengl::context > pgpucontextOpenGL = m_pgpucontextOutput;

   //      pgpucontextOpenGL->m_sizeHost = rectanglePlacement.size();

   //      pgpucontextOpenGL->set_placement(rectanglePlacement);

   //      //m_pgpucontext->m_eoutput = ::gpu::e_output_gpu_buffer;

   //      //prendererOutput->defer_update_render_pass();

   //      prendererOutput->_on_graphics_end_draw(this);


   //   }
   //   else if (m_eoutputOnEndDraw == ::gpu::e_output_cpu_buffer)
   //   {

   //      //m_pgpucontext->swap_buffers();

   //    //}
   //    //else
   //    //{

   //      read_to_cpu_buffer();

   //      throw ::exception(error_not_implemented, "renderer::endDraw() not implemented for e_output_cpu_buffer");

   //      /*m_pimage->map();

   //      m_pimage->copy(&m_pgpucontext->m_pcpubuffer->m_pixmap);*/

   //   }



   //}


   void renderer::_sample()
   {

      //      glDisable(GL_DEPTH_TEST);
      //
      //
      //      //}
      //
      ////            glDepthFunc(GL_LESS);
      //
      //      glPopAttrib();
      //      glPopMatrix();


      ::cast<context>pgpucontext = m_pgpucontext;

      if (pgpucontext)
      {

         auto pcpubuffer = pgpucontext->m_pcpubuffer;

         if (pcpubuffer)
         {

            auto pimagetarget = pcpubuffer->m_pimagetarget;

            if (pimagetarget)
            {

               auto pcpubuffer = pgpucontext->m_pcpubuffer;

               if (pcpubuffer)
               {

                  pcpubuffer->set_size(pgpucontext->m_rectangle.size());

                  pcpubuffer->gpu_read();

                  //auto data = pcpubuffer->m_pixmap.data();
                  //auto width = pcpubuffer->m_pixmap.width();
                  //auto height = pcpubuffer->m_pixmap.height();
                  //auto scan = pcerrorpubuffer->m_pixmap.m_iScan;

                  //pimagetarget->set_image_pixels(data, width, height, scan);

               }

            }

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


   void renderer::_swap()
   {

      m_pgpucontext->swap_buffers();

   }
   GLuint createFullscreenQuad(GLuint& quadVBO) {
      // Vertex data: (x, y, u, v)
#if 1
      float quadVertices[] = {
         //  Position   TexCoords
         -1.0f,  1.0f,  0.0f, 1.0f, // Top-left
         -1.0f, -1.0f,  0.0f, 0.0f, // Bottom-left
          1.0f, -1.0f,  1.0f, 0.0f, // Bottom-right

         -1.0f,  1.0f,  0.0f, 1.0f, // Top-left
          1.0f, -1.0f,  1.0f, 0.0f, // Bottom-right
          1.0f,  1.0f,  1.0f, 1.0f  // Top-right
      };
#else
      float quadVertices[] = {
         //  Position   TexCoords
         0.0f,  1.0f,  0.0f, 1.0f, // Top-left
         0.0f, 0.0f,  0.0f, 0.0f, // Bottom-left
          1.0f, 0.0f,  1.0f, 0.0f, // Bottom-right

         0.0f,  1.0f,  0.0f, 1.0f, // Top-left
          1.0f, 0.0f,  1.0f, 0.0f, // Bottom-right
          1.0f,  1.0f,  1.0f, 1.0f  // Top-right
      };
#endif
      GLuint quadVAO = 0;

      glGenVertexArrays(1, &quadVAO);
      glGenBuffers(1, &quadVBO);

      glBindVertexArray(quadVAO);
      glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
      glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), quadVertices, GL_STATIC_DRAW);

      // Position attribute (location = 0)
      glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
      glEnableVertexAttribArray(0);

      // Texture Coord attribute (location = 1)
      glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
      glEnableVertexAttribArray(1);

      // Unbind for safety
      glBindVertexArray(0);
      return quadVAO;

   }


   void renderer::endDraw(::user::interaction* puserinteraction, ::gpu::renderer* pgpurendererSrc)
   {

      ::cast < ::gpu_opengl::renderer > prenderer = pgpurendererSrc;

      auto rectangle = prenderer->m_pgpucontext->rectangle();

      m_pgpucontext->set_placement(rectangle);

      //VkImage image = prenderer->m_pvkcrenderpass->m_images[prenderer->get_frame_index()];

      //on_new_frame();

      //if (1)
      //{
      //   //auto cmdBuffer = m_pgpucontext->beginSingleTimeCommands();

      //   //VkImageMemoryBarrier barrier = {
      //   //    .sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER,
      //   //    .srcAccessMask = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT,
      //   //    .dstAccessMask = VK_ACCESS_SHADER_READ_BIT,
      //   //    .oldLayout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL,
      //   //    .newLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL,
      //   //    .srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED,
      //   //    .dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED,
      //   //    .image = image,
      //   //    .subresourceRange = {
      //   //        .aspectMask = VK_IMAGE_ASPECT_COLOR_BIT,
      //   //        .baseMipLevel = 0,
      //   //        .levelCount = 1,
      //   //        .baseArrayLayer = 0,
      //   //        .layerCount = 1
      //   //    },
      //   //};

      //   //vkCmdPipelineBarrier(
      //   //   cmdBuffer,
      //   //   VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT,
      //   //   VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT,
      //   //   0,
      //   //   0, NULL,
      //   //   0, NULL,
      //   //   1, &barrier
      //   //);

      //   //VkSubmitInfo submitInfo = {};
      //   //submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;

      //   //VkSemaphore waitSemaphores[] = { prendererSrc->m_pvkcrenderpass->renderFinishedSemaphores[prendererSrc->m_pvkcrenderpass->currentFrame] };
      //   //VkPipelineStageFlags waitStages[] = { VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT };
      //   //submitInfo.waitSemaphoreCount = 1;
      //   //submitInfo.pWaitSemaphores = waitSemaphores;
      //   //submitInfo.pWaitDstStageMask = waitStages;

      //   //submitInfo.commandBufferCount = 1;
      //   //submitInfo.pCommandBuffers = &cmdBuffer;

      //   //m_pgpucontext->endSingleTimeCommands(cmdBuffer, 1, &submitInfo);
      //   auto cmdBuffer = m_pgpucontext->beginSingleTimeCommands();


      //   insertImageMemoryBarrier(cmdBuffer,
      //      image,
      //      0,
      //      VK_ACCESS_TRANSFER_WRITE_BIT,
      //      VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL,
      //      VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL,
      //      VK_PIPELINE_STAGE_TRANSFER_BIT,
      //      VK_PIPELINE_STAGE_TRANSFER_BIT,
      //      VkImageSubresourceRange{ VK_IMAGE_ASPECT_COLOR_BIT, 0, 1, 0, 1 });



      //   VkSubmitInfo submitInfo{};
      //   submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
      //   submitInfo.commandBufferCount = 1;
      //   submitInfo.pCommandBuffers = &cmdBuffer;
      //   ::array<VkSemaphore> waitSemaphores;
      //   ::array<VkPipelineStageFlags> waitStages;
      //   waitStages.add(VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT);
      //   waitSemaphores.add(prenderer->m_pvkcrenderpass->renderFinishedSemaphores[prenderer->get_frame_index()]);
      //   submitInfo.waitSemaphoreCount = waitSemaphores.size();
      //   submitInfo.pWaitSemaphores = waitSemaphores.data();
      //   submitInfo.pWaitDstStageMask = waitStages.data();
      //   m_pgpucontext->endSingleTimeCommands(cmdBuffer, 1, &submitInfo);

      //   //m_prendererResolve->m_pvkcrenderpass->m_semaphoreaWaitToSubmit.add(
      //   //   m_pvkcrenderpass->renderFinishedSemaphores[iPassCurrentFrame]
      //   //);


      //}

      m_pgpucontext->send([this, prenderer]()
         {

            if (auto pframe = beginFrame())
            {

               //m_pvkcrenderpass->m_semaphoreaSignalOnSubmit.add(prendererSrc->m_pvkcrenderpass->imageAvailableSemaphores[prendererSrc->get_frame_index()]);


               //on_begin_frame();
               // render
               on_begin_render(pframe);

               m_pgpucontext->clear(::argb(127, 140 / 2, 220 / 2, 240 / 2));
               //m_pgpucontext->clear(::color::transparent);


               if (1)
               {


                  //if (m_pimpact->global_ubo_block().size() > 0)
                  //{

                    // update_global_ubo(m_pgpucontext);

                  //}

                  //m_pscene->on_render(m_pgpucontext);

                  //_blend_image(image, m_rectangle);

         //         glDisable(GL_BLEND);
         //         //glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
                  auto pvertexshader = R"vertexshader(#version 330 core
layout(location = 0) in vec2 aPos;
layout(location = 1) in vec2 aTexCoord;

out vec2 TexCoord;

void main() {
   gl_Position = vec4(aPos.xy, 0.0, 1.0);
   TexCoord = aTexCoord;
}
)vertexshader";


                  auto pfragmentshader = R"fragmentshader(#version 330 core
in vec2 TexCoord;
out vec4 FragColor;

uniform sampler2D uTexture;

void main() {
   FragColor = texture(uTexture, TexCoord);
}
)fragmentshader";

                  if (!m_pshaderBlend)
                  {

                     m_pshaderBlend = __create_new < ::gpu_opengl::shader >();

                     m_pshaderBlend->initialize_shader_with_block(
                        this,
                        pvertexshader, pfragmentshader);


                  }

                  m_pshaderBlend->bind();

                  if (1)
                  {

                     glActiveTexture(GL_TEXTURE0);

                     int iGlError1 = glGetError();

                     ::cast < context > pcontext = prenderer->m_pgpucontext;

                     GLuint tex = pcontext->m_pframebuffer->m_tex;

                     glBindTexture(GL_TEXTURE_2D, tex);

                     int iGlError2 = glGetError();

                     ::cast < ::gpu_opengl::shader > pshaderBlend = m_pshaderBlend;

                     pshaderBlend->_set_int("uTexture", 0);

                     if (!m_VAOFullScreenQuad)
                     {

                        m_VAOFullScreenQuad = createFullscreenQuad(m_VBOFullScreenQuad);

                     }

                     glBindVertexArray(m_VAOFullScreenQuad);

                     int iGlError00 = glGetError();

                     glDrawArrays(GL_TRIANGLES, 0, 6); // assuming 2 triangles (quad)

                     int iGlError01 = glGetError();

                     glBindVertexArray(0);

                     int iGlErrorA = glGetError();

                     glBindTexture(GL_TEXTURE_2D, 0);

                     int iGlErrorB = glGetError();

                     debug() << "gl error";

                  }

                  m_pshaderBlend->unbind();

               }

               on_end_render(pframe);

               endFrame();


            }

         });


   }


   void renderer::blend(::gpu::renderer* prendererSource)
   {

      auto rectangleHost = m_pgpucontext->rectangle();

      int wHost = rectangleHost.width();

      int hHost = rectangleHost.height();

      glPopAttrib();
      glPopMatrix();

      glViewport(0, 0, wHost, hHost);

      glDisable(GL_DEPTH_TEST);
      glDepthMask(GL_FALSE);

      glEnable(GL_BLEND);



      glMatrixMode(GL_PROJECTION);
      glLoadIdentity();
      ////glOrtho(0, size.cx() * d, size.cy() * d, 0.0f, 000.0f, 1000.0f);
      ////glOrtho(0, size.cx() * d, size.cy() * d, 0.0f, 000.0f, 1000.0f);
      //////glOrtho(0, size.cx() * d, 0.0f, size.cy() * d, 000.0f, 1000.0f);
      ////glOrtho(0, size.cx(), size.cy(), 0.0f, -1000.0f, 1000.0f);
      //glOrtho(0.f, size.cx(), 0.f, -size.cy(), -1.0f, 1.0f);
      auto bYSwap = true;
      if (bYSwap)
      {
         glOrtho(0.0f, wHost, hHost, 0, -1.0f, 1.0f);  // Flip Y
      }
      else
      {
         glOrtho(0.0f, wHost, 0, hHost, -1.0f, 1.0f);  // Flip Y
      }
      glMatrixMode(GL_MODELVIEW);
      glLoadIdentity();

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
            m_pgpucontext->m_pgpurenderer,
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

      float WIDTH = (float) wHost;
      float HEIGHT = (float) hHost;

      auto rectangle = prendererSource->m_pgpucontext->rectangle();

      float w = (float) rectangle.width();
      float h = (float) rectangle.height();
      float x = (float) rectangle.left();
      float y = (float) (hHost - rectangle.bottom());

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
         l = (float) rectangle.left();
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


} // namespace gpu_opengl





