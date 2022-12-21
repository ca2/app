#include "framework.h"
#include "resource.h"


resource_exception::resource_exception(const ::scoped_string & scopedstrMessage) :
   ::exception(error_resource, scopedstrMessage)
{

}


resource_exception::~resource_exception()
{

}



CLASS_DECL_ACME void throw_resource_exception(const ::scoped_string & scopedstrMessage)
{

   throw ::resource_exception(scopedstrMessage);

}



