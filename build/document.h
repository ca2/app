#pragma once


namespace app_core_build
{


   class CLASS_DECL_APP_CORE_BUILD document :
      virtual public ::app_consumer < application, ::user::document >
   {
   public:


      

      document();
      ~document() override;


//      void assert_ok() const override;
//      void dump(dump_context & dumpcontext) const override;

      bool on_new_document() override;
      virtual bool on_open_document(const ::payload & payloadFile) override;
      virtual bool on_save_document(::file::file * pwriter) override;

#ifdef _DEBUG
      
      virtual i64 increment_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS) override;
      virtual i64 decrement_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS) override;

#endif



   };


} // namespace app_core_build



