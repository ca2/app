#include "framework.h"
#include "hresult_exception.h"
#include "acme/_operating_system.h"


CLASS_DECL_ACME_WINDOWS_COMMON void throw_if_failed(HRESULT hr)
{

   if (FAILED(hr))
   {

      throw ::hresult_exception(hr);

   }

}




