#include "framework.h"


os_history::os_history(::layered * pbojectContext) :
   ::object(pbojectContext)//,
   //::apex::history(pobject)
{
}


bool os_history::hist(const char * psz)
{

#if !defined(_UWP)

   ::apex::shell_launcher launcher(nullptr, "open", psz, "", "", e_display_normal);

   launcher.execute();

#endif

   return true;

}


