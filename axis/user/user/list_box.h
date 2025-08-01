#pragma once


#include "aura/user/user/scroll_base.h"


namespace user
{


   class CLASS_DECL_AXIS list_box :
      virtual public ::user::scroll_base
   {
   public:


      bool                                m_bCaseSensitiveMatch;
      class ::time                            m_timeKillFocus;
      //bool                                m_bPendingKillFocusHiding;
      bool                                m_bMovingComboBox;
      bool                                m_bComboList;
      ::pointer<combo_box>               m_pcombo;
      int                                 m_iScreenMargin;
      int                                 m_iPadding;
      ::int_size                          m_sizeFull;
      int                                 m_iMinListItemCount;
      class ::time                        m_timeShowDropDown;
      class ::time                        m_timeHideDropDown;
      //::item                        m_itemLButtonDown;
      //::user::frame_window *            m_puiDeactivateTogether;
      ::user::interaction *               m_puiDeactivateTogether;
      string_array                    m_straList;
      ::atom_array                    m_atoma;


      class ::time                                m_timeLastVisibilityChange;


      list_box();
      ~list_box() override;

      void on_initialize_particle() override;

      void destroy() override;

      void user_combo_list_common_construct();


      void install_message_routing(::channel * pchannel) override;

      virtual void _001OnNcDraw(::draw2d::graphics_pointer & pgraphics) override;

      virtual void _001OnDraw(::draw2d::graphics_pointer & pgraphics) override;

      virtual void _001OnDrawComboList(::draw2d::graphics_pointer & pgraphics);

      virtual void query_full_size(::draw2d::graphics_pointer& pgraphics, ::int_size * psize);

      ::write_text::font_pointer get_font(style* pstyle, enum_element eelement = e_element_none, ::user::enum_state estate = e_state_none) override;

      virtual int _001GetItemHeight() const;

      virtual void on_change_combo_sel(::collection::index iSel);

      bool pre_create_window(::user::system * pusersystem) override;

      virtual void ensure_item_visible_by_index(::collection::index iItem);

      void on_timer(::timer* ptimer) override;

      void on_layout(::draw2d::graphics_pointer & pgraphics) override;

      DECLARE_MESSAGE_HANDLER(on_message_create);
      DECLARE_MESSAGE_HANDLER(on_message_destroy);
      DECLARE_MESSAGE_HANDLER(on_message_activate);
      DECLARE_MESSAGE_HANDLER(on_message_show_window);
      //DECLARE_MESSAGE_HANDLER(on_message_set_focus);
      //DECLARE_MESSAGE_HANDLER(on_message_kill_focus);
      DECLARE_MESSAGE_HANDLER(on_message_close);
      DECLARE_MESSAGE_HANDLER(_001OnActivate);
      DECLARE_MESSAGE_HANDLER(_001OnMouseActivate);
      DECLARE_MESSAGE_HANDLER(on_message_key_down);
      DECLARE_MESSAGE_HANDLER(on_message_key_up);
      //DECLARE_MESSAGE_HANDLER(on_message_left_button_down);
      //DECLARE_MESSAGE_HANDLER(on_message_left_button_up);
      DECLARE_MESSAGE_HANDLER(on_message_middle_button_down);
      DECLARE_MESSAGE_HANDLER(on_message_right_button_down);
      //DECLARE_MESSAGE_HANDLER(on_message_mouse_move);


      void on_set_keyboard_focus() override;
      void on_kill_keyboard_focus() override;

      ::item_pointer on_hit_test(const ::int_point & point, ::user::e_zorder ezorder) override;


      ::item_pointer current_item() override;
      ::item_pointer hover_item() override;


      bool keyboard_focus_is_focusable() override;
      bool keyboard_focus_OnKillFocus(::oswindow oswindowNew) override;


      //bool has_pending_graphical_update() override;


      void on_drop_down(const ::int_rectangle & rectangleWindow, const ::int_size & sizeFull);


      void _on_show_window() override;


      bool on_set_owner(::user::interaction_base * pprimitive) override;


      void set_current_item(::item * pitem, const ::action_context & context) override;
      virtual void set_current_item_by_atom(const ::atom & atom, const ::action_context& action_context);
      virtual void set_current_item_by_text(const ::scoped_string & scopedstr, const ::action_context& action_context);
      virtual void set_current_item_by_index(::collection::index iIndex, const ::action_context& context);
      virtual string get_current_item_text();
      virtual ::atom get_current_item_id();


      virtual bool _001GetListText(::collection::index iSel, string& str);
      virtual ::collection::index _001FindListText(const ::scoped_string & scopedstr);
      virtual ::collection::count _001GetListCount();


      
      //virtual ::collection::index add_string(const ::scoped_string & scopedstrString, uptr dwItemData = 0);
      //virtual ::collection::index add_string(const ::scoped_string & scopedstrString, const ::scoped_string & scopedstrValue);
      virtual ::collection::index add_item(const ::scoped_string & scopedstr, const ::atom & atom);

      
      virtual ::collection::index erase_item_at(::collection::index nIndex);
      virtual ::collection::index insert_item_at(::collection::index nIndex, const ::scoped_string & scopedstrString);


      virtual void reset_content();


      void handle(::topic * ptopic, ::handler_context * phandlercontext) override;


   };


} //  namespace user



