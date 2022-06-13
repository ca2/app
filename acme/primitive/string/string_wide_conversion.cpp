#include "framework.h"


wtostring::wtostring(string& str, i32 iAllocCount)
{
   
   m_pstringUtf8 = &str;
   
   get_string_buffer(iAllocCount);

}


wtostring::~wtostring()
{

   if(m_pstringUtf8 != nullptr)
   {

      *m_pstringUtf8 = unicode_to_utf8(m_pdata);

   }

}
