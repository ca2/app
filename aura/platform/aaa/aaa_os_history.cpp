#include "framework.h"


os_history::os_history(::object * pobject) :
   ::object(pobject)//,
   //::aura::history(pobject)
{
}


bool os_history::hist(const ::string & psz)
{

#if !defined(_UWP)

   ::aura::shell_launcher launcher(nullptr, "open", psz, "", "", e_display_restored);

   launcher.execute();

#endif

   return true;

}


