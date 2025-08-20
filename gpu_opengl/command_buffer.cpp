// Created by camilo on 2025-06-30 22:42 <3ThomasBorregaardSørensen!!
#include "framework.h"
#include "command_buffer.h"
#include "device.h"
#include "render_target.h"
#include "renderer.h"
#include "texture.h"
#include "bred/gpu/frame.h"


namespace gpu_opengl
{


   command_buffer::command_buffer()
   {


   }


   command_buffer::~command_buffer()
   {


   }


   void command_buffer::set_viewport(const ::int_rectangle& rectangle)
   {

      glViewport(
         rectangle.left(),
         rectangle.top(),
         rectangle.width(),
         rectangle.height());
      GLCheckError("");

   }


   void command_buffer::set_scissor(const ::int_rectangle& rectangle)
   {

      glEnable(GL_SCISSOR_TEST);

      glScissor(
         rectangle.left(),
         rectangle.top(),
         rectangle.width(),
         rectangle.height()
      );

   }



   void command_buffer::draw(int a)
   {

      glDrawArrays(GL_TRIANGLES, 0, a);
      GLCheckError("");

   }


   void command_buffer::set_render_target()
   {


      ::cast < render_target > prendertarget = m_pgpurendertarget;

      ::cast < texture > ptexture = prendertarget->current_texture(::gpu::current_frame());

      if (!ptexture->m_gluFbo)
      {

         if (prendertarget->m_pgpurenderer->m_pgpucontext->m_escene == ::gpu::e_scene_3d)
         {

            ptexture->create_depth_resources();

         }
            
         ptexture->create_render_target();

      }

      ptexture->bind_render_target();

   }

   
   void command_buffer::draw_vertexes(int iVertexCount)
   {

      GLenum mode = GL_TRIANGLES;

      auto pshaderBound = m_pgpurendertarget->m_pgpurenderer->m_pgpucontext->m_pshaderBound;

      if (pshaderBound)
      {

         auto etopology = pshaderBound->m_etopology;

         mode = ::opengl::as_gl_draw_mode(etopology);

      }

      glDrawArrays(mode, 0, iVertexCount);
      GLCheckError("");

   }


   void command_buffer::draw_indexes(int iIndexCount)
   {

      GLenum mode = GL_TRIANGLES;

      auto pshaderBound = m_pgpurendertarget->m_pgpurenderer->m_pgpucontext->m_pshaderBound;

      if (pshaderBound)
      {

         auto etopology = pshaderBound->m_etopology;

         mode = ::opengl::as_gl_draw_mode(etopology);

      }

      GLenum etype;

      etype = GL_UNSIGNED_INT;

      glDrawElements(mode, iIndexCount, etype, 0);
      GLCheckError("");

   }



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



} // namespace gpu_opengl



