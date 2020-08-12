#include "framework.h"
#include "_.h"


namespace linux
{


   namespace axis
   {


      factory_exchange::factory_exchange()
      {

         //create_factory < file_system                , ::file::system> ();
         //create_factory < dir                        , ::file::system_dir> ();
         create_factory < port_forward               , ::net::port_forward> ();
         //create_factory <crypto               , ::crypto::crypto> ();
         create_factory <ip_enum              , ::net::ip_enum > ();





//         create_factory <copydesk             , ::user::copydesk> ();
//         create_factory <message_queue        , ::user::message_queue> ();


      }


      factory_exchange::~factory_exchange()
      {

      }


   } // namespace axis


} // namespace win


void __node_axis_factory_exchange()
{

   linux::axis::factory_exchange factoryexchange;

}




