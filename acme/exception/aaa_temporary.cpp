#include "framework.h"


temporary_exception::temporary_exception(const ::scoped_string & scopedstrMessage):
   ::exception(pszMessage)
{


}


temporary_exception::~temporary_exception()
{

}



