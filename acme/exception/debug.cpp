#include "framework.h"


unsigned char OriginalBytes[5] = {0};


CLASS_DECL_ACME int is_debugger_attached()
{

   return __node_is_debugger_attached() != false;

}



//CLASS_DECL_ACME void throw_what_exclamation_exclamation(const ::scoped_string & scopedstr)
//{
//
//   throw what_exclamation_exclamation(psz);
//
//}


//


//assert_exception::assert_exception(const ::scoped_string & scopedstrFile, long lLine)
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
//misc_exception::misc_exception(const ::scoped_string & scopedstrMessage) :
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
//   CLASS_DECL_ACME string error_message(unsigned int dwError)
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


int g_iDebuggingConsumer = 0;


CLASS_DECL_ACME void this_is_a_debugging_consumer(int & i)
{

   g_iDebuggingConsumer += i;

}



