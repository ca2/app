#include "framework.h"
#include "cancel.h"


cancel_exception::cancel_exception(const char * pszMessage) :
   exception(pszMessage)
{

}

cancel_exception::~cancel_exception()
{

}

//bool cancel_exception::get_error_message(string & str,P::u32 pnHelpContext)
//{
//
//   str = what();
//
//   return true;
//
//}



