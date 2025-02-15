//
// Created by camilo on 2022-08-03
//
#pragma once


#include "base/user/user/document.h"


class CLASS_DECL_BASE simple_tab_document :
   virtual public ::user::document
{
public:


   simple_tab_document();
   ~simple_tab_document() override;


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



