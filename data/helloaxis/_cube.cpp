#include "framework.h"

::aura::application * get_acid_app(::context_object * pcontextobject)
{

   return new ::helloaxis::application();

}


#include "aura/os/windows/windows_axis.inl"