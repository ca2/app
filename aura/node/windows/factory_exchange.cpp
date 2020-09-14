#include "framework.h"
#include "aura/node/windows/_windows.h"
#include "aura/node/windows/buffer.h"



//namespace aura
//{
//
//
//   namespace windows
//   {
//
//
//      factory_exchange::factory_exchange()
//      {
//
//
//
//         //::windows::shell::theWindowsShell.Initialize();
//
//      }
//
//
//      factory_exchange::~factory_exchange()
//      {
//
//      }
//
//
//   } // namespace windows
//
//
//} // namespace aura


void __node_aura_factory_exchange()
{


   //create_factory < ::windows::console, ::console::console >();
   //create_factory < ::windows::crypto, ::crypto::crypto >();
   //create_factory < ::windows::ip_enum, ::net::ip_enum >();


   create_factory < ::windows::buffer, ::graphics::graphics >();
   create_factory < ::windows::interaction_impl, ::user::interaction_impl >();

   //create_factory < ::file::os_watcher, ::file::watcher >();
   //create_factory < ::file::os_watch, ::file::watch >();

   create_factory < ::windows::copydesk, ::user::copydesk >();
   //create_factory < ::windows::shell, ::user::shell >();


}




