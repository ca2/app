#include "framework.h"


overflow_exception::overflow_exception(const ::scoped_string & scopedstrMessage):
   ::exception(scopedstrMessage)
{


}


overflow_exception::~overflow_exception()
{

}
