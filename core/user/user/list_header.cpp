#include "framework.h"
#include "core/user/user/_user.h"


namespace user
{

   list_header::list_header()
   {
      m_plistctrlinterface = nullptr;
      m_bTrack = false;
      m_bLButtonDown = false;
      m_bHover = false;
      m_iImageSpacing = 4;
      //m_ecolorBackground = color_list_header_background;
      m_flagNonClient.remove(::user::interaction::non_client_background);
      m_flagNonClient.remove(::user::interaction::non_client_focus_rect);
   }

   list_header::~list_header()
   {

   }

   void list_header::SetBaseListCtrlInterface(list *pinterface)
   {
      m_plistctrlinterface = pinterface;
   }

   void list_header::DrawItem(::draw2d::item * pdrawitem)
   {

      ::draw2d::graphics_pointer pgraphics = pdrawitem->m_pgraphics;

      ::rectangle_i32 rectColumn = pdrawitem->rcItem;

      i32 iColumn = pdrawitem->itemID;

      list * plist = m_plistctrlinterface;

      if (plist->m_columna.get_visible(iColumn)->m_pimageHeader->is_set() && plist->m_columna.get_visible(iColumn)->m_pimageHeader->area() > 0)
      {

         ::rectangle_i32 rectangle;

         rectangle.left = 0;
         rectangle.top = 0;
         rectangle.right = plist->m_columna.get_visible(iColumn)->m_pimageHeader->width();
         rectangle.bottom = plist->m_columna.get_visible(iColumn)->m_pimageHeader->height();

         ::rectangle_i32 rC;

         rC = rectColumn;

         rC.left += 2;

         rectangle.Align(::e_align_left_center, rC);

         pgraphics->stretch(rectangle, plist->m_columna.get_visible(iColumn)->m_pimageHeader->get_graphics());

         rectColumn.left = rectangle.right + m_iImageSpacing;

      }

      string str;

      auto papplication = get_application();

      str = papplication->load_string(plist->_001GetColumnTextId(ItemToColumnKey(iColumn)));
      //m_font->create_point_font("Verdana", 10.0);

      if (str.has_char())
      {

         auto pstyle = get_style(pdrawitem->m_pgraphics);

         pdrawitem->m_pgraphics->set(get_font(pstyle));
         //      pgraphics->SetBkMode(TRANSPARENT);

         pgraphics->set_text_color(get_color(pstyle, ::user::e_element_text));
         
         ::e_align ealign = plist->get_draw_text_align(plist->m_eview);
         
         ::e_draw_text edrawtext = plist->get_draw_text_flags(plist->m_eview);

         pgraphics->draw_text(str, rectColumn, ealign, edrawtext);

      }

   }



   index list_header::MapItemToOrder(index iItem)
   {
//#ifdef WINDOWS_DESKTOP
      //    HDITEM hditem;


      //hditem.mask = HDI_ORDER| HDI_TEXT;

      //  hditem.mask = HDI_ORDER;

      //   char pszText[1024];

      //   hditem.pszText = pszText;
      //   hditem.cchTextMax = 1024;

      //   get_item(iItem, &hditem);

      //   return hditem.iOrder;
      return iItem;

//#else

      //__throw(todo);

//#endif

   }


   bool list_header::GetItemRect(RECTANGLE_I32 * prectangle, enum_element eelement, index iItem)

   {

      if(iItem < 0)
         return false;

      list * plist = m_plistctrlinterface;
      if(iItem >= plist->_001GetColumnCount())
         return false;

      i32 x;
      if(plist->m_bGroup && plist->m_bLateralGroup)
      {
         x = plist->m_iLateralGroupWidth;
      }
      else
      {
         x = 0;
      }
      i32 xLast = x;
      draw_list_item item(plist);
      for(i32 i = 0; i <= iItem; i++)
      {
         xLast = x;
         item.m_iColumn = ItemToColumnKey(i);
         plist->_001GetColumnWidth(&item);
         if(item.m_bOk)
         {
            x += item.m_iColumnWidth;
         }
      }

      ::rectangle_i32 rectangle;

      get_client_rect(rectangle);
      rectangle.left = xLast;
      rectangle.right = x;

      if(eelement == e_element_item)
      {
         *prectangle = rectangle;

         return true;
      }

      if(eelement == element_item_Box)
      {
         rectangle.right -= GetDividerWidth();
         *prectangle = rectangle;

         return true;
      }

      if(eelement == ElementDivider)
      {
         rectangle.left = rectangle.right - GetDividerWidth();
         *prectangle = rectangle;

         return true;
      }
      return true;
   }

