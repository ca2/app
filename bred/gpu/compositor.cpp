// Created by camilo on 2025-06-18 19:58 <3ThomasBorregaardSørensen!!
#include "framework.h"
#include "bred_approach.h"
#include "compositor.h"
#include "context.h"
#include "device.h"
#include "frame.h"
#include "layer.h"
#include "renderer.h"
#include "render_target.h"
#include "acme/platform/application.h"


namespace gpu
{


   compositor::compositor()
   {

   }


   compositor::~compositor()
   {


   }

   
   void compositor::set_gpu_context(::gpu::context* pgpucontextCompositor)
   {

      m_pgpucontextCompositor2 = pgpucontextCompositor;

      on_set_gpu_context();

   }


   void compositor::on_set_gpu_context()
   {



   }


   //void compositor::defer_yield_gpu_context()
   //{



   //}


   void compositor::defer_yield_gpu_context(const ::int_rectangle & rectanglePlacement)
   {

       if (!m_pgpucontextCompositor2)
       {

           auto pgpuapproach = application()->get_gpu_approach();

           //if (!m_puserinteraction)
           //{

           //   m_puserinteraction = dynamic_cast <::user::interaction*>(application()->m_pacmeuserinteractionMain.m_p);

           //}

           //ASSERT(m_puserinteraction);

           auto pgpudevice = pgpuapproach->get_gpu_device();

           auto pgpucontext = pgpudevice->create_draw2d_context(::gpu::e_output_gpu_buffer, rectanglePlacement.size());

           //::gpu::start_context_t startcontext;
           //startcontext.m_pparticle = this;
           //startcontext.m_pgpudevice = pgpudevice;
           //startcontext.m_eoutput = ::gpu::e_output_color_and_alpha_accumulation_buffers;
           //startcontext.m_rectanglePlacement = rectanglePlacement;

           auto pgpucontextNew = pgpucontext;

           set_gpu_context(pgpucontextNew);

           m_pgpucontextCompositor2->m_pgpucompositor = this;

           //pcontext = gpu_context();

           //pcontext->m_pgpucompositor = this;
           //m_pgpucontextCompositor = pgpudevice->start_gpu_output_context(
           //   this,
           //   ::gpu::e_output_color_and_alpha_accumulation_buffers,
           //   rectanglePlacement
           //);


       }
       else
       {

           m_pgpucontextCompositor2->set_placement(rectanglePlacement);

       }

       //return m_pgpucontextCompositor2;

   }





   ::gpu::context* compositor::gpu_context()
   {

       return m_pgpucontextCompositor2;

   }


   void compositor::start_gpu_layer(::gpu::frame* pgpuframe)
   {

      auto pcontext = gpu_context();

      auto pgpudevice = pcontext->m_pgpudevice;

      auto player = pgpudevice->next_layer(pcontext->m_pgpurenderer);

      pgpuframe->m_pgpulayer = player;

      player->m_pgpuframe = pgpuframe;

      player->layer_start();

   }


   ::gpu::frame * compositor::end_gpu_layer()
   {

      //auto prendererOutput = m_pgpucontextCompositor->m_pgpurenderer;

      //auto prendertarget = prendererOutput->m_pgpurendertarget;

      auto pcontext = gpu_context();

      auto player = pcontext->m_pgpudevice->current_layer();

      player->layer_end();

      return player->m_pgpuframe;

//      m_pgpucontextCompositor->copy(player->texture(), prendertarget->current_texture());

   }


   void compositor::gpu_layer_on_after_begin_render()
   {


   }


   void compositor::gpu_layer_on_before_end_render()
   {


   }


   void compositor::just_after_new_frame()
   {


   }


   void compositor::on_start_layer()
   {



   }


   void compositor::on_end_layer()
   {



   }


} // namespace gpu




