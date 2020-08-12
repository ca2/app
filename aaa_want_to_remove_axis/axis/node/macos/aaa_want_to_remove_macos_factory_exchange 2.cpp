#include "framework.h"
#include "macos.h"


namespace macos
{


   namespace axis
   {


      factory_exchange::factory_exchange()
      {

         create_factory < window_draw                 >   (__type(::user::window_draw), 1);
         create_factory < interaction_impl      >   (__type(::user::interaction_impl));
         create_factory < copydesk                    >   (__type(::axis::copydesk), 1);
         create_factory < printer                     >   (__type(::user::printer), 1);
         create_factory < message_queue               >   (__type(::user::message_queue), 1);

      }


      factory_exchange::~factory_exchange()
      {

      }


   } // namespace axis


} //   namespace macos


void __node_axis_factory_exchange()
{

   ::macos::axis::factory_exchange factoryexchange();


}



