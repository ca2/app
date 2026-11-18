// From aura's graphics_configuration.h by camilo (close to its creation day) on 2026-11-02 07:57 <3ThomasBorregaardSorensen!! Mummi!! bilbo!!
// Changed by camilo (close to its creation day) on 2026-11-02 07:57 <3ThomasBorregaardSorensen!! Mummi!! bilbo!!
#pragma once


#include "acme/constant/operating_system.h"


namespace graphics
{


   class CLASS_DECL_APEX early_configuration :
      virtual public ::particle
   {
   public:


      early_configuration();
      ~early_configuration() override;


      virtual ::string normalized(::string strPayload, const ::scoped_string & scopedstrPrefixToErase = {});

      virtual ::string gpu_api(const ::scoped_string & scopedstrApplication, const ::scoped_string & scopedstrFile);

      virtual ::string_array_base gpu_apis(const ::enum_operating_system & eoperatingsystem);

      virtual ::string_array_base gpu_apis();

      virtual ::string output(const ::scoped_string & scopedstrApplication, const ::scoped_string & scopedstrFile);

      virtual ::string_array_base draw2d_apis(const ::scoped_string & scopedstrGpu, bool bOffScreen, const ::enum_operating_system & eoperatingsystem);

      virtual ::string draw2d_api(const ::scoped_string & scopedstrSetting, const ::string_array_base & straOk);


   };


} // namespace graphics



