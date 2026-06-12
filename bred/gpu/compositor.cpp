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


   ::gpu::texture* compositor::current_target_texture(::gpu::layer* pgpulayer)
   {

      return nullptr;

   }


   void compositor::set_gpu_context(::gpu::context* pgpucontextCompositor)
   {

      m_pgpucontextCompositor2 = pgpucontextCompositor;

      on_set_gpu_context();

   }


   void compositor::on_set_gpu_context()
   {


   }


   void compositor::on_gpu_context_placement_change(const ::i32_rectangle &rectanglePlacement,
                                                    ::acme::windowing::window *pacmewindowingwindow)
   {

      if (!m_pgpucontextCompositor2)
      {

         auto pgpuapproach = application()->get_gpu_approach();

         auto pgpudevice = pgpuapproach->get_gpu_device(pacmewindowingwindow);

         auto pgpucontext = pgpudevice->create_draw2d_context(::gpu::e_output_gpu_buffer, rectanglePlacement.size());

         auto pgpucontextNew = pgpucontext;

         set_gpu_context(pgpucontextNew);

         m_pgpucontextCompositor2->m_pgpucompositor = this;

      }
      else
      {

         m_pgpucontextCompositor2->set_placement(rectanglePlacement);

      }

   }


   void compositor::on_start_layer_before_begin_render(::gpu::layer * pgpulayer)
   {


   }


   ::gpu::context* compositor::gpu_context()
   {

      return m_pgpucontextCompositor2;

   }


   //void compositor::start_gpu_layer(::gpu::layer* pgpulayer)
   //{

   //   auto pcontext = gpu_context();

   //   auto pgpudevice = pcontext->m_pgpudevice;

   //   auto player = pgpulayer;

   //   player->layer_start();

   //}


   //::gpu::frame* compositor::end_gpu_layer(::gpu::layer* pgpulayer)
   //{

   //   //auto pcontext = gpu_context();

   //   auto player = pgpulayer;

   //   player->layer_end();

   //   return player;

   //}


   void compositor::gpu_layer_on_after_begin_render()
   {


   }


   void compositor::gpu_layer_on_before_end_render()
   {


   }


   void compositor::just_after_new_frame()
   {


   }


   void compositor::on_start_layer(::gpu::layer* pgpulayer)
   {



   }


   void compositor::on_end_layer(::gpu::layer* pgpulayer)
   {


   }


} // namespace gpu




