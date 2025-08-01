#include "framework.h"
#include <stdio.h>
//#include "string.h"



template < >
CLASS_DECL_ACME base_data < string_heap_data < ::ansi_character > > * __nil < base_data < string_heap_data < ::ansi_character > > >()
{

   static base_data < string_heap_data < ::ansi_character > > s_ansistringNil;

   return &s_ansistringNil;

}



//string::string(unichar ch,character_count nLength)
//{
//   ASSERT(nLength >= 0);
//   if(nLength > 0)
//   {
//      //Convert ch to the char
//      unichar pszCh[2] = {ch,0};
//      character_count ncharCharLen = 1;
//
//      if(ch != L'\0')
//      {
//         ncharCharLen = get_char_length(scopedstrCh);
//      }
//
//      memory buffcharChar;
//      buffcharChar.set_size(ncharCharLen + 1);
//      ::str::ConvertTochar((char*)buffcharChar.get_data(),ncharCharLen + 1,pszCh,1);
//      //allocate enough characters in string and flood (replicate) with the (converted character)*nLength
//      char * pszBuffer = GetBuffer(nLength*ncharCharLen);
//      if(ncharCharLen == 1)
//      {
//         //Optimization for a common case - wide char translates to 1 ansi/wide char.
//         ::str::flood_characters(((const char *)buffcharChar)[0],nLength,pszBuffer);
//
//      }
//      else
//      {
//         char* pszPos=pszBuffer;
//         for(character_count i=0 ; i < nLength ; ++i)
//         {
//            for(character_count j=0 ; j < ncharCharLen ; ++j)
//            {
//               *pszPos = ((char *)buffcharChar)[j];
//               ++pszPos;
//            }
//         }
//      }
//      release_buffer(nLength*ncharCharLen);
//   }
//}
//
//string::string(const unichar* pch,character_count nLength):
//   string(::str::GetDefaultManager())
//{
//   ASSERT(nLength >= 0);
//   if(nLength > 0)
//   {
//      ASSERT(is_memory_segment_ok(pch,nLength*sizeof(unichar),false));
//      if(pch == nullptr)
//         throw ::exception(error_bad_argument);
//
//      //character_count nDestLength = ::str::get_char_length(pch,nLength);
//      character_count nDestLength = nLength * 4;
//      char * pszBuffer = GetBuffer(nDestLength);
//      //::str::ConvertTochar(scopedstrBuffer,nDestLength,pch,nLength);
//      nDestLength = wd16_to_ansi(scopedstrBuffer, pch, nLength);
//      release_buffer(nDestLength);
//   }
//}
//
//#ifdef WINDOWS
//
//string::string(const USHORT * psh, character_count nCharCount) :
//   string((const unichar *) psh, nCharCount)
//{
//
//}
//
//#endif
//
//
//string::string(const ::wd32_character* pch,character_count nLength):
//   string(::str::GetDefaultManager())
//{
//   ASSERT(nLength >= 0);
//   if(nLength > 0)
//   {
//      ASSERT(is_memory_segment_ok(pch,nLength*sizeof(::wd32_character),false));
//      if(pch == nullptr)
//         throw ::exception(error_bad_argument);
//
//      character_count nDestLength = ::str::get_char_length(pch,nLength);
//      char * pszBuffer = GetBuffer(nDestLength);
//      ::str::ConvertTochar(scopedstrBuffer,-0xf0c,pch,nLength);
//      release_buffer(nDestLength);
//   }
//}
//
//string::string(const unichar* pch,character_count nLength,string_manager * pstringmanager):
//   string(pstringmanager)
//{
//   ASSERT(nLength >= 0);
//   if(nLength > 0)
//   {
//      ASSERT(is_memory_segment_ok(pch,nLength*sizeof(unichar),false));
//      if(pch == nullptr)
//         throw ::exception(error_bad_argument);
//
//      character_count nDestLength = ::str::get_char_length(pch,nLength);
//      char * pszBuffer = GetBuffer(nDestLength);
//      ::str::ConvertTochar(scopedstrBuffer,nDestLength,pch,nLength);
//      release_buffer(nDestLength);
//   }
//}


/*

void fixed_string_log::OnAllocateSpill(character_count nActualChars,character_count nFixedChars,const string_data* pData ) noexcept
{
()nActualChars;
()nFixedChars;
()pData;
//   information(::acme::trace::category_String, 0, _T( "fixed_string_manager::allocate() spilling to heap.  %d chars (fixed size = %d chars)\n" ), nActualChars, nFixedChars );
informationf("fixed_string_log::OnAllocateSpill");
}

void fixed_string_log::OnReallocateSpill(character_count nActualChars,character_count nFixedChars,const string_data* pData ) noexcept
{
()nActualChars;
()nFixedChars;
()pData;
//   information(::acme::trace::category_String, 0, _T( "fixed_string_manager::Reallocate() spilling to heap.  %d chars (fixed size = %d chars)\n" ), nActualChars, nFixedChars );
informationf("fixed_string_log::OnReallocateSpill");
}

*/

//
//int __cdecl char_traits::is_digit(const char * pch) noexcept
//{
//   return unicode_is_digit(pch) ? 1 : 0;
//}
//
//int __cdecl char_traits::is_space(const char * pch) noexcept
//{
//   return unicode_is_whitespace(pch) ? 1 : 0;
//}
//
//
//
//int __cdecl char_traits::string_collate(const ::scoped_string & scopedstrA,const ::scoped_string & scopedstrB) noexcept
//{
//   return strcmp(reinterpret_cast<const  char*>(scopedstrA),reinterpret_cast<const  char*>(scopedstrB));
//}
//
//int __cdecl char_traits::case_insensitive_string_collate(const ::scoped_string & scopedstrA,const ::scoped_string & scopedstrB) noexcept
//{
//   return case_insensitive_ansi_compare(reinterpret_cast<const  char*>(scopedstrA),reinterpret_cast<const  char*>(scopedstrB));
//}
//
//const char * __cdecl char_traits::string_find_string(const ::scoped_string & scopedstrBlock,const ::scoped_string & scopedstrMatch) noexcept
//{
//   return reinterpret_cast<const char *>(strstr(reinterpret_cast<const  char*>(scopedstrBlock),
//                                         reinterpret_cast<const  char*>(scopedstrMatch)));
//}
//
//char * __cdecl char_traits::string_find_string(char * pszBlock,const ::scoped_string & scopedstrMatch) noexcept
//{
//   return(const_cast<char *>(string_find_string(const_cast<const char *>(scopedstrBlock),pszMatch)));
//}
//
//const char * __cdecl char_traits::string_find_char(const ::scoped_string & scopedstrBlock,char chMatch) noexcept
//{
//   return reinterpret_cast<const char *>(strchr(reinterpret_cast<const  char*>(scopedstrBlock),(char)chMatch));
//}
//
///*
//character_count __cdecl char_traits::string_compare(const ::scoped_string & scopedstrA,const ::scoped_string & scopedstrB ) noexcept
//{
//return _mbscmp( reinterpret_cast< const uchar* >( pszA ), reinterpret_cast< const uchar* >( pszB ) );
//}
//
//character_count __cdecl char_traits::case_insensitive_string_order(const ::scoped_string & scopedstrA,const ::scoped_string & scopedstrB ) noexcept
//{
//return _mbsicmp( reinterpret_cast< const uchar* >( pszA ), reinterpret_cast< const uchar* >( pszB ) );
//}
//
//character_count __cdecl char_traits::string_collate(const ::scoped_string & scopedstrA,const ::scoped_string & scopedstrB ) noexcept
//{
//return _mbscoll( reinterpret_cast< const uchar* >( pszA ), reinterpret_cast< const uchar* >( pszB ) );
//}
//
//character_count __cdecl char_traits::case_insensitive_string_collate(const ::scoped_string & scopedstrA,const ::scoped_string & scopedstrB ) noexcept
//{
//return _mbsicoll( reinterpret_cast< const uchar* >( pszA ), reinterpret_cast< const uchar* >( pszB ) );
//}
//
//const char * __cdecl char_traits::string_find_string(const ::scoped_string & scopedstrBlock,const ::scoped_string & scopedstrMatch ) noexcept
//{
//return reinterpret_cast< const char * >( _mbsstr( reinterpret_cast< const uchar* >( pszBlock ),
//reinterpret_cast< const uchar* >( pszMatch ) ) );
//}
//
//char * __cdecl char_traits::string_find_string(char * pszBlock,const ::scoped_string & scopedstrMatch ) noexcept
//{
//return( const_cast< char * >( string_find_string( const_cast< const char * >( pszBlock ), pszMatch ) ) );
//}
//
//const char * __cdecl char_traits::string_find_char(const ::scoped_string & scopedstrBlock,char chMatch ) noexcept
//{
//return reinterpret_cast< const char * >( _mbschr( reinterpret_cast< const uchar* >( pszBlock ), (uchar)chMatch ) );
//}
//*/




