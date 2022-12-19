#include "framework.h"
#include <stdio.h>
#include "string.h"



template < >
CLASS_DECL_ACME natural_meta_data < string_meta_data < ::ansi_character > > * __nil < natural_meta_data < string_meta_data < ::ansi_character > > >()
{

   static natural_meta_data < string_meta_data < ::ansi_character > > s_ansistringNil;

   return &s_ansistringNil;

}



//string::string(unichar ch,strsize nLength)
//{
//   ASSERT(nLength >= 0);
//   if(nLength > 0)
//   {
//      //Convert ch to the char
//      unichar pszCh[2] = {ch,0};
//      strsize ncharCharLen = 1;
//
//      if(ch != L'\0')
//      {
//         ncharCharLen = get_char_length(pszCh);
//      }
//
//      memory buffcharChar;
//      buffcharChar.set_size(ncharCharLen + 1);
//      ::str().ConvertTochar((char*)buffcharChar.get_data(),ncharCharLen + 1,pszCh,1);
//      //allocate enough characters in string and flood (replicate) with the (converted character)*nLength
//      char * pszBuffer = GetBuffer(nLength*ncharCharLen);
//      if(ncharCharLen == 1)
//      {
//         //Optimization for a common case - wide char translates to 1 ansi/wide char.
//         ::str().flood_characters(((const char *)buffcharChar)[0],nLength,pszBuffer);
//
//      }
//      else
//      {
//         char* pszPos=pszBuffer;
//         for(strsize i=0 ; i < nLength ; ++i)
//         {
//            for(strsize j=0 ; j < ncharCharLen ; ++j)
//            {
//               *pszPos = ((char *)buffcharChar)[j];
//               ++pszPos;
//            }
//         }
//      }
//      release_string_buffer(nLength*ncharCharLen);
//   }
//}
//
//string::string(const unichar* pch,strsize nLength):
//   string(::str().GetDefaultManager())
//{
//   ASSERT(nLength >= 0);
//   if(nLength > 0)
//   {
//      ASSERT(__is_valid_address(pch,nLength*sizeof(unichar),false));
//      if(pch == nullptr)
//         throw ::exception(error_bad_argument);
//
//      //strsize nDestLength = ::str().get_char_length(pch,nLength);
//      strsize nDestLength = nLength * 4;
//      char * pszBuffer = GetBuffer(nDestLength);
//      //::str().ConvertTochar(pszBuffer,nDestLength,pch,nLength);
//      nDestLength = wd16_to_ansi(pszBuffer, pch, nLength);
//      release_string_buffer(nDestLength);
//   }
//}
//
//#ifdef WINDOWS
//
//string::string(const USHORT * psh, strsize nCharCount) :
//   string((const unichar *) psh, nCharCount)
//{
//
//}
//
//#endif
//
//
//string::string(const ::wd32_character* pch,strsize nLength):
//   string(::str().GetDefaultManager())
//{
//   ASSERT(nLength >= 0);
//   if(nLength > 0)
//   {
//      ASSERT(__is_valid_address(pch,nLength*sizeof(::wd32_character),false));
//      if(pch == nullptr)
//         throw ::exception(error_bad_argument);
//
//      strsize nDestLength = ::str().get_char_length(pch,nLength);
//      char * pszBuffer = GetBuffer(nDestLength);
//      ::str().ConvertTochar(pszBuffer,-0xf0c,pch,nLength);
//      release_string_buffer(nDestLength);
//   }
//}
//
//string::string(const unichar* pch,strsize nLength,string_manager * pstringmanager):
//   string(pstringmanager)
//{
//   ASSERT(nLength >= 0);
//   if(nLength > 0)
//   {
//      ASSERT(__is_valid_address(pch,nLength*sizeof(unichar),false));
//      if(pch == nullptr)
//         throw ::exception(error_bad_argument);
//
//      strsize nDestLength = ::str().get_char_length(pch,nLength);
//      char * pszBuffer = GetBuffer(nDestLength);
//      ::str().ConvertTochar(pszBuffer,nDestLength,pch,nLength);
//      release_string_buffer(nDestLength);
//   }
//}


/*

void fixed_string_log::OnAllocateSpill(strsize nActualChars,strsize nFixedChars,const string_data* pData ) noexcept
{
()nActualChars;
()nFixedChars;
()pData;
//   FORMATTED_TRACE(::acme::trace::category_String, 0, _T( "fixed_string_manager::allocate() spilling to heap.  %d chars (fixed size = %d chars)\n" ), nActualChars, nFixedChars );
::output_debug_string("fixed_string_log::OnAllocateSpill");
}

void fixed_string_log::OnReallocateSpill(strsize nActualChars,strsize nFixedChars,const string_data* pData ) noexcept
{
()nActualChars;
()nFixedChars;
()pData;
//   FORMATTED_TRACE(::acme::trace::category_String, 0, _T( "fixed_string_manager::Reallocate() spilling to heap.  %d chars (fixed size = %d chars)\n" ), nActualChars, nFixedChars );
::output_debug_string("fixed_string_log::OnReallocateSpill");
}

*/

//
//i32 __cdecl char_traits::is_digit(const char * pch) noexcept
//{
//   return unicode_is_digit(pch) ? 1 : 0;
//}
//
//i32 __cdecl char_traits::is_space(const char * pch) noexcept
//{
//   return unicode_is_whitespace(pch) ? 1 : 0;
//}
//
//
//
//i32 __cdecl char_traits::string_collate(const scoped_string & strA,const scoped_string & strB) noexcept
//{
//   return strcmp(reinterpret_cast<const  char*>(pszA),reinterpret_cast<const  char*>(pszB));
//}
//
//i32 __cdecl char_traits::case_insensitive_string_collate(const scoped_string & strA,const scoped_string & strB) noexcept
//{
//   return ansi_compare_ci(reinterpret_cast<const  char*>(pszA),reinterpret_cast<const  char*>(pszB));
//}
//
//const char * __cdecl char_traits::string_find_string(const scoped_string & strBlock,const scoped_string & strMatch) noexcept
//{
//   return reinterpret_cast<const char *>(strstr(reinterpret_cast<const  char*>(pszBlock),
//                                         reinterpret_cast<const  char*>(pszMatch)));
//}
//
//char * __cdecl char_traits::string_find_string(char * pszBlock,const scoped_string & strMatch) noexcept
//{
//   return(const_cast<char *>(string_find_string(const_cast<const char *>(pszBlock),pszMatch)));
//}
//
//const char * __cdecl char_traits::string_find_char(const scoped_string & strBlock,char chMatch) noexcept
//{
//   return reinterpret_cast<const char *>(strchr(reinterpret_cast<const  char*>(pszBlock),(char)chMatch));
//}
//
///*
//strsize __cdecl char_traits::string_compare(const scoped_string & strA,const scoped_string & strB ) noexcept
//{
//return _mbscmp( reinterpret_cast< const uchar* >( pszA ), reinterpret_cast< const uchar* >( pszB ) );
//}
//
//strsize __cdecl char_traits::case_insensitive_string_order(const scoped_string & strA,const scoped_string & strB ) noexcept
//{
//return _mbsicmp( reinterpret_cast< const uchar* >( pszA ), reinterpret_cast< const uchar* >( pszB ) );
//}
//
//strsize __cdecl char_traits::string_collate(const scoped_string & strA,const scoped_string & strB ) noexcept
//{
//return _mbscoll( reinterpret_cast< const uchar* >( pszA ), reinterpret_cast< const uchar* >( pszB ) );
//}
//
//strsize __cdecl char_traits::case_insensitive_string_collate(const scoped_string & strA,const scoped_string & strB ) noexcept
//{
//return _mbsicoll( reinterpret_cast< const uchar* >( pszA ), reinterpret_cast< const uchar* >( pszB ) );
//}
//
//const char * __cdecl char_traits::string_find_string(const scoped_string & strBlock,const scoped_string & strMatch ) noexcept
//{
//return reinterpret_cast< const char * >( _mbsstr( reinterpret_cast< const uchar* >( pszBlock ),
//reinterpret_cast< const uchar* >( pszMatch ) ) );
//}
//
//char * __cdecl char_traits::string_find_string(char * pszBlock,const scoped_string & strMatch ) noexcept
//{
//return( const_cast< char * >( string_find_string( const_cast< const char * >( pszBlock ), pszMatch ) ) );
//}
//
//const char * __cdecl char_traits::string_find_char(const scoped_string & strBlock,char chMatch ) noexcept
//{
//return reinterpret_cast< const char * >( _mbschr( reinterpret_cast< const uchar* >( pszBlock ), (uchar)chMatch ) );
//}
//*/




