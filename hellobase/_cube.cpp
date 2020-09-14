#include "framework.h"

::aura::application * get_acid_app(::layered * pobjectContext)
{

   return new ::hellobase::application();

}


#include "aura/os/windows/windows_base.inl"