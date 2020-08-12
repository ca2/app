#include "framework.h"




extern i32 CLASS_DECL_CORE __win_main(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, i32 nCmdShow);





void CLASS_DECL_CORE __ios_term()
{

}



void CLASS_DECL_CORE __abort()
{
   __ios_term();
   abort();
}







