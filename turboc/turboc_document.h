#pragma once


namespace turboc
{


   class CLASS_DECL_TURBOC document :
      public ::aura::document
   {
   public:


      document(::particle * pparticle);
	   virtual ~document();

      
	   // void assert_ok() const override;
	   // void dump(dump_context & dumpcontext) const override;

      virtual bool on_new_document();
      virtual bool on_open_document(const ::payload & payloadFile) override;

      virtual long long increment_reference_count();

      virtual long long decrement_reference_count();


   };


} // namespace turboc















