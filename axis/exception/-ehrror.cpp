#include "framework.h"


namespace exception
{


   error::error(const char * pszMessage, const ::estatus & estatus):
      ::exception::exception(pszMessage, estatus)
   {

   }


   error::~error()
   {

   }


} // namespace exception



index_out_of_bounds::index_out_of_bounds(const char * pszMessage) :
   ::exception::error(pszMessage, error_index_out_of_bounds)
{

}




index_out_of_bounds::~index_out_of_bounds()
{

}


