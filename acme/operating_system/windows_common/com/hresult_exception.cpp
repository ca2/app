#include "framework.h"
#include "hresult_exception.h"
#include "acme/operating_system/windows_common/_string.h"


hresult_exception::hresult_exception(HRESULT hresult, const_char_pointer pszMessage) :
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


CLASS_DECL_ACME ::string hresult_to_string(HRESULT hr)
{

   LPWSTR pwszBuffer = nullptr;

   DWORD size = ::FormatMessageW(
       FORMAT_MESSAGE_ALLOCATE_BUFFER |
       FORMAT_MESSAGE_FROM_SYSTEM |
       FORMAT_MESSAGE_IGNORE_INSERTS,
       nullptr,
       hr,
       MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
       (LPWSTR)&pwszBuffer,
       0,
       nullptr);

   ::wstring wstrMessage;

   if (size && pwszBuffer)
   {

      wstrMessage = pwszBuffer;

      ::LocalFree(pwszBuffer);

   }
   else
   {

      wstrMessage = L"Unknown error";

   }

   return wstrMessage;

}

