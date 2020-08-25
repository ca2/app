#pragma once


namespace user
{


   class CLASS_DECL_CORE color_combo_box :
      virtual public ::user::interaction
   {
   public:

      ::user::document *         m_pdocument;
      ::userex::color_view *     m_pview;
      ::simple_frame_window *    m_pframe;
      ::hls                      m_hls;
      bool                       m_bMouseDown;


      color_combo_box();
      virtual ~color_combo_box();


      virtual void install_message_routing(::channel * psender) override;


      DECL_GEN_SIGNAL(_001OnCreate);
      DECL_GEN_SIGNAL(_001OnLButtonDown);
      DECL_GEN_SIGNAL(_001OnLButtonUp);
      DECL_GEN_SIGNAL(_001OnMouseMove);
      DECL_GEN_SIGNAL(_001OnMouseLeave);
      DECL_GEN_SIGNAL(_001OnShowWindow);


      void on_layout(::draw2d::graphics_pointer & pgraphics) override;


      virtual void _001OnDraw(::draw2d::graphics_pointer & pgraphics) override;

      virtual void on_control_event(::user::control_event * pevent) override;

   };


} //  namespace user



