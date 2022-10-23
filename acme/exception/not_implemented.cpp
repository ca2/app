#include "framework.h"
#include "not_implemented.h"


not_implemented::not_implemented(const char * pszMessage, const ::e_status & estatus) :
   ::exception(estatus,  pszMessage)
{



}


not_implemented::~not_implemented()
{

}





