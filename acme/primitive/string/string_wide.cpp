#include "framework.h"


natural_meta_data < string_meta_data < wd16char > > * g_pwd16stringNil = nullptr;

natural_meta_data < string_meta_data < wd32char > > * g_pwd32stringNil = nullptr;





template < >
CLASS_DECL_ACME natural_meta_data < string_meta_data < wd16char > > * __nil < natural_meta_data < string_meta_data < wd16char > > >()
{

    return g_pwd16stringNil;

}

template < >
CLASS_DECL_ACME natural_meta_data < string_meta_data < wd32char > > * __nil < natural_meta_data < string_meta_data < wd32char > > >()
{

    return g_pwd32stringNil;

}

//const unichar * wstring::g_pszWindowsBBQBUNC(L"\\\\?\\UNC");
//const unichar * wstring::g_pszWindowsBBQB(L"\\\\?\\");
//const unichar * wstring::g_pszWindowsBB(L"\\\\");
//
//
//wstring::wstring(const char* psz)
//{
//
//   operator = (psz);
//
//}
//
//
//wstring::wstring(const u8* psz)
//{
//
//   operator = ((const char*)psz);
//
//}
//
//wstring::wstring(const u8* psz, strsize iSize)
//{
//
//   operator = ((const char*)string(psz, iSize));
//
//}
//
//
//wstring::wstring(const unichar* pwsz, strsize strsize)
//{
//
//   if (::is_null(pwsz))
//   {
//
//      if (strsize != 0)
//      {
//
//         __throw(error_invalid_argument);
//
//      }
//
//      natural_release();
//
//   }
//   else
//   {
//
//      auto pNew = create_meta_data(char_length_to_byte_length(strsize + 1));
//
//      if (pNew == nullptr)
//      {
//
//         throw_memory_exception();
//
//      }
//
//      POINTER::operator=(pNew);
//
//      memcpy(pNew->m_pdata, pwsz, pNew->memsize());
//
//      set_length(strsize);
//
//   }
//
//}
//
//
//wstring::wstring(const unichar* pwsz)
//   : string_base(pwsz, string_safe_length(pwsz))
//{
//
//
//}
//
////
////void wstring::assign(const unichar* pwsz)
////{
////
////   POINTER::operator=(pwsz);
////
////}
//
//
//wstring::wstring(const wstring& wstr)
//{
//
//   POINTER::operator=(wstr);
//
//}
//
//
//wstring::~wstring()
//{
//
//   natural_release();
//
//}
//
////unichar* wstring::alloc(::count iCount)
////{
////
////   if (m_psz != nullptr && iCount < me()->m_iAllocation)
////   {
////
////      return m_psz;
////
////   }
////
////   wstring_data::_free(m_psz);
////
////   m_psz = (unichar*)wstring_data::alloc(iCount);
////
////   return m_psz;
////
////}
//
//
//wstring& wstring::operator = (const wstring& wstr)
//{
//
//   POINTER::operator =(wstr);
//
//   return *this;
//
//}
//
//wstring& wstring::operator = (const unichar* pwsz)
//{
//
//   assign(pwsz);
//
//   return *this;
//
//}
//
//wstring& wstring::operator = (const char * psz)
//{
//   assign(psz);
//
//   return *this;
//
//}
//
//
//
//void wstring::assign(const char* psz)
//{
//
//   if (::is_null(psz) || *psz == '\0')
//   {
//
//      natural_release();
//
//      return;
//
//   }
//
//   auto strsize = utf16_len(psz);
//
//   auto pNew = create_meta_data(strsize + 1);
//
//   ansi_to_wd16(pNew->m_pdata, psz);
//
//   pNew->set_length(strsize);
//
//   POINTER::operator = (pNew);
//
//}
//
//
//wstring operator + (const wstring& wstr1, const wstring& wstr2)
//{
//
//   ::count iLen1 = wstr1.length();
//
//   ::count iLen2 = wstr2.length();
//
//   wstring wstrRet;
//
//   wstrRet.get_buffer(iLen1 + iLen2 + 1);
//
//   wide_copy(wstrRet, wstr1);
//
//   wide_concatenate(wstrRet, wstr2);
//
//   wstrRet.set_length(iLen1 + iLen2);
//
//   return wstrRet;
//
//}
//
//
//wstring operator + (const wstring& wstr, const unichar* wpsz)
//{
//   return wstr + wstring(wpsz);
//}
//
//wstring operator + (const unichar* wpsz, const wstring& wstr)
//{
//   return wstring(wpsz) + wstr;
//}
//
//
//wstring gen_utf8_to_16(const char* psz)
//{
//
//   wstring wstr;
//
//   ::count iLen = utf16_len(psz);
//
//   if (iLen < 0)
//      return wstr;
//
//   wstr.get_buffer(iLen);
//
//   ansi_to_wd16(wstr, psz);
//
//   wstr.set_length(iLen);
//
//   return wstr;
//
//}
//
//
//
//wstring wstring::substr(::index iStart, ::count count)
//{
//   if (m_psz == nullptr)
//   {
//      unichar push[] = { 0 };
//      return push;
//
//   }
//   else
//   {
//
//      if (count < 0)
//      {
//         count = get_length()- iStart + count + 1;
//      }
//
//      if (iStart + count > get_length())
//      {
//         count = get_length() - iStart;
//      }
//
//      if (count <= 0)
//      {
//         unichar push[] = { 0 };
//         return push;
//      }
//
//      return wstring(&m_psz[iStart], count);
//
//   }
//
//}
//
//
//
//
//wstring& wstring::replace(::index iStart, ::count c, const unichar* psz)
//{
//   if (c < 0)
//   {
//      return operator = (substr(0, iStart) + psz);
//   }
//   else
//   {
//      return operator = (substr(0, iStart) + psz + substr(iStart + c));
//   }
//
//
//}
//
//
//
//// find the first occurrence of character 'ch', starting at strsize 'iStart'
//strsize wstring::find(unichar ch, strsize iStart, strsize nCount) const RELEASENOTHROW
//{
//   // iStart is in XCHARs
//   ASSERT(iStart >= 0);
//
//   // nLength is in XCHARs
//   strsize nLength = get_length();
//   if (iStart < 0 || iStart >= nLength)
//   {
//      return -1;
//   }
//
//   if (nCount < 0)
//      nCount = nLength;
//
//   if (nCount + iStart > nLength)
//      nCount = nLength - iStart;
//
//   if (nCount < 0)
//      return -1;
//
//   const unichar* psz = m_psz + iStart;
//   for (i32 i = 0; i < nCount; i++)
//   {
//      if (psz[i] == ch)
//      {
//         return iStart + i;
//      }
//   }
//   return -1;
//}
//// find the first occurrence of string 'pszSub', starting at strsize 'iStart'
//strsize wstring::find(const unichar* pszSub, strsize iStart, strsize nCount, const unichar** pszTail) const RELEASENOTHROW
//{
//   // iStart is in XCHARs
//   ASSERT(iStart >= 0);
//   ASSERT(__is_valid_string(pszSub));
//
//   if (pszSub == nullptr)
//   {
//      return(-1);
//   }
//   // nLength is in XCHARs
//   strsize nLength = get_length();
//   if (iStart < 0 || iStart > nLength)
//   {
//      return(-1);
//   }
//
//   strsize nLength2 = unilen(pszSub);
//
//   if (nCount < 0)
//      nCount = nLength;
//
//   if (nCount + iStart + nLength2 > nLength)
//      nCount = nLength - iStart - nLength2;
//
//   if (nCount < 0)
//      return -1;
//
//   const unichar* psz = m_psz + iStart;
//   for (i32 i = 0; i <= nCount; i++)
//   {
//      bool bFound = true;
//      i32 j;
//      for (j = 0; j < nLength2; j++)
//      {
//         if (psz[j] != pszSub[j])
//         {
//            bFound = false;
//            break;
//         }
//      }
//      if (bFound && j == nLength2)
//      {
//         if (pszTail)
//            *pszTail = &psz[j];
//         return i + iStart;
//      }
//      psz++;
//   }
//   return -1;
//}
