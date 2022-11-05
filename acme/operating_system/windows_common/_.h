#pragma once


#include "acme/operating_system/error_code.h"


CLASS_DECL_ACME void TRACELASTERROR();


namespace windows
{


   CLASS_DECL_ACME string last_error_message();
   CLASS_DECL_ACME string last_error_message(DWORD dwError);


   CLASS_DECL_ACME::enum_status _last_error_status(DWORD dwLastError);
   inline ::e_status last_error_status(DWORD dwLastError) { return _last_error_status(dwLastError); }


   CLASS_DECL_ACME::enum_status _hresult_status(HRESULT hresult);
   inline ::e_status hresult_status(HRESULT hresult) { return _hresult_status(hresult); }


   CLASS_DECL_ACME void * get_library_symbol_address(const char * pszLibrary, const char * lpszSymbolName);


   template < typename PFN >
   class function
   {
   public:


      inline static PFN get_address(const char * pszModule, const char * lpszName)
      {

         return (PFN) get_library_symbol_address(pszModule, lpszName);

      }


   };


   CLASS_DECL_ACME ::e_status wait_result_status(int iResult);


   CLASS_DECL_ACME wstring get_file_path_root(const wstring & wstrPath);


   CLASS_DECL_ACME DWORD get_file_attributes(const char * path);


   CLASS_DECL_ACME error_code last_error_error_code(DWORD dwLastError);


   CLASS_DECL_ACME error_code last_error_error_code();


   CLASS_DECL_ACME void throw_last_error(DWORD dwLastError);


   CLASS_DECL_ACME void throw_last_error();


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
