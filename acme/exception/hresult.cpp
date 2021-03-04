#include "framework.h"


#ifdef WINDOWS


hresult_exception::hresult_exception(HRESULT hresult, const char * pszMessage)
{

   if (hresult == S_OK)
   {

      m_estatus = success;

   }
   else if (FAILED(hresult))
   {

      m_estatus = error_hresult;

   }
   else if (SUCCEEDED(hresult))
   {

      m_estatus = success_hresult;

   }

   m_hresult = hresult;

   m_strMessage = pszMessage;

}



hresult_exception::~hresult_exception()
{

}


#define ERRMSGBUFFERSIZE 256


CLASS_DECL_ACME int trace_hr(const char * psz,HRESULT hr)
{

   string strError = get_system_error_message(hr);

   strError.trim();

   //TRACE("%s hr=%d:\"%s\"",psz,hr,strError.c_str());

   return 0;

}


#endif

