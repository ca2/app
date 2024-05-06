#pragma once


#include "aura/user/user/plain_edit.h"


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

//enum e_data_mode
//{
//
//   data_mode_opaque,
//   data_mode_string
//
//};
//

      ::size_i32                    m_sizeFull;
      //string                        m_strText;
      class ::time                      m_timeShowComboList;
      ::pointer<list_box>          m_plistbox;

      ::type_atom                   m_typeatomListBox;

      e_style                       m_estyle;

      bool                          m_bEdit;
      //e_data_mode                   m_edatamode;


      combo_box();
      ~combo_box() override;


      void user_combo_box_common_construct();


      void install_message_routing(::channel * pchannel) override;


      ::pointer < ::particle > clone() override;


      ::write_text::font_pointer get_font(style* pstyle, enum_element eelement = e_element_none, ::user::enum_state estate = e_state_none) override;


      void _000OnDraw(::draw2d::graphics_pointer & pgraphics) override;
      void _001OnDraw(::draw2d::graphics_pointer & pgraphics) override;
      virtual void _001OnDrawCombo(::draw2d::graphics_pointer & pgraphics);
      virtual void _001OnDrawStaticText(::draw2d::graphics_pointer & pgraphics);

      void _001OnNcPostDraw(::draw2d::graphics_pointer & pgraphics) override;

      virtual enum_input_type preferred_input_type() override;

      virtual void get_simple_drop_down_open_arrow_polygon(point_f64_array& pointa) override;

      virtual bool has_action_hover();




      virtual void _001GetText(string & str) override;
      virtual void _001SetText(const ::string & str, const ::action_context & action_context) override;


      virtual bool _001GetListText(::raw::index iSel, string & str) const;
      virtual ::raw::index _001FindListText(const ::string & str) const;
      virtual ::raw::count _001GetListCount() const;

      //virtual bool create_interaction(::user::interaction * pinteractionParent, const ::atom & atom) override;

      bool get_element_rectangle(::rectangle_i32 & prectangle, enum_element eelement) override;

      ::item_pointer on_hit_test(const ::point_i32 & point, ::user::e_zorder ezorder) override;

      virtual bool plain_edit_is_enabled() override;

      DECLARE_MESSAGE_HANDLER(on_message_mouse_move);
      DECLARE_MESSAGE_HANDLER(on_message_mouse_leave);
      DECLARE_MESSAGE_HANDLER(on_message_left_button_down);
      DECLARE_MESSAGE_HANDLER(on_message_left_button_up);
      DECLARE_MESSAGE_HANDLER(on_message_key_down);
      DECLARE_MESSAGE_HANDLER(on_message_key_up);
      DECLARE_MESSAGE_HANDLER(on_message_show_window);
      DECLARE_MESSAGE_HANDLER(on_message_move);


      void on_reposition() override;

      virtual void _on_reposition();

      /// @return true if drop down list box was displayed
      virtual bool _001ShowDropDown(bool bShow = true);
      /// @return  true if drop down list box was displayed 
      virtual bool _001ToggleDropDown();


      void on_set_keyboard_focus() override;
      void on_kill_keyboard_focus() override;


      virtual void defer_create_list_box();

      virtual bool has_text_input() override;
      virtual bool is_drop_down();


      bool should_show_keyboard_focus() override;


      virtual void on_layout(::draw2d::graphics_pointer & pgraphics) override;

      virtual void plain_edit_on_after_change_text(::draw2d::graphics_pointer& pgraphics, const ::action_context & action_context) override;

      void handle(::topic * ptopic, ::context * pcontext) override;



      //virtual bool create_interaction(::user::interaction * puiParent, const ::atom & atom) override;

      //::raw::count get_count();
      //virtual ::raw::index current_index();
      void set_current_item(::item * pitem, const ::action_context & actioncontext) override;


      virtual void set_current_item_by_atom(const ::atom & atom, const ::action_context & action_context);
      virtual void set_current_item_by_text(const ::scoped_string & scopedstr, const ::action_context & action_context);
      virtual void set_current_item_by_index(::raw::index iIndex, const ::action_context & action_context);
      virtual string get_current_item_text();
      virtual ::atom get_current_item_atom();


//      LCID GetLocale();
  //    LCID SetLocale(LCID nNewLocale);
      ::raw::index GetTopIndex();
      ::raw::index SetTopIndex(::raw::index nIndex);
      ::raw::index InitStorage(::raw::count nItems, ::u32 nBytes);
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
      uptr GetItemData(::raw::index nIndex);
      ::raw::index SetItemData(::raw::index nIndex, uptr dwItemData);
      void * GetItemDataPtr(::raw::index nIndex);
      ::raw::index SetItemDataPtr(::raw::index nIndex, void * pData);
      ::raw::index GetLBText(::raw::index nIndex, char * pszText);

      void GetLBText(::raw::index nIndex, string & rString);
      strsize GetLBTextLen(::raw::index nIndex);

      i32 SetItemHeight(::raw::index nIndex, ::u32 cyItemHeight);
      i32 GetItemHeight(::raw::index nIndex);
      ::raw::index FindStringExact(::raw::index nIndexStart, const ::string & pszFind);

      i32 SetExtendedUI(bool bExtended = true);
      bool GetExtendedUI();
      void GetDroppedControlRect(::rectangle_i32 * prectangle);

      bool GetDroppedState();

      
      // for drop-down combo boxes
      void ShowDropDown(bool bShowIt = true);

      // manipulating listbox items
      //virtual ::raw::index add_string(const ::string & pszString, uptr dwItemData = 0);
      //virtual ::raw::index add_string(const ::string & pszString, const string& strValue);

      virtual ::raw::index add_item(const ::scoped_string & scopedstr, const ::atom & atom);


      virtual ::raw::index erase_item_at(::raw::index nIndex);
      virtual ::raw::index insert_item_at(::raw::index nIndex, const ::string & pszString);

      virtual void reset_content();
      ::raw::index Dir(::raw::index attr, const ::string & pszWildCard);



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



      bool keyboard_focus_is_focusable() override;


      //void handle(::topic * ptopic, ::context * pcontext) override;


   };


} //  namespace user



