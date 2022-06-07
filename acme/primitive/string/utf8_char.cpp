#include "framework.h"


utf8_char::utf8_char(u64 u)
{

   m_chLen = (char)wd32_to_ansi_char(m_sz, (u32)u);

   m_sz[m_chLen] = '\0';

}


i32 utf8_char::parse(const char * psz)
{
   char chLen = 1 + trailingBytesForUTF8(*psz);
   char ch = 0;
   for (; ch < chLen; ch++)
   {
      if (*psz == 0)
      {
         m_chLen = -1;
         return -1;
      }
      m_sz[ch] = *psz++;
   }
   m_sz[ch] = '\0';
   m_chLen = chLen;
   return chLen;
}




