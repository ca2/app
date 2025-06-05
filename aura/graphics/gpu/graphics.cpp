// Created by camilo on 2025-05-31 15:32 <3ThomasBorregaardSørensen!!
#include "framework.h"
#include "graphics.h"
#include "acme/platform/application.h"
#include "aura/user/user/interaction.h"
#include "aura/windowing/window.h"
#include "aura/graphics/gpu/approach.h"
#include "aura/graphics/gpu/context.h"
#include "aura/graphics/gpu/end_draw.h"
#include "aura/graphics/gpu/device.h"
#include "aura/graphics/gpu/renderer.h"


namespace draw2d_gpu
{



   void thread_graphics(graphics* pgraphics)
   {

      ::get_task()->payload("draw2d_gpu::graphics") = pgraphics;

   }



   graphics::graphics()
   {

      m_eoutputOnEndDraw = ::gpu::e_output_none;

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

      thread_select();

      //g_z = -0.5;

      ::int_rectangle rectangle;

      if (!m_puserinteraction && m_papplication->m_bUseSwapChainWindow)
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

      bool bYSwap = m_papplication->m_bUseSwapChainWindow;

      //::vulkan::resize(rectangle.size(), bYSwap);

      //m_z = 0.f;

      if (!m_pgpucontext->m_pgpurenderer)
      {

         __øconstruct(m_pgpucontext->m_pgpurenderer);

         //m_pgpucontext->m_eoutput = ::gpu::e_output_color_and_alpha_accumulation_buffers;

         //m_pgpucontext->m_eoutput = ::gpu::e_output_gpu_buffer;

         //m_pgpucontext->m_pgpurenderer->initialize_renderer(m_pgpucontext, ::gpu::e_output_color_and_alpha_accumulation_buffers);

         m_pgpucontext->m_pgpurenderer->initialize_renderer(m_pgpucontext, ::gpu::e_output_gpu_buffer, ::gpu::e_scene_2d);

         //::cast < ::gpu_vulkan::renderer >prenderer = m_pgpucontext->m_prenderer;

         //prenderer->m_poffscreensampler->initialize_offscreen_sampler(m_pgpucontext);

         //prenderer->m_poffscreensampler->update({ (uint32_t)rectangle.width(),(uint32_t)rectangle.height() });

      }
      else
      {


      }

      if (m_egraphics == e_graphics_draw)
      {

         //::cast < ::gpu_vulkan::renderer > pgpurenderer = m_pgpucontext->m_pgpurenderer;

         auto pgpurenderer = m_pgpucontext->m_pgpurenderer;

         m_pgpucontext->set_placement(rectangle);

         pgpurenderer->defer_update_renderer();

         pgpurenderer->on_new_frame();

         m_pgpuframe = pgpurenderer->beginFrame();

         pgpurenderer->on_begin_render(m_pgpuframe);

      }

      //if (m_callbackImage32CpuBuffer)
      //{

      //   m_pgpucontext->m_callbackImage32CpuBuffer = m_callbackImage32CpuBuffer;

      //}

   }


   void graphics::create_end_draw()
   {


   }


   ::gpu::renderer* graphics::end_draw_renderer_output()
   {

      ::cast < ::windowing::window > pwindow = m_puserinteraction->m_pacmewindowingwindow;

      if (!m_pgpucontextOutput)
      {

         __øconstruct(m_pgpucontextOutput);

         m_pgpucontextOutput = m_papplication->get_gpu()->get_device(pwindow, pwindow->get_window_rectangle())->start_swap_chain_context(this, pwindow);

         //m_pgpucontextOutput->create_window_buffer(pwindow);

      }

      auto rectanglePlacement = pwindow->get_window_rectangle();

      m_pgpucontextOutput->set_placement(rectanglePlacement);

      auto prendererOutput = m_pgpucontextOutput->get_renderer(::gpu::e_scene_2d);

      prendererOutput->defer_update_renderer();

      return prendererOutput;

   }


