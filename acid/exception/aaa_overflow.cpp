#include "framework.h"


overflow_exception::overflow_exception(const ::scoped_string & scopedstrMessage):
   ::exception(pszMessage)
{


}


overflow_exception::~overflow_exception()
{

}
