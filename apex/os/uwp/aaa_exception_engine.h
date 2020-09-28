#pragma once


namespace uwp
{


   class CLASS_DECL_APEX exception_engine :
      virtual public ::exception_engine
   {
   public:


      exception_engine();
      virtual ~exception_engine();

      
      virtual void reset() override;

      //virtual char* stack_trace(uptr uiSkip, void* caller_address, const char* pszFormat) override;


   };


} // namespace uwp



