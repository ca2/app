#include "framework.h"


runtime_exception::runtime_exception(const ::scoped_string & scopedstrMessage):
   ::exception(scopedstrMessage)
{

}


runtime_exception::~runtime_exception()
{

}



