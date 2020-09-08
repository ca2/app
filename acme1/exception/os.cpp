#include "framework.h"


os_exception::os_exception(const char * pszMessage):
   ::exception::exception(pszMessage)
{

}


os_exception::~os_exception()
{

}
