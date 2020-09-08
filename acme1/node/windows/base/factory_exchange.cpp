#include "framework.h" 
#include "acme/user/_.h"
#include "_windows.h"


 namespace acme
 {


    namespace windows
    {


       factory_exchange::factory_exchange()
       {

          create_factory < ::windows::print_job, ::user::print_task >();

       }


       factory_exchange::~factory_exchange()
       {

       }


    } // namespace windows


 } // namespace acme


 void __node_base_factory_exchange()
 {

    ::acme::windows::factory_exchange factoryexchange;

 }




