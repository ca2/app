#include "framework.h"


runtime_exception::runtime_exception(const char * pszMessage):
   ::exception(pszMessage)
{

}


runtime_exception::~runtime_exception()
{

}



