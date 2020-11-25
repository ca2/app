#include "framework.h"
#include "acme/node/windows/_windows.h"
//#include "file_os_watcher.h"
//#include "acme/node/windows/buffer.h"
#include "acme/os/console.h"
#include "console.h"



//namespace acme
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
//} // namespace acme


void __node_acme_factory_exchange()
{

   //create_factory < ::windows::dir_system, ::dir_system >();
   //create_factory < ::windows::file_system, ::file_system >();

   //create_factory < ::windows::dir_context, ::dir_context >();
   //create_factory < ::windows::file_context, ::file_context >();

   //create_factory < ::windows::stdio_file, ::file::text_file >();
   create_factory < ::windows::file, ::file::file >();
   //create_factory < ::windows::os_context, ::os_context >();
   create_factory < ::windows::pipe, ::process::pipe >();
   //create_factory < ::windows::promise::process, ::process::process >();

   create_factory < ::windows::console, ::console::console >();
   //create_factory < ::windows::crypto, ::crypto::crypto >();
   //create_factory < ::windows::ip_enum, ::net::ip_enum >();


   //create_factory < ::windows::buffer, ::graphics::graphics >();
   //create_factory < ::windows::interaction_impl, ::user::interaction_impl >();

   //create_factory < ::file::os_watcher, ::file::watcher >();
   //create_factory < ::file::os_watch, ::file::watch >();

   //create_factory < ::windows::copydesk, ::user::copydesk >();
   //create_factory < ::windows::shell, ::user::shell >();


}




