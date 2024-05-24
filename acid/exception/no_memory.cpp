#include "framework.h"
#include "no_memory.h"


no_memory::no_memory(const ::scoped_string & scopedstrMessage, const ::scoped_string & scopedstrDetails) :
   ::exception(error_no_memory, scopedstrMessage, scopedstrDetails)
{



}


no_memory::~no_memory()
{

}



