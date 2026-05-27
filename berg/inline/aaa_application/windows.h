

::i32 WINAPI _tWinMain(HINSTANCE hinstance, HINSTANCE hPrevInstance, char_pointer pCmdLine, ::i32 nCmdShow)
{

   auto psystem = allocateø ::aura::system();

   psystem->application_initialize();

   application_common(psystem);

   psystem->system_construct(hinstance, hPrevInstance, pCmdLine, nCmdShow);

   psystem->set_current_handles();

   ::e_status estatus = psystem->__thread_procedure();

   ::i32 iErrorStatus = estatus.error_status();

   return iErrorStatus;

}


#include "openssl/applink.c"



