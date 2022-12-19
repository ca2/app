#include "framework.h"


temporary_exception::temporary_exception(const scoped_string & strMessage):
   ::exception(pszMessage)
{


}


temporary_exception::~temporary_exception()
{

}



