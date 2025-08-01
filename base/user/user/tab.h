#pragma once


#include "place_holder_container.h"
#include "auto_hide.h"


namespace user
{


   class tab_callback;


   class CLASS_DECL_BASE tab :
      virtual public place_holder_container,
      virtual public ::user::auto_hide
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


      class CLASS_DECL_BASE erase_tab_exception
      {
      public:

         string m_strHint;

         erase_tab_exception(const ::scoped_string & scopedstrHint)
         {
            m_strHint = scopedstrHint;
         }

      };


      enum_state                                   m_estate;
      ::pointer<tab_data>                          m_pdata;
      ::pointer<::draw2d::graphics_extension>      m_pgraphicsextension;
      bool                                         m_bDisableSavingRestorableTabs;
      ::item_pointer                               m_pitemClick;
      ::item_pointer                               m_pitemTabNearScroll;
      ::item_pointer                               m_pitemTabFarScroll;
      ::write_text::font_pointer                   m_pfontTab;
      ::collection::count                                      m_iRestoredTabCount;
      bool                                         m_bDrawTabAtBackground;
      ::logic::boolean                                    m_bitLastShowTabs;
      int                                          m_iTabSize;
      bool                                         m_bCreatedTabs;
      bool                                         m_bAutoCreateTabsOnCreate;
      //::int_rectangle                              m_rectangleHosting;


      tab();
      ~tab() override;


      void on_initialize_particle() override;


      void destroy() override;


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
      // virtual void set_current_tab_by_index(::collection::index iTab);
      virtual void _001CloseTab(::collection::index iTab);


      void handle(::topic * ptopic, ::handler_context * phandlercontext) override;

      virtual void rotate();

      virtual ::user::interaction * tab_window(::collection::index iTab);
      virtual ::user::place_holder * tab_holder(::collection::index iTab);

      virtual ::user::interaction * pane_window(::collection::index iTab);
      virtual ::user::place_holder * pane_holder(::collection::index iTab);

      virtual ::user::interaction * get_impact_uie();

      virtual void _001SetTabCallback(tab_callback * pcallback);
      virtual bool _001IsAddTab(::collection::index iTab);
      virtual void _001OnDropTab(::collection::index iTab, enum_position eposition);


      virtual atom get_current_tab_id();
      virtual bool set_current_tab_by_id(const ::atom & atom, ::request * prequest = nullptr);


      virtual ::user::tab_pane * get_current_tab();


      virtual ::collection::index get_current_tab_index();
      virtual ::collection::index get_current_visible_tab_index();
      virtual void set_current_tab_by_index(::collection::index iSel);

      virtual ::collection::index tab_index(::user::tab_pane* ptabpane);

      virtual ::collection::index visible_index_index(::collection::index iVisibleIndex);
      virtual ::collection::index index_visible_index(::collection::index iIndex);

      virtual bool contains_tab_with_id(const ::atom & atom);

      virtual ::collection::index id_index(const ::atom & atom);
      virtual ::atom index_id(::collection::index iIndex);

      virtual ::collection::index id_visible_index(const ::atom& atom);
      virtual ::atom visible_index_id(::collection::index iIndex);

      virtual ::collection::count get_tab_count();
      virtual ::collection::count get_visible_tab_count();


      void get_child_rect(::int_rectangle & rectangle) override;


      virtual void _001OnRemoveTab(tab_pane * ptab);

      bool on_click(::item * pitem, ::user::mouse * pmouse) override;

      int auto_hide_threshold_height() override;

      virtual ::user::interaction_array place_holders();
      virtual tab_pane * place_holder_pane(::user::place_holder * pplaceholder);
      virtual tab_pane * top_pane();

      virtual void _001OnTabClick(::collection::index iTab);
      virtual void _001OnTabClose(::collection::index iTab);
      virtual ::user::interaction * GetNotifyWnd();
      ::item_pointer on_hit_test(const ::int_point & point, ::user::e_zorder ezorder) override;
      virtual enum_position DragHitTest(const ::int_point & point);
      virtual void GetDragRect(::int_rectangle & rectangle, enum_position eposition);

      virtual bool get_element_rectangle(::collection::index iTab, ::int_rectangle & rectangle, enum_element eelement);


      virtual void get_title(int iPane,string_array & stra);

      void on_perform_top_down_layout(::draw2d::graphics_pointer & pgraphics) override;

      //void on_layout(::draw2d::graphics_pointer & pgraphics) override;

      virtual void layout_pane(::collection::index iPane, bool bDisplay = false);

      virtual void GetTabClientRect(::int_rectangle & rectangle);

      virtual void GetTabClientRect(::long_long_rectangle & rectangle);

      virtual bool add_tab(const ::scoped_string & scopedstrName, const ::atom & idImpact = nullptr, bool bVisible = true, bool bPermanent = false, ::user::place_holder * pholder = nullptr);

