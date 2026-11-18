// From aura's graphics_configuration.h by camilo (close to its creation day) on 2026-11-02 07:57 <3ThomasBorregaardSorensen!! Mummi!! bilbo!!
// Changed by camilo (close to its creation day) on 2026-11-02 07:57 <3ThomasBorregaardSorensen!! Mummi!! bilbo!!
#include "platform.h"
#include "early_configuration.h"
#include "acme/operating_system/operating_system.h"


namespace graphics
{


   early_configuration::early_configuration()
   {


   }


   early_configuration::~early_configuration()
   {

   }


   ::string early_configuration::normalized(::string strPayload, const ::scoped_string & scopedstrPrefixToErase)
   {

      strPayload.trim();

      strPayload.begins_eat(scopedstrPrefixToErase);

      return strPayload;

   }

   
   // An application setting wins over its file setting; otherwise retain the
   // ordinary application defaults. These rules are also used by Options.
   ::string early_configuration::gpu_api(const ::scoped_string & scopedstrApplication, const ::scoped_string & scopedstrFile)
   {
      
      auto strGpuApi = normalized(scopedstrApplication, "gpu_");
      
      if (strGpuApi.is_empty())
      {

         strGpuApi = normalized(scopedstrFile, "gpu_");

      }

      if (strGpuApi == "opengl" || strGpuApi == "vulkan" || strGpuApi == "directx11"
         || strGpuApi == "directx12" || strGpuApi == "metal") return strGpuApi;
      return "opengl";
   }


   ::string_array_base early_configuration::gpu_apis(const ::enum_operating_system & eoperatingsystem)
   {

      ::string_array_base straGpuApis;

      straGpuApis.add("opengl");

      straGpuApis.add("vulkan");

      if (eoperatingsystem == ::e_operating_system_windows)
      {

         straGpuApis.add("directx11");

         straGpuApis.add("directx12");

      }
      else if (::operating_system::is_apple(eoperatingsystem))
      {
          
         straGpuApis.add("metal");

      }

      return straGpuApis;  

   }

   
   ::string_array_base early_configuration::gpu_apis()
   {

      return gpu_apis(::operating_system::get());

   }


   ::string early_configuration::output(const ::scoped_string & scopedstrApplication, const ::scoped_string & scopedstrFile)
   {
   
      auto strOutput = normalized(scopedstrApplication);

      if (strOutput.is_empty())
      {

         strOutput = normalized(scopedstrFile);

      }

      if (strOutput == "on_screen" || strOutput == "swap_chain" || strOutput == "onscreen")
      {

         return "on_screen";

      } 
      else
      {

         return "off_screen";

      } 

   }

   
   ::string_array_base early_configuration::draw2d_apis(const ::scoped_string & scopedstrGpu, bool bOffScreen, const ::enum_operating_system & eoperatingsystem)
   {

      ::string_array_base straDraw2dApis;

      if (bOffScreen)
      {

         if (eoperatingsystem == ::e_operating_system_windows_desktop)
         {

            straDraw2dApis.add("gdiplus");

            straDraw2dApis.add("direct2d");

         }
         else if (::operating_system::is_apple(eoperatingsystem))
         {
             
             straDraw2dApis.add("quartz2d");

         }
         else if (eoperatingsystem == ::e_operating_system_universal_windows)
         {
             
             straDraw2dApis.add("direct2d");

         }
         else if (eoperatingsystem == ::e_operating_system_haiku)
         {
             
             straDraw2dApis.add("haiku");

         }
         else
         {
             
            straDraw2dApis.add("cairo");

         }
//         {
//
//#ifdef WINDOWS_DESKTOP
//
//             return implementation_name("draw2d", "gdiplus");
//
//#elif __APPLE__
//
//             return implementation_name("draw2d", "quartz2d");
//
//#elif defined(UNIVERSAL_WINDOWS)
//
//             return implementation_name("draw2d", "direct2d");
//
//#elif defined(__HAIKU__)
//
//             return implementation_name("draw2d", "haiku");
//
//#else
//
//             return implementation_name("draw2d", "cairo");
//
//#endif
//
//            if (bApple)
//            {
//
//               straDraw2dApis.add("quartz2d");
//
//            }
//            else
//            {
//
//               straDraw2dApis.add("cairo");
//
//            }
//
//         }

      }
      else
      {

         straDraw2dApis.add(scopedstrGpu);

         if (scopedstrGpu == "opengl")
         {

            straDraw2dApis.add("nanovg");

         }
         else if (scopedstrGpu == "vulkan")
         {

            straDraw2dApis.add("vkvg");

         }
         else if (eoperatingsystem == ::e_operating_system_windows_desktop && scopedstrGpu == "directx11")
         {

            straDraw2dApis.add("direct2d_for_directx11");

         }
         else if (eoperatingsystem == ::e_operating_system_windows_desktop && scopedstrGpu == "directx12")
         {

            straDraw2dApis.add("direct2d_for_directx12");

         }

      }

      return straDraw2dApis;

   }


   ::string early_configuration::draw2d_api(const ::scoped_string & scopedstrSetting, const ::string_array_base & straOk)
   {

      auto strDraw2dApi = normalized(scopedstrSetting, "draw2d_");

      if (straOk.contains(strDraw2dApi))
      {
         
         return strDraw2dApi;

      }

      return straOk.is_empty() ? ::string{} : straOk.first();

   }


} // namespace graphics