   bool list_header::GetItemRect(
   RECTANGLE_I32 * prectangle,

   enum_element eelementLButtonDown,
   index iItemLButtonDown,
   enum_element eelement,
   index iItem)
   {
      if(iItem < 0)
         return false;
      list * plist = m_plistctrlinterface;
      if(iItem >= plist->_001GetColumnCount())
         return false;


      if(eelementLButtonDown == element_item_Box
            && eelement == element_item_Box)
      {
         if(iItem == iItemLButtonDown)
         {
            ::rectangle_i32 rectA;
            if(!GetItemRect(rectA, element_item_Box, iItem - 1))
            {
               GetItemRect(rectA, element_item_Box, iItem);
            }

            ::rectangle_i32 rectangle;
            GetItemRect(rectangle, element_item_Box, iItem);

            ::rectangle_i32 rectB;
            if(!GetItemRect(rectA, element_item_Box, iItem + 1))
            {
               GetItemRect(rectA, element_item_Box, iItem);
            }

            rectangle.left = rectA.left + rectA.width() / 2;
            rectangle.right = rectB.left + rectB.width() / 2;
            *prectangle = rectangle;

            return true;
         }
         else if(iItem <= iItemLButtonDown - 1)
         {
            ::rectangle_i32 rectA;
            if(!GetItemRect(rectA, element_item_Box, iItem - 1))
            {
               GetItemRect(rectA, element_item_Box, iItem);
            }

            ::rectangle_i32 rectangle;
            GetItemRect(rectangle, element_item_Box, iItem);

            rectangle.left = rectA.left + rectA.width() / 2;
            rectangle.right = rectangle.left + rectangle.width() / 2;
            *prectangle = rectangle;

            return true;
         }
         else if(iItem >= iItemLButtonDown + 1)
         {
            ::rectangle_i32 rectB;
            if(!GetItemRect(rectB, element_item_Box, iItem + 1))
            {
               GetItemRect(rectB, element_item_Box, iItem);
            }

            ::rectangle_i32 rectangle;
            GetItemRect(rectangle, element_item_Box, iItem);

            rectangle.left = rectangle.left + rectangle.width() / 2;
            rectangle.right = rectB.left + rectB.width() / 2;
            *prectangle = rectangle;

            return true;
         }
         return false;
      }
      else
      {
         return GetItemRect(prectangle, eelement, iItem);

      }

   }

   bool list_header::hit_test(const ::point_i32 & point, enum_element & eelement, index & iItemParam)
   {
      list * plist = m_plistctrlinterface;
      ::rectangle_i32 rectangle;
      for(i32 iItem = 0; iItem < plist->_001GetColumnCount(); iItem++)
      {
         if(GetItemRect(rectangle, element_item_Box, iItem))
         {
            if(rectangle.contains(point))
            {
               iItemParam = iItem;
               eelement = element_item_Box;
               return true;
            }
         }
         if(GetItemRect(rectangle, ElementDivider, iItem))
         {
            if(rectangle.contains(point))
            {
               iItemParam = iItem;
               eelement = ElementDivider;
               return true;
            }
         }
      }
      return false;
   }

   bool list_header::hit_test(const ::point_i32 & point, enum_element eelementLButtonDown, index iItemLButtonDown, enum_element & eelement, index & iItemParam)
   {
      list * plist = m_plistctrlinterface;
      ::rectangle_i32 rectangle;
      for(i32 iItem = 0; iItem < plist->_001GetColumnCount(); iItem++)
      {
         if(GetItemRect(rectangle, eelementLButtonDown, iItemLButtonDown, element_item_Box, iItem))
         {
            if(rectangle.contains(point))
            {
               iItemParam = iItem;
               eelement = element_item_Box;
               return true;
            }
         }
         if(GetItemRect(rectangle, ElementDivider, iItem))
         {
            if(rectangle.contains(point))
            {
               iItemParam = iItem;
               eelement = ElementDivider;
               return true;
            }
         }
      }
      return false;
   }


   index list_header::ItemToColumnKey(index iItem)
   {

      list * plist = m_plistctrlinterface;

      return plist->_001MapColumnToOrder(iItem);

   }


   bool list_header::DIDDXLayout(bool bSave)
   {

      bool bFail = false;

      if(!DIDDXColumn(bSave))
         bFail = true;

      return !bFail;

   }


   bool list_header::DIDDXColumn(bool bSave)
   {

      ::database::key datakey({ true, "::user::list_column_width" });

      draw_list_item item(m_plistctrlinterface);

      int_array iaWidth;

      if (bSave)
      {

         for (index iColumn = 0; iColumn < m_plistctrlinterface->_001GetColumnCount(); iColumn++)
         {

            item.m_iColumn = iColumn;

            m_plistctrlinterface->_001GetColumnWidth(&item);

            if (item.m_bOk)
            {

               iaWidth.add(item.m_iColumnWidth);

            }
            else
            {

               iaWidth.add(-1);

            }

         }

         if (!papplication->data_set(datakey, iaWidth))
         {

            return false;

         }

      }
      else
      {

         if (papplication->data_get(datakey, iaWidth))
         {

            ::count c = minimum(iaWidth.get_count(), m_plistctrlinterface->_001GetColumnCount());

            for (index iColumn = 0; iColumn < c; iColumn++)
            {

               m_plistctrlinterface->_001SetColumnWidth(iColumn, maximum(iaWidth[iColumn], 50));

            }

         }

      }

      return true;

   }


