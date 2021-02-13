#include "framework.h"


user_exception::user_exception(::enum_status estatus, const char * pszMessage) :
   ::exception::exception(pszMessage, estatus)
{

}


user_exception::~user_exception()
{

}


