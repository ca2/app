#include "framework.h"
#include "_ios.h"


//
//namespace ios
//{
//
//namespace acme
//   {
//   factory_exchange::factory_exchange()
//   {
//
//      create_factory < stdio_file           >   (__type(::file::text_file));
//      create_factory < file                 >   (__type(::file::binary_file));
////      create_factory < file_set             >   (__type(::file::set));
//      create_factory < file                 >   (__type(::file::file));
//      //      create_factory < application                >   (__type(::acme::application), 1);
//      create_factory < ::thread               >   (__type(::thread));
//
//      create_factory < file_system                >   (__type(::file::system), 1);
////    create_factory < file_exception, ::file::exception >();
////    create_factory <    WinResource             >   (__type(::ca2::resource), 1);
//      //create_factory < application                >   (__type(::acme::application), 1);
//      create_factory < dir                        >   (__type(::file::system_dir), 1);
////    create_factory < folder_watch, ::ca2::folder_watch >();
////      create_factory < window_draw                >   (__type(::user::window_draw), 1);
//      //create_factory < thread               >   (__type(::thread_impl));
////      create_factory < window               >   (__type(::window));
//      create_factory < os                         >   (__type(::acme::os), 1);
////      create_factory < port_forward               >   (__type(::net::port_forward), 1);
////      create_factory < crypto                      >   (__type(::crypto::crypto), 1);
////      create_factory < copydesk                   >   (__type(::acme::copydesk), 1);
//  //    create_factory < ::ios2::printer                   >   (__type(::user::printer), 1);
//
//   }
//
//
//   factory_exchange::~factory_exchange()
//   {
//
//   }
//
//   } //   namespace acme
//
//} // namespace ios
//


void __node_aura_factory_exchange()
{

   create_factory < ::ios::file              , ::file::file             >();
   create_factory < ::ios::dir_context       , ::dir_context            >();
   create_factory < ::ios::file_context      , ::file_context           >();
   create_factory < ::ios::dir_system        , ::dir_system             >();
   create_factory < ::ios::file_system       , ::file_system            >();
   create_factory < ::ios::os_context        , ::os_context             >();
   create_factory < ::ios::shell             , ::user::shell            >();
   create_factory < ::ios::interaction_impl  , ::user::interaction_impl >();

   create_factory < ::file::os_watch       , ::file::watch            >();

   create_factory < ::file::os_watcher       , ::file::watcher            >();

   // create_factory < stdio_file         , ::file::text_file> ();
   // create_factory < file_set           , ::file::set));
   // create_factory < application        , ::acme::application), 1);
   // create_factory < ::thread           , ::thread));
   // create_factory < file_exception     , ::file::exception >();
   // create_factory < WinResource        , ::ca2::resource), 1);
   // create_factory < application        , ::acme::application), 1);
   // create_factory < ::ios::dir         , ::file::system_dir), 1);
   // create_factory < folder_watch       , ::ca2::folder_watch >();
   // create_factory < window_draw        , ::user::window_draw), 1);
   // create_factory < thread             , ::thread_impl));
   // create_factory < window             , ::window));
   // create_factory < port_forward       , ::net::port_forward), 1);
   // create_factory < crypto             , ::crypto::crypto), 1);
   // create_factory < copydesk           , ::acme::copydesk), 1);
   // create_factory < ::ios2::printer    , ::user::printer), 1);

   
}



