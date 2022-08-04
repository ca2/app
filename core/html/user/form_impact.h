#pragma once

class CLASS_DECL_CORE html_form_impact :
   virtual public ::html_form
{
public:


   html::element* m_pelementalLButtonDown;


   html_form_impact();
   virtual ~html_form_impact();


   void assert_ok() const override;
   void dump(dump_context & dumpcontext) const override;

   string GetLocationURL();
   bool Refresh2(i32 i);
   virtual bool Navigate(const ::string & pszUrl) override;

   virtual void on_document_complete(const ::string & strUrl);

   void install_message_routing(::channel * pchannel) override;
   virtual bool pre_create_window(::user::system * pusersystem) override;
   virtual void OnDraw(::draw2d::graphics_pointer & pgraphics);      // overridden to draw this ::user::impact
   virtual void handle(::topic * ptopic, ::context * pcontext) override;


   //virtual void handle(::topic * ptopic, ::context * pcontext) override;
   DECLARE_MESSAGE_HANDLER(on_message_set_focus);
   DECLARE_MESSAGE_HANDLER(on_message_kill_focus);


   form_document * get_document();

};



