#include "framework.h"


index_out_of_bounds::index_out_of_bounds(const char * pszMessage) :
   ::exception(pszMessage, error_index_out_of_bounds)
{

}


index_out_of_bounds::~index_out_of_bounds()
{

}



