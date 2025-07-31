#include "framework.h"


os_exception::os_exception(const ::scoped_string & scopedstrMessage):
   ::exception(scopedstrMessage)
{

}


os_exception::~os_exception()
{

}
