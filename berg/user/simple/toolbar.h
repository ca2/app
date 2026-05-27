#pragma once


#include "acme/graphics/write_text/font_size.h"
#include "berg/user/user/toolbar.h"

class image_list;


class CLASS_DECL_BERG simple_toolbar :
   virtual public ::user::toolbar
{
public:

   bool                       m_bStyleFlat : 1;
   
   ::i32                     m_iImageSpacing;
   ::i32_size                  m_sizePress;
   ::i32_size                  m_sizeSpacing;
   ::i32_size                  m_sizeSeparator;
   ::i32_rectangle                m_rectangleBorder;
   ::i32_rectangle                m_rectangleItemPad;
   //bool                       m_bTransparentBackground;
   bool                    m_bSimpleLayout;
   ::write_text::font_size       m_fontsize;

   ::i32_size                  m_sizeButton;
   ::i32_size                  m_sizeImage;
//#ifdef WINDOWS
  // HRSRC           m_hRsrcImageWell; // handle to loaded resource for image well
//#endif
  // HINSTANCE        m_hInstImageWell; // instance handle to load image well from
   //HBITMAP          m_hbmImageWell; // contains color mapped button images
//   ::image::image_list_pointer    m_pimagelist;
//   ::image::image_list_pointer    m_pimagelistHue;
//   ::image::image_list_pointer    m_pimagelistBlend;
//   ::image::image_list_pointer    m_pimagelistHueLight;
   //bool           m_bInternalImageList;
   //bool             m_bDelayedButtonLayout;
   ::image::image_pointer     m_pimageDraft;
   ::pointer < ::user::interaction >      m_puserinteractionCommandTarget;


   simple_toolbar();
   ~simple_toolbar() override;

   virtual ::i32  get_image_spacing();
   virtual ::i32_size get_press_shift();
   virtual ::i32_size get_item_spacing();
   virtual ::i32_size get_separator_size();
   virtual ::i32_rectangle get_bar_border();
   virtual ::i32_rectangle get_item_pad();

   virtual ::f64 get_pixel_font_size() const;

   //bool create(::user::interaction * puiParent, ::u32 uStyle = WS_CHILD | WS_VISIBLE | CBRS_TOP, atom nID = "__IDW_TOOLBAR");
   //using ::user::interaction::create_window_ex;
   //virtual bool create_toolbar(::user::interaction * puiParent, ::u32 dwCtrlStyle = TBSTYLE_FLAT, ::u32 uStyle = WS_CHILD | WS_VISIBLE | CBRS_ALIGN_TOP, atom nID = "__IDW_TOOLBAR") override;


   virtual ::collection::index WrapToolBar(::draw2d::graphics_pointer& pgraphics, ::collection::index nCount, ::collection::index nWidth);
   virtual void SizeToolBar(::draw2d::graphics_pointer& pgraphics, ::collection::index nCount, ::collection::index nLength, bool bVert = false);

   virtual ::i32_size CalcDynamicLayout(::draw2d::graphics_pointer& pgraphics, ::i32 nLength, ::u32 dwMode) override;
   virtual ::i32_size CalcLayout(::draw2d::graphics_pointer& pgraphics, ::u32 dwMode, ::collection::index nLength = -1) override;
   //bool CalcSize(size & size, bool bHorz);
   virtual ::i32_size CalcSize(::draw2d::graphics_pointer & pgraphics, ::collection::index nCount);
   virtual void OnBarStyleChange(::u32 dwOldStyle, ::u32 dwNewStyle) override;
   virtual ::i32_size CalcFixedLayout(::draw2d::graphics_pointer& pgraphics, bool bStretch, bool bHorz) override;


   void RemoveAllTools();
//   virtual ::collection::index _001GetHoverItem() override;
   //virtual void OnUpdateHover();
   //void SetItemImage(::collection::index iItem, ::collection::index iImage);
   //void GetButtonText(::collection::index i, string & str);
   //void SetButtonStyle(index nIndex, const enumeration < ::enum_tool_item_style > & nStyle);
   //enumeration < ::enum_tool_item_style > GetButtonStyle(::collection::index iButton);
   //bool SetItemStyle(::collection::index iItem, const enumeration < ::enum_tool_item_style > & bStyle);
   //enumeration < ::enum_tool_item_style > GetItemStyle(::collection::index iItem);
   void _001SetImageList(::image::image_list_pointer imagelist);
   void _001DiscardImageList();
   bool on_click(::item * pitem, ::user::mouse * pmouse) override;
   virtual ::item_pointer on_hit_test(const ::i32_point & point, ::user::e_zorder ezorder) override;
   //void _001Hover(const ::i32_point & point, bool bRedraw = true);
   //void _001Hover(bool bRedraw = true);


   void on_layout(::draw2d::graphics_pointer & pgraphics) override;


   void _001DrawItem(::draw2d::graphics_pointer & pgraphics, ::collection::index iItem);
   void _001DrawSimpleToolbarItem(::draw2d::graphics_pointer & pgraphics, ::collection::index iItem);

   /*
      bool LoadToolBar(const ::scoped_string & scopedstrResourceName);

      bool LoadToolBar(::u32 nIDResource);
      bool LoadBitmap(const ::scoped_string & scopedstrResourceName);

      bool LoadBitmap(::u32 nIDResource);
   */

//  virtual bool index_item_rectangle(::collection::index iItem,::i32_rectangle * prectangle)

   ::status < ::i32_rectangle > index_element_rectangle(::collection::index iItem, ::enum_element eelement,
                                   ::user::enum_state estate) override;




//   bool SetButtons(const ::u32* pIDArray, ::collection::index nIDCount);

   void SetSizes(const ::i32_size & sizeButton, const ::i32_size & sizeImage);



   //void TransparentEraseNonClient(::draw2d::graphics_pointer & pgraphics);
   //void SetTransparentBackground(bool bSet);
   virtual void _001OnDraw(::draw2d::graphics_pointer & pgraphics) override;
   virtual ::i32_size CalcSimpleLayout(::draw2d::graphics_pointer& pgraphics) override;

   void _001OnImageListAttrib();
   DECLARE_MESSAGE_HANDLER(on_message_create);
   DECLARE_MESSAGE_HANDLER(on_message_left_button_f64_click);
   //DECLARE_MESSAGE_HANDLER(on_message_mouse_move);
   //DECLARE_MESSAGE_HANDLER(on_message_left_button_down);
   void on_timer(::timer * ptimer) override;
   //DECLARE_MESSAGE_HANDLER(on_message_left_button_up);
   DECLARE_MESSAGE_HANDLER(on_message_non_client_calculate_size);
   //DECLARE_MESSAGE_HANDLER(_001OnNcHitTest);
   //DECLARE_MESSAGE_HANDLER(on_message_mouse_leave);

   void install_message_routing(::channel * pchannel) override;


};



