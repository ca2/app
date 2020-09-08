#include "framework.h"




extern i32 CLASS_DECL_AQUA __win_main(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, i32 nCmdShow);





void CLASS_DECL_AQUA __ios_term()
{

}



void CLASS_DECL_AQUA __abort()
{
   __ios_term();
   abort();
}







