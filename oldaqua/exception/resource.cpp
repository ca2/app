#include "framework.h"


resource_exception::resource_exception(const char * pszMessage) :
   ::exception::exception(pszMessage)
{

}


resource_exception::~resource_exception()
{

}



CLASS_DECL_AQUA void throw_resource_exception(const char * psz)
{

   __throw(resource_exception(psz));

}
