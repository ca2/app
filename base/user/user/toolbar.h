#pragma once


#include "control_bar.h"
#include "acme/user/user/_constant.h"


namespace user
{


   class CLASS_DECL_BASE toolbar :
      virtual public ::user::control_bar
   {
   public:


//      enum enum_element
//      {
//         e_element_item,
//         element_item_hover,
//         element_item_press,
//         element_image,
//         element_image_hover,
//         element_image_press,
//         e_element_text,
//         element_text_hover,
//         element_text_press,
//      };


      //pointer_array < tool_item >    m_itema;

      bool                       m_bDelayedButtonLayout; // used to manage when button on_layout should be done

      ::size_i32               m_sizeImage;  // current image size_i32
      ::size_i32               m_sizeButton; // current button size_i32
      bool                 m_bSimpleLayout;
//      string_to_ptr *      m_pStringMap;  // used as CMapStringTo::u32
//      //index                m_iButtonPressItem;



      toolbar();
      ~toolbar() override;

//      // void assert_ok() const override;
//      // void dump(dump_context & dumpcontext) const override;

      
      
      void install_message_routing(::channel * pchannel) override;



      void _001OnTimer(::timer * ptimer) override;


      //using ::user::control_bar::create_interaction;
      //virtual bool create_interaction(::user::interaction * puiParent,u32 uStyle = WS_CHILD | WS_VISIBLE | CBRS_TOP, ::atom atom = __IDW_TOOLBAR);
      //using ::user::control_bar::create_window_ex;
      //virtual bool create_toolbar(::user::interaction * puiParent, u32 dwCtrlStyle = TBSTYLE_FLAT,u32 uStyle = WS_CHILD | WS_VISIBLE | CBRS_ALIGN_TOP, atom nID = __IDW_TOOLBAR);

      void SetSizes(const ::size_i32 & sizeButton, const ::size_i32 & sizeImage);
      // button size_i32 should be bigger than image
      void SetHeight(index cyHeight);
      // call after SetSizes, height overrides bitmap size_i32
      //bool LoadToolBar(const ::string & pszResourceName);

      //bool LoadToolBar(::u32 nIDResource);
      //bool LoadBitmap(const ::string & pszResourceName);

      //bool LoadBitmap(::u32 nIDResource);
//#ifdef WINDOWS_DESKTOP
//      bool from(HBITMAP hbmImageWell);
//#endif
      bool SetButtons(const ::u32* pIDArray, index nIDCount);

      // pIDArray can be nullptr to allocate is_empty buttons

      //virtual ::user::enum_state get_button_state(int iItem);

      // standard control bar things
      //virtual ::index atom_index(const ::atom & atom) const;
      
      //::u32 GetItemID(index nIndex);
      
//      virtual void index_item_rectangle(index nIndex, RECTANGLE_I32 * prectangle);
      
      //::index tool_item_index(const ::atom & atom) const;
      
      ::user::tool_item * tool_item(const ::atom & atom) const;
      
      e_tool_item_style tool_item_style(const ::atom & atom) const;
      void set_tool_item_style(const ::atom & atom, const e_tool_item_style & estyle);

      e_tool_item_state tool_item_state(const ::atom & atom) const;
      void set_tool_item_state(const ::atom & atom, const e_tool_item_state & estate);
      void add_tool_item_state(const ::atom & atom, const e_tool_item_state & estate);
      void erase_tool_item_state(const ::atom & atom, const e_tool_item_state & estate);

      void hide_tool_item(const ::atom & atom);
      void display_tool_item(const ::atom & atom);
      
      ::user::e_state tool_item_user_state(const ::atom & atom) const;

      ::index tool_item_image(const ::atom & atom) const;
      void set_tool_item_image(const ::atom & atom, index iImage);
      void set_tool_item_text(const ::atom & atom, const ::string & pszText);

      string tool_item_text(const ::atom & atom) const;
//      void GetButtonText(const ::atom & atom, string & rString) const;

      // for direct access to the underlying common control
      //inline toolbar_control& GetToolBarCtrl() const;

      virtual ::size_i32 CalcSimpleLayout(::draw2d::graphics_pointer& pgraphics);
      ::size_i32 CalcFixedLayout(::draw2d::graphics_pointer& pgraphics, bool bStretch, bool bHorz) override;
      virtual ::size_i32 CalcDynamicLayout(::draw2d::graphics_pointer& pgraphics, ::i32 nLength, u32 nMode) override;
      //virtual void OnUpdateCmdUI(::pointer<::user::frame_window>pTarget, bool bDisableIfNoHndler);
      void set_owner(::user::interaction * pinteractionOwner);


//#ifdef WINDOWS_DESKTOP
//      bool AddReplaceBitmap(HBITMAP hbmImageWell);
//#endif


      void OnBarStyleChange(u32 dwOldStyle, u32 dwNewStyle) override;

      virtual void load_xml_toolbar(const ::payload & payloadFile);

      virtual bool index_item_rectangle(index iItem,RECTANGLE_I32 * prectangle);

      virtual bool index_element_rectangle(index iItem,RECTANGLE_I32 * prectangle,enum_element eelement, ::user::enum_state estate);

      virtual void set_index_tool_item(index iItem, ::user::tool_item * pitem);
      virtual ::user::tool_item * index_tool_item(index iItem) const;
      virtual ::count tool_item_count() const;


      virtual ::size_i32 SimpleLayout(::draw2d::graphics_pointer& pgraphics);


      // implementation helpers
//#ifdef WINDOWS_DESKTOP
//      virtual void _GetButton(::index nIndex, TBBUTTON* pButton) const;
//      virtual void _SetButton(::index nIndex, TBBUTTON* pButton);
//#endif
      virtual ::size_i32 CalcLayout(::draw2d::graphics_pointer& pgraphics, u32 nMode, index nLength = -1);
//#ifdef WINDOWS_DESKTOP
//      virtual ::size_i32 CalcSize(TBBUTTON* pData, index nCount);
//      virtual index WrapToolBar(TBBUTTON* pData, index nCount, index nWidth);
//      virtual void SizeToolBar(TBBUTTON* pData, index nCount, index nLength, bool bVert = false);
//#endif
      void on_layout(::draw2d::graphics_pointer & pgraphics) override; // called for for delayed button on_layout

      void _001OnDraw(::draw2d::graphics_pointer & pgraphics) override;

      DECLARE_MESSAGE_HANDLER(on_message_create);
      DECLARE_MESSAGE_HANDLER(_001OnNcHitTest);
      DECLARE_MESSAGE_HANDLER(on_message_non_client_calculate_size);
      DECLARE_MESSAGE_HANDLER(_001OnWindowPosChanging);
      DECLARE_MESSAGE_HANDLER(_001OnSysColorChange);
      DECLARE_MESSAGE_HANDLER(_001OnSetButtonSize);
      DECLARE_MESSAGE_HANDLER(_001OnSetBitmapSize);
      DECLARE_MESSAGE_HANDLER(_001OnPreserveZeroBorderHelper);
      DECLARE_MESSAGE_HANDLER(on_message_left_button_double_click);


      void on_command_probe(::user::interaction * puserinteraction, bool bDisableIfNoHndler) override;


   };


} // namespace user

