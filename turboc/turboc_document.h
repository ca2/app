#pragma once


namespace turboc
{


   class CLASS_DECL_TURBOC document :
      public ::aura::document
   {
   public:


      document(::particle * pparticle);
	   virtual ~document();

      
	   void assert_ok() const override;
	   void dump(dump_context & dumpcontext) const override;

      virtual bool on_new_document();
      virtual bool on_open_document(const ::payload & payloadFile) override;

      virtual i64 increment_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS);

      virtual i64 decrement_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS);


   };


} // namespace turboc















