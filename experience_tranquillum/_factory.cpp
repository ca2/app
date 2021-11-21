#include "framework.h"
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

__FACTORY_EXPORT void experience_tranquillum_factory(::factory::factory * pfactory)
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

   pfactory->add_factory_item < ::experience::tranquillum::experience, ::experience::experience >();
   pfactory->add_factory_item < ::experience::tranquillum::control_box, ::experience::control_box >();
   pfactory->add_factory_item < ::experience::tranquillum::button, ::experience::button >();
   pfactory->add_factory_item < ::experience::tranquillum::style, ::user::style >();

}



