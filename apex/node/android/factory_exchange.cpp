#include "framework.h"
#include "_android.h"
//#include "buffer.h"
//#include "apex/node/posix/pipe.h"


//namespace android
//{
//
//   namespace apex
//   {
//
//      factory_exchange::factory_exchange()
//      {
//
//
//         create_factory < ::android::file_system      , ::file_system              >(),1);
//         create_factory < ::android::dir_system       , ::dir_system         >(),1);
//         create_factory < stdio_file            >(__type(::file::text_file);
//         create_factory < file                  >(__type(::file::binary_file);
//         create_factory < file, ::file::file >();
//         create_factory < os                          >(__type(::apex::os),1);
//         create_factory < ::ansios::process           >(__type(::process::process), 10);
//         create_factory < ::ansios::pipe              >(__type(::process::pipe), 10);
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
//   } // namespace apex
//
//
//} // namespace android


void __node_apex_factory_exchange()
{


   //create_factory < ::android::buffer              , ::graphics::graphics        > ();


   create_factory < ::android::file_system         , ::file_system               > ();
   create_factory < ::android::dir_system          , ::dir_system                > ();
   create_factory < ::android::file_context        , ::file_context              > ();
   create_factory < ::android::dir_context         , ::dir_context               > ();
   //create_factory < ::android::file                , ::file::file                > ();
   create_factory < ::android::os_context          , ::os_context                > ();
   //create_factory < ::posix::pipe                  , ::process::pipe             > ();

   //create_factory < ::android::shell               , ::user::shell               > ();

   //create_factory < ::android::interaction_impl    , ::user::interaction_impl    > ();

   create_factory < ::file::os_watcher             , ::file::watcher             > ();

}







