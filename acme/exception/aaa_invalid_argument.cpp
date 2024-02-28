#include "framework.h"


invalid_argument_exception::invalid_argument_exception(const ::scoped_string & scopedstrMessage):
   ::exception(pszMessage)
{

}


invalid_argument_exception::~invalid_argument_exception()
{

}



