#include "framework.h"


os_exception::os_exception(const scoped_string & strMessage):
   ::exception(pszMessage)
{

}


os_exception::~os_exception()
{

}