   void list_header::install_message_routing(::channel * pchannel)
   {
      ::user::box::install_message_routing(pchannel);
      MESSAGE_LINK(e_message_left_button_down, pchannel, this, &list_header::on_message_left_button_down);
      MESSAGE_LINK(e_message_left_button_up, pchannel, this, &list_header::on_message_left_button_up);
      MESSAGE_LINK(e_message_left_button_double_click, pchannel, this, &list_header::_001OnLButtonDblClk);
      MESSAGE_LINK(e_message_mouse_move, pchannel, this, &list_header::on_message_mouse_move);
   }

   void list_header::on_message_left_button_down(::message::message * pmessage)
   {
      __pointer(::message::mouse) pmouse(pmessage);
      auto pointCursor = pmouse->m_point;
      _001ScreenToClient(&pointCursor);
      if(hit_test(pointCursor, m_eelementLButtonDown, m_iItemLButtonDown))
      {
         m_bLButtonDown = true;
      }

      pmouse->m_bRet = false;
   }

   void list_header::on_message_left_button_up(::message::message * pmessage)
   {
      __pointer(::message::mouse) pmouse(pmessage);
      list * plist = m_plistctrlinterface;
      auto pointCursor = pmouse->m_point;
      _001ScreenToClient(&pointCursor);
      if(m_bLButtonDown)
      {
         m_bLButtonDown = false;
         enum_element eelement;
         index iItem;
         if(hit_test(pointCursor, eelement, iItem))
         {
            if(m_eelementLButtonDown == element_item_Box
                  && eelement == element_item_Box)
            {
               if(iItem == m_iItemLButtonDown)
               {
                  // This is a single click in a header item
                  plist->_001OnListHeaderItemClick(iItem);
               }
               else // iItem != m_iItemLButtonDown
               {
                  // The header item has been dragged

                  index iKeyA = plist->m_columna.order_index(iItem);
                  index iKeyB = plist->m_columna.order_index(iItem);
                  index iOrderA = plist->m_columna.get_by_index(iKeyA)->m_iOrder;
                  index iOrderB = plist->m_columna.get_by_index(iKeyB)->m_iOrder;
                  plist->m_columna.get_by_index(iKeyA)->m_iOrder = iOrderB;
                  plist->m_columna.get_by_index(iKeyB)->m_iOrder = iOrderA;
                  plist->_001OnColumnChange();
                  plist->DISaveOrder();
                  plist->set_need_redraw();
                  set_need_redraw();
               }
            }
            else if(m_eelementLButtonDown == ElementDivider)
            {
               ::rectangle_i32 rectangle;
               GetItemRect(rectangle, e_element_item, m_iItemLButtonDown);
               rectangle.right = pointCursor.x;
               i32 iNewWidth = rectangle.width();
               plist->_001SetColumnWidth(m_iItemLButtonDown, maximum(0, iNewWidth));
               plist->set_need_redraw();
               set_need_redraw();
            }

         }
      }

      pmouse->m_bRet = false;
   }



   void list_header::on_message_mouse_move(::message::message * pmessage)
   {
      __pointer(::message::mouse) pmouse(pmessage);
      auto pointCursor = pmouse->m_point;
      _001ScreenToClient(&pointCursor);
      list * plist = m_plistctrlinterface;
      enum_element eelement;
      index iItem;

      auto psession = get_session();

      if(hit_test(pointCursor, eelement, iItem))
      {
         if(!m_bTrack)
         {
            m_bTrack = true;
            // trans SetCapture();
         }
         m_bHover = true;
         m_eelementHover = eelement;
         m_iItemHover = iItem;
      }
      else
      {
         if(m_bTrack)
         {

            m_bTrack = false;

            auto psession = get_session();

            auto puser = psession->user();

            auto pwindowing = puser->windowing();

            pwindowing->release_mouse_capture();

         }
         if(m_bHover)
         {
            m_bHover = false;
         }
      }

      if(m_bLButtonDown)
      {
         if(m_eelementLButtonDown == ElementDivider)
         {
            ::rectangle_i32 rectangle;
            GetItemRect(rectangle, e_element_item, m_iItemLButtonDown);
            rectangle.right = pointCursor.x;
            i32 iNewWidth = rectangle.width();
            plist->_001SetColumnWidth(m_iItemLButtonDown, maximum(0, iNewWidth));
            plist->set_need_redraw();
            set_need_redraw();
         }
      }


      if(m_bHover && m_eelementHover == ElementDivider)
      {
         pmouse->m_ecursor = e_cursor_size_horizontal;
      }
      else
      {
         pmouse->m_ecursor = e_cursor_arrow;
      }

      pmouse->m_bRet = false;
   }


