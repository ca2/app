#pragma once


namespace turboc
{


   class CLASS_DECL_TURBOC document :
      public ::aura::document
   {
   public:


      document(::object * pobject);
	   virtual ~document();

      
	   virtual void assert_valid() const;
	   virtual void dump(dump_context & dumpcontext) const;

      virtual bool on_new_document();
      virtual bool on_open_document(const ::payload & varFile) override;

      virtual i64 add_ref(OBJECT_REF_DEBUG_PARAMS);

      virtual i64 dec_ref(OBJECT_REF_DEBUG_PARAMS);


   };


} // namespace turboc















