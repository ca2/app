#include "framework.h"


range_exception::range_exception(const ::scoped_string & scopedstrMessage):
   ::exception(scopedstrMessage)
{


}


range_exception::~range_exception()
{

}
