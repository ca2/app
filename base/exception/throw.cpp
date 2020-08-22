#include "framework.h"


void throw_memory_exception()
{

   __throw(memory_exception());

}


void throw_error_exception(const char * psz)
{

   __throw(::exception::error(psz));

}

