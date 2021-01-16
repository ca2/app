

i32 WINAPI _tWinMain(HINSTANCE hinstance, HINSTANCE hPrevInstance, TCHAR * pCmdLine, int nCmdShow)
{

   string strAppId;

#ifdef _APP_ID

   strAppId = _APP_ID;

#else

   strAppId = executable_get_app_id(hinstance);

#endif;

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

   string strCommandLine(pCmdLine);

   psystem->system_construct(hinstance, hPrevInstance, strCommandLine, nCmdShow);

   psystem->set_current_handles();

   ::e_status estatus = psystem->do_task();

   ::i32 iErrorStatus = estatus.error_status();

   return iErrorStatus;

}


#include "openssl/applink.c"



