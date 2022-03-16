#pragma once


class CLASS_DECL_CORE html_document :
   virtual public ::form_document
{
public:


   //__composite(::html_data)         m_phtmldata;


   html_document();
   virtual ~html_document();


   void assert_ok() const override;
   void dump(dump_context & dumpcontext) const override;


   //virtual void create_html_data();


   virtual ::html_data * get_html_data();

   virtual ::form_data* get_form_data() override;

   DECLARE_MESSAGE_HANDLER(data_on_after_change);

   virtual bool open_document(const ::payload & payloadFile) override;

   virtual bool load_html(const ::string & str);

   bool on_new_document() override;

   virtual void form_document_set_property_set(const property_set & set) override;
   virtual property_set * form_document_get_property_set() override;

   virtual void form_document_set_view(::user::form * pimpact);
   virtual void form_document_set_callback(::user::form_callback * pcallback);

   //bool open_document(::create * pcreate) override;
   bool on_open_document(const ::payload & payloadFile) override;

   virtual void on_command_probe(::message::command * pcommand) override;
   virtual void on_command(::message::command * pcommand) override;

   virtual void soft_reload() override;

   virtual __pointer(::user::interaction) get_frame();


};



