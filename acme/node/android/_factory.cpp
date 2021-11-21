#include "framework.h"
#include "_android.h"
//#include "buffer.h"
#include "acme/node/posix/pipe.h"


//namespace android
//{
//
//   namespace acme
//   {
//
//      factory_exchange::factory_exchange()
//      {
//
//
//         add_factory_item < ::android::file_system      , ::file_system              >(),1);
//         add_factory_item < ::android::dir_system       , ::dir_system         >(),1);
//         add_factory_item < stdio_file            >(__type(::file::text_file);
//         add_factory_item < file                  >(__type(::file::binary_file);
//         add_factory_item < file, ::file::file >();
//         add_factory_item < os                          >(__type(::acme::os),1);
//         add_factory_item < ::ansios::process           >(__type(::operating_system::process), 10);
//         add_factory_item < ::ansios::pipe              >(__type(::operating_system::pipe), 10);
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
//   } // namespace acme
//
//
//} // namespace android


void __node_acme_factory(::factory::factory * pfactory)
{


   //add_factory_item < ::android::buffer              , ::graphics::graphics        > ();


   //add_factory_item < ::android::file_system         , ::file_system               > ();
   //add_factory_item < ::android::dir_system          , ::dir_system                > ();
   //add_factory_item < ::android::file_context        , ::file_context              > ();
   //add_factory_item < ::android::dir_context         , ::dir_context               > ();
   add_factory_item < ::android::file                , ::file::file                > ();
   //add_factory_item < ::android::os_context          , ::os_context                > ();
   add_factory_item < ::posix::pipe                  , ::operating_system::pipe             > ();

   //add_factory_item < ::android::shell               , ::user::shell               > ();

   //add_factory_item < ::android::interaction_impl    , ::user::interaction_impl    > ();

   //add_factory_item < ::file::os_watcher             , ::file::watcher             > ();

}







