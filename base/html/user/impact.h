#pragma once


#include "axis/html/user/form.h"
#include "base/user/form/impact.h"
#include "base/user/user/show.h"


class form_document;


class CLASS_DECL_BASE html_impact :
   virtual public ::html_form,
   virtual public ::user::form_impact
{
public:


   string m_strLocationURL;


   html_impact();
   ~html_impact() override;


   // void assert_ok() const override;
   // void dump(dump_context & dumpcontext) const override;

   void initialize(::particle * pparticle) override;


   string GetLocationURL();
   bool Refresh2(i32 i);
   virtual bool browse(const ::string & pszUrl) override;

   virtual void on_document_complete(const ::string & strUrl);


   void install_message_routing(::channel * pchannel) override;
   virtual bool pre_create_window(::user::system * pusersystem) override;
   void handle(::topic * ptopic, ::context * pcontext) override;

   DECLARE_MESSAGE_HANDLER(on_message_destroy);
   DECLARE_MESSAGE_HANDLER(on_message_create);
   DECLARE_MESSAGE_HANDLER(on_message_context_menu);


   bool open_document(const ::payload & payloadFile) override;
   bool open_html(const ::string & strHtml) override;
   void soft_reload() override;


   void _001OnDraw(::draw2d::graphics_pointer & pgraphics) override;
   

   void on_form_implemented() override;


   void on_layout(::draw2d::graphics_pointer & pgraphics) override;


   void set_need_load_form_data() override;


};




