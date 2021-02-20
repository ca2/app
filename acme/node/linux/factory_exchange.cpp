#include "framework.h"
#include "acme/os/console.h"
//#include "shell_linux.h"
#include "console.h"
#include "acme/node/posix/pipe.h"
//#include "acme/node/linux/process.h"
#include "_linux.h"
#include "acme/node/_node2.h"
#include "acme/os/_os2.h"
#include "acme/node/posix/file_memory_map.h"
//#include "copydesk.h"


void __node_acme_factory_exchange(::factory_map * pfactorymap)
{

   //create_factory < ::linux::dir_system         , ::dir_system             >();
   //create_factory < ::linux::dir_context        , ::dir_context            >();
   //create_factory < ::linux::file_system        , ::file_system            >();
   //create_factory < ::linux::file_context       , ::file_context           >();
   create_factory < ::linux::stdio_file         , ::file::text_file        >();
   create_factory < ::linux::file               , ::file::file             >();
   //create_factory < ::linux::os_context         , ::os_context             >();
   //create_factory < ::ansios::process           , ::process::process       >();
   create_factory < ::posix::pipe               , ::process::pipe          >();
   create_factory < ::linux::console            , ::console::console       >();
   //create_factory < ::xlib::buffer              , ::graphics::graphics     >();
   //create_factory < ::linux::interaction_impl   , ::user::interaction_impl >();
   //create_factory < ::linux::copydesk           , ::user::copydesk         >();

   //create_factory < ::file::os_watcher          , ::file::watcher          >();
   //create_factory < ::file::os_watch            , ::file::watch            >();


//   create_factory < ::linux::shell              , ::user::shell            >();

   create_factory < ::posix::file_memory_map, ::file::memory_map >();


}



