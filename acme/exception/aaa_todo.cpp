#include "framework.h"


todo::todo(const ::scoped_string & scopedstrMessage) :
   not_implemented(scopedstrMessage)
{

}


todo::~todo()
{

}





CLASS_DECL_ACME void throw_todo()
{

   throw ::exception(todo);

}






