#include "framework.h"


temporary_exception::temporary_exception(const char * pszMessage):
   ::exception(pszMessage)
{


}


temporary_exception::~temporary_exception()
{

}



