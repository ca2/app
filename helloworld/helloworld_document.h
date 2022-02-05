#pragma once


namespace helloworld
{


   class CLASS_DECL_APP_HELLOWORLD document :
      public ::user::document
   {
   public:


      document(::object * pobject);
      virtual ~document();


      void assert_ok() const override;
      void dump(dump_context & dumpcontext) const override;

      virtual bool on_new_document();
      virtual bool on_open_document(const ::payload & payloadFile) override;

      virtual i64 increment_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS);

      virtual i64 decrement_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS);


   };


} // namespace helloworld















