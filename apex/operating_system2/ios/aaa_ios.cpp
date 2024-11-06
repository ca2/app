#include "framework.h"


//
//
//extern int CLASS_DECL_APEX __win_main(HINSTANCE hInstance, HINSTANCE hPrevInstance, char * lpCmdLine, int nCmdShow);
//




void CLASS_DECL_APEX __ios_term()
{

}



void CLASS_DECL_APEX __abort()
{
   __ios_term();
   abort();
}







