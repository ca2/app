

[MTAThread]
int main(Array < String ^ > ^ stra)
{

   auto psystem = __new(::acme::system());

   psystem->application_initialize();

   application_common(psystem);

   psystem->system_construct(stra);

   ::e_status estatus = psystem->os_application_system_run();

   ::i32 iErrorStatus = estatus.error_status();

   return iErrorStatus;


}


#include "openssl/applink.c"



