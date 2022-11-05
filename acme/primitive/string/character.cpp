#include "framework.h"
#include "character.h"
#include "string.h"


//character::utf8_char(u64 u)
//{
//
//   m_chLen = (char)wd32_to_ansi_char(m_sz, (u32)u);
//
//   m_sz[m_chLen] = '\0';
//
//}
//


wd32char character::parse_utf8(const char * pszUtf8)
{

   ::i32 iLen;

   return unicode_index_len(pszUtf8, iLen);

}


//char chLen = 1 + trailingBytesForUTF8(*pszUtf8);
//char ch = 0;
//for (; ch < chLen; ch++)
//{
//   if (*psz == 0)
//   {
//      m_chLen = -1;
//      return -1;
//   }
//   m_sz[ch] = *psz++;
//}
//m_sz[ch] = '\0';
//m_chLen = chLen;
//return chLen;



