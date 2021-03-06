#include "framework.h"
#include "_uwp.h"

//
//namespace uwp
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
//} // namespace uwp



void __node_apex_factory_exchange(::factory_map * pfactorymap)
{

   //create_factory < ::uwp::interaction_impl, ::user::interaction_impl >();
   //create_factory < ::uwp::file, ::file::file >();
   create_factory < ::file::os_watcher, ::file::watcher >();
   create_factory < ::uwp::os_context, ::os_context >();
   create_factory < ::uwp::file_system, ::file_system >();
   create_factory < ::uwp::file_context, ::file_context >();
   create_factory < ::uwp::dir_system, ::dir_system >();
   create_factory < ::uwp::dir_context, ::dir_context >();
   //create_factory < ::uwp::tts::speaker, ::tts::speaker >();
   //create_factory < ::uwp::shell, ::user::shell >();
   //create_factory < ::uwp::copydesk, ::user::copydesk >();
   create_factory < ::file::watch >();

}



