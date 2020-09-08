#include "framework.h"


memory_exception::memory_exception(const char * pszMessage) :
   ::exception::exception(pszMessage)
{



}


memory_exception::~memory_exception()
{

}


