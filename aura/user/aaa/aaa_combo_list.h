#pragma once


namespace user
{


   class CLASS_DECL_AURA list_box :
      virtual public ::user::scroll_base
   {
   public:


      ::duration                              m_durationKillFocus;
      bool                                m_bPendingKillFocusHiding;
      bool                                m_bMovingComboBox;
      bool                                m_bComboList;
      __pointer(combo_box)                m_pcombo;
      int                                 m_iBorder;
      int                                 m_iPadding;
      int                                 m_iMinListItemCount;
      ::item                        m_itemLButtonDown;
      //::user::frame_window *            m_puiDeactivateTogether;
      ::user::interaction *               m_puiDeactivateTogether;

      ::duration                                m_durationLastVisibilityChange;


      list_box();
      virtual ~list_box();


      void user_combo_list_common_construct();


      void install_message_routing(::channel * pchannel) override;

      virtual void _001OnDraw(::draw2d::graphics_pointer & pgraphics) override;

      //virtual void _001OnDrawVerisimple(::draw2d::graphics_pointer & pgraphics);
      //virtual void _001OnDrawSimply(::draw2d::graphics_pointer & pgraphics);

      //virtual void _002OnDrawVerisimple(::draw2d::graphics_pointer & pgraphics);
      virtual void _001OnDrawComboList(::draw2d::graphics_pointer & pgraphics);

      virtual void query_full_size(::draw2d::graphics_pointer& pgraphics, LPSIZE32 psize);


      virtual ::write_text::font_pointer get_font(style* pstyle, enum_element eelement = e_element_none, estate estate = e_state_none) const override;


      virtual i32 _001GetItemHeight() const;

      virtual void on_change_combo_sel(index iSel);

      bool pre_create_window(::user::system * pusersystem) override;

      virtual void _001EnsureVisible(index iItem);

      //virtual void nextstyle(style_context* pcontext) override;

      virtual void _001OnTimer(::timer* ptimer) override;

      DECLARE_MESSAGE_HANDLER(on_message_show_window);
      DECLARE_MESSAGE_HANDLER(on_message_set_focus);
      DECLARE_MESSAGE_HANDLER(on_message_kill_focus);
      DECLARE_MESSAGE_HANDLER(on_message_close);
      DECLARE_MESSAGE_HANDLER(_001OnActivate);
      DECLARE_MESSAGE_HANDLER(_001OnMouseActivate);
      DECLARE_MESSAGE_HANDLER(on_message_key_down);
      DECLARE_MESSAGE_HANDLER(on_message_key_up);
      DECLARE_MESSAGE_HANDLER(on_message_left_button_down);
      DECLARE_MESSAGE_HANDLER(on_message_left_button_up);
      DECLARE_MESSAGE_HANDLER(on_message_middle_button_down);
      DECLARE_MESSAGE_HANDLER(on_message_right_button_down);
      DECLARE_MESSAGE_HANDLER(on_message_mouse_move);


      virtual ::item_pointer on_hit_test(const ::point_i32 & point) override;


      virtual ::item current_item() override;
      virtual ::item hover_item() override;


      virtual bool keyboard_focus_is_focusable() override;
      virtual bool keyboard_focus_OnKillFocus(oswindow oswindowNew) override;


      //virtual bool display(int nCmdShow) override;

      virtual bool has_pending_graphical_update() override;


      void on_drop_down(const ::rectangle & rectangleWindow, const ::size & sizeFull);


      //virtual bool get_font(::write_text::font_pointer & spfont, e_font efont, ::user::interaction * pinteraction) override;

      virtual void _on_show_window() override;

   };


} //  namespace user



