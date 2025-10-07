

[MTAThread]
int main(Array < String ^ > ^ stra)
{

   auto psystem = øallocate ::platform::system();

   psystem->application_initialize();

   application_common(psystem);

   psystem->system_construct(stra);

   ::e_status estatus = psystem->start();

   int iErrorStatus = estatus.error_status();

   return iErrorStatus;


}


#include "openssl/applink.c"



