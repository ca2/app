#include "framework.h"
#include "approach.h"
#include "context.h"
#include "device.h"
#include "types.h"
#include "acme/exception/interface_only.h"
#include "acme/filesystem/filesystem/file_context.h"
#include "acme/platform/application.h"
//#include "_.h"
//#include "_gpu.h"


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


   ::gpu::device* approach::get_device(::windowing::window * pwindow, const ::int_rectangle & rectanglePlacement)
   {

      if (!m_pgpudevice)
      {

         __øconstruct(m_pgpudevice);

         m_pgpudevice->initialize_gpu_device(this, pwindow, rectanglePlacement, m_papplication->m_bUseSwapChainWindow);

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

   
   

} // namespace gpu



