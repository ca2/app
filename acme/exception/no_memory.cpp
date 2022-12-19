#include "framework.h"
#include "no_memory.h"


no_memory::no_memory(const scoped_string & strMessage, const scoped_string & strDetails) :
   ::exception(error_no_memory, pszMessage, pszDetails)
{



}


no_memory::~no_memory()
{

}



