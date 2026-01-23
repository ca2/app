// Created by camilo on 2025-06-11 00:50 <3ThomasBorregaardSørensen!!
#include "framework.h"
#include "_gpu_opengl.h"
#include "context.h"
#include "device.h"
#include "memory_buffer.h"
#include "model_buffer.h"
#include "renderer.h"
#include "bred/gpu/context_lock.h"
#include "bred/gpu/frame.h"


namespace gpu_opengl
{


   memory_buffer::memory_buffer()
   {

      m_gluVbo = 0;

   }


   memory_buffer::~memory_buffer()
   {

      glDeleteBuffers(1, &m_gluVbo);

   }


   void memory_buffer::on_initialize_memory_buffer(const ::block &block)
   {

      if (m_pmodelbuffer->m_pmodeldatabase2->is_dummy())
      {

         return;

      }

//      ::cast<::gpu_opengl::model_buffer> pmodelbuffer = m_pmodelbuffer;
//
//      auto vao = pmodelbuffer->m_gluVao;

//      ::gpu::context_lock contextlock(m_pcontext);

//      glBindVertexArray(vao);

      memsize size;

      if (m_etype == ::gpu::memory_buffer::e_type_vertex_buffer)
      {

         m_iType = GL_ARRAY_BUFFER;

         size = m_pmodelbuffer->m_pmodeldatabase2->vertex_bytes();

      }
      else if (m_etype == ::gpu::memory_buffer::e_type_index_buffer)
      {

         m_iType = GL_ELEMENT_ARRAY_BUFFER;

         size = m_pmodelbuffer->m_pmodeldatabase2->index_bytes();

      }
      else
      {

         throw not_implemented();

      }
      
      glGenBuffers(1, &m_gluVbo);                            // Create a buffer ID
      
      GLCheckError("");

      glBindBuffer(m_iType, m_gluVbo);              // Bind as a vertex buffer
      
      GLCheckError("");
      
      auto iGlStaticDraw = GL_STATIC_DRAW;
      
      auto iGlDynamicDraw = GL_DYNAMIC_DRAW;

      //GLsizeiptr size = 1024; // e.g., 1 KB buffer
      auto usageFlags = block.data() ? iGlStaticDraw : iGlDynamicDraw;
      
      glBufferData(m_iType, (GLsizeiptr)size, block.data(), usageFlags); // just allocate space
      GLCheckError("");
      
      glBindBuffer(m_iType, 0);
      
      GLCheckError("");

   }


   void memory_buffer::on_set_memory_buffer(const ::block &block)
   {

      if (m_pmodelbuffer->m_pmodeldatabase2->is_dummy())
      {

         return;

      }

//      m_pmodelbuffer->bind2(m_pcontext->m_pgpurenderer->getCurrentCommandBuffer2(::gpu::current_frame()));

      _on_set_memory_buffer(block);

//      m_pmodelbuffer->unbind(m_pmodelbuffer->m_pcommandbufferLoading);

   }


   void memory_buffer::_on_set_memory_buffer(const ::block &block)
   {

      bind();
      
      auto data = block.data();
      
      auto size = block.size();

      glBufferData(m_iType, (GLsizeiptr)size, data, GL_DYNAMIC_DRAW); // just allocate space
      GLCheckError("");
      
      unbind();

   }


   bool memory_buffer::is_initialized() const
   {

      return m_gluVbo != 0;

   }


   void memory_buffer::_assign(const ::block &block)
   {

      glBufferSubData(m_iType, 0, block.size(), block.data());
      GLCheckError("");

   }


   void* memory_buffer::_map(memsize start, memsize count)
   {

      void* data = glMapBuffer(m_iType, GL_READ_ONLY);

      GLCheckError("");

      m_pMap = data;

      return data;

   }


   void memory_buffer::_unmap()
   {

      glUnmapBuffer(m_iType); // Important!

      GLCheckError("");

      //glBindBuffer(m_iType, 0);
      
      //GLCheckError("");

      m_pMap = nullptr;

   }


   void memory_buffer::bind()
   {
      
      if(m_gluVbo <= 0)
      {
         
         ::string strMessage;
         
         strMessage = "memory_buffer::bind vbo is null";
         
         warning(strMessage);
         
         throw ::exception(error_wrong_state, strMessage);
         
      }

      glBindBuffer(m_iType, m_gluVbo);

      GLCheckError("");

   }


   void memory_buffer::unbind()
   {

      glBindBuffer(m_iType, 0);
      
      GLCheckError("");

   }


} // namespace gpu_opengl



