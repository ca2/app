#include "framework.h"
#include "hresult_exception.h"
#include "acme/operating_system/windows_common/_string.h"


hresult_exception::hresult_exception(HRESULT hresult, const char * pszMessage) :
   ::exception(::error_hresult, pszMessage)
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

   m_errorcodea.add(hresult_error_code(hresult));

   //m_strMessage = pszMessage;

}


hresult_exception::~hresult_exception()
{


}


#define ERRMSGBUFFERSIZE 256





