#pragma once


namespace user
{


   class toolbar_item:
      virtual public ::item
   {
   public:


      //index                               m_iIndex;
      index                               m_iImage;
      ::image_pointer                     m_pimage;
      //atom                                  m_atom;
      e_toolbar_item_state                m_estate;
      e_toolbar_item_style                m_estyle;
      string                              m_str;
      //::rectangle_i32                              m_rectangle;
      bool                                m_bEnableIfHasCommandHandler;
      ::write_text::font_pointer              m_pfont;


      toolbar_item();
      ~toolbar_item() override;


   };


   inline toolbar_item * __toolbar_item(::item * pitem)
   {

      return (toolbar_item*) pitem->m_data[0];

   }


   class toolbar_control; // forward object (see afxcmn.h for definition)


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


      //__pointer_array(toolbar_item)    m_itema;

      bool                             m_bDelayedButtonLayout; // used to manage when button on_layout should be done

      ::size_i32               m_sizeImage;  // current image size_i32
      ::size_i32               m_sizeButton; // current button size_i32
      bool                 m_bSimpleLayout;
      string_to_ptr *      m_pStringMap;  // used as CMapStringTo::u32
      //index                m_iButtonPressItem;



      toolbar();
      ~toolbar() override;


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
      index CommandToIndex(::u32 nIDFind);
      ::u32 GetItemID(index nIndex);
      virtual void GetItemRect(index nIndex, RECTANGLE_I32 * prectangle);

      e_toolbar_item_style get_item_style(index iIndex);
      void set_item_style(index iIndex, const e_toolbar_item_style & estyle);

      e_toolbar_item_state get_item_state(index iIndex);
      void set_item_state(index iIndex, const e_toolbar_item_state & estate);

      ::user::enum_state get_item_user_state(index iIndex);

      // for changing button info
      void GetButtonInfo(index nIndex, ::u32& nID, ::u32& nStyle, index& iImage);
      void SetButtonInfo(index nIndex, ::u32 nID, ::u32 nStyle, index iImage);
      bool SetButtonText(index nIndex, const ::string & pszText);

      string GetButtonText(index nIndex) const;
      void GetButtonText(index nIndex, string & rString) const;

      // for direct access to the underlying common control
      inline toolbar_control& GetToolBarCtrl() const;

      virtual ::size_i32 CalcSimpleLayout(::draw2d::graphics_pointer& pgraphics);
      ::size_i32 CalcFixedLayout(::draw2d::graphics_pointer& pgraphics, bool bStretch, bool bHorz) override;
      virtual ::size_i32 CalcDynamicLayout(::draw2d::graphics_pointer& pgraphics, index nLength, u32 nMode);
      //virtual void OnUpdateCmdUI(__pointer(::user::frame_window) pTarget, bool bDisableIfNoHndler);
      __pointer(::user::interaction)  set_owner(__pointer(::user::interaction) pOwnerWnd);


//#ifdef WINDOWS_DESKTOP
//      bool AddReplaceBitmap(HBITMAP hbmImageWell);
//#endif


      void OnBarStyleChange(u32 dwOldStyle, u32 dwNewStyle) override;

      void assert_ok() const override;
      void dump(dump_context & dumpcontext) const override;


      virtual bool LoadXmlToolBar(const ::string & pszFileName);

      virtual bool _001GetItemRect(index iItem,RECTANGLE_I32 * prectangle);

      virtual bool _001GetElementRect(index iItem,RECTANGLE_I32 * prectangle,enum_element eelement, ::user::enum_state estate);

      virtual bool _001SetItem(index iItem, toolbar_item * pitem);
      virtual toolbar_item * _001GetItem(index iItem);
      virtual index _001GetItemCount();


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

      //LRESULT OnSetSizeHelper(::size_i32& size, LPARAM lParam);

      void on_command_probe(::user::interaction * puserinteraction, bool bDisableIfNoHndler) override;


      //virtual index _001GetHoverItem();


   };


} // namespace user

//
//
//// Styles for toolbar buttons
//#define TBBS_BUTTON     __MAKE_LONG(TBSTYLE_BUTTON, 0) // this entry is button
//#define e_toolbar_item_style_separator  __MAKE_LONG(TBSTYLE_SEP, 0)    // this entry is a separator
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
//#define e_toolbar_item_style_disabled   __MAKE_LONG(0, TBSTATE_ENABLED)    // button is disabled
//#define TBBS_INDETERMINATE  __MAKE_LONG(0, TBSTATE_INDETERMINATE)  // third state
//#define TBBS_HIDDEN     __MAKE_LONG(0, e_toolbar_button_hidden) // button is hidden
//#define TBBS_WRAPPED    __MAKE_LONG(0, TBSTATE_WRAP)   // button is wrapped at this point_i32
//#define TBBS_ELLIPSES   __MAKE_LONG(0, TBSTATE_ELIPSES)
//#define TBBS_MARKED      __MAKE_LONG(0, TBSTATE_MARKED)
//

