#include "framework.h"


index_out_of_bounds::index_out_of_bounds(const ::scoped_string & scopedstrMessage) :
   ::exception(scopedstrMessage, error_index_out_of_bounds)
{

}


index_out_of_bounds::~index_out_of_bounds()
{

}



