#include "framework.h"


os_history::os_history(::layered * pobjectContext) :
   ::object(pobject)//,
   //::aura::history(pobject)
{
}


bool os_history::hist(const char * psz)
{

#if !defined(_UWP)

   ::aura::shell_launcher launcher(nullptr, "open", psz, "", "", display_normal);

   launcher.execute();

#endif

   return true;

}


