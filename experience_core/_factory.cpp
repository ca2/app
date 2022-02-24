#include "framework.h"
#include "acme/platform/system_setup.h"

//
//namespace experience
//{
//
//
//   namespace core
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
//      __namespace_library_factory("experience_core");
//   
//
//   } // namespace core
//
//
//} // namespace experience
//



__FACTORY_EXPORT void experience_core_factory(::factory::factory* pfactory)
{

   //pfactory->add_factory_item < ::windows::dir_system, ::dir_system >();
   //pfactory->add_factory_item < ::windows::file_system, ::file_system >();

   //pfactory->add_factory_item < ::windows::dir_context, ::dir_context >();
   //pfactory->add_factory_item < ::windows::file_context, ::file_context >();

   //add_factory_item < ::windows::stdio_file, ::file::text_file >();
   //add_factory_item < ::windows::file, ::file::file >();
   //pfactory->add_factory_item < ::windows::os_context, ::os_context >();
   //pfactory->add_factory_item < ::windows::pipe, ::operating_system::pipe >();
   //pfactory->add_factory_item < ::windows::process, ::operating_system::process >();

   ////add_factory_item < ::windows::console, ::console::console >();
   //pfactory->add_factory_item < ::windows::crypto, ::crypto::crypto >();
   //pfactory->add_factory_item < ::windows::ip_enum, ::net::ip_enum >();

   pfactory->add_factory_item < ::experience::core::experience, ::experience::experience >();
   pfactory->add_factory_item < ::experience::core::control_box, ::experience::control_box >();
   pfactory->add_factory_item < ::experience::core::button, ::experience::button >();
   pfactory->add_factory_item < ::experience::core::style, ::user::style >();

}



