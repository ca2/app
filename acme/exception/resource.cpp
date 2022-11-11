#include "framework.h"
#include "resource.h"


resource_exception::resource_exception(const char * pszMessage) :
   ::exception(error_resource, pszMessage)
{

}


resource_exception::~resource_exception()
{

}



CLASS_DECL_ACME void throw_resource_exception(const char * pszMessage)
{

   throw ::resource_exception(pszMessage);

}



