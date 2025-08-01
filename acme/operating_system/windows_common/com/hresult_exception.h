#pragma once


#include "acme/exception/exception.h"
#include "acme/_operating_system.h"


class CLASS_DECL_ACME hresult_exception :
   public ::exception
{
public:


   hresult_exception(HRESULT hresult, const_char_pointer  pszMessage = nullptr);
   ~hresult_exception() override;


};


inline ::string hresult_text(HRESULT hresult)
{

   return ::windows::last_error_message((DWORD)hresult);

}


inline void defer_throw_hresult(HRESULT hresult)
{

   if (FAILED(hresult))
   {

      throw hresult_exception(hresult);

   }

}


inline error_code hresult_error_code(HRESULT hresult)
{

   return { e_error_code_type_hresult, (long long)hresult };

}



