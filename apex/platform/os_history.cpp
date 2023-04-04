#include "framework.h"
#include "os_history.h"
#include "shell_launcher.h"


os_history::os_history(::particle * pparticle) //:
//   ::object(pbojectContext)//,
   //::apex::history(pparticle)
{
}


bool os_history::hist(const ::scoped_string & scopedstr)
{

#if !defined(UNIVERSAL_WINDOWS)

   //pointer <  > plauncher;
   
   auto plauncher = __create<::apex::shell_launcher>();

   if (!plauncher)
   {

      return plauncher;

   }
   
    plauncher->setup((oswindow) nullptr, "open", scopedstr, "", "", e_display_restored);

   //if (!estatus)
   //{

   //   return estatus;

   //}

   plauncher->launch();

#endif

   return true;

}


