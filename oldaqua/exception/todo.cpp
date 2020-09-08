#include "framework.h"


todo::todo(const char * pszMessage) :
   not_implemented(pszMessage)
{

}


todo::~todo()
{

}





CLASS_DECL_AQUA void throw_todo()
{

   __throw(todo());

}






