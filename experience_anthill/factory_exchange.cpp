#include "framework.h"
//#include "apex/platform/static_setup.h"
//
//
//namespace experience
//{
//
//
//   namespace anthill
//   {
//
//
//      library::library() 
//      {
//
//      }
//
//
//      library::~library()
//      {
//
//      }
//
//
//      ::matter * library::new_object(const ::string & pszClass)
//      {
//
//         if(string(pszClass) == "experience")
//         {
//
//            return new experience;
//
//         }
//         else if(string(pszClass) == "control_box")
//         {
//
//            return new control_box;
//
//         }
//         else if(string(pszClass) == "button")
//         {
//
//            return new button;
//
//         }
//         else if(string(pszClass) == "user_theme")
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
//      __namespace_library_factory("experience_anthill");
//
//
//   } // namespace anthill
//
//
//} // namespace experience
//
//
//



extern "C"
void experience_anthill_factory_exchange(::factory_map * pfactorymap)
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

   pfactorymap->create_factory < ::experience::anthill::experience, ::experience::experience >();
   pfactorymap->create_factory < ::experience::anthill::control_box, ::experience::control_box >();
   pfactorymap->create_factory < ::experience::anthill::button, ::experience::button >();
   pfactorymap->create_factory < ::experience::anthill::style, ::user::style >();

}


