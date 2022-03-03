#include "framework.h"
#include "no_memory.h"


no_memory::no_memory(const char * pszMessage, const char * pszDetails) :
   ::exception(error_no_memory, pszMessage, pszDetails)
{



}


no_memory::~no_memory()
{

}


