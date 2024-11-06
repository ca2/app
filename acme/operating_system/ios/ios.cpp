#include "framework.h"


//
//
//extern int CLASS_DECL_ACME __win_main(HINSTANCE hInstance, HINSTANCE hPrevInstance, char * lpCmdLine, int nCmdShow);
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
