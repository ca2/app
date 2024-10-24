#include "framework.h"
#include "application.h"
#include "system.h"
#include "acme/filesystem/filesystem/directory_system.h"


namespace bred
{


   //void initialize()
   //{

   //}


   application::application()
   {

      //::bred::initialize();

      m_pbredapplication = this;


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



} // namespace bred



