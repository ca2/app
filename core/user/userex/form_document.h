#pragma once


class CLASS_DECL_CORE form_document :
   virtual public ::aura::document,
   virtual public ::database::client,
   virtual public ::user::form_callback
{
public:


   


   form_document();

   virtual void form_document_set_property_set(const property_set & set);
   virtual property_set * form_document_get_property_set();
   virtual property_set & form_document_property_set();

   virtual void form_document_set_view(form_impact * pimpact);
   virtual void form_document_set_callback(form_callback * pcallback);


   virtual bool open_document(const ::payload & payloadFile) override;


};



