#include "framework.h"


os_history::os_history(::object * pobject) //:
//   ::object(pbojectContext)//,
   //::apex::history(pobject)
{
}


bool os_history::hist(const char * psz)
{

#if !defined(_UWP)

   //__pointer() plauncher;
   
   auto plauncher = __create<::apex::shell_launcher>();

   if (!plauncher)
   {

      return plauncher;

   }
   
   auto estatus = plauncher->setup((oswindow) nullptr, "open", psz, "", "", e_display_normal);

   if (!estatus)
   {

      return estatus;

   }

   plauncher->launch();

#endif

   return true;

}


