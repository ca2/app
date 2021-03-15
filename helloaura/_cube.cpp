#include "framework.h"


::aura::application * get_acid_app(::context_object * pcontextobject)
{

   return new ::helloaura::application();

}


#include "aura/os/windows/windows_aura.inl"