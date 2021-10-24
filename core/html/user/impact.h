#pragma once

class form_document;


class CLASS_DECL_CORE html_view :
   virtual public ::html_form
{
public:



   

   string m_strLocationURL;


   html_view();
   virtual ~html_view();


   void assert_valid() const override;
   void dump(dump_context & dumpcontext) const override;

   


   string GetLocationURL();
   bool Refresh2(i32 i);
   virtual bool Navigate(const ::string & pszUrl) override;

   virtual void on_document_complete(const ::string & strUrl);


   void install_message_routing(::channel * pchannel) override;
   virtual bool pre_create_window(::user::system * pusersystem) override;
   virtual void handle(::subject * psubject, ::context * pcontext) override;

   DECLARE_MESSAGE_HANDLER(on_message_destroy);
   DECLARE_MESSAGE_HANDLER(on_message_create);
   DECLARE_MESSAGE_HANDLER(on_message_context_menu);
   ////DECLARE_MESSAGE_HANDLER(on_message_set_cursor);

};

