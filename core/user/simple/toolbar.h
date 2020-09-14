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


   
   int                     m_iImageSpacing;
   ::size                  m_sizePress;
   ::size                  m_sizeSpacing;
   ::size                  m_sizeSeparator;
   ::rect                m_rectBorder;
   ::rect                m_rectItemPad;
   //bool                       m_bTransparentBackground;
   bool                    m_bSimpleLayout;
   double                  m_dFontSize;

   ::size                  m_sizeButton;
   ::size                  m_sizeImage;
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
   virtual ::size get_press_shift();
   virtual ::size get_item_spacing();
   virtual ::size get_separator_size();
   virtual ::rect get_bar_border();
   virtual ::rect get_item_pad();

   bool create(::user::interaction * puiParent, u32 uStyle = WS_CHILD | WS_VISIBLE | CBRS_TOP, id nID = "__IDW_TOOLBAR");
   using ::user::interaction::create_window_ex;
   virtual bool create_toolbar(::user::interaction * puiParent, u32 dwCtrlStyle = TBSTYLE_FLAT, u32 uStyle = WS_CHILD | WS_VISIBLE | CBRS_ALIGN_TOP, id nID = "__IDW_TOOLBAR") override;


   virtual index WrapToolBar(::draw2d::graphics_pointer& pgraphics, index nCount, index nWidth);
   virtual void SizeToolBar(::draw2d::graphics_pointer& pgraphics, index nCount, index nLength, bool bVert = FALSE);

   virtual ::size CalcDynamicLayout(::draw2d::graphics_pointer& pgraphics, index nLength, u32 dwMode) override;
   virtual ::size CalcLayout(::draw2d::graphics_pointer& pgraphics, u32 dwMode, index nLength = -1) override;
   //bool CalcSize(size & size, bool bHorz);
   virtual ::size CalcSize(::draw2d::graphics_pointer & pgraphics, index nCount);
   virtual void OnBarStyleChange(u32 dwOldStyle, u32 dwNewStyle) override;
   virtual ::size CalcFixedLayout(::draw2d::graphics_pointer& pgraphics, bool bStretch, bool bHorz) override;


   void RemoveAllTools();
//   virtual index _001GetHoverItem() override;
   //virtual void OnUpdateHover();
   void SetItemImage(index iItem, index iImage);
   void GetButtonText(index i, string & str);
   void SetButtonStyle(index nIndex, UINT nStyle);
   UINT GetButtonStyle(index iButton);
   bool SetItemStyle(index iItem, BYTE bStyle);
   index GetItemStyle(index iItem);
   void _001SetImageList(__pointer(::image_list) imagelist);
   void _001DiscardImageList();
   virtual bool on_click(const ::user::item & item) override;
   virtual void on_hit_test(::user::item & item) override;
   //void _001Hover(const ::point & point, bool bRedraw = true);
   //void _001Hover(bool bRedraw = true);


   void on_layout(::draw2d::graphics_pointer & pgraphics) override;


   void _001DrawItem(::draw2d::graphics_pointer & pgraphics, index iItem);
   void _001DrawSimpleToolbarItem(::draw2d::graphics_pointer & pgraphics, index iItem);

   /*
      bool LoadToolBar(const char * pszResourceName);

      bool LoadToolBar(UINT nIDResource);
      bool LoadBitmap(const char * pszResourceName);

      bool LoadBitmap(UINT nIDResource);
   */

//  virtual bool _001GetItemRect(index iItem,RECT * prect)

   virtual bool _001GetElementRect(index iItem,RECT * prect, ::user::e_element eelement,
                                   ::user::estate estate) override;




//   bool SetButtons(const UINT* pIDArray, index nIDCount);

   void SetSizes(const ::size & sizeButton, const ::size & sizeImage);

   void on_command_probe(::user::frame_window * ptarget, bool bDisableIfNoHndler) override;


   //void TransparentEraseNonClient(::draw2d::graphics_pointer & pgraphics);
   //void SetTransparentBackground(bool bSet);
   virtual void _001OnDraw(::draw2d::graphics_pointer & pgraphics) override;
   virtual ::size CalcSimpleLayout(::draw2d::graphics_pointer& pgraphics) override;

   void _001OnImageListAttrib();
   DECL_GEN_SIGNAL(_001OnCreate);
   //DECL_GEN_SIGNAL(_001OnMouseMove);
   //DECL_GEN_SIGNAL(_001OnLButtonDown);
   void _001OnTimer(::timer * ptimer) override;
   //DECL_GEN_SIGNAL(_001OnLButtonUp);
   DECL_GEN_SIGNAL(_001OnNcCalcSize);
   //DECL_GEN_SIGNAL(_001OnNcHitTest);
   //DECL_GEN_SIGNAL(_001OnMouseLeave);

   virtual void install_message_routing(::channel * pchannel) override;


};
