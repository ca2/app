#pragma once


#include "axis/html/user/form.h"
#include "base/user/user/show.h"


class form_document;


class CLASS_DECL_BASE html_impact :
   virtual public ::user::show < ::html_form >
{
public:


   string m_strLocationURL;


   html_impact();
   ~html_impact() override;


   void assert_ok() const override;
   void dump(dump_context & dumpcontext) const override;

   


   string GetLocationURL();
   bool Refresh2(i32 i);
   virtual bool browse(const ::string & pszUrl) override;

   virtual void on_document_complete(const ::string & strUrl);


   void install_message_routing(::channel * pchannel) override;
   virtual bool pre_create_window(::user::system * pusersystem) override;
   virtual void handle(::topic * ptopic, ::context * pcontext) override;

   DECLARE_MESSAGE_HANDLER(on_message_destroy);
   DECLARE_MESSAGE_HANDLER(on_message_create);
   DECLARE_MESSAGE_HANDLER(on_message_context_menu);
   ////DECLARE_MESSAGE_HANDLER(on_message_set_cursor);

   void on_form_implemented() override;


};




