#include "framework.h"
#include "_.h"
#include "copydesk.h"
//#include "file_os_watcher.h"
//#include "aura/node/posix/pipe.h"
//#include "aura/node/apple/process.h"
//#include "aura/node/macos/shell_macos.h"
//#include "aura/node/unix/process.h"


//namespace macos
//{
//
//   factory_exchange::factory_exchange()
//   {
//
//
//
//   }
//
//
//   factory_exchange::~factory_exchange()
//   {
//
//   }
//
//
//} // namespace macos



void __node_aura_factory_exchange()
{

//   create_factory < ::macos::stdio_file         , ::file::text_file  > ();
//   create_factory < ::macos::file               , ::file::file       > ();
//   create_factory < ::macos::os_context         , ::os_context       > ();
//   create_factory < ::apple::process            , ::process::process > ();
//   create_factory < ::posix::pipe               , ::process::pipe    > ();
//   create_factory < ::macos::dir_system         , ::dir_system       > ();
//   create_factory < ::macos::file_system        , ::file_system      > ();
//   create_factory < ::macos::dir_context        , ::dir_context      > ();
//   create_factory < ::macos::file_context       , ::file_context     > ();

   create_factory < ::macos::interaction_impl   , ::user::interaction_impl > ();
   
   create_factory < ::macos::copydesk           , ::user::copydesk > ();

//   create_factory < ::file::os_watcher          , ::file::watcher    > ();
//   create_factory < ::file::os_watch            , ::file::watch      > ();
   
   
   //create_factory < ::macos::shell   , ::user::shell > ();

}



