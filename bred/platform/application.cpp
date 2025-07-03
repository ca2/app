#include "framework.h"
#include "application.h"
#include "system.h"
#include "acme/exception/interface_only.h"
#include "acme/filesystem/filesystem/directory_system.h"
#include "bred/gpu/bred_approach.h"


namespace bred
{


   //void initialize()
   //{

   //}


   application::application()
   {

      //::bred::initialize();

      //m_pbredapplication = this;


   }


   application::~application()
   {

   }


   void application::on_set_platform()
   {

      ::base::application::on_set_platform();

      factory()->add_factory_item < ::bred::system, ::platform::system >();

   }


   void application::common_construct()
   {


   }


   void application::initialize(::particle * pparticle)
   {

      //auto estatus = 
      
      ::axis::application::initialize(pparticle);

      //if (!estatus)
      //{

      //   return estatus;

      //}

      //return estatus;

   }


   //::pointer<progress_control>application::show_progress(::user::interaction* puiParent, const ::string & pszTitle, ::collection::count iProgressCount)
   //{

   //   auto pprogresscontrol = __create_new <  ::userex::progress_control >();

   //   pprogresscontrol->defer_show(puiParent, pszTitle, iProgressCount);

   //   return ::transfer(pprogresscontrol);

   //}


   ::file::path application::get_main_weather_file_path(const ::scoped_string & scopedstringAspect)
   {

      return directory_system()->roaming() / "user/weather" / (scopedstringAspect + ".txt");

   }

   
   //::pointer < ::graphics3d::application > application::start_graphics3d_aplication()
   //{

   //   auto p3dapplication = __øcreate < graphics3d::application>();

   //   return p3dapplication;

   //}

   ::gpu::approach* application::get_gpu_approach()
   {

      if (!m_bGpu)
      {

         throw ::exception(error_wrong_state, "Gpu application flag should be enabled to use gpu components.");

      }

      if (!m_pgpuapproach)
      {

         create_gpu_approach();

      }

      return m_pgpuapproach.get();

   }


   ::gpu::approach* application::gpu_approach()
   {

      return m_pgpuapproach.get();

   }


   ::string application::draw2d_get_default_implementation_name()
   {
      
      auto strName = ::base::application::draw2d_get_default_implementation_name();

      return strName;

   }


   //#ifdef _OPENGL
   void application::create_gpu_approach()
   {

      if (m_pgpuapproach)
      {

         return;

      }

      //load_library("gpu_opengl");

      auto pfactoryGpu = component_factory("gpu");

      if (!pfactoryGpu)
      {

         ::string strGpuImplementation;

         ::string strDraw2dImplementation = m_papplication->draw2d_get_default_implementation_name();

         if (strDraw2dImplementation.is_empty())
         {


         }

         if (strDraw2dImplementation == "vkvg")
         {

            strGpuImplementation = "vulkan";

         }
         else if (strDraw2dImplementation == "opengl")
         {

            strGpuImplementation = "opengl";

         }
         else if (strDraw2dImplementation == "directx11")
         {

            strGpuImplementation = "directx11";

         }
         else if (strDraw2dImplementation == "directx12")
         {

            strGpuImplementation = "directx12";

         }
         else if (strDraw2dImplementation == "gdiplus")
         {

            strGpuImplementation = graphics3d_get_implementation_name();

         }
         else if (strDraw2dImplementation == "cairo")
         {

            strGpuImplementation = graphics3d_get_implementation_name();

         }
         else if (strDraw2dImplementation.begins_eat("direct2d"))
         {

            strGpuImplementation = graphics3d_get_implementation_name();

            if(!strGpuImplementation.case_insensitive_begins("directx"))
            {
               
               strGpuImplementation = "directx12";

            }

         }

         pfactoryGpu = factory("gpu", strGpuImplementation);

         pfactoryGpu->merge_to_global_factory();

      }

      //get_library("gpu_opengl");



      //if (!pfactoryGpu)
      //{

      //   error() <<"gpu_opengl ([a-z0-9_]+)_factory has failed";

      //   return pfactoryGpu;

      //}

      //auto estatus =

      pfactoryGpu->__øconstruct(this, m_pgpuapproach);


      m_pgpuapproach->initialize_gpu_approach();

      //if (!estatus)
      //{

      //   return estatus;

      //}

      //return ::success;

   }


} // namespace bred



