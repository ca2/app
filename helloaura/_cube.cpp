#include "framework.h"


::aura::application * get_acid_app(::particle * pparticle)
{

   return __new< ::helloaura::application >();

}


#include "aura/os/windows/windows_aura.inl"
