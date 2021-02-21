
class RunBeforeMain
{
public:
   RunBeforeMain()
   {
      //HMODULE hNtDll = (HMODULE)LoadLibrary(_T("ntdll.dll"));
      //FARPROC lpNeeded = GetProcAddress(hNtDll, "NtWaitForMultipleObjects");
      //DebugBreakPoint();
   }
};

RunBeforeMain go;
[MTAThread]
int main(Array < String ^ > ^ stra)
{

   //auto psystem = p(::apex::system());

   string strAppId = executable_get_app_id();

   auto psystem = platform_create_system(strAppId);

   if (!psystem)
   {

      return -1;

   }

   auto papplicationStartup = psystem->new_application(strAppId);

   if (!papplicationStartup)
   {

      return -1;

   }

   __bind(psystem, m_papplicationStartup, papplicationStartup);

   psystem->m_bConsole = false;
   application_common(psystem);

   psystem->system_construct(stra);

   ::e_status estatus = psystem->start();

   ::i32 iErrorStatus = estatus.error_status();

   return iErrorStatus;


}


#include "openssl/applink.c"