   void list_header::_001OnLButtonDblClk(::message::message * pmessage)
   {
      __pointer(::message::mouse) pmouse(pmessage);
      auto pointCursor = pmouse->m_point;
      _001ScreenToClient(&pointCursor);
      list * plist = m_plistctrlinterface;
      enum_element eelement;
      index iItem;
      if(hit_test(
            pointCursor,
            eelement,
            iItem)
        )
      {
         if(eelement == element_item_Box)
         {
            plist->_001OnListHeaderItemDblClk(iItem);
         }
      }

      pmouse->m_bRet = false;
   }


   void list_header::_001OnClip(::draw2d::graphics_pointer & pgraphics)
   {

      try
      {

         ::rectangle_i32 rectClip;

         ::aura::draw_context * pdrawcontext = pgraphics->::aura::simple_chain < ::aura::draw_context >::get_last();

         ::rectangle_i32 rectClient;

         bool bFirst = true;

         if (pdrawcontext != nullptr)
         {

            rectClient = pdrawcontext->m_rectWindow;

            _001ScreenToClient(rectClient);

            rectClient.bottom++;
            rectClient.right++;

            rectClip = rectClient;

            bFirst = false;

         }
         
         if(!m_pshapeaClip)
         {

            __construct_new(m_pshapeaClip);
            
            ::user::interaction * pinteraction = this;

            ::rectangle_i32 rectFocus;

            ::rectangle_i32 rectIntersect;

            index i = 0;

            while (pinteraction != nullptr)
            {

               if (i == 1)
               {
                  // guess list client rectangle_i32 doesn't include header?
                  pinteraction->::user::interaction::get_client_rect(rectFocus);

               }
               else
               {

                  pinteraction->get_client_rect(rectFocus);

               }

               pinteraction->_001ClientToScreen(rectFocus);

               _001ScreenToClient(rectFocus);

               rectFocus.bottom++;

               rectFocus.right++;

               m_pshapeaClip->add_item(__new(rectd_shape(rectIntersect)));

               m_pshapeaClip->add_item(__new(intersect_clip_shape));

               i++;

               pinteraction = pinteraction->get_parent();

            }
            
         }
         
         pgraphics->add_shapes(*m_pshapeaClip);


      }
      catch (...)
      {

         __throw(::exception::exception("no more a window"));

      }


   }


   void list_header::_001OnDraw(::draw2d::graphics_pointer & pgraphics)
   {


      ::rectangle_i32 rectClient;

      get_client_rect(rectClient);

      ::rectangle_i32 rectUpdate(rectClient);

      ::rectangle_f64 rectClipBox;

      pgraphics->get_clip_box(&rectClipBox);

      rectClipBox.right--;

      if(rectClipBox.is_empty())
      {
         
         rectClipBox = rectClient;

      }

      rectUpdate.intersect(rectUpdate, rectClipBox);

      pgraphics->set_alpha_mode(::draw2d::alpha_mode_blend);

      auto pstyle = get_style(pgraphics);

      pgraphics->fill_rectangle(rectUpdate, get_color(pstyle, ::user::e_element_background));

      ::draw2d::item drawitem;
      drawitem.m_pgraphics = pgraphics;
      list * plist = m_plistctrlinterface;
      ::rectangle_i32 rectDivider;
      ::draw2d::pen_pointer ppen(e_create);

      auto color = get_color(pstyle, ::user::e_element_separator);

      ppen->create_solid(1.0, color);

      for(i32 iItem = 0; iItem < plist->_001GetColumnCount(); iItem++)
      {

         drawitem.itemID = iItem;

         GetItemRect(&drawitem.rcItem, element_item_Box, iItem);

         DrawItem(&drawitem);

         GetItemRect(rectDivider, ElementDivider, iItem);

         pgraphics->set(ppen);

         pgraphics->move_to(rectDivider.left, rectDivider.top);

         pgraphics->line_to(rectDivider.left, rectDivider.bottom);

         //pgraphics->draw3d_rect(rectDivider, crButtonShadow, psession->get_default_color(COLOR_BTNHIGHLIGHT));

      }

   }


   i32 list_header::GetDividerWidth()
   {
      return 4;
   }


   ::point_i32 list_header::get_parent_viewport_offset() const
   {

      __pointer(::user::interaction) puser = get_parent();

      if (puser.is_null())
      {

         return point_i32(0, 0);

      }

      puser = puser->get_parent();

      if (puser.is_null())
      {

         return point_i32(0, 0);

      }

      return puser->get_viewport_offset();

   }


} // namespace user
