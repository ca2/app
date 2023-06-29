#pragma once


#include "place_holder_container.h"


namespace user
{


   class tab_callback;


   class CLASS_DECL_BASE tab :
      virtual public ::user::interaction,
      virtual public place_holder_container
   {
   public:


      enum enum_state
      {

         e_state_initial,
         state_close_button_down,
         state_other_tab_button_down,
         state_drag_commanded,
         state_drag_started

      };

      enum e_message
      {

         message_start_tab_drag = WM_USER + 223 + 2000 + 77 + 51,

      };


      class CLASS_DECL_BASE erase_tab_exception
      {
      public:

         string m_strHint;

         erase_tab_exception(const ::string & pszHint)
         {
            m_strHint = pszHint;
         }

      };


      enum_state                                   m_estate;
      ::pointer<tab_data>                          m_pdata;
      ::pointer<::draw2d::graphics_extension>      m_pgraphicsextension;
      bool                                         m_bDisableSavingRestorableTabs;
      bool                                         m_bEffectiveVisibleTabs;
      bool                                         m_bTabVisibilityChanging;
      bool                                         m_bVisibleTabs;
      bool                                         m_bOverrideVisibleTabs;
      bool                                         m_bForceNoTabs;
      bool                                         m_bHideTabsOnFullScreenOrTransparentFrame;
      class ::time                                 m_timeLastTabVisibilityChange;
      ::item_pointer                               m_pitemClick;
      ::write_text::font_pointer                   m_pfontTab;
      ::count                                      m_iRestoredTabCount;
      bool                                         m_bDrawTabAtBackground;
      ::tristate                                   m_bitLastShowTabs;
      int                                          m_iTabSize;
      bool                                         m_bCreatedTabs;
      bool                                         m_bAutoCreateTabsOnCreate;


      tab();
      ~tab() override;


      void on_initialize_particle() override;


      void install_message_routing(::channel * pchannel) override;


      enum_element get_default_element() override;

      DECLARE_MESSAGE_HANDLER(on_message_create);
      DECLARE_MESSAGE_HANDLER(on_message_left_button_down);
      DECLARE_MESSAGE_HANDLER(on_message_left_button_up);
      DECLARE_MESSAGE_HANDLER(on_message_left_button_double_click);
      DECLARE_MESSAGE_HANDLER(on_message_mouse_move);
      DECLARE_MESSAGE_HANDLER(on_message_mouse_leave);
      DECLARE_MESSAGE_HANDLER(on_message_show_window);
      DECLARE_MESSAGE_HANDLER(on_message_size);
      DECLARE_MESSAGE_HANDLER(_001OnStartTabDrag);
      DECLARE_MESSAGE_HANDLER(_001OnAppLanguage);


      inline tab_data * get_data() { return m_pdata; }

      virtual void on_change_cur_sel();

      virtual void on_after_change_cur_sel();

      virtual void  _001SetVertical(bool bSet = true);
      // virtual void set_current_tab_by_index(::index iTab);
      virtual void _001CloseTab(::index iTab);


      void handle(::topic * ptopic, ::context * pcontext) override;

      virtual void rotate();

      virtual ::user::interaction * tab_window(::index iTab);
      virtual ::user::place_holder * tab_holder(::index iTab);

      virtual ::user::interaction * pane_window(::index iTab);
      virtual ::user::place_holder * pane_holder(::index iTab);

      virtual ::user::interaction * get_impact_uie();

      virtual void _001SetTabCallback(tab_callback * pcallback);
      virtual bool _001IsAddTab(::index iTab);
      virtual void _001OnDropTab(::index iTab, enum_position eposition);


      virtual atom get_current_tab_id();
      virtual bool set_current_tab_by_id(const ::atom & atom, ::request * prequest = nullptr);


      virtual ::user::tab_pane * get_current_tab();


      virtual ::index get_current_tab_index();
      virtual ::index get_current_visible_tab_index();
      virtual void set_current_tab_by_index(::index iSel);

      virtual ::index tab_index(::user::tab_pane* ptabpane);

      virtual ::index visible_index_index(::index iVisibleIndex);
      virtual ::index index_visible_index(::index iIndex);

      virtual ::index id_index(const ::atom & atom);
      virtual ::atom index_id(::index iIndex);

      virtual ::index id_visible_index(const ::atom& atom);
      virtual ::atom visible_index_id(::index iIndex);

      virtual ::count get_tab_count();
      virtual ::count get_visible_tab_count();


      void get_child_rect(::rectangle_i32 & rectangle) override;


      virtual void _001OnRemoveTab(tab_pane * ptab);


      virtual void _001OnTabClick(::index iTab);
      virtual void _001OnTabClose(::index iTab);
      virtual ::user::interaction * GetNotifyWnd();
      ::item_pointer on_hit_test(const ::point_i32 & point, ::user::e_zorder ezorder) override;
      virtual enum_position DragHitTest(const ::point_i32 & point);
      virtual void GetDragRect(::rectangle_i32 & rectangle, enum_position eposition);

      virtual bool get_element_rect(::index iTab, ::rectangle_i32 & rectangle, enum_element eelement);


      virtual void get_title(int iPane,string_array & stra);

      void on_perform_top_down_layout(::draw2d::graphics_pointer & pgraphics) override;

      //void on_layout(::draw2d::graphics_pointer & pgraphics) override;

      virtual void layout_pane(index iPane, bool bDisplay = false);

      virtual void GetTabClientRect(::rectangle_i32 & rectangle);

      virtual void GetTabClientRect(::rectangle_i64 & rectangle);

      virtual bool add_tab(const ::string & strName, const ::atom & idImpact = nullptr, bool bVisible = true, bool bPermanent = false, ::user::place_holder * pholder = nullptr);

      virtual bool set_tab(const ::string & pcsz, const ::atom & idTab = nullptr, bool bVisible = true);

      virtual bool add_tab_with_icon(const ::string & strName, const ::string & strImage, const ::atom & idImpact = nullptr, bool bVisible = true, bool bPermanent = false, ::user::place_holder * pholder = nullptr);

      virtual bool set_tab_with_icon(const ::string & pcsz, const ::string & pszImage, const ::atom & idTab = nullptr, bool bVisible = true);

      virtual bool erase_tab_by_id(const ::atom & idTab);
      virtual void erase_tab(::index iTab, bool bVisible = true);
      virtual void erase_all_tabs();
      virtual bool show_tab_by_id(const ::atom & idTab, bool bShow = true);
      virtual bool show_pane(::index iPane, bool bShow = true);
      virtual bool hide_tab(::index iTab);


      virtual bool hide_place_holder_by_id(const ::atom & atomTab);


      virtual bool set_title(::index iTab, const ::string & psz);
      virtual bool set_title_by_id(const ::atom & idTab, const ::string & psz);


      virtual index find_child_pane(::user::interaction * pinteraction);
      virtual void defer_erase_child_pane(::user::interaction * pinteraction);

      void on_erase_child(::user::interaction * pinteraction) override;
      void on_erase_place_holder_child(::user::interaction * pinteraction) override;

      void on_hide_child(::user::interaction * pinteraction) override;
      void on_hide_place_holder_child(::user::interaction * pinteraction) override;

      //virtual ::index id_tab_index(const ::atom & idTab);
      //virtual atom tab_index_id(::index iTab);
      //virtual ::index id_pane(const ::atom & idTab);
      //virtual atom pane_id(::index iPane);

      //virtual ::index tab_pane(index iTab);
      //virtual ::index pane_tab(index iPane);


      virtual ::user::tab_pane * get_tab(::index iTab);
      virtual ::user::tab_pane * get_visible_tab(::index iVisibleTab);


      virtual ::user::tab_pane * get_tab_by_id(const ::atom & idTab);
      virtual ::user::tab_pane* create_tab_by_id(const ::atom & idTab);

      virtual void on_change_tab_count(::array < ::user::tab_pane * > array = ::array < ::user::tab_pane * >());

      virtual void get_text_id(string_array & stra);

      virtual void get_prefixed_ci_id(string_array & stra, const ::string & pszPrefix);
      virtual void get_suffixed_ci_id(string_array & stra, const ::string & pszSuffix);
      virtual void get_presuffixed_ci_id(string_array & stra, const ::string & pszPrefix, const ::string & pszSuffixed);

      virtual void get_begins_ci_eat_id(string_array & stra, const ::string & pszPrefix);
      virtual void get_ends_ci_eat_id(string_array & stra, const ::string & pszSuffix);
      virtual void get_begins_ends_ci_eat_id(string_array & stra, const ::string & pszPrefix, const ::string & pszSuffixed);

      virtual void _001ConnectParent(::channel * pchannel);


      virtual void create_tabs();
      virtual bool has_restore_tab();
      virtual void get_restore_tab(payload_array & payloada);
      virtual bool matches_restorable_tab(const ::payload & varId, ::user::place_holder * pholder = nullptr);
      virtual ::count open_tabs(const payload_array & payloada);
      virtual ::count restore_tabs();
      virtual void save_restorable_tabs();
      virtual void on_create_tabs();


      void _001OnDraw(::draw2d::graphics_pointer & pgraphics) override;


      virtual void _001OnDrawStandard(::draw2d::graphics_pointer & pgraphics);
      virtual void _001OnDrawSchema01(::draw2d::graphics_pointer & pgraphics);

      void _001OnTimer(::timer * ptimer) override;

      virtual bool is_top_level_full_screen_or_transparent();

      virtual bool full_screen_or_transparent_frame_tab_visibility();

      virtual void calculate_tab_visibility();


   };


} // namespace user



