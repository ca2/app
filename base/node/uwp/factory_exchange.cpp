#include "framework.h"
#include "_uwp.h"

//
//namespace uwp
//{
//
//
//   namespace aura
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
//   } // namespace aura
//
//
//} // namespace uwp



void __node_aura_factory_exchange()
{

   create_factory < ::uwp::interaction_impl, ::user::interaction_impl >();
   create_factory < ::uwp::file, ::file::file >();
   create_factory < ::file::os_watcher, ::file::watcher >();
   create_factory < ::uwp::os_context, ::os_context >();
   create_factory < ::uwp::file_system, ::file_system >();
   create_factory < ::uwp::file_context, ::file_context >();
   create_factory < ::uwp::dir_system, ::dir_system >();
   create_factory < ::uwp::dir_context, ::dir_context >();
   create_factory < ::uwp::tts::speaker, ::tts::speaker >();
   create_factory < ::uwp::shell, ::user::shell >();
   create_factory < ::uwp::copydesk, ::user::copydesk >();
   create_factory < ::file::watch >();

}