      virtual bool set_tab(const ::scoped_string & scopedstr, const ::atom & idTab = nullptr, bool bVisible = true);

      virtual bool add_tab_with_icon(const ::scoped_string & scopedstrName, const ::scoped_string & scopedstrImage, const ::atom & idImpact = nullptr, bool bVisible = true, bool bPermanent = false, ::user::place_holder * pholder = nullptr);

      virtual bool set_tab_with_icon(const ::scoped_string & scopedstr, const ::scoped_string & scopedstrImage, const ::atom & idTab = nullptr, bool bVisible = true);

      virtual bool erase_tab_by_id(const ::atom & idTab);
      virtual void erase_tab(::collection::index iTab, bool bVisible = true);
      virtual void erase_all_tabs();
      virtual bool show_tab_by_id(const ::atom & idTab, bool bShow = true);
      virtual bool show_pane(::collection::index iPane, bool bShow = true);
      virtual bool hide_tab(::collection::index iTab);


      virtual bool hide_place_holder_by_id(const ::atom & atomTab);


      virtual bool set_title(::collection::index iTab, const ::scoped_string & scopedstr);
      virtual bool set_title_by_id(const ::atom & idTab, const ::scoped_string & scopedstr);


      virtual ::collection::index find_child_pane(::user::interaction * pinteraction);
      virtual void defer_erase_child_pane(::user::interaction * pinteraction);

      void on_erase_child(::user::interaction * pinteraction) override;
      void on_erase_place_holder_child(::user::interaction * pinteraction) override;

      void on_hide_child(::user::interaction * pinteraction) override;
      void on_hide_place_holder_child(::user::interaction * pinteraction) override;

      //virtual ::collection::index id_tab_index(const ::atom & idTab);
      //virtual atom tab_index_id(::collection::index iTab);
      //virtual ::collection::index id_pane(const ::atom & idTab);
      //virtual atom pane_id(::collection::index iPane);

      //virtual ::collection::index tab_pane(::collection::index iTab);
      //virtual ::collection::index pane_tab(::collection::index iPane);


      virtual ::user::tab_pane * get_tab(::collection::index iTab);
      virtual ::user::tab_pane * get_visible_tab(::collection::index iVisibleTab);


      virtual ::user::tab_pane * get_tab_by_id(const ::atom & idTab);
      virtual ::user::tab_pane* create_tab_by_id(const ::atom & idTab);

      virtual void on_change_tab_count(::array < ::user::tab_pane * > array = ::array < ::user::tab_pane * >());

      virtual void get_text_id(string_array & stra);

      virtual void get_prefixed_ci_id(string_array & stra, const ::scoped_string & scopedstrPrefix);
      virtual void get_suffixed_ci_id(string_array & stra, const ::scoped_string & scopedstrSuffix);
      virtual void get_presuffixed_ci_id(string_array & stra, const ::scoped_string & scopedstrPrefix, const ::scoped_string & scopedstrSuffixed);

      virtual void get_begins_ci_eat_id(string_array & stra, const ::scoped_string & scopedstrPrefix);
      virtual void get_ends_ci_eat_id(string_array & stra, const ::scoped_string & scopedstrSuffix);
      virtual void get_begins_ends_ci_eat_id(string_array & stra, const ::scoped_string & scopedstrPrefix, const ::scoped_string & scopedstrSuffixed);

      virtual void _001ConnectParent(::channel * pchannel);


      virtual void create_tabs();
      virtual bool has_restore_tab();
      virtual void get_restore_tab(payload_array & payloada);
      virtual bool matches_restorable_tab(const ::payload & varId, ::user::place_holder * pholder = nullptr);
      virtual ::collection::count open_tabs(const payload_array & payloada);
      virtual ::collection::count restore_tabs();
      virtual void save_restorable_tabs();
      virtual void on_create_tabs();


      void _001OnDraw(::draw2d::graphics_pointer & pgraphics) override;


      virtual void _001OnDrawStandard(::draw2d::graphics_pointer & pgraphics);
      virtual void _001OnDrawSchema01(::draw2d::graphics_pointer & pgraphics);

      void on_timer(::timer * ptimer) override;

      ::int_rectangle hosting_rectangle(::user::enum_layout elayout = ::user::e_layout_design) override;

//     void on_perform_top_down_layout(::draw2d::graphics_pointer & pgraphics) override;


      virtual void _001TabOnDrawSchema01(::draw2d::graphics_pointer & pgraphics);
      virtual void _001OnTabLayout(::draw2d::graphics_pointer & pgraphics);
      
      
      bool on_drag_start(::int_point & pointDrag, ::user::mouse * pmouse, ::item * pitem) override;


      void on_drag_scroll_layout(::draw2d::graphics_pointer & pgraphics) override;

      
      bool drag_shift(::item * pitem, ::user::mouse * pmouse) override;

      
   };


} // namespace user



