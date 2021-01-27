#pragma once


class CLASS_DECL_BASE form_document :
   virtual public ::user::document,
   virtual public ::user::form_callback
{
public:

   
   form_document();

   virtual ~form_document();

   virtual ::form_data* get_form_data();

   virtual bool on_open_document(const ::payload & varFile) override;
   
   virtual void soft_reload();

};
