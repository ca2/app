#pragma once


#include "control_bar.h"
#include "acme/user/user/_constant.h"

#define TBSTYLE_ALIGN_LEFT     0x10000
#define TBSTYLE_ALIGN_RIGHT    0x30000
#define TBSTYLE_ALIGN_CENTER   0x20000
#define TBSTYLE_ALIGN_TOP      0x40000
#define TBSTYLE_ALIGN_BOTTOM   0x80000
#define TBSTYLE_ALIGN_VCENTER  0xC0000

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
      void SetHeight(::collection::index cyHeight);
      // call after SetSizes, height overrides bitmap size_i32
      //bool LoadToolBar(const ::string & pszResourceName);

      //bool LoadToolBar(::u32 nIDResource);
      //bool LoadBitmap(const ::string & pszResourceName);

      //bool LoadBitmap(::u32 nIDResource);
//#ifdef WINDOWS_DESKTOP
//      bool from(HBITMAP hbmImageWell);
//#endif
      bool SetButtons(const ::u32* pIDArray, ::collection::index nIDCount);

      // pIDArray can be nullptr to allocate is_empty buttons

      //virtual ::user::enum_state get_button_state(int iItem);

      // standard control bar things
      //virtual ::collection::index atom_index(const ::atom & atom) const;
      
      //::u32 GetItemID(index nIndex);
      
//      virtual void index_item_rectangle(index nIndex, ::rectangle_i32 * prectangle);
      
      //::collection::index tool_item_index(const ::atom & atom) const;
      
      ::user::tool_item * tool_item_by_atom(const ::atom & atom);
      
      e_tool_item_style tool_item_style(const ::atom & atom);
      void set_tool_item_style(const ::atom & atom, const e_tool_item_style & estyle);

      e_tool_item_state tool_item_state(const ::atom & atom);
      void set_tool_item_state(const ::atom & atom, const e_tool_item_state & estate);
      void add_tool_item_state(const ::atom & atom, const e_tool_item_state & estate);
      void erase_tool_item_state(const ::atom & atom, const e_tool_item_state & estate);

      void hide_tool_item(const ::atom & atom);
      void display_tool_item(const ::atom & atom);
      
      ::user::e_state tool_item_user_state(const ::atom & atom);


      ::user::tool_item & tool_item(const ::item * pitem);


      ::collection::index tool_item_image(const ::atom & atom);
      void set_tool_item_image(const ::atom & atom, ::collection::index iImage);
      void set_tool_item_text(const ::atom & atom, const ::string & pszText);

      string tool_item_text(const ::atom & atom);
//      void GetButtonText(const ::atom & atom, string & rString) const;

      // for direct access to the underlying common control
      //inline toolbar_control& GetToolBarCtrl() const;

      virtual ::size_i32 CalcSimpleLayout(::draw2d::graphics_pointer& pgraphics);
      ::size_i32 CalcFixedLayout(::draw2d::graphics_pointer& pgraphics, bool bStretch, bool bHorz) override;
      virtual ::size_i32 CalcDynamicLayout(::draw2d::graphics_pointer& pgraphics, int nLength, u32 nMode) override;
      //virtual void OnUpdateCmdUI(::pointer<::user::frame_window>pTarget, bool bDisableIfNoHndler);
      void set_owner(::user::interaction * pinteractionOwner);


//#ifdef WINDOWS_DESKTOP
//      bool AddReplaceBitmap(HBITMAP hbmImageWell);
//#endif


      void OnBarStyleChange(u32 dwOldStyle, u32 dwNewStyle) override;

      virtual void load_xml_toolbar(const ::payload & payloadFile);

      virtual ::status < ::rectangle_i32 > index_item_rectangle(::collection::index iItem);

      virtual ::status < ::rectangle_i32 > index_element_rectangle(::collection::index iItem, enum_element eelement, ::user::enum_state estate);

      virtual ::user::tool_item * tool_item_at(::collection::index iItem);
      virtual ::collection::count tool_item_count();


      virtual ::size_i32 SimpleLayout(::draw2d::graphics_pointer& pgraphics);


      // implementation helpers
//#ifdef WINDOWS_DESKTOP
//      virtual void _GetButton(::collection::index nIndex, TBBUTTON* pButton) const;
//      virtual void _SetButton(::collection::index nIndex, TBBUTTON* pButton);
//#endif
      virtual ::size_i32 CalcLayout(::draw2d::graphics_pointer& pgraphics, u32 nMode, ::collection::index nLength = -1);
//#ifdef WINDOWS_DESKTOP
//      virtual ::size_i32 CalcSize(TBBUTTON* pData, ::collection::index nCount);
//      virtual ::collection::index WrapToolBar(TBBUTTON* pData, ::collection::index nCount, ::collection::index nWidth);
//      virtual void SizeToolBar(TBBUTTON* pData, ::collection::index nCount, ::collection::index nLength, bool bVert = false);
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
//#define TBBS_BUTTON     make_i32(TBSTYLE_BUTTON, 0) // this entry is button
//#define e_tool_item_style_separator  make_i32(TBSTYLE_SEP, 0)    // this entry is a separator
//#define TBBS_CHECKBOX   make_i32(TBSTYLE_CHECK, 0)  // this is an auto check button
//#define TBBS_GROUP      make_i32(TBSTYLE_GROUP, 0)  // marks the start of a group
//#define TBBS_CHECKGROUP (TBBS_GROUP|TBBS_CHECKBOX)  // normal use of TBBS_GROUP
//#define TBBS_DROPDOWN   make_i32(TBSTYLE_DROPDOWN, 0) // drop down style
//#define TBBS_AUTOSIZE   make_i32(TBSTYLE_AUTOSIZE, 0) // autocalc button width
//#define TBBS_NOPREFIX   make_i32(TBSTYLE_NOPREFIX, 0) // no accel prefix for this button
//
//// styles for display states
//#define TBBS_CHECKED    make_i32(0, TBSTATE_CHECKED)    // button is checked/down
//#define TBBS_PRESSED    make_i32(0, TBSTATE_PRESSED)    // button is being depressed
//#define e_tool_item_style_disabled   make_i32(0, TBSTATE_ENABLED)    // button is disabled
//#define TBBS_INDETERMINATE  make_i32(0, TBSTATE_INDETERMINATE)  // third state
//#define TBBS_HIDDEN     make_i32(0, e_toolbar_button_hidden) // button is hidden
//#define TBBS_WRAPPED    make_i32(0, TBSTATE_WRAP)   // button is wrapped at this point_i32
//#define TBBS_ELLIPSES   make_i32(0, TBSTATE_ELIPSES)
//#define TBBS_MARKED      make_i32(0, TBSTATE_MARKED)
//

