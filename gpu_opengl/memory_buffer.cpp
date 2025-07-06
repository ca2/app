// Created by camilo on 2025-06-11 00:50 <3ThomasBorregaardSørensen!!
#include "framework.h"
#include "context.h"
#include "device.h"
#include "memory_buffer.h"
#include "model_buffer.h"


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


   void memory_buffer::on_initialize_memory_buffer()
   {

      memsize size;

      if (m_etype == ::gpu::memory_buffer::e_type_vertex_buffer)
      {

         m_iType = GL_ARRAY_BUFFER;

         size = m_pmodelbuffer->m_iVertexCount * m_pmodelbuffer->m_iVertexTypeSize;

      }
      else if (m_etype == ::gpu::memory_buffer::e_type_index_buffer)
      {

         m_iType = GL_ELEMENT_ARRAY_BUFFER;

         size = m_pmodelbuffer->m_iIndexCount * m_pmodelbuffer->m_iIndexTypeSize;

      }
      else
      {

         throw not_implemented();

      }

      glGenBuffers(1, &m_gluVbo);                            // Create a buffer ID
      GLCheckError("");
      glBindBuffer(m_iType, m_gluVbo);              // Bind as a vertex buffer
      GLCheckError("");

      //GLsizeiptr size = 1024; // e.g., 1 KB buffer
      auto i2 = GL_DYNAMIC_DRAW;
      if (size > 1024)
      {
         i2 = GL_STATIC_DRAW;
      }
      glBufferData(m_iType, (GLsizeiptr) size, NULL, i2); // just allocate space
      GLCheckError("");


      glBindBuffer(m_iType, 0);
      GLCheckError("");

      
   }


   bool memory_buffer::is_initialized() const
   {

      return m_gluVbo != 0;

   }


   //void memory_buffer::assign(const void* pData, memsize size)
   //{

   //   if (m_vkdevicememory == VK_NULL_HANDLE || m_vkbuffer == VK_NULL_HANDLE)
   //   {

   //      throw ::exception(error_wrong_state, "Buffer not initialized");

   //   }

   //   void* data;

   //   vkMapMemory(m_pcontext->logicalDevice(), m_vkdevicememory, 0, size, 0, &data);

   //   memcpy(data, pData, size);

   //   vkUnmapMemory(m_pcontext->logicalDevice(), m_vkdevicememory);

   //}


   //void memory_buffer::assign(const ::block& block)
   //{

   //   assign(block.data(), block.size()); 

   //}


   //void* memory_buffer::_map(memsize start, memsize count)
   //{

   //   glBindBuffer(m_iType, m_gluVbo);
   //   GLCheckError("");

   //   void* data = glMapBuffer(m_iType, GL_WRITE_ONLY);
   //   GLCheckError("");
   //  
   //   m_pMap = data;

   //   glBindBuffer(m_iType, 0);
   //   GLCheckError("");


   //   return data;

   //}


   //void memory_buffer::_unmap()
   //{

   //   //if (!m_pMap)
   //   //{

   //   //   return;

   //   //}

   //   glBindBuffer(m_iType, m_gluVbo);
   //   GLCheckError("");

   //   glUnmapBuffer(m_iType); // Important!
   //   GLCheckError("");

   //   glBindBuffer(m_iType, 0);
   //   GLCheckError("");

   //   m_pMap = nullptr;

   //}


   void* memory_buffer::_map(memsize start, memsize count)
   {

      //glBindBuffer(m_iType, m_gluVbo);
      //GLCheckError("");

      void* data = glMapBuffer(m_iType, GL_WRITE_ONLY);
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

      glBindBuffer(m_iType, m_gluVbo);
      GLCheckError("");

   }



   void memory_buffer::unbind()
   {

      //glBindBuffer(m_iType, 0);
      //GLCheckError("");

   }

} // namespace gpu_opengl



