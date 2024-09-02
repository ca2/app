#include "framework.h"


::aura::application * get_acid_app(::particle * pparticle)
{

   return new ::helloaura::application ();

}


#include "aura/os/windows/windows_aura.inl"
