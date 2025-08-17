// Created by camilo on 2025-08-16 01:20 <3ThomasBorregaardSørensen!!
#include "framework.h"
#include "device.h"
#include "frame_storage.h"
#include "memory_buffer.h"


namespace gpu
{


   frame_storage::frame_storage()
   {


   }


   frame_storage::~frame_storage()
   {


   }


   void frame_storage::initialize_gpu_frame_storage(::gpu::device* pgpudevice)
   {

      m_pgpudevice = pgpudevice;

   }


   void frame_storage::map_allocate(::gpu::memory_buffer* pgpumemorybuffer, int size)
   {

      if (size > m_iBufferSize)
      {

         throw ::exception(error_wrong_state);

      }

      bool bDiscard;

      if (size > m_iBufferSize - m_iBufferOffset)
      {

         bDiscard = true;

         m_iBuffer++;

      }
      else
      {

         bDiscard = false;

      }

      auto& pbuffer = m_buffera.ø(m_iBuffer);

      if (!pbuffer)
      {

         øconstruct(pbuffer);

         pbuffer->initialize_memory_buffer_with_context(
            pgpumemorybuffer->m_pcontext, 
            m_iBufferSize,
            ::gpu::memory_buffer::e_type_shared_dynamic_vertex_buffer);

      }

      //m_iBufferOffset = m_iBufferOffset;

      //m_pmodelbuffer->m_strDebugString.formatf("24*th:%d", m_iBufferOffset / 24);

      //m_pbuffer = pbuffer;
      //buffer buffer;

      // ::cast < memory_buffer > pmemorybuffer = pgpumemorybuffer;

      pgpumemorybuffer->_complete_map_allocate(pbuffer, this, size);
      //pgpumemorybuffer->m_presource = resource.m_presource;
      //pgpumemorybuffer->m_iBufferOffset = m_iBufferOffset;
      //pgpumemorybuffer->m_iSizeMapped = size;
      //pgpumemorybuffer->m_pMap = 

      m_iBufferOffset += size;

      //return buffer;


   }


   void frame_storage::on_end_frame()
   {

      for (auto & pair1 : m_mapObject)
      {

         for (auto pair : pair1.element2())
         {

            auto& pobject = pair.element2();

            try
            {

               pobject->on_end_frame();

            }
            catch (...)
            {


            }


         }

      }

   }


   void frame_storage::object::on_end_frame()
   {


   }



   //void* frame_storage::allocate(int size)
   //{

   //   return nullptr;

   //}


} // namespace gpu



