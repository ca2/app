#include "framework.h"
#include "list.h"
#include "list_header.h"
#include "list_column.h"
#include "list_column_array.h"
#include "acme/constant/message.h"
#include "acme/primitive/collection/_array_binary_stream.h"
#include "apex/database/_binary_stream.h"
#include "aura/graphics/draw2d/pen.h"
#include "aura/graphics/draw2d/item.h"
#include "aura/graphics/image/drawing.h"
#include "aura/message/user.h"
#include "aura/platform/application.h"


namespace user
{


   list_header::list_header()
   {
      m_plist = nullptr;
      m_bTrack = false;
      m_bLButtonDown = false;
      m_bHover = false;
      m_iImageSpacing = 4;
      m_bParentScrollY = false;
      //m_ecolorBackground = color_list_header_background;
      m_flagNonClient.erase(::user::interaction::e_non_client_background);
      m_flagNonClient.erase(::user::interaction::e_non_client_focus_rect);
   }

   list_header::~list_header()
   {

   }

   void list_header::SetBaseListCtrlInterface(list *pinterface)
   {
      m_plist = pinterface;
   }

   void list_header::DrawItem(::draw2d::item * pdrawitem)
   {

      ::draw2d::graphics_pointer pgraphics = pdrawitem->m_pgraphics;

      ::rectangle_i32 rectangleColumn = pdrawitem->rcItem;

      i32 iColumn = pdrawitem->itemID;

      list * plist = m_plist;

      if (plist->m_pcolumna->get_visible(iColumn)->m_pimageHeader->is_set() && plist->m_pcolumna->get_visible(iColumn)->m_pimageHeader->area() > 0)
      {

         ::rectangle_i32 rectangle;

         rectangle.left = 0;
         rectangle.top = 0;
         rectangle.right = plist->m_pcolumna->get_visible(iColumn)->m_pimageHeader->width();
         rectangle.bottom = plist->m_pcolumna->get_visible(iColumn)->m_pimageHeader->height();

         ::rectangle_i32 rC;

         rC = rectangleColumn;

         rC.left += 2;

         rectangle.Align(::e_align_left_center, rC);

         image_source imagesource(plist->m_pcolumna->get_visible(iColumn)->m_pimageHeader);

         image_drawing_options imagedrawingoptions(rectangle);

         image_drawing imagedrawing(imagedrawingoptions, imagesource);

         pgraphics->draw(imagedrawing);

         rectangleColumn.left = rectangle.right + m_iImageSpacing;

      }

      string str;

      auto papp = get_app();

      str = plist->_001GetColumnText(ItemToColumnKey(iColumn));

      if (str.has_char())
      {

         auto pstyle = get_style(pdrawitem->m_pgraphics);

         auto pfont = get_font(pstyle);

         //pfont->m_strFontFamilyName = "Arial";

         //pfont->m_bUpdated2 = false;

         pdrawitem->m_pgraphics->set(pfont);

         auto color = get_color(pstyle, ::e_element_text);

         pgraphics->set_text_color(color);
         
         ::e_align ealign = plist->get_draw_text_align(plist->m_eview);
         
         ::e_draw_text edrawtext = plist->get_draw_text_flags(plist->m_eview);

         //rectangleColumn.bottom += rectangleColumn.height() * 2;

         pgraphics->draw_text(str, rectangleColumn, ealign, edrawtext);

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

      //throw ::exception(todo);

//#endif

   }


   bool list_header::GetItemRect(::rectangle_i32 * prectangle, enum_element eelement, index iItem)
   {

      if (iItem < 0)
      {

         return false;

      }

      list * plist = m_plist;

      if (iItem >= plist->_001GetColumnCount())
      {

         return false;

      }

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
      
      for(i32 i = 0; i <= iItem; i++)
      {
         
         xLast = x;
         
         auto pcolumn = plist->m_pcolumna->get_visible(iItem);
         
         x += pcolumn->m_iWidth;

      }

      ::rectangle_i32 rectangle;

      client_rectangle(rectangle);

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


   bool list_header::GetItemRect(::rectangle_i32 * prectangle, enum_element eelementLButtonDown, index iItemLButtonDown, enum_element eelement, index iItem)
   {

      if (iItem < 0)
      {

         return false;

      }

      list * plist = m_plist;

      if (iItem >= plist->_001GetColumnCount())
      {

         return false;

      }

      if(eelementLButtonDown == element_item_Box && eelement == element_item_Box)
      {

         if(iItem == iItemLButtonDown)
         {

            ::rectangle_i32 rectangleA;

            if(!GetItemRect(&rectangleA, element_item_Box, iItem - 1))
            {

               GetItemRect(&rectangleA, element_item_Box, iItem);

            }

            ::rectangle_i32 rectangle;

            GetItemRect(&rectangle, element_item_Box, iItem);

            ::rectangle_i32 rectangleB;

            if(!GetItemRect(&rectangleA, element_item_Box, iItem + 1))
            {

               GetItemRect(&rectangleA, element_item_Box, iItem);

            }

            rectangle.left = rectangleA.left + rectangleA.width() / 2;

            rectangle.right = rectangleB.left + rectangleB.width() / 2;

            *prectangle = rectangle;

            return true;

         }
         else if(iItem <= iItemLButtonDown - 1)
         {
            
            ::rectangle_i32 rectangleA;

            if(!GetItemRect(&rectangleA, element_item_Box, iItem - 1))
            {

               GetItemRect(&rectangleA, element_item_Box, iItem);

            }

            ::rectangle_i32 rectangle;

            GetItemRect(&rectangle, element_item_Box, iItem);

            rectangle.left = rectangleA.left + rectangleA.width() / 2;

            rectangle.right = rectangle.left + rectangle.width() / 2;

            *prectangle = rectangle;

            return true;

         }
         else if(iItem >= iItemLButtonDown + 1)
         {
            
            ::rectangle_i32 rectangleB;

            if(!GetItemRect(&rectangleB, element_item_Box, iItem + 1))
            {

               GetItemRect(&rectangleB, element_item_Box, iItem);

            }

            ::rectangle_i32 rectangle;

            GetItemRect(&rectangle, element_item_Box, iItem);

            rectangle.left = rectangle.left + rectangle.width() / 2;

            rectangle.right = rectangleB.left + rectangleB.width() / 2;

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
      list * plist = m_plist;
      ::rectangle_i32 rectangle;
      for(i32 iItem = 0; iItem < plist->_001GetColumnCount(); iItem++)
      {
         if(GetItemRect(&rectangle, element_item_Box, iItem))
         {
            if(rectangle.contains(point))
            {
               iItemParam = iItem;
               eelement = element_item_Box;
               return true;
            }
         }
         if(GetItemRect(&rectangle, ElementDivider, iItem))
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
      list * plist = m_plist;
      ::rectangle_i32 rectangle;
      for(i32 iItem = 0; iItem < plist->_001GetColumnCount(); iItem++)
      {
         if(GetItemRect(&rectangle, eelementLButtonDown, iItemLButtonDown, element_item_Box, iItem))
         {
            if(rectangle.contains(point))
            {
               iItemParam = iItem;
               eelement = element_item_Box;
               return true;
            }
         }
         if(GetItemRect(&rectangle, ElementDivider, iItem))
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

      list * plist = m_plist;

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

      ::string strDataKey({ true, "::user::list_column_width" });

      int_array iaWidth;

      if (bSave)
      {

         for (index iColumn = 0; iColumn < m_plist->_001GetColumnCount(); iColumn++)
         {

            auto pcolumn = m_plist->m_pcolumna->get_visible(iColumn);

            iaWidth.add(pcolumn->m_iWidth);

         }

         auto papp = get_app();

         papp->datastream()->set(strDataKey, iaWidth);

         //if (!papp->datastream()->set(datakey, iaWidth))
         //{

         //   return false;

         //}

      }
      else
      {

         auto papp = get_app();

         if (papp->datastream()->get(strDataKey, iaWidth))
         {

            ::count c = minimum(iaWidth.get_count(), m_plist->_001GetColumnCount());

            for (index iColumn = 0; iColumn < c; iColumn++)
            {

               auto pcolumn = m_plist->m_pcolumna->get_visible(iColumn);

               pcolumn->m_iWidth= iaWidth[iColumn];

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
      MESSAGE_LINK(e_message_left_button_double_click, pchannel, this, &list_header::on_message_left_button_double_click);
      MESSAGE_LINK(e_message_mouse_move, pchannel, this, &list_header::on_message_mouse_move);
   }

   void list_header::on_message_left_button_down(::message::message * pmessage)
   {

      auto pmouse = pmessage->m_union.m_pmouse;

      auto pointCursor = pmouse->m_point;

      screen_to_client()(pointCursor);

      if(hit_test(pointCursor, m_eelementLButtonDown, m_iItemLButtonDown))
      {

         m_bLButtonDown = true;

      }

      pmouse->m_bRet = false;

   }


   void list_header::on_message_left_button_up(::message::message * pmessage)
   {

      auto pmouse = pmessage->m_union.m_pmouse;

      list * plist = m_plist;

      auto pointCursor = pmouse->m_point;

      screen_to_client()(pointCursor);

      if(m_bLButtonDown)
      {

         m_bLButtonDown = false;

         enum_element eelement;

         index iItem;

         if(hit_test(pointCursor, eelement, iItem))
         {

            if(m_eelementLButtonDown == element_item_Box && eelement == element_item_Box)
            {

               if(iItem == m_iItemLButtonDown)
               {

                  // This is a single click in a header item
                  plist->_001OnListHeaderItemClick(iItem);

               }
               else // iItem != m_iItemLButtonDown
               {

                  // The header item has been dragged

                  index iKeyA = plist->m_pcolumna->order_index(iItem);
                  index iKeyB = plist->m_pcolumna->order_index(iItem);
                  index iOrderA = plist->m_pcolumna->get_by_index(iKeyA)->m_iOrder;
                  index iOrderB = plist->m_pcolumna->get_by_index(iKeyB)->m_iOrder;
                  plist->m_pcolumna->get_by_index(iKeyA)->m_iOrder = iOrderB;
                  plist->m_pcolumna->get_by_index(iKeyB)->m_iOrder = iOrderA;
                  plist->_001OnColumnChange();
                  plist->DISaveOrder();
                  plist->set_need_redraw();
                  set_need_redraw();
               }

            }
            else if(m_eelementLButtonDown == ElementDivider)
            {
               
               ::rectangle_i32 rectangle;
               
               GetItemRect(&rectangle, e_element_item, m_iItemLButtonDown);
               
               rectangle.right = pointCursor.x();
               
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

      auto pmouse = pmessage->m_union.m_pmouse;

      auto pointCursor = pmouse->m_point;

      screen_to_client()(pointCursor);

      list * plist = m_plist;

      enum_element eelement;

      index iItem;

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

            release_mouse_capture();

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
            
            GetItemRect(&rectangle, e_element_item, m_iItemLButtonDown);
            
            rectangle.right = pointCursor.x();
            
            i32 iNewWidth = rectangle.width();
            
            plist->_001SetColumnWidth(m_iItemLButtonDown, maximum(0, iNewWidth));
            
            plist->set_need_redraw();
            
            set_need_redraw();
            
         }
         
      }

      auto pwindowing = windowing();

      ::pointer<::windowing::cursor>pcursor;

      if(m_bHover && m_eelementHover == ElementDivider)
      {
         
         pcursor = get_mouse_cursor(e_cursor_size_horizontal);

      }
      else
      {

         pcursor = get_mouse_cursor(e_cursor_arrow);

      }

      pmouse->m_pcursor = pcursor;

      pmouse->m_bRet = false;

   }


   void list_header::on_message_left_button_double_click(::message::message * pmessage)
   {

      auto pmouse = pmessage->m_union.m_pmouse;

      auto pointCursor = pmouse->m_point;

      screen_to_client()(pointCursor);

      list * plist = m_plist;

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

      ::user::box::_001OnClip(pgraphics);

      return;

      //try
      //{

      //   ::rectangle_i32 rectangleClip;

      //   ::aura::draw_context* pdrawcontext = pgraphics->::aura::simple_chain < ::aura::draw_context >::get_last();

      //   ::rectangle_i32 rectangleClient;

      //   bool bFirst = true;

      //   string strType = __type_name(this);

      //   if (strType.case_insensitive_contains("control_box"))
      //   {

      //      infomration("control box on clip");

      //   }

      //   if (pdrawcontext != nullptr)
      //   {

      //      rectangleClient = pdrawcontext->m_rectangleWindow;

      //      screen_to_client(rectangleClient, e_layout_design);

      //      rectangleClient.bottom++;
      //      rectangleClient.right++;

      //      rectangleClip = rectangleClient;

      //      bFirst = false;

      //   }

      //   ::user::interaction* pinteraction = this;

      //   if (!m_pshapeaClip)
      //   {

      //      __construct_new(m_pshapeaClip);

      //      ::rectangle_i32 rectangleIntersect;

      //      while (pinteraction != nullptr)
      //      {

      //         pinteraction->client_rectangle(rectangleClient);

      //         pinteraction->client_to_host(rectangleClient);

      //         host_to_client(rectangleClient);

      //         m_pshapeaClip->add_item(__new(rectangle_shape(::rectangle_f64(rectangleClient))));

      //         m_pshapeaClip->add_item(__new(intersect_clip_shape()));

      //         pinteraction = pinteraction->get_parent();

      //      }

      //   }

      //   pgraphics->reset_clip();

      //   pgraphics->m_pointAddShapeTranslate = m_pointScroll;

      //   pgraphics->add_shapes(*m_pshapeaClip);

      //   //try
      ////{

      ////   ::rectangle_i32 rectangleClip;

      ////   ::aura::draw_context * pdrawcontext = pgraphics->::aura::simple_chain < ::aura::draw_context >::get_last();

      ////   ::rectangle_i32 rectangleClient;

      ////   bool bFirst = true;

      ////   if (pdrawcontext != nullptr)
      ////   {

      ////      rectangleClient = pdrawcontext->m_rectangleWindow;

      ////      screen_to_client(rectangleClient);

      ////      rectangleClient.bottom++;
      ////      rectangleClient.right++;

      ////      rectangleClip = rectangleClient;

      ////      bFirst = false;

      ////   }
      ////   
      ////   if(!m_pshapeaClip)
      ////   {

      ////      __construct_new(m_pshapeaClip);
      ////      
      ////      ::user::interaction * pinteraction = this;

      ////      ::rectangle_i32 rectangleFocus;

      ////      ::rectangle_i32 rectangleIntersect;

      ////      index i = 0;

      ////      while (pinteraction != nullptr)
      ////      {

      ////         if (i == 1)
      ////         {
      ////            // guess list client rectangle_i32 doesn't include header?
      ////            pinteraction->::user::interaction::client_rectangle(rectangleFocus);

      ////         }
      ////         else
      ////         {

      ////            pinteraction->client_rectangle(rectangleFocus);

      ////         }

      ////         pinteraction->client_to_screen(rectangleFocus);

      ////         screen_to_client(rectangleFocus);

      ////         rectangleFocus.bottom++;

      ////         rectangleFocus.right++;

      ////         m_pshapeaClip->add_item(__new(rectangle_shape(rectangleIntersect)));

      ////         m_pshapeaClip->add_item(__new(intersect_clip_shape));

      ////         i++;

      ////         pinteraction = pinteraction->get_parent();

      ////      }
      ////      
      ////   }
      ////   
      ////   pgraphics->add_shapes(*m_pshapeaClip);


      //}
      //catch (...)
      //{

      //   throw ::exception(::exception("no more a window"));

      //}


   }


   void list_header::_001OnDraw(::draw2d::graphics_pointer & pgraphics)
   {


      auto rectangleClient = client_rectangle();

      ::rectangle_i32 rectangleUpdate(rectangleClient);

      ::rectangle_f64 rectangleClipBox;

      pgraphics->get_clip_box(rectangleClipBox);

      rectangleClipBox.right--;

      if(rectangleClipBox.is_empty())
      {
         
         rectangleClipBox = rectangleClient;

      }

      rectangleUpdate.intersect(rectangleUpdate, rectangleClipBox);

      pgraphics->set_alpha_mode(::draw2d::e_alpha_mode_blend);

      auto pstyle = get_style(pgraphics);

      pgraphics->fill_rectangle(rectangleUpdate, get_color(pstyle, ::e_element_background));

      ::draw2d::item drawitem;
      drawitem.m_pgraphics = pgraphics;
      list * plist = m_plist;
      ::rectangle_i32 rectangleDivider;
      auto ppen = __create < ::draw2d::pen > ();

      auto color = get_color(pstyle, ::e_element_separator);

      ppen->create_solid(1.0, color);

      for(i32 iItem = 0; iItem < plist->_001GetColumnCount(); iItem++)
      {

         drawitem.itemID = iItem;

         GetItemRect(&drawitem.rcItem, element_item_Box, iItem);

         DrawItem(&drawitem);

         GetItemRect(&rectangleDivider, ElementDivider, iItem);

         pgraphics->set(ppen);

         pgraphics->set_current_point(rectangleDivider.left, rectangleDivider.top);

         pgraphics->line_to(rectangleDivider.left, rectangleDivider.bottom);

         //pgraphics->draw_inset_3d_rectangle(rectangleDivider, crButtonShadow, psession->get_default_color(COLOR_BTNHIGHLIGHT));

      }

   }


   i32 list_header::GetDividerWidth()
   {
      return 4;
   }


   ::point_i32 list_header::get_parent_context_offset()
   {

      ::pointer<::user::interaction>puser = get_parent();

      if (puser.is_null())
      {

         return point_i32(0, 0);

      }

      puser = puser->get_parent();

      if (puser.is_null())
      {

         return point_i32(0, 0);

      }

      return puser->get_context_offset();

   }


} // namespace user
