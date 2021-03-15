#include "framework.h"

::aura::application * get_acid_app(::context_object * pcontextobject)
{

   return new ::helloworld::application();

}


#include "aura/os/windows/windows_core.inl"