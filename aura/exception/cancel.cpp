#include "framework.h"



cancel_exception::cancel_exception(const char * pszMessage) :
   exception(pszMessage)
{

}

cancel_exception::~cancel_exception()
{

}

//bool cancel_exception::get_error_message(string & str,PUINT pnHelpContext)
//{
//
//   str = what();
//
//   return true;
//
//}



