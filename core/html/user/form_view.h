#pragma once

class CLASS_DECL_CORE html_form_view :
   virtual public ::html_form
{
public:


   html::element* m_pelementalLButtonDown;


   html_form_view();
   virtual ~html_form_view();


   virtual void assert_valid() const override;
   virtual void dump(dump_context & dumpcontext) const override;

   string GetLocationURL();
   bool Refresh2(i32 i);
   virtual bool Navigate(const char * pszUrl) override;

   virtual void on_document_complete(const ::string & strUrl);

   virtual void install_message_routing(::channel * pchannel) override;
   virtual bool pre_create_window(::user::system * pusersystem) override;
   virtual void OnDraw(::draw2d::graphics_pointer & pgraphics);      // overridden to draw this ::user::impact
   virtual void on_subject(::subject::subject * psubject, ::subject::context * pcontext) override;


   //virtual void on_subject(::subject::subject * psubject, ::subject::context * pcontext) override;
   DECLARE_MESSAGE_HANDLER(_001OnSetFocus);
   DECLARE_MESSAGE_HANDLER(_001OnKillFocus);


   form_document * get_document();

};



