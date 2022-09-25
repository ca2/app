#include "framework.h"

::aura::application * get_acid_app(::object * pobject)
{

   return memory_new ::helloworld::application();

}


#include "aura/os/windows/windows_core.inl"
