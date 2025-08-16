// From gpu_vulkan/memory_buffer.cpp by
// camilo on 2025-07-01 12:38 <3ThomasBorregaardSørensen!!
#include "framework.h"
#include "context.h"
#include "device.h"
#include "memory_buffer.h"
#include "model_buffer.h"


namespace gpu
{


   memory_buffer::memory_buffer()
   {

      m_bDynamic = false;
      m_pmodelbuffer = nullptr;
      m_etype = e_type_none;
      m_pcontext = nullptr;
      //m_vkbuffer = VK_NULL_HANDLE;
      //m_vkdevicememory = VK_NULL_HANDLE;
      m_pMap = nullptr;
   }


   memory_buffer::~memory_buffer()
   {
      //if (m_vkbuffer != VK_NULL_HANDLE)
      //{
      //   vkDestroyBuffer(m_pcontext->logicalDevice(), m_vkbuffer, nullptr);
      //   m_vkbuffer = VK_NULL_HANDLE;
      //}
      //if (m_vkdevicememory != VK_NULL_HANDLE)
      //{
      //   vkFreeMemory(m_pcontext->logicalDevice(), m_vkdevicememory, nullptr);
      //   m_vkdevicememory = VK_NULL_HANDLE;
      //}
   }


   void memory_buffer::initialize_memory_buffer_with_context(::gpu::context* pcontext, memsize size, enum_type etype)
   {

      m_pmodelbuffer = nullptr;

      m_pcontext = pcontext;

      m_size = size;

      m_etype = etype;

      on_initialize_memory_buffer();

   }



   void memory_buffer::initialize_memory_buffer_with_model_buffer(::gpu::model_buffer* pmodelbuffer, memsize size, enum_type etype, bool bDynamic)
   {

      m_pmodelbuffer = pmodelbuffer;

      m_pcontext = pmodelbuffer->m_pgpucontext;

      m_size = size;

      m_etype = etype;

      m_bDynamic = bDynamic;

      on_initialize_memory_buffer(nullptr, size);

   }

   
   void memory_buffer::static_initialize_memory_buffer_with_context(::gpu::context* pcontext, const void * data, memsize size, enum_type etype)
   {

      m_pmodelbuffer = nullptr;

      m_pcontext = pcontext;

      m_size = size;

      m_etype = etype;

      on_initialize_memory_buffer(data, size);

   }



   void memory_buffer::static_initialize_memory_buffer_with_model_buffer(::gpu::model_buffer* pmodelbuffer, const void * data, memsize size, enum_type etype)
   {

      m_pmodelbuffer = pmodelbuffer;

      m_pcontext = pmodelbuffer->m_pgpucontext;

      m_size = size;

      m_etype = etype;

      on_initialize_memory_buffer(data, size);

   }


   void memory_buffer::on_initialize_memory_buffer(const void * dataStatic, memsize sizeStatic)
   {


   }


   void memory_buffer::on_set_memory_buffer(const void* dataStatic, memsize sizeStatic)
   {

      auto p = map(0, sizeStatic);

      memcpy(p, dataStatic, sizeStatic);

      unmap();


   }


   void memory_buffer::_on_set_memory_buffer(const void* dataStatic, memsize sizeStatic)
   {


   }


   bool memory_buffer::is_initialized() const
   {

      return false;

   }

   
   memsize memory_buffer::total_size_in_bytes() const
   {

      if (m_etype == e_type_vertex_buffer)
      {

         auto size = type_size() * m_pmodelbuffer->m_iVertexCount;

         return size;

      }
      else if (m_etype == e_type_index_buffer)
      {

         auto size = type_size() * m_pmodelbuffer->m_iIndexCount;

         return size;

      }
      else if (m_etype == e_type_constant_buffer)
      {

         return m_size;

      }
      else
      {

         throw ::not_implemented();

      }

   }


   memsize memory_buffer::type_size() const
   {

      if (m_etype == e_type_vertex_buffer)
      {

         return m_pmodelbuffer->m_iVertexTypeSize;

      }
      else if (m_etype == e_type_index_buffer)
      {

         return m_pmodelbuffer->m_iIndexTypeSize;

      }
      else if (m_etype == e_type_constant_buffer)
      {

         throw error_not_found;

      }
      else
      {

         throw error_not_found;

      }

   }


   void memory_buffer::assign(const void* data, memsize size)
   {

      if (!is_initialized())
      {

         throw ::exception(error_wrong_state, "Buffer not initialized");

      }

      bind();

      _assign(data, size);

      unbind();

   }


   void memory_buffer::assign(const ::block& block)
   {

      assign(block.data(), block.size());

   }


   void memory_buffer::_assign(const void* pData, memsize size)
   {

      if (!is_initialized())
      {

         throw ::exception(error_wrong_state, "Buffer not initialized");

      }

      _map(0, size);

      memcpy(m_pMap, pData, size);

      _unmap();

   }


   void memory_buffer::_assign(const ::block& block)
   {

      _assign(block.data(), block.size());

   }


   void* memory_buffer::map()
   {

      return map(0, m_size);

   }


   void* memory_buffer::map(memsize start, memsize count)
   {

      if (!count)
      {

         throw ::exception(error_wrong_state);

      }

      bind();

      if (!m_pMap)
      {

         _map(start, count);

         //vkMapMemory(
         //   m_pcontext->logicalDevice(),
         //   m_vkdevicememory,
         //   start,
         //   count > 0 ? count : (m_size + count + 1),
         //   0,
         //   &m_pMap);

      }

      return m_pMap;

   }


   void memory_buffer::unmap()
   {

      if (!m_pMap)
      {

         return;

      }

      _unmap();

      unbind();

      m_pMap = nullptr;

   }


   void* memory_buffer::_map(memsize start, memsize count)
   {

      throw ::interface_only();

      return nullptr;
      
   }


   void memory_buffer::_unmap()
   {

      throw ::interface_only();

   }


   //void* memory_buffer::__map(memsize start, memsize count)
   //{

   //   return nullptr;

   //}


   //void memory_buffer::__unmap()
   //{


   //}


   void memory_buffer::bind()
   {


   }


   void memory_buffer::unbind()
   {


   }



} // namespace gpu_vulkan



