#pragma once


namespace base
{


   class CLASS_DECL_BASE session:
      virtual public ::aura::session
   {
   public:


      __pointer(::user::user)                  m_puser;


      session();
      virtual ~session();

      inline ::user::user *                        user() { return m_puser; }

      virtual __pointer(::user::impact)                      get_view();


      virtual ::estatus     initialize(::object * pobjectContext) override;


      virtual void frame_pre_translate_message(::message::message * pmessage) override;

      virtual ::estatus process_init() override;

      virtual ::estatus init1() override;

      virtual ::estatus init() override;

      virtual void term_session() override;

      virtual void interactive_credentials(::account::credentials * pcredentials) override;

      virtual void on_finally_focus_set(::user::primitive * pelementalFocus) override;

      //virtual ::user::menu_interaction * create_menu_button(::user::style_pointer & pstyle, ::user::menu_item * pitem) override;

      //virtual oswindow get_capture() override;


      virtual void _001OnDefaultTabPaneDrawTitle(::user::tab_pane & pane, ::user::tab * ptab, ::draw2d::graphics_pointer & pgraphics, const ::rect & rect, ::draw2d::brush_pointer & brushText) override;


      virtual bool prepare_menu_button(::user::menu_item * pitem) override;

      virtual bool on_ui_mouse_message(::message::mouse * pmouse) override;

   };


} // namespace base


