#include "framework.h"
#include "approach.h"
#include "context.h"
#include "device.h"
#include "types.h"
#include "acme/exception/interface_only.h"
#include "acme/filesystem/filesystem/file_context.h"
#include "acme/platform/application.h"
#include "acme/user/user/interaction.h"


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


   ::gpu::device* approach::get_device()
   {

      if (!m_pgpudevice)
      {

         __øconstruct(m_pgpudevice);

         if (m_papplication->m_bUseSwapChainWindow)
         {

            m_pgpudevice->initialize_gpu_device_for_swap_chain(this, m_papplication->m_pacmeuserinteractionMain->window());

         }
         else
         {

            if (m_rectangleOffscreen.is_empty())
            {

               m_rectangleOffscreen = {1920, 1080};

            }

            m_pgpudevice->initialize_gpu_device_for_off_screen(this, m_rectangleOffscreen);

         }

      }

      return m_pgpudevice;

   }
   

   void approach::engine_on_frame_context_initialization(::gpu::context* pgpucontext)
   {

      pgpucontext->engine_on_frame_context_initialization();

   }

   
   ::file::path approach::shader_path(const ::file::path& pathShader)
   {

      return pathShader;

   }





   void approach::defer_init_gpu_library()
   {

      //return ::success;

   }


   ::gpu::payload approach::load_dds(const ::scoped_string & scopedstrImagePath)
   {

      throw interface_only();

      return {};

   }

   /*::subparticle* approach::get_draw2d_connector_for_swap_chain(::windowing::window* pwindow)
   {

      return nullptr;

   }
   */

} // namespace gpu



