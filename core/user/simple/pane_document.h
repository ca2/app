#pragma once


class CLASS_DECL_CORE simple_pane_document :
   public ::user::document
{
public:


   simple_pane_document();
   virtual ~simple_pane_document();


   virtual void assert_valid() const override;
   virtual void dump(dump_context & dumpcontext) const override;

   virtual bool on_new_document() override;
   virtual bool on_open_document(const ::payload & varFile) override;

#ifdef DEBUG
   virtual i64 add_ref(OBJ_REF_DBG_PARAMS) override;
   virtual i64 dec_ref(OBJ_REF_DBG_PARAMS) override;
#else
   
#endif


};
