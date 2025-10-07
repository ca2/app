#include "framework.h"


not_supported_exception::not_supported_exception(const ::scoped_string & scopedstrMessage) :
   interface_only_exception(scopedstrMessage)
{

}


not_supported_exception::~not_supported_exception()
{

}





