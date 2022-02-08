#include "framework.h"
#include "_uwp.h"

//
//namespace universal_windows
//{
//
//
//   namespace apex
//   {
//
//
//      factory_exchange::factory_exchange()
//      {
//
//
//
//      }
//
//
//      factory_exchange::~factory_exchange()
//      {
//      }
//
//
//   } // namespace apex
//
//
//} // namespace universal_windows



void __node_apex_factory(::factory::factory * pfactory)
{

   //add_factory_item < ::universal_windows::interaction_impl, ::user::interaction_impl >();
   //add_factory_item < ::universal_windows::file, ::file::file >();
   add_factory_item < ::file::os_watcher, ::file::watcher >();
   add_factory_item < ::universal_windows::os_context, ::os_context >();
   add_factory_item < ::universal_windows::file_system, ::file_system >();
   add_factory_item < ::universal_windows::file_context, ::file_context >();
   add_factory_item < ::universal_windows::dir_system, ::dir_system >();
   add_factory_item < ::universal_windows::dir_context, ::dir_context >();
   //add_factory_item < ::universal_windows::tts::speaker, ::tts::speaker >();
   //add_factory_item < ::universal_windows::shell, ::user::shell >();
   //add_factory_item < ::universal_windows::copydesk, ::user::copydesk >();
   add_factory_item < ::file::watch >();

}



