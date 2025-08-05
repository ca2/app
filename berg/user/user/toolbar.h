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


   class CLASS_DECL_BERG toolbar :
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

      ::int_size               m_sizeImage;  // current image int_size
      ::int_size               m_sizeButton; // current button int_size
      bool                 m_bSimpleLayout;
//      string_to_ptr *      m_pStringMap;  // used as CMapStringTounsigned int
//      //index                m_iButtonPressItem;



      toolbar();
      ~toolbar() override;

//      // void assert_ok() const override;
//      // void dump(dump_context & dumpcontext) const override;

      
      
      void install_message_routing(::channel * pchannel) override;



      void on_timer(::timer * ptimer) override;


      //using ::user::control_bar::create_interaction;
      //virtual bool create_interaction(::user::interaction * puiParent,unsigned int uStyle = WS_CHILD | WS_VISIBLE | CBRS_TOP, ::atom atom = __IDW_TOOLBAR);
      //using ::user::control_bar::create_window_ex;
      //virtual bool create_toolbar(::user::interaction * puiParent, unsigned int dwCtrlStyle = TBSTYLE_FLAT,unsigned int uStyle = WS_CHILD | WS_VISIBLE | CBRS_ALIGN_TOP, atom nID = __IDW_TOOLBAR);

      void SetSizes(const ::int_size & sizeButton, const ::int_size & sizeImage);
      // button int_size should be bigger than image
      void SetHeight(::collection::index cyHeight);
      // call after SetSizes, height overrides bitmap int_size
      //bool LoadToolBar(const ::scoped_string & scopedstrResourceName);

      //bool LoadToolBar(unsigned int nIDResource);
      //bool LoadBitmap(const ::scoped_string & scopedstrResourceName);

      //bool LoadBitmap(unsigned int nIDResource);
//#ifdef WINDOWS_DESKTOP
//      bool from(HBITMAP hbmImageWell);
//#endif
      bool SetButtons(const unsigned int* pIDArray, ::collection::index nIDCount);

      // pIDArray can be nullptr to allocate is_empty buttons

      //virtual ::user::enum_state get_button_state(int iItem);

      // standard control bar things
      //virtual ::collection::index atom_index(const ::atom & atom) const;
      
      //unsigned int GetItemID(index nIndex);
      
//      virtual void index_item_rectangle(index nIndex, ::int_rectangle * prectangle);
      
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
      void set_tool_item_text(const ::atom & atom, const ::scoped_string & scopedstrText);

      string tool_item_text(const ::atom & atom);
//      void GetButtonText(const ::atom & atom, string & rString) const;

      // for direct access to the underlying common control
      //inline toolbar_control& GetToolBarCtrl() const;

      virtual ::int_size CalcSimpleLayout(::draw2d::graphics_pointer& pgraphics);
      ::int_size CalcFixedLayout(::draw2d::graphics_pointer& pgraphics, bool bStretch, bool bHorz) override;
      virtual ::int_size CalcDynamicLayout(::draw2d::graphics_pointer& pgraphics, int nLength, unsigned int nMode) override;
      //virtual void OnUpdateCmdUI(::pointer<::user::frame_window>pTarget, bool bDisableIfNoHndler);
      void set_owner(::user::interaction * pinteractionOwner);


//#ifdef WINDOWS_DESKTOP
//      bool AddReplaceBitmap(HBITMAP hbmImageWell);
//#endif


      void OnBarStyleChange(unsigned int dwOldStyle, unsigned int dwNewStyle) override;

      virtual void load_xml_toolbar(const ::payload & payloadFile);

      virtual ::status < ::int_rectangle > index_item_rectangle(::collection::index iItem);

      virtual ::status < ::int_rectangle > index_element_rectangle(::collection::index iItem, enum_element eelement, ::user::enum_state estate);

      virtual ::user::tool_item * tool_item_at(::collection::index iItem);
      virtual ::collection::count tool_item_count();


      virtual ::int_size SimpleLayout(::draw2d::graphics_pointer& pgraphics);


      // implementation helpers
//#ifdef WINDOWS_DESKTOP
//      virtual void _GetButton(::collection::index nIndex, TBBUTTON* pButton) const;
//      virtual void _SetButton(::collection::index nIndex, TBBUTTON* pButton);
//#endif
      virtual ::int_size CalcLayout(::draw2d::graphics_pointer& pgraphics, unsigned int nMode, ::collection::index nLength = -1);
//#ifdef WINDOWS_DESKTOP
//      virtual ::int_size CalcSize(TBBUTTON* pData, ::collection::index nCount);
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
//#define TBBS_BUTTON     make_int(TBSTYLE_BUTTON, 0) // this entry is button
//#define e_tool_item_style_separator  make_int(TBSTYLE_SEP, 0)    // this entry is a separator
//#define TBBS_CHECKBOX   make_int(TBSTYLE_CHECK, 0)  // this is an auto check button
//#define TBBS_GROUP      make_int(TBSTYLE_GROUP, 0)  // marks the start of a group
//#define TBBS_CHECKGROUP (TBBS_GROUP|TBBS_CHECKBOX)  // normal use of TBBS_GROUP
//#define TBBS_DROPDOWN   make_int(TBSTYLE_DROPDOWN, 0) // drop down style
//#define TBBS_AUTOSIZE   make_int(TBSTYLE_AUTOSIZE, 0) // autocalc button width
//#define TBBS_NOPREFIX   make_int(TBSTYLE_NOPREFIX, 0) // no accel prefix for this button
//
//// styles for display states
//#define TBBS_CHECKED    make_int(0, TBSTATE_CHECKED)    // button is checked/down
//#define TBBS_PRESSED    make_int(0, TBSTATE_PRESSED)    // button is being depressed
//#define e_tool_item_style_disabled   make_int(0, TBSTATE_ENABLED)    // button is disabled
//#define TBBS_INDETERMINATE  make_int(0, TBSTATE_INDETERMINATE)  // third state
//#define TBBS_HIDDEN     make_int(0, e_toolbar_button_hidden) // button is hidden
//#define TBBS_WRAPPED    make_int(0, TBSTATE_WRAP)   // button is wrapped at this int_point
//#define TBBS_ELLIPSES   make_int(0, TBSTATE_ELIPSES)
//#define TBBS_MARKED      make_int(0, TBSTATE_MARKED)
//