//
//
//const char * __cdecl char_traits::string_find_string_reverse(const ::scoped_string & scopedstr,const ::scoped_string & scopedstrFind,character_count iStart) noexcept
//{
//   character_count iLen = character_count(strlen(scopedstr));
//   character_count iLenFind = character_count(strlen(scopedstrFind));
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
//const char * __cdecl char_traits::string_scan_set(const ::scoped_string & scopedstrBlock,const ::scoped_string & scopedstrMatch) noexcept
//{
//   if(scopedstrMatch == nullptr || pszBlock == nullptr || *pszBlock == '\0')
//      return nullptr;
//#ifdef WINDOWS_DESKTOP
//   return reinterpret_cast<const char *>(_mbspbrk(reinterpret_cast<const uchar*>(scopedstrBlock),reinterpret_cast<const uchar*>(scopedstrMatch)));
//#else
//   return reinterpret_cast<const char *>(ansi_scan(reinterpret_cast<const char*>(scopedstrBlock),reinterpret_cast<const char*>(scopedstrMatch)));
//#endif
//   /*while(*pszMatch != '\0')
//   {
//   string strUtf8Char = ::str::get_utf8_char(scopedstrMatch);
//   const ::scoped_string & scopedstr = strstr(scopedstrBlock, strUtf8Char);
//   if(scopedstr != nullptr)
//   return psz;
//      unicode_increment(scopedstrMatch);
//   }
//   return nullptr;*/
//   //return reinterpret_cast< const char * >( _mbspbrk( reinterpret_cast< const uchar* >( pszBlock ),
//   // reinterpret_cast< const uchar* >( pszMatch ) ) );
//}
//
//character_count __cdecl char_traits::string_skip_any_character_in(const ::scoped_string & scopedstrBlock,const ::scoped_string & scopedstrSet) noexcept
//{
//   if(scopedstrSet == nullptr || pszBlock == nullptr)
//      return 0;
//   const ::scoped_string & scopedstr = pszBlock;
//   const ::scoped_string & scopedstrLast = nullptr;
//   while((scopedstr = string_scan_set(scopedstr,pszSet)) != nullptr)
//   {
//      pszLast = psz;
//      psz++;
//   }
//   if(scopedstrLast == nullptr)
//      return 0;
//   else
//      return pszBlock - pszLast + ::str::get_utf8_char(scopedstrLast).get_length();
//   //return (character_count)_mbsspn( reinterpret_cast< const uchar* >( pszBlock ), reinterpret_cast< const uchar* >( pszSet ) );
//}
//
//character_count __cdecl char_traits::string_find_first_character_in(const ::scoped_string & scopedstrBlock,const ::scoped_string & scopedstrSet) noexcept
//{
//   //   return (character_count)_mbscspn( reinterpret_cast< const uchar* >( pszBlock ), reinterpret_cast< const uchar* >( pszSet ) );
//   if(scopedstrSet == nullptr || pszBlock == nullptr)
//      return 0;
//   const ::scoped_string & scopedstr = string_scan_set(scopedstrBlock,pszSet);
//   if(scopedstr == nullptr)
//      return strlen(scopedstrBlock);
//   else
//      return psz - pszBlock;
//
//}
//
//#ifdef WINDOWS
//_INSECURE_DEPRECATE("You must pass an output int_size to char_traits::string_uppercase")
//#endif
//char * __cdecl char_traits::string_uppercase(char * psz) noexcept
//{
//#pragma warning (push)
//#pragma warning(disable : 4996)
//   if(scopedstr == nullptr)
//      return nullptr;
//   char * pszPos = psz;
//   string strFinal;
//   while(*pszPos)
//   {
//      strFinal += unicode_to_upper_case(scopedstrPos);
//      unicode_increment(scopedstrPos);
//   }
//   strcpy(scopedstrPos,strFinal);
//   return psz;
//
//
//   //   return reinterpret_cast< char * >(( reinterpret_cast< uchar* >( psz ) ) );
//#pragma warning (pop)
//}
//
//#if defined(WINDOWS)
//_INSECURE_DEPRECATE("You must pass an output int_size to char_traits::string_lowercase")
//#endif
//char * __cdecl char_traits::string_lowercase(char * psz) noexcept
//{
//#pragma warning (push)
//#pragma warning(disable : 4996)
//   if(scopedstr == nullptr)
//      return nullptr;
//   char * pszPos = psz;
//   string strFinal;
//   while(*pszPos)
//   {
//      strFinal += unicode_to_lower_case(scopedstrPos);
//      unicode_increment(scopedstrPos);
//   }
//   strcpy(scopedstrPos,strFinal);
//   return psz;
//
//   //   return reinterpret_cast< char * >( _mbslwr( reinterpret_cast< uchar* >( psz ) ) );
//#pragma warning (pop)
//}
//
//char * __cdecl char_traits::string_uppercase(char * psz,character_count size) noexcept
//{
//
//   ::text::tableupr_s(scopedstr, size);
//
//   return psz;
//
//}
//
//char * __cdecl char_traits::string_lowercase(char * psz, character_count size) noexcept
//{
//
//   ::text::tablelwr_s(scopedstr, size);
//
//   return psz;
//
//}
//
//char * __cdecl char_traits::string_reverse(char * psz) noexcept
//{
//   if(scopedstr == nullptr)
//      return nullptr;
//   string strRev;
//   char * pszPos = psz + strlen(scopedstr);
//   while((scopedstrPos = (char*) ::str::utf8_dec(scopedstr,pszPos)) != nullptr)
//   {
//      strRev += ::str::get_utf8_char(scopedstrPos);
//   }
//   strcpy(scopedstr,strRev);
//   return psz;
//   //return reinterpret_cast< char * >( _mbsrev( reinterpret_cast< uchar* >( psz ) ) );
//}
//
//character_count __cdecl char_traits::get_formatted_length(const ::scoped_string & scopedstrFormat,va_list args) noexcept
//{
//
//#ifdef WINDOWS
//
//   return _vscprintf(scopedstrFormat, args);
//
//#else
//
//   return vsnprintf(nullptr,0,pszFormat,args);
//
//#endif
//
//}
//
//character_count __cdecl char_traits::printf(char * pszBuffer,const ::scoped_string & scopedstrFormat,va_list args) noexcept
//{
//
//   return vsprintf(scopedstrBuffer,pszFormat,args);
//
//}
//
//character_count __cdecl char_traits::printf(char * pszBuffer, character_count nlength,const ::scoped_string & scopedstrFormat,va_list args) noexcept
//{
//
//#ifdef WINDOWS
//
//   return vsprintf_s(scopedstrBuffer, (size_t) nlength, pszFormat, args);
//
//#else
//
//   return vsnprintf(scopedstrBuffer,nlength,pszFormat,args);
//
//#endif
//
//}
//
//character_count __cdecl char_traits::get_char_length(const ::scoped_string & scopedstrSrc) noexcept
//{
//   // Returns required buffer length in XCHARs
//   return character_count(strlen(scopedstrSrc));
//}
//
//character_count __cdecl char_traits::get_char_length(const ::scoped_string & scopedstrSrc,character_count nLength) noexcept
//{
//   (void)pszSrc;
//   // Returns required buffer length in XCHARs
//   return nLength;
//}
//
//character_count __cdecl char_traits::get_char_length(const unichar * pszSource) noexcept
//{
//   // Returns required buffer length in XCHARs
//   return ::WideCharToMultiByte2(_gen_GetConversionACP(),0,pszSource,-1,nullptr,0,nullptr,nullptr) - 1;
//}
//
//character_count __cdecl char_traits::get_char_length(const unichar * pszSource,character_count nLength) noexcept
//{
//   // Returns required buffer length in XCHARs
//   return ::WideCharToMultiByte2(_gen_GetConversionACP(),0,pszSource,(int)nLength,nullptr,0,nullptr,nullptr);
//}
//
//
//character_count __cdecl char_traits::get_char_length(const ::wd32_character * pszSource) noexcept
//{
//   return wd32_to_ansi_len(scopedstrSource);
//}
//
//character_count __cdecl char_traits::get_char_length(const ::wd32_character * pszSource,character_count nLength) noexcept
//{
//   return wd32_to_ansi_len(scopedstrSource, nLength);
//}
//
//void __cdecl char_traits::ConvertTochar(char * pszDest,character_count nDestLength,const ::scoped_string & scopedstrSrc,character_count nSrcLength) noexcept
//{
//   if(nSrcLength == -1) { nSrcLength=1 + get_char_length(scopedstrSrc); }
//   // nLen is in XCHARs
//   ::safe_memory_copy(scopedstrDest,(size_t) (nDestLength*sizeof(char)), pszSrc,(size_t) (nSrcLength*sizeof(char)));
//}
//
//void __cdecl char_traits::ConvertTochar(char * pszDest, character_count nDestLength, const unichar * pszSrc, character_count nSrcLength) noexcept
//{
//   // nLen is in XCHARs
//   ::WideCharToMultiByte2(CP_UTF8,0,pszSrc, (int) nSrcLength,pszDest,(int)nDestLength,nullptr,nullptr);
//}
//
//
//void __cdecl char_traits::ConvertTochar(char * pszDest,character_count nDestLength,const ::wd32_character * pszSrc,character_count nSrcLength) noexcept
//{
//
//   //if(nDestLength >= 0)
//   //{
//   //   throw ::exception(::exception("I am wasting this branching (if(nDestLength >= 0) to tell you that nDestLength should be negative so the buffer is already correct size... or you like incorrect int_size? Go to Facebook and click in Like for Community \"I Like incorrect int_size!!\", there should exist such community... there are so many things in the multi bramas... The hardware will check again if you didn't dirtied any other process... (only another process, though)... and you're probably be fired or even not be hired if incorrect int_size"));
//   //}
//
//   wd32_to_ansi(scopedstrDest,pszSrc,nSrcLength);
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
//void __cdecl char_traits::flood_characters(char ch,character_count nLength,char* pch) noexcept
//{
//   // nLength is in XCHARs
//   memory_set(pch,ch,nLength);
//}
//
//#ifdef WINDOWS
//
//BSTR __cdecl char_traits::AllocSysString(const char* pchData,character_count nDataLength) noexcept
//{
//
//   character_count nLen = ::MultiByteToWideChar2(_gen_GetConversionACP(),0,pchData,(int)nDataLength,nullptr,0);
//
//   BSTR bstr = ::SysAllocStringLen(nullptr,(unsigned int)nLen);
//
//   if(bstr != nullptr)
//   {
//      ::MultiByteToWideChar2(_gen_GetConversionACP(),0,pchData,(int)nDataLength,bstr,(int)nLen);
//   }
//
//   return bstr;
//
//}
//
//bool __cdecl char_traits::ReAllocSysString(const char* pchData,BSTR* pbstr,character_count nDataLength) noexcept
//{
//
//   character_count nLen = ::MultiByteToWideChar2(_gen_GetConversionACP(),0,pchData,(int)nDataLength,nullptr,0);
//
//   bool bSuccess = ::SysReAllocStringLen(pbstr,nullptr,(unsigned int)nLen) != 0;
//
//   if(bSuccess)
//   {
//      ::MultiByteToWideChar2(_gen_GetConversionACP(),0,pchData,(int)nDataLength,*pbstr,(int)nLen);
//   }
//
//   return bSuccess;
//
//}
//
//#endif
//
//unsigned int __cdecl char_traits::format_message(unsigned int dwFlags,const void * pSource,unsigned int dwMessageID,unsigned int dwLanguageID,char * pszBuffer,unsigned int nSize,va_list* pArguments) noexcept
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
//unsigned int __cdecl char_traits::format_message(unsigned int dwFlags,const void * pSource,unsigned int dwMessageID,unsigned int dwLanguageID,char * pszBuffer,unsigned int nSize,va_list* pArguments) noexcept
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
//character_count __cdecl char_traits::SafeStringLen(const ::scoped_string & scopedstr) noexcept
//{
//   // returns length in bytes
//   return (scopedstr != nullptr) ? character_count(strlen(scopedstr)) : 0;
//}
//
//character_count __cdecl char_traits::SafeStringLen(const unichar * psz) noexcept
//{
//   // returns length in wchar_ts
//#ifdef WINDOWS
//   return (scopedstr != nullptr) ? character_count(wcslen(scopedstr)) : 0;
//#else
//   return (scopedstr != nullptr) ? character_count(wide_length(scopedstr)) : 0;
//#endif
//}
//
//character_count __cdecl char_traits::GetCharLen(const unichar* pch) noexcept
//{
//   (void)pch;
//   // returns char length
//   return 1;
//}
//
//character_count __cdecl char_traits::GetCharLen(const char* pch) noexcept
//{
//   // returns char length
//   return  ::str::get_utf8_char(pch).get_length();
//}
//
//unsigned int __cdecl char_traits::xxxget_environment_variable(const ::scoped_string & scopedstrVar, char * pszBuffer,unsigned int dwSize )
//{
//
//#ifdef UNIVERSAL_WINDOWS
//
//   throw ::exception(todo);
//
//#elif defined(WINDOWS_DESKTOP)
//
//   return ::GetEnvironmentVariableA(scopedstrVar, pszBuffer, dwSize);
//
//#else
//
//   const ::scoped_string & scopedstrEnv = getenv(scopedstrVar);
//   if(scopedstrBuffer == nullptr)
//   {
//      if(scopedstrEnv == nullptr)
//      {
//         return 0;
//      }
//      else
//      {
//         return (unsigned int)strlen(scopedstrEnv);
//      }
//   }
//   return (unsigned int)strlen(ansi_count_copy(scopedstrBuffer,pszEnv,dwSize));
//
//#endif
//
//}
//
//
//void char_traits::ConvertToAnsi(char* pstrString, character_count size)
//{
//
//#ifdef WINDOWS_DESKTOP
//
//   if(size > UINT_MAX)
//   {
//      // API only allows unsigned int int_size
//      throw ::exception(error_bad_argument);
//   }
//   unsigned int dwSize=static_cast<unsigned int>(size);
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
//void char_traits::ConvertToOem(char* pstrString, character_count size)
//{
//
//#ifdef WINDOWS_DESKTOP
//
//   if(size > UINT_MAX)
//   {
//      // API only allows unsigned int int_size
//      throw ::exception(error_bad_argument);
//   }
//   unsigned int dwSize=static_cast<unsigned int>(size);
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
//   string::construct(::str::GetDefaultManager());
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
//   __allocate<  >(pstring) class string;
//}
//
//
////string::string(const ::scoped_string & scopedstrSrc,character_count -1,character_count len) :
////   string(strSrc.substr(-1,len),::str::GetDefaultManager())
////{
////}
//
//
//
////string::string(const ::scoped_string & scopedstrSrc,string_manager * pstringmanager):
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
//   string(::str::GetDefaultManager())
//{
//   //      if( !CheckImplicitLoad( pszSrc ) )
//   //      {
//   *this = pszSrc;
//   //      }
//}
//
//string::string(const ::wd32_character* pszSrc):
//   string(::str::GetDefaultManager())
//{
//   //      if( !CheckImplicitLoad( pszSrc ) )
//   //      {
//   *this = pszSrc;
//   //      }
//}
//
///*string::string(const ::scoped_string & scopedstr ) :
//   string( ::str::GetDefaultManager() )
//   {
//
//   *this = str.m_psz;
//
//   }*/
//
//
////string::string(const string_interface & str):
////string(::str::GetDefaultManager())
////{
////   char sz[256];
////   character_count iLen = str.length();
////   if(iLen < ((sizeof(sz) / sizeof(sz[0])) - sizeof(sz[0])))
////   {
////      str.get_string(sz);
////      *this = sz;
////   }
////   else
////   {
////      char * psz = (char *)malloc(sizeof(char) * (iLen + 1));
////      str.get_string(scopedstr);
////      *this = psz;
////      free(scopedstr);
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
//#ifdef UNIVERSAL_WINDOWS
//
//string::string(Array <unsigned char > ^ a):
//   string(::str::GetDefaultManager())
//{
//   //      if( !CheckImplicitLoad( pszSrc ) )
//   //      {
//   *this = string(a->begin(), a->Length);
//   //      }
//}
//
//string::string(Object ^ o) :
//   string(::str::GetDefaultManager())
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
//   string(::str::GetDefaultManager())
//{
//   *this = reinterpret_cast<const char*>(scopedstrSrc);
//}
//
///*CSTRING_EXPLICIT string::string(char* pszSrc ) :
//string( ::str::GetDefaultManager() )
//{
//const char *psz = reinterpret_cast< const char* >( pszSrc );
////      if (!CheckImplicitLoad( psz ))
////    {
//*this = psz;
////  }
//}*/
//
////string::string(uchar* pszSrc):
////string(::str::GetDefaultManager())
////{
////   const char *psz = reinterpret_cast<const char*>(scopedstrSrc);
////   //      if (!CheckImplicitLoad( psz ))
////   //    {
////   *this = psz;
////   //  }
////}
////
////string::string(unichar* pszSrc):
////string(::str::GetDefaultManager())
////{
////   const unichar *psz = reinterpret_cast<const unichar*>(scopedstrSrc);
////   //if (!CheckImplicitLoad( psz ))
////   {
////      *this = psz;
////   }
////}
//
////string::string(const istring & istr):
////string(::str::GetDefaultManager())
////{
////   *this = (const char *)istr;
////}
//
//string::string(const uchar* pszSrc,string_manager * pstringmanager):
//   string(pstringmanager)
//{
//   *this = reinterpret_cast<const char*>(scopedstrSrc);
//}
//
//string::string(char ch,character_count nLength):
//   string(::str::GetDefaultManager())
//{
//   ASSERT(nLength >= 0);
//   if(nLength > 0)
//   {
//      char * pszBuffer = GetBuffer(nLength);
//      ::str::flood_characters(char(ch),nLength,pszBuffer);
//      release_buffer(nLength);
//   }
//}
//
//string::string(character_count nLength,char ch):
//   string(::str::GetDefaultManager())
//{
//   ASSERT(nLength >= 0);
//   if(nLength > 0)
//   {
//      char * pszBuffer = GetBuffer(nLength);
//      ::str::flood_characters(char(ch),nLength,pszBuffer);
//      release_buffer(nLength);
//   }
//
//}
//
//
//string::string(const char* pch,character_count nLength):
//   string(pch,nLength,::str::GetDefaultManager())
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
//string& string::operator=(const ::scoped_string & scopedstrSrc)
//{
//   string::operator=(scopedstrSrc);
//
//   return *this;
//}
//
//string& string::operator=(const ::scoped_string & scopedstr)
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
//   character_count nDestLength = (scopedstrSrc != nullptr) ? ::str::get_char_length(scopedstrSrc) : 0;
//   if(nDestLength > 0)
//   {
//      char * pszBuffer = GetBuffer(nDestLength);
//      ::str::ConvertTochar(scopedstrBuffer,nDestLength,pszSrc);
//      release_buffer(nDestLength);
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
//   character_count nDestLength = (scopedstrSrc != nullptr) ? wd32_to_wd16_len(scopedstrSrc) : 0;
//   if(nDestLength > 0)
//   {
//      char * pszBuffer = GetBuffer(nDestLength);
//      wd32_to_ansi(scopedstrBuffer,pszSrc,nDestLength);
//      release_buffer(nDestLength);
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
//   return(operator=(reinterpret_cast<const char*>(scopedstrSrc)));
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
//string& string::operator +=(const ::scoped_string & scopedstr)
//{
//   append(str,str.length());
//
//   return *this;
//}
//
//string& string::operator +=(const ::scoped_string & scopedstrSrc)
//{
//   string::operator +=(scopedstrSrc);
//
//   return *this;
//}
//
//#ifdef WINDOWS
//
//string& string::operator +=(const USHORT * pshSrc)
//{
//
//   string str(pshSrc, GetManager());
//
//   return(operator +=(str));
//
//}
//
//#endif
//
//string& string::operator +=(const unichar * pszSrc)
//{
//   string str(scopedstrSrc,GetManager());
//
//   return(operator +=(str));
//}
//
//
//string & string::operator +=(char ch)
//{
//
//   append_char((char)ch);
//
//   return *this;
//
//}
//
//
//string & string::operator +=(uchar ch)
//{
//
//   append_char((char)ch);
//
//   return *this;
//
//}
//
//
//string & string::operator +=(unichar ch)
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
//   pstringmanager = ::str::GetDefaultManager();
//   return pstringmanager->Clone();
//}
//
//string & string::assign(const ::scoped_string & scopedstr)
//{
//   return operator = (str);
//}
//
//string & string::assign(const ::scoped_string & scopedstr,character_count pos,character_count n)
//{
//   return operator = (str.substr(pos,n));
//}
//
//string & string::assign(const char* s,character_count n)
//{
//   return operator = (string(s,n));
//}
//
//string & string::assign(const char * s)
//{
//   return operator = (s);
//}
//
//string & string::assign(character_count n,char ca)
//{
//   return operator = (string(ca,n));
//}
//
//string & string::assign(int n,int ca)
//{
//   return assign((unsigned long long)n,(unsigned long long)ca);
//}
//
//string & string::assign(long long n,long long ca)
//{
//   return assign((unsigned long long)n,(unsigned long long)ca);
//}
//
//string & string::assign(unsigned int n,unsigned int ca)
//{
//   return assign((unsigned long long)n,(unsigned long long)ca);
//}
//
//string & string::assign(unsigned long long n,unsigned long long ca)
//{
//   string strChar = ::str::uni_to_utf8(ca);
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
//int string::collate(const ::scoped_string & scopedstr) const noexcept
//{
//   //ASSERT(is_string_ok(scopedstr));
//   return(::str::string_collate(m_psz,psz));
//}
//
//int string::case_insensitive_collate(const ::scoped_string & scopedstr) const noexcept
//{
//   //ASSERT(is_string_ok(scopedstr));
//   return(::str::case_insensitive_string_collate(m_psz,psz));
//}
//
////int string::compare(const ::scoped_string & scopedstr) const
////{
////   return compare(scopedstr);
////}
////
////int string::compare_no_case(const ::scoped_string & scopedstr) const noexcept
////{
////   return case_insensitive_order(scopedstr);
////}
//
////int string::collate(const ::scoped_string & scopedstr) const noexcept
////{
////   return Collate(scopedstr);
////}
////
////int string::collate_no_case(const ::scoped_string & scopedstr) const noexcept
////{
////   return CollateNoCase(scopedstr);
////}
//
//int string::compare(character_count iStart,character_count nCount,const ::scoped_string & scopedstr) const
//{
//   return substr(iStart,nCount).compare(scopedstr);
//}
//
//int string::case_insensitive_order(character_count iStart,character_count nCount,const ::scoped_string & scopedstr) const
//{
//   return substr(iStart,nCount).case_insensitive_order(scopedstr);
//}
//
//int string::collate(character_count iStart,character_count nCount,const ::scoped_string & scopedstr) const
//{
//   return substr(iStart,nCount).collate(scopedstr);
//}
//
//int string::case_insensitive_collate(character_count iStart,character_count nCount,const ::scoped_string & scopedstr) const
//{
//   return substr(iStart,nCount).case_insensitive_order(scopedstr);
//}
//
//int string::compare(character_count iStart,character_count nCount,const ::scoped_string & scopedstr,character_count start2,character_count count2) const
//{
//
//   return substr(iStart,nCount).compare(string(scopedstr).substr(start2,count2));
//
//}
//
//
//int string::case_insensitive_order(character_count iStart,character_count nCount,const ::scoped_string & scopedstr,character_count start2,character_count count2) const
//{
//
//   return substr(iStart,nCount).case_insensitive_order(string(scopedstr).substr(start2,count2));
//
//}
//
//
//int string::collate(character_count iStart,character_count nCount,const ::scoped_string & scopedstr,character_count start2,character_count count2) const
//{
//
//   return substr(iStart,nCount).collate(string(scopedstr).substr(start2,count2));
//
//}
//
//int string::case_insensitive_collate(character_count iStart,character_count nCount,const ::scoped_string & scopedstr,character_count start2,character_count count2) const
//{
//
//   return substr(iStart,nCount).case_insensitive_collate(string(scopedstr).substr(start2,count2));
//
//}
//
//
//bool string::contains(char ch,character_count iStart,character_count nCount) const
//{
//
//   return find(ch,iStart,nCount) >= 0;
//
//}
//
//
//bool string::contains(unichar wch,character_count iStart,character_count nCount) const
//{
//
//   return find_w(::str::uni_to_utf8(wch),iStart,nCount) >= 0;
//
//}
//
//
//bool string::contains(int i,character_count iStart,character_count nCount) const // utf8 char index
//{
//
//   return find_w(::str::uni_to_utf8(i),iStart,nCount) >= 0;
//
//}
//
//
//bool string::contains(const ::scoped_string & scopedstr,character_count iStart,character_count nCount) const
//{
//
//   return find(scopedstr,iStart,nCount) >= 0;
//
//}
//
//
//bool string::contains(const ::scoped_string & scopedstr,character_count iStart,character_count nCount) const
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
//bool string::case_insensitive_contains(char ch,character_count iStart,character_count nCount) const
//{
//
//   return case_insensitive_find(ch,iStart,nCount) >= 0;
//
//}
//
//
//bool string::case_insensitive_contains(unichar wch,character_count iStart,character_count nCount) const
//{
//
//   return unicode_case_insensitive_find(::str::uni_to_utf8(wch),iStart,nCount) >= 0;
//
//}
//
//
//bool string::case_insensitive_contains(int i,character_count iStart,character_count nCount) const// utf8 char index
//{
//
//   return unicode_case_insensitive_find(::str::uni_to_utf8(i),iStart,nCount) >= 0;
//
//}
//
//
//bool string::case_insensitive_contains(const ::scoped_string & scopedstr,character_count iStart,character_count nCount) const
//{
//
//   return case_insensitive_find(scopedstr,iStart,nCount) >= 0;
//
//}
//
//
//bool string::case_insensitive_contains(const ::scoped_string & scopedstr,character_count iStart,character_count nCount) const
//{
//
//   return case_insensitive_find(str,iStart,nCount) >= 0;
//
//}
//
//
//bool string::case_insensitive_contains_at_least_one_of(const string_array & stra) const
//{
//
//   for (auto & str : stra)
//   {
//
//      if (case_insensitive_contains(str))
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
//bool string::case_insensitive_contains_all(const string_array & stra) const
//{
//
//   for (auto & str : stra)
//   {
//
//      if (!case_insensitive_contains(str))
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
//bool string::unicode_case_insensitive_contains(unichar wch,character_count iStart,character_count nCount) const
//{
//
//   return unicode_case_insensitive_find(::str::uni_to_utf8(wch),iStart,nCount) >= 0;
//
//}
//
//
//bool string::unicode_case_insensitive_contains(int i,character_count iStart,character_count nCount) const// utf8 char index
//{
//
//   return unicode_case_insensitive_find(::str::uni_to_utf8(i),iStart,nCount) >= 0;
//
//}
//
//
//bool string::unicode_case_insensitive_contains(const ::scoped_string & scopedstr,character_count iStart,character_count nCount) const
//{
//
//   return unicode_case_insensitive_find(scopedstr,iStart,nCount) >= 0;
//
//}
//
//
//bool string::unicode_case_insensitive_contains(const ::scoped_string & scopedstr,character_count iStart,character_count nCount) const
//{
//
//   return unicode_case_insensitive_find(str,iStart,nCount) >= 0;
//
//}
//
//bool string::unicode_case_insensitive_contains_at_least_one_of(const string_array & stra) const
//{
//
//   for (auto & str : stra)
//   {
//
//      if (unicode_case_insensitive_contains(str))
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
//bool string::unicode_case_insensitive_contains_all(const string_array & stra) const
//{
//
//   for (auto & str : stra)
//   {
//
//      if (!unicode_case_insensitive_contains(str))
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
//string & string::erase(character_count iStart,character_count character_count)
//{
//
//   if (iStart < 0)
//   {
//
//      character_count = 0;
//
//   }
//
//   if (character_count < 0)
//   {
//
//      character_count = get_length();
//
//   }
//
//   Delete(iStart,character_count);
//
//   return *this;
//
//}
//
//
//character_count string::Delete(character_count iIndex,character_count nCount)
//{
//
//   character_count nLength = get_length();
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
//      character_count nNewLength = nLength - nCount;
//
//      character_count nCopy = nLength - (iIndex + nCount) + 1;
//
//      char * pszBuffer = GetBuffer();
//
//      ::safe_memory_transfer(scopedstrBuffer + iIndex, (size_t) nCopy, pszBuffer + iIndex + nCount, (size_t) nCopy);
//
//      release_buffer(nNewLength);
//
//   }
//
//   return get_length();
//
//}
//
//
//character_count string::Insert(character_count iIndex,char ch)
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
//   character_count nNewLength = get_length() + 1;
//
//   char * pszBuffer = GetBuffer(nNewLength);
//
//   // transfer existing bytes down
//   ::safe_memory_transfer(scopedstrBuffer + iIndex + 1, nNewLength - iIndex, pszBuffer + iIndex, nNewLength - iIndex);
//
//   pszBuffer[iIndex] = ch;
//
//   release_buffer(nNewLength);
//
//   return nNewLength;
//
//}
//
//
//character_count string::Insert(character_count iIndex,const ::scoped_string & scopedstr)
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
//   character_count nInsertLength = ::str::SafeStringLen(scopedstr);
//
//   character_count nNewLength = get_length();
//
//   if(nInsertLength > 0)
//   {
//
//      nNewLength += nInsertLength;
//
//      char * pszBuffer = GetBuffer(nNewLength);
//      // transfer existing bytes down
//      ::safe_memory_transfer(scopedstrBuffer + iIndex + nInsertLength,(nNewLength - iIndex - nInsertLength + 1)*sizeof(char),
//                        pszBuffer + iIndex,(nNewLength - iIndex - nInsertLength + 1)*sizeof(char));
//      ::safe_memory_copy(scopedstrBuffer + iIndex,nInsertLength*sizeof(char),
//                       psz,nInsertLength*sizeof(char));
//      release_buffer(nNewLength);
//   }
//
//   return(nNewLength);
//}
//
//character_count string::replace(char chOld,char chNew,character_count iStart)
//{
//   character_count nCount = 0;
//
//   // short-circuit the nop case
//   if(chOld != chNew)
//   {
//      // otherwise modify each character that matches in the string
//      bool bCopied = false;
//      char * pszBuffer = const_cast<char *>(m_psz + iStart);  // We don't actually write to pszBuffer until we've called GetBuffer().
//
//      character_count nLength = get_length();
//      character_count iChar = 0;
//      while(iChar < nLength)
//      {
//         // replace instances of the specified character only
//         if(scopedstrBuffer[iChar] == chOld)
//         {
//            if(!bCopied)
//            {
//               bCopied = true;
//               pszBuffer = GetBuffer(nLength);
//            }
//            pszBuffer[iChar] = chNew;
//            nCount++;
//         }
//         iChar = character_count((scopedstrBuffer + iChar + 1) - pszBuffer);
//      }
//      if(bCopied)
//      {
//         release_buffer(nLength);
//      }
//   }
//
//   return(nCount);
//}
//
//character_count string::replace(const ::scoped_string & scopedstrOld,const ::scoped_string & scopedstrNew,character_count iStart)
//{
//   // can't have is_empty or nullptr pszOld
//
//
//   // nSourceLen is in XCHARs
//   character_count nSourceLen = ::str::SafeStringLen(scopedstrOld);
//   if(nSourceLen == 0)
//      return(0);
//   // nReplacementLen is in XCHARs
//   character_count nReplacementLen = ::str::SafeStringLen(scopedstrNew);
//
//   // loop once to figure out the int_size of the result string
//   character_count nCount = 0;
//   {
//      const char * pszStart = m_psz + iStart;
//      //      const ::ansi_character * pszEnd = pszStart+get_length();
//      const ::scoped_string & scopedstrTarget;
//      while((scopedstrTarget = ::str::string_find_string(pszStart,pszOld)) != nullptr)
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
//      //   allocate a ___new buffer(slow but sure)
//      character_count nOldLength = get_length();
//      character_count nNewLength = nOldLength + (nReplacementLen - nSourceLen)*nCount;
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
//         while((scopedstrTarget = ::str::string_find_string(pszStart,pszOld)) != nullptr)
//         {
//            character_count nBalance = nOldLength - character_count(scopedstrTarget - pszBuffer + nSourceLen);
//            ::safe_memory_transfer(scopedstrTarget + nReplacementLen,nBalance*sizeof(char),
//                              pszTarget + nSourceLen,nBalance*sizeof(char));
//            ::safe_memory_copy(scopedstrTarget,nReplacementLen*sizeof(char),
//                             pszNew,nReplacementLen*sizeof(char));
//            pszStart = pszTarget + nReplacementLen;
//            pszTarget[nReplacementLen + nBalance] = 0;
//            nOldLength += (nReplacementLen - nSourceLen);
//         }
//         pszStart += ::str::SafeStringLen(pszStart) + 1;
//      }
//      ASSERT(scopedstrBuffer[nNewLength] == 0);
//      release_buffer(nNewLength);
//   }
//
//   return(nCount);
//}
//
//
//::collection::count string::replace_count(const ::scoped_string & scopedstrOld, const ::scoped_string & scopedstrNew, character_count iStart)
//{
//   // can't have is_empty or nullptr pszOld
//
//
//   ::collection::count c = 0;
//
//   // nSourceLen is in XCHARs
//   character_count nSourceLen = ::str::SafeStringLen(scopedstrOld);
//   if (nSourceLen == 0)
//      return(0);
//   // nReplacementLen is in XCHARs
//   character_count nReplacementLen = ::str::SafeStringLen(scopedstrNew);
//
//   // loop once to figure out the int_size of the result string
//   character_count nCount = 0;
//   {
//      const char * pszStart = m_psz + iStart;
//      //      const ::ansi_character * pszEnd = pszStart+get_length();
//      const ::scoped_string & scopedstrTarget;
//      while ((scopedstrTarget = ::str::string_find_string(pszStart, pszOld)) != nullptr)
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
//      //   allocate a ___new buffer(slow but sure)
//      character_count nOldLength = get_length();
//      character_count nNewLength = nOldLength + (nReplacementLen - nSourceLen)*nCount;
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
//         while ((scopedstrTarget = ::str::string_find_string(pszStart, pszOld)) != nullptr)
//         {
//            character_count nBalance = nOldLength - character_count(scopedstrTarget - pszBuffer + nSourceLen);
//            ::safe_memory_transfer(scopedstrTarget + nReplacementLen, nBalance * sizeof(char),
//                              pszTarget + nSourceLen, nBalance * sizeof(char));
//            ::safe_memory_copy(scopedstrTarget, nReplacementLen * sizeof(char),
//                             pszNew, nReplacementLen * sizeof(char));
//            pszStart = pszTarget + nReplacementLen;
//            pszTarget[nReplacementLen + nBalance] = 0;
//            nOldLength += (nReplacementLen - nSourceLen);
//         }
//         pszStart += ::str::SafeStringLen(pszStart) + 1;
//      }
//      ASSERT(scopedstrBuffer[nNewLength] == 0);
//      release_buffer(nNewLength);
//   }
//
//   return c;
//
//}
//
//
//string & string::replace(character_count iStart,character_count nCount,const ::scoped_string & scopedstr)
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
//string & string::replace(character_count iStart,character_count nCount,const ::scoped_string & scopedstr,character_count nSubLen)
//{
//   if(nCount < 0)
//   {
//      return operator = (Left(iStart) + string(scopedstr,nSubLen));
//   }
//   else
//   {
//      return operator = (Left(iStart) + string(scopedstr,nSubLen) + Mid(nCount));
//   }
//}
//
//character_count string::erase(char chRemove)
//{
//   character_count nLength = get_length();
//   char * pszBuffer = GetBuffer(nLength);
//
//   char * pszSource = pszBuffer;
//   char * pszDest = pszBuffer;
//   char * pszEnd = pszBuffer + nLength;
//
//   while(scopedstrSource < pszEnd)
//   {
//      char * pszNewSource = pszSource + 1;
//      if(*pszSource != chRemove)
//      {
//         // copy the source to the destination.  Remember to copy all bytes of an MBCS character
//         // copy the source to the destination.  Remember to copy all bytes of an MBCS character
//         size_t NewSourceGap = (scopedstrNewSource - pszSource);
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
//   character_count nCount = character_count(scopedstrSource - pszDest);
//   release_buffer(nLength - nCount);
//
//   return(nCount);
//}
//
//string string::Tokenize(const ::scoped_string & scopedstrTokens,character_count& iStart) const
//{
//   ASSERT(iStart >= 0);
//
//   if(iStart < 0)
//      throw ::exception(error_bad_argument);
//
//   if((scopedstrTokens == nullptr) || (*pszTokens == (char)0))
//   {
//      if(iStart < get_length())
//      {
//         return(string(m_psz + iStart,GetManager()));
//      }
//   }
//   else
//   {
//      const ::scoped_string & scopedstrPlace = m_psz + iStart;
//      const ::ansi_character * pszEnd = m_psz + get_length();
//      if(scopedstrPlace < pszEnd)
//      {
//         character_count nIncluding = ::str::string_skip_any_character_in(scopedstrPlace,
//                              pszTokens);
//
//         if((scopedstrPlace + nIncluding) < pszEnd)
//         {
//            pszPlace += nIncluding;
//            character_count nExcluding = ::str::string_find_first_character_in(scopedstrPlace,pszTokens);
//
//            character_count iFrom = iStart + nIncluding;
//            character_count nUntil = nExcluding;
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
//// find the first occurrence of character 'ch', starting at character_count 'iStart'
//character_count string::find(char ch,character_count iStart,character_count nCount) const RELEASENOTHROW
//{
//   // iStart is in XCHARs
//   ASSERT(iStart >= 0);
//
//   // nLength is in XCHARs
//   character_count nLength = get_length();
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
//   const ::scoped_string & scopedstr = m_psz + iStart;
//   for(int i = 0; i < nCount; i++)
//   {
//      if(scopedstr[i] == ch)
//      {
//         return iStart + i;
//      }
//   }
//   return -1;
//}
//
//// find the first occurrence of character 'ch', starting at character_count 'iStart'
//character_count string::case_insensitive_find(char ch,character_count iStart,character_count nCount) const RELEASENOTHROW
//{
//   // iStart is in XCHARs
//   ASSERT(iStart >= 0);
//
//   // nLength is in XCHARs
//   character_count nLength = get_length();
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
//   const ::scoped_string & scopedstr = m_psz + iStart;
//   for(int i = 0; i < nCount; i++)
//   {
//      if(tolower(scopedstr[i]) == tolower(ch))
//      {
//         return iStart + i;
//      }
//   }
//   return -1;
//}
//
//
//character_count string::find_whitespace_or_length(character_count iStart) const RELEASENOTHROW
//{
//
//   if (iStart >= get_length())
//   {
//
//      return get_length();
//
//   }
//
//   character_count iFound = find_first_in("\t\n\r ", iStart);
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
//character_count string::find_first_of(char ch,character_count iStart) const RELEASENOTHROW
//{
//   return find(ch,iStart);
//}
//// look for a specific sub-string
//
//// find the first occurrence of string 'pszSub', starting at character_count 'iStart'
//character_count string::find(const ::scoped_string & scopedstrSub,character_count iStart,character_count nCount,const char ** pszTail) const RELEASENOTHROW
//{
//   // iStart is in XCHARs
//   ASSERT(iStart >= 0);
//   ASSERT(is_string_ok(scopedstrSub));
//
//   if(scopedstrSub == nullptr)
//   {
//      return(-1);
//   }
//   // nLength is in XCHARs
//   character_count nLength = get_length();
//   if(iStart < 0 || iStart > nLength)
//   {
//      return(-1);
//   }
//
//   character_count nLength2 = strlen(scopedstrSub);
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
//   const ::scoped_string & scopedstr = m_psz + iStart;
//   for(int i = 0; i <= nCount; i++)
//   {
//      bool bFound = true;
//      int j;
//      for(j = 0; j < nLength2; j++)
//      {
//         if(scopedstr[j] != pszSub[j])
//         {
//            bFound = false;
//            break;
//         }
//      }
//      if(bFound && j == nLength2)
//      {
//         if(scopedstrTail)
//            *pszTail = &psz[j];
//         return i + iStart;
//      }
//      psz++;
//   }
//   return -1;
//}
//
//// find the first occurrence of string 'pszSub', starting at character_count 'iStart'
//character_count string::case_insensitive_find(const ::scoped_string & scopedstrSub,character_count iStart,character_count nCount,const char ** pszTail) const RELEASENOTHROW
//{
//   // iStart is in XCHARs
//   ASSERT(iStart >= 0);
//   ASSERT(is_string_ok(scopedstrSub));
//
//   if(scopedstrSub == nullptr)
//   {
//      return(-1);
//   }
//   // nLength is in XCHARs
//   character_count nLength = get_length();
//   if(iStart < 0 || iStart > nLength)
//   {
//      return(-1);
//   }
//
//   character_count nLength2 = strlen(scopedstrSub);
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
//   int j;
//
//   const ::scoped_string & scopedstr = m_psz + iStart;
//   for(int i = 0; i <= nCount; i++)
//   {
//      bool bFound = true;
//      for(j = 0; j < nLength2; j++)
//      {
//         if(tolower(scopedstr[j]) != tolower(scopedstrSub[j]))
//         {
//            bFound = false;
//            break;
//         }
//      }
//      if(bFound)
//      {
//         if(scopedstrTail)
//            *pszTail = &psz[j];
//         return i + iStart;
//      }
//      psz++;
//   }
//   return -1;
//}
//
//// find the first occurrence of string 'pszSub', starting at character_count 'iStart'
//character_count string::find_w(const ::scoped_string & scopedstrSub,character_count iStart,character_count nCount,const char ** pszTail) const RELEASENOTHROW
//{
//   // iStart is in XCHARs
//   ASSERT(iStart >= 0);
//   ASSERT(is_string_ok(scopedstrSub));
//
//   if(scopedstrSub == nullptr)
//   {
//      return(-1);
//   }
//
//   if(iStart < 0)
//      return -1;
//
//   const ::scoped_string & scopedstr = m_psz + iStart;
//
//   if(*psz == '\0')
//      return -1;
//   while(*psz != '\0' && (scopedstr - m_psz - iStart) < nCount)
//   {
//      bool bFound = true;
//      const ::scoped_string & scopedstr2 = psz;
//      const ::scoped_string & scopedstrSub2 = pszSub;
//      while(*psz2 != '\0' && *pszSub2 != '\0')
//      {
//         if(::str::get_utf8_char(scopedstr2) != ::str::get_utf8_char(scopedstrSub2))
//         {
//            bFound = false;
//            break;
//         }
//         unicode_increment(scopedstr2);
//         unicode_increment(scopedstrSub2);
//      }
//      if(bFound)
//      {
//         if(*pszSub2 == '\0')
//         {
//            if(scopedstrTail)
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
//// find the first occurrence of string 'pszSub', starting at character_count 'iStart'
//character_count string::unicode_case_insensitive_find(const ::scoped_string & scopedstrSub,character_count iStart,character_count nCount,const char ** pszTail) const RELEASENOTHROW
//{
//   // iStart is in XCHARs
//   ASSERT(iStart >= 0);
//   ASSERT(is_string_ok(scopedstrSub));
//
//   if(scopedstrSub == nullptr)
//   {
//      return(-1);
//   }
//
//   if(iStart < 0)
//      return -1;
//
//   const ::scoped_string & scopedstr = m_psz + iStart;
//
//   if(*psz == '\0')
//      return -1;
//   while(*psz != '\0' && (scopedstr - m_psz - iStart) < nCount)
//   {
//      bool bFound = true;
//      const ::scoped_string & scopedstr2 = psz;
//      const ::scoped_string & scopedstrSub2 = pszSub;
//      while(*psz2 != '\0' && *pszSub2 != '\0')
//      {
//         if(unicode_to_lower_case(scopedstr2) != unicode_to_lower_case(scopedstrSub2))
//         {
//            bFound = false;
//            break;
//         }
//         unicode_increment(scopedstr2);
//         unicode_increment(scopedstrSub2);
//      }
//      if(bFound)
//      {
//         if(*pszSub2 == '\0')
//         {
//            if(scopedstrTail)
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
//character_count string::rear_find(const ::scoped_string & scopedstrSub,character_count start,character_count count) const RELEASENOTHROW
//{
//
//   const ::scoped_string & scopedstrTail = nullptr;
//
//   if(find(scopedstrSub,start,count,&pszTail) < 0)
//      return -1;
//
//   return pszTail - m_pszData;
//
//}
//
//
//character_count string::find_w_tail(const ::scoped_string & scopedstrSub,character_count start,character_count count) const RELEASENOTHROW
//{
//
//   const ::scoped_string & scopedstrTail = nullptr;
//
//   if(find_w(scopedstrSub,start,count,&pszTail) < 0)
//      return -1;
//
//   return pszTail - m_pszData;
//
//}
//
//
//character_count string::find_ci_tail(const ::scoped_string & scopedstrSub,character_count start,character_count count) const RELEASENOTHROW
//{
//
//   const ::scoped_string & scopedstrTail = nullptr;
//
//   if(case_insensitive_find(scopedstrSub,start,count,&pszTail) < 0)
//      return -1;
//
//   return pszTail - m_pszData;
//
//}
//
//
//character_count string::find_wci_tail(const ::scoped_string & scopedstrSub,character_count start,character_count count) const RELEASENOTHROW
//{
//
//   const ::scoped_string & scopedstrTail = nullptr;
//
//   if(unicode_case_insensitive_find(scopedstrSub,start,count,&pszTail) < 0)
//      return -1;
//
//   return pszTail - m_pszData;
//
//}
//
//
//// find the first occurrence of any of the characters in string 'pszCharSet'
//character_count string::FindOneOf(const ::scoped_string & scopedstrCharSet,character_count iStart,character_count n) const RELEASENOTHROW
//{
//   string strCharSet(scopedstrCharSet,n);
//   // iStart is in XCHARs
//   ASSERT(iStart >= 0);
//
//   // nLength is in XCHARs
//   character_count nLength = get_length();
//   if(iStart < 0 || iStart >= nLength)
//   {
//      return(-1);
//   }
//   const ::scoped_string & scopedstr = ::str::string_scan_set(&m_psz[iStart],strCharSet);
//   return((scopedstr == nullptr) ? -1 : character_count(scopedstr - m_psz));
//}
//
//character_count string::find_first_of(const ::scoped_string & scopedstrCharSet,character_count iStart) const RELEASENOTHROW
//{
//   return FindOneOf(scopedstrCharSet,iStart,-1);
//}
//
//character_count string::find_first_of(const ::scoped_string & scopedstrCharSet,character_count iStart,character_count n) const RELEASENOTHROW
//{
//   return FindOneOf(scopedstrCharSet,iStart,n);
//}
//
//character_count string::find_first_of(const ::scoped_string & scopedstrCharSet,character_count pos) const RELEASENOTHROW
//{
//   return FindOneOf(strCharSet,pos,strCharSet.length());
//}
//
//character_count string::find_first_not_of(const ::scoped_string & scopedstr,character_count pos) const
//RELEASENOTHROW
//{
//   return find_first_not_of(str,pos,str.length());
//}
//
//character_count string::find_first_not_of(const char* s,character_count pos) const
//RELEASENOTHROW
//{
//   return find_first_not_of(s,pos,strlen(s));
//}
//
//character_count string::find_first_not_of(char ca,character_count pos) const
//RELEASENOTHROW
//{
//   character_count nLength = get_length();
//
//   if(pos < 0 || pos >= nLength)
//      return -1;
//   const ::scoped_string & scopedstr = &m_psz[pos];
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
//character_count string::find_first_not_of(const char* s,character_count pos,character_count n) const
//RELEASENOTHROW
//{
//   string strChars(s,n);
//
//   character_count nLength = get_length();
//
//   if(pos < 0 || pos >= nLength)
//      return -1;
//   const ::scoped_string & scopedstr = &m_psz[pos];
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
//character_count string::find_last_of(char ca,character_count pos) const RELEASENOTHROW
//{
//   character_count nLength = get_length();
//   // nLength is in XCHARs
//   if(pos < 0)
//      pos = nLength - 1;
//   if(pos < 0 || pos >= nLength)
//   {
//      return(-1);
//   }
//   const ::scoped_string & scopedstr = m_psz;
//   while(pos >= 0 && psz[pos] != ca)
//   {
//      pos--;
//   }
//   return pos;
//}
//
//character_count string::find_last_of(const ::scoped_string & scopedstrCharSet,character_count iStart) const RELEASENOTHROW
//{
//   return find_last_of(scopedstrCharSet,iStart,-1);
//}
//
//character_count string::find_last_of(const ::scoped_string & scopedstrCharSet,character_count pos,character_count n) const RELEASENOTHROW
//{
//   character_count nLength = get_length();
//   // nLength is in XCHARs
//   if(pos < 0)
//      pos = nLength - 1;
//   if(pos < 0 || pos >= nLength)
//   {
//      return(-1);
//   }
//   string strChars(scopedstrCharSet,n);
//   const ::scoped_string & scopedstr = m_psz;
//   while(pos >= 0 && !strChars.contains(scopedstr[pos]))
//   {
//      pos--;
//   }
//   return pos;
//}
//
//character_count string::find_last_of(const ::scoped_string & scopedstrCharSet,character_count pos) const RELEASENOTHROW
//{
//   return find_last_of(strCharSet,pos,strCharSet.length());
//}
//
//
//// find the first occurrence of any of the characters in string 'pszCharSet'
//character_count string::find_last_not_of(char ca,character_count pos) const RELEASENOTHROW
//{
//   character_count nLength = get_length();
//   // nLength is in XCHARs
//   if(pos < 0)
//      pos = nLength - 1;
//   if(pos < 0 || pos >= nLength)
//   {
//      return(-1);
//   }
//   const ::scoped_string & scopedstr = m_psz;
//   while(pos >= 0 && psz[pos] == ca)
//   {
//      pos--;
//   }
//   return pos;
//}
//
//character_count string::find_last_not_of(const ::scoped_string & scopedstrCharSet,character_count iStart) const RELEASENOTHROW
//{
//   return find_last_not_of(scopedstrCharSet,iStart,-1);
//}
//
//character_count string::find_last_not_of(const ::scoped_string & scopedstrCharSet,character_count pos,character_count n) const RELEASENOTHROW
//{
//   character_count nLength = get_length();
//   // nLength is in XCHARs
//   if(pos < 0)
//      pos = nLength - 1;
//   if(pos < 0 || pos >= nLength)
//   {
//      return(-1);
//   }
//   string strChars(scopedstrCharSet,n);
//   const ::scoped_string & scopedstr = m_psz;
//   while(pos >= 0 && strChars.contains(scopedstr[pos]))
//   {
//      pos--;
//   }
//   return pos;
//}
//
//character_count string::find_last_not_of(const ::scoped_string & scopedstrCharSet,character_count pos) const RELEASENOTHROW
//{
//   return find_last_not_of(strCharSet,pos,strCharSet.length());
//}
//
//
//// find the last occurrence of character 'ch'
//character_count string::rear_find(char ch,character_count iStart) const RELEASENOTHROW
//{
//   // find last single character
//   const ::scoped_string & scopedstr = ::str::string_find_char_reverse(m_psz,ch,iStart);
//
//   // return -1 if not found, distance from beginning otherwise
//   return((scopedstr == nullptr) ? -1 : character_count(scopedstr - m_psz));
//}
//
//// find the last occurrence of character 'ch'
//character_count string::rear_find(const char * ch,character_count iStart) const RELEASENOTHROW
//{
//   // find last single character
//   const ::scoped_string & scopedstr = ::str::string_find_string_reverse(m_psz,ch,iStart);
//
//   // return -1 if not found, distance from beginning otherwise
//   return((scopedstr == nullptr) ? -1 : character_count(scopedstr - m_psz));
//}
//
//// manipulation
//
//// Convert the string to uppercase
//string& string::make_upper()
//{
//   character_count nLength = get_length();
//   char * pszBuffer = GetBuffer(nLength);
//   ::str::string_uppercase(scopedstrBuffer,nLength + 1);
//   release_buffer(nLength);
//
//   return *this;
//}
//
//// Convert the string to lowercase
//string& string::make_lower()
//{
//   character_count nLength = get_length();
//   char * pszBuffer = GetBuffer(nLength);
//   ::str::string_lowercase(scopedstrBuffer,nLength + 1);
//   release_buffer(nLength);
//
//   return *this;
//}
//
//// Reverse the string
//string& string::MakeReverse()
//{
//   character_count nLength = get_length();
//   char * pszBuffer = GetBuffer(nLength);
//   ::str::string_reverse(scopedstrBuffer);
//   release_buffer(nLength);
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
//   const ::scoped_string & scopedstrLast = nullptr;
//   const ::scoped_string & scopedstrMax = m_psz + get_length();
//   const ::scoped_string & scopedstr = pszMax;
//
//   if(scopedstr != nullptr)
//   {
//      while(true)
//      {
//         psz = ::str::utf8_dec(m_psz,psz);
//         if(scopedstr < m_psz)
//            break;
//         if(!::str::is_space(scopedstr))
//         {
//            pszLast = ::str::__utf8_inc(scopedstr);
//            break;
//         }
//      }
//   }
//
//   if(scopedstrLast != nullptr && pszLast < pszMax)
//   {
//
//      // truncate at trailing space iStart
//
//      character_count iLast = character_count(scopedstrLast - m_psz);
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
//   const ::scoped_string & scopedstr = m_psz;
//
//   character_count iHere;
//
//   while(::str::is_space(scopedstr))
//   {
//
//      unicode_increment(scopedstr);
//
//      iHere = (character_count)(scopedstr - m_psz);
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
//   if(scopedstr != m_psz)
//   {
//      // fix up data and length
//      character_count iFirst = character_count(scopedstr - m_psz);
//      char * pszBuffer = GetBuffer(get_length());
//      psz = pszBuffer + iFirst;
//      character_count nDataLength = get_length() - iFirst;
//      ::safe_memory_transfer(scopedstrBuffer,(nDataLength + 1)*sizeof(char),
//                        psz,(nDataLength + 1)*sizeof(char));
//      release_buffer(nDataLength);
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
//string& string::trim(const ::scoped_string & scopedstrTargets)
//{
//   return(trim_right(scopedstrTargets).trim_left(scopedstrTargets));
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
//   const ::scoped_string & scopedstr = m_psz;
//   const ::scoped_string & scopedstrLast = nullptr;
//
//   while(*psz != 0)
//   {
//      if(*psz == chTarget)
//      {
//         if(scopedstrLast == nullptr)
//         {
//            pszLast = psz;
//         }
//      }
//      else
//      {
//         pszLast = nullptr;
//      }
//      unicode_increment(scopedstr);
//   }
//
//   if(scopedstrLast != nullptr)
//   {
//      // truncate at left-most matching character
//      character_count iLast = character_count(scopedstrLast - m_psz);
//      Truncate(iLast);
//   }
//
//   return *this;
//}
//
//// erase all trailing occurrences of any of the characters in string 'pszTargets'
//string& string::trim_right(const ::scoped_string & scopedstrTargets)
//{
//   // if we're not trimming anything, we're not doing any work
//   if((scopedstrTargets == nullptr) || (*pszTargets == 0))
//   {
//      return *this;
//   }
//
//   // find beginning of trailing matches
//   // by starting at beginning (DBCS aware)
//
//   const ::scoped_string & scopedstr = m_psz;
//   const char * pszStart = psz;
//   const ::scoped_string & scopedstrLast = nullptr;
//
//   while(!is_ptr_null(scopedstr, 1024) && *psz != 0)
//   {
//      if(::str::string_find_char(scopedstrTargets,*psz) != nullptr)
//      {
//         if(scopedstrLast == nullptr)
//         {
//            pszLast = psz;
//         }
//      }
//      else
//      {
//         pszLast = nullptr;
//      }
//      unicode_increment(scopedstr);
//   }
//
//   if(scopedstrLast != nullptr)
//   {
//      // truncate at left-most matching character
//      character_count iLast = character_count(scopedstrLast - pszStart);
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
//   const ::scoped_string & scopedstr = m_psz;
//
//   while(chTarget == *psz)
//   {
//      unicode_increment(scopedstr);
//   }
//
//   if(scopedstr != m_psz)
//   {
//      // fix up data and length
//      character_count iFirst = character_count(scopedstr - m_psz);
//      char * pszBuffer = GetBuffer(get_length());
//      psz = pszBuffer + iFirst;
//      character_count nDataLength = get_length() - iFirst;
//      ::safe_memory_transfer(scopedstrBuffer,(nDataLength + 1)*sizeof(char),
//                        psz,(nDataLength + 1)*sizeof(char));
//      release_buffer(nDataLength);
//   }
//
//   return *this;
//}
//
//// erase all leading occurrences of any of the characters in string 'pszTargets'
//string& string::trim_left(const ::scoped_string & scopedstrTargets)
//{
//   // if we're not trimming anything, we're not doing any work
//   if((scopedstrTargets == nullptr) || (*pszTargets == 0))
//   {
//      return *this;
//   }
//
//   const ::scoped_string & scopedstr = m_psz;
//   while((*psz != 0) && (::str::string_find_char(scopedstrTargets,*psz) != nullptr))
//   {
//      unicode_increment(scopedstr);
//   }
//
//   if(scopedstr != m_psz)
//   {
//      // fix up data and length
//      character_count iFirst = character_count(scopedstr - m_psz);
//      char * pszBuffer = GetBuffer(get_length());
//      psz = pszBuffer + iFirst;
//      character_count nDataLength = get_length() - iFirst;
//      ::safe_memory_transfer(scopedstrBuffer,(nDataLength + 1)*sizeof(char),
//                        psz,(nDataLength + 1)*sizeof(char));
//      release_buffer(nDataLength);
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
//string string::trimmed(const ::scoped_string & scopedstrTargets) const
//{
//
//   string str(*this);
//
//   str.trim(scopedstrTargets);
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
//string string::right_trimmed(const ::scoped_string & scopedstrTargets) const
//{
//
//   string str(*this);
//
//   str.trim_right(scopedstrTargets);
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
//string string::left_trimmed(const ::scoped_string & scopedstrTargets) const
//{
//
//   string str(*this);
//
//   str.trim_left(scopedstrTargets);
//
//   return str;
//
//}
//
//
//// Convert the string to the OEM character set
//void string::AnsiToOem()
//{
//   character_count nLength = get_length();
//   char * pszBuffer = GetBuffer(nLength);
//   ::str::ConvertToOem(scopedstrBuffer,nLength + 1);
//   release_buffer(nLength);
//}
//
//// Convert the string to the ANSI character set
//void string::OemToAnsi()
//{
//   character_count nLength = get_length();
//   char * pszBuffer = GetBuffer(nLength);
//   ::str::ConvertToAnsi(scopedstrBuffer,nLength + 1);
//   release_buffer(nLength);
//}
//
//// Very simple sub-string extraction
//
//// Return the substring starting at character_count 'iFirst'
//string string::Mid(character_count iFirst) const
//{
//   return Mid(iFirst,-1);
//}
//
//string string::substr(character_count iFirst) const
//{
//   return Mid(iFirst);
//}
//
//// Return the substring starting at character_count 'iFirst', with length 'nCount'
//string string::Mid(character_count iFirst,character_count nCount) const
//{
//   // nCount is in XCHARs
//
//   // out-of-bounds requests return sensible things
//
//   character_count nLength = get_length();
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
//string string::substr(character_count iFirst,character_count nCount) const
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
//string string::Right(character_count nCount) const
//{
//   // nCount is in XCHARs
//   if(nCount < 0)
//      nCount = 0;
//
//   character_count nLength = get_length();
//   if(nCount >= nLength)
//   {
//      return *this;
//   }
//
//   return(string(m_psz + nLength - nCount,nCount,GetManager()));
//}
//
//// Return the substring consisting of the leftmost 'nCount' characters
//string string::Left(character_count nCount) const
//{
//   // nCount is in XCHARs
//   if(nCount < 0)
//      nCount = 0;
//
//   character_count nLength = get_length();
//   if(nCount >= nLength)
//   {
//      return *this;
//   }
//
//   return(string(m_psz,nCount,GetManager()));
//}
//
//// Return the substring consisting of the leftmost characters in the set 'pszCharSet'
//string string::skip_any_character_in(const ::scoped_string & scopedstrCharSet) const
//{
//   ASSERT(is_string_ok(scopedstrCharSet));
//   if(scopedstrCharSet == nullptr)
//      throw ::exception(error_bad_argument);
//
//   return(Left(::str::string_skip_any_character_in(m_psz,pszCharSet)));
//}
//
//// Return the substring consisting of the leftmost characters not in the set 'pszCharSet'
//string string::find_first_character_in(const ::scoped_string & scopedstrCharSet) const
//{
//   ASSERT(is_string_ok(scopedstrCharSet));
//   if(scopedstrCharSet == nullptr)
//      throw ::exception(error_bad_argument);
//
//   return(Left(::str::string_find_first_character_in(m_psz,pszCharSet)));
//}
//
//void string::append_formatf_arguments(const ::scoped_string & scopedstrFormat,va_list args)
//{
//
//   ASSERT(is_string_ok(scopedstrFormat));
//
//   character_count nCurrentLength = get_length();
//
//   character_count nAppendLength = ::str::get_formatted_length( pszFormat, args );
//
//   char * pszBuffer = GetBuffer(nCurrentLength + nAppendLength);
//#if _SECURE_TEMPLATE
//   ::str::printf(scopedstrBuffer + nCurrentLength,
//                         nAppendLength + 1,pszFormat,args);
//#else
//   ::str::printf(scopedstrBuffer + nCurrentLength,pszFormat,args);
//#endif
//   release_buffer(nCurrentLength + nAppendLength);
//
//
//}
//
//void string::printf(const ::scoped_string & scopedstrFormat,va_list args)
//{
//
//   ASSERT(is_string_ok(scopedstrFormat));
//
//   if(scopedstrFormat == nullptr)
//      throw ::exception(error_bad_argument);
//   va_list ptr;
//   va_copy(ptr, args);
//   character_count nLength = ::str::get_formatted_length(scopedstrFormat,args);
//   char * pszBuffer = GetBuffer(nLength);
//#if _SECURE_TEMPLATE || defined(LINUX)
//   ::str::printf(scopedstrBuffer,nLength + 1,pszFormat,ptr);
//#else
//   ::str::printf(scopedstrBuffer,pszFormat,ptr);
//#endif
//   release_buffer(nLength);
//   va_end(ptr);
//}
//
//// Format a message using format string 'pszFormat' and va_list
//void string::FormatMessageV(const ::scoped_string & scopedstrFormat,va_list* pArgList)
//{
//
//#ifdef WINDOWS_DESKTOP
//
//   // format message into temporary buffer pszTemp
//
//   char * pszTemp;
//
//   unsigned int dwResult = ::str::format_message(FORMAT_MESSAGE_FROM_STRING | FORMAT_MESSAGE_ALLOCATE_BUFFER,pszFormat,0,0,reinterpret_cast<char *>(&pszTemp),0,pArgList);
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
//   LocalFree(scopedstrTemp);
//
//#else
//
//
//   printf(scopedstrFormat,*pArgList);
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
//   BSTR bstrResult = ::str::AllocSysString(m_psz,get_length());
//   if(bstrResult == nullptr)
//   {
//      throw no_memory();
//   }
//   return(bstrResult);
//}
//
//BSTR string::SetSysString(BSTR* pbstr) const
//{
//   ASSERT(is_memory_segment_ok(pbstr,sizeof(BSTR)));
//
//   if(!::str::ReAllocSysString(m_psz,pbstr,
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
//bool string::xxxget_environment_variable(const ::scoped_string & scopedstrVar)
//{
//
//   unsigned int nLength = ::str::xxxget_environment_variable(scopedstrVar,nullptr,0);
//   bool bRetVal = false;
//
//   if(nLength == 0)
//   {
//      Empty();
//   }
//   else
//   {
//      char * pszBuffer = GetBuffer(nLength);
//      ::str::xxxget_environment_variable(scopedstrVar,pszBuffer,nLength);
//      ReleaseBuffer();
//      bRetVal = true;
//   }
//
//   return(bRetVal);
//
//}
//
//bool string::xxxetenv(const ::scoped_string & scopedstrVar)
//{
//
//   return xxxget_environment_variable(scopedstrVar);
//
//}
//
//
//// Load the string from resource 'nID'
////bool load_string(atom atom);
//
//// Load the string from resource 'nID' in module 'hInstance'
///*    bool load_string(HINSTANCE hInstance,unsigned int nID )
//{
//const STRINGRESOURCEIMAGE* pImage = gen_GetStringResourceImage( hInstance, nID );
//if( pImage == nullptr )
//{
//return( false );
//}
//
//character_count nLength = ::str::get_char_length( pImage->achString, pImage->nLength );
//char * pszBuffer = GetBuffer( nLength );
//::str::ConvertTochar( pszBuffer, nLength, pImage->achString, pImage->nLength );
//release_buffer( nLength );
//
//return( true );
//}*/
//
//// Load the string from resource 'nID' in module 'hInstance', using language 'wLanguageID'
///*bool load_string(HINSTANCE hInstance,unsigned int nID,unsigned short wLanguageID )
//{
//const STRINGRESOURCEIMAGE* pImage = gen_GetStringResourceImage( hInstance, nID, wLanguageID );
//if( pImage == nullptr )
//{
//return( false );
//}
//
//character_count nLength = ::str::get_char_length( pImage->achString, pImage->nLength );
//char * pszBuffer = GetBuffer( nLength );
//::str::ConvertTochar( pszBuffer, nLength, pImage->achString, pImage->nLength );
//release_buffer( nLength );
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
////void __cdecl string::_Format(const ::scoped_string & scopedstrFormat, ...)
////{
////   ASSERT(is_string_ok(scopedstrFormat));
////
////   va_list argList;
////   va_start(argList, pszFormat);
////   printf(scopedstrFormat, argList);
////   va_end(argList);
////}
////
////
////// append formatted data using format string 'pszFormat'
////void __cdecl string::_AppendFormat(const ::scoped_string & scopedstrFormat, ...)
////{
////   ASSERT(is_string_ok(scopedstrFormat));
////
////   va_list argList;
////   va_start(argList, pszFormat);
////
////   append_formatf_arguments(scopedstrFormat, argList);
////
////   va_end(argList);
////}
////
////
////#elif !defined(VARIADIC_TEMPLATE_FORMAT2)
//
//
//void __cdecl string::Format(const ::scoped_string & scopedstrFormat,...)
//{
//   ASSERT(is_string_ok(scopedstrFormat));
//
//   va_list argList;
//   va_start(argList,pszFormat);
//   printf(scopedstrFormat,argList);
//   va_end(argList);
//}
//
//
//// append formatted data using format string 'pszFormat'
//void __cdecl string::AppendFormat(const ::scoped_string & scopedstrFormat,...)
//{
//   ASSERT(is_string_ok(scopedstrFormat));
//
//   va_list argList;
//   va_start(argList,pszFormat);
//
//   append_formatf_arguments(scopedstrFormat,argList);
//
//   va_end(argList);
//}
//
//// Format a message using format string 'pszFormat'
//void __cdecl string::format_message(const ::scoped_string & scopedstrFormat,...)
//{
//   if(scopedstrFormat == nullptr)
//      throw ::exception(error_bad_argument);
//
//   va_list argList;
//   va_start(argList,pszFormat);
//
//   FormatMessageV(scopedstrFormat,&argList);
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
//void string::reserve(character_count res_arg)
//{
//   get_buffer(res_arg + 1);
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
//string string::unichar_substr(character_count iFirst) const
//{
//
//   return unichar_substr(iFirst,-1);
//
//}
//
//string string::unichar_substr(character_count iFirst,character_count nCount) const
//{
//
//   const char * pchStart = *this;
//
//   if(pchStart == nullptr)
//      return "";
//
//   ::collection::count iUnicharLength = unichar_length();
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
//   ::collection::count cCount = 0;
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
//      pchEnd = ::str::__utf8_inc(pchEnd);
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
//::collection::count string::utf8_get_length() const
//{
//
//   const char * pch = *this;
//
//   if(pch == nullptr)
//      return 0;
//
//   ::collection::count cCharCount = 0;
//
//   while(pch != nullptr && *pch != '\0')
//   {
//
//      pch = ::str::__utf8_inc(pch);
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
//character_count string::char_get_count(character_count iCharCount) const
//{
//
//   character_count iFinalLen = 0;
//
//   auto psz = operator const char*();
//
//   character_count cMaxLen = get_length();
//
//   while(iCharCount > 0)
//   {
//
//      character_count iLen = unicode_uni_len(scopedstr);
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
//   return ::str::eat_before(strBefore, strSeparator, *this, bEatEverythingIfNotFound);
//
//}
//
//
//bool string::eat_before_let_separator(string & strBefore, string strSeparator, bool bEatEverythingIfNotFound)
//{
//
//   return ::str::eat_before_let_separator(strBefore, strSeparator, *this, bEatEverythingIfNotFound);
//
//}
//
//
//void string::add(char ch)
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


CLASS_DECL_ACME::string string_formatf(const ::ansi_character * pszFormat, ...)
{

   ::string str;

   va_list argList;

   va_start(argList, pszFormat);

   str.formatf_arguments(scopedstrFormat, argList);

   va_end(argList);

   return str;

}