//
//
//// Styles for toolbar buttons
//#define TBBS_BUTTON     __MAKE_LONG(TBSTYLE_BUTTON, 0) // this entry is button
//#define e_tool_item_style_separator  __MAKE_LONG(TBSTYLE_SEP, 0)    // this entry is a separator
//#define TBBS_CHECKBOX   __MAKE_LONG(TBSTYLE_CHECK, 0)  // this is an auto check button
//#define TBBS_GROUP      __MAKE_LONG(TBSTYLE_GROUP, 0)  // marks the start of a group
//#define TBBS_CHECKGROUP (TBBS_GROUP|TBBS_CHECKBOX)  // normal use of TBBS_GROUP
//#define TBBS_DROPDOWN   __MAKE_LONG(TBSTYLE_DROPDOWN, 0) // drop down style
//#define TBBS_AUTOSIZE   __MAKE_LONG(TBSTYLE_AUTOSIZE, 0) // autocalc button width
//#define TBBS_NOPREFIX   __MAKE_LONG(TBSTYLE_NOPREFIX, 0) // no accel prefix for this button
//
//// styles for display states
//#define TBBS_CHECKED    __MAKE_LONG(0, TBSTATE_CHECKED)    // button is checked/down
//#define TBBS_PRESSED    __MAKE_LONG(0, TBSTATE_PRESSED)    // button is being depressed
//#define e_tool_item_style_disabled   __MAKE_LONG(0, TBSTATE_ENABLED)    // button is disabled
//#define TBBS_INDETERMINATE  __MAKE_LONG(0, TBSTATE_INDETERMINATE)  // third state
//#define TBBS_HIDDEN     __MAKE_LONG(0, e_toolbar_button_hidden) // button is hidden
//#define TBBS_WRAPPED    __MAKE_LONG(0, TBSTATE_WRAP)   // button is wrapped at this point_i32
//#define TBBS_ELLIPSES   __MAKE_LONG(0, TBSTATE_ELIPSES)
//#define TBBS_MARKED      __MAKE_LONG(0, TBSTATE_MARKED)
//

