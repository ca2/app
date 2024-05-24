#include "framework.h"


todo::todo(const ::scoped_string & scopedstrMessage) :
   not_implemented(pszMessage)
{

}


todo::~todo()
{

}





CLASS_DECL_ACID void throw_todo()
{

   throw ::exception(todo);

}






