#include "framework.h"
#include "acme/platform/app_core.h"
#include "application.h"
#include "acme/operating_system/_application.h"


CLASS_DECL_ACME int main_uwp(Array < String^ >^ stra, const ::scoped_string & scopedstrCommandLine)
{

   //int iStatus = -1;

   //::aura_main_struct mainstruct = {};

   //mainstruct.m_bConsole = false;
   //mainstruct.m_bDraw2d = true;
   //mainstruct.m_bUser = true;
   //mainstruct.m_bUserEx = true;
   //mainstruct.m_bShowApplicationInformation = false;

   auto psystem = __allocate ::platform::system();

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

