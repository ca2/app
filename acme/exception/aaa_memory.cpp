#include "framework.h"


memory_exception::memory_exception(const char * pszMessage) :
   ::exception(pszMessage)
{



}


memory_exception::~memory_exception()
{

}


