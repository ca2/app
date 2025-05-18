#pragma once


#include "base/platform/application.h"



namespace bred
{


   class CLASS_DECL_BRED application :
      virtual public ::base::application
   {
   public:


      application();
      ~application() override;


      void on_set_platform() override;
      

      void common_construct();


      //virtual ::pointer < ::graphics3d::application > start_graphics3d_aplication();


      void initialize(::particle * pparticle) override;
      //virtual ::pointer<progress_control>show_progress(::user::interaction* puiParent, const ::string & pszTitle, ::collection::count iProgressCount);

      ::file::path get_main_weather_file_path(const ::scoped_string & scopedstringAspect) override;


   };


} // namespace bred




