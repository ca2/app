#pragma once


#include "berg/user/simple/tab_document.h"


class CLASS_DECL_CORE simple_pane_document :
   virtual public ::simple_tab_document
{
public:


   //__creatable(simple_pane_document);


   simple_pane_document();
   ~simple_pane_document() override;


   // void assert_ok() const override;
   // void dump(dump_context & dumpcontext) const override;

   bool on_new_document() override;
   bool on_open_document(const ::payload & payloadFile) override;

#ifdef _DEBUG
   virtual long long increment_reference_count() override;
   virtual long long decrement_reference_count() override;
#else
   
#endif


};
