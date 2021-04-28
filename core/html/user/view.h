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
   virtual bool pre_create_window(::user::system * pusersystem) override;
   virtual void on_subject(::subject::subject * psubject, ::subject::context * pcontext) override;

   DECLARE_MESSAGE_HANDLER(_001OnDestroy);
   DECLARE_MESSAGE_HANDLER(on_message_create);
   DECLARE_MESSAGE_HANDLER(_001OnContextMenu);
   DECLARE_MESSAGE_HANDLER(_001OnSetCursor);

};

