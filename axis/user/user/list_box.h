#pragma once


#include "aura/user/user/scroll_base.h"


namespace user
{


   class CLASS_DECL_AXIS list_box :
      virtual public ::user::scroll_base
   {
   public:


      bool                                m_bCaseSensitiveMatch;
      ::duration                            m_durationKillFocus;
      bool                                m_bPendingKillFocusHiding;
      bool                                m_bMovingComboBox;
      bool                                m_bComboList;
      __pointer(combo_box)                m_pcombo;
      int                                 m_iBorder;
      int                                 m_iPadding;
      ::size_i32                          m_sizeFull;
      int                                 m_iMinListItemCount;
      //::item                        m_itemLButtonDown;
      //::user::frame_window *            m_puiDeactivateTogether;
      ::user::interaction *               m_puiDeactivateTogether;
      string_array                    m_straList;
      string_array                    m_straValue;


      ::duration                                m_durationLastVisibilityChange;


      list_box();
      virtual ~list_box();


      void user_combo_list_common_construct();


      void install_message_routing(::channel * pchannel) override;

      virtual void _001OnDraw(::draw2d::graphics_pointer & pgraphics) override;

      virtual void _001OnDrawComboList(::draw2d::graphics_pointer & pgraphics);

      virtual void query_full_size(::draw2d::graphics_pointer& pgraphics, SIZE_I32 * psize);

      virtual ::write_text::font_pointer get_font(style* pstyle, enum_element eelement = e_element_none, ::user::enum_state estate = e_state_none) const override;

      virtual i32 _001GetItemHeight() const;

      virtual void on_change_combo_sel(index iSel);

      virtual bool pre_create_window(::user::system * pusersystem) override;

      virtual void _001EnsureVisible(index iItem);

      virtual void _001OnTimer(::timer* ptimer) override;

       void on_layout(::draw2d::graphics_pointer & pgraphics) override;

      DECLARE_MESSAGE_HANDLER(on_message_create);
      DECLARE_MESSAGE_HANDLER(on_message_destroy);
      DECLARE_MESSAGE_HANDLER(on_message_show_window);
      DECLARE_MESSAGE_HANDLER(on_message_set_focus);
      DECLARE_MESSAGE_HANDLER(on_message_kill_focus);
      DECLARE_MESSAGE_HANDLER(on_message_close);
      DECLARE_MESSAGE_HANDLER(_001OnActivate);
      DECLARE_MESSAGE_HANDLER(_001OnMouseActivate);
      DECLARE_MESSAGE_HANDLER(on_message_key_down);
      DECLARE_MESSAGE_HANDLER(on_message_key_up);
      //DECLARE_MESSAGE_HANDLER(on_message_left_button_down);
      //DECLARE_MESSAGE_HANDLER(on_message_left_button_up);
      DECLARE_MESSAGE_HANDLER(on_message_middle_button_down);
      DECLARE_MESSAGE_HANDLER(on_message_right_button_down);
      DECLARE_MESSAGE_HANDLER(on_message_mouse_move);


      ::item_pointer on_hit_test(const ::point_i32 & point) override;


      ::item_pointer current_item() override;
      ::item_pointer hover_item() override;


      bool keyboard_focus_is_focusable() const override;
      bool keyboard_focus_OnKillFocus(::oswindow oswindowNew) override;


      bool has_pending_graphical_update() override;


      void on_drop_down(const ::rectangle_i32 & rectangleWindow, const ::size_i32 & sizeFull);


      void _on_show_window() override;


      bool on_set_owner(::user::primitive * pprimitive) override;


      void set_current_item(::item * pitem, const ::action_context & context) override;
      virtual void set_current_item_by_data(uptr u, const ::action_context& action_context);
      virtual void set_current_item_by_string_value(const string& strValue, const ::action_context& action_context);
      virtual string get_current_item_string_value();


      virtual bool _001GetListText(index iSel, string& str) const;
      virtual index _001FindListText(const string& str) const;
      virtual count _001GetListCount() const;


      
      virtual index add_string(const ::string & pszString, uptr dwItemData = 0);
      virtual index add_string(const ::string & pszString, const string& strValue);

      
      virtual index delete_string(index nIndex);
      virtual index insert_string(index nIndex, const ::string & pszString);


      virtual void reset_content();


      void handle(::topic * ptopic, ::context * pcontext) override;


   };


} //  namespace user


