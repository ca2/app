#include "framework.h"


not_implemented_exception::not_implemented_exception(const char * pszMessage, const ::e_status & estatus) :
   ::exception(estatus,  pszMessage)
{



}


not_implemented_exception::~not_implemented_exception()
{

}





