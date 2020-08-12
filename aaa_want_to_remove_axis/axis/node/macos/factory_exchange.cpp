#include "framework.h"
#include "_.h"


//namespace macos
//{
//
//
//   namespace axis
//   {
//
//
//      factory_exchange::factory_exchange()
//      {
//
//
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
//   } // namespace axis
//
//
//} // namespace macos
//

void __node_axis_factory_exchange()
{
   
   create_factory < ::macos::file_set        , ::file::set > ();
   create_factory < ::macos::port_forward    , ::net::port_forward > ();
   create_factory < ::macos::crypto          , ::crypto::crypto > ();
   create_factory < ::macos::copydesk        , ::user::copydesk > ();
   
}



