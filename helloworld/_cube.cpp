#include "framework.h"

::aura::application * get_acid_app(::layered * pobjectContext)
{

   return new ::helloworld::application();

}


#include "aura/os/windows/windows_core.inl"