#include "framework.h"




extern i32 CLASS_DECL_AURA __win_main(HINSTANCE hInstance, HINSTANCE hPrevInstance, char * lpCmdLine, i32 nCmdShow);





void CLASS_DECL_AURA __ios_term()
{

}



void CLASS_DECL_AURA __abort()
{
   __ios_term();
   abort();
}







