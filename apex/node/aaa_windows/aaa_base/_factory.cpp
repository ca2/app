#include "framework.h" 
#include "base/user/_.h"
#include "_windows.h"


 namespace base
 {


    namespace windows
    {


       factory_exchange::factory_exchange()
       {

          add_factory_item < ::windows::print_job, ::user::print_task >();

       }


       factory_exchange::~factory_exchange()
       {

       }


    } // namespace windows


 } // namespace base


 void __node_base_factory(::factory::factory * pfactory)
 {

    ::base::windows::factory_exchange factoryexchange;

 }




