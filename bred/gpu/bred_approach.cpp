#include "framework.h"
#include "binding.h"
#include "bred_approach.h"
#include "context.h"
#include "device.h"
#include "types.h"
#include "acme/exception/interface_only.h"
#include "acme/filesystem/filesystem/file_context.h"
#include "acme/platform/application.h"
#include "acme/user/user/interaction.h"
#include "acme/windowing/windowing.h"


namespace gpu
{


   bred_approach::bred_approach()
   {

      //m_emode = e_mode_none;
      //m_bSimpleMessageLoop = false;


   }


   bred_approach::~bred_approach()
   {

   }


   void bred_approach::initialize(::particle * pparticle)
   {

      ::gpu::approach::initialize(pparticle);


   }


   void bred_approach::initialize_gpu_approach()
   {

      ::gpu::approach::initialize_gpu_approach();

      system()->m_pfactory->add_factory_item<::gpu::binding>();
      system()->m_pfactory->add_factory_item<::gpu::binding_set>();
      system()->m_pfactory->add_factory_item<::gpu::binding_set_array>();

      system()->m_pfactory->add_factory_item<::gpu::binding_slot_set>();
      system()->m_pfactory->add_factory_item<::gpu::binding_slot_set_array>();


   }


   ::gpu::device* bred_approach::get_gpu_device(::acme::windowing::window * pacmewindowingwindow)
   {

      if (!m_pgpudevice)
      {

         øconstruct(m_pgpudevice);

         if (m_papplication->m_gpu.m_bUseSwapChainWindow)
         {

            ///auto pwindow = m_papplication->m_pacmeuserinteractionMain->window();

            ::cast < ::windowing::window > pwindow;

            pwindow = pacmewindowingwindow;

            if (!pwindow)
            {

               pwindow = m_papplication->m_pacmeuserinteractionMain->window();

            }

            m_pgpudevice->initialize_gpu_device_for_swap_chain(this, pwindow);

         }
         else
         {

            if (m_rectangleOffscreen.is_empty())
            {

               m_rectangleOffscreen = {API_CHANGED_ARGUMENT, 1920, 1080};

            }

            m_pgpudevice->initialize_gpu_device_for_off_screen(this, m_rectangleOffscreen);

         }

      }

      return m_pgpudevice;

   }
   

   void bred_approach::engine_on_frame_context_initialization(::gpu::context* pgpucontext)
   {

      pgpucontext->engine_on_frame_context_initialization();

   }

   





   void bred_approach::defer_init_gpu_library()
   {

      //return ::success;

   }


   void bred_approach::on_before_create_window(::windowing::window* pwindow)
   {


   }


   void bred_approach::on_create_window(::windowing::window* pwindow)
   {


   }



   //::gpu::payload bred_approach::load_dds(const ::scoped_string & scopedstrImagePath)
   //{

   //   throw interface_only();

   //   return {};

   //}

   /*::subparticle* bred_approach::get_draw2d_connector_for_swap_chain(::windowing::window* pwindow)
   {

      return nullptr;

   }
   */

} // namespace gpu



