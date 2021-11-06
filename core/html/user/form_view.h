#pragma once

class CLASS_DECL_CORE html_form_view :
   virtual public ::html_form
{
public:


   html::element* m_pelementalLButtonDown;


   html_form_view();
   virtual ~html_form_view();


   void assert_valid() const override;
   void dump(dump_context & dumpcontext) const override;

   string GetLocationURL();
   bool Refresh2(i32 i);
   virtual bool Navigate(const ::string & pszUrl) override;

   virtual void on_document_complete(const ::string & strUrl);

   void install_message_routing(::channel * pchannel) override;
   virtual bool pre_create_window(::user::system * pusersystem) override;
   virtual void OnDraw(::draw2d::graphics_pointer & pgraphics);      // overridden to draw this ::user::impact
   virtual void handle(::subject * psubject, ::context * pcontext) override;


   //virtual void handle(::subject * psubject, ::context * pcontext) override;
   DECLARE_MESSAGE_HANDLER(_001OnSetFocus);
   DECLARE_MESSAGE_HANDLER(_001OnKillFocus);


   form_document * get_document();

};



