#include "framework.h"
#include "stringtow.h"


stringtow::stringtow(wstring & str, i32 iAllocCount)
{
   m_pwstring = &str;
   get_string_buffer(iAllocCount);
}

stringtow::~stringtow()
{

   release_string_buffer();

   if(m_pwstring != nullptr)
   {

      ::count len = utf8_to_unichar_len(c_str());

      auto psz = m_pwstring->get_string_buffer(len);

      utf8_to_unichar(psz, c_str(), len);

      m_pwstring->release_string_buffer(len);

   }

}
