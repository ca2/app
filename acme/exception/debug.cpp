#include "framework.h"


byte OriginalBytes[5] = {0};



CLASS_DECL_ACME int is_debugger_attached()
{

   return __node_is_debugger_attached() != FALSE;

}




CLASS_DECL_ACME int throw_assert_exception(const char * pszFileName,int iLineNumber)
{

   __throw(assert_exception(pszFileName,iLineNumber));

}



assert_exception::assert_exception(const char * pszFile, long lLine)
{


   m_strFile = pszFile;

   m_lLine = lLine;

}


assert_exception::~assert_exception()
{
}



misc_exception::misc_exception(const char * pszMessage) :
   ::exception::exception(pszMessage)
{

}


misc_exception::~misc_exception()
{

}


/*


namespace win
{


   CLASS_DECL_ACME string error_message(u32 dwError)
   {

      return get_system_error_message(dwError);

   }


} // namespace win


*/



