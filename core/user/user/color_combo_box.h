#pragma once


namespace user
{


   class CLASS_DECL_CORE color_combo_box :
      virtual public ::user::interaction
   {
   public:


      ::user::document *            m_pdocument;
      ::userex::color_view *        m_pimpact;
      ::experience::frame_window *  m_pframewindow;
      ::color::hls                         m_hls;
      bool                          m_bMouseDown;


      color_combo_box();
      virtual ~color_combo_box();


      inline ::core::application* get_application() const { return m_pcontext ? m_pcontext->m_pcoreapplication : nullptr; }
      inline ::core::session* get_session() const { return m_pcontext ? m_pcontext->m_pcoresession : nullptr; }
      inline ::core::system* get_system() const { return m_psystem ? m_psystem->m_pcoresystem : nullptr; }



      virtual void install_message_routing(::channel * psender) override;


      DECLARE_MESSAGE_HANDLER(on_message_create);
      DECLARE_MESSAGE_HANDLER(on_message_left_button_down);
      DECLARE_MESSAGE_HANDLER(on_message_left_button_up);
      DECLARE_MESSAGE_HANDLER(on_message_mouse_move);
      DECLARE_MESSAGE_HANDLER(on_message_mouse_leave);
      DECLARE_MESSAGE_HANDLER(on_message_show_window);


      void on_layout(::draw2d::graphics_pointer & pgraphics) override;


      virtual void _001OnDraw(::draw2d::graphics_pointer & pgraphics) override;

      virtual void handle(::subject * psubject, ::context * pcontext) override;

   };


} //  namespace user



