// Created by camilo on 2025-06-11 01:08 <3ThomasBorregaardSørensen!!
#include "framework.h"
#include "_gpu_opengl.h"
#include "command_buffer.h"
#include "context.h"
#include "input_layout.h"
#include "memory_buffer.h"
#include "model_buffer.h"
#include "acme/prototype/geometry2d/matrix.h"
#include "acme/prototype/prototype/call.h"
#include "bred/gpu/context_lock.h"
#include "bred/gpu/types.h"
#include "bred/graphics3d/types.h"


namespace gpu_opengl
{


   model_buffer::model_buffer()
   {

      m_gluVao = 0;

   }


   model_buffer::~model_buffer()
   {


   }


   void model_buffer::initialize_dummy_model(::gpu::context* pgpucontext, int iVertexCount)
   {

      ::gpu::model_buffer::initialize_dummy_model(pgpucontext, iVertexCount);

   }


   void model_buffer::on_initialize_gpu_context_object()
   {

      ::gpu::model_buffer::on_initialize_gpu_context_object();

      if (!m_gluVao)
      {

         ::gpu::context_lock contextlock(m_pgpucontext);

         glGenVertexArrays(1, &m_gluVao);
         GLCheckError("");

      }

   }


   void model_buffer::apply_input_layout()
   {

      //m_pinputlayout = pgpuinputlayout;

      ::cast < memory_buffer > pbufferVertex = m_pbufferVertex;

      ::cast < memory_buffer > pbufferIndex = m_pbufferIndex;

      if (pbufferVertex)
      {

         ::cast < input_layout > pinputlayout = m_pinputlayout;

         pinputlayout->__do_opengl_vao_vbo_and_ebo_input_layout(
            m_gluVao,
            pbufferVertex->m_gluVbo,
            pbufferIndex ? pbufferIndex->m_gluVbo : 0
         );

      }

   }


   void model_buffer::bind2(::gpu::command_buffer* pgpucommandbuffer)
   {

      //::gpu::context_lock contextlock(m_pgpucontext);

      ::gpu::context_lock contextlock(m_pgpucontext);

      if (m_pbufferVertex)
      {

         glBindVertexArray(m_gluVao);
         GLCheckError("");
         
         //m_pbufferVertex->bind();

         //if (m_pbufferIndex)
         //{

         //   m_pbufferIndex->bind();

         //}

         //glEnableVertexAttribArray(0); // Index must match the layout(location)
         //glVertexAttribPointer(
         //   0,              // index (matches shader layout location)
         //   2,              // size (number of components per vertex: x, y)
         //   GL_FLOAT,       // type
         //   GL_FALSE,       // normalized?
         //   2 * sizeof(float), // stride (bytes per vertex)
         //   (void*)0        // offset
         //);

         // 4. Unbind (optional for safety)
         //glBindBuffer(GL_ARRAY_BUFFER, 0);
         //glBindVertexArray(0);

         //::cast < command_buffer > pcommandbuffer = pgpucommandbuffer;

         //VkDeviceSize offsets[] = { 0 };

         //::cast < memory_buffer > pbufferVertex = m_pbufferVertex;

         //vkCmdBindVertexBuffers(
         //   pcommandbuffer->m_vkcommandbuffer,
         //   0, 1,
         //   &pbufferVertex->m_vkbuffer, offsets);

         //if (m_pbufferIndex)
         //{

         //   ::cast < memory_buffer > pbufferIndex = m_pbufferIndex;

         //   vkCmdBindIndexBuffer(
         //      pcommandbuffer->m_vkcommandbuffer,
         //      pbufferIndex->m_vkbuffer, 0, VK_INDEX_TYPE_UINT16);

         //}

      }
      else
      {

         glBindVertexArray(m_gluVao);
         GLCheckError("");

      }

   }


   void model_buffer::draw2(::gpu::command_buffer* pgpucommandbuffer)
   {

      GLenum mode = GL_TRIANGLES;

      auto pshaderBound = m_pgpucontext->m_pshaderBound;

      if (pshaderBound)
      {

         auto etopology = pshaderBound->m_etopology;

         mode = ::opengl::as_gl_draw_mode(etopology);

      }

      if (m_pbufferVertex)
      {

         if (m_pbufferIndex)
         {

            GLenum etype;

            if (m_iIndexTypeSize == 1)
            {

               etype = GL_UNSIGNED_BYTE;

            }
            else if(m_iIndexTypeSize == 2)
            {

               etype = GL_UNSIGNED_SHORT;

            }
            else
            {

               etype = GL_UNSIGNED_INT;

            }
            
            glDrawElements(mode, m_iIndexCount, etype, 0);
            GLCheckError("");

         }
         else
         {

            glDrawArrays(mode, 0, m_iVertexCount);
            GLCheckError("");

         }

      }
      else
      {

         glDrawArrays(mode, 0, m_iVertexCount);
         GLCheckError("");

      }

   }


   void model_buffer::draw_lines(::gpu::command_buffer* pgpucommandbuffer)
   {

      if (m_pbufferVertex)
      {

         //if (m_pbufferIndex)
         //{

         //   GLenum etype;

         //   if (m_iSizeIndex == 1)
         //   {

         //      etype = GL_UNSIGNED_BYTE;

         //   }
         //   else if (m_iSizeIndex == 2)
         //   {

         //      etype = GL_UNSIGNED_SHORT;

         //   }
         //   else
         //   {

         //      etype = GL_UNSIGNED_INT;

         //   }

         //   glDrawElements(GL_TRIANGLES, m_iIndexCount, etype, 0);
         //   GLCheckError("");

         //}
         //else
         {

            glDrawArrays(GL_LINES, 0, m_iVertexCount);
            GLCheckError("");

         }

      }
      else
      {

         glDrawArrays(GL_LINES, 0, m_iVertexCount);
         GLCheckError("");

      }

   }


   void model_buffer::unbind(::gpu::command_buffer* pgpucommandbuffer)
   {

      if (m_pbufferVertex)
      {

         if (m_pbufferIndex)
         {

            m_pbufferIndex->unbind();

         }

         m_pbufferVertex->unbind();

      }

      glBindVertexArray(0);

   }


} // namespace gpu_opengl



