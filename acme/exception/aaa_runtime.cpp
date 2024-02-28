#include "framework.h"


runtime_exception::runtime_exception(const ::scoped_string & scopedstrMessage):
   ::exception(pszMessage)
{

}


runtime_exception::~runtime_exception()
{

}



