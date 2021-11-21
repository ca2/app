#include "framework.h"


namespace ios
{

   namespace axis
   {

   factory_exchange::factory_exchange()
   {

      create_factory < file_set             >   (__type(::file::set));
      create_factory < file_system                >   (__type(::file::system), 1);
      create_factory < dir                        >   (__type(::file::system_dir), 1);
      create_factory < port_forward               >   (__type(::net::port_forward), 1);
      create_factory < crypto                      >   (__type(::crypto::crypto), 1);
      create_factory < copydesk                   >   (__type(::user::copydesk), 1);

   }


   factory_exchange::~factory_exchange()
   {

   }

   } // namespace axis

} // namespace ios



void __node_axis_factory(::factory::factory * pfactory)
{

   ios::axis::factory_exchange factoryexchange();

}



