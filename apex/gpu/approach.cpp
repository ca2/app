#include "platform.h"
#include "approach.h"
//#include "context.h"
//#include "device.h"
//#include "types.h"
#include "window_attachment.h"
#include "acme/exception/interface_only.h"
#include "acme/filesystem/filesystem/file_context.h"
#include "acme/platform/application.h"
#include "acme/user/user/interaction.h"
#include "acme/windowing/windowing.h"


namespace gpu
{


   approach::approach()
   {

      m_emode = e_mode_none;
      //m_bSimpleMessageLoop = false;


   }


   approach::~approach()
   {

   }


   void approach::initialize(::particle * pparticle)
   {

      ::object::initialize(pparticle);

   }


   void approach::initialize_gpu_approach()
   {

   }



   ::pointer < ::apex::gpu::window_attachment > approach::allocate_gpu_window_attachment(::acme::windowing::window * pacmewindowingwindow)
   {

      return nullptr;

   }


   ::gpu::device* approach::get_gpu_device(::acme::windowing::window * pacmewindowingwindow)
   {

      return nullptr;

      //if (!m_pgpudevice)
      //{

      //   constructø(m_pgpudevice);

      //   if (m_papplication->m_gpu.m_bUseSwapChainWindow)
      //   {

      //      m_pgpudevice->initialize_gpu_device_for_swap_chain(this, m_pacmeuserinteractionMain->window());

      //   }
      //   else
      //   {

      //      if (m_rectangleOffscreen.is_empty())
      //      {

      //         m_rectangleOffscreen = {1920, 1080};

      //      }

      //      m_pgpudevice->initialize_gpu_device_for_off_screen(this, m_rectangleOffscreen);

      //   }

      //}

      //return m_pgpudevice;

   }
   

   void approach::engine_on_frame_context_initialization(::gpu::context* pgpucontext)
   {

      //pgpucontext->engine_on_frame_context_initialization();

   }

   
   //::file::path approach::shader_path(const ::file::path& pathShader)
   //{

   //   return pathShader;

   //}


   ::particle_pointer approach::_allocate_draw2d_window_attachment_for_gpu(::acme::windowing::window * pacmewindowingwindow)
   {

      return {};

   }


   void approach::defer_init_gpu_library()
   {

      //return ::success;

   }


   int approach::graphics3d_modes_step()
   {

      if (m_iGraphicsModeStep < 0)
      {

         ::i32 iStep = -1;

         ::i32 iBase = -1;

         ::i32 iSwapChain = -1;

         ::string strGpu = system()->component_factory_implementation_name("gpu");

         ::string strDraw2d = system()->component_factory_implementation_name("draw2d");

         ::string_array straGpu;

         straGpu.add("opengl");
         straGpu.add("vulkan");
         straGpu.add("directx11");
         straGpu.add("directx12");

         auto iGpu = straGpu.find_first(strGpu);

         if (iGpu < 0 || strDraw2d.is_empty())
         {

            goto error;

         }
         
         iSwapChain = m_papplication->m_gpu.m_bUseSwapChainWindow ? 1 : 0;

#ifdef WINDOWS

         iBase = (::i32) ( iGpu * 4 + iSwapChain * 2);

         iStep = iBase;

         if (iSwapChain == 1)
         {

            if (strGpu != strDraw2d)
            {

               iStep++;

            }

         }
         else
         {

            if (strDraw2d != "gdiplus")
            {

               iStep++;

            }

         }

#endif

         m_iGraphicsModeStep = iStep + 1;

         goto end;
      error:

         m_iGraphicsModeStep = -1;

      }
   end:

      return m_iGraphicsModeStep;

   }
   
   
   int approach::graphics3d_modes_step_count()
   {

      if (m_iGraphicsModeStepCount < 0)
      {

#ifdef WINDOWS_DESKTOP

         m_iGraphicsModeStepCount = 16;

#endif

      }

      return m_iGraphicsModeStepCount;

   }



   void approach::gpu_on_before_create_window(::acme::windowing::window* pwindow)
   {


   }


   void approach::gpu_on_create_window(::acme::windowing::window* pwindow)
   {


   }



   //::gpu::payload approach::load_dds(const ::scoped_string & scopedstrImagePath)
   //{

   //   throw interface_only();

   //   return {};

   //}

   /*::subparticle* approach::get_draw2d_connector_for_swap_chain(::windowing::window* pwindow)
   {

      return nullptr;

   }
   */

} // namespace gpu



