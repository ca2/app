// get_mem_info2 from debug.h by camilo on 2022-11-07 01:53 <3ThomasBorregaardSorensen!!
#pragma once


#include "_c.h"


#include "acme/operating_system/error_code.h"


#include "acme/prototype/comparison/compare.h"


#include "acme/prototype/time/_time.h"


#include "acme/operating_system/time.h"


#include "acme/operating_system/windows_common/last_error.h"


#include "_string.h"


using dword_array_base = ::numeric_array_base < DWORD >;

using dword_array = ::array_particle < ::dword_array_base >;



#ifdef MEMDLEAK


//CLASS_DECL_ACME string get_mem_info_report1();
//CLASS_DECL_ACME::collection::count get_mem_info(int ** ppiUse, const_char_pointer ** ppszFile, const_char_pointer ** pszCallStack, unsigned int ** ppuiLine, size_t ** ppsize);
#ifdef WINDOWS
CLASS_DECL_ACME::collection::count get_mem_info2(int ** ppiUse, const_char_pointer ** ppszFile, DWORD64 ** ppuiStack[64], long long ** ppiStack, int ** ppiLine, long long ** ppiSize);
#endif


#endif


namespace windows
{

   constexpr DWORD wait(const class time& time)
   {

      auto i = time.integral_millisecond();

      return i > ((decltype(i))INFINITE) ? INFINITE : (DWORD) i;

   }



}

//template < >
//inline bool gt(DWORD dw, int i)
//{
//   return i < 0 ? true : dw >((DWORD)i);
//}

//template < >
//inline bool gt(count i,unsigned long long u)
//{

//   return i < 0 ? false : ((unsigned long long)i) > u;

//}

//#endif

CLASS_DECL_ACME void TRACELASTERROR();


namespace windows
{


   CLASS_DECL_ACME::enum_status _last_error_status(unsigned int uLastError);
   inline ::e_status last_error_status(const last_error & lasterror) { return _last_error_status(lasterror.m_uLastError); }
   
   
   CLASS_DECL_ACME::enum_status _failed_last_error_status(unsigned int uLastError);
   inline ::e_status failed_last_error_status(const last_error & lasterror) { return _failed_last_error_status(lasterror.m_uLastError); }


   CLASS_DECL_ACME::enum_status _hresult_status(HRESULT hresult);
   inline ::e_status hresult_status(HRESULT hresult) { return _hresult_status(hresult); }


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

   CLASS_DECL_ACME unsigned int _get_file_attributes(const ::file::path & path);

   CLASS_DECL_ACME unsigned int get_file_attributes(const ::file::path & path);

   CLASS_DECL_ACME int_bool is_win32_accessible(unsigned int uFileAttributes, const last_error & lasterror);

   CLASS_DECL_ACME int_bool is_win32_accessible(const ::file::path & path);

   CLASS_DECL_ACME void set_file_attributes(const ::file::path & path, unsigned int uFileAttributes);


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


   CLASS_DECL_ACME void enum_processes(dword_array_base & dwaProcesses);
   CLASS_DECL_ACME dword_array_base enum_processes();


   [[ noreturn ]] CLASS_DECL_ACME void throw_last_error_exception(const ::scoped_string & scopedstrErrorMessage, const last_error & lasterror = {});
   [[ noreturn ]] CLASS_DECL_ACME void throw_file_last_error_exception(const ::file::path & path, ::file::e_open eopen, const last_error & lasterror = {}, const ::scoped_string & scopedstrErrorMessage = nullptr);



} // namespace windows




