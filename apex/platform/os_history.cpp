#include "framework.h"
#include "shell_launcher.h"

os_history::os_history(::object * pobject) //:
//   ::object(pbojectContext)//,
   //::apex::history(pobject)
{
}


bool os_history::hist(const char * psz)
{

#if !defined(_UWP)

   //pointer <  > plauncher;
   
   auto plauncher = __create<::apex::shell_launcher>();

   if (!plauncher)
   {

      return plauncher;

   }
   
    plauncher->setup((oswindow) nullptr, "open", psz, "", "", e_display_restored);

   //if (!estatus)
   //{

   //   return estatus;

   //}

   plauncher->launch();

#endif

   return true;

}


