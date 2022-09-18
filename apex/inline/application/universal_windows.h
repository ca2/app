
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



//[MTAThread]
//int main(Array < String ^ > ^ stra)
//{
//
//   //auto psystem = p(::apex::system());
//
//   string strAppId = executable_get_app_id();
//
//   auto psystem = platform_create_system(strAppId);
//
//   if (!psystem)
//   {
//
//      return -1;
//
//   }
//
//   auto pappStartup = psystem->new_application(strAppId);
//
//   if (!pappStartup)
//   {
//
//      return -1;
//
//   }
//
//   __bind(psystem, m_pacmeapplicationStartup, pappStartup);
//
//   psystem->m_bConsole = false;
//   application_common(psystem);
//
//   psystem->system_construct(stra);
//
//   ::e_status estatus = psystem->start();
//
//   ::i32 iErrorStatus = estatus.error_status();
//
//   return iErrorStatus;
//
//
//}
//
//
//#include "openssl/applink.c"


//CLASS_DECL_EXPORT int unicode_main(int argc, wchar_t ** argv, const char * pszAppId)
//{
//
//   string strAppId = pszAppId;
//
//   set_main_user_thread();
//
//   auto psystem = platform_create_system(strAppId);
//
//   if (!psystem)
//   {
//
//      return -1;
//
//   }
//
//   psystem->m_bConsole = false;
//
//   psystem->m_bPreferNoFrameWindow = true;
//
//   application_common(psystem);
//
//   psystem->system_construct(argc, argv, nullptr);
//
//   //psystem->set_current_handles();
//
//   //   auto estatus = psystem->system_main();
//   //
//   //   if (!estatus)
//   //   {
//   //    
//   //      ::i32 iErrorStatus = estatus.error_status();
//   //
//   //      return iErrorStatus;
//   //
//   //   }
//
//   auto estatus = psystem->init_system();
//
//   if (!estatus)
//   {
//
//      return estatus.error_status();
//
//   }
//
//   auto pnode = psystem->node();
//
//   estatus = pnode->implement();
//
//   auto estatusEnd = psystem->end();
//
//   ::i32 iErrorStatus = estatus.error_status();
//
//   return iErrorStatus;
//
//
//}


//#include "openssl/applink.c"



