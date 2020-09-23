

[MTAThread]
int main(Array < String ^ > ^ stra)
{

   auto psystem = __new(::apex::system());

   psystem->m_bConsole = false;

   application_common(psystem);

   psystem->system_construct(stra);

   ::estatus estatus = os_application_system_run(psystem);

   ::i32 iErrorStatus = estatus.error_status();

   return iErrorStatus;


}


#include "openssl/applink.c"



