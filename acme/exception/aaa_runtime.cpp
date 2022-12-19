#include "framework.h"


runtime_exception::runtime_exception(const scoped_string & strMessage):
   ::exception(pszMessage)
{

}


runtime_exception::~runtime_exception()
{

}



