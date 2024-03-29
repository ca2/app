#pragma once


#include "base/user/user/document.h"
#include "aura/user/user/form_callback.h"


class CLASS_DECL_BASE form_document :
   virtual public ::user::document,
   virtual public ::user::form_callback
{
public:

   
   form_document();

   ~form_document() override;


   virtual ::form_data* get_form_data();

   virtual bool on_open_document(const ::payload & payloadFile) override;
   
   virtual void soft_reload();


};
