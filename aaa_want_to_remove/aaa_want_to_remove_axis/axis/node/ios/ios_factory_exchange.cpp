#include "framework.h"


namespace ios
{

   namespace axis
   {

   factory_exchange::factory_exchange()
   {

      add_factory_item < file_set             >   (__type(::file::set));
      add_factory_item < file_system                >   (__type(::file::system), 1);
      add_factory_item < dir                        >   (__type(::file::system_dir), 1);
      add_factory_item < port_forward               >   (__type(::net::port_forward), 1);
      add_factory_item < crypto                      >   (__type(::crypto::crypto), 1);
      add_factory_item < copydesk                   >   (__type(::user::copydesk), 1);

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



