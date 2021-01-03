#include "framework.h"


user_exception::user_exception(const ::e_status & estatus, const char * pszMessage) :
   ::exception::exception(pszMessage, estatus)
{

}


user_exception::~user_exception()
{

}


