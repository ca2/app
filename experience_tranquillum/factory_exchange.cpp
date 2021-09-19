#include "framework.h"
#include "aura/application.h"
//
//
//namespace experience
//{
//
//
//   namespace tranquillum
//
//   {
//
//
//      library::library()
//      {
//      }
//
//
//      library::~library()
//      {
//
//      }
//
//
//      ::matter * library::new_object(const ::string & lpszClass)
//      {
//
//         if(string(lpszClass) == "experience")
//         {
//
//            return new experience;
//
//         }
//         else if(string(lpszClass) == "control_box")
//         {
//
//            return new control_box;
//
//         }
//         else if(string(lpszClass) == "button")
//         {
//
//            return new button;
//
//         }
//         else if(string(lpszClass) == "user_theme")
//         {
//
//            return new style;
//
//         }
//         else
//         {
//
//            return nullptr;
//
//         }
//
//      }
//
//
//      __namespace_library_factory("experience_tranquillum");
//
//
//   } // namespace tranquillum
//
//
//} // namespace experience
//
//
//
//
//
//
//if (string(lpszClass) == "experience")
//{
//
//   return new experience;
//
//}
//else if (string(lpszClass) == "control_box")
//{
//
//   return new control_box;
//
//}
//else if (string(lpszClass) == "button")
//{
//
//   return new button;
//
//}
//else if (string(lpszClass) == "user_theme")
//{
//
//   return new style;
//
//}
//else
//{
//
//   return nullptr;
//
//}

extern "C"
void experience_tranquillum_factory_exchange(::factory_map * pfactorymap)
{

   //pfactorymap->create_factory < ::windows::dir_system, ::dir_system >();
   //pfactorymap->create_factory < ::windows::file_system, ::file_system >();

   //pfactorymap->create_factory < ::windows::dir_context, ::dir_context >();
   //pfactorymap->create_factory < ::windows::file_context, ::file_context >();

   //create_factory < ::windows::stdio_file, ::file::text_file >();
   //create_factory < ::windows::file, ::file::file >();
   //pfactorymap->create_factory < ::windows::os_context, ::os_context >();
   //pfactorymap->create_factory < ::windows::pipe, ::operating_system::pipe >();
   //pfactorymap->create_factory < ::windows::process, ::operating_system::process >();

   ////create_factory < ::windows::console, ::console::console >();
   //pfactorymap->create_factory < ::windows::crypto, ::crypto::crypto >();
   //pfactorymap->create_factory < ::windows::ip_enum, ::net::ip_enum >();

   pfactorymap->create_factory < ::experience::tranquillum::experience, ::experience::experience >();
   pfactorymap->create_factory < ::experience::tranquillum::control_box, ::experience::control_box >();
   pfactorymap->create_factory < ::experience::tranquillum::button, ::experience::button >();
   pfactorymap->create_factory < ::experience::tranquillum::style, ::user::style >();

}



