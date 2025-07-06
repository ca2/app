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



   void memory_buffer::initialize_memory_buffer_with_model_buffer(::gpu::model_buffer* pmodelbuffer, memsize size, enum_type etype)
   {

      m_pmodelbuffer = pmodelbuffer;

      m_pcontext = pmodelbuffer->m_pgpucontext;

      m_size = size;

      m_etype = etype;

      on_initialize_memory_buffer();

   }


   void memory_buffer::on_initialize_memory_buffer()
   {


   }


   bool memory_buffer::is_initialized() const
   {

      return false;

   }


   void memory_buffer::assign(const void* pData, memsize size)
   {

      if (!is_initialized())
      {

         throw ::exception(error_wrong_state, "Buffer not initialized");

      }

      //void* data;

      map(0, size);

      //vkMapMemory(m_pcontext->logicalDevice(), m_vkdevicememory, 0, size, 0, &data);

      memcpy(m_pMap, pData, size);

      unmap();

      //vkUnmapMemory(m_pcontext->logicalDevice(), m_vkdevicememory);

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

      //void* data;

      _map(0, size);

      //vkMapMemory(m_pcontext->logicalDevice(), m_vkdevicememory, 0, size, 0, &data);

      memcpy(m_pMap, pData, size);

      _unmap();

      //vkUnmapMemory(m_pcontext->logicalDevice(), m_vkdevicememory);

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

      return __map(start, count);

   }


   void memory_buffer::_unmap()
   {

      return __unmap();

   }


   void* memory_buffer::__map(memsize start, memsize count)
   {

      return nullptr;

   }


   void memory_buffer::__unmap()
   {


   }


   void memory_buffer::bind()
   {


   }


   void memory_buffer::unbind()
   {


   }



} // namespace gpu_vulkan



