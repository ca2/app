#include "framework.h"


runtime_error::runtime_error(const char * pszMessage):
   ::exception::error(pszMessage)
{

}


runtime_error::~runtime_error()
{

}



