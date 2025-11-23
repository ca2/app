#pragma once


namespace user
{


   class list_box;


   class CLASS_DECL_AURA combo_box :
      virtual public ::user::plain_edit
   {
   public:


      

      enum e_style
      {

         style_verisimple,
         style_simply,

      };

      enum e_data_mode
      {

         data_mode_opaque,
         data_mode_string

      };


      ::size                     m_sizeFull;
      string                     m_strText;
      bool                       m_bCaseSensitiveMatch;

      ::pointer<list_box>            m_plist;

      ::type              m_typeComboList;

      e_style                    m_estyle;

      bool                       m_bEdit;
      e_data_mode                m_edatamode;
      string_array_base                    m_straList;
      string_array_base                    m_straValue;


      combo_box();
      virtual ~combo_box();


      void user_combo_box_common_construct();


      void install_message_routing(::channel * pchannel) override;


      virtual ::write_text::font_pointer get_font(style* pstyle, enum_element eelement = e_element_none, estate estate = e_state_none) const override;


      virtual void _000OnDraw(::draw2d::graphics_pointer & pgraphics) override;
      virtual void _001OnDraw(::draw2d::graphics_pointer & pgraphics) override;
      //virtual void _001OnDrawVerisimple(::draw2d::graphics_pointer & pgraphics);
      virtual void _001OnDrawCombo(::draw2d::graphics_pointer & pgraphics);
      virtual void _001OnDrawStaticText(::draw2d::graphics_pointer & pgraphics);

      virtual void get_simple_drop_down_open_arrow_polygon(point_array& pointa) override;

      virtual void set_current_item(const ::item & item, const ::action_context & action_context) override;

      virtual bool has_action_hover();

      virtual void set_current_item_by_data(uptr u, const ::action_context & action_context);
      
      virtual void set_current_item_by_string_value(const ::scoped_string & scopedstrValue, const ::action_context & action_context);
      
      virtual string get_current_item_string_value();



      virtual void get_text(string & str) const override;
      virtual void set_text(const ::scoped_string & scopedstr, const ::action_context & action_context) override;


      virtual bool _001GetListText(::collection::index iSel, string & str) const;
      virtual ::collection::index _001FindListText(const ::scoped_string & scopedstr) const;
      virtual count _001GetListCount() const;

      virtual bool create_control(class control_descriptor * pdescriptor) override;

      virtual bool get_element_rectangle(RECT32 * prect, enum_element eelement) override;

      virtual ::item_pointer on_hit_test(const ::int_point & point, ::user::e_zorder ezorder) override;

      virtual bool plain_edit_is_enabled() override;

      DECLARE_MESSAGE_HANDLER(on_message_mouse_move);
      DECLARE_MESSAGE_HANDLER(on_message_mouse_leave);
      DECLARE_MESSAGE_HANDLER(on_message_left_button_down);
      DECLARE_MESSAGE_HANDLER(on_message_left_button_up);
      DECLARE_MESSAGE_HANDLER(on_message_left_button_double_click);
      DECLARE_MESSAGE_HANDLER(on_message_key_down);
      DECLARE_MESSAGE_HANDLER(on_message_key_up);
      DECLARE_MESSAGE_HANDLER(on_message_set_focus);
      DECLARE_MESSAGE_HANDLER(on_message_kill_focus);
      DECLARE_MESSAGE_HANDLER(on_message_show_window);
      DECLARE_MESSAGE_HANDLER(on_message_move);

      virtual void _001ShowDropDown(bool bShow = true);
      virtual void _001ToggleDropDown();


      virtual void defer_create_combo_list();

      virtual bool has_text_input() override;
      virtual bool is_drop_down();



      virtual void on_layout(::draw2d::graphics_pointer & pgraphics) override;

      virtual void plain_edit_on_after_change_text(::draw2d::graphics_pointer& pgraphics, const ::action_context & action_context) override;

      virtual void handle(::topic * ptopic, ::handler_context * phandlercontext) override;



      virtual bool create_window(::user::interaction * puiParent, const ::atom & atom) override;

      //::collection::count get_count();
      //index current_item();
      //index set_current_item(index nSelect);
      LCID GetLocale();
      LCID SetLocale(LCID nNewLocale);
      ::collection::index GetTopIndex();
      ::collection::index SetTopIndex(index nIndex);
      ::collection::index InitStorage(::collection::count nItems, unsigned int nBytes);
      void SetHorizontalExtent(unsigned int nExtent);
      unsigned int GetHorizontalExtent();
      int SetDroppedWidth(unsigned int nWidth);
      int GetDroppedWidth();

#if defined(WINDOWS_DESKTOP) && (WINVER >= 0x0500)
      bool GetComboBoxInfo(PCOMBOBOXINFO pcbi);
#endif   // WINVER >= 0x0500

      // for edit control
      bool GetEditSel(character_count & nStartChar, character_count & nEndChar);
      bool LimitText(character_count nMaxChars);
      bool SetEditSel(character_count nStartChar, character_count nEndChar);

      // for combobox item
      uptr GetItemData(index nIndex);
      ::collection::index SetItemData(index nIndex, uptr dwItemData);
      void * GetItemDataPtr(index nIndex);
      ::collection::index SetItemDataPtr(index nIndex, void * pData);
      ::collection::index GetLBText(index nIndex, char * pszText);

      void GetLBText(index nIndex, string & rString);
      character_count GetLBTextLen(index nIndex);

      int SetItemHeight(index nIndex, unsigned int cyItemHeight);
      int GetItemHeight(index nIndex);
      ::collection::index FindStringExact(index nIndexStart, const ::scoped_string & scopedstrFind);

      int SetExtendedUI(bool bExtended = true);
      bool GetExtendedUI();
      void GetDroppedControlRect(RECT32 * prect);

      bool GetDroppedState();

      
      // for drop-down combo boxes
      void ShowDropDown(bool bShowIt = true);

      // manipulating listbox items
      virtual ::collection::index AddString(const ::scoped_string & scopedstrString, uptr dwItemData = 0);
      virtual ::collection::index AddString(const ::scoped_string & scopedstrString, const ::scoped_string & scopedstrValue);



      ::collection::index DeleteString(index nIndex);
      ::collection::index InsertString(index nIndex, const ::scoped_string & scopedstrString);

      void reset_content();
      ::collection::index Dir(index attr, const ::scoped_string & scopedstrWildCard);



      void clear();
      void copy();
      void Cut();
      void Paste();


      // Overridables (must override draw, measure and compare for owner draw)
#ifdef WINDOWS_DESKTOP
      virtual void DrawItem(LPDRAWITEMSTRUCT pDrawItemStruct);

      virtual void MeasureItem(LPMEASUREITEMSTRUCT pMeasureItemStruct);

      virtual int CompareItem(LPCOMPAREITEMSTRUCT pCompareItemStruct);

      virtual void DeleteItem(LPDELETEITEMSTRUCT pDeleteItemStruct);

#endif

      virtual bool OnChildNotify(::user::message * pusermessage) override;


      //virtual color32_t get_action_hover_border_color() override;



      virtual bool keyboard_focus_is_focusable() override;


      virtual void handle(::topic * ptopic, ::handler_context * phandlercontext) override;


   };


} //  namespace user