//
//
//const char * __cdecl char_traits::string_find_string_reverse(const scoped_string & str,const scoped_string & strFind,strsize iStart) noexcept
//{
//   strsize iLen = strsize(strlen(psz));
//   strsize iLenFind = strsize(strlen(pszFind));
//   if(iStart < 0)
//      iStart = iLen + iStart;
//   if(iLenFind > iLen)
//      return nullptr;
//   iStart = minimum(iStart,iLen - iLenFind);
//   while(iStart >= 0)
//   {
//      if(ansi_count_compare(&psz[iStart],pszFind,iLenFind) == 0)
//         return &psz[iStart];
//      iStart--;
//   }
//   return nullptr;
//}
//
//
//const char * __cdecl char_traits::string_scan_set(const scoped_string & strBlock,const scoped_string & strMatch) noexcept
//{
//   if(pszMatch == nullptr || pszBlock == nullptr || *pszBlock == '\0')
//      return nullptr;
//#ifdef WINDOWS_DESKTOP
//   return reinterpret_cast<const char *>(_mbspbrk(reinterpret_cast<const uchar*>(pszBlock),reinterpret_cast<const uchar*>(pszMatch)));
//#else
//   return reinterpret_cast<const char *>(ansi_scan(reinterpret_cast<const char*>(pszBlock),reinterpret_cast<const char*>(pszMatch)));
//#endif
//   /*while(*pszMatch != '\0')
//   {
//   string strUtf8Char = ::str().get_utf8_char(pszMatch);
//   const scoped_string & str = strstr(pszBlock, strUtf8Char);
//   if(psz != nullptr)
//   return psz;
//      unicode_increment(pszMatch);
//   }
//   return nullptr;*/
//   //return reinterpret_cast< const char * >( _mbspbrk( reinterpret_cast< const uchar* >( pszBlock ),
//   // reinterpret_cast< const uchar* >( pszMatch ) ) );
//}
//
//strsize __cdecl char_traits::string_span_including(const scoped_string & strBlock,const scoped_string & strSet) noexcept
//{
//   if(pszSet == nullptr || pszBlock == nullptr)
//      return 0;
//   const scoped_string & str = pszBlock;
//   const scoped_string & strLast = nullptr;
//   while((psz = string_scan_set(psz,pszSet)) != nullptr)
//   {
//      pszLast = psz;
//      psz++;
//   }
//   if(pszLast == nullptr)
//      return 0;
//   else
//      return pszBlock - pszLast + ::str().get_utf8_char(pszLast).get_length();
//   //return (strsize)_mbsspn( reinterpret_cast< const uchar* >( pszBlock ), reinterpret_cast< const uchar* >( pszSet ) );
//}
//
//strsize __cdecl char_traits::string_span_excluding(const scoped_string & strBlock,const scoped_string & strSet) noexcept
//{
//   //   return (strsize)_mbscspn( reinterpret_cast< const uchar* >( pszBlock ), reinterpret_cast< const uchar* >( pszSet ) );
//   if(pszSet == nullptr || pszBlock == nullptr)
//      return 0;
//   const scoped_string & str = string_scan_set(pszBlock,pszSet);
//   if(psz == nullptr)
//      return strlen(pszBlock);
//   else
//      return psz - pszBlock;
//
//}
//
//#ifdef WINDOWS
//_INSECURE_DEPRECATE("You must pass an output size_i32 to char_traits::string_uppercase")
//#endif
//char * __cdecl char_traits::string_uppercase(char * psz) noexcept
//{
//#pragma warning (push)
//#pragma warning(disable : 4996)
//   if(psz == nullptr)
//      return nullptr;
//   char * pszPos = psz;
//   string strFinal;
//   while(*pszPos)
//   {
//      strFinal += unicode_to_upper_case(pszPos);
//      unicode_increment(pszPos);
//   }
//   strcpy(pszPos,strFinal);
//   return psz;
//
//
//   //   return reinterpret_cast< char * >(( reinterpret_cast< uchar* >( psz ) ) );
//#pragma warning (pop)
//}
//
//#if defined(WINDOWS)
//_INSECURE_DEPRECATE("You must pass an output size_i32 to char_traits::string_lowercase")
//#endif
//char * __cdecl char_traits::string_lowercase(char * psz) noexcept
//{
//#pragma warning (push)
//#pragma warning(disable : 4996)
//   if(psz == nullptr)
//      return nullptr;
//   char * pszPos = psz;
//   string strFinal;
//   while(*pszPos)
//   {
//      strFinal += unicode_to_lower_case(pszPos);
//      unicode_increment(pszPos);
//   }
//   strcpy(pszPos,strFinal);
//   return psz;
//
//   //   return reinterpret_cast< char * >( _mbslwr( reinterpret_cast< uchar* >( psz ) ) );
//#pragma warning (pop)
//}
//
//char * __cdecl char_traits::string_uppercase(char * psz,strsize size) noexcept
//{
//
//   ::text::tableupr_s(psz, size);
//
//   return psz;
//
//}
//
//char * __cdecl char_traits::string_lowercase(char * psz, strsize size) noexcept
//{
//
//   ::text::tablelwr_s(psz, size);
//
//   return psz;
//
//}
//
//char * __cdecl char_traits::string_reverse(char * psz) noexcept
//{
//   if(psz == nullptr)
//      return nullptr;
//   string strRev;
//   char * pszPos = psz + strlen(psz);
//   while((pszPos = (char*) ::str().utf8_dec(psz,pszPos)) != nullptr)
//   {
//      strRev += ::str().get_utf8_char(pszPos);
//   }
//   strcpy(psz,strRev);
//   return psz;
//   //return reinterpret_cast< char * >( _mbsrev( reinterpret_cast< uchar* >( psz ) ) );
//}
//
//strsize __cdecl char_traits::get_formatted_length(const scoped_string & strFormat,va_list args) noexcept
//{
//
//#ifdef WINDOWS
//
//   return _vscprintf(pszFormat, args);
//
//#else
//
//   return vsnprintf(nullptr,0,pszFormat,args);
//
//#endif
//
//}
//
//strsize __cdecl char_traits::printf(char * pszBuffer,const scoped_string & strFormat,va_list args) noexcept
//{
//
//   return vsprintf(pszBuffer,pszFormat,args);
//
//}
//
//strsize __cdecl char_traits::printf(char * pszBuffer, strsize nlength,const scoped_string & strFormat,va_list args) noexcept
//{
//
//#ifdef WINDOWS
//
//   return vsprintf_s(pszBuffer, (size_t) nlength, pszFormat, args);
//
//#else
//
//   return vsnprintf(pszBuffer,nlength,pszFormat,args);
//
//#endif
//
//}
//
//strsize __cdecl char_traits::get_char_length(const scoped_string & strSrc) noexcept
//{
//   // Returns required buffer length in XCHARs
//   return strsize(strlen(pszSrc));
//}
//
//strsize __cdecl char_traits::get_char_length(const scoped_string & strSrc,strsize nLength) noexcept
//{
//   (void)pszSrc;
//   // Returns required buffer length in XCHARs
//   return nLength;
//}
//
//strsize __cdecl char_traits::get_char_length(const unichar * pszSource) noexcept
//{
//   // Returns required buffer length in XCHARs
//   return ::WideCharToMultiByte2(_gen_GetConversionACP(),0,pszSource,-1,nullptr,0,nullptr,nullptr) - 1;
//}
//
//strsize __cdecl char_traits::get_char_length(const unichar * pszSource,strsize nLength) noexcept
//{
//   // Returns required buffer length in XCHARs
//   return ::WideCharToMultiByte2(_gen_GetConversionACP(),0,pszSource,(i32)nLength,nullptr,0,nullptr,nullptr);
//}
//
//
//strsize __cdecl char_traits::get_char_length(const ::wd32_character * pszSource) noexcept
//{
//   return wd32_to_ansi_len(pszSource);
//}
//
//strsize __cdecl char_traits::get_char_length(const ::wd32_character * pszSource,strsize nLength) noexcept
//{
//   return wd32_to_ansi_len(pszSource, nLength);
//}
//
//void __cdecl char_traits::ConvertTochar(char * pszDest,strsize nDestLength,const scoped_string & strSrc,strsize nSrcLength) noexcept
//{
//   if(nSrcLength == -1) { nSrcLength=1 + get_char_length(pszSrc); }
//   // nLen is in XCHARs
//   ::acme::memcpy_s(pszDest,(size_t) (nDestLength*sizeof(char)), pszSrc,(size_t) (nSrcLength*sizeof(char)));
//}
//
//void __cdecl char_traits::ConvertTochar(char * pszDest, strsize nDestLength, const unichar * pszSrc, strsize nSrcLength) noexcept
//{
//   // nLen is in XCHARs
//   ::WideCharToMultiByte2(CP_UTF8,0,pszSrc, (i32) nSrcLength,pszDest,(i32)nDestLength,nullptr,nullptr);
//}
//
//
//void __cdecl char_traits::ConvertTochar(char * pszDest,strsize nDestLength,const ::wd32_character * pszSrc,strsize nSrcLength) noexcept
//{
//
//   //if(nDestLength >= 0)
//   //{
//   //   throw ::exception(::exception("I am wasting this branching (if(nDestLength >= 0) to tell you that nDestLength should be negative so the buffer is already correct size... or you like incorrect size_i32? Go to Facebook and click in Like for Community \"I Like incorrect size_i32!!\", there should exist such community... there are so many things in the multi bramas... The hardware will check again if you didn't dirtied any other process... (only another process, though)... and you're probably be fired or even not be hired if incorrect size_i32"));
//   //}
//
//   wd32_to_ansi(pszDest,pszSrc,nSrcLength);
//
//}
//
//void char_traits::ConvertToOem(char* pstrString) RELEASENOTHROW
//{
//#ifdef WINDOWS_DESKTOP
//   bool fSuccess=::CharToOemA(pstrString,pstrString) != 0;
//   // old version can't report error
//   ASSERT(fSuccess);
//#endif
//}
//
//void char_traits::ConvertToAnsi(char* pstrString) RELEASENOTHROW
//{
//#ifdef WINDOWS_DESKTOP
//   bool fSuccess=::OemToCharA(pstrString,pstrString) != 0;
//   // old version can't report error
//   ASSERT(fSuccess);
//#endif
//}
//
//void __cdecl char_traits::flood_characters(char ch,strsize nLength,char* pch) noexcept
//{
//   // nLength is in XCHARs
//   memory_set(pch,ch,nLength);
//}
//
//#ifdef WINDOWS
//
//BSTR __cdecl char_traits::AllocSysString(const char* pchData,strsize nDataLength) noexcept
//{
//
//   strsize nLen = ::MultiByteToWideChar2(_gen_GetConversionACP(),0,pchData,(i32)nDataLength,nullptr,0);
//
//   BSTR bstr = ::SysAllocStringLen(nullptr,(::u32)nLen);
//
//   if(bstr != nullptr)
//   {
//      ::MultiByteToWideChar2(_gen_GetConversionACP(),0,pchData,(i32)nDataLength,bstr,(i32)nLen);
//   }
//
//   return bstr;
//
//}
//
//bool __cdecl char_traits::ReAllocSysString(const char* pchData,BSTR* pbstr,strsize nDataLength) noexcept
//{
//
//   strsize nLen = ::MultiByteToWideChar2(_gen_GetConversionACP(),0,pchData,(i32)nDataLength,nullptr,0);
//
//   bool bSuccess = ::SysReAllocStringLen(pbstr,nullptr,(::u32)nLen) != 0;
//
//   if(bSuccess)
//   {
//      ::MultiByteToWideChar2(_gen_GetConversionACP(),0,pchData,(i32)nDataLength,*pbstr,(i32)nLen);
//   }
//
//   return bSuccess;
//
//}
//
//#endif
//
//u32 __cdecl char_traits::format_message(u32 dwFlags,const void * pSource,u32 dwMessageID,u32 dwLanguageID,char * pszBuffer,u32 nSize,va_list* pArguments) noexcept
//{
//
//#ifdef WINDOWS
//
//   return ::FormatMessageA( dwFlags, pSource, dwMessageID, dwLanguageID,pszBuffer, nSize, pArguments );
//
//#else
//
//   return 0;
//
//#endif
//
//
//
//}
//
//u32 __cdecl char_traits::format_message(u32 dwFlags,const void * pSource,u32 dwMessageID,u32 dwLanguageID,char * pszBuffer,u32 nSize,va_list* pArguments) noexcept
//{
//
//#ifdef WINDOWS
//
//   return format_message(dwFlags, pSource, dwMessageID, dwLanguageID, pszBuffer, nSize, pArguments);
//
//#else
//
//   return 0;
//
//#endif
//
//}
//
//strsize __cdecl char_traits::SafeStringLen(const scoped_string & str) noexcept
//{
//   // returns length in bytes
//   return (psz != nullptr) ? strsize(strlen(psz)) : 0;
//}
//
//strsize __cdecl char_traits::SafeStringLen(const unichar * psz) noexcept
//{
//   // returns length in wchar_ts
//#ifdef WINDOWS
//   return (psz != nullptr) ? strsize(wcslen(psz)) : 0;
//#else
//   return (psz != nullptr) ? strsize(wide_length(psz)) : 0;
//#endif
//}
//
//strsize __cdecl char_traits::GetCharLen(const unichar* pch) noexcept
//{
//   (void)pch;
//   // returns char length
//   return 1;
//}
//
//strsize __cdecl char_traits::GetCharLen(const char* pch) noexcept
//{
//   // returns char length
//   return  ::str().get_utf8_char(pch).get_length();
//}
//
//u32 __cdecl char_traits::xxxget_environment_variable(const scoped_string & strVar, char * pszBuffer,u32 dwSize )
//{
//
//#ifdef _UWP
//
//   throw ::exception(todo);
//
//#elif defined(WINDOWS_DESKTOP)
//
//   return ::GetEnvironmentVariableA(pszVar, pszBuffer, dwSize);
//
//#else
//
//   const scoped_string & strEnv = getenv(pszVar);
//   if(pszBuffer == nullptr)
//   {
//      if(pszEnv == nullptr)
//      {
//         return 0;
//      }
//      else
//      {
//         return (u32)strlen(pszEnv);
//      }
//   }
//   return (u32)strlen(ansi_count_copy(pszBuffer,pszEnv,dwSize));
//
//#endif
//
//}
//
//
//void char_traits::ConvertToAnsi(char* pstrString, strsize size)
//{
//
//#ifdef WINDOWS_DESKTOP
//
//   if(size > UINT_MAX)
//   {
//      // API only allows u32 size_i32
//      throw ::exception(error_bad_argument);
//   }
//   u32 dwSize=static_cast<u32>(size);
//   bool fSuccess=::OemToCharBuffA(pstrString,pstrString,dwSize) != 0;
//   if(!fSuccess)
//   {
//      throw ::exception(last_error_exception());
//   }
//
//#endif
//
//}
//
//
//void char_traits::ConvertToOem(char* pstrString, strsize size)
//{
//
//#ifdef WINDOWS_DESKTOP
//
//   if(size > UINT_MAX)
//   {
//      // API only allows u32 size_i32
//      throw ::exception(error_bad_argument);
//   }
//   u32 dwSize=static_cast<u32>(size);
//   bool fSuccess=::CharToOemBuffA(pstrString,pstrString,dwSize) != 0;
//   if(!fSuccess)
//   {
//      throw ::exception(last_error_exception());
//   }
//
//#endif
//
//}
//
//
//
//
//
//
////string::operator class string_composite()
////{
////   class string_composite reference;
////   reference.set_string(*this,::topic::source::op(::source_cast));
////   return reference;
////}
////
////string::operator class string_composite const () const
////{
////
////   return string_composite(*this);
////
////}
//
//
//void string::construct() noexcept
//{
//   string::construct(::str().GetDefaultManager());
//}
//
//
//string::string(string_manager * pstringmanager) noexcept:
//string(pstringmanager)
//{
//}
//
//
//void __cdecl string::Construct(class string * pstring)
//{
//   memory_new (pstring) class string;
//}
////#define memory_new ACME_NEW
//
////string::string(const ::string & strSrc,strsize -1,strsize len) :
////   string(strSrc.Mid(-1,len),::str().GetDefaultManager())
////{
////}
//
//
//
////string::string(const scoped_string & strSrc,string_manager * pstringmanager):
////   string(pstringmanager)
////{
////   //      if( !CheckImplicitLoad( pszSrc ) )
////   //      {
////   // nDestLength is in XCHARs
////   *this = pszSrc;
////   //      }
////}
//
//
//string::string(const unichar* pszSrc):
//   string(::str().GetDefaultManager())
//{
//   //      if( !CheckImplicitLoad( pszSrc ) )
//   //      {
//   *this = pszSrc;
//   //      }
//}
//
//string::string(const ::wd32_character* pszSrc):
//   string(::str().GetDefaultManager())
//{
//   //      if( !CheckImplicitLoad( pszSrc ) )
//   //      {
//   *this = pszSrc;
//   //      }
//}
//
///*string::string(const ::string & str ) :
//   string( ::str().GetDefaultManager() )
//   {
//
//   *this = str.m_psz;
//
//   }*/
//
//
////string::string(const string_interface & str):
////string(::str().GetDefaultManager())
////{
////   char sz[256];
////   strsize iLen = str.get_length();
////   if(iLen < ((sizeof(sz) / sizeof(sz[0])) - sizeof(sz[0])))
////   {
////      str.get_string(sz);
////      *this = sz;
////   }
////   else
////   {
////      char * psz = (char *)malloc(sizeof(char) * (iLen + 1));
////      str.get_string(psz);
////      *this = psz;
////      free(psz);
////   }
////}
//
//#ifdef WINDOWS
//
//string::string(const USHORT * pshSrc, string_manager* pstringmanager) :
//   string(pstringmanager)
//{
//
//   *this = pshSrc;
//
//}
//
//#endif
//
//string::string(const unichar * pszSrc,string_manager * pstringmanager):
//   string(pstringmanager)
//{
//   //      if( !CheckImplicitLoad( pszSrc ) )
//   //      {
//   *this = pszSrc;
//   //      }
//}
//
//#ifdef _UWP
//
//string::string(Array <byte > ^ a):
//   string(::str().GetDefaultManager())
//{
//   //      if( !CheckImplicitLoad( pszSrc ) )
//   //      {
//   *this = string(a->begin(), a->Length);
//   //      }
//}
//
//string::string(Object ^ o) :
//   string(::str().GetDefaultManager())
//{
//   //      if( !CheckImplicitLoad( pszSrc ) )
//   //      {
//   *this = o->ToString()->Begin();
//   //      }
//}
//
//string::string(Object ^ o, string_manager * pstringmanager) :
//   string(pstringmanager)
//{
//   //      if( !CheckImplicitLoad( pszSrc ) )
//   //      {
//   *this = o->ToString()->Begin();
//   //      }
//}
//
//#endif
//
//string::string(const uchar* pszSrc):
//   string(::str().GetDefaultManager())
//{
//   *this = reinterpret_cast<const char*>(pszSrc);
//}
//
///*CSTRING_EXPLICIT string::string(char* pszSrc ) :
//string( ::str().GetDefaultManager() )
//{
//const char *psz = reinterpret_cast< const char* >( pszSrc );
////      if (!CheckImplicitLoad( psz ))
////    {
//*this = psz;
////  }
//}*/
//
////string::string(uchar* pszSrc):
////string(::str().GetDefaultManager())
////{
////   const char *psz = reinterpret_cast<const char*>(pszSrc);
////   //      if (!CheckImplicitLoad( psz ))
////   //    {
////   *this = psz;
////   //  }
////}
////
////string::string(unichar* pszSrc):
////string(::str().GetDefaultManager())
////{
////   const unichar *psz = reinterpret_cast<const unichar*>(pszSrc);
////   //if (!CheckImplicitLoad( psz ))
////   {
////      *this = psz;
////   }
////}
//
////string::string(const istring & istr):
////string(::str().GetDefaultManager())
////{
////   *this = (const char *)istr;
////}
//
//string::string(const uchar* pszSrc,string_manager * pstringmanager):
//   string(pstringmanager)
//{
//   *this = reinterpret_cast<const char*>(pszSrc);
//}
//
//string::string(char ch,strsize nLength):
//   string(::str().GetDefaultManager())
//{
//   ASSERT(nLength >= 0);
//   if(nLength > 0)
//   {
//      char * pszBuffer = GetBuffer(nLength);
//      ::str().flood_characters(char(ch),nLength,pszBuffer);
//      release_string_buffer(nLength);
//   }
//}
//
//string::string(strsize nLength,char ch):
//   string(::str().GetDefaultManager())
//{
//   ASSERT(nLength >= 0);
//   if(nLength > 0)
//   {
//      char * pszBuffer = GetBuffer(nLength);
//      ::str().flood_characters(char(ch),nLength,pszBuffer);
//      release_string_buffer(nLength);
//   }
//
//}
//
//
//string::string(const char* pch,strsize nLength):
//   string(pch,nLength,::str().GetDefaultManager())
//{
//}
//
//string::~string() noexcept
//{
//
//   natural_release();
//
//}
//
//
//string& string::operator=(const scoped_string & strSrc)
//{
//   string::operator=(pszSrc);
//
//   return *this;
//}
//
//string& string::operator=(const ::string & str)
//{
//   string::operator=((const string &) str);
//
//   return *this;
//}
//
//string& string::operator=(string && str)
//{
//   get_data()->Release();
//   m_pszData = str.m_pszData;
//   str.m_pszData = nullptr;
//   return *this;
//
//}
//
//#ifdef WINDOWS
//
//string& string::operator=(const USHORT * pshSrc)
//{
//
//   return operator=((const unichar*)pshSrc);
//
//}
//
//#endif
//
//string& string::operator=(const unichar * pszSrc)
//{
//   // nDestLength is in XCHARs
//   strsize nDestLength = (pszSrc != nullptr) ? ::str().get_char_length(pszSrc) : 0;
//   if(nDestLength > 0)
//   {
//      char * pszBuffer = GetBuffer(nDestLength);
//      ::str().ConvertTochar(pszBuffer,nDestLength,pszSrc);
//      release_string_buffer(nDestLength);
//   }
//   else
//   {
//      Empty();
//   }
//
//   return *this;
//}
//
//string& string::operator=(const ::wd32_character * pszSrc)
//{
//   // nDestLength is in XCHARs
//   strsize nDestLength = (pszSrc != nullptr) ? wd32_to_wd16_len(pszSrc) : 0;
//   if(nDestLength > 0)
//   {
//      char * pszBuffer = GetBuffer(nDestLength);
//      wd32_to_ansi(pszBuffer,pszSrc,nDestLength);
//      release_string_buffer(nDestLength);
//   }
//   else
//   {
//      Empty();
//   }
//
//   return *this;
//}
//
//
//string& string::operator=(const uchar* pszSrc)
//{
//   return(operator=(reinterpret_cast<const char*>(pszSrc)));
//}
//
//string& string::operator=(char ch)
//{
//   char ach[2] = {ch,0};
//
//   return(operator=(ach));
//}
//
//string& string::operator=(unichar ch)
//{
//   unichar ach[2] = {ch,0};
//
//   return(operator=(ach));
//}
//
//string& string::operator+=(const string& str)
//{
//   append(str,str.get_length());
//
//   return *this;
//}
//
//string& string::operator+=(const scoped_string & strSrc)
//{
//   string::operator+=(pszSrc);
//
//   return *this;
//}
//
//#ifdef WINDOWS
//
//string& string::operator+=(const USHORT * pshSrc)
//{
//
//   string str(pshSrc, GetManager());
//
//   return(operator+=(str));
//
//}
//
//#endif
//
//string& string::operator+=(const unichar * pszSrc)
//{
//   string str(pszSrc,GetManager());
//
//   return(operator+=(str));
//}
//
//
//string & string::operator+=(char ch)
//{
//
//   append_char((char)ch);
//
//   return *this;
//
//}
//
//
//string & string::operator+=(uchar ch)
//{
//
//   append_char((char)ch);
//
//   return *this;
//
//}
//
//
//string & string::operator+=(unichar ch)
//{
//
//   append_char((char)ch);
//
//   return *this;
//
//}
//
//// Override from acme class
//string_manager * string::GetManager() const noexcept
//{
//   string_manager * pstringmanager = string::GetManager();
//   if(pstringmanager) { return pstringmanager; }
//
//   pstringmanager = ::str().GetDefaultManager();
//   return pstringmanager->Clone();
//}
//
//string & string::assign(const ::string & str)
//{
//   return operator = (str);
//}
//
//string & string::assign(const ::string & str,strsize pos,strsize n)
//{
//   return operator = (str.substr(pos,n));
//}
//
//string & string::assign(const char* s,strsize n)
//{
//   return operator = (string(s,n));
//}
//
//string & string::assign(const char * s)
//{
//   return operator = (s);
//}
//
//string & string::assign(strsize n,char ca)
//{
//   return operator = (string(ca,n));
//}
//
//string & string::assign(i32 n,i32 ca)
//{
//   return assign((u64)n,(u64)ca);
//}
//
//string & string::assign(i64 n,i64 ca)
//{
//   return assign((u64)n,(u64)ca);
//}
//
//string & string::assign(u32 n,u32 ca)
//{
//   return assign((u64)n,(u64)ca);
//}
//
//string & string::assign(u64 n,u64 ca)
//{
//   string strChar = ::str().uni_to_utf8(ca);
//   while(n > 0)
//   {
//      *this += strChar;
//   }
//   return *this;
//}
//
//
//
//// Comparison
//
//
//i32 string::collate(const scoped_string & str) const noexcept
//{
//   //ASSERT(__is_valid_string(psz));
//   return(::str().string_collate(m_psz,psz));
//}
//
//i32 string::case_insensitive_collate(const scoped_string & str) const noexcept
//{
//   //ASSERT(__is_valid_string(psz));
//   return(::str().case_insensitive_string_collate(m_psz,psz));
//}
//
////i32 string::compare(const scoped_string & str) const
////{
////   return compare(psz);
////}
////
////i32 string::compare_no_case(const scoped_string & str) const noexcept
////{
////   return case_insensitive_order(psz);
////}
//
////i32 string::collate(const scoped_string & str) const noexcept
////{
////   return Collate(psz);
////}
////
////i32 string::collate_no_case(const scoped_string & str) const noexcept
////{
////   return CollateNoCase(psz);
////}
//
//i32 string::compare(strsize iStart,strsize nCount,const scoped_string & str) const
//{
//   return substr(iStart,nCount).compare(psz);
//}
//
//i32 string::case_insensitive_order(strsize iStart,strsize nCount,const scoped_string & str) const
//{
//   return substr(iStart,nCount).case_insensitive_order(psz);
//}
//
//i32 string::collate(strsize iStart,strsize nCount,const scoped_string & str) const
//{
//   return substr(iStart,nCount).collate(psz);
//}
//
//i32 string::case_insensitive_collate(strsize iStart,strsize nCount,const scoped_string & str) const
//{
//   return substr(iStart,nCount).case_insensitive_order(psz);
//}
//
//i32 string::compare(strsize iStart,strsize nCount,const scoped_string & str,strsize start2,strsize count2) const
//{
//
//   return substr(iStart,nCount).compare(string(psz).substr(start2,count2));
//
//}
//
//
//i32 string::case_insensitive_order(strsize iStart,strsize nCount,const scoped_string & str,strsize start2,strsize count2) const
//{
//
//   return substr(iStart,nCount).case_insensitive_order(string(psz).substr(start2,count2));
//
//}
//
//
//i32 string::collate(strsize iStart,strsize nCount,const scoped_string & str,strsize start2,strsize count2) const
//{
//
//   return substr(iStart,nCount).collate(string(psz).substr(start2,count2));
//
//}
//
//i32 string::case_insensitive_collate(strsize iStart,strsize nCount,const scoped_string & str,strsize start2,strsize count2) const
//{
//
//   return substr(iStart,nCount).case_insensitive_collate(string(psz).substr(start2,count2));
//
//}
//
//
//bool string::contains(char ch,strsize iStart,strsize nCount) const
//{
//
//   return find(ch,iStart,nCount) >= 0;
//
//}
//
//
//bool string::contains(unichar wch,strsize iStart,strsize nCount) const
//{
//
//   return find_w(::str().uni_to_utf8(wch),iStart,nCount) >= 0;
//
//}
//
//
//bool string::contains(i32 i,strsize iStart,strsize nCount) const // utf8 char index
//{
//
//   return find_w(::str().uni_to_utf8(i),iStart,nCount) >= 0;
//
//}
//
//
//bool string::contains(const scoped_string & str,strsize iStart,strsize nCount) const
//{
//
//   return find(psz,iStart,nCount) >= 0;
//
//}
//
//
//bool string::contains(const ::string & str,strsize iStart,strsize nCount) const
//{
//
//   return find(str,iStart,nCount) >= 0;
//
//}
//
//bool string::contains_any(const string_array & stra) const
//{
//
//   for (auto & str : stra)
//   {
//
//      if (contains(str))
//      {
//
//         return true;
//
//      }
//
//   }
//
//   return false;
//
//}
//
//
//bool string::contains_all(const string_array & stra) const
//{
//
//   for (auto & str : stra)
//   {
//
//      if (!contains(str))
//      {
//
//         return false;
//
//      }
//
//   }
//
//   return true;
//
//}
//
//
//bool string::contains_ci(char ch,strsize iStart,strsize nCount) const
//{
//
//   return case_insensitive_find(ch,iStart,nCount) >= 0;
//
//}
//
//
//bool string::contains_ci(unichar wch,strsize iStart,strsize nCount) const
//{
//
//   return find_wci(::str().uni_to_utf8(wch),iStart,nCount) >= 0;
//
//}
//
//
//bool string::contains_ci(i32 i,strsize iStart,strsize nCount) const// utf8 char index
//{
//
//   return find_wci(::str().uni_to_utf8(i),iStart,nCount) >= 0;
//
//}
//
//
//bool string::contains_ci(const scoped_string & str,strsize iStart,strsize nCount) const
//{
//
//   return case_insensitive_find(psz,iStart,nCount) >= 0;
//
//}
//
//
//bool string::contains_ci(const ::string & str,strsize iStart,strsize nCount) const
//{
//
//   return case_insensitive_find(str,iStart,nCount) >= 0;
//
//}
//
//
//bool string::contains_any_ci(const string_array & stra) const
//{
//
//   for (auto & str : stra)
//   {
//
//      if (contains_ci(str))
//      {
//
//         return true;
//
//      }
//
//   }
//
//   return false;
//
//}
//
//
//bool string::contains_all_ci(const string_array & stra) const
//{
//
//   for (auto & str : stra)
//   {
//
//      if (!contains_ci(str))
//      {
//
//         return false;
//
//      }
//
//   }
//
//   return true;
//
//}
//
//
//bool string::contains_wci(unichar wch,strsize iStart,strsize nCount) const
//{
//
//   return find_wci(::str().uni_to_utf8(wch),iStart,nCount) >= 0;
//
//}
//
//
//bool string::contains_wci(i32 i,strsize iStart,strsize nCount) const// utf8 char index
//{
//
//   return find_wci(::str().uni_to_utf8(i),iStart,nCount) >= 0;
//
//}
//
//
//bool string::contains_wci(const scoped_string & str,strsize iStart,strsize nCount) const
//{
//
//   return find_wci(psz,iStart,nCount) >= 0;
//
//}
//
//
//bool string::contains_wci(const ::string & str,strsize iStart,strsize nCount) const
//{
//
//   return find_wci(str,iStart,nCount) >= 0;
//
//}
//
//bool string::contains_any_wci(const string_array & stra) const
//{
//
//   for (auto & str : stra)
//   {
//
//      if (contains_wci(str))
//      {
//
//         return true;
//
//      }
//
//   }
//
//   return false;
//
//}
//
//
//bool string::contains_all_wci(const string_array & stra) const
//{
//
//   for (auto & str : stra)
//   {
//
//      if (!contains_wci(str))
//      {
//
//         return false;
//
//      }
//
//   }
//
//   return true;
//
//}
//
//string & string::erase(strsize iStart,strsize strsize)
//{
//
//   if (iStart < 0)
//   {
//
//      strsize = 0;
//
//   }
//
//   if (strsize < 0)
//   {
//
//      strsize = get_length();
//
//   }
//
//   Delete(iStart,strsize);
//
//   return *this;
//
//}
//
//
//strsize string::Delete(strsize iIndex,strsize nCount)
//{
//
//   strsize nLength = get_length();
//
//   if (iIndex < 0)
//   {
//
//      iIndex = 0;
//
//   }
//
//   if (nCount < 0)
//   {
//
//      nCount = nLength;
//
//   }
//
//   if (nCount + iIndex > nLength)
//   {
//
//      nCount = nLength - iIndex;
//
//   }
//
//   if (nCount < 0)
//   {
//
//      return get_length();
//
//   }
//
//   if(nCount + iIndex > nLength)
//   {
//
//      nCount = nLength - iIndex;
//
//   }
//
//   if(nCount > 0)
//   {
//
//      strsize nNewLength = nLength - nCount;
//
//      strsize nCopy = nLength - (iIndex + nCount) + 1;
//
//      char * pszBuffer = GetBuffer();
//
//      ::acme::memmove_s(pszBuffer + iIndex, (size_t) nCopy, pszBuffer + iIndex + nCount, (size_t) nCopy);
//
//      release_string_buffer(nNewLength);
//
//   }
//
//   return get_length();
//
//}
//
//
//strsize string::Insert(strsize iIndex,char ch)
//{
//
//   if (iIndex < 0)
//   {
//
//      iIndex = 0;
//
//   }
//
//   if(iIndex > get_length())
//   {
//
//      iIndex = get_length();
//
//   }
//
//   strsize nNewLength = get_length() + 1;
//
//   char * pszBuffer = GetBuffer(nNewLength);
//
//   // move existing bytes down
//   ::acme::memmove_s(pszBuffer + iIndex + 1, nNewLength - iIndex, pszBuffer + iIndex, nNewLength - iIndex);
//
//   pszBuffer[iIndex] = ch;
//
//   release_string_buffer(nNewLength);
//
//   return nNewLength;
//
//}
//
//
//strsize string::Insert(strsize iIndex,const scoped_string & str)
//{
//
//   if (iIndex < 0)
//   {
//
//      iIndex = 0;
//
//   }
//
//   if(iIndex > get_length())
//   {
//
//      iIndex = get_length();
//
//   }
//
//   // nInsertLength and nNewLength are in XCHARs
//
//   strsize nInsertLength = ::str().SafeStringLen(psz);
//
//   strsize nNewLength = get_length();
//
//   if(nInsertLength > 0)
//   {
//
//      nNewLength += nInsertLength;
//
//      char * pszBuffer = GetBuffer(nNewLength);
//      // move existing bytes down
//      ::acme::memmove_s(pszBuffer + iIndex + nInsertLength,(nNewLength - iIndex - nInsertLength + 1)*sizeof(char),
//                        pszBuffer + iIndex,(nNewLength - iIndex - nInsertLength + 1)*sizeof(char));
//      ::acme::memcpy_s(pszBuffer + iIndex,nInsertLength*sizeof(char),
//                       psz,nInsertLength*sizeof(char));
//      release_string_buffer(nNewLength);
//   }
//
//   return(nNewLength);
//}
//
//strsize string::replace(char chOld,char chNew,strsize iStart)
//{
//   strsize nCount = 0;
//
//   // i16-circuit the nop case
//   if(chOld != chNew)
//   {
//      // otherwise modify each character that matches in the string
//      bool bCopied = false;
//      char * pszBuffer = const_cast<char *>(m_psz + iStart);  // We don't actually write to pszBuffer until we've called GetBuffer().
//
//      strsize nLength = get_length();
//      strsize iChar = 0;
//      while(iChar < nLength)
//      {
//         // replace instances of the specified character only
//         if(pszBuffer[iChar] == chOld)
//         {
//            if(!bCopied)
//            {
//               bCopied = true;
//               pszBuffer = GetBuffer(nLength);
//            }
//            pszBuffer[iChar] = chNew;
//            nCount++;
//         }
//         iChar = strsize((pszBuffer + iChar + 1) - pszBuffer);
//      }
//      if(bCopied)
//      {
//         release_string_buffer(nLength);
//      }
//   }
//
//   return(nCount);
//}
//
//strsize string::replace(const scoped_string & strOld,const scoped_string & strNew,strsize iStart)
//{
//   // can't have is_empty or nullptr pszOld
//
//
//   // nSourceLen is in XCHARs
//   strsize nSourceLen = ::str().SafeStringLen(pszOld);
//   if(nSourceLen == 0)
//      return(0);
//   // nReplacementLen is in XCHARs
//   strsize nReplacementLen = ::str().SafeStringLen(pszNew);
//
//   // loop once to figure out the size_i32 of the result string
//   strsize nCount = 0;
//   {
//      const scoped_string & strStart = m_psz + iStart;
//      //      const scoped_string & strEnd = pszStart+get_length();
//      const scoped_string & strTarget;
//      while((pszTarget = ::str().string_find_string(pszStart,pszOld)) != nullptr)
//      {
//         nCount++;
//         pszStart = pszTarget + nSourceLen;
//      }
//   }
//
//   // if any changes were made, make them
//   if(nCount > 0)
//   {
//      // if the buffer is too small, just
//      //   allocate a memory_new buffer (slow but sure)
//      strsize nOldLength = get_length();
//      strsize nNewLength = nOldLength + (nReplacementLen - nSourceLen)*nCount;
//
//      char * pszBuffer = GetBuffer(maximum(nNewLength,nOldLength));
//
//      char * pszStart = pszBuffer + iStart;
//      char * pszEnd = pszBuffer + nOldLength;
//
//      // loop again to actually do the work
//      while(pszStart < pszEnd)
//      {
//         char * pszTarget;
//         while((pszTarget = ::str().string_find_string(pszStart,pszOld)) != nullptr)
//         {
//            strsize nBalance = nOldLength - strsize(pszTarget - pszBuffer + nSourceLen);
//            ::acme::memmove_s(pszTarget + nReplacementLen,nBalance*sizeof(char),
//                              pszTarget + nSourceLen,nBalance*sizeof(char));
//            ::acme::memcpy_s(pszTarget,nReplacementLen*sizeof(char),
//                             pszNew,nReplacementLen*sizeof(char));
//            pszStart = pszTarget + nReplacementLen;
//            pszTarget[nReplacementLen + nBalance] = 0;
//            nOldLength += (nReplacementLen - nSourceLen);
//         }
//         pszStart += ::str().SafeStringLen(pszStart) + 1;
//      }
//      ASSERT(pszBuffer[nNewLength] == 0);
//      release_string_buffer(nNewLength);
//   }
//
//   return(nCount);
//}
//
//
//::count string::replace_count(const scoped_string & strOld, const scoped_string & strNew, strsize iStart)
//{
//   // can't have is_empty or nullptr pszOld
//
//
//   ::count c = 0;
//
//   // nSourceLen is in XCHARs
//   strsize nSourceLen = ::str().SafeStringLen(pszOld);
//   if (nSourceLen == 0)
//      return(0);
//   // nReplacementLen is in XCHARs
//   strsize nReplacementLen = ::str().SafeStringLen(pszNew);
//
//   // loop once to figure out the size_i32 of the result string
//   strsize nCount = 0;
//   {
//      const scoped_string & strStart = m_psz + iStart;
//      //      const scoped_string & strEnd = pszStart+get_length();
//      const scoped_string & strTarget;
//      while ((pszTarget = ::str().string_find_string(pszStart, pszOld)) != nullptr)
//      {
//         nCount++;
//         pszStart = pszTarget + nSourceLen;
//         c++;
//      }
//   }
//
//   // if any changes were made, make them
//   if (nCount > 0)
//   {
//      // if the buffer is too small, just
//      //   allocate a memory_new buffer (slow but sure)
//      strsize nOldLength = get_length();
//      strsize nNewLength = nOldLength + (nReplacementLen - nSourceLen)*nCount;
//
//      char * pszBuffer = GetBuffer(maximum(nNewLength, nOldLength));
//
//      char * pszStart = pszBuffer + iStart;
//      char * pszEnd = pszBuffer + nOldLength;
//
//      // loop again to actually do the work
//      while (pszStart < pszEnd)
//      {
//         char * pszTarget;
//         while ((pszTarget = ::str().string_find_string(pszStart, pszOld)) != nullptr)
//         {
//            strsize nBalance = nOldLength - strsize(pszTarget - pszBuffer + nSourceLen);
//            ::acme::memmove_s(pszTarget + nReplacementLen, nBalance * sizeof(char),
//                              pszTarget + nSourceLen, nBalance * sizeof(char));
//            ::acme::memcpy_s(pszTarget, nReplacementLen * sizeof(char),
//                             pszNew, nReplacementLen * sizeof(char));
//            pszStart = pszTarget + nReplacementLen;
//            pszTarget[nReplacementLen + nBalance] = 0;
//            nOldLength += (nReplacementLen - nSourceLen);
//         }
//         pszStart += ::str().SafeStringLen(pszStart) + 1;
//      }
//      ASSERT(pszBuffer[nNewLength] == 0);
//      release_string_buffer(nNewLength);
//   }
//
//   return c;
//
//}
//
//
//string & string::replace(strsize iStart,strsize nCount,const scoped_string & str)
//{
//   if(nCount < 0)
//   {
//      return operator = (Left(iStart) + psz);
//   }
//   else
//   {
//      return operator = (Left(iStart) + psz + Mid(nCount));
//   }
//}
//
//string & string::replace(strsize iStart,strsize nCount,const scoped_string & str,strsize nSubLen)
//{
//   if(nCount < 0)
//   {
//      return operator = (Left(iStart) + string(psz,nSubLen));
//   }
//   else
//   {
//      return operator = (Left(iStart) + string(psz,nSubLen) + Mid(nCount));
//   }
//}
//
//strsize string::erase(char chRemove)
//{
//   strsize nLength = get_length();
//   char * pszBuffer = GetBuffer(nLength);
//
//   char * pszSource = pszBuffer;
//   char * pszDest = pszBuffer;
//   char * pszEnd = pszBuffer + nLength;
//
//   while(pszSource < pszEnd)
//   {
//      char * pszNewSource = pszSource + 1;
//      if(*pszSource != chRemove)
//      {
//         // copy the source to the destination.  Remember to copy all bytes of an MBCS character
//         // copy the source to the destination.  Remember to copy all bytes of an MBCS character
//         size_t NewSourceGap = (pszNewSource - pszSource);
//         char * pszNewDest = pszDest + NewSourceGap;
//         size_t i = 0;
//         for(i = 0; pszDest != pszNewDest && i < NewSourceGap; i++)
//         {
//            *pszDest = *pszSource;
//            pszSource++;
//            pszDest++;
//         }
//      }
//      pszSource = pszNewSource;
//   }
//   *pszDest = 0;
//   strsize nCount = strsize(pszSource - pszDest);
//   release_string_buffer(nLength - nCount);
//
//   return(nCount);
//}
//
//string string::Tokenize(const scoped_string & strTokens,strsize& iStart) const
//{
//   ASSERT(iStart >= 0);
//
//   if(iStart < 0)
//      throw ::exception(error_bad_argument);
//
//   if((pszTokens == nullptr) || (*pszTokens == (char)0))
//   {
//      if(iStart < get_length())
//      {
//         return(string(m_psz + iStart,GetManager()));
//      }
//   }
//   else
//   {
//      const scoped_string & strPlace = m_psz + iStart;
//      const scoped_string & strEnd = m_psz + get_length();
//      if(pszPlace < pszEnd)
//      {
//         strsize nIncluding = ::str().string_span_including(pszPlace,
//                              pszTokens);
//
//         if((pszPlace + nIncluding) < pszEnd)
//         {
//            pszPlace += nIncluding;
//            strsize nExcluding = ::str().string_span_excluding(pszPlace,pszTokens);
//
//            strsize iFrom = iStart + nIncluding;
//            strsize nUntil = nExcluding;
//            iStart = iFrom + nUntil + 1;
//
//            return(Mid(iFrom,nUntil));
//         }
//      }
//   }
//
//   // return is_empty string, done tokenizing
//   iStart = -1;
//
//   return(string(GetManager()));
//}
//
//// find routines
//
//// find the first occurrence of character 'ch', starting at strsize 'iStart'
//strsize string::find(char ch,strsize iStart,strsize nCount) const RELEASENOTHROW
//{
//   // iStart is in XCHARs
//   ASSERT(iStart >= 0);
//
//   // nLength is in XCHARs
//   strsize nLength = get_length();
//   if(iStart < 0 || iStart >= nLength)
//   {
//      return -1;
//   }
//
//   if(nCount < 0)
//      nCount = nLength;
//
//   if(nCount + iStart > nLength)
//      nCount = nLength - iStart;
//
//   if(nCount < 0)
//      return -1;
//
//   const scoped_string & str = m_psz + iStart;
//   for(i32 i = 0; i < nCount; i++)
//   {
//      if(psz[i] == ch)
//      {
//         return iStart + i;
//      }
//   }
//   return -1;
//}
//
//// find the first occurrence of character 'ch', starting at strsize 'iStart'
//strsize string::case_insensitive_find(char ch,strsize iStart,strsize nCount) const RELEASENOTHROW
//{
//   // iStart is in XCHARs
//   ASSERT(iStart >= 0);
//
//   // nLength is in XCHARs
//   strsize nLength = get_length();
//   if(iStart < 0 || iStart >= nLength)
//   {
//      return(-1);
//   }
//
//   if(nCount < 0)
//      nCount = nLength;
//
//   if(nCount + iStart > nLength)
//      nCount = nLength - iStart;
//
//   if(nCount < 0)
//      return -1;
//
//   const scoped_string & str = m_psz + iStart;
//   for(i32 i = 0; i < nCount; i++)
//   {
//      if(tolower(psz[i]) == tolower(ch))
//      {
//         return iStart + i;
//      }
//   }
//   return -1;
//}
//
//
//strsize string::find_whitespace_or_length(strsize iStart) const RELEASENOTHROW
//{
//
//   if (iStart >= get_length())
//   {
//
//      return get_length();
//
//   }
//
//   strsize iFound = find_first_in("\t\n\r ", iStart);
//
//   if (iFound < 0)
//   {
//
//      return get_length();
//
//   }
//
//   return iFound;
//
//}
//
//
//strsize string::find_first_of(char ch,strsize iStart) const RELEASENOTHROW
//{
//   return find(ch,iStart);
//}
//// look for a specific sub-string
//
//// find the first occurrence of string 'pszSub', starting at strsize 'iStart'
//strsize string::find(const scoped_string & strSub,strsize iStart,strsize nCount,const char ** pszTail) const RELEASENOTHROW
//{
//   // iStart is in XCHARs
//   ASSERT(iStart >= 0);
//   ASSERT(__is_valid_string(pszSub));
//
//   if(pszSub == nullptr)
//   {
//      return(-1);
//   }
//   // nLength is in XCHARs
//   strsize nLength = get_length();
//   if(iStart < 0 || iStart > nLength)
//   {
//      return(-1);
//   }
//
//   strsize nLength2 = strlen(pszSub);
//
//   if(nCount < 0)
//      nCount = nLength;
//
//   if(nCount + iStart + nLength2 > nLength)
//      nCount = nLength - iStart - nLength2;
//
//   if(nCount < 0)
//      return -1;
//
//   const scoped_string & str = m_psz + iStart;
//   for(i32 i = 0; i <= nCount; i++)
//   {
//      bool bFound = true;
//      i32 j;
//      for(j = 0; j < nLength2; j++)
//      {
//         if(psz[j] != pszSub[j])
//         {
//            bFound = false;
//            break;
//         }
//      }
//      if(bFound && j == nLength2)
//      {
//         if(pszTail)
//            *pszTail = &psz[j];
//         return i + iStart;
//      }
//      psz++;
//   }
//   return -1;
//}
//
//// find the first occurrence of string 'pszSub', starting at strsize 'iStart'
//strsize string::case_insensitive_find(const scoped_string & strSub,strsize iStart,strsize nCount,const char ** pszTail) const RELEASENOTHROW
//{
//   // iStart is in XCHARs
//   ASSERT(iStart >= 0);
//   ASSERT(__is_valid_string(pszSub));
//
//   if(pszSub == nullptr)
//   {
//      return(-1);
//   }
//   // nLength is in XCHARs
//   strsize nLength = get_length();
//   if(iStart < 0 || iStart > nLength)
//   {
//      return(-1);
//   }
//
//   strsize nLength2 = strlen(pszSub);
//
//   if(nCount < 0)
//      nCount = nLength;
//
//   if(nCount + iStart + nLength2 > nLength)
//      nCount = nLength - iStart - nLength2;
//
//   if(nCount < 0)
//      return -1;
//
//   i32 j;
//
//   const scoped_string & str = m_psz + iStart;
//   for(i32 i = 0; i <= nCount; i++)
//   {
//      bool bFound = true;
//      for(j = 0; j < nLength2; j++)
//      {
//         if(tolower(psz[j]) != tolower(pszSub[j]))
//         {
//            bFound = false;
//            break;
//         }
//      }
//      if(bFound)
//      {
//         if(pszTail)
//            *pszTail = &psz[j];
//         return i + iStart;
//      }
//      psz++;
//   }
//   return -1;
//}
//
//// find the first occurrence of string 'pszSub', starting at strsize 'iStart'
//strsize string::find_w(const scoped_string & strSub,strsize iStart,strsize nCount,const char ** pszTail) const RELEASENOTHROW
//{
//   // iStart is in XCHARs
//   ASSERT(iStart >= 0);
//   ASSERT(__is_valid_string(pszSub));
//
//   if(pszSub == nullptr)
//   {
//      return(-1);
//   }
//
//   if(iStart < 0)
//      return -1;
//
//   const scoped_string & str = m_psz + iStart;
//
//   if(*psz == '\0')
//      return -1;
//   while(*psz != '\0' && (psz - m_psz - iStart) < nCount)
//   {
//      bool bFound = true;
//      const scoped_string & str2 = psz;
//      const scoped_string & strSub2 = pszSub;
//      while(*psz2 != '\0' && *pszSub2 != '\0')
//      {
//         if(::str().get_utf8_char(psz2) != ::str().get_utf8_char(pszSub2))
//         {
//            bFound = false;
//            break;
//         }
//         unicode_increment(psz2);
//         unicode_increment(pszSub2);
//      }
//      if(bFound)
//      {
//         if(*pszSub2 == '\0')
//         {
//            if(pszTail)
//               *pszTail = psz2;
//            return psz - m_psz;
//         }
//         else
//         {
//            return -1;
//         }
//      }
//      psz++;
//   }
//   return -1;
//}
//
//// find the first occurrence of string 'pszSub', starting at strsize 'iStart'
//strsize string::find_wci(const scoped_string & strSub,strsize iStart,strsize nCount,const char ** pszTail) const RELEASENOTHROW
//{
//   // iStart is in XCHARs
//   ASSERT(iStart >= 0);
//   ASSERT(__is_valid_string(pszSub));
//
//   if(pszSub == nullptr)
//   {
//      return(-1);
//   }
//
//   if(iStart < 0)
//      return -1;
//
//   const scoped_string & str = m_psz + iStart;
//
//   if(*psz == '\0')
//      return -1;
//   while(*psz != '\0' && (psz - m_psz - iStart) < nCount)
//   {
//      bool bFound = true;
//      const scoped_string & str2 = psz;
//      const scoped_string & strSub2 = pszSub;
//      while(*psz2 != '\0' && *pszSub2 != '\0')
//      {
//         if(unicode_to_lower_case(psz2) != unicode_to_lower_case(pszSub2))
//         {
//            bFound = false;
//            break;
//         }
//         unicode_increment(psz2);
//         unicode_increment(pszSub2);
//      }
//      if(bFound)
//      {
//         if(*pszSub2 == '\0')
//         {
//            if(pszTail)
//               *pszTail = psz2;
//            return psz - m_psz;
//         }
//         else
//         {
//            return -1;
//         }
//      }
//      psz++;
//   }
//   return -1;
//}
//
//
//strsize string::rear_find(const scoped_string & strSub,strsize start,strsize count) const RELEASENOTHROW
//{
//
//   const scoped_string & strTail = nullptr;
//
//   if(find(pszSub,start,count,&pszTail) < 0)
//      return -1;
//
//   return pszTail - m_pszData;
//
//}
//
//
//strsize string::find_w_tail(const scoped_string & strSub,strsize start,strsize count) const RELEASENOTHROW
//{
//
//   const scoped_string & strTail = nullptr;
//
//   if(find_w(pszSub,start,count,&pszTail) < 0)
//      return -1;
//
//   return pszTail - m_pszData;
//
//}
//
//
//strsize string::find_ci_tail(const scoped_string & strSub,strsize start,strsize count) const RELEASENOTHROW
//{
//
//   const scoped_string & strTail = nullptr;
//
//   if(case_insensitive_find(pszSub,start,count,&pszTail) < 0)
//      return -1;
//
//   return pszTail - m_pszData;
//
//}
//
//
//strsize string::find_wci_tail(const scoped_string & strSub,strsize start,strsize count) const RELEASENOTHROW
//{
//
//   const scoped_string & strTail = nullptr;
//
//   if(find_wci(pszSub,start,count,&pszTail) < 0)
//      return -1;
//
//   return pszTail - m_pszData;
//
//}
//
//
//// find the first occurrence of any of the characters in string 'pszCharSet'
//strsize string::FindOneOf(const scoped_string & strCharSet,strsize iStart,strsize n) const RELEASENOTHROW
//{
//   string strCharSet(pszCharSet,n);
//   // iStart is in XCHARs
//   ASSERT(iStart >= 0);
//
//   // nLength is in XCHARs
//   strsize nLength = get_length();
//   if(iStart < 0 || iStart >= nLength)
//   {
//      return(-1);
//   }
//   const scoped_string & str = ::str().string_scan_set(&m_psz[iStart],strCharSet);
//   return((psz == nullptr) ? -1 : strsize(psz - m_psz));
//}
//
//strsize string::find_first_of(const scoped_string & strCharSet,strsize iStart) const RELEASENOTHROW
//{
//   return FindOneOf(pszCharSet,iStart,-1);
//}
//
//strsize string::find_first_of(const scoped_string & strCharSet,strsize iStart,strsize n) const RELEASENOTHROW
//{
//   return FindOneOf(pszCharSet,iStart,n);
//}
//
//strsize string::find_first_of(const ::string & strCharSet,strsize pos) const RELEASENOTHROW
//{
//   return FindOneOf(strCharSet,pos,strCharSet.get_length());
//}
//
//strsize string::find_first_not_of(const string& str,strsize pos) const
//RELEASENOTHROW
//{
//   return find_first_not_of(str,pos,str.get_length());
//}
//
//strsize string::find_first_not_of(const char* s,strsize pos) const
//RELEASENOTHROW
//{
//   return find_first_not_of(s,pos,strlen(s));
//}
//
//strsize string::find_first_not_of(char ca,strsize pos) const
//RELEASENOTHROW
//{
//   strsize nLength = get_length();
//
//   if(pos < 0 || pos >= nLength)
//      return -1;
//   const scoped_string & str = &m_psz[pos];
//   while(*psz != '\0' && *psz == ca)
//   {
//      psz++;
//   }
//   if(*psz == '\0')
//      return -1;
//   else
//      return psz - m_psz;
//}
//
//strsize string::find_first_not_of(const char* s,strsize pos,strsize n) const
//RELEASENOTHROW
//{
//   string strChars(s,n);
//
//   strsize nLength = get_length();
//
//   if(pos < 0 || pos >= nLength)
//      return -1;
//   const scoped_string & str = &m_psz[pos];
//   while(*psz != '\0' && strChars.contains(*psz))
//   {
//      psz++;
//   }
//   if(*psz == '\0')
//      return -1;
//   else
//      return psz - m_psz;
//}
//
//
//// find the first occurrence of any of the characters in string 'pszCharSet'
//strsize string::find_last_of(char ca,strsize pos) const RELEASENOTHROW
//{
//   strsize nLength = get_length();
//   // nLength is in XCHARs
//   if(pos < 0)
//      pos = nLength - 1;
//   if(pos < 0 || pos >= nLength)
//   {
//      return(-1);
//   }
//   const scoped_string & str = m_psz;
//   while(pos >= 0 && psz[pos] != ca)
//   {
//      pos--;
//   }
//   return pos;
//}
//
//strsize string::find_last_of(const scoped_string & strCharSet,strsize iStart) const RELEASENOTHROW
//{
//   return find_last_of(pszCharSet,iStart,-1);
//}
//
//strsize string::find_last_of(const scoped_string & strCharSet,strsize pos,strsize n) const RELEASENOTHROW
//{
//   strsize nLength = get_length();
//   // nLength is in XCHARs
//   if(pos < 0)
//      pos = nLength - 1;
//   if(pos < 0 || pos >= nLength)
//   {
//      return(-1);
//   }
//   string strChars(pszCharSet,n);
//   const scoped_string & str = m_psz;
//   while(pos >= 0 && !strChars.contains(psz[pos]))
//   {
//      pos--;
//   }
//   return pos;
//}
//
//strsize string::find_last_of(const ::string & strCharSet,strsize pos) const RELEASENOTHROW
//{
//   return find_last_of(strCharSet,pos,strCharSet.get_length());
//}
//
//
//// find the first occurrence of any of the characters in string 'pszCharSet'
//strsize string::find_last_not_of(char ca,strsize pos) const RELEASENOTHROW
//{
//   strsize nLength = get_length();
//   // nLength is in XCHARs
//   if(pos < 0)
//      pos = nLength - 1;
//   if(pos < 0 || pos >= nLength)
//   {
//      return(-1);
//   }
//   const scoped_string & str = m_psz;
//   while(pos >= 0 && psz[pos] == ca)
//   {
//      pos--;
//   }
//   return pos;
//}
//
//strsize string::find_last_not_of(const scoped_string & strCharSet,strsize iStart) const RELEASENOTHROW
//{
//   return find_last_not_of(pszCharSet,iStart,-1);
//}
//
//strsize string::find_last_not_of(const scoped_string & strCharSet,strsize pos,strsize n) const RELEASENOTHROW
//{
//   strsize nLength = get_length();
//   // nLength is in XCHARs
//   if(pos < 0)
//      pos = nLength - 1;
//   if(pos < 0 || pos >= nLength)
//   {
//      return(-1);
//   }
//   string strChars(pszCharSet,n);
//   const scoped_string & str = m_psz;
//   while(pos >= 0 && strChars.contains(psz[pos]))
//   {
//      pos--;
//   }
//   return pos;
//}
//
//strsize string::find_last_not_of(const ::string & strCharSet,strsize pos) const RELEASENOTHROW
//{
//   return find_last_not_of(strCharSet,pos,strCharSet.get_length());
//}
//
//
//// find the last occurrence of character 'ch'
//strsize string::rear_find(char ch,strsize iStart) const RELEASENOTHROW
//{
//   // find last single character
//   const scoped_string & str = ::str().string_find_char_reverse(m_psz,ch,iStart);
//
//   // return -1 if not found, distance from beginning otherwise
//   return((psz == nullptr) ? -1 : strsize(psz - m_psz));
//}
//
//// find the last occurrence of character 'ch'
//strsize string::rear_find(const char * ch,strsize iStart) const RELEASENOTHROW
//{
//   // find last single character
//   const scoped_string & str = ::str().string_find_string_reverse(m_psz,ch,iStart);
//
//   // return -1 if not found, distance from beginning otherwise
//   return((psz == nullptr) ? -1 : strsize(psz - m_psz));
//}
//
//// manipulation
//
//// Convert the string to uppercase
//string& string::make_upper()
//{
//   strsize nLength = get_length();
//   char * pszBuffer = GetBuffer(nLength);
//   ::str().string_uppercase(pszBuffer,nLength + 1);
//   release_string_buffer(nLength);
//
//   return *this;
//}
//
//// Convert the string to lowercase
//string& string::make_lower()
//{
//   strsize nLength = get_length();
//   char * pszBuffer = GetBuffer(nLength);
//   ::str().string_lowercase(pszBuffer,nLength + 1);
//   release_string_buffer(nLength);
//
//   return *this;
//}
//
//// Reverse the string
//string& string::MakeReverse()
//{
//   strsize nLength = get_length();
//   char * pszBuffer = GetBuffer(nLength);
//   ::str().string_reverse(pszBuffer);
//   release_string_buffer(nLength);
//
//   return *this;
//}
//
//// trimming
//
//// erase all trailing whitespace
//string& string::trim_right()
//{
//
//   const scoped_string & strLast = nullptr;
//   const scoped_string & strMax = m_psz + get_length();
//   const scoped_string & str = pszMax;
//
//   if(psz != nullptr)
//   {
//      while(true)
//      {
//         psz = ::str().utf8_dec(m_psz,psz);
//         if(psz < m_psz)
//            break;
//         if(!::str().is_space(psz))
//         {
//            pszLast = ::str().__utf8_inc(psz);
//            break;
//         }
//      }
//   }
//
//   if(pszLast != nullptr && pszLast < pszMax)
//   {
//
//      // truncate at trailing space iStart
//
//      strsize iLast = strsize(pszLast - m_psz);
//
//      Truncate(iLast);
//
//   }
//
//   return *this;
//
//}
//
//// erase all leading whitespace
//string& string::trim_left()
//{
//   // find first non-space character
//
//   const scoped_string & str = m_psz;
//
//   strsize iHere;
//
//   while(::str().is_space(psz))
//   {
//
//      unicode_increment(psz);
//
//      iHere = (strsize)(psz - m_psz);
//
//      if(iHere >= get_length())
//      {
//
//         if(iHere == get_length())
//         {
//
//            break;
//
//         }
//         else
//         {
//
//            return *this;
//
//         }
//
//
//      }
//
//   }
//
//
//   if(psz != m_psz)
//   {
//      // fix up data and length
//      strsize iFirst = strsize(psz - m_psz);
//      char * pszBuffer = GetBuffer(get_length());
//      psz = pszBuffer + iFirst;
//      strsize nDataLength = get_length() - iFirst;
//      ::acme::memmove_s(pszBuffer,(nDataLength + 1)*sizeof(char),
//                        psz,(nDataLength + 1)*sizeof(char));
//      release_string_buffer(nDataLength);
//   }
//
//   return *this;
//}
//
//// erase all leading and trailing whitespace
//string& string::trim()
//{
//   return(trim_right().trim_left());
//}
//
//// erase all leading and trailing occurrences of character 'chTarget'
//string& string::trim(char chTarget)
//{
//   return(trim_right(chTarget).trim_left(chTarget));
//}
//
//// erase all leading and trailing occurrences of any of the characters in the string 'pszTargets'
//string& string::trim(const scoped_string & strTargets)
//{
//   return(trim_right(pszTargets).trim_left(pszTargets));
//}
//
//// trimming anything (either side)
//
//// erase all trailing occurrences of character 'chTarget'
//string& string::trim_right(char chTarget)
//{
//   // find beginning of trailing matches
//   // by starting at beginning (DBCS aware)
//
//   const scoped_string & str = m_psz;
//   const scoped_string & strLast = nullptr;
//
//   while(*psz != 0)
//   {
//      if(*psz == chTarget)
//      {
//         if(pszLast == nullptr)
//         {
//            pszLast = psz;
//         }
//      }
//      else
//      {
//         pszLast = nullptr;
//      }
//      unicode_increment(psz);
//   }
//
//   if(pszLast != nullptr)
//   {
//      // truncate at left-most matching character
//      strsize iLast = strsize(pszLast - m_psz);
//      Truncate(iLast);
//   }
//
//   return *this;
//}
//
//// erase all trailing occurrences of any of the characters in string 'pszTargets'
//string& string::trim_right(const scoped_string & strTargets)
//{
//   // if we're not trimming anything, we're not doing any work
//   if((pszTargets == nullptr) || (*pszTargets == 0))
//   {
//      return *this;
//   }
//
//   // find beginning of trailing matches
//   // by starting at beginning (DBCS aware)
//
//   const scoped_string & str = m_psz;
//   const scoped_string & strStart = psz;
//   const scoped_string & strLast = nullptr;
//
//   while(!is_ptr_null(psz, 1024) && *psz != 0)
//   {
//      if(::str().string_find_char(pszTargets,*psz) != nullptr)
//      {
//         if(pszLast == nullptr)
//         {
//            pszLast = psz;
//         }
//      }
//      else
//      {
//         pszLast = nullptr;
//      }
//      unicode_increment(psz);
//   }
//
//   if(pszLast != nullptr)
//   {
//      // truncate at left-most matching character
//      strsize iLast = strsize(pszLast - pszStart);
//      Truncate(iLast);
//   }
//
//   return *this;
//}
//
//// erase all leading occurrences of character 'chTarget'
//string& string::trim_left(char chTarget)
//{
//   // find first non-matching character
//   const scoped_string & str = m_psz;
//
//   while(chTarget == *psz)
//   {
//      unicode_increment(psz);
//   }
//
//   if(psz != m_psz)
//   {
//      // fix up data and length
//      strsize iFirst = strsize(psz - m_psz);
//      char * pszBuffer = GetBuffer(get_length());
//      psz = pszBuffer + iFirst;
//      strsize nDataLength = get_length() - iFirst;
//      ::acme::memmove_s(pszBuffer,(nDataLength + 1)*sizeof(char),
//                        psz,(nDataLength + 1)*sizeof(char));
//      release_string_buffer(nDataLength);
//   }
//
//   return *this;
//}
//
//// erase all leading occurrences of any of the characters in string 'pszTargets'
//string& string::trim_left(const scoped_string & strTargets)
//{
//   // if we're not trimming anything, we're not doing any work
//   if((pszTargets == nullptr) || (*pszTargets == 0))
//   {
//      return *this;
//   }
//
//   const scoped_string & str = m_psz;
//   while((*psz != 0) && (::str().string_find_char(pszTargets,*psz) != nullptr))
//   {
//      unicode_increment(psz);
//   }
//
//   if(psz != m_psz)
//   {
//      // fix up data and length
//      strsize iFirst = strsize(psz - m_psz);
//      char * pszBuffer = GetBuffer(get_length());
//      psz = pszBuffer + iFirst;
//      strsize nDataLength = get_length() - iFirst;
//      ::acme::memmove_s(pszBuffer,(nDataLength + 1)*sizeof(char),
//                        psz,(nDataLength + 1)*sizeof(char));
//      release_string_buffer(nDataLength);
//   }
//
//   return *this;
//}
//
//
//// erase all trailing whitespace
//string string::right_trimmed() const
//{
//
//   string str(*this);
//
//   str.trim_right();
//
//   return str;
//
//}
//
//
//// erase all leading whitespace
//string string::left_trimmed() const
//{
//
//   string str(*this);
//
//   str.trim_left();
//
//   return str;
//
//}
//
//
//// erase all leading and trailing whitespace
//string string::trimmed() const
//{
//
//   string str(*this);
//
//   str.trim();
//
//   return str;
//
//}
//
//
//// erase all leading and trailing occurrences of character 'chTarget'
//string string::trimmed(char chTarget) const
//{
//
//   string str(*this);
//
//   str.trim(chTarget);
//
//   return str;
//
//}
//
//
//// erase all leading and trailing occurrences of any of the characters in the string 'pszTargets'
//string string::trimmed(const scoped_string & strTargets) const
//{
//
//   string str(*this);
//
//   str.trim(pszTargets);
//
//   return str;
//
//}
//
//
//// trimming anything (either side)
//
//// erase all trailing occurrences of character 'chTarget'
//string string::right_trimmed(char chTarget) const
//{
//
//   string str(*this);
//
//   str.trim_right(chTarget);
//
//   return str;
//
//}
//
//
//// erase all trailing occurrences of any of the characters in string 'pszTargets'
//string string::right_trimmed(const scoped_string & strTargets) const
//{
//
//   string str(*this);
//
//   str.trim_right(pszTargets);
//
//   return str;
//
//}
//
//
//// erase all leading occurrences of character 'chTarget'
//string string::left_trimmed(char chTarget) const
//{
//
//   string str(*this);
//
//   str.trim_left(chTarget);
//
//   return str;
//
//}
//
//
//// erase all leading occurrences of any of the characters in string 'pszTargets'
//string string::left_trimmed(const scoped_string & strTargets) const
//{
//
//   string str(*this);
//
//   str.trim_left(pszTargets);
//
//   return str;
//
//}
//
//
//// Convert the string to the OEM character set
//void string::AnsiToOem()
//{
//   strsize nLength = get_length();
//   char * pszBuffer = GetBuffer(nLength);
//   ::str().ConvertToOem(pszBuffer,nLength + 1);
//   release_string_buffer(nLength);
//}
//
//// Convert the string to the ANSI character set
//void string::OemToAnsi()
//{
//   strsize nLength = get_length();
//   char * pszBuffer = GetBuffer(nLength);
//   ::str().ConvertToAnsi(pszBuffer,nLength + 1);
//   release_string_buffer(nLength);
//}
//
//// Very simple sub-string extraction
//
//// Return the substring starting at strsize 'iFirst'
//string string::Mid(strsize iFirst) const
//{
//   return Mid(iFirst,-1);
//}
//
//string string::substr(strsize iFirst) const
//{
//   return Mid(iFirst);
//}
//
//// Return the substring starting at strsize 'iFirst', with length 'nCount'
//string string::Mid(strsize iFirst,strsize nCount) const
//{
//   // nCount is in XCHARs
//
//   // out-of-bounds requests return sensible things
//
//   strsize nLength = get_length();
//
//   if(iFirst < 0)
//      iFirst = 0;
//
//   if(nCount < 0)
//      nCount = nLength + nCount + 1;
//
//   if(nCount + iFirst > nLength)
//      nCount = nLength - iFirst;
//
//   if(nCount < 0)
//      return "";
//
//   if(iFirst + nCount > get_length())
//   {
//
//      nCount = get_length() - iFirst;
//
//   }
//
//   if(iFirst > get_length())
//   {
//      nCount = 0;
//   }
//
//   ASSERT((nCount == 0) || ((iFirst + nCount) <= get_length()));
//
//   // optimize case of returning entire string
//   if((iFirst == 0) && ((iFirst + nCount) == get_length()))
//   {
//      return *this;
//   }
//
//   return(string(m_psz + iFirst,nCount,GetManager()));
//}
//
//string string::substr(strsize iFirst,strsize nCount) const
//{
//   return Mid(iFirst,nCount);
//}
//
//void string::clear()
//{
//   Empty();
//}
//
//// Return the substring consisting of the rightmost 'nCount' characters
//string string::Right(strsize nCount) const
//{
//   // nCount is in XCHARs
//   if(nCount < 0)
//      nCount = 0;
//
//   strsize nLength = get_length();
//   if(nCount >= nLength)
//   {
//      return *this;
//   }
//
//   return(string(m_psz + nLength - nCount,nCount,GetManager()));
//}
//
//// Return the substring consisting of the leftmost 'nCount' characters
//string string::Left(strsize nCount) const
//{
//   // nCount is in XCHARs
//   if(nCount < 0)
//      nCount = 0;
//
//   strsize nLength = get_length();
//   if(nCount >= nLength)
//   {
//      return *this;
//   }
//
//   return(string(m_psz,nCount,GetManager()));
//}
//
//// Return the substring consisting of the leftmost characters in the set 'pszCharSet'
//string string::span_including(const scoped_string & strCharSet) const
//{
//   ASSERT(__is_valid_string(pszCharSet));
//   if(pszCharSet == nullptr)
//      throw ::exception(error_bad_argument);
//
//   return(Left(::str().string_span_including(m_psz,pszCharSet)));
//}
//
//// Return the substring consisting of the leftmost characters not in the set 'pszCharSet'
//string string::span_excluding(const scoped_string & strCharSet) const
//{
//   ASSERT(__is_valid_string(pszCharSet));
//   if(pszCharSet == nullptr)
//      throw ::exception(error_bad_argument);
//
//   return(Left(::str().string_span_excluding(m_psz,pszCharSet)));
//}
//
//void string::append_format_arguments(const scoped_string & strFormat,va_list args)
//{
//
//   ASSERT(__is_valid_string(pszFormat));
//
//   strsize nCurrentLength = get_length();
//
//   strsize nAppendLength = ::str().get_formatted_length( pszFormat, args );
//
//   char * pszBuffer = GetBuffer(nCurrentLength + nAppendLength);
//#if _SECURE_TEMPLATE
//   ::str().printf(pszBuffer + nCurrentLength,
//                         nAppendLength + 1,pszFormat,args);
//#else
//   ::str().printf(pszBuffer + nCurrentLength,pszFormat,args);
//#endif
//   release_string_buffer(nCurrentLength + nAppendLength);
//
//
//}
//
//void string::printf(const scoped_string & strFormat,va_list args)
//{
//
//   ASSERT(__is_valid_string(pszFormat));
//
//   if(pszFormat == nullptr)
//      throw ::exception(error_bad_argument);
//   va_list ptr;
//   va_copy(ptr, args);
//   strsize nLength = ::str().get_formatted_length(pszFormat,args);
//   char * pszBuffer = GetBuffer(nLength);
//#if _SECURE_TEMPLATE || defined(LINUX)
//   ::str().printf(pszBuffer,nLength + 1,pszFormat,ptr);
//#else
//   ::str().printf(pszBuffer,pszFormat,ptr);
//#endif
//   release_string_buffer(nLength);
//   va_end(ptr);
//}
//
//// Format a message using format string 'pszFormat' and va_list
//void string::FormatMessageV(const scoped_string & strFormat,va_list* pArgList)
//{
//
//#ifdef WINDOWS_DESKTOP
//
//   // format message into temporary buffer pszTemp
//
//   char * pszTemp;
//
//   u32 dwResult = ::str().format_message(FORMAT_MESSAGE_FROM_STRING | FORMAT_MESSAGE_ALLOCATE_BUFFER,pszFormat,0,0,reinterpret_cast<char *>(&pszTemp),0,pArgList);
//
//   if(dwResult == 0)
//   {
//
//      throw no_memory();
//
//   }
//
//   *this = pszTemp;
//
//   LocalFree(pszTemp);
//
//#else
//
//
//   printf(pszFormat,*pArgList);
//
//#endif
//
//}
//
//#ifdef WINDOWS
//
//// OLE BSTR support
//
//// allocate a BSTR containing a copy of the string
//BSTR string::AllocSysString() const
//{
//   BSTR bstrResult = ::str().AllocSysString(m_psz,get_length());
//   if(bstrResult == nullptr)
//   {
//      throw no_memory();
//   }
//   return(bstrResult);
//}
//
//BSTR string::SetSysString(BSTR* pbstr) const
//{
//   ASSERT(__is_valid_address(pbstr,sizeof(BSTR)));
//
//   if(!::str().ReAllocSysString(m_psz,pbstr,
//                                      get_length()))
//   {
//      throw no_memory();
//   }
//   ASSERT(*pbstr != nullptr);
//   return(*pbstr);
//}
//
//#endif
//
//// set the string to the value of environment ::payload 'pszVar'
//bool string::xxxget_environment_variable(const scoped_string & strVar)
//{
//
//   u32 nLength = ::str().xxxget_environment_variable(pszVar,nullptr,0);
//   bool bRetVal = false;
//
//   if(nLength == 0)
//   {
//      Empty();
//   }
//   else
//   {
//      char * pszBuffer = GetBuffer(nLength);
//      ::str().xxxget_environment_variable(pszVar,pszBuffer,nLength);
//      ReleaseBuffer();
//      bRetVal = true;
//   }
//
//   return(bRetVal);
//
//}
//
//bool string::xxxetenv(const scoped_string & strVar)
//{
//
//   return xxxget_environment_variable(pszVar);
//
//}
//
//
//// Load the string from resource 'nID'
////bool load_string(atom atom);
//
//// Load the string from resource 'nID' in module 'hInstance'
///*    bool load_string(HINSTANCE hInstance,::u32 nID )
//{
//const STRINGRESOURCEIMAGE* pImage = gen_GetStringResourceImage( hInstance, nID );
//if( pImage == nullptr )
//{
//return( false );
//}
//
//strsize nLength = ::str().get_char_length( pImage->achString, pImage->nLength );
//char * pszBuffer = GetBuffer( nLength );
//::str().ConvertTochar( pszBuffer, nLength, pImage->achString, pImage->nLength );
//release_string_buffer( nLength );
//
//return( true );
//}*/
//
//// Load the string from resource 'nID' in module 'hInstance', using language 'wLanguageID'
///*bool load_string(HINSTANCE hInstance,::u32 nID,::u16 wLanguageID )
//{
//const STRINGRESOURCEIMAGE* pImage = gen_GetStringResourceImage( hInstance, nID, wLanguageID );
//if( pImage == nullptr )
//{
//return( false );
//}
//
//strsize nLength = ::str().get_char_length( pImage->achString, pImage->nLength );
//char * pszBuffer = GetBuffer( nLength );
//::str().ConvertTochar( pszBuffer, nLength, pImage->achString, pImage->nLength );
//release_string_buffer( nLength );
//
//return( true );
//}*/
//
//
//#ifndef _CSTRING_BUFFER_SIZE
//#define _CSTRING_BUFFER_SIZE(_CStringObj) ((_CStringObj).GetAllocLength() + 1)
//#endif
//
////#if defined(VARIADIC_TEMPLATE_FORMAT)
////
////void __cdecl string::_Format(const scoped_string & strFormat, ...)
////{
////   ASSERT(__is_valid_string(pszFormat));
////
////   va_list argList;
////   va_start(argList, pszFormat);
////   printf(pszFormat, argList);
////   va_end(argList);
////}
////
////
////// append formatted data using format string 'pszFormat'
////void __cdecl string::_AppendFormat(const scoped_string & strFormat, ...)
////{
////   ASSERT(__is_valid_string(pszFormat));
////
////   va_list argList;
////   va_start(argList, pszFormat);
////
////   append_format_arguments(pszFormat, argList);
////
////   va_end(argList);
////}
////
////
////#elif !defined(VARIADIC_TEMPLATE_FORMAT2)
//
//
//void __cdecl string::Format(const scoped_string & strFormat,...)
//{
//   ASSERT(__is_valid_string(pszFormat));
//
//   va_list argList;
//   va_start(argList,pszFormat);
//   printf(pszFormat,argList);
//   va_end(argList);
//}
//
//
//// append formatted data using format string 'pszFormat'
//void __cdecl string::AppendFormat(const scoped_string & strFormat,...)
//{
//   ASSERT(__is_valid_string(pszFormat));
//
//   va_list argList;
//   va_start(argList,pszFormat);
//
//   append_format_arguments(pszFormat,argList);
//
//   va_end(argList);
//}
//
//// Format a message using format string 'pszFormat'
//void __cdecl string::format_message(const scoped_string & strFormat,...)
//{
//   if(pszFormat == nullptr)
//      throw ::exception(error_bad_argument);
//
//   va_list argList;
//   va_start(argList,pszFormat);
//
//   FormatMessageV(pszFormat,&argList);
//
//   va_end(argList);
//}
//
////#endif
//
//bool string::load_string(::particle * pparticle,atom atom)
//{
//   return App(pparticle).load_string(*this,atom);
//}
//
//
//void string::reserve(strsize res_arg)
//{
//   get_string_buffer(res_arg + 1);
//}
//
//
//
//// Convert the string to uppercase
//string string::uppered() const
//{
//
//   return string(*this).make_upper();
//
//}
//
//// Convert the string to lowercase
//string string::lowered() const
//{
//
//   return string(*this).make_lower();
//
//}
//
//// Convert the string to lowercase
//string string::reversed() const
//{
//
//   return string(*this).MakeReverse();
//
//}
//
//
//string string::unichar_substr(strsize iFirst) const
//{
//
//   return unichar_substr(iFirst,-1);
//
//}
//
//string string::unichar_substr(strsize iFirst,strsize nCount) const
//{
//
//   const char * pchStart = *this;
//
//   if(pchStart == nullptr)
//      return "";
//
//   ::count iUnicharLength = unichar_length();
//
//   if(iFirst < 0)
//      iFirst = iUnicharLength + iFirst;
//
//   if(nCount < 0)
//      nCount = iUnicharLength - iFirst + nCount + 1;
//
//   if(iFirst + nCount > iUnicharLength)
//      nCount = iUnicharLength - iFirst;
//
//   if(nCount <= 0)
//      return "";
//
//   ::count cCount = 0;
//
//   while(cCount < iFirst && *pchStart != '\0')
//   {
//
//      unicode_increment(pchStart);
//
//      ca++;
//
//   }
//
//   if(*pchStart == '\0')
//      return "";
//
//   const char * pchEnd = pchStart;
//
//   ca = 0;
//
//   while(ca < nCount && *pchEnd != '\0')
//   {
//
//      pchEnd = ::str().__utf8_inc(pchEnd);
//
//      ca++;
//
//   }
//
//   return string(pchStart,pchEnd - pchStart);
//
//
//}
//
//::count string::utf8_get_length() const
//{
//
//   const char * pch = *this;
//
//   if(pch == nullptr)
//      return 0;
//
//   ::count cCharCount = 0;
//
//   while(pch != nullptr && *pch != '\0')
//   {
//
//      pch = ::str().__utf8_inc(pch);
//
//      cCharCount++;
//
//   }
//
//   return cCharCount;
//
//}
//
//
//strsize string::char_get_count(strsize iCharCount) const
//{
//
//   strsize iFinalLen = 0;
//
//   auto psz = operator const char*();
//
//   strsize cMaxLen = get_length();
//
//   while(iCharCount > 0)
//   {
//
//      strsize iLen = unicode_uni_len(psz);
//
//      psz += iLen;
//
//      iFinalLen += iLen;
//
//      if(iFinalLen >= cMaxLen)
//      {
//
//         return cMaxLen;
//
//      }
//
//      iCharCount--;
//
//   }
//
//   return iFinalLen;
//
//}
//
//
//
//bool string::eat_before(string & strBefore, string strSeparator, bool bEatEverythingIfNotFound)
//{
//
//   return ::str().eat_before(strBefore, strSeparator, *this, bEatEverythingIfNotFound);
//
//}
//
//
//bool string::eat_before_let_separator(string & strBefore, string strSeparator, bool bEatEverythingIfNotFound)
//{
//
//   return ::str().eat_before_let_separator(strBefore, strSeparator, *this, bEatEverythingIfNotFound);
//
//}
//
//
//void string::push_back(char ch)
//{
//
//   operator += (ch);
//
//}
//
//
//string& string::operator = (const ::string_stream& str)
//{
//
//
//   return this->operator =(str.operator const string &());
//
//}
//
//string & string::operator = (const wstring & wstr)
//{
//
//   return this->operator =(unicode_to_utf8(wstr));
//
//}
//
//


CLASS_DECL_ACME::string string_format(const scoped_string & strFormat, ...)
{

   ::string str;

   va_list argList;

   va_start(argList, pszFormat);

   str.format_arguments(pszFormat, argList);

   va_end(argList);

   return str;

}



