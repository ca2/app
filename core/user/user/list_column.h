#pragma once


#include "aura/graphics/image/icon.h"


namespace user
{


   class CLASS_DECL_CORE draw_list_column :
      virtual public ::element
   {
   public:


      ::draw2d::brush_pointer          m_brushaText[16];
      ::status < ::color::color >      m_coloraText[16];
      ::write_text::font *             m_pfont;
      ::e_align                        m_ealign;
      ::e_draw_text                    m_edrawtext;


   };


   class CLASS_DECL_CORE list_column :
      virtual public matter
   {
   public:

      // Always indicate what maybe "superfluous" information
      // in this case
      //
      // Cache:
      //
      // int                           m_iKey;

      //::atom                                m_atom;
      bool                                   m_bNew;
      bool                                   m_bVisible;
      index                                  m_iNextGlobalOrderKey;
      ::user::list_column_array *            m_pcontainer;
      index                                  m_iOrder;
      ::text::text                           m_text;
      ::u32                                  m_uiSmallBitmap;
      ::color::color                         m_colorSmallMask;
      i32                                    m_iSmallImageWidth;
      index                                  m_iSubItem;
      index                                  m_iColumn;
      __pointer(::image_list)                m_pimagelist;
      __pointer(::image_list)                m_pimagelistHover;
      __pointer(draw_list_column)            m_pdrawlistcolumn;
      __pointer(::user::interaction)         m_puserinteractionTemplate;
      __pointer(::user::interaction_array)   m_puserinteractiona;
      ::draw2d::icon_int_map                 m_mapIcon;
      ::size_i32                             m_sizeIcon;
      bool                                   m_bIcon;
      ::i32                                  m_iPosition;
      ::i32                                  m_iWidth;
      bool                                   m_bCustomDraw;
      ::image_pointer                        m_pimageHeader;

      // form list attributes
      bool                                   m_bEditOnSecondClick;
      //index                                m_iControl;
      ::database::key                        m_datakey;



      list_column();
      //list_column(const list_column & pcolumn);
      ~list_column() override;


      bool bind(::user::interaction * pinteraction);
   
   

      static int CompareOrderSectEndNonVisible(const __pointer(list_column) & columna, const __pointer(list_column) & columnb);
      static int CompareOrder(const __pointer(list_column) & columna, const __pointer(list_column) & columnb);

      static inline bool less_SectEndNonVisible(const __pointer(list_column)& columna, const __pointer(list_column)& columnb)
      {
         return CompareOrderSectEndNonVisible(columna, columnb) < 0;

      }

      //inline static auto fn_compare_key = [](auto & p1, auto & p2)
      //{

      //   return (p1->get_index() - p2->get_index()) < 0;

      //};

      static int CompareKey(const __pointer(list_column) & columna, const __pointer(list_column) & columnb);

      bool operator ==(const ::user::list_column & pcolumn) const;
      //list_column & operator = (const list_column & column);


      ::index        get_index() const;
      ::index        get_visible_index() const;

      ::index        item_index() const;
      ::index        subitem_index() const { return (::index) m_iSubItem; }
      ::index        column_index() const { return (::index) m_iColumn; }
      ::index        order() const { return (::index) m_iOrder; }

   };


} // namespace user



