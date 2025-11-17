#include "framework.h"
//#include "string.h"
//
//
// template < >
// CLASS_DECL_ACME base_data < string_heap_data < ::wd16_character > > * __nil < base_data < string_heap_data < ::wd16_character > > >()
// {
//
//    static base_data < string_heap_data < ::wd16_character > > s_wd16stringNil;
//
//    return &s_wd16stringNil;
//
// }
//
//
// template < >
// CLASS_DECL_ACME base_data < string_heap_data < ::wd32_character > > * __nil < base_data < string_heap_data < ::wd32_character > > >()
// {
//
//    static base_data < string_heap_data < ::wd32_character > > s_wd32stringNil;
//
//    return &s_wd32stringNil;
//
// }

//const unichar * wstring::g_pszWindowsBBQBUNC(L"\\\\?\\UNC");
//const unichar * wstring::g_pszWindowsBBQB(L"\\\\?\\");
//const unichar * wstring::g_pszWindowsBB(L"\\\\");
//
//
//wstring::wstring(const ::scoped_string & scopedstr)
//{
//
//   operator = (scopedstr);
//
//}
//
//
//wstring::wstring(const unsigned char* psz)
//{
//
//   operator = ((const_char_pointer )psz);
//
//}
//
//wstring::wstring(const unsigned char* psz, character_count iSize)
//{
//
//   operator = ((const_char_pointer )string(scopedstr, iSize));
//
//}
//
//
//wstring::wstring(const unichar* pwsz, character_count character_count)
//{
//
//   if (::is_null(pwsz))
//   {
//
//      if (character_count != 0)
//      {
//
//         throw ::exception(error_bad_argument);
//
//      }
//
//      natural_release();
//
//   }
//   else
//   {
//
//      auto pNew = create_meta_data(char_length_to_byte_length(character_count + 1));
//
//      if (pNew == nullptr)
//      {
//
//         throw no_memory();
//
//      }
//
//      POINTER::operator=(pNew);
//
//      ::memory_copy(pNew->m_pdata, pwsz, pNew->memsize());
//
//      set_length(character_count);
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
////unichar* wstring::alloc(::collection::count iCount)
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
//wstring& wstring::operator = (const ::scoped_string & scopedstr)
//{
//   assign(scopedstr);
//
//   return *this;
//
//}
//
//
//
//void wstring::assign(const ::scoped_string & scopedstr)
//{
//
//   if (::is_null(scopedstr) || *psz == '\0')
//   {
//
//      natural_release();
//
//      return;
//
//   }
//
//   auto character_count = utf16_len(scopedstr);
//
//   auto pNew = create_meta_data(character_count + 1);
//
//   ansi_to_wd16(pNew->m_pdata, psz);
//
//   pNew->set_length(character_count);
//
//   POINTER::operator = (pNew);
//
//}
//
//
//wstring operator + (const wstring& wstr1, const wstring& wstr2)
//{
//
//   ::collection::count iLen1 = wstr1.length();
//
//   ::collection::count iLen2 = wstr2.length();
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
//wstring gen_utf8_to_16(const ::scoped_string & scopedstr)
//{
//
//   wstring wstr;
//
//   ::collection::count iLen = utf16_len(scopedstr);
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
//wstring wstring::substr(::collection::index iStart, ::collection::count count)
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
//wstring& wstring::replace(::collection::index iStart, ::collection::count c, const unichar* psz)
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
//// find the first occurrence of character 'ch', starting at character_count 'iStart'
//character_count wstring::find(unichar ch, character_count iStart, character_count nCount) const RELEASENOTHROW
//{
//   // iStart is in XCHARs
//   ASSERT(iStart >= 0);
//
//   // nLength is in XCHARs
//   character_count nLength = get_length();
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
//   for (int i = 0; i < nCount; i++)
//   {
//      if (scopedstr[i] == ch)
//      {
//         return iStart + i;
//      }
//   }
//   return -1;
//}
//// find the first occurrence of string 'pszSub', starting at character_count 'iStart'
//character_count wstring::find(const unichar* pszSub, character_count iStart, character_count nCount, const unichar** pszTail) const RELEASENOTHROW
//{
//   // iStart is in XCHARs
//   ASSERT(iStart >= 0);
//   ASSERT(is_string_ok(scopedstrSub));
//
//   if (scopedstrSub == nullptr)
//   {
//      return(-1);
//   }
//   // nLength is in XCHARs
//   character_count nLength = get_length();
//   if (iStart < 0 || iStart > nLength)
//   {
//      return(-1);
//   }
//
//   character_count nLength2 = unilen(scopedstrSub);
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
//   for (int i = 0; i <= nCount; i++)
//   {
//      bool bFound = true;
//      int j;
//      for (j = 0; j < nLength2; j++)
//      {
//         if (scopedstr[j] != pszSub[j])
//         {
//            bFound = false;
//            break;
//         }
//      }
//      if (bFound && j == nLength2)
//      {
//         if (scopedstrTail)
//            *pszTail = &psz[j];
//         return i + iStart;
//      }
//      psz++;
//   }
//   return -1;
//}
