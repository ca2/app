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
#include "aura/windowing/window.h"


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

      if (::is_null(pacmewindowingwindow))
      {

         throw ::exception(error_bad_argument);

      }

      if (!pacmewindowingwindow->is_window())
      {

         throw ::exception(error_bad_argument);

      }

      auto &pdevice = m_devicemap[pacmewindowingwindow];

      ::string strType = ::type(pacmewindowingwindow->m_pacmeuserinteraction).name();

      auto pszType = strType.c_str();

      if (!pdevice)
      {

         øconstruct(pdevice);

         ::string strType = ::type(pacmewindowingwindow->m_pacmeuserinteraction).name();
         
         const char *pszType = strType.c_str();

         if (m_papplication->m_gpu.m_bUseSwapChainWindow)
         {

            ///auto pwindow = m_papplication->m_pacmeuserinteractionMain->window();

            ::cast < ::windowing::window > pwindow;

            pwindow = pacmewindowingwindow;

            //if (!pwindow)
            //{

            //   pwindow = m_papplication->m_pacmeuserinteractionMain->window();

            //}

            pdevice->initialize_gpu_device_for_swap_chain(this, pwindow);

         }
         else
         {

            if (m_rectangleOffscreen.is_empty())
            {

               m_rectangleOffscreen = {API_CHANGED_ARGUMENT, 1920, 1080};

            }

            pdevice->initialize_gpu_device_for_off_screen(this, m_rectangleOffscreen);

         }

      }

      return pdevice;

   }
   

   void bred_approach::engine_on_frame_context_initialization(::gpu::context* pgpucontext)
   {

      pgpucontext->engine_on_frame_context_initialization();

   }

   





   void bred_approach::defer_init_gpu_library()
   {

      //return ::success;

   }


   void bred_approach::on_before_create_window(::acme::windowing::window* pwindow)
   {


   }


   void bred_approach::on_create_window(::acme::windowing::window* pacmewindowingwindow)
   {

      ::gpu::approach::on_create_window(pacmewindowingwindow);
      
      ::string strType;

      strType = ::type(pacmewindowingwindow->m_pacmeuserinteraction).name();

      const char *pszType = strType.c_str();

      information("gpu::approach::on_create_window for type {}", pszType);

      auto pdevice = ::system()->m_papplication->gpu_approach()->get_gpu_device(pacmewindowingwindow);

      pdevice->create_main_context(pacmewindowingwindow);

      //::cast<::gpu_opengl::approach> papproach = m_papplication->get_gpu_approach();
      _on_create_window(pacmewindowingwindow);
      //::draw2d_gpu::draw2d::on_create_window(pwindowParam);

      //::cast < ::windowing_win32::window > pwindow = pwindowParam;

      // auto hwnd = pwindow->m_hwnd;

      // HRGN hRgn = CreateRectRgn(0, 0, -1, -1);
      // bb.dwFlags = DWM_BB_ENABLE | DWM_BB_BLURREGION;
      // bb.hRgnBlur = hRgn;
      // bb.fEnable = TRUE;
      // DwmEnableBlurBehindWindow(hwnd, &bb);

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

   void bred_approach::_on_create_window(::acme::windowing::window * pwindow)
   {



   }

} // namespace gpu



