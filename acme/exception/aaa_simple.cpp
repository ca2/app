#include "framework.h"


//::::exception(const char * pszMessage):
//   ::matter(pobject),
//   ::callstack(pobject),
//   ::exception()
//{
//
//   if(pszMessage == nullptr)
//   {
//
//      cat_exception(":simple(nullptr)");
//
//   }
//   else
//   {
//
//      cat_exception(":simple(\"");
//      cat_exception(pszMessage);
//      cat_exception("\")");
//
//   }
//
//   cat_message(pszMessage);
//
//}
//
//
//::::exception(const char * pszMessage, ::acme::application * papp):
//   matter(papp),
//   ::callstack(papp),
//   ::exception(papp)
//{
//
//   if(pszMessage == nullptr)
//   {
//
//      cat_exception(":simple(nullptr)");
//
//   }
//   else
//   {
//
//      cat_exception(":simple(\"");
//      cat_exception(pszMessage);
//      cat_exception("\")");
//
//   }
//
//   cat_message(pszMessage);
//
//}
//
//
//::exception::~exception()
//{
//
//}
//
//
//bool ::exception::get_error_message(string & str,P::u32 pnHelpContext)
//{
//
//   str = what();
//
//   return true;
//
//}
//
//
//
