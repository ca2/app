#include "framework.h"


user_exception::user_exception(const ::estatus & estatus, const char * pszMessage) :
   ::exception::exception(pszMessage, estatus)
{

}


user_exception::~user_exception()
{

}


