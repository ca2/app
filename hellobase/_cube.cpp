#include "framework.h"

::aura::application * get_acid_app(::context_object * pcontextobject)
{

   return new ::hellobase::application();

}


#include "aura/os/windows/windows_base.inl"