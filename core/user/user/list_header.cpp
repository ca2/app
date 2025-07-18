#include "framework.h"
#include "list.h"
#include "list_header.h"
#include "list_column.h"
#include "list_column_array.h"
#include "acme/constant/message.h"
#include "acme/prototype/collection/_array_binary_stream.h"
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

      ::int_rectangle rectangleColumn = pdrawitem->rcItem;

      int iColumn = pdrawitem->itemID;

      list * plist = m_plist;

      if (plist->m_pcolumna->get_visible(iColumn)->m_pimageHeader->is_set() && plist->m_pcolumna->get_visible(iColumn)->m_pimageHeader->area() > 0)
      {

         ::int_rectangle rectangle;

         rectangle.left() = 0;
         rectangle.top() = 0;
         rectangle.right() = plist->m_pcolumna->get_visible(iColumn)->m_pimageHeader->width();
         rectangle.bottom() = plist->m_pcolumna->get_visible(iColumn)->m_pimageHeader->height();

         ::int_rectangle rC;

         rC = rectangleColumn;

         rC.left() += 2;

         rectangle.Align(::e_align_left_center, rC);

         ::image::image_source imagesource(plist->m_pcolumna->get_visible(iColumn)->m_pimageHeader);

         ::image::image_drawing_options imagedrawingoptions(rectangle);

         ::image::image_drawing imagedrawing(imagedrawingoptions, imagesource);

         pgraphics->draw(imagedrawing);

         rectangleColumn.left() = rectangle.right() + m_iImageSpacing;

      }

      string str;

      auto papp = get_app();

      str = plist->_001GetColumnText(ItemToColumnKey(iColumn));

      if (str.has_character())
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

         //rectangleColumn.bottom() += rectangleColumn.height() * 2;

         pgraphics->draw_text(str, rectangleColumn, ealign, edrawtext);

      }

   }



   ::collection::index list_header::MapItemToOrder(::collection::index iItem)
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


   bool list_header::GetItemRect(::int_rectangle * prectangle, enum_element eelement, ::collection::index iItem)
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

      int x;

      if(plist->m_bGroup && plist->m_bLateralGroup)
      {

         x = plist->m_iLateralGroupWidth;

      }
      else
      {

         x = 0;

      }
      
      int xLast = x;
      
      for(int i = 0; i <= iItem; i++)
      {
         
         xLast = x;
         
         auto pcolumn = plist->m_pcolumna->get_visible(iItem);
         
         x += pcolumn->m_iWidth;

      }

      ::int_rectangle rectangle;

      rectangle = this->rectangle();

      rectangle.left() = xLast;

      rectangle.right() = x;

      if(eelement == e_element_item)
      {

         *prectangle = rectangle;

         return true;

      }

      if(eelement == element_item_Box)
      {

         rectangle.right() -= GetDividerWidth();

         *prectangle = rectangle;

         return true;

      }

      if(eelement == ElementDivider)
      {

         rectangle.left() = rectangle.right() - GetDividerWidth();

         *prectangle = rectangle;

         return true;

      }

      return true;

   }


   bool list_header::GetItemRect(::int_rectangle * prectangle, enum_element eelementLButtonDown, ::collection::index iItemLButtonDown, enum_element eelement, ::collection::index iItem)
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

            ::int_rectangle rectangleA;

            if(!GetItemRect(&rectangleA, element_item_Box, iItem - 1))
            {

               GetItemRect(&rectangleA, element_item_Box, iItem);

            }

            ::int_rectangle rectangle;

            GetItemRect(&rectangle, element_item_Box, iItem);

            ::int_rectangle rectangleB;

            if(!GetItemRect(&rectangleA, element_item_Box, iItem + 1))
            {

               GetItemRect(&rectangleA, element_item_Box, iItem);

            }

            rectangle.left() = rectangleA.left() + rectangleA.width() / 2;

            rectangle.right() = rectangleB.left() + rectangleB.width() / 2;

            *prectangle = rectangle;

            return true;

         }
         else if(iItem <= iItemLButtonDown - 1)
         {
            
            ::int_rectangle rectangleA;

            if(!GetItemRect(&rectangleA, element_item_Box, iItem - 1))
            {

               GetItemRect(&rectangleA, element_item_Box, iItem);

            }

            ::int_rectangle rectangle;

            GetItemRect(&rectangle, element_item_Box, iItem);

            rectangle.left() = rectangleA.left() + rectangleA.width() / 2;

            rectangle.right() = rectangle.left() + rectangle.width() / 2;

            *prectangle = rectangle;

            return true;

         }
         else if(iItem >= iItemLButtonDown + 1)
         {
            
            ::int_rectangle rectangleB;

            if(!GetItemRect(&rectangleB, element_item_Box, iItem + 1))
            {

               GetItemRect(&rectangleB, element_item_Box, iItem);

            }

            ::int_rectangle rectangle;

            GetItemRect(&rectangle, element_item_Box, iItem);

            rectangle.left() = rectangle.left() + rectangle.width() / 2;

            rectangle.right() = rectangleB.left() + rectangleB.width() / 2;

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

   bool list_header::hit_test(const ::int_point & point, enum_element & eelement, ::collection::index & iItemParam)
   {
      list * plist = m_plist;
      ::int_rectangle rectangle;
      for(int iItem = 0; iItem < plist->_001GetColumnCount(); iItem++)
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

   bool list_header::hit_test(const ::int_point & point, enum_element eelementLButtonDown, ::collection::index iItemLButtonDown, enum_element & eelement, ::collection::index & iItemParam)
   {
      list * plist = m_plist;
      ::int_rectangle rectangle;
      for(int iItem = 0; iItem < plist->_001GetColumnCount(); iItem++)
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


   ::collection::index list_header::ItemToColumnKey(::collection::index iItem)
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

      ::int_array iaWidth;

      if (bSave)
      {

         for (::collection::index iColumn = 0; iColumn < m_plist->_001GetColumnCount(); iColumn++)
         {

            auto pcolumn = m_plist->m_pcolumna->get_visible(iColumn);

            iaWidth.add(pcolumn->m_iWidth);

         }

         ::cast < ::database::client > pdatabaseclient = application();

         pdatabaseclient->datastream()->set(strDataKey, iaWidth);

         //if (!papp->datastream()->set(datakey, iaWidth))
         //{

         //   return false;

         //}

      }
      else
      {

         ::cast < ::database::client > pdatabaseclient = application();

         if (pdatabaseclient->datastream()->get(strDataKey, iaWidth))
         {

            ::collection::count c = minimum(iaWidth.get_count(), m_plist->_001GetColumnCount());

            for (::collection::index iColumn = 0; iColumn < c; iColumn++)
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

      auto pointCursor = pmouse->m_pointHost;

      host_to_client()(pointCursor);

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

      auto pointCursor = pmouse->m_pointHost;

      host_to_client()(pointCursor);

      if(m_bLButtonDown)
      {

         m_bLButtonDown = false;

         enum_element eelement;

         ::collection::index iItem;

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

                  ::collection::index iKeyA = plist->m_pcolumna->order_index(iItem);
                  ::collection::index iKeyB = plist->m_pcolumna->order_index(iItem);
                  ::collection::index iOrderA = plist->m_pcolumna->get_by_index(iKeyA)->m_iOrder;
                  ::collection::index iOrderB = plist->m_pcolumna->get_by_index(iKeyB)->m_iOrder;
                  plist->m_pcolumna->get_by_index(iKeyA)->m_iOrder = iOrderB;
                  plist->m_pcolumna->get_by_index(iKeyB)->m_iOrder = iOrderA;
                  plist->set_pending_column_update();
                  plist->DISaveOrder();
                  plist->set_need_redraw();
                  set_need_redraw();
               }

            }
            else if(m_eelementLButtonDown == ElementDivider)
            {
               
               ::int_rectangle rectangle;
               
               GetItemRect(&rectangle, e_element_item, m_iItemLButtonDown);
               
               rectangle.right() = pointCursor.x();
               
               int iNewWidth = rectangle.width();
               
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

      auto pointCursor = pmouse->m_pointHost;

      host_to_client()(pointCursor);

      list * plist = m_plist;

      enum_element eelement;

      ::collection::index iItem;

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

            defer_release_mouse_capture();

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
            
            ::int_rectangle rectangle;
            
            GetItemRect(&rectangle, e_element_item, m_iItemLButtonDown);
            
            rectangle.right() = pointCursor.x();
            
            int iNewWidth = rectangle.width();
            
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

      user_mouse_set_cursor(pmouse, pcursor);

      pmouse->m_bRet = false;

   }


   void list_header::on_message_left_button_double_click(::message::message * pmessage)
   {

      auto pmouse = pmessage->m_union.m_pmouse;

      auto pointCursor = pmouse->m_pointHost;

      host_to_client()(pointCursor);

      list * plist = m_plist;

      enum_element eelement;

      ::collection::index iItem;

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

      //   ::int_rectangle rectangleClip;

      //   ::aura::draw_context* pdrawcontext = pgraphics->::aura::simple_chain < ::aura::draw_context >::get_last();

      //   ::int_rectangle rectangleX;

      //   bool bFirst = true;

      //   string strType = ::type(this).name();

      //   if (strType.case_insensitive_contains("control_box"))
      //   {

      //      informationf("control box on clip");

      //   }

      //   if (pdrawcontext != nullptr)
      //   {

      //      rectangleX = pdrawcontext->m_rectangleWindow;

      //      screen_to_client(rectangleX, e_layout_design);

      //      rectangleX.bottom()++;
      //      rectangleX.right()++;

      //      rectangleClip = rectangleX;

      //      bFirst = false;

      //   }

      //   ::user::interaction* pinteraction = this;

      //   if (!m_pshapeaClip)
      //   {

      //      __construct_new(m_pshapeaClip);

      //      ::int_rectangle rectangleIntersect;

      //      while (pinteraction != nullptr)
      //      {

      //         pinteraction->rectangle(rectangleX);

      //         pinteraction->client_to_host(rectangleX);

      //         host_to_client(rectangleX);

      //         m_pshapeaClip->add_item(__allocate rectangle_shape(::double_rectangle(rectangleX)));

      //         m_pshapeaClip->add_item(__allocate intersect_clip_shape());

      //         pinteraction = pinteraction->get_parent();

      //      }

      //   }

      //   pgraphics->reset_clip();

      //   pgraphics->m_pointAddShapeTranslate = m_pointScroll;

      //   pgraphics->add_shapes(*m_pshapeaClip);

      //   //try
      ////{

      ////   ::int_rectangle rectangleClip;

      ////   ::aura::draw_context * pdrawcontext = pgraphics->::aura::simple_chain < ::aura::draw_context >::get_last();

      ////   ::int_rectangle rectangleX;

      ////   bool bFirst = true;

      ////   if (pdrawcontext != nullptr)
      ////   {

      ////      rectangleX = pdrawcontext->m_rectangleWindow;

      ////      screen_to_client(rectangleX);

      ////      rectangleX.bottom()++;
      ////      rectangleX.right()++;

      ////      rectangleClip = rectangleX;

      ////      bFirst = false;

      ////   }
      ////   
      ////   if(!m_pshapeaClip)
      ////   {

      ////      __construct_new(m_pshapeaClip);
      ////      
      ////      ::user::interaction * pinteraction = this;

      ////      ::int_rectangle rectangleFocus;

      ////      ::int_rectangle rectangleIntersect;

      ////      ::collection::index i = 0;

      ////      while (pinteraction != nullptr)
      ////      {

      ////         if (i == 1)
      ////         {
      ////            // guess list client int_rectangle doesn't include header?
      ////            pinteraction->::user::interaction::this->rectangle(rectangleFocus);

      ////         }
      ////         else
      ////         {

      ////            pinteraction->rectangle(rectangleFocus);

      ////         }

      ////         pinteraction->client_to_screen(rectangleFocus);

      ////         screen_to_client(rectangleFocus);

      ////         rectangleFocus.bottom()++;

      ////         rectangleFocus.right()++;

      ////         m_pshapeaClip->add_item(__allocate rectangle_shape(rectangleIntersect));

      ////         m_pshapeaClip->add_item(__allocate intersect_clip_shape());

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


      auto rectangleX = this->rectangle();

      ::int_rectangle rectangleUpdate(rectangleX);

      ::double_rectangle rectangleClipBox;

      pgraphics->get_clip_box(rectangleClipBox);

      rectangleClipBox.right()--;

      if(rectangleClipBox.is_empty())
      {
         
         rectangleClipBox = rectangleX;

      }

      rectangleUpdate.intersect(rectangleUpdate, rectangleClipBox);

      pgraphics->set_alpha_mode(::draw2d::e_alpha_mode_blend);

      auto pstyle = get_style(pgraphics);

      pgraphics->fill_rectangle(rectangleUpdate, get_color(pstyle, ::e_element_background));

      ::draw2d::item drawitem;
      drawitem.m_pgraphics = pgraphics;
      list * plist = m_plist;
      ::int_rectangle rectangleDivider;
      auto ppen = __øcreate < ::draw2d::pen > ();

      auto color = get_color(pstyle, ::e_element_separator);

      ppen->create_solid(1.0, color);

      for(int iItem = 0; iItem < plist->_001GetColumnCount(); iItem++)
      {

         drawitem.itemID = iItem;

         GetItemRect(&drawitem.rcItem, element_item_Box, iItem);

         DrawItem(&drawitem);

         GetItemRect(&rectangleDivider, ElementDivider, iItem);

         pgraphics->set(ppen);

         pgraphics->line(
            rectangleDivider.left(), rectangleDivider.top(),
               rectangleDivider.left(), rectangleDivider.bottom());

         //pgraphics->draw_inset_3d_rectangle(rectangleDivider, crButtonShadow, psession->get_default_color(COLOR_BTNHIGHLIGHT));

      }

   }


   int list_header::GetDividerWidth()
   {
      return 4;
   }


   ::double_point list_header::get_parent_context_offset()
   {

      ::pointer<::user::interaction>puser = get_parent();

      if (puser.is_null())
      {

         return {};

      }

      puser = puser->get_parent();

      if (puser.is_null())
      {

         return {};

      }

      return puser->get_context_offset();

   }


} // namespace user
