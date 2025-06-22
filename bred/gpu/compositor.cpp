// Created by camilo on 2025-06-18 19:58 <3ThomasBorregaardSørensen!!
#include "framework.h"
#include "compositor.h"
#include "context.h"
#include "device.h"
#include "layer.h"
#include "renderer.h"
#include "render_target.h"


namespace gpu
{


   compositor::compositor()
   {

   }


   compositor::~compositor()
   {


   }



   void compositor::start_gpu_layer()
   {

      auto player = m_pgpucontext->m_pgpudevice->next_layer(m_pgpucontext->m_pgpurenderer);

      player->layer_start();

   }


   void compositor::end_gpu_layer()
   {

      //auto prendererOutput = m_pgpucontext->m_pgpurenderer;

      //auto prendertarget = prendererOutput->m_pgpurendertarget;

      auto player = m_pgpucontext->m_pgpudevice->current_layer();

      player->layer_end();

//      m_pgpucontext->copy(player->texture(), prendertarget->current_texture());

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


} // namespace gpu




