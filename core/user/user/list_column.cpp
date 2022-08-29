#include "framework.h"
#include "aura/user/user/interaction.h"
#include "aura/graphics/draw2d/_component.h"
#include "list_column.h"
#include "list_column_array.h"


namespace user
{


   list_column::list_column()
   {

      m_bNew = true;
      m_uiSmallBitmap = (::u32)-1;
      m_iOrder = -1;
      m_iColumn = -1;
      m_bVisible = true;
      m_pimagelist = nullptr;
      //m_iControl = -1;
      m_bEditOnSecondClick = false;
      m_bCustomDraw = false;
      m_bIcon = false;
      m_pimagelist = nullptr;
      m_pimagelistHover = nullptr;
      m_sizeIcon.cx = 0;
      m_sizeIcon.cy = 0;
      m_pdrawlistcolumn = __new(draw_list_column);

   }


   list_column::~list_column()
   {

   }



   ::index list_column::get_index() const
   {

      return m_pcontainer->get_index(this);

   }


   ::index list_column::item_index() const
   {

      return get_index();

   }


   bool list_column::bind(::user::interaction * pinteraction)
   {

      if (is_null(pinteraction))
      {

         return false;

      }

      m_atom = pinteraction->m_atom;

      return m_atom;

   }


   ::index list_column::get_visible_index() const
   {

      return m_pcontainer->get_visible_index(this);

   }


   bool list_column::operator ==(const list_column & column) const
   {

      return m_iSubItem == column.m_iSubItem;

   }


   int list_column::CompareOrderSectEndNonVisible(const __pointer(list_column) & pcolumna, const __pointer(list_column) & pcolumnb)
   {

      if (pcolumna->m_bVisible && pcolumnb->m_bVisible)
      {

         return (int)(pcolumna->m_iOrder - pcolumnb->m_iOrder);

      }
      else if (pcolumna->m_bVisible)
      {

         return -1;

      }
      else if (pcolumnb->m_bVisible)
      {

         return 1;

      }
      else
      {

         return 0;

      }

   }


   int list_column::CompareOrder(const __pointer(list_column) & pcolumna, const __pointer(list_column) & pcolumnb)
   {

      return (int)(pcolumna->m_iOrder - pcolumnb->m_iOrder);

   }


   //::user::interaction * list_column::get_control()
   //{

   //   if (!m_pcontainer)
   //   {

   //      return nullptr;

   //   }

   //   auto plist = m_pcontainer->m_plist;

   //   if (!plist)
   //   {

   //      return nullptr;

   //   }

   //   auto puserinteraction = plist->get_child_by_id(m_atom);

   //   if (!puserinteraction)
   //   {

   //      return nullptr;

   //   }

   //   return puserinteraction;

   //}


} // namespace user



