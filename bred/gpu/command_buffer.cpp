// Created by camilo on 2025-06-23 00:16 <3ThomasBorregaardSørensen!!
#include "framework.h"
#include "command_buffer.h"
#include "context.h"
#include "frame.h"
#include "queue.h"
#include "renderer.h"
#include "render_target.h"
#include "bred/graphics3d/renderable.h"



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


   ::interlocked_long_long g_iGpuCommandBufferSerialSeed;


   command_buffer::command_buffer()
   {
      m_iSerial = g_iGpuCommandBufferSerialSeed++;
      if (m_iSerial == 74)
      {

         ::information("m_iSerial == 74");

      }
      m_ecommandbuffer = e_command_buffer_none;
      m_bLoadingCommandBuffer = false;
      m_iCommandBufferFrameIndex = -1;
   }


   command_buffer::~command_buffer()
   {


   }


   void command_buffer::begin_render(::gpu::shader * pgpushader, ::gpu::texture * pgputextureTarget)
   {

      auto pgpucontext = m_pgpurendertarget.m_p->m_pgpurenderer.m_p->m_pgpucontext.m_p;

      pgpucontext->begin_render(this, pgputextureTarget);

      pgpucontext->defer_bind2(this, pgpushader, pgputextureTarget);

   }


   void command_buffer::set_shader(::gpu::shader *pgpushader)
   {

      m_pgpurendertarget->m_pgpurenderer->m_pgpucontext->defer_bind3(this, pgpushader);

      // pgpushader->bind(this, pgputextureTarget);

   }


   void command_buffer::set_block3(::gpu::block *pgpublock)
   {

      auto pgpucontext = m_pgpurendertarget->m_pgpurenderer->m_pgpucontext;

      auto pgpushader = pgpucontext->m_pshaderBound;

      pgpushader->bind_block(this, pgpublock);

   }


   void command_buffer::bind_slot_set(int iSet, ::gpu::binding_slot_set * pgpubindingslotset)
   {

      auto pgpucontext = m_pgpurendertarget->m_pgpurenderer->m_pgpucontext;

      auto pgpushader = pgpucontext->m_pshaderBound;

      pgpushader->bind_slot_set(this, iSet, pgpubindingslotset);


   }


   void command_buffer::set_source(::gpu::texture * pgputexture)
   {

      auto pgpucontext = m_pgpurendertarget->m_pgpurenderer->m_pgpucontext;

      auto pgpushader = pgpucontext->m_pshaderBound;

      pgpushader->bind_source(this, pgputexture);

   }


   void command_buffer::set_source(::gpu::pixmap *pgpupixmap)
   {

      auto pgpucontext = m_pgpurendertarget->m_pgpurenderer->m_pgpucontext;

      auto pgpushader = pgpucontext->m_pshaderBound;

      pgpushader->bind_source(this, pgpupixmap);

   }


   void command_buffer::set_model2(::graphics3d::renderable * prenderable)
   {

      prenderable->bind2(this);

   }


   void command_buffer::draw(::graphics3d::renderable *prenderable)
   {

      prenderable->draw_model(this);

   }


   void command_buffer::set_model_view_projection(const floating_matrix4 & model, const floating_matrix4 & view,
                                    const floating_matrix4 & projection)
   {

      auto pgpucontext = m_pgpurendertarget->m_pgpurenderer->m_pgpucontext;

      auto pgpushader = pgpucontext->m_pshaderBound;

      pgpushader->setModelViewProjection(model, view, projection);

   }



   //void command_buffer::unbind(::graphics3d::renderable *prenderable)
   //{
   //   
   //   prenderable->unbind(this); 
   //
   //}


   void command_buffer::end_render()
   {


   }


   //void command_buffer::set_binding_set(::gpu::binding_set_pointer pbindingset)
   //{

   //   m_pbindingsetCurrent = pbindingset;

   //}


   //::pointer <command_buffer >renderer::beginSingleTimeCommands()
   //{

   //   ::pointer <command_buffer > pcommandbuffer;

   //   ødefer_construct_new(pcommandbuffer);

   //   ::cast < device > pdevice= m_pgpucontext->m_pgpudevice;

   //   pcommandbuffer->initialize_command_buffer(pdevice);

   //   return pcommandbuffer;

   //}


   void command_buffer::initialize_command_buffer(::gpu::render_target* pgpurendertarget, ::gpu::queue * pqueue, enum_command_buffer ecommandbuffer)
   {

      m_pgpurendertarget = pgpurendertarget;

      m_pgpuqueue = pqueue;

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

      m_pgpurendertarget->m_pgpurenderer->m_pgpucontext->set_viewport(this, rectangle);
   }


   void command_buffer::set_scissor(const ::int_rectangle& rectangle)
   {

      m_pgpurendertarget->m_pgpurenderer->m_pgpucontext->set_scissor(this, rectangle);

   }

   
   void command_buffer::reset()
   {


   }


   ::gpu::fence * command_buffer::insert_gpu_fence()
   {

      øconstruct(m_pgpufence);

      m_pgpufence->initialize_gpu_fence(m_pgpurendertarget->m_pgpurenderer->m_pgpucontext);

      return m_pgpufence;

   }


   //void command_buffer::set_primitive_topology_triangle_strip()
   //{


   //}


   void command_buffer::draw_int_a_count(int a)
   {


   }


   void command_buffer::draw_vertexes(int iVertexCount)
   {


   }


   void command_buffer::draw_indexes(int iIndexCount)
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


   CLASS_DECL_BRED::gpu::command_buffer * current_command_buffer()
   {

      auto pframe = ::gpu::current_frame();

      if (::is_null(pframe))
      {

         return nullptr;

      }

      auto pgpucommandbuffer = pframe->m_pgpucommandbuffer;

      if (::is_null(pgpucommandbuffer))
      {

         return nullptr;

      }


      return pgpucommandbuffer;

   }


} // namespace gpu



