#include "framework.h"
#include "acme/operating_system/posix/shared_memory.h"


//
//
//extern ::i32 CLASS_DECL_ACME __win_main(HINSTANCE hInstance, HINSTANCE hPrevInstance, char_pointer lpCmdLine, ::i32 nCmdShow);
//




void CLASS_DECL_ACME __ios_term()
{

}



void CLASS_DECL_ACME __abort()
{
   __ios_term();
   abort();
}










void ios_message_box_factory(::factory::factory * pfactory)
{
   
   
}


void ios_factory(::factory::factory * pfactory)
{

   ios_message_box_factory(pfactory);

}




void operating_system_factory(::factory::factory * pfactory)
{

   pfactory->add_factory_item< ::posix::shared_memory, ::shared_memory>();

}
