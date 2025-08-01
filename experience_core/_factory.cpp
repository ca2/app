#include "framework.h"
#include "acme/platform/system_setup.h"
#include "experience/experience.h"
#include "experience/control_box.h"
#include "experience/control_box_button.h"
#include "user/style.h"


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
//      ::matter * library::new_object(const ::scoped_string & scopedstrClass)
//      {
//
//         if(string(scopedstrClass) == "experience")
//         {
//
//            return ___new experience();
//
//         }
//         else if(string(scopedstrClass) == "control_box")
//         {
//
//            return ___new control_box();
//
//         }
//         else if(string(scopedstrClass) == "button")
//         {
//
//            return ___new button();
//
//         }
//         else if(string(scopedstrClass) == "user_theme")
//         {
//
//            return ___new style();
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

   //pfactory->add_factory_item < ::windows::directory_system, ::directory_system >();
   //pfactory->add_factory_item < ::windows::file_system, ::file_system >();

   //pfactory->add_factory_item < ::windows::directory_context, ::directory_context >();
   //pfactory->add_factory_item < ::windows::file_context, ::file_context >();

   //add_factory_item < ::windows::stdio_file, ::file::text_file >();
   //add_factory_item < ::windows::file, ::file::file >();
   //pfactory->add_factory_item < ::windows::os_context, ::os_context >();
   //pfactory->add_factory_item < ::windows::pipe, ::operating_system::pipe >();
   //pfactory->add_factory_item < ::windows::process, ::operating_system::process >();

   ////add_factory_item < ::windows::console, ::console::console >();
   //pfactory->add_factory_item < ::windows::crypto, ::crypto::crypto >();
   //pfactory->add_factory_item < ::windows::ip_enum, ::net::ip_enum >();

   pfactory->add_factory_item < ::experience_core::experience, ::experience::experience >();
   pfactory->add_factory_item < ::experience_core::control_box, ::experience::control_box >();
   pfactory->add_factory_item < ::experience_core::control_box_button, ::experience::button >();
   pfactory->add_factory_item < ::experience_core::style, ::user::style >();


}



