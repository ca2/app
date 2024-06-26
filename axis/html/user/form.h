#pragma once


#include "axis/user/form/window.h"


class CLASS_DECL_AXIS html_form :
   virtual public ::user::form_window
{
public:


   ::pointer<::html::element>               m_pelementLButtonDown;
   ::pointer<::html::element>               m_pelementHover;
   pointer_array < ::html::element >          m_elementaMouseMove;
   ::pointer<::html_data>                   m_phtmldata;


   html_form();
   ~html_form() override;

   
   void initialize(::particle * pparticle) override;


   virtual bool has_document() const;
   virtual bool on_open_document(const ::payload & payloadFile) const;

   
   virtual bool browse(const ::string & pszUrl);


   void _001OnDraw(::draw2d::graphics_pointer & pgraphics) override;
   void _001DrawChildren(::draw2d::graphics_pointer & pgraphics) override;

   //virtual void on_layout(::html_data * phtmldata);
   void on_layout(::draw2d::graphics_pointer & pgraphics) override;

   void handle(::topic * ptopic, ::context * pcontext) override;

   void install_message_routing(::channel * pchannel) override;

   string get_path() override;

   bool open_document(const ::payload & payloadFile) override;
   bool open_html(const ::string & str) override;


   ::html_data * get_html_data();

   //::html_document * get_document();


   virtual void create_html_data();


   DECLARE_MESSAGE_HANDLER(on_message_create);
   DECLARE_MESSAGE_HANDLER(on_message_left_button_down);
   DECLARE_MESSAGE_HANDLER(on_message_mouse_move);
   DECLARE_MESSAGE_HANDLER(on_message_mouse_leave);
   DECLARE_MESSAGE_HANDLER(on_message_left_button_up);
   DECLARE_MESSAGE_HANDLER(_001OnImageLoaded);
   DECLARE_MESSAGE_HANDLER(on_message_key_down);
   DECLARE_MESSAGE_HANDLER(on_message_destroy);



   //virtual void get_text(string & str) override;
   //virtual void set_text(const ::string & str, const ::action_context & action_context) override;
   virtual ::string get_html_form_text();
   virtual void set_html_form_text(const ::scoped_string & scopedstr, const ::action_context & actioncontext);

   virtual void GetClientBox(::rectangle_f32 & box);


   virtual void defer_implement();

   virtual void defer_html_layout();


   virtual bool get_edit_mode();
   virtual void set_edit_mode(bool bSet = true);
   virtual bool load_html(const ::string & str);
   
   virtual void soft_reload() override;

   virtual void set_need_load_form_data() override;
   
   virtual void on_form_implemented();


};
