// Created by camilo on 2025-06-18 19:58 <3ThomasBorregaardSørensen!!
#include "platform.h"
#include "bred_approach.h"
#include "compositor.h"
#include "context.h"
#include "device.h"
#include "frame.h"
#include "layer.h"
#include "renderer.h"
#include "render_target.h"
#include "acme/platform/application.h"
#include "acme/windowing/window.h"


namespace gpu
{


   compositor::compositor()
   {

   }


   compositor::~compositor()
   {


   }


   ::gpu::texture_site * compositor::current_target_texture(::gpu::layer* pgpulayer)
   {

      return nullptr;

   }


   void compositor::set_gpu_context(::gpu::context* pgpucontextCompositor)
   {

      m_pgpucontextCompositor2 = pgpucontextCompositor;

      m_pgpucontextCompositor2->m_pgpucompositor = this;

      on_set_gpu_context();

   }


   void compositor::on_set_gpu_context()
   {


   }


   void compositor::on_gpu_context_placement_change(
         const ::i32_point & pointTarget,
         const ::i32_point & pointSource,
         const ::i32_size & size,
         ::acme::windowing::window *pacmewindowingwindow,
         ::draw2d::graphics * pdraw2dgraphics)
   {

      if (!m_pgpucontextCompositor2)
      {

         auto pgpuapproach = application()->get_gpu_approach();

         auto pgpudevice = pgpuapproach->get_gpu_device(pacmewindowingwindow);

//<<<<<<< HEAD
         //auto pgpucontext = pgpudevice->create_draw2d_context(::gpu::e_output_gpu_buffer, pacmewindowingwindow, rectanglePlacement.size());
//=======
         auto pgpucontext = pgpudevice->allocate_gpu_context();
         
         pgpucontext->create_draw2d_gpu_context(pgpudevice, pacmewindowingwindow, pdraw2dgraphics, pointSource, pointTarget, size, pacmewindowingwindow->m_sizeRaw);
//>>>>>>> origin/main

         auto pgpucontextNew = pgpucontext;

         set_gpu_context(pgpucontextNew);

         m_pgpucontextCompositor2->m_pgpucompositor = this;

      }
      else
      {

         m_pgpucontextCompositor2->set_input_origin(pointSource);

         m_pgpucontextCompositor2->set_output_origin(pointTarget);

      }

   }


   bool compositor::renders_layer_externally(::gpu::layer * pgpulayer)
   {

      return false;

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




