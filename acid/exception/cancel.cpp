#include "framework.h"
#include "cancel.h"


cancel_exception::cancel_exception(const ::scoped_string & scopedstrMessage) :
   exception(error_cancelled, scopedstrMessage)
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



