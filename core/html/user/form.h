#pragma once


class CLASS_DECL_CORE html_form :
   virtual public ::user::form_view
{
public:


   __pointer(::html::element)                m_pelementLButtonDown;
   __pointer(::html::element)                m_pelementHover;
   __pointer_array(::html::element)          m_elementaMouseMove;
   __pointer(::html_data)                    m_phtmldata;


   html_form();
   virtual ~html_form();

   
   virtual void initialize(::object * pobject) override;


   virtual void _001OnDraw(::draw2d::graphics_pointer & pgraphics) override;
   virtual void _001DrawChildren(::draw2d::graphics_pointer & pgraphics) override;

   //virtual void on_layout(::html_data * phtmldata);
   virtual void on_layout(::draw2d::graphics_pointer & pgraphics) override;

   virtual void handle(::subject * psubject, ::context * pcontext) override;

   void install_message_routing(::channel * pchannel) override;

   virtual string get_path() override;

   virtual void open_document(const ::payload & payloadFile) override;
   virtual void open_html(const ::string & str) override;


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



   virtual void _001GetText(string & str) const override;
   virtual void _001SetText(const ::string & str, const ::action_context & action_context) override;


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
