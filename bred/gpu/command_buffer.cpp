// Created by camilo on 2025-06-23 00:16 <3ThomasBorregaardSørensen!!
#include "framework.h"
#include "command_buffer.h"
#include "frame.h"
#include "render_target.h"


namespace gpu
{


   scoped_command_buffer::scoped_command_buffer(::gpu::command_buffer* pcommandbufferIn)
   {

      m_pcommandbufferOut = ::gpu::current_frame()->m_pgpucommandbuffer;
      m_pcommandbufferIn = pcommandbufferIn;
      ::gpu::current_frame()->m_pgpucommandbuffer = m_pcommandbufferIn;


   }

   scoped_command_buffer::~scoped_command_buffer()
   {

      ::gpu::current_frame()->m_pgpucommandbuffer = m_pcommandbufferOut;

   }




   command_buffer::command_buffer()
   {
      m_ecommandbuffer = e_command_buffer_none;
      m_bLoadingCommandBuffer = false;
      m_iFrameIndex = -1;
   }


   command_buffer::~command_buffer()
   {


   }


   //::pointer <command_buffer >renderer::beginSingleTimeCommands()
   //{

   //   ::pointer <command_buffer > pcommandbuffer;

   //   ødefer_construct_new(pcommandbuffer);

   //   ::cast < device > pdevice= m_pgpucontext->m_pgpudevice;

   //   pcommandbuffer->initialize_command_buffer(pdevice);

   //   return pcommandbuffer;

   //}


   void command_buffer::initialize_command_buffer(::gpu::render_target* pgpurendertarget, enum_command_buffer ecommandbuffer)
   {

      m_pgpurendertarget = pgpurendertarget;

      m_ecommandbuffer = ecommandbuffer;

   }


   void command_buffer::begin_command_buffer(bool bOneTime)
   {


   }


   void command_buffer::submit_command_buffer(::gpu::layer * pgpulayer)
   {


   }


   void command_buffer::wait_commands_to_execute()
   {


   }


   void command_buffer::set_viewport(const ::int_rectangle& rectangle)
   {


   }


   void command_buffer::set_scissor(const ::int_rectangle& rectangle)
   {



   }

   
   void command_buffer::reset()
   {


   }


   //void command_buffer::set_primitive_topology_triangle_strip()
   //{


   //}


   void command_buffer::draw(int a)
   {


   }


   void command_buffer::draw_vertices(int iVertexCount)
   {


   }


   void command_buffer::draw_indices(int iIndexCount)
   {


   }


   void command_buffer::draw(::gpu::pixmap* ppixmap)
   {


   }


   void command_buffer::set_render_target()
   {


   }



   //void command_buffer::wait_for_gpu()
   //{

   //   //const UINT64 fenceValue = ++m_fenceValue;

   //   //prenderer->m_pcommandqueue->Signal(m_pfence, m_fenceValue);

   //   if (m_pfence->GetCompletedValue() < m_fenceValue)
   //   {

   //      m_pfence->SetEventOnCompletion(m_fenceValue, m_hFenceEvent);

   //      ::WaitForSingleObject(m_hFenceEvent, INFINITE);

   //   }

   //   //m_iCurrentFrame2 = (m_iCurrentFrame2 + 1) % get_frame_count();


   //}


   //void command_buffer::reset()
   //{

   //   auto pcommandallocator = m_pcommandallocator;

   //   HRESULT hrResetCommandAllocator = pcommandallocator->Reset();

   //   ::defer_throw_hresult(hrResetCommandAllocator);

   //   m_pcommandlist->Reset(pcommandallocator, nullptr);

   //}




} // namespace gpu



