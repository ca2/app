#pragma once


#include "acme/primitive/primitive/payload.h"


namespace dynamic_source
{


   class CLASS_DECL_APP_PROGRAMMING exit_exception
   {
   public:


      i32     m_iCode;
      ::payload         m_varRet;


      exit_exception(i32 iCode);


   };


} // namespace dynamic_source



