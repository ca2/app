#include "framework.h"


::aura::application * get_acid_app(::object * pobject)
{

   return new ::helloaura::application();

}


#include "aura/os/windows/windows_aura.inl"