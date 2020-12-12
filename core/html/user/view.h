#pragma once

class form_document;


class CLASS_DECL_CORE html_view :
   virtual public ::html_form
{
public:



   

   string m_strLocationURL;


   html_view();
   virtual ~html_view();


   virtual void assert_valid() const override;
   virtual void dump(dump_context & dumpcontext) const override;

   


   string GetLocationURL();
   bool Refresh2(i32 i);
   virtual bool Navigate(const char * pszUrl) override;

   virtual void on_document_complete(const char * pszUrl);


   virtual void install_message_routing(::channel * pchannel) override;
   virtual bool pre_create_window(::user::create_struct * pcreatestruct) override;
   virtual void on_subject(::promise::subject * psubject, ::promise::context * pcontext) override;

   DECL_GEN_SIGNAL(_001OnDestroy);
   DECL_GEN_SIGNAL(_001OnCreate);
   DECL_GEN_SIGNAL(_001OnContextMenu);
   DECL_GEN_SIGNAL(_001OnSetCursor);

};

