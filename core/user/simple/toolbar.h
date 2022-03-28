#pragma once


#define TBSTYLE_ALIGN_LEFT     0x10000
#define TBSTYLE_ALIGN_RIGHT    0x30000
#define TBSTYLE_ALIGN_CENTER   0x20000
#define TBSTYLE_ALIGN_TOP      0x40000
#define TBSTYLE_ALIGN_BOTTOM   0x80000
#define TBSTYLE_ALIGN_VCENTER  0xC0000


class image_list;


class CLASS_DECL_CORE simple_toolbar :
   virtual public ::user::toolbar
{
public:

   bool                       m_bStyleFlat : 1;
   
   int                     m_iImageSpacing;
   ::size_i32                  m_sizePress;
   ::size_i32                  m_sizeSpacing;
   ::size_i32                  m_sizeSeparator;
   ::rectangle_i32                m_rectangleBorder;
   ::rectangle_i32                m_rectangleItemPad;
   //bool                       m_bTransparentBackground;
   bool                    m_bSimpleLayout;
   double                  m_dFontSize;

   ::size_i32                  m_sizeButton;
   ::size_i32                  m_sizeImage;
//#ifdef WINDOWS
  // HRSRC           m_hRsrcImageWell; // handle to loaded resource for image well
//#endif
  // HINSTANCE        m_hInstImageWell; // instance handle to load image well from
   //HBITMAP          m_hbmImageWell; // contains color mapped button images
//   __pointer(::image_list)    m_pimagelist;
//   __pointer(::image_list)    m_pimagelistHue;
//   __pointer(::image_list)    m_pimagelistBlend;
//   __pointer(::image_list)    m_pimagelistHueLight;
   //bool           m_bInternalImageList;
   //bool             m_bDelayedButtonLayout;
   ::image_pointer     m_pimageDraft;


   simple_toolbar();
   virtual ~simple_toolbar();

   virtual int  get_image_spacing();
   virtual ::size_i32 get_press_shift();
   virtual ::size_i32 get_item_spacing();
   virtual ::size_i32 get_separator_size();
   virtual ::rectangle_i32 get_bar_border();
   virtual ::rectangle_i32 get_item_pad();

   //bool create(::user::interaction * puiParent, u32 uStyle = WS_CHILD | WS_VISIBLE | CBRS_TOP, atom nID = "__IDW_TOOLBAR");
   //using ::user::interaction::create_window_ex;
   //virtual bool create_toolbar(::user::interaction * puiParent, u32 dwCtrlStyle = TBSTYLE_FLAT, u32 uStyle = WS_CHILD | WS_VISIBLE | CBRS_ALIGN_TOP, atom nID = "__IDW_TOOLBAR") override;


   virtual index WrapToolBar(::draw2d::graphics_pointer& pgraphics, index nCount, index nWidth);
   virtual void SizeToolBar(::draw2d::graphics_pointer& pgraphics, index nCount, index nLength, bool bVert = false);

   virtual ::size_i32 CalcDynamicLayout(::draw2d::graphics_pointer& pgraphics, index nLength, u32 dwMode) override;
   virtual ::size_i32 CalcLayout(::draw2d::graphics_pointer& pgraphics, u32 dwMode, index nLength = -1) override;
   //bool CalcSize(size & size, bool bHorz);
   virtual ::size_i32 CalcSize(::draw2d::graphics_pointer & pgraphics, index nCount);
   virtual void OnBarStyleChange(u32 dwOldStyle, u32 dwNewStyle) override;
   virtual ::size_i32 CalcFixedLayout(::draw2d::graphics_pointer& pgraphics, bool bStretch, bool bHorz) override;


   void RemoveAllTools();
//   virtual index _001GetHoverItem() override;
   //virtual void OnUpdateHover();
   void SetItemImage(index iItem, index iImage);
   void GetButtonText(index i, string & str);
   //void SetButtonStyle(index nIndex, const enumeration < ::enum_toolbar_item_style > & nStyle);
   //enumeration < ::enum_toolbar_item_style > GetButtonStyle(index iButton);
   //bool SetItemStyle(index iItem, const enumeration < ::enum_toolbar_item_style > & bStyle);
   //enumeration < ::enum_toolbar_item_style > GetItemStyle(index iItem);
   void _001SetImageList(__pointer(::image_list) imagelist);
   void _001DiscardImageList();
   virtual bool on_click(::item * pitem) override;
   virtual ::item_pointer on_hit_test(const ::point_i32 & point) override;
   //void _001Hover(const ::point_i32 & point, bool bRedraw = true);
   //void _001Hover(bool bRedraw = true);


   void on_layout(::draw2d::graphics_pointer & pgraphics) override;


   void _001DrawItem(::draw2d::graphics_pointer & pgraphics, index iItem);
   void _001DrawSimpleToolbarItem(::draw2d::graphics_pointer & pgraphics, index iItem);

   /*
      bool LoadToolBar(const ::string & pszResourceName);

      bool LoadToolBar(::u32 nIDResource);
      bool LoadBitmap(const ::string & pszResourceName);

      bool LoadBitmap(::u32 nIDResource);
   */

//  virtual bool _001GetItemRect(index iItem,RECTANGLE_I32 * prectangle)

   virtual bool _001GetElementRect(index iItem,RECTANGLE_I32 * prectangle, ::enum_element eelement,
                                   ::user::enum_state estate) override;




//   bool SetButtons(const ::u32* pIDArray, index nIDCount);

   void SetSizes(const ::size_i32 & sizeButton, const ::size_i32 & sizeImage);



   //void TransparentEraseNonClient(::draw2d::graphics_pointer & pgraphics);
   //void SetTransparentBackground(bool bSet);
   virtual void _001OnDraw(::draw2d::graphics_pointer & pgraphics) override;
   virtual ::size_i32 CalcSimpleLayout(::draw2d::graphics_pointer& pgraphics) override;

   void _001OnImageListAttrib();
   DECLARE_MESSAGE_HANDLER(on_message_create);
   //DECLARE_MESSAGE_HANDLER(on_message_mouse_move);
   //DECLARE_MESSAGE_HANDLER(on_message_left_button_down);
   void _001OnTimer(::timer * ptimer) override;
   //DECLARE_MESSAGE_HANDLER(on_message_left_button_up);
   DECLARE_MESSAGE_HANDLER(on_message_non_client_calculate_size);
   //DECLARE_MESSAGE_HANDLER(_001OnNcHitTest);
   //DECLARE_MESSAGE_HANDLER(on_message_mouse_leave);

   void install_message_routing(::channel * pchannel) override;


};