   void graphics::on_end_draw()
   {

      if (m_egraphics == e_graphics_draw)
      {

         auto pgpurenderer = m_pgpucontext->m_pgpurenderer;

         pgpurenderer->on_end_render(m_pgpuframe);

         pgpurenderer->endFrame();

         if (m_eoutputOnEndDraw == ::gpu::e_output_swap_chain)
         {

            if (!m_puserinteraction)
            {

               throw ::exception(error_not_ready, "m_puserinteraction is null in graphics::on_end_draw()");

            }


            //auto prendererOutput = m_pgpucontextOutput->get_renderer();

            //m_pgpucontext->m_eoutput = ::gpu::e_output_gpu_buffer;

            /*prendererOutput->defer_update_renderer();

            prendererOutput->on_graphics_end_draw(m_puserinteraction);

            prenderer->_blend_image(vkimage, rectangle);*/

            //if (m_eoutputOnEndDraw == ::gpu::e_output_swap_chain)
            //{

            //   m_pgpucontext->swap_buffers();

               //m_pwindow->m_timeLastDrawGuard1.Now();


            //VkImage vkimage = prenderer->m_pvkcrenderpass->m_images[prenderer->currentImageIndex];

            ::int_rectangle rectangle;

            if (!m_puserinteraction->host_rectangle().size().is_empty())
            {

               rectangle = m_puserinteraction->host_rectangle();

            }
            else
            {

               rectangle = { 0, 0, 1920, 1080 };

            }

            //::cast < ::windowing::window > pwindow = m_puserinteraction->m_pacmewindowingwindow;

            //if (!m_pgpucontextOutput)
            //{

            //   __øconstruct(m_pgpucontextOutput);

            //   m_pgpucontextOutput = m_papplication->get_gpu()->get_device(pwindow, pwindow->get_window_rectangle())->start_swap_chain_context(this, pwindow);

            //   //m_pgpucontextOutput->create_window_buffer(pwindow);

            //}

            //auto prendererOutput = m_pgpucontextOutput->get_renderer();

            
            //m_pgpucontextOutput->m_size = rectanglePlacement.size();

            //auto pgpucontextOpenGL = m_pgpucontextOutput;

            //pgpucontextOpenGL->m_sizeHost = rectanglePlacement.size();

            //pgpucontextOpenGL->set_placement(rectanglePlacement);

            //m_pgpucontext->m_eoutput = ::gpu::e_output_gpu_buffer;

            //prendererOutput->defer_update_render_pass();

            if (!m_penddraw)
            {

               create_end_draw();

            }

            if (m_penddraw)
            {

               m_penddraw->endDraw(m_puserinteraction, pgpurenderer);

            }
            else
            {

               auto prendererOutput = end_draw_renderer_output();

               prendererOutput->endDraw(m_puserinteraction, pgpurenderer);

            }

            m_pgpucontext->m_pgpudevice->on_top_end_frame();

         }
         else if (m_eoutputOnEndDraw == ::gpu::e_output_cpu_buffer)
         {

            //m_pgpucontext->swap_buffers();

          //}
          //else
          //{

            //read_to_cpu_buffer();

            throw ::exception(error_not_implemented, "renderer::endDraw() not implemented for e_output_cpu_buffer");

            /*m_pimage->map();

            m_pimage->copy(&m_pgpucontext->m_pcpubuffer->m_pixmap);*/

         }

      }

   }


   void graphics::set_hint_window_output()
   {

      m_eoutputOnEndDraw = ::gpu::e_output_swap_chain;

   }



   void graphics::thread_select()
   {

      //if (thread_graphics() == this)
      //{

        // return;
      //}

      //wglMakeCurrent(m_hdc, m_hglrc);

      m_pgpucontext->make_current();

      thread_graphics(this);

   }


   void graphics::_set(const ::geometry2d::matrix& matrix)
   {

      m_m1 = matrix;

   }


   void graphics::do_on_context(const ::procedure& procedure)
   {
     
      m_pgpucontext->_send([procedure]()
         {

            procedure();

         });

   }



} // namespace draw2d_gpu



