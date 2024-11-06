#pragma once


#include "aura/graphics/image/icon.h"
#include "acme/prototype/text/text.h"
#include "apex/database/key.h"


namespace user
{


   class CLASS_DECL_CORE draw_list_column :
      virtual public ::particle
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
      ::collection::index                                  m_iNextGlobalOrderKey;
      ::user::list_column_array *            m_pcontainer;
      ::collection::index                                  m_iOrder;
      ::text::text                           m_text;
      ::u32                                  m_uiSmallBitmap;
      ::color::color                         m_colorSmallMask;
      i32                                    m_iSmallImageWidth;
      ::collection::index                                  m_iSubItem;
      ::collection::index                                  m_iColumn;
      ::image::image_list_pointer                m_pimagelist;
      ::image::image_list_pointer                m_pimagelistHover;
      ::pointer<draw_list_column>           m_pdrawlistcolumn;
      ::pointer<::user::interaction>        m_puserinteractionTemplate;
      ::pointer<::user::interaction_array>  m_puserinteractiona;
      ::image::icon_int_map                 m_mapIcon;
      ::size_i32                             m_sizeIcon;
      bool                                   m_bIcon;
      int                                  m_iPosition;
      int                                  m_iWidth;
      bool                                   m_bCustomDraw;
      ::image::image_pointer                        m_pimageHeader;

      // form list attributes
      bool                                   m_bEditOnSecondClick;
      //index                                m_iControl;
      ::string                               m_strDataKey;


      list_column();
      //list_column(const list_column & pcolumn);
      ~list_column() override;


      bool bind(::user::interaction * pinteraction);
   
   

      static int CompareOrderSectEndNonVisible(const ::pointer<list_column>& columna, const ::pointer<list_column> columnb);
      static int CompareOrder(const ::pointer<list_column>& columna, const ::pointer<list_column> columnb);

      static inline bool less_SectEndNonVisible(const ::pointer<list_column> columna, const ::pointer<list_column>columnb)
      {
         return CompareOrderSectEndNonVisible(columna, columnb) < 0;

      }

      //inline static auto fn_compare_key = [](auto & p1, auto & p2)
      //{

      //   return (p1->get_index() - p2->get_index()) < 0;

      //};

      static int CompareKey(const ::pointer<list_column>& columna, const ::pointer<list_column> columnb);

      bool operator ==(const ::user::list_column & pcolumn) const;
      //list_column & operator = (const list_column & column);


      ::collection::index        get_index() const;
      ::collection::index        get_visible_index() const;

      ::collection::index        item_index() const;
      ::collection::index        subitem_index() const { return (::collection::index) m_iSubItem; }
      ::collection::index        column_index() const { return (::collection::index) m_iColumn; }
      ::collection::index        order() const { return (::collection::index) m_iOrder; }

   };


} // namespace user



