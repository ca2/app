#include "framework.h"
#include "resource.h"


resource_exception::resource_exception(const scoped_string & strMessage) :
   ::exception(error_resource, pszMessage)
{

}


resource_exception::~resource_exception()
{

}



CLASS_DECL_ACME void throw_resource_exception(const scoped_string & strMessage)
{

   throw ::resource_exception(pszMessage);

}



