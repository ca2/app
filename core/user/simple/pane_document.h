#pragma once




class CLASS_DECL_CORE simple_pane_document :
   public ::user::document
{
public:


   DECLARE_CREATABLE(simple_pane_document);


   simple_pane_document();
   virtual ~simple_pane_document();


   void assert_ok() const override;
   void dump(dump_context & dumpcontext) const override;

   bool on_new_document() override;
   virtual bool on_open_document(const ::payload & payloadFile) override;

#ifdef _DEBUG
   virtual i64 increment_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS) override;
   virtual i64 decrement_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS) override;
#else
   
#endif


};
