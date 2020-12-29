

[MTAThread]
int main(Array < String ^ > ^ stra)
{

   //auto psystem = p(::apex::system());

   string strAppId = executable_get_app_id();

   auto psystem = platform_create_system(strAppId);

   psystem->m_bConsole = false;

   application_common(psystem);

   psystem->system_construct(stra);

   ::e_status estatus = psystem->os_application_system_run();

   ::i32 iErrorStatus = estatus.error_status();

   return iErrorStatus;


}


#include "openssl/applink.c"



