#pragma once


namespace browser
{


   class CLASS_DECL_APP_BROWSER document :
      public ::user::document
   {
   public:


      document(::particle * pparticle);
      virtual ~document();


//      // void assert_ok() const override;
//      // void dump(dump_context & dumpcontext) const override;

      virtual bool on_new_document();
      virtual bool on_open_document(const ::payload & payloadFile) override;

      virtual i64 increment_reference_count(REFERENCING_DEBUGGING_PARAMETERS);

      virtual i64 decrement_reference_count(REFERENCING_DEBUGGING_PARAMETERS);


   };


} // namespace browser



