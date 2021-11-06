#include "framework.h"

::aura::application * get_acid_app(::object * pobject)
{

   return new ::helloworld::application();

}


#include "aura/os/windows/windows_core.inl"
