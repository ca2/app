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

      ::int_size                    m_sizeFull;
      //string                        m_strText;
      class ::time                      m_timeShowComboList;
      ::pointer<list_box>          m_plistbox;

      ::type_atom                   m_typeatomListBox;

      e_style                       m_estyle;

      bool                          m_bEdit;
      //e_data_mode                   m_edatamode;


      combo_box();
      ~combo_box() override;


      void destroy() override;

      void user_combo_box_common_construct();


      void install_message_routing(::channel * pchannel) override;


      ::subparticle_pointer clone() override;


      ::write_text::font_pointer get_font(style* pstyle, enum_element eelement = e_element_none, ::user::enum_state estate = e_state_none) override;


      void _000OnDraw(::draw2d::graphics_pointer & pgraphics) override;
      void _001OnDraw(::draw2d::graphics_pointer & pgraphics) override;
      virtual void _001OnDrawCombo(::draw2d::graphics_pointer & pgraphics);
      virtual void _001OnDrawStaticText(::draw2d::graphics_pointer & pgraphics);

      void _001OnNcPostDraw(::draw2d::graphics_pointer & pgraphics) override;

      virtual enum_input_type preferred_input_type() override;

      virtual void get_simple_drop_down_open_arrow_polygon(double_point_array& pointa) override;

      virtual bool has_action_hover();




      //virtual void get_text(string & str) override;
      //virtual void set_text(const ::scoped_string & scopedstr, const ::action_context & action_context) override;


      virtual bool _001GetListText(::collection::index iSel, string & str) const;
      virtual ::collection::index _001FindListText(const ::scoped_string & scopedstr) const;
      virtual ::collection::count _001GetListCount() const;

      //virtual bool create_interaction(::user::interaction * pinteractionParent, const ::atom & atom) override;

      bool get_element_rectangle(::int_rectangle & prectangle, enum_element eelement) override;

      ::item_pointer on_hit_test(const ::int_point & point, ::user::e_zorder ezorder) override;

      virtual bool plain_edit_is_enabled() override;

      DECLARE_MESSAGE_HANDLER(on_message_destroy);
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

      void handle(::topic * ptopic, ::handler_context * phandlercontext) override;



      //virtual bool create_interaction(::user::interaction * puiParent, const ::atom & atom) override;

      //::collection::count get_count();
      //virtual ::collection::index current_index();
      void set_current_item(::item * pitem, const ::action_context & actioncontext) override;


      virtual void set_current_item_by_atom(const ::atom & atom, const ::action_context & action_context);
      virtual void set_current_item_by_text(const ::scoped_string & scopedstr, const ::action_context & action_context);
      virtual void set_current_item_by_index(::collection::index iIndex, const ::action_context & action_context);
      virtual string get_current_item_text();
      virtual ::atom get_current_item_id();


//      LCID GetLocale();
  //    LCID SetLocale(LCID nNewLocale);
      ::collection::index GetTopIndex();
      ::collection::index SetTopIndex(::collection::index nIndex);
      ::collection::index InitStorage(::collection::count nItems, unsigned int nBytes);
      void SetHorizontalExtent(unsigned int nExtent);
      unsigned int GetHorizontalExtent();
      int SetDroppedWidth(unsigned int nWidth);
      int GetDroppedWidth();

//#if defined(WINDOWS_DESKTOP) && (WINVER >= 0x0500)
//      bool GetComboBoxInfo(PCOMBOBOXINFO pcbi);
//#endif   // WINVER >= 0x0500

      // for edit control
      bool GetEditSel(character_count & nStartChar, character_count & nEndChar);
      bool LimitText(character_count nMaxChars);
      bool SetEditSel(character_count nStartChar, character_count nEndChar);

      // for combobox item
      uptr GetItemData(::collection::index nIndex);
      ::collection::index SetItemData(::collection::index nIndex, uptr dwItemData);
      void * GetItemDataPtr(::collection::index nIndex);
      ::collection::index SetItemDataPtr(::collection::index nIndex, void * pData);
      ::collection::index GetLBText(::collection::index nIndex, char * pszText);

      void GetLBText(::collection::index nIndex, string & rString);
      character_count GetLBTextLen(::collection::index nIndex);

      int SetItemHeight(::collection::index nIndex, unsigned int cyItemHeight);
      int GetItemHeight(::collection::index nIndex);
      ::collection::index FindStringExact(::collection::index nIndexStart, const ::scoped_string & scopedstrFind);

      int SetExtendedUI(bool bExtended = true);
      bool GetExtendedUI();
      void GetDroppedControlRect(::int_rectangle * prectangle);

      bool GetDroppedState();

      
      // for drop-down combo boxes
      void ShowDropDown(bool bShowIt = true);

      // manipulating listbox items
      //virtual ::collection::index add_string(const ::scoped_string & scopedstrString, uptr dwItemData = 0);
      //virtual ::collection::index add_string(const ::scoped_string & scopedstrString, const ::scoped_string & scopedstrValue);

      virtual ::collection::index add_item(const ::scoped_string & scopedstr, const ::atom & atom);


      virtual ::collection::index erase_item_at(::collection::index nIndex);
      virtual ::collection::index insert_item_at(::collection::index nIndex, const ::scoped_string & scopedstrString);

      virtual void reset_content();
      ::collection::index Dir(::collection::index attr, const ::scoped_string & scopedstrWildCard);



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
//      virtual int CompareItem(LPCOMPAREITEMSTRUCT pCompareItemStruct);
//
//      virtual void DeleteItem(LPDELETEITEMSTRUCT pDeleteItemStruct);
//
//#endif

      //virtual bool OnChildNotify(::user::message * pusermessage) override;


      //virtual ::color::color get_action_hover_border_color() override;



      bool keyboard_focus_is_focusable() override;


      //void handle(::topic * ptopic, ::handler_context * phandlercontext) override;


   };


} //  namespace user



