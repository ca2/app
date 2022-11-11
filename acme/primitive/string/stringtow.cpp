#include "framework.h"
#include "stringtow.h"


stringtow::stringtow(wstring & str, i32 iAllocCount)
{
   
   m_pwstring = &str;
   
   m_pszBuffer = m_str.get_string_buffer(iAllocCount);

}


stringtow::~stringtow()
{

   m_pszBuffer = nullptr;

   m_str.release_string_buffer();

   if(m_pwstring != nullptr)
   {
      
      *m_pwstring = m_str;

   }

}



