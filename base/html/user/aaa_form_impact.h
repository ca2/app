#pragma once


#include "axis/html/user/form.h"
#include "base/user/user/show.h"


class CLASS_DECL_BASE html_form_impact :
   virtual public ::user::show<::html_form>
{
public:


   html::element* m_pelementalLButtonDown;


   html_form_impact();
   ~html_form_impact() override;


   // void assert_ok() const override;
   // void dump(dump_context & dumpcontext) const override;

   string GetLocationURL();
   bool Refresh2(int i);
   bool browse(const ::scoped_string & scopedstrUrl) override;

   virtual void on_document_complete(const ::scoped_string & scopedstrUrl);

   void install_message_routing(::channel * pchannel) override;
   bool pre_create_window(::user::system * pusersystem) override;
   //virtual void OnDraw(::draw2d::graphics_pointer & pgraphics);      // overridden to draw this ::user::impact
   void handle(::topic * ptopic, ::handler_context * phandlercontext) override;


   //virtual void handle(::topic * ptopic, ::handler_context * phandlercontext) override;
   DECLARE_MESSAGE_HANDLER(on_message_set_focus);
   DECLARE_MESSAGE_HANDLER(on_message_kill_focus);


   form_document * get_document();


   void on_form_implemented() override;


};



