#pragma once


#include "aura/graphics/image/image.h"
#include "aura/user/user/box.h"


#ifndef HDS_HORZ


#define HDS_HORZ                0x0000
#define HDS_BUTTONS             0x0002
#define HDS_HOTTRACK            0x0004
#define HDS_HIDDEN              0x0008

#define HDS_DRAGDROP            0x0040
#define HDS_FULLDRAG            0x0080
#define HDS_FILTERBAR           0x0100

#if (NTDDI_VERSION >= NTDDI_WINXP)
#define HDS_FLAT                0x0200
#endif

#if (NTDDI_VERSION >= NTDDI_VISTA)
#define HDS_CHECKBOXES          0x0400
#define HDS_NOSIZING            0x0800
#define HDS_OVERFLOW            0x1000
#endif
// end_r_commctrl

#define HDFT_ISSTRING       0x0000      // HD_ITEM.pvFilter points to a HD_TEXTFILTER
#define HDFT_ISNUMBER       0x0001      // HD_ITEM.pvFilter points to a ::i32
#define HDFT_ISDATE         0x0002      // HD_ITEM.pvFilter points to a ::u32 (dos date)

#define HDFT_HASNOVALUE     0x8000      // clear the filter, by setting this bit

#ifdef UNICODE
#define HD_TEXTFILTER HD_TEXTFILTERW
#define HDTEXTFILTER HD_TEXTFILTERW
#define LPHD_TEXTFILTER LPHD_TEXTFILTERW
#define LPHDTEXTFILTER LPHD_TEXTFILTERW
#else
#define HD_TEXTFILTER HD_TEXTFILTERA
#define HDTEXTFILTER HD_TEXTFILTERA
#define LPHD_TEXTFILTER LPHD_TEXTFILTERA
#define LPHDTEXTFILTER LPHD_TEXTFILTERA
#endif

#endif

namespace user
{


   class list;


   class CLASS_DECL_CORE list_header :
      virtual public box
   {
   public:


      class CLASS_DECL_CORE item
      {
      public:


         ::u32       mask;
         i32         cxy;
         string      m_strTextText;
         ::image     m_image;
         i32         cchTextMax;
         i32         fmt;
         lparam      lParam;
         i32         iImage;        // index of bitmap in ImageList
         i32         iOrder;
         ::u32       type;           // [in] filter type (defined what pvFilter is a pointer to)
         void *      pvFilter;       // [in] fillter data see above
         ::u32       state;
      };


      enum enum_element
      {
         e_element_item,
         element_item_Box,
         ElementDivider,
      };

      int                           m_iImageSpacing;
      //::write_text::font_pointer                 m_pfont;
      string                        m_strBuffer;
      __pointer(draw2d::graphics_extension)    m_pdcextension;

      bool                          m_bTrack;
      bool                          m_bHover;
      enum_element                      m_eelementHover;
      index                         m_iItemHover;
      bool                          m_bLButtonDown;
      enum_element                      m_eelementLButtonDown;
      index                         m_iItemLButtonDown;

      list *                        m_plist;


      list_header();
      virtual ~list_header();

      void install_message_routing(::channel * pchannel) override;
      void SetBaseListCtrlInterface(list * pinterface);

      virtual void _001OnClip(::draw2d::graphics_pointer & pgraphics) override;
      virtual void _001OnDraw(::draw2d::graphics_pointer & pgraphics) override;
      virtual void DrawItem(::draw2d::item * pdrawitem);


      virtual bool DIDDXColumn(bool bSave);
      virtual bool DIDDXLayout(bool bSave);
      virtual index MapItemToOrder(index iItem);
      virtual index ItemToColumnKey(index iItem);

      virtual i32 GetDividerWidth();


      bool GetItemRect(RECTANGLE_I32 * prectangle, enum_element eelement, index iItem);


      bool GetItemRect(RECTANGLE_I32 * prectangle, enum_element eelementLButtonDown, index iItemLButtonDown,

                       enum_element eelement,
                       index iItem);

      bool hit_test(
      const ::point_i32 & point,
      enum_element & eelement,
      index & iItem);

      bool hit_test(
      const ::point_i32 & point,
      enum_element eelementLButtonDown,
      index iItemLButtonDown,
      enum_element & eelement,
      index & iItem);


      virtual ::point_i32 get_parent_context_offset() const override;

      // Message Handlers
   protected:
      DECLARE_MESSAGE_HANDLER(on_message_left_button_down);
      DECLARE_MESSAGE_HANDLER(on_message_left_button_up);
      DECLARE_MESSAGE_HANDLER(on_message_left_button_double_click);
      DECLARE_MESSAGE_HANDLER(on_message_mouse_move);

   };

} // namespace user



