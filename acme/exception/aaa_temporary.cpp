#include "framework.h"


temporary_exception::temporary_exception(const ::scoped_string & scopedstrMessage):
   ::exception(scopedstrMessage)
{


}


temporary_exception::~temporary_exception()
{

}



