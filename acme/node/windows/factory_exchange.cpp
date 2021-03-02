#include "framework.h"
#include "acme/operating_system.h"
#include "acme/node/windows/_windows.h"
//#include "file_os_watcher.h"
//#include "acme/node/windows/buffer.h"
#include "acme/os/console.h"
#include "console.h"
#include "file_memory_map.h"



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


void __node_acme_factory_exchange(::factory_map * pfactorymap)
{

   //pfactorymap->create_factory < ::windows::dir_system, ::dir_system >();
   //pfactorymap->create_factory < ::windows::file_system, ::file_system >();

   //pfactorymap->create_factory < ::windows::dir_context, ::dir_context >();
   //pfactorymap->create_factory < ::windows::file_context, ::file_context >();

   //pfactorymap->create_factory < ::windows::stdio_file, ::file::text_file >();
   pfactorymap->create_factory < ::windows::file, ::file::file >();
   //pfactorymap->create_factory < ::windows::os_context, ::os_context >();
   pfactorymap->create_factory < ::windows::pipe, ::process::pipe >();
   //pfactorymap->create_factory < ::windows::future, ::process::process >();

   pfactorymap->create_factory < ::windows::console, ::console::console >();
   //pfactorymap->create_factory < ::windows::crypto, ::crypto::crypto >();
   //pfactorymap->create_factory < ::windows::ip_enum, ::net::ip_enum >();

   pfactorymap->create_factory < ::windows::file_memory_map, ::file::memory_map >();
   //pfactorymap->create_factory < ::windows::buffer, ::graphics::graphics >();
   //pfactorymap->create_factory < ::windows::interaction_impl, ::user::interaction_impl >();

   //pfactorymap->create_factory < ::file::os_watcher, ::file::watcher >();
   //pfactorymap->create_factory < ::file::os_watch, ::file::watch >();

   //pfactorymap->create_factory < ::windows::copydesk, ::user::copydesk >();
   //pfactorymap->create_factory < ::windows::shell, ::user::shell >();


}




