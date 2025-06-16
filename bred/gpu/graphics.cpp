// Created by camilo on 2025-05-31 15:32 <3ThomasBorregaardSørensen!!
#include "framework.h"
#include "graphics.h"
#include "acme/platform/application.h"
#include "aura/user/user/interaction.h"
#include "aura/windowing/window.h"
#include "bred/gpu/approach.h"
#include "bred/gpu/context.h"
#include "bred/gpu/device.h"
#include "bred/gpu/renderer.h"
#include "bred/gpu/render_target.h"
#include "bred/gpu/swap_chain.h"


namespace draw2d_gpu
{



   void thread_graphics(graphics* pgraphics)
   {

      ::get_task()->payload("draw2d_gpu::graphics") = pgraphics;

   }



   graphics::graphics()
   {

      //m_eoutputOnEndDraw = ::gpu::e_output_none;

   }


   graphics::~graphics()
   {


   }


   void graphics::initialize(::particle* pparticle)
   {

      ::draw2d::graphics::initialize(pparticle);

   }


   void graphics::on_begin_draw()
   {

      //thread_select();

      ::int_rectangle rectangle;

      if (!m_puserinteraction && m_papplication->m_gpu.m_bUseSwapChainWindow)
      {

         m_puserinteraction = dynamic_cast <::user::interaction*>(m_papplication->m_pacmeuserinteractionMain.m_p);

      }

      if (m_puserinteraction && !m_puserinteraction->host_rectangle().size().is_empty())
      {

         rectangle = m_puserinteraction->host_rectangle();

      }
      else
      {

         rectangle = { 0, 0, 1920, 1080 };

      }

      m_pgpucontextDraw2d->on_begin_draw_attach(this, rectangle);

   }


   //void graphics::create_end_draw()
   //{


   //}


   //::gpu::renderer* graphics::end_draw_renderer_output()
   //{

   //   ::cast < ::windowing::window > pwindow = m_puserinteraction->m_pacmewindowingwindow;

   //   if (!m_pgpucontextOutput)
   //   {

   //      __øconstruct(m_pgpucontextOutput);

   //      m_pgpucontextOutput = m_papplication->get_gpu()->get_device()->start_swap_chain_context(this, pwindow);

   //      //m_pgpucontextOutput->create_window_buffer(pwindow);

   //   }

   //   auto rectanglePlacement = pwindow->get_window_rectangle();

   //   m_pgpucontextOutput->set_placement(rectanglePlacement);

   //   auto prendererOutput = m_pgpucontextOutput->get_renderer(::gpu::e_scene_2d);

   //   prendererOutput->defer_update_renderer();

   //   return prendererOutput;

   //}


   void graphics::on_end_draw()
   {

      end_gpu_layer();

      m_pgpucontextDraw2d->on_end_draw_detach(this);

   }


   void graphics::start_gpu_layer(const ::int_rectangle& rectangleTarget)
   {

      m_pgpucontextDraw2d->m_pgpurendererOutput2->start_layer(rectangleTarget);

   }


   ::int_rectangle graphics::end_gpu_layer()
   {

      auto prendererOutput = m_pgpucontextDraw2d->m_pgpurendererOutput2;

      auto rectangleHostUpperLayer = prendererOutput->end_layer();

      return rectangleHostUpperLayer;

   }


   //void graphics::set_hint_window_output()
   //{

   //   m_eoutputOnEndDraw = ::gpu::e_output_swap_chain;

   //}



   void graphics::thread_select()
   {

      //if (thread_graphics() == this)
      //{

        // return;
      //}

      //wglMakeCurrent(m_hdc, m_hglrc);

      m_pgpucontextDraw2d->make_current();

      thread_graphics(this);

   }


   void graphics::_set(const ::geometry2d::matrix& matrix)
   {

      m_m1 = matrix;

   }


   void graphics::do_on_context(const ::procedure& procedure)
   {

      auto pgpudevice = m_papplication->get_gpu_approach()->get_gpu_device();

      auto pgpucontextMainWindow = pgpudevice->get_main_window_context();

      ::cast < ::user::interaction > puserinteraction = m_puserinteraction;

      auto pwindow = puserinteraction->window();

      auto rectangleWindow = pwindow->get_window_rectangle();

      pgpucontextMainWindow->set_placement(rectangleWindow);
      
      m_pgpucontextDraw2d->m_escene = ::gpu::e_scene_2d;

      pgpucontextMainWindow->top_send_on_context(
         m_pgpucontextDraw2d,
         m_egraphics & e_graphics_draw,
         procedure);

      //pgpudevice->start_stacking_layers();

      //pgpucontextMainWindow->top_send_on_context([this, pgpucontextMainWindow, procedure]()
      //   {

      //      m_pgpucontextDraw2d->send_on_context([this, procedure]()
      //         {

      //            if (m_egraphics & e_graphics_draw)
      //            {

      //               m_pgpucontextDraw2d->get_gpu_renderer()->do_on_frame([procedure]()
      //                  {

      //                     procedure();

      //                  });

      //            }
      //            else
      //            {

      //               procedure();

      //            }

      //         });

      //   });

   }


   void graphics::create_offscreen_graphics_for_swap_chain_blitting(const ::int_size& size)
   {

      create_memory_graphics(size);

   }


   void graphics::create_for_window_drawing(const ::int_size& size)
   {

      create_offscreen_graphics_for_swap_chain_blitting(size);

   }


} // namespace draw2d_gpu



