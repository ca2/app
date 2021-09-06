#pragma once


#include "acme/exception/exception_engine.h"


namespace universal_windows
{


   class CLASS_DECL_CORE exception_engine :
      virtual public ::exception_engine
   {
   public:


      exception_engine();
      virtual ~exception_engine();

      
      virtual void reset() override;

      //virtual char* stack_trace(uptr uiSkip, void* caller_address, const ::string & pszFormat) override;


   };


} // namespace universal_windows



