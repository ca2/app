#include "framework.h"
#include "acme/os/console.h"
#include "console_window.h"
#include "_linux.h"
#include "aura/node/_node.h"
#include "aura/os/_os.h"
//#include "copydesk.h"


void __node_aura_factory_exchange(::factory_map * pfactorymap)
{

   create_factory < ::linux::console            , ::console::console       >();
   //create_factory < ::xlib::buffer              , ::graphics::graphics     >();
   create_factory < ::linux::interaction_impl   , ::user::interaction_impl >();
   //create_factory < ::linux::copydesk           , ::user::copydesk         >();

}



