#include "framework.h"
#include "not_implemented.h"


not_implemented::not_implemented(const scoped_string & strMessage, const ::e_status & estatus) :
   ::exception(estatus,  pszMessage)
{



}


not_implemented::~not_implemented()
{

}





