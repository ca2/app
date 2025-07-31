#include "framework.h"


invalid_index_exception::invalid_index_exception(const ::scoped_string & scopedstrMessage):
   invalid_argument_exception(scopedstrMessage)
{


}


invalid_index_exception::~invalid_index_exception()
{

}
