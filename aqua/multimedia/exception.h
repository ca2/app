#pragma once


////#include "acme/exception/exception.h"


namespace multimedia
{


   class CLASS_DECL_AQUA exception :
      public ::exception
   {
   public:


      enum_exception          m_eexception;


      exception(enum_exception eexception = e_exception_undefined, const ::e_status & estatus = error_exception, const char * pszMessage = nullptr);
      ~exception() override;


      string get_message() const override;


   };


} // namespace multimedia



