// get_mem_info2 from debug.h by camilo on 2022-11-07 01:53 <3ThomasBorregaardSorensen!!
#pragma once


#include "_c.h"


#include "acme/operating_system/error_code.h"


#include "acme/prototype/comparison/compare.h"


#include "acme/prototype/time/_time.h"


#include "acme/operating_system/time.h"


#include "acme/operating_system/windows_common/last_error.h"


#include "_string.h"


//using dword_array_base = ::numeric_array_base < DWORD >;

//using dword_array = ::array_particle < ::dword_array_base >;



// #ifdef MEMDLEAK
//
//
// //CLASS_DECL_ACME string get_mem_info_report1();
// //CLASS_DECL_ACME::collection::count get_mem_info(int ** ppiUse, const_char_pointer ** ppszFile, const_char_pointer ** pszCallStack, ::u32 ** ppuiLine, size_t ** ppsize);
// #ifdef WINDOWS
// CLASS_DECL_ACME::collection::count get_mem_info2(int ** ppiUse, const_char_pointer ** ppszFile, DWORD64 ** ppuiStack[64], ::i64 ** ppiStack, int ** ppiLine, ::i64 ** ppiSize);
// #endif
//
//
// #endif


namespace windows
{

   constexpr ::u32 wait_millis(const class time& time)
   {

      if (time.is_infinite())
      {

         return INFINITE;

      }

      auto i = time.integral_millisecond();

      return i > 0xFFFFFFFEu ? 0xFFFFFFFEu : (DWORD) i;

   }



}

//template < >
//inline bool gt(DWORD dw, int i)
//{
//   return i < 0 ? true : dw >((DWORD)i);
//}

//template < >
//inline bool gt(count i,::u64 u)
//{

//   return i < 0 ? false : ((::u64)i) > u;

//}

//#endif

CLASS_DECL_ACME void TRACELASTERROR();


#include "acme/operating_system/windows_common/last_error.h"
#include "acme/operating_system/windows_common/last_error_exception.h"



namespace windows
{


   CLASS_DECL_ACME::enum_status _last_error_status(::u32 uLastError);
   inline ::e_status last_error_status(const last_error & lasterror) { return _last_error_status(lasterror.m_uLastError); }
   
   
   CLASS_DECL_ACME::enum_status _failed_last_error_status(::u32 uLastError);
   inline ::e_status failed_last_error_status(const last_error & lasterror) { return _failed_last_error_status(lasterror.m_uLastError); }


   //CLASS_DECL_ACME::enum_status _hresult_status(HRESULT hresult);
   //inline ::e_status hresult_status(HRESULT hresult) { return _hresult_status(hresult); }


   CLASS_DECL_ACME void * get_library_symbol_address(const ::file::path & pathLibrary, const ::scoped_string & scopedstrSymbolName);


   template < typename PFN >
   class function
   {
   public:


      inline static PFN get_address(const ::scoped_string & scopedstrModule, const_char_pointer lpszName)
      {

         return (PFN) get_library_symbol_address(scopedstrModule, lpszName);

      }


   };


   CLASS_DECL_ACME ::e_status wait_result_status(int iResult, int nCount);

   CLASS_DECL_ACME ::u32 _get_file_attributes(const ::file::path & path);

   CLASS_DECL_ACME ::u32 get_file_attributes(const ::file::path & path);

   CLASS_DECL_ACME ::i32_bool is_win32_accessible(::u32 uFileAttributes, const last_error & lasterror);

   CLASS_DECL_ACME ::i32_bool is_win32_accessible(const ::file::path & path);

   CLASS_DECL_ACME void set_file_attributes(const ::file::path & path, ::u32 uFileAttributes);


   CLASS_DECL_ACME error_code last_error_error_code(const last_error & lasterror);


   CLASS_DECL_ACME error_code last_error_error_code();


   //CLASS_DECL_ACME void throw_last_error_exception(const ::last_error & lasterror);


   //CLASS_DECL_ACME void throw_last_error_exception();


} // namespace windows


//
//
//
//#ifdef WINDOWS 
//#define ARG_SEC_ATTRS_DEF , void * psaAttributes = nullptr
//#define ARG_SEC_ATTRS , void * psaAttributes
//#define PARAM_SEC_ATTRS (void *) psaAttributes
//#define PASS_SEC_ATTRS psaAttributes
//#define INSERT_PARAM_SEC_ATTRS(ATTRS) , ATTRS
//#define ADD_PARAM_SEC_ATTRS , PARAM_SEC_ATTRS
//#define ADD_PASS_SEC_ATTRS , PASS_SEC_ATTRS
//#else
//#define ARG_SEC_ATTRS_DEF 
//#define ARG_SEC_ATTRS
//#define PARAM_SEC_ATTRS
//#define INSERT_PARAM_SEC_ATTRS(ATTRS) 
//#define ADD_PARAM_SEC_ATTRS
//#define ADD_PASS_SEC_ATTRS
//#endif
//
//
//



#include "acme/operating_system/windows_common/handle.h"
#include "acme/operating_system/windows_common/file.h"


namespace windows
{


   [[ noreturn ]] CLASS_DECL_ACME void throw_last_error_exception(const ::scoped_string & scopedstrErrorMessage, const last_error & lasterror = {});
   [[ noreturn ]] CLASS_DECL_ACME void throw_file_last_error_exception(const ::file::path & path, ::file::e_open eopen, const last_error & lasterror = {}, const ::scoped_string & scopedstrErrorMessage = nullptr);


} // namespace windows




