#pragma once


namespace windows
{


   CLASS_DECL_ACME string last_error_message();
   CLASS_DECL_ACME string last_error_message(DWORD dwError);


   CLASS_DECL_ACME::enum_status _last_error_status(DWORD dwLastError);
   inline ::e_status last_error_status(DWORD dwLastError) { return _last_error_status(dwLastError); }


   CLASS_DECL_ACME::enum_status _hresult_status(HRESULT hresult);
   inline ::e_status hresult_status(HRESULT hresult) { return _hresult_status(hresult); }


   CLASS_DECL_ACME void * get_library_symbol_addrress(const char * pszLibrary, const char * lpszSymbolName);


   template < typename PFN >
   class library
   {
   public:


      inline static PFN get_address(const char * pszModule, const char * lpszName)
      {

         return (PFN) get_library_symbol_addrress(pszModule, lpszName);

      }


   };


} // namespace windows





#ifdef WINDOWS 
#define ARG_SEC_ATTRS_DEF , void * psaAttributes = nullptr
#define ARG_SEC_ATTRS , void * psaAttributes
#define PARAM_SEC_ATTRS (void *) psaAttributes
#define PASS_SEC_ATTRS psaAttributes
#define INSERT_PARAM_SEC_ATTRS(ATTRS) , ATTRS
#define ADD_PARAM_SEC_ATTRS , PARAM_SEC_ATTRS
#define ADD_PASS_SEC_ATTRS , PASS_SEC_ATTRS
#else
#define ARG_SEC_ATTRS_DEF 
#define ARG_SEC_ATTRS
#define PARAM_SEC_ATTRS
#define INSERT_PARAM_SEC_ATTRS(ATTRS) 
#define ADD_PARAM_SEC_ATTRS
#define ADD_PASS_SEC_ATTRS
#endif



