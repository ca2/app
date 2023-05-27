#include "framework.h"


os_history::os_history(::particle * pparticle) :
   ::object(pparticle)//,
   //::aura::history(pparticle)
{
}


bool os_history::hist(const ::string & psz)
{

#if !defined(UNIVERSAL_WINDOWS)

   ::aura::shell_launcher launcher(nullptr, "open", psz, "", "", e_display_normal);

   launcher.execute();

#endif

   return true;

}


