// Created by camilo on 2025-06-11 01:08 <3ThomasBorregaardSørensen!!
#include "framework.h"
#include "_gpu_opengl.h"
#include "command_buffer.h"
#include "context.h"
#include "device.h"
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

      //m_gluVao = 0;

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

   }


   void model_buffer::_defer_apply_input_layout(struct vertex_array_object & vertexarrayobject)
   {

      ::cast < input_layout > pinputlayout = m_pinputlayout;

      if(::is_set(pinputlayout))
      {
         
         //m_pinputlayout = pgpuinputlayout;
         
         ::cast < memory_buffer > pbufferVertex = m_pbufferVertex;
         
         ::cast < memory_buffer > pbufferIndex = m_pbufferIndex;
         
         if (pbufferVertex)
         {
            
            ::cast < input_layout > pinputlayout = m_pinputlayout;
            
            pinputlayout->__do_opengl_vao_vbo_and_ebo_input_layout(
                                                                   vertexarrayobject.m_gluVertexArrayObject,
                                                                   pbufferVertex->m_gluVbo,
                                                                   pbufferIndex ? pbufferIndex->m_gluVbo : 0
                                                                   );
            
            vertexarrayobject.m_bPendingInputLayout = false;
            
         }
         
      }

   }


   void model_buffer::bind2(::gpu::command_buffer* pgpucommandbuffer)
   {
      
      auto gluVertexArrayObject = vertex_array_object();
      
      if(gluVertexArrayObject <= 0)
      {
         
         ::string strMessage;
         
         strMessage = "model_buffer::bind2 VAO is null";
         
         warning(strMessage);
         
         throw ::exception(error_wrong_state, strMessage);
         
      }

      glBindVertexArray(gluVertexArrayObject);
      GLCheckError("");

   }


   GLuint model_buffer::vertex_array_object()
   {
 
      auto poperatingsystemgpucontext = m_pgpucontext->m_pgpudevice->current_operating_system_gpu_context();
      
      if(::is_null(poperatingsystemgpucontext))
      {
         
         throw ::exception(error_wrong_state);
         
      }
      
      auto & vertexarrayobject = m_mapContextVertexArrayObject[poperatingsystemgpucontext];
      
      auto & gluVertexArrayObject = vertexarrayobject.m_gluVertexArrayObject;
      
      if(gluVertexArrayObject == 0)
      {
         glGenVertexArrays(1, &gluVertexArrayObject);
         GLCheckError("");
         
         if(gluVertexArrayObject == 74)
         {
            
            information("gluVertexArrayObject == 74");
         
         }
         
         //glBindVertexArray(vertexarrayobject.m_gluVertexArrayObject);
         //GLCheckError("");
         
   //      ::cast < memory_buffer > pbufferVertex = m_pbufferVertex;
   //
   //      ::cast < memory_buffer > pbufferIndex = m_pbufferIndex;
   //
   //      if(::is_set(pbufferVertex))
   //      {
   //
   //         ::cast < input_layout > pinputlayout = m_pinputlayout;
   //
   //         pinputlayout->__do_opengl_vao_vbo_and_ebo_input_layout(
   //                                                gluVertexArrayObject,
   //                                                                pbufferVertex->m_gluVbo,
   //                                                                pbufferIndex ? pbufferIndex->m_gluVbo : 0
   //                                                                );
   //
   //      }
         
         //glBindVertexArray(0);
         //GLCheckError("");
      }
      
      if(m_pinputlayout && vertexarrayobject.m_bPendingInputLayout)
      {
         
         _defer_apply_input_layout(vertexarrayobject);
        
      }
      
      return gluVertexArrayObject;

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

            if (m_pmodeldatabase2->index_type_size() == 1)
            {

               etype = GL_UNSIGNED_BYTE;

            }
            else if (m_pmodeldatabase2->index_type_size() == 2)
            {

               etype = GL_UNSIGNED_SHORT;

            }
            else
            {

               etype = GL_UNSIGNED_INT;

            }
            
            auto iIndexCount = m_pmodeldatabase2->index_count();
            
            glDrawElements(mode, (int) iIndexCount, etype, 0);
            GLCheckError("");

         }
         else
         {
            
            auto iVertexCount = m_pmodeldatabase2->vertex_count();

            glDrawArrays(mode, 0, (int) iVertexCount);
            GLCheckError("");

         }

      }
      else
      {
         
         auto iVertexCount = m_pmodeldatabase2->vertex_count();

         glDrawArrays(mode, 0, iVertexCount);
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

            glDrawArrays(GL_LINES, 0, m_pmodeldatabase2->vertex_count());
            GLCheckError("");

         }

      }
      else
      {

         glDrawArrays(GL_LINES, 0, m_pmodeldatabase2->vertex_count());
         GLCheckError("");

      }

   }


   void model_buffer::unbind(::gpu::command_buffer* pgpucommandbuffer)
   {

//      if (m_pbufferVertex)
//      {
//
//         if (m_pbufferIndex)
//         {
//
//            m_pbufferIndex->unbind();
//
//         }
//
//         m_pbufferVertex->unbind();
//
//      }

      glBindVertexArray(0);
      GLCheckError("");

   }


} // namespace gpu_opengl



