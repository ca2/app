#include "framework.h"
#include "_windows.h" 


namespace windows
{


   factory_exchange::factory_exchange()
   {

      create_factory          < port_forward, ::net::port_forward         >();
      create_factory < crypto, ::crypto::crypto            >();
      create_factory < ip_enum,::net::ip_enum              >();
      create_factory < ::windows::copydesk, ::user::copydesk            >();



//      create_factory < ::windows::copydesk        , ::user::copydesk            >(),1);
//      create_factory < ::windows::print_job, ::user::print_task >();
//      create_factory          < ::windows::message_queue   , ::user::message_queue       >(),32);

   }


   factory_exchange::~factory_exchange()
   {
   }


} // namespace windows


void __node_axis_factory_exchange()
{

   windows::factory_exchange factoryexchange();

}




