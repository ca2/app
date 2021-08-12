#include "framework.h"
#include "acme/platform/app_core.h"
#include "application.h"
#include "acme/os/_application.h"


CLASS_DECL_ACME i32 main_uwp(Array < String^ >^ stra, const ::string & strCommandLine)
{

   //int iStatus = -1;

   //::aura_main_struct mainstruct = {};

   //mainstruct.m_bConsole = false;
   //mainstruct.m_bDraw2d = true;
   //mainstruct.m_bUser = true;
   //mainstruct.m_bUserEx = true;
   //mainstruct.m_bShowApplicationInformation = false;

   auto psystem = __new(class ::system());

   psystem->construct_system(stra);

   if (!psystem->system_beg())
   {

      throw ::exception::exception("The application didn't started.");

   }

      bool bOk = psystem->system_ini();

      if (!bOk)
      {

         throw ::exception::exception("The application didn't started. (2)");

      }

      psystem->system_start();

      iStatus = psystem->system_run();

      psystem->system_end();

   }

   return iStatus;

}

