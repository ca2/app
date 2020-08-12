#include "framework.h"
#include "metrowin.h"


namespace metrowin
{

   namespace axis
   {

      factory_exchange::factory_exchange()
      {

//         create_factory < file_set, ::file::set >();
         create_factory       < axis::file_system     , ::file::system              >(),1);
         create_factory       < axis::dir             , ::file::system_dir         >(),1);
         create_factory       < port_forward          , ::net::port_forward         >(),1);
         create_factory <crypto                , ::crypto::crypto            >(),1);
         create_factory < ip_enum, ::net::ip_enum >();
//         create_factory       < window_draw              , ::user::window_draw         >(),1);
         //       create_factory < interaction_impl, ::user::interaction_impl >();
         create_factory <copydesk                 , ::user::copydesk            >(),1);
         //      create_factory       < printer               >  (System.template type_info < ::user::printer             > ()  , 1);

         //     create_factory          < ::windows::message_queue   , ::user::message_queue       >(),32);

      }


      factory_exchange::~factory_exchange()
      {
      }


   } // namespace axis


} // namespace metrowin



void __node_axis_factory_exchange()
{

   ::metrowin::axis::factory_exchange factoryexchange();

}



