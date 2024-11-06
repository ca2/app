#include "framework.h"
#include "stringtow.h"


stringtow::stringtow(wstring & str, int iAllocCount)
{
   
   m_pwstring = &str;
   
   m_pszBuffer = m_str.get_buffer(iAllocCount);

}


stringtow::~stringtow()
{

   m_pszBuffer = nullptr;

   m_str.release_buffer();

   if(m_pwstring != nullptr)
   {
      
      *m_pwstring = m_str;

   }

}



