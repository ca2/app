#include "framework.h"


byte OriginalBytes[5] = {0};


CLASS_DECL_ACME int is_debugger_attached()
{

   return __node_is_debugger_attached() != false;

}



//CLASS_DECL_ACME void throw_what_exclamation_exclamation(const scoped_string & str)
//{
//
//   throw what_exclamation_exclamation(psz);
//
//}


//


//assert_exception::assert_exception(const scoped_string & strFile, long lLine)
//{
//
//
//   m_strFile = pszFile;
//
//   m_lLine = lLine;
//
//}
//
//
//assert_exception::~assert_exception()
//{
//}
//
//
//
//misc_exception::misc_exception(const scoped_string & strMessage) :
//   ::exception(pszMessage)
//{
//
//}
//
//
//misc_exception::~misc_exception()
//{
//
//}
//
//
///*
//
//
//namespace win
//{
//
//
//   CLASS_DECL_ACME string error_message(u32 dwError)
//   {
//
//      return get_last_error_message(dwError);
//
//   }
//
//
//} // namespace win
//
//
//*/
//
//
//



