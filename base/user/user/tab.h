#pragma once


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






      class CLASS_DECL_BASE remove_tab_exception
      {
      public:

         string m_strHint;

         remove_tab_exception(const char * pszHint)
         {
            m_strHint = pszHint;
         }

      };


      enum_state                       m_estate;
      __pointer(tab_data)              m_pdata;
      ::draw2d::graphics_extension     m_dcextension;
      bool                             m_bDisableSavingRestorableTabs;
      bool                             m_bShowTabs;
      bool                             m_bNoTabs;
      item                             m_itemClick;
      ::write_text::font_pointer           m_pfontTab;
      //__pointer(::create)              m_pcreate;
      ::count                          m_iRestoredTabCount;
      bool                             m_bDrawTabAtBackground;
      ::logic::bit                     m_bitLastShowTabs;
      enum_display                        m_edisplayParentFrameAutoHide;
      int                              m_iTabScroll;
      int                              m_iTabScrollMax;
      int                              m_iTabSize;
      bool                             m_bMouseDown;


      tab();
      virtual ~tab();


      virtual void install_message_routing(::channel * pchannel) override;


      virtual enum_element get_default_element() const override;

      DECL_GEN_SIGNAL(on_message_left_button_down);
      DECL_GEN_SIGNAL(on_message_left_button_up);
      DECL_GEN_SIGNAL(_001OnMouseMove);
      DECL_GEN_SIGNAL(_001OnMouseLeave);
      DECL_GEN_SIGNAL(on_message_create);
      DECL_GEN_SIGNAL(_001OnShowWindow);
      DECL_GEN_SIGNAL(_001OnSize);
      DECL_GEN_SIGNAL(_001OnStartTabDrag);
      DECL_GEN_SIGNAL(_001OnAppLanguage);


      tab_data * get_data();


      virtual void on_change_cur_sel();

      virtual void  _001SetVertical(bool bSet = true);
      virtual void _001SelectTab(::index iTab);
      virtual void _001CloseTab(::index iTab);


      virtual void on_subject(::subject::subject * psubject, ::subject::context * pcontext) override;

      virtual void rotate();

      virtual ::user::interaction * tab_window(::index iTab);
      virtual ::user::place_holder * tab_holder(::index iTab);

      virtual ::user::interaction * pane_window(::index iTab);
      virtual ::user::place_holder * pane_holder(::index iTab);

      //virtual void _000OnMouse(::message::mouse * pmouse) override;

      virtual ::user::interaction * get_view_uie();

      virtual void _001SetTabCallback(tab_callback * pcallback);
      virtual bool _001IsAddTab(::index iTab);
      virtual void _001OnDropTab(::index iTab, enum_position eposition);
      virtual bool set_cur_tab_by_id(id id, ::create * pcreate = nullptr);

      virtual id get_cur_tab_id();
      virtual id get_current_id();


      virtual void get_child_rect(RECTANGLE_I32 * prectangle) override;


      virtual void _001OnRemoveTab(tab_pane * ptab);

      virtual ::index _001GetSel();
      virtual void _001SetSel(::index iSel);

      virtual ::count _001GetPaneCount();

      virtual void _001OnTabClick(::index iTab);
      virtual void _001OnTabClose(::index iTab);
      virtual ::user::interaction * GetNotifyWnd();
      virtual void on_hit_test(::user::item & item) override;
      virtual enum_position DragHitTest(const ::point_i32 & point);
      virtual void GetDragRect(RECTANGLE_I32 * prectangle, enum_position eposition);

      virtual bool get_element_rect(::index iTab, RECTANGLE_I32 * prectangle, enum_element eelement);


      virtual void get_title(int iPane,string_array & stra);

      virtual void on_layout(::draw2d::graphics_pointer & pgraphics) override;
      virtual void layout_pane(index iPane, bool bDisplay = false);

      virtual void GetTabClientRect(RECTANGLE_I32 * prectangle);

      virtual void GetTabClientRect(RECTANGLE_I64 * prectangle);


      virtual bool add_tab(const char * pcsz, id idTab = id(), bool bVisible = true, bool bPermanent = false, ::user::place_holder * pholder = nullptr);

      virtual bool set_tab(const char * pcsz, id idTab = id(), bool bVisible = true);

      virtual bool add_image_tab(const char * pcsz, const char * pszImage, id idTab = id(), bool bVisible = true, bool bPermanent = false);

      virtual bool set_image_tab(const char * pcsz, const char * pszImage, id idTab = id(), bool bVisible = true);

      virtual bool remove_tab_by_id(id idTab = id());
      virtual void remove_tab(::index iTab, bool bVisible = true);
      virtual void remove_all_tabs();
      virtual bool show_tab_by_id(id idTab = id(), bool bShow = true);
      virtual bool show_pane(::index iPane, bool bShow = true);
      virtual bool hide_tab(::index iTab);


      virtual bool set_title(::index iTab, const char * psz);
      virtual bool SetTitleById(id id, const char * psz);

      virtual ::count get_tab_count();
      virtual ::count get_pane_count();

      virtual index find_child_pane(::user::interaction * pinteraction);
      virtual void defer_remove_child_pane(::user::interaction * pinteraction);

      virtual void on_remove_child(::user::interaction * pinteraction) override;
      virtual void on_remove_place_holder_child(::user::interaction * pinteraction) override;

      virtual void on_hide_child(::user::interaction * pinteraction) override;
      virtual void on_hide_place_holder_child(::user::interaction * pinteraction) override;

      virtual ::index id_tab(id id);
      virtual id tab_id(::index iTab);
      virtual ::index id_pane(id id);
      virtual id pane_id(::index iPane);

      virtual ::index tab_pane(index iTab);
      virtual ::index pane_tab(index iPane);


      virtual ::user::tab_pane * get_pane(::index iPane);
      virtual ::user::tab_pane * get_tab(::index iTab);


      virtual ::user::tab_pane * get_pane_by_id(id id);
      virtual ::user::tab_pane * create_pane_by_id(id id);
      virtual ::index create_tab_by_id(id id);

      virtual void on_change_pane_count(::array < ::user::tab_pane * > array = ::array < ::user::tab_pane * >());

      virtual void get_text_id(string_array & stra);

      virtual void get_prefixed_ci_id(string_array & stra, const char * pszPrefix);
      virtual void get_suffixed_ci_id(string_array & stra, const char * pszSuffix);
      virtual void get_presuffixed_ci_id(string_array & stra, const char * pszPrefix, const char * pszSuffixed);

      virtual void get_begins_ci_eat_id(string_array & stra, const char * pszPrefix);
      virtual void get_ends_ci_eat_id(string_array & stra, const char * pszSuffix);
      virtual void get_begins_ends_ci_eat_id(string_array & stra, const char * pszPrefix, const char * pszSuffixed);

      virtual void _001ConnectParent(::channel * pchannel);


      virtual bool has_restore_tab();
      virtual void get_restore_tab(var_array & vara);
      virtual bool matches_restorable_tab(const ::payload & varId, ::user::place_holder * pholder = nullptr);
      virtual ::count open_tabs(const var_array & vara);
      virtual ::count restore_tabs();
      virtual void save_restorable_tabs();
      virtual void on_create_tabs();


      virtual void _001OnDraw(::draw2d::graphics_pointer & pgraphics) override;


      virtual void _001OnDrawStandard(::draw2d::graphics_pointer & pgraphics);
      virtual void _001OnDrawSchema01(::draw2d::graphics_pointer & pgraphics);

      virtual void _001OnTimer(::timer * ptimer) override;

      virtual bool defer_handle_auto_hide_tabs(bool bLayout = true);

      virtual bool has_tab_scrolling() const;

   };


} // namespace user


