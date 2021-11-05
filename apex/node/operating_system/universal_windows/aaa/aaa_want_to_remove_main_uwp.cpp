#include "framework.h"
#include "apex/platform/app_core.h"
#include "application.h"
#include "apex/os/_application.h"


CLASS_DECL_APEX i32 main_uwp(Array < String^ >^ stra, const ::string & strCommandLine)
{

   //int iStatus = -1;

   //::apex_main_struct mainstruct = {};

   //mainstruct.m_bConsole = false;
   //mainstruct.m_bDraw2d = true;
   //mainstruct.m_bUser = true;
   //mainstruct.m_bUserEx = true;
   //mainstruct.m_bShowApplicationInformation = false;

   auto psystem = __new(::apex::system());

   psystem->construct_system(stra);

   if (!psystem->system_beg())
   {

      throw ::exception("The application didn't started.");

   }

      bool bOk = psystem->system_ini();

      if (!bOk)
      {

         throw ::exception("The application didn't started. (2)");

      }

      psystem->system_start();

      iStatus = psystem->system_run();

      psystem->system_end();

   }

   return iStatus;

}

