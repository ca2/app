#include "framework.h"
#include "aura/platform/app_core.h"
#include "application.h"
#include "aura/os/_application.h"


CLASS_DECL_CORE i32 main_uwp(Array < String^ >^ stra, const ::string & strCommandLine)
{

   //int iStatus = -1;

   //::aura_main_struct mainstruct = {};

   //mainstruct.m_bConsole = false;
   //mainstruct.m_bDraw2d = true;
   //mainstruct.m_bUser = true;
   //mainstruct.m_bUserEx = true;
   //mainstruct.m_bShowApplicationInformation = false;

   auto psystem = __new(::aura::system());

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

