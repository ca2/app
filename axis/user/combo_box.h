#pragma once


namespace user
{


   class list_box;


   class CLASS_DECL_AXIS combo_box :
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


      ::size_i32                    m_sizeFull;
      //string                        m_strText;
      ::duration                      m_durationShowComboList;
      __pointer(list_box)           m_plistbox;

      ::type                        m_typeListBox;

      e_style                       m_estyle;

      bool                          m_bEdit;
      e_data_mode                   m_edatamode;


      combo_box();
      virtual ~combo_box();


      void user_combo_box_common_construct();


      void install_message_routing(::channel * pchannel) override;


      virtual ::write_text::font_pointer get_font(style* pstyle, enum_element eelement = e_element_none, ::user::enum_state estate = e_state_none) const override;


      virtual void _000OnDraw(::draw2d::graphics_pointer & pgraphics) override;
      virtual void _001OnDraw(::draw2d::graphics_pointer & pgraphics) override;
      virtual void _001OnDrawCombo(::draw2d::graphics_pointer & pgraphics);
      virtual void _001OnDrawStaticText(::draw2d::graphics_pointer & pgraphics);

      virtual enum_input_type preferred_input_type() const override;

      virtual void get_simple_drop_down_open_arrow_polygon(point_f64_array& pointa) override;

      virtual bool has_action_hover();




      virtual void _001GetText(string & str) const override;
      virtual void _001SetText(const ::string & str, const ::action_context & action_context) override;


      virtual bool _001GetListText(index iSel, string & str) const;
      virtual index _001FindListText(const ::string & str) const;
      virtual count _001GetListCount() const;

      //virtual bool create_interaction(::user::interaction * pinteractionParent, const ::id & id) override;

      virtual bool get_element_rect(RECTANGLE_I32 * prectangle, enum_element eelement) override;

      virtual void on_hit_test(::item & item) override;

      virtual bool plain_edit_is_enabled() override;

      DECLARE_MESSAGE_HANDLER(on_message_mouse_move);
      DECLARE_MESSAGE_HANDLER(on_message_mouse_leave);
      DECLARE_MESSAGE_HANDLER(on_message_left_button_down);
      DECLARE_MESSAGE_HANDLER(on_message_left_button_up);
      DECLARE_MESSAGE_HANDLER(on_message_left_button_double_click);
      DECLARE_MESSAGE_HANDLER(on_message_key_down);
      DECLARE_MESSAGE_HANDLER(on_message_key_up);
      DECLARE_MESSAGE_HANDLER(on_message_show_window);
      DECLARE_MESSAGE_HANDLER(on_message_move);

      virtual void _001ShowDropDown(bool bShow = true);
      virtual void _001ToggleDropDown();


      void on_set_keyboard_focus() override;
      void on_kill_keyboard_focus() override;


      virtual void defer_create_list_box();

      virtual bool has_text_input() override;
      virtual bool is_drop_down();



      virtual void on_layout(::draw2d::graphics_pointer & pgraphics) override;

      virtual void plain_edit_on_after_change_text(::draw2d::graphics_pointer& pgraphics, const ::action_context & action_context) override;

      virtual void handle(::topic * ptopic, ::context * pcontext) override;



      //virtual bool create_interaction(::user::interaction * puiParent, const ::id & id) override;

      //::count get_count();
      //::item current_item() override;
      void set_current_item(const ::item & item, const ::action_context & actioncontext) override;


      virtual string get_current_item_string_value();
      virtual void set_current_item_by_data(uptr u, const ::action_context & action_context);
      virtual void set_current_item_by_string_value(const ::string & strValue, const ::action_context & action_context);


//      LCID GetLocale();
  //    LCID SetLocale(LCID nNewLocale);
      index GetTopIndex();
      index SetTopIndex(index nIndex);
      index InitStorage(::count nItems, ::u32 nBytes);
      void SetHorizontalExtent(::u32 nExtent);
      ::u32 GetHorizontalExtent();
      i32 SetDroppedWidth(::u32 nWidth);
      i32 GetDroppedWidth();

//#if defined(WINDOWS_DESKTOP) && (WINVER >= 0x0500)
//      bool GetComboBoxInfo(PCOMBOBOXINFO pcbi);
//#endif   // WINVER >= 0x0500

      // for edit control
      bool GetEditSel(strsize & nStartChar, strsize & nEndChar);
      bool LimitText(strsize nMaxChars);
      bool SetEditSel(strsize nStartChar, strsize nEndChar);

      // for combobox item
      uptr GetItemData(index nIndex);
      index SetItemData(index nIndex, uptr dwItemData);
      void * GetItemDataPtr(index nIndex);
      index SetItemDataPtr(index nIndex, void * pData);
      index GetLBText(index nIndex, char * pszText);

      void GetLBText(index nIndex, string & rString);
      strsize GetLBTextLen(index nIndex);

      i32 SetItemHeight(index nIndex, ::u32 cyItemHeight);
      i32 GetItemHeight(index nIndex);
      index FindStringExact(index nIndexStart, const ::string & pszFind);

      i32 SetExtendedUI(bool bExtended = true);
      bool GetExtendedUI();
      void GetDroppedControlRect(RECTANGLE_I32 * prectangle);

      bool GetDroppedState();

      // Operations
      // for drop-down combo boxes
      void ShowDropDown(bool bShowIt = true);

      // manipulating listbox items
      virtual index add_string(const ::string & pszString, uptr dwItemData = 0);
      virtual index add_string(const ::string & pszString, const string& strValue);



      virtual index delete_string(index nIndex);
      virtual index insert_string(index nIndex, const ::string & pszString);

      virtual void reset_content();
      index Dir(index attr, const ::string & pszWildCard);



      void clear();
      void copy();
      void Cut();
      void Paste();


      // Overridables (must override draw, measure and compare for owner draw)
//#ifdef WINDOWS_DESKTOP
//      virtual void DrawItem(LPDRAWITEMSTRUCT pDrawItemStruct);
//
//      virtual void MeasureItem(LPMEASUREITEMSTRUCT pMeasureItemStruct);
//
//      virtual i32 CompareItem(LPCOMPAREITEMSTRUCT pCompareItemStruct);
//
//      virtual void DeleteItem(LPDELETEITEMSTRUCT pDeleteItemStruct);
//
//#endif

      //virtual bool OnChildNotify(::user::message * pusermessage) override;


      //virtual ::color::color get_action_hover_border_color() override;



      virtual bool keyboard_focus_is_focusable() const override;


      //virtual void handle(::topic * ptopic, ::context * pcontext) override;


   };


} //  namespace user



