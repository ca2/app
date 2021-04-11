#include "framework.h"
#include "core/user/user/_user.h"
#include "acme/const/timer.h"


#define DBLCLKMS 500_ms


CLASS_DECL_CORE index_array array_translate_a_array(index_biunique & ia, index_array iaNew, index_array iaOld);

namespace user
{

   auto predicate_list_compare_key = [](auto& p1, auto& p2)
   {

      return (p1->get_index() - p2->get_index()) < 0;

   };


   list::list()
   {

      m_econtroltype = e_control_type_list;

      m_bHighHighLight = true;

      //m_ecolorBackground = color_list_background;

      m_iImageSpacing = 2;
      m_dIconSaturation = 1.0;
      m_dIconLightness = 1.0;
      m_dIconOpacity = 1.0;

      m_iIconBlur = 0;

      m_iIconBlurRadius = 0;

      m_iTextSpreadRadius = 0;

      m_iTextBlurRadius = 0;

      m_iTextBlur = 0;

      m_plist = this;

      m_eview = impact_report;

      m_columna.Initialize(this);

      m_bHeaderCtrl = true;
      m_bSingleColumnMode = false;

      m_pdrawlistitem = nullptr;


      m_bAutoCreateListHeader = true;


      m_bMorePlain = false;

      m_bSelect = true;

   }


   list::~list()
   {

      ::acme::del(m_pdrawlistitem);

   }


   void list::install_message_routing(::channel * pchannel)
   {

      ::user::mesh::install_message_routing(pchannel);

      MESSAGE_LINK(e_message_size, pchannel, this, &list::_001OnSize);
      MESSAGE_LINK(e_message_vscroll, pchannel, this, &list::_001OnVScroll);
      MESSAGE_LINK(e_message_hscroll, pchannel, this, &list::_001OnHScroll);
      MESSAGE_LINK(e_message_mouse_leave, pchannel, this, &list::on_message_mouse_leave);

      MESSAGE_LINK(e_message_left_button_down, pchannel, this, &list::on_message_left_button_down);
      MESSAGE_LINK(e_message_left_button_up, pchannel, this, &list::on_message_left_button_up);
      MESSAGE_LINK(e_message_left_button_double_click, pchannel, this, &list::_001OnLButtonDblClk);
      MESSAGE_LINK(e_message_right_button_down, pchannel, this, &list::on_message_right_button_down);

      MESSAGE_LINK(e_message_mouse_move, pchannel, this, &list::on_message_mouse_move);

      MESSAGE_LINK(e_message_key_down, pchannel, this, &list::_001OnKeyDown);

      MESSAGE_LINK(e_message_create, pchannel, this, &list::on_message_create);
      //      //MESSAGE_LINK(e_message_timer,           pchannel, this, &list::_001OnTimer);
      connect_command("list_view_auto_arrange", &list::_001OnListViewAutoArrange);
      connect_command_probe("list_view_auto_arrange", &list::_001OnUpdateListViewAutoArrange);
   }

   bool list::CreateHeaderCtrl()
   {
      if (m_plistheader != nullptr)
      {
         if (!m_plistheader->is_window())
         {
            bool bOk = m_plistheader->create_child(this);
            //bool bOk = m_plistheader->create_window(
            //           nullptr,
            //           "",
            //           WS_CHILD
            //           | WS_VISIBLE
            //           | HDS_FULLDRAG
            //           | HDS_HOTTRACK
            //           | HDS_DRAGDROP,
            //           this,
            //           1023) != 0;
            //if (bOk)
            //{
            //   m_plistheader->m_font = m_font;
            //}
            return bOk;
         }
         else
            return true;
         return false;
      }
      return false;
   }


   void list::_001OnNcDraw(::draw2d::graphics_pointer & pgraphics)
   {

      ::user::mesh::_001OnNcDraw(pgraphics);

      //__throw(todo("scroll"));
      //defer_draw_scroll_gap(pgraphics);

   }


   void list::_001OnDraw(::draw2d::graphics_pointer & pgraphics)
   {

      m_penFocused->create_solid(2, argb(255, 0, 255, 255));

      if (m_bHighHighLight)
      {

         m_penHighlight->create_solid(2, argb(255, 0, 255, 255));

      }
      else
      {

         m_penHighlight->create_solid(2, argb(60, 0, 130, 130));

      }

      pgraphics->set_text_rendering_hint(::write_text::e_rendering_anti_alias_grid_fit);

      if (m_bLockViewUpdate)
      {

         return;

      }

      ::user::interaction::_001OnDraw(pgraphics);

      if (is_null(m_pmeshdata.m_p))
      {

         return;

      }

      synchronous_lock synchronouslock(m_pmeshdata->mutex());

      ::rectangle_i32 rectClient = get_client_rect();

      auto pointOffset = get_viewport_offset();

      pgraphics->set_alpha_mode(::draw2d::alpha_mode_blend);

      if (m_bTopText)
      {

         ::draw2d::brush_pointer brushText(e_create);

         auto pstyle = get_style(pgraphics);

         brushText->create_solid(get_color(pstyle,::user::e_element_text));

         auto pointViewportOrg = pgraphics->GetViewportOrg();

         pgraphics->set(brushText);

         ::size_array sizea;

         m_dcextension.GetTextExtent(pgraphics, m_strTopText, sizea);

         index x = 0;

         index right = (index)rectClient.right;

         double y = m_dItemHeight;

         index iStart = 0;

         index iNewStart = 0;

         index w;

         for (index i = 0; i < sizea.get_size(); i++)
         {

            if ((sizea[i].cx - x > right)
                  || i == sizea.get_upper_bound())
            {

               ::rectangle_i32 rectangle;

               rectangle.top = ::i32(y - pointOffset.y);

               if (i == 0)
               {
                  w = sizea[0].cx - x;
                  x = sizea[0].cx;
                  y += sizea[0].cy;
                  iNewStart = 0;

               }
               else
               {
                  w = sizea[i - 1].cx - x;
                  x = sizea[i - 1].cx;
                  y += sizea[i - 1].cy;
                  iNewStart = i - 1;
               }
               rectangle.left = ::i32(-pointOffset.x);
               rectangle.right = rectClient.right;
               rectangle.bottom = ::i32(y - pointOffset.y);

               pgraphics->_DrawText(m_strTopText.Mid(iStart, i - iStart), rectangle, e_align_left);
               iStart = iNewStart;
            }
         }

         pgraphics->SetViewportOrg(pointViewportOrg);

      }

      if (m_pdrawlistitem == nullptr)
      {

         return;

      }

      m_pdrawlistitem->m_pgraphics = pgraphics;
      m_pdrawlistitem->m_iItemRectItem = -1;
      m_pdrawlistitem->m_iSubItemRectOrder = -1;
      m_pdrawlistitem->m_iSubItemRectSubItem = -1;
      m_pdrawlistitem->m_iSubItemRectItem = -1;
      m_pdrawlistitem->m_iSubItemRectColumn = -1;
      m_pdrawlistitem->m_iColumn = -1;
      m_pdrawlistitem->m_iColumnWidth = 0;

      ::rectangle_i32 rectItem;
      ::rectangle_i32 rectIntersect;

      auto iItemCount = m_nDisplayCount;

      auto iItemFirst = m_iTopDisplayIndex;

      decltype(iItemCount) iItemLast;

      if (m_eview == impact_icon)
      {

         iItemLast = iItemCount;

      }
      else
      {

         iItemLast = minimum(m_nItemCount - 1, iItemFirst + m_nDisplayCount - 1);

      }

      if (iItemFirst < 0)
      {

         return;

      }

      _001DrawItems(m_pdrawlistitem, (::index) iItemFirst, (::index) iItemLast);

      if (m_bGroup && m_bLateralGroup)
      {

         index iGroupFirst = 0;
         index iGroupFirstTopIndex = 0;
         for (; iGroupFirst < m_nGroupCount; iGroupFirst++)
         {
            if (iItemFirst >= iGroupFirstTopIndex && iItemFirst < (iGroupFirstTopIndex + _001GetGroupItemCount((::index) iGroupFirst)))
               break;
         }
         index iGroupLast = iGroupFirst;
         index iGroupLastTopIndex = iGroupFirstTopIndex;
         for (; iGroupLast < m_nGroupCount; iGroupLast++)
         {
            if (iItemLast >= iGroupLastTopIndex && iItemLast < (iGroupLastTopIndex + _001GetGroupItemCount((::index) iGroupLast)))
               break;
         }

         _001DrawGroups(m_pdrawlistitem, (::index) iGroupFirst, (::index) iGroupLast, (::index) iItemFirst, (::index) iItemLast);

      }

      if (m_eview == impact_icon)
      {

         if (m_bDrag && m_iItemLButtonDown < 0)
         {

            int x1 = m_pointLButtonDown1.x;

            int x2 = m_pointLButtonUp.x;

            __sort(x1, x2);

            int y1 = m_pointLButtonDown1.y;

            int y2 = m_pointLButtonUp.y;

            __sort(y1, y2);

            pgraphics->set_alpha_mode(::draw2d::alpha_mode_blend);
            
            pgraphics->fill_rectangle(::rectangle_f64(x1, y1, x2, y2), argb(90, 250, 250, 255));

            pgraphics->draw_rectangle(::rectangle_f64(x1, y1, x2, y2), argb(192, 192, 192, 208));

         }

      }

   }



















   void list::_001DrawGroups(draw_list_item * pdrawitem, index iGroupFirst, index iGroupLast, index iItemFirst, index iItemLast)
   {

      UNREFERENCED_PARAMETER(iItemFirst);
      UNREFERENCED_PARAMETER(iItemLast);

      index iGroup;

      ::rectangle_i32 rectClient;

      ::rectangle_i32 rectIntersect;

      get_client_rect(rectClient);

      bool bHoverFont = false;

      pdrawitem->m_pgraphics->set_font(this, ::user::e_element_none);
      //pdrawitem->m_pgraphics->set(pfont);

      m_pdrawlistitem->m_pfont = pdrawitem->m_pgraphics->m_pfont;

      for (iGroup = iGroupFirst; iGroup <= iGroupLast; iGroup++)
      {

         m_pdrawlistitem->m_iGroup = iGroup;

         _001GetGroupRect(m_pdrawlistitem);

         if (!m_pdrawlistitem->m_bOk)
            continue;

         if (!rectIntersect.intersect(m_pdrawlistitem->m_rectItem, rectClient))
            continue;

         if (iGroup == m_iGroupHover)
         {
            if (!bHoverFont)
            {
               pdrawitem->m_pgraphics->set_font(this, ::user::e_element_none, e_state_hover);
               //pdrawitem->m_pgraphics->set(m_pdrawlistitem->m_pfont);
            }
         }
         else
         {
            if (bHoverFont)
            {
               //m_pdrawlistitem->m_pfont = pfont;
               //pdrawitem->m_pgraphics->set(pfont);
               pdrawitem->m_pgraphics->set_font(this, ::user::e_element_none);
            }
         }

         _001DrawGroup(m_pdrawlistitem);

      }

   }



















   void list::_001DrawGroup(draw_list_item * pdrawitem)
   {

      /*if(m_bGroupCustomDraw)
      {
         pdrawitem->m_bListSubItemHover = pdrawitem->m_bListItemHover && (pdrawitem->m_iSubItem == m_iSubItemHover);
         pdrawitem->m_bFocus = false;
         return;
      }*/

      _001GetElementRect(pdrawitem, ::user::list::element_group_image);
      if (pdrawitem->m_bOk)
      {
         pdrawitem->draw_group_image();
      }

      ::count nItem = _001GetGroupMetaItemCount(pdrawitem->m_iGroup);

      for (pdrawitem->m_iItem = 0; pdrawitem->m_iItem < nItem; pdrawitem->m_iItem++)
      {
         _001GetElementRect(pdrawitem, ::user::list::element_group_item_text);
         if (pdrawitem->m_bOk)
         {
            _001GetGroupText(pdrawitem);
            pdrawitem->draw_text();
         }
      }



   }


   void list::_001DrawItems(draw_list_item * pdrawitem, index iItemFirst, index iItemLast)
   {

      ::rectangle_i32 rectClient;

      get_client_rect(rectClient);

      ::rectangle_i32 rectIntersect;

      rectClient.offset(get_viewport_offset());

      m_pdrawlistitem->m_ealign = get_draw_text_align(m_eview);

      m_pdrawlistitem->m_edrawtext = get_draw_text_flags(m_eview);

      bool bHoverFont = false;

      pdrawitem->m_pgraphics->set_font(this, ::user::e_element_none);

      pdrawitem->m_pfont = pdrawitem->m_pgraphics->m_pfont;

      index iDisplayItem;

      for (iDisplayItem = iItemFirst; iDisplayItem <= iItemLast; iDisplayItem++)
      {

         m_pdrawlistitem->m_iItem = _001DisplayToStrict(iDisplayItem);

         m_pdrawlistitem->m_iDisplayItem = iDisplayItem;

         if (m_bGroup)
         {

            m_pdrawlistitem->m_iGroupTopDisplayIndex = 0;

            for (m_pdrawlistitem->m_iGroup = 0; m_pdrawlistitem->m_iGroup < m_nGroupCount; m_pdrawlistitem->m_iGroup++)
            {

               m_pdrawlistitem->m_iGroupCount = _001GetGroupItemCount(m_pdrawlistitem->m_iGroup);

               if (iDisplayItem >= m_pdrawlistitem->m_iGroupTopDisplayIndex
                     && iDisplayItem < (m_pdrawlistitem->m_iGroupTopDisplayIndex + m_pdrawlistitem->m_iGroupCount))
               {

                  break;

               }

            }

         }

         _001GetItemRect(m_pdrawlistitem);

         if (!m_pdrawlistitem->m_bOk)
         {

            continue;

         }

         if (!rectIntersect.intersect(m_pdrawlistitem->m_rectItem, rectClient))
         {

            continue;

         }

         if (iDisplayItem == m_iDisplayItemHover)
         {

            if (!bHoverFont)
            {

               bHoverFont = true;

               pdrawitem->m_pgraphics->set_font(this, ::user::e_element_none, ::user::e_state_hover);

            }

         }
         else
         {

            if (bHoverFont)
            {

               bHoverFont = false;

               pdrawitem->m_pgraphics->set_font(this, ::user::e_element_none);

            }

         }

         {

#ifdef _DEBUG

            auto tickStart = millis::now();

#endif

            _001DrawItem(m_pdrawlistitem);

#ifdef _DEBUG

            auto tickEnd = millis::now();

            millis tickElapsed = tickEnd - tickStart;

            if (tickElapsed > 100)
            {

               output_debug_string("\ndrawing took " + __str(tickElapsed) + "!!");
               output_debug_string("\ndrawing took more than 100ms to complete!!");
               output_debug_string("\n");

               // let's try to reproduce the offending scenario
               //_001DrawItem(m_pdrawlistitem);

            }

#endif

         }


      }

   }


   void list::_001DrawItem(draw_list_item * pdrawitem)
   {

      pdrawitem->m_iState = 0;

      range & rangeSelection = m_rangeSelection;

      range & rangeHighlight = m_rangeHighlight;

      if (pdrawitem->m_iItem < 0)
      {

         return;

      }

      pdrawitem->m_bListItemHover = pdrawitem->m_iDisplayItem == m_iDisplayItemHover &&
                                    (m_eview != impact_icon ||
                                     ((m_piconlayout->m_iaDisplayToStrict.get_b((::index) m_iDisplayItemHover) >= 0 && m_piconlayout->m_iaDisplayToStrict.get_b((::index) m_iDisplayItemHover) < m_nItemCount)));

      if (pdrawitem->m_bListItemHover)
      {

         if (!pdrawitem->m_plist->m_bMorePlain)
         {

            pdrawitem->m_pgraphics->set_alpha_mode(::draw2d::alpha_mode_blend);

            pdrawitem->m_pgraphics->draw_rectangle(pdrawitem->m_rectItem, argb(80, 235, 235, 255));

            pdrawitem->m_pgraphics->fill_rectangle(pdrawitem->m_rectItem, argb(40, 255, 255, 255));

         }

      }

      pdrawitem->m_bListItemSelected = (m_eview != impact_icon || is_valid_display_item(pdrawitem->m_iItem)) && rangeSelection.has_item(pdrawitem->m_iItem);

      if (pdrawitem->m_bListItemHover)
      {

         pdrawitem->m_iState |= ItemStateHover;

      }

      if (pdrawitem->m_bListItemSelected)
      {

         pdrawitem->m_iState |= ItemStateSelected;

      }

      auto pstyle = get_style(pdrawitem->m_pgraphics);

      pdrawitem->m_colorText = get_color(pstyle, ::user::e_element_item_text);

      pdrawitem->m_colorTextBackground = 0;

      pdrawitem->m_colorItemBackground = 0;

      pdrawitem->update_item_color();

      if (pdrawitem->m_bListItemSelected)
      {

         auto psession = get_session();

         if (pdrawitem->m_plist->m_bMorePlain)
         {

         }
         else if (psession->m_paurasession->savings().is_trying_to_save(::e_resource_processing))
         {

            pdrawitem->m_pgraphics->fill_rectangle(pdrawitem->m_rectItem, argb(255, 96, 96, 96));

         }
         else
         {

            pdrawitem->m_pgraphics->fill_rectangle(pdrawitem->m_rectItem, pdrawitem->m_colorItemBackground);

         }

      }
      else if (pdrawitem->m_colorItemBackground.is_ok())
      {

         pdrawitem->m_pgraphics->fill_rectangle(pdrawitem->m_rectItem, pdrawitem->m_colorItemBackground);

      }

      string str;

      index iColumnCount;

      if (m_eview == impact_icon)
      {

         iColumnCount = 1;

      }
      else
      {

         iColumnCount = m_columna.VisibleGetCount();

      }

      pdrawitem->m_iSubItemRectOrder = -1;

      pdrawitem->m_iSubItemRectSubItem = -1;

      pdrawitem->m_iSubItemRectColumn = -1;

      for (index iVisible = 0; iVisible < iColumnCount; iVisible++)
      {

         pdrawitem->m_iColumn = iVisible;

         pdrawitem->m_iOrder = _001MapColumnToOrder(iVisible);

         if (pdrawitem->m_iOrder < 0)
         {

            continue;

         }

         pdrawitem->m_pcolumn = m_columna.get_visible(pdrawitem->m_iColumn);

         if (pdrawitem->m_pcolumn != nullptr)
         {

            pdrawitem->m_iSubItem = pdrawitem->m_pcolumn->subitem_index();

         }

         _001GetSubItemRect(pdrawitem);

         if (!pdrawitem->m_bOk)
         {

            continue;

         }

         _001DrawSubItem(pdrawitem);

      }

      if (rangeHighlight.has_item(pdrawitem->m_iDisplayItem))
      {

         ::draw2d::pen_pointer penHighlight(e_create);

         ::draw2d::pen * ppenHighlight = _001GetPenHighlight();

         ::rectangle_i32 rectHighlight(pdrawitem->m_rectItem);

         rectHighlight.inflate(8, 0, 8, -1);

         pdrawitem->m_pgraphics->set(ppenHighlight);

         pdrawitem->m_pgraphics->draw_rectangle(rectHighlight);

      }

      if (pdrawitem->m_bListItemSelected)
      {

         if (pdrawitem->m_plist->m_bMorePlain)
         {

            auto color = get_color(pstyle, ::user::e_element_item_text);

            if (!color.is_ok())
            {

               color = argb(255, 96, 96, 96);

            }

            pdrawitem->m_pgraphics->set_alpha_mode(::draw2d::alpha_mode_blend);

            color.alpha = 90;

            pdrawitem->m_pgraphics->fill_rectangle(pdrawitem->m_rectItem, color);

         }

      }

   }


   void list::_001DrawSubItem(draw_list_item * pdrawitem)
   {

      if (pdrawitem->m_pcolumn->m_bCustomDraw)
      {

         pdrawitem->m_bListSubItemHover = pdrawitem->m_bListItemHover && (pdrawitem->m_iSubItem == m_iSubItemHover);

         pdrawitem->m_bFocus = false;

         return;

      }

      if (pdrawitem->m_bListItemHover)
      {

         pdrawitem->m_pgraphics->set_font(this, ::user::e_element_none, ::user::e_state_hover);

      }
      else
      {

         pdrawitem->m_pgraphics->set_font(this, ::user::e_element_none);

      }

      pdrawitem->m_iListItem = -1;

      pdrawitem->m_bOk = false;

      _001GetElementRect(pdrawitem, ::user::list::element_image);

      if (pdrawitem->m_bOk)
      {

         try
         {

            _001GetItemImage(pdrawitem);

         }
         catch (...)
         {

            pdrawitem->m_bOk = false;

         }

         pdrawitem->draw_image();

      }

      pdrawitem->m_iListItem = -1;

      _001GetElementRect(pdrawitem, ::user::mesh::e_element_text);

      if (pdrawitem->m_bOk)
      {

         try
         {

            _001GetItemText(pdrawitem);

         }
         catch (...)
         {

            pdrawitem->m_bOk = false;

         }

         if (pdrawitem->m_bOk)
         {

            pdrawitem->draw_text();

         }

      }

   }


   ::count list::_001GetColumnCount()
   {

      return m_columna.VisibleGetCount();

   }


   void list::_001OnSize(::message::message * pmessage)
   {

      UNREFERENCED_PARAMETER(pmessage);

   }


   void list::on_layout(::draw2d::graphics_pointer & pgraphics)
   {

      synchronous_lock synchronouslock(mutex());

      auto rect1 = get_client_rect();

      if (!rect1)
      {

         return;

      }

      //if (m_puserstyle == nullptr)
      //{

      //   m_puserstyle = top_level_frame();

      //}

      //if (m_puserstyle == nullptr)
      //{

      //   m_puserstyle = papplication->userstyle();

      //}

      if (m_bTopText)
      {

         _001LayoutTopText(pgraphics);

      }

      if (m_eview == impact_icon)
      {

         ::rectangle_i32 rectClient;

         get_client_rect(rectClient);

         index iIconSize;

         if (m_columna.get_count() > 0)
         {

            iIconSize = maximum(32, m_columna[0]->m_sizeIcon.cy);

         }
         else
         {

            iIconSize = 32;

         }

      }

      ::count iCount = m_nItemCount;

      i32 iMaxWidth = 0;

      i32 iWidth;

      if (m_bSingleColumnMode)
      {

         for (index i = 0; i < iCount; i++)
         {

            iWidth = _001CalcItemWidth(pgraphics, i, 0);

            if (iWidth > iMaxWidth)
            {

               iMaxWidth = iWidth;

            }

         }

         m_iItemWidth = iMaxWidth;

         m_columna.get_visible(0)->m_iWidth = iMaxWidth;

      }

      LayoutHeaderCtrl();

      on_change_view_size(pgraphics);

      LayoutHeaderCtrl();

      update_icon_list_view_sort();

   }


   bool list::_001OnUpdateItemCount(u32 dwFlags)
   {

      UNREFERENCED_PARAMETER(dwFlags);

      auto pointOffset = get_viewport_offset();

      ::count nCount = _001GetItemCount();

      if (nCount < 0)
      {

         m_nItemCount = nCount;

         return false;

      }

      ::count nGroupCount = 1;

      if (m_bGroup)
      {

         nGroupCount = _001GetGroupCount();

         if (nGroupCount < 0)
         {

            m_nGroupCount = nGroupCount;

            return false;

         }

      }

      {

         synchronous_lock synchronouslock(mutex());

         m_nItemCount = nCount;

         if (m_bGroup)
         {
            m_nGroupCount = nGroupCount;
         }

         if (m_eview == impact_icon)
         {

            update_icon_list_view_sort();

         }
         else
         {

            index iStart = m_pmeshlayout->m_iaDisplayToStrict.get_count();

            index iEnd = m_nItemCount - 1;

            m_pmeshlayout->m_iaDisplayToStrict.allocate((::count) m_nItemCount);

            for (index iStrict = iStart; iStrict <= iEnd; iStrict++)
            {

               m_pmeshlayout->m_iaDisplayToStrict.set_at((::index) iStrict, (::index) iStrict);

            }

         }

      }

      if (m_bFilter1)
      {

         FilterApply();

      }

      CacheHint();

      set_need_layout();

      //TRACE("list::_001OnUpdateItemCount ItemCount %d\n", m_nItemCount);

      //if (m_bGroup)
      //{

        // TRACE("list::_001OnUpdateItemCount GroupCount %d\n", m_nGroupCount);

      //}

      queue_graphics_call([this, pointOffset](::draw2d::graphics_pointer & pgraphics)
         {

            set_viewport_offset(pgraphics, pointOffset.x, pointOffset.y);

         });

      set_need_redraw();

      return true;

   }


   void list::on_change_view_size(::draw2d::graphics_pointer & pgraphics)
   {

      m_iTopDisplayIndex = _001CalcDisplayTopIndex();

      index iLow = 0;

      for (m_iTopGroup = 0; m_iTopGroup < m_nGroupCount; m_iTopGroup++)
      {

         if (m_iTopDisplayIndex >= iLow && m_iTopDisplayIndex < (iLow + _001GetGroupItemCount((::index) m_iTopGroup)))
         {

            break;

         }

      }

      m_nDisplayCount = _001CalcDisplayItemCount();

      ::rectangle_i32 rectangle;

      if (m_eview == impact_list)
      {

         if (m_nItemCount == 0)
         {

            rectangle = ::rectangle_i32(0, 0, 0, 0);

         }
         else
         {

            ::rectangle_i32 rectClient;

            get_client_rect(&rectClient);

            draw_list_item itemFirst(this);

            itemFirst.m_iItem = 0;

            itemFirst.m_iDisplayItem = 0;

            _001GetItemRect(&itemFirst);

            rectangle.top = rectClient.top;

            rectangle.bottom = rectClient.bottom;

            rectangle.left = rectClient.left;

            if (m_dItemHeight <= 0 || rectClient.height() <= 0)
            {

               rectangle.right = rectClient.right;

            }
            else
            {

               rectangle.right = (::i32)minimum(
                            rectClient.left +
                            m_nItemCount * itemFirst.m_rectItem.width() * m_dItemHeight /
                            rectClient.height()
                            + itemFirst.m_rectItem.width(), MAXI32);

            }

         }

      }
      else if (m_eview == impact_report)
      {

         if (m_nItemCount == 0)
         {

            rectangle = ::rectangle_i32(0, 0, 0, 0);

         }
         else
         {

            draw_list_item itemFirst(this);

            itemFirst.m_iItem = 0;

            itemFirst.m_iDisplayItem = 0;

            itemFirst.m_iGroup = 0;

            _001GetItemRect(&itemFirst);

            rectangle = itemFirst.m_rectItem;

            rectangle.top = 0;

            rectangle.bottom = (::i32) ((_001GetItemCount() + (m_bHeaderCtrl ? 1 : 0)) * m_dItemHeight);

         }

      }
      else if (m_eview == impact_icon)
      {

         rectangle = ::rectangle_i32(0, 0, 0, 0);

         draw_list_item itemFirst(this);

         itemFirst.m_iItem = 0;

         itemFirst.m_iDisplayItem = 0;

         _001GetItemRect(&itemFirst);

         if (itemFirst.m_bOk)
         {

            draw_list_item itemLast(this);

            if (m_nItemCount <= 0)
            {

               itemLast.m_iDisplayItem = 0;

               itemLast.m_iItem = 0;

            }
            else
            {

               itemLast.m_iDisplayItem = m_nItemCount - 1;

               itemLast.m_iItem = m_nItemCount - 1;

            }


            _001GetItemRect(&itemLast);

            if (itemLast.m_bOk)
            {

               draw_list_item itemTopRight(this);

               ::rectangle_i32 rectClient;

               get_client_rect(&rectClient);

               itemTopRight.m_iItem = (index)maximum(1, rectClient.width() / get_item_size().cx) - 1;

               itemTopRight.m_iDisplayItem = itemTopRight.m_iItem;

               _001GetItemRect(&itemTopRight);

               if (itemTopRight.m_bOk)
               {

                  rectangle.unite(itemFirst.m_rectItem, itemLast.m_rectItem);

                  rectangle.unite(rectangle, itemTopRight.m_rectItem);

               }

            }

         }

      }

      set_total_size(rectangle.size());

      ::user::scroll_base::on_change_view_size(pgraphics);

   }


   void list::_001OnInitialize()
   {

   }


   __pointer(list_column) list::new_list_column()
   {

      auto pcolumn = __new(list_column());

      m_columna.add(pcolumn);

      pcolumn->m_iColumn = m_columna.get_upper_bound();

      return pcolumn;

   }


   void list::_001OnAddColumn(list_column * pcolumn)
   {

   }


   


   //list_column & list_column::operator = (const list_column & column)
   //{

   //   m_iOrder = pcolumn->m_iOrder;
   //   m_iSubItem = pcolumn->m_iSubItem;
   //   m_iColumn = pcolumn->m_iColumn;
   //   m_uiText = pcolumn->m_uiText;
   //   m_iWidth = pcolumn->m_iWidth;
   //   m_uiSmallBitmap = pcolumn->m_uiSmallBitmap;
   //   m_colorSmallMask = pcolumn->m_colorSmallMask;
   //   m_iSmallImageWidth = pcolumn->m_iSmallImageWidth;
   //   m_pil = pcolumn->m_pil;
   //   m_pilHover = pcolumn->m_pilHover;
   //   m_bVisible = pcolumn->m_bVisible;
   //   m_iControl = pcolumn->m_iControl;
   //   m_datakey = pcolumn->m_datakey;
   //   m_bIcon = pcolumn->m_bIcon;
   //   m_sizeIcon = pcolumn.m_sizeIcon;
   //   m_bCustomDraw = pcolumn->m_bCustomDraw;
   //   m_mapIcon = pcolumn->m_mapIcon;
   //   m_bEditOnSecondClick = pcolumn->m_bEditOnSecondClick;
   //   m_pimageHeader = pcolumn->m_pimageHeader;

   //   return *this;

   //}


   void list::_thread_data_update_visible_subitem()
   {

   }


   i32 list::_001CalcItemHeight(::user::style * pstyle, int iBaseHeight)
   {

      return (i32) (iBaseHeight * get_double(pstyle, ::user::e_double_list_item_height_rate, ::user::e_state_none, 1.0));

   }


   void list::_001OnColumnChange()
   {

      for (auto & pcolumn : m_columna.ptra())
      {

         if (pcolumn->m_bNew)
         {

            pcolumn->m_bNew = false;

            _001OnAddColumn(pcolumn);

         }

      }

      index iItemHeight = 0;

      index iItemWidth = 0;

      ::rectangle_i32 rectangle;

      string str;

      index iColumn;

      iptr iColumnWidth;

      //defer_fork("data_update_visible_subitem",
      //   [this]()
      //{

      //   _thread_data_update_visible_subitem();

      //});

      ::image_list::info ii;

      for (iColumn = 0; iColumn < m_columna.VisibleGetCount(); iColumn++)
      {

         list_column * pcolumn = m_columna.get_visible(iColumn);

         iColumnWidth = pcolumn->m_iWidth;

         _001CreateImageList(pcolumn);

         if (iColumnWidth >= 0)
         {

            iItemWidth += iColumnWidth;

         }

         if (pcolumn->m_pil != nullptr && pcolumn->m_pil->get_image_count() > 0)
         {

            pcolumn->m_pil->get_image_info(0, &ii);

            rectangle = ii.m_rectangle;

            if (rectangle.height() + 2 > iItemHeight)
            {

               iItemHeight = (index)rectangle.height() + 2;

            }

         }

         if (pcolumn->m_sizeIcon.cy + 2 > iItemHeight)
         {

            iItemHeight = pcolumn->m_sizeIcon.cy + 2;

         }

      }

      auto pgraphics = ::draw2d::create_memory_graphics();

      //draw_select ds(this, pgraphics);

      pgraphics->set_font(this, ::user::e_element_none);

      auto pfont = pgraphics->get_current_font();

      auto iFontHeight = pfont->get_height(pgraphics);

      iItemHeight = 1;

      if (iFontHeight > iItemHeight)
      {

         iItemHeight = (decltype(iItemHeight)) maximum(iFontHeight, iItemHeight);

      }

      //on_ui_event(event_calc_item_height, object_list, this);

//      m_iVScrollOffset = m_dItemHeight;

      m_iItemWidth = (i32)iItemWidth;

      if (m_bSingleColumnMode)
      {

         m_iItemWidth = _001CalcColumnWidth(pgraphics, 0);

      }

      if (m_plistheader != nullptr && m_plistheader->is_window())
      {

         //      while(m_plistheader->DeleteItem(0));

         ::user::list_header::item hditem;

         for (index iOrder = 0; iOrder < m_columna.VisibleGetCount(); iOrder++)
         {
            iColumn = _001MapOrderToColumn(iOrder);

            if (iColumn < 0)
            {

               continue;

            }

            list_column * pcolumn = m_columna.get_visible(iColumn);

            //hditem.mask = HDI_WIDTH | HDI_TEXT | HDI_LPARAM | HDI_ORDER;
            //str.load_string(_001GetColumnTextId(iColumn));
            //hditem.pszText = (char *) (const char *) str;
            //hditem.pszText = LPSTR_TEXTCALLBACK;
            //hditem.cchTextMax = str.get_length();

            hditem.cchTextMax = 0;

            hditem.cxy = pcolumn->m_iWidth;;

            hditem.lParam = (lparam) iColumn;

            hditem.iOrder = (i32)iOrder;

         }

      }

   }


   bool list::_001SetColumnWidth(index iColumn, i32 iWidth)
   {

      if (iColumn < 0)
      {

         return false;

      }

      if (iColumn >= m_columna.VisibleGetCount())
      {

         return false;

      }

      m_columna.get_visible(iColumn)->m_iWidth = iWidth;

      m_plistheader->DIDDXColumn(true);

      _001OnColumnChange();

      return true;

   }


   void list::_001GetColumnWidth(draw_list_item * pitem)
   {

      auto  * pcolumn = m_columna.get_visible(pitem->m_iColumn);

      if (pcolumn == nullptr)
      {

         pitem->m_iColumnWidth = 0;

         pitem->m_bOk = false;

      }
      else
      {

         pitem->m_iSubItem = pcolumn->subitem_index();

         pitem->m_iColumnWidth = pcolumn->m_iWidth;

         pitem->m_bOk = true;

      }

   }


   index list::_001MapSubItemToOrder(index iSubItem)
   {

      return _001MapColumnToOrder(_001MapSubItemToColumn(iSubItem));

   }


   index list::_001MapOrderToSubItem(index iOrder)
   {

      return _001MapColumnToSubItem(_001MapOrderToColumn(iOrder));

   }


   index list::_001MapOrderToColumn(index iOrder)
   {

      for (index iColumn = 0; iColumn < m_columna.get_size(); iColumn++)
      {
         list_column * pcolumn = m_columna.element_at(iColumn);

         if (pcolumn->m_bVisible)
         {

            if (pcolumn->m_iOrder == iOrder)
            {

               return iColumn;

            }

         }

      }

      return -1;

   }


   index list::_001MapColumnToOrder(index iColumn)
   {

      if (iColumn < 0)
      {

         return -1;

      }

      if (iColumn >= m_columna.VisibleGetCount())
      {

         return -1;

      }

      auto pcolumn = m_columna.get_visible(iColumn);

      if (!pcolumn)
      {

         return -1;

      }

      return (::index)pcolumn->m_iOrder;

   }


   index list::_001MapSubItemToColumn(index iSubItem)
   {

      return m_columna.subitem_visible_index(iSubItem);

   }


   index list::_001MapColumnToSubItem(index iColumn)
   {

      ASSERT(iColumn >= 0);
      ASSERT(iColumn < m_columna.VisibleGetCount());

      return m_columna.get_visible(iColumn)->subitem_index();

   }


   void list::_001DeleteColumn(index iColumn)
   {

      ASSERT(iColumn >= 0);
      ASSERT(iColumn < m_columna.VisibleGetCount());

      m_columna.erase(iColumn);

   }


   ::count list::_001GetItemCount()
   {

      if (m_pmeshdata.is_null())
      {

         return 0;

      }

      return m_pmeshdata->_001GetItemCount();

   }


   ::count list::_001GetGroupCount()
   {

      if (m_pmeshdata.is_null())
      {

         return -1;

      }

      return m_pmeshdata->_001GetGroupCount();

   }


   /////////////////////////////////////////////////////////////////
   //
   // Function: _001CalcDisplayTopIndex
   // Old Name: _001GetTopIndex
   //
   // Purpose:
   // Return the index of the first visible item in the list
   //
   // Output:
   // The index of the first visible item in the list
   //
   //
   /////////////////////////////////////////////////////////////////
   index list::_001CalcDisplayTopIndex()
   {

      auto pointOffset = get_viewport_offset();

      index iItem;

      if (_001DisplayHitTest(point_i32(0, (::i32) (m_bHeaderCtrl ? m_dItemHeight : 0.)), iItem))
      {

         return (::index) iItem;

      }
      else
      {

         if (m_eview == impact_report)
         {

            if (pointOffset.y < 0)
            {

               return 0;

            }

         }

         return -1;

      }

   }


   ::count list::_001CalcDisplayItemCount()
   {

      if (m_eview == impact_list)
      {

         ::rectangle_i32 rectView;

         get_client_rect(&rectView);

         index dHeight = (::index) ((rectView.height() / m_dItemHeight) * m_dItemHeight);

         index iWidth = rectView.width();

         int iViewRowCount = 1;

         if(m_dItemHeight > 0)
         {

            iViewRowCount = (int) maximum(1, dHeight / m_dItemHeight);

         }

         int iColumnCount = 1;

         if(m_iItemWidth > 0)
         {

            iColumnCount = (int) (iWidth / m_iItemWidth);

         }

         return iViewRowCount * iColumnCount;

      }
      else if (m_eview == impact_icon)
      {

         ::rectangle_i32 rectView;

         get_client_rect(&rectView);

         const ::size_i32 & sizeItem = get_item_size();

         return maximum((rectView.width() / sizeItem.cx) * (rectView.height() / sizeItem.cy),
                    m_piconlayout->m_iaDisplayToStrict.get_max_a() + 1);

      }
      else if (m_eview == impact_report)
      {

         ::rectangle_i32 rectView;

         get_client_rect(&rectView);

         if (m_dItemHeight == 0)
         {

            return 0;

         }
         else
         {

            double dHeight = rectView.height();

            if (m_bTopText)
            {

               dHeight -= m_rectTopText.height();

            }

            ::count iItemCount = (::count) ceil(dHeight / m_dItemHeight);

            return iItemCount;

         }

      }

      index iItemCount;

      if (m_bFilter1 && (m_eview == impact_list || m_eview == impact_report))
      {

         iItemCount = m_piaFilterMesh->get_count();

      }
      else
      {

         iItemCount = m_nItemCount;

      }

      auto iItemFirst = m_iTopDisplayIndex;

      auto iItemLast = iItemFirst;

      ::rectangle_i32 rectItem;

      ::rectangle_i32 rectIntersect;

      ::rectangle_i32 rectUpdate;

      get_client_rect(&rectUpdate);

      draw_list_item item(this);

      if (iItemFirst >= 0)
      {

         iItemLast = -1;

         for (index i = iItemFirst + 1; i < iItemCount; i++)
         {

            item.m_iItem = i;

            item.m_iDisplayItem = i;

            if (m_bGroup)
            {

               item.m_iGroupTopDisplayIndex = 0;

               for (item.m_iGroup = 0; item.m_iGroup < m_nGroupCount; item.m_iGroup++)
               {

                  item.m_iGroupCount = _001GetGroupItemCount(item.m_iGroup);

                  if (i >= item.m_iGroupTopDisplayIndex && i < (item.m_iGroupTopDisplayIndex + item.m_iGroupCount))
                  {

                     break;

                  }

               }

            }

            _001GetItemRect(&item);

            if (item.m_bOk)
            {

               if (!rectIntersect.intersect(item.m_rectItem, rectUpdate))
               {

                  iItemLast = i - 1;

                  break;

               }

            }
            else
            {

               iItemLast = i - 1;

               break;

            }

         }

         if (iItemLast < 0)
         {

            iItemLast = iItemCount - 1;

         }

         return iItemLast - iItemFirst + 1;

      }
      else
      {

         return 0;

      }

   }


   bool list::_001HitTest_(const ::point_i32 & point, index &iItem, index &iSubItem, index&iListItem, ::user::mesh::enum_element &eelement)
   {

      UNREFERENCED_PARAMETER(point);
      UNREFERENCED_PARAMETER(iItem);
      UNREFERENCED_PARAMETER(iSubItem);
      UNREFERENCED_PARAMETER(iListItem);
      UNREFERENCED_PARAMETER(eelement);

      return false;

   }


   bool list::_001HitTest_(const ::point_i32 & point, index &iItem, index&iSubItem)
   {

      if (!_001DisplayHitTest(point, iItem, iSubItem))
      {

         return false;

      }

      iItem = _001DisplayToStrict((::index) iItem);

      return true;

   }


   bool list::_001HitTest_(const ::point_i32 & point, index & iItem)
   {

      if (!_001DisplayHitTest(point, iItem))
      {

         return false;

      }

      iItem = _001DisplayToStrict((::index)iItem);

      return true;

   }


   bool list::_001DisplayHitTest(const ::point_i32 & point, index& iItem, index& iSubItem, index& iListItem, ::user::mesh::enum_element &eelement)
   {

      UNREFERENCED_PARAMETER(point);
      UNREFERENCED_PARAMETER(iItem);
      UNREFERENCED_PARAMETER(iSubItem);
      UNREFERENCED_PARAMETER(iListItem);
      UNREFERENCED_PARAMETER(eelement);

      return false;

   }


   bool list::_001DisplayHitTest(const ::point_i32 & point, index&iItemParam, index&iSubItemParam)
   {

      index iItem;

      if (!_001DisplayHitTest(point, iItem))
      {

         return false;

      }

      if (m_eview == impact_icon || m_eview == impact_list)
      {

         iItemParam = iItem;

         if (iItem == -1)
         {

            iSubItemParam = -1;

         }
         else
         {

            iSubItemParam = 0;

         }

         return true;

      }

      auto iColumnCount = _001GetColumnCount();

      auto pointOffset = get_viewport_offset();

      ::rectangle_i32 rectMargin;

      get_margin_rect(rectMargin);

      auto iLeft = (index)-pointOffset.x - (rectMargin.left * 2);

      if (m_bGroup && m_bLateralGroup)
      {

         iLeft += m_iLateralGroupWidth;

      }

      index iRight;

      draw_list_item item(this);

      if (point.x < 0)
      {

         return false;

      }

      for (item.m_iColumn = 0; item.m_iColumn < iColumnCount; item.m_iColumn++)
      {

         _001GetColumnWidth(&item);

         if (!item.m_bOk)
         {

            continue;

         }

         iRight = iLeft + item.m_iColumnWidth;

         if (iLeft <= point.x && point.x < iRight)
         {

            iItemParam = iItem;

            iSubItemParam = item.m_iSubItem;

            return true;

         }

         iLeft = iRight;

      }

      return false;

   }


   bool list::_001DisplayHitTest(const ::point_i32 & point, index&iItemParam)
   {

      {

         ::rectangle_i32 rectClient;

         get_client_rect(&rectClient);

         if (point.x < 0
               || point.x > rectClient.right
               || point.y < 0
               || point.y > rectClient.bottom)
         {

            return false;

         }

      }

      if (m_eview == impact_report)
      {

         auto pointOffset = get_viewport_offset();

         double iy = point.y + pointOffset.y + (m_bHeaderCtrl ? -m_dItemHeight : 0);

         index iItem = -1;

         if (m_dItemHeight != 0)
         {

            iItem = (::index) (iy / m_dItemHeight);

         }

         if (iItem < 0)
         {

            return false;

         }

         if (m_bFilter1)
         {

            if (iItem >= m_piaFilterMesh->get_count())
            {

               return false;

            }

         }

         if (iItem >= m_nItemCount)
         {

            return false;

         }

         iItemParam = (index)iItem;

         return true;

      }
      else if (m_eview == impact_list)
      {

         if (m_dItemHeight <= 0)
         {

            return false;

         }

         ::rectangle_i32 rectClient;

         get_client_rect(&rectClient);

         if (m_bTopText)
         {

            rectClient.top += m_rectTopText.height();

         }

         if (m_bHeaderCtrl)
         {

            rectClient.top += (::i32) m_dItemHeight;

         }

         index dHeight = (::index) ((rectClient.height() / m_dItemHeight) * m_dItemHeight);

         auto pointOffset = get_viewport_offset();

         index iy;

         if (m_iItemWidth <= 0)
         {

            iy = 0;

         }
         else
         {

            iy = (index)(point.y + pointOffset.y);

         }

         index iItem = -1;

         int iViewRowCount = 1;

         if(m_dItemHeight > 0)
         {

            iViewRowCount = (int) maximum(1, dHeight / m_dItemHeight);

         }

         int iColumn = 0;

         if(m_iItemWidth > 0)
         {

            iColumn = (point.x + pointOffset.x) / m_iItemWidth;

         }

         int iRow = 0;

         if (m_dItemHeight != 0)
         {

            iRow = (int) (iy / m_dItemHeight);

         }

         iItem = iColumn * iViewRowCount + iRow;

         if (iItem < 0)
         {

            return false;

         }

         if (m_bHeaderCtrl)
         {

            iItem--;

            if (iItem < 0)
            {

               return false;

            }

         }

         if (m_bFilter1)
         {

            if (iItem >= m_piaFilterMesh->get_count())
            {

               return false;

            }

         }

         if (iItem >= m_nItemCount)
         {

            return false;

         }

         iItemParam = iItem;

         return true;

      }
      else if (m_eview == impact_icon)
      {

         if (m_columna.get_count() == 0)
         {

            return false;

         }

         ::rectangle_i32 rectClient;

         get_client_rect(&rectClient);

         if (m_bTopText)
         {

            rectClient.top += m_rectTopText.height();

         }

         index iIconSize = maximum(32, m_columna[0]->m_sizeIcon.cy);

         index iItemSize = iIconSize * 2;

         auto pointOffset = get_viewport_offset();

         index ix = (index)(point.x + pointOffset.x);

         ix = (index)maximum(pointOffset.x, ix);

         ix = (index)minimum(rectClient.right, ix);

         ix = (index)maximum(rectClient.left, ix);

         ix /= iItemSize;

         index iy = point.y + pointOffset.y;

         iy = maximum(pointOffset.y, iy);

         iy = maximum(rectClient.top, iy);

         iy /= iItemSize;

         iItemParam = iy * (maximum(1, rectClient.width() / iItemSize)) + ix;

         return true;

      }

      return false;

   }


   void list::_001GetGroupRect(::user::draw_list_item * pdrawitem)
   {

      if (pdrawitem->m_iGroup < 0)
      {

         return_(pdrawitem->m_bOk, false);

      }

      if (pdrawitem->m_iGroup >= m_nGroupCount)
      {

         return_(pdrawitem->m_bOk, false);

      }

      index iItemFirst = 0;

      index iItemLast = _001GetGroupItemCount(0) - 1;

      pdrawitem->m_iGroupRectGroup = 0;

      while (pdrawitem->m_iGroupRectGroup < pdrawitem->m_iGroup)
      {

         pdrawitem->m_iGroupRectGroup++;

         iItemFirst = iItemLast + 1;

         iItemLast = iItemFirst + _001GetGroupItemCount(pdrawitem->m_iGroupRectGroup) - 1;

      }

      draw_list_item itemFirst(this);

      itemFirst.m_iItem = _001DisplayToStrict(iItemFirst);

      itemFirst.m_iDisplayItem = iItemFirst;

      itemFirst.m_iGroup = pdrawitem->m_iGroupRectGroup;

      _001GetItemRect(&itemFirst);

      draw_list_item itemLast(this);

      itemLast.m_iDisplayItem = _001DisplayToStrict(iItemLast);

      itemLast.m_iItem = iItemLast;

      itemLast.m_iGroup = pdrawitem->m_iGroupRectGroup;

      _001GetItemRect(&itemLast);

      pdrawitem->m_rectGroup.unite(itemFirst.m_rectItem, itemLast.m_rectItem);

      pdrawitem->m_rectGroup.bottom = maximum(itemLast.m_rectItem.bottom, itemFirst.m_rectItem.top + m_iGroupMinHeight);

      pdrawitem->m_rectGroup.left = 0;

      pdrawitem->m_rectGroup.right = m_iLateralGroupWidth;

      pdrawitem->m_bOk = true;

   }


   void list::_001GetItemRect(::user::draw_list_item * pdrawitem)
   {

      if (pdrawitem->m_iDisplayItem == (-1 - pdrawitem->m_iItemRectItem) && pdrawitem->m_iItemRectItem >= 0)
      {

         return_(pdrawitem->m_bOk, false);

      }

      if (pdrawitem->m_iDisplayItem == pdrawitem->m_iItemRectItem)
      {

         return_(pdrawitem->m_bOk, true);

      }

      if (pdrawitem->m_iDisplayItem < 0)
      {

         pdrawitem->m_rectItem.left = 0;

         pdrawitem->m_rectItem.top = 0;

         pdrawitem->m_rectItem.right = 0;

         pdrawitem->m_rectItem.bottom = 0;

         pdrawitem->m_iItemRectItem = (-1 - pdrawitem->m_iDisplayItem);

         return_(pdrawitem->m_bOk, false);

      }

      if (m_eview == impact_icon && pdrawitem->m_iDisplayItem >= m_nDisplayCount)
      {

         pdrawitem->m_rectItem.left = 0;

         pdrawitem->m_rectItem.top = 0;

         pdrawitem->m_rectItem.right = 0;

         pdrawitem->m_rectItem.bottom = 0;

         pdrawitem->m_iItemRectItem = (-1 - pdrawitem->m_iDisplayItem);

         return_(pdrawitem->m_bOk, false);

      }

      auto pointOffset = get_viewport_offset();

      if (m_eview == impact_report)
      {

         if (m_bGroup)
         {

            if (m_bLateralGroup)
            {

               if (pdrawitem->m_iItemRectItem < 0)
               {

                  pdrawitem->m_rectItem.left = m_iLateralGroupWidth;

                  pdrawitem->m_rectItem.right = (::i32)(pdrawitem->m_rectItem.left + m_iItemWidth);

                  pdrawitem->m_iItemRectItem = 0;

                  pdrawitem->m_rectItem.top = 0;

                  if (m_bHeaderCtrl)
                  {

                     pdrawitem->m_rectItem.top += (::i32) (m_dItemHeight);

                  }

                  if (m_bTopText)
                  {

                     pdrawitem->m_rectItem.top += m_rectTopText.height();

                  }

                  pdrawitem->m_rectItem.bottom = (::i32) (pdrawitem->m_rectItem.top + m_dItemHeight);

              //    pdrawitem->m_rectItem.offset(-pointOffset.x, -pointOffset.y);

               }

               if (pdrawitem->m_iDisplayItem > pdrawitem->m_iItemRectItem)
               {

                  i32 iOffset = (i32)((pdrawitem->m_iItemRectItem - pdrawitem->m_iGroupTopDisplayIndex) * m_dItemHeight);

                  pdrawitem->m_rectItem.top -= iOffset;

                  pdrawitem->m_rectItem.bottom = (::i32) (pdrawitem->m_rectItem.top + m_dItemHeight);

                  while (pdrawitem->m_iGroupTopDisplayIndex + pdrawitem->m_iGroupCount < pdrawitem->m_iDisplayItem)
                  {

                     pdrawitem->m_rectItem.top += iOffset;

                     pdrawitem->m_rectItem.bottom = (::i32) (pdrawitem->m_rectItem.top + m_dItemHeight);

                     if ((pdrawitem->m_iGroup + 1) >= m_nGroupCount)
                     {

                        break;

                     }

                     pdrawitem->m_iGroup++;

                     pdrawitem->m_iGroupTopDisplayIndex += pdrawitem->m_iGroupCount;

                     pdrawitem->m_iGroupCount = _001GetGroupItemCount(pdrawitem->m_iGroup);

                     pdrawitem->m_iItemRectItem = pdrawitem->m_iGroupTopDisplayIndex;

                  }

               }
               else
               {

                  i32 iOffset = (i32)((pdrawitem->m_iItemRectItem - pdrawitem->m_iGroupTopDisplayIndex) * m_dItemHeight);

                  pdrawitem->m_rectItem.top -= iOffset;

                  pdrawitem->m_rectItem.bottom = (::i32)(pdrawitem->m_rectItem.top + m_dItemHeight);

                  while (pdrawitem->m_iGroupTopDisplayIndex + pdrawitem->m_iGroupCount > pdrawitem->m_iDisplayItem)
                  {

                     if ((pdrawitem->m_iGroup - 1) < 0)
                     {

                        break;

                     }

                     pdrawitem->m_iGroup--;

                     i32 dHeight = _001GetGroupHeight(pdrawitem->m_iGroup);

                     pdrawitem->m_rectItem.top -= dHeight;

                     pdrawitem->m_rectItem.bottom = (::i32)(pdrawitem->m_rectItem.top + m_dItemHeight);

                     pdrawitem->m_iGroupCount = _001GetGroupItemCount(pdrawitem->m_iGroup);

                     pdrawitem->m_iGroupTopDisplayIndex -= pdrawitem->m_iGroupCount;

                     pdrawitem->m_iItemRectItem = pdrawitem->m_iGroupTopDisplayIndex;

                  }

               }

               if (pdrawitem->m_iGroup < m_nGroupCount && pdrawitem->m_iGroup >= 0)
               {

                  pdrawitem->m_iItemRectItem = pdrawitem->m_iDisplayItem;

                  pdrawitem->m_rectItem.top += (::i32)((pdrawitem->m_iItemRectItem - pdrawitem->m_iGroupTopDisplayIndex) * m_dItemHeight);

                  pdrawitem->m_rectItem.bottom = (::i32)(pdrawitem->m_rectItem.top + m_dItemHeight);

               }

            }
            else
            {

               ::exception::throw_not_implemented();

            }

         }
         else
         {

            pdrawitem->m_rectItem.left = 0;

            pdrawitem->m_rectItem.right = (::i32)m_iItemWidth;

            pdrawitem->m_rectItem.top = 0;

            if (m_bHeaderCtrl)
            {

               pdrawitem->m_rectItem.top += (::i32)(m_dItemHeight);

            }

            pdrawitem->m_rectItem.top += (::i32)(m_dItemHeight * pdrawitem->m_iDisplayItem);

            if (m_bTopText)
            {

               pdrawitem->m_rectItem.top += m_rectTopText.height();

            }

            pdrawitem->m_rectItem.bottom = (::i32)(pdrawitem->m_rectItem.top + m_dItemHeight);

            //pdrawitem->m_rectItem.offset(-pointOffset.x, -pointOffset.y);

            pdrawitem->m_iItemRectItem = pdrawitem->m_iDisplayItem;

         }

      }
      else if (m_eview == impact_list)
      {

         ::rectangle_i32 rectClient;

         get_client_rect(&rectClient);

         if (m_bTopText)
         {

            rectClient.top += m_rectTopText.height();

         }

         if (m_bHeaderCtrl)
         {

            rectClient.top += (::i32)(m_dItemHeight);

         }

         if (m_dItemHeight <= 0)
         {

            return_(pdrawitem->m_bOk, false);

         }

         index dHeight = (::index) ((rectClient.height() / m_dItemHeight) * m_dItemHeight);

         if (dHeight != 0 && m_dItemHeight != 0)
         {

            int iViewRowCount = (int) maximum(1, dHeight / m_dItemHeight);

            int iColumn = (int) (pdrawitem->m_iItem / iViewRowCount);

            int iRow = pdrawitem->m_iItem % iViewRowCount;

            pdrawitem->m_rectItem.left = iColumn * m_iItemWidth;

            pdrawitem->m_rectItem.top = (::i32)(iRow * m_dItemHeight);

         }

         if (m_bTopText)
         {

            pdrawitem->m_rectItem.top += m_rectTopText.height();

         }

         if (m_bHeaderCtrl)
         {

            pdrawitem->m_rectItem.top += (::i32)(m_dItemHeight);

         }

         pdrawitem->m_rectItem.bottom = (::i32)(pdrawitem->m_rectItem.top + m_dItemHeight);

         pdrawitem->m_rectItem.right = (::i32)(pdrawitem->m_rectItem.left + m_iItemWidth);

         pdrawitem->m_rectItem.offset(-pointOffset.x, -pointOffset.y);

      }
      else if (m_eview == impact_icon)
      {

         ::rectangle_i32 rectClient;

         get_client_rect(&rectClient);

         if (rectClient.is_empty())
         {

            return_(pdrawitem->m_bOk, false);

         }

         if (m_bTopText)
         {

            rectClient.top += m_rectTopText.height();

         }

         index iIconSize = maximum(32, m_columna[0]->m_sizeIcon.cy);

         index iItemSize = iIconSize * 2;

         pdrawitem->m_rectItem.left = (::i32)(iItemSize * (pdrawitem->m_iDisplayItem % (maximum(1, rectClient.width() / iItemSize))));

         pdrawitem->m_rectItem.top = (::i32)(iItemSize * (pdrawitem->m_iDisplayItem / (maximum(1, rectClient.width() / iItemSize))));

         pdrawitem->m_rectItem.bottom = (::i32)(pdrawitem->m_rectItem.top + iItemSize);

         pdrawitem->m_rectItem.right = (::i32)(pdrawitem->m_rectItem.left + iItemSize);

         pdrawitem->m_rectItem.offset(-pointOffset.x, -pointOffset.y);

         if (m_bDrag && m_iItemLButtonDown >= 0)
         {

            if (pdrawitem->m_iItem == m_iItemLButtonDown || m_rangeSelection.has_item(pdrawitem->m_iDisplayItem))
            {

               ::point_i32 point = m_pointLButtonUp;

               ::point_i32 point2 = m_pointLButtonDown1;

               point -= point2;

               pdrawitem->m_rectItem.offset(point);

            }

         }

      }

      pdrawitem->m_bOk = true;

   }


   void list::_001GetSubItemRect(::user::draw_list_item * pdrawitem)
   {

      if (pdrawitem->m_iDisplayItem != pdrawitem->m_iItemRectItem)
      {

         _001GetItemRect(pdrawitem);

         if (!pdrawitem->m_bOk)
         {

            return;

         }

      }

      if (pdrawitem->m_iSubItemRectOrder == pdrawitem->m_iOrder)
      {

         if (pdrawitem->m_iSubItemRectItem != pdrawitem->m_iItemRectItem)
         {

            pdrawitem->m_rectSubItem.top = pdrawitem->m_rectItem.top;

            pdrawitem->m_rectSubItem.bottom = pdrawitem->m_rectItem.bottom;

         }

         return_(pdrawitem->m_bOk, true);

      }

      if (m_eview == impact_icon)
      {

         pdrawitem->m_rectSubItem = pdrawitem->m_rectItem;

         return_(pdrawitem->m_bOk, true);

      }

      pdrawitem->m_bOk = false;

      pdrawitem->m_rectSubItem.top = pdrawitem->m_rectItem.top;

      pdrawitem->m_rectSubItem.bottom = pdrawitem->m_rectItem.bottom;

      index iLastOrder = _001GetColumnCount() - 1;

      if (iLastOrder < 0)
      {

         return_(pdrawitem->m_bOk, false);

      }

      if (pdrawitem->m_iSubItemRectOrder < 0 || pdrawitem->m_iOrder == 0 || pdrawitem->m_iSubItemRectOrder > pdrawitem->m_iOrder)
      {
         pdrawitem->m_iSubItemRectOrder = 0;
         pdrawitem->m_rectSubItem.left = pdrawitem->m_rectItem.left;
         pdrawitem->m_iSubItemRectColumn = _001MapOrderToColumn(pdrawitem->m_iOrder);
         pdrawitem->m_iColumn = pdrawitem->m_iSubItemRectColumn;
         _001GetColumnWidth(pdrawitem);
         pdrawitem->m_rectSubItem.right = pdrawitem->m_rectItem.left + pdrawitem->m_iColumnWidth;
         pdrawitem->m_iSubItemRectItem = pdrawitem->m_iItemRectItem;
         pdrawitem->m_iSubItemRectSubItem = pdrawitem->m_iSubItem;
         if (pdrawitem->m_iOrder == 0)
         {
            pdrawitem->m_bOk = true;
            return;
         }
      }

      if (pdrawitem->m_iOrder <= iLastOrder)
      {
         while (pdrawitem->m_iSubItemRectOrder < pdrawitem->m_iOrder)
         {
            pdrawitem->m_iColumn = _001MapOrderToColumn(pdrawitem->m_iSubItemRectOrder);
            _001GetColumnWidth(pdrawitem);
            pdrawitem->m_rectSubItem.left += pdrawitem->m_iColumnWidth;
            pdrawitem->m_iSubItemRectOrder++;
         }
         pdrawitem->m_iColumn = _001MapOrderToColumn(pdrawitem->m_iSubItemRectOrder);
         pdrawitem->m_iSubItemRectColumn = pdrawitem->m_iColumn;
         _001GetColumnWidth(pdrawitem);
         pdrawitem->m_rectSubItem.right = pdrawitem->m_rectSubItem.left + pdrawitem->m_iColumnWidth;
         pdrawitem->m_iSubItemRectOrder = pdrawitem->m_iOrder;
         pdrawitem->m_iSubItemRectItem = pdrawitem->m_iItemRectItem;
         pdrawitem->m_iSubItemRectSubItem = pdrawitem->m_iSubItem;
         pdrawitem->m_bOk = true;
      }

   }


   ::user::interaction * list::get_subitem_control(::index iSubItem)
   {

      auto pcolumn = m_columna.get_by_subitem(iSubItem);

      if (!pcolumn)
      {

         return nullptr;

      }

      auto puserinteraction = get_child_by_id(pcolumn->m_id);

      if (!puserinteraction)
      {

         return nullptr;

      }

      return puserinteraction;

   }


   void list::_001GetElementRect(::user::draw_list_item * pdrawitem, ::user::mesh::enum_element eelement)
   {

      if (m_bGroup && m_bLateralGroup && (eelement == ::user::list::element_group_image || eelement == ::user::list::element_group_item_text))
      {

         i32 x = pdrawitem->m_rectGroup.left;

         i32 iImageBottom = pdrawitem->m_rectGroup.top;

         if (m_pilGroup != nullptr)
         {

            ::image_list::info ii;

            _001GetGroupImage(pdrawitem);

            if (pdrawitem->m_bOk && pdrawitem->m_iImage >= 0)
            {

               m_pilGroup->get_image_info((i32)pdrawitem->m_iImage, &ii);

               if (eelement == ::user::list::element_group_image)
               {

                  pdrawitem->m_rectImage.left = x;
                  pdrawitem->m_rectImage.right = x + ii.m_rectangle.width();
                  pdrawitem->m_rectImage.top = pdrawitem->m_rectGroup.top;
                  pdrawitem->m_rectImage.bottom = pdrawitem->m_rectImage.top + ii.m_rectangle.height();

                  return_(pdrawitem->m_bOk, true);

               }
               else
               {

                  x += ii.m_rectangle.width();

                  x += 2;

                  iImageBottom += ii.m_rectangle.height() + 2;

               }

            }
            else if (eelement == ::user::list::element_group_image)
            {

               return_(pdrawitem->m_bOk, false);

            }

         }
         else if (eelement == ::user::list::element_group_image)
         {

            return_(pdrawitem->m_bOk, false);

         }

         if (eelement == ::user::list::element_group_item_text)
         {

            pdrawitem->m_rectText.top = (::i32)(pdrawitem->m_rectGroup.top + m_dItemHeight * pdrawitem->m_iItem);

            if (pdrawitem->m_rectText.top >= iImageBottom)
            {

               pdrawitem->m_rectText.left = pdrawitem->m_rectGroup.left;

            }
            else
            {

               pdrawitem->m_rectText.left = x;

            }

            pdrawitem->m_rectText.right = pdrawitem->m_rectGroup.right;

            pdrawitem->m_rectText.bottom = (::i32)(pdrawitem->m_rectText.top + m_dItemHeight);

            return_(pdrawitem->m_bOk, true);

         }

         pdrawitem->m_bOk = false;

      }
      else
      {

         if (pdrawitem->m_iDisplayItem != pdrawitem->m_iItemRectItem)
         {

            pdrawitem->m_bOk = false;

            _001GetItemRect(pdrawitem);

            if (!pdrawitem->m_bOk)
            {

               return;

            }

         }

         if (eelement == ::user::list::e_element_item)
         {

            return_(pdrawitem->m_bOk, true);

         }

         if (m_eview == impact_icon)
         {

            if (eelement == ::user::list::element_image)
            {

               i32 iIconSize = m_columna[0]->m_sizeIcon.cy;

               pdrawitem->m_rectImage.left = pdrawitem->m_rectItem.left + iIconSize / 2;
               pdrawitem->m_rectImage.top = pdrawitem->m_rectItem.top;
               pdrawitem->m_rectImage.right = pdrawitem->m_rectImage.left + iIconSize;
               pdrawitem->m_rectImage.bottom = pdrawitem->m_rectImage.top + iIconSize;

               return_(pdrawitem->m_bOk, true);

            }
            else if (eelement == ::user::mesh::e_element_text)
            {

               i32 iIconSize = m_columna[0]->m_sizeIcon.cy;

               pdrawitem->m_rectText.left = pdrawitem->m_rectItem.left;
               pdrawitem->m_rectText.top = pdrawitem->m_rectItem.top + iIconSize;
               pdrawitem->m_rectText.right = pdrawitem->m_rectText.left + iIconSize * 2;
               pdrawitem->m_rectText.bottom = pdrawitem->m_rectText.top + iIconSize;

               return_(pdrawitem->m_bOk, true);

            }

            return_(pdrawitem->m_bOk, false);

         }

         pdrawitem->m_bOk = false;

         _001GetSubItemRect(pdrawitem);

         if (!pdrawitem->m_bOk)
         {

            return;

         }

         i32 x = pdrawitem->m_rectSubItem.left;

         if (pdrawitem->m_iListItem == -1)
         {

            if (eelement == ::user::mesh::element_sub_item)
            {

               return_(pdrawitem->m_bOk, true);

            }

            if (::is_set(pdrawitem->m_pcolumn))
            {
               if (pdrawitem->m_pcolumn->m_bIcon)
               {

                  pdrawitem->m_bOk = false;

                  _001GetItemImage(pdrawitem);

                  if (pdrawitem->m_bOk && pdrawitem->m_iImage >= 0)
                  {

                     if (eelement == ::user::list::element_image)
                     {

                        ::rectangle_i32 rectAlign(pdrawitem->m_rectSubItem);

                        rectAlign.left = x;
                        ::rectangle_i32 rectIcon;
                        rectIcon.set(0, 0, pdrawitem->m_pcolumn->m_sizeIcon.cx, pdrawitem->m_pcolumn->m_sizeIcon.cy);
                        rectIcon.Align(e_align_left_center, rectAlign);
                        pdrawitem->m_rectImage = rectIcon;

                        return_(pdrawitem->m_bOk, true);

                     }
                     else
                     {

                        x += pdrawitem->m_pcolumn->m_sizeIcon.cx;

                        x += m_iImageSpacing;

                     }

                  }
                  else if (eelement == ::user::list::element_image)
                  {

                     return_(pdrawitem->m_bOk, false);

                  }

               }
               else if (pdrawitem->m_pcolumn->m_pil != nullptr)
               {

                  ::image_list::info ii;

                  pdrawitem->m_bOk = false;

                  _001GetItemImage(pdrawitem);

                  if (pdrawitem->m_bOk && pdrawitem->m_iImage >= 0)
                  {

                     pdrawitem->m_pcolumn->m_pil->get_image_info((i32)pdrawitem->m_iImage, &ii);

                     if (eelement == ::user::list::element_image)
                     {

                        ::rectangle_i32 rectAlign(pdrawitem->m_rectSubItem);
                        rectAlign.left = x;
                        ::rectangle_i32 rectIcon;
                        rectIcon.set(0, 0, ii.m_rectangle.width(), ii.m_rectangle.height());
                        rectIcon.Align(e_align_left_center, rectAlign);
                        pdrawitem->m_rectImage = rectIcon;

                        return_(pdrawitem->m_bOk, true);

                     }
                     else
                     {

                        x += ii.m_rectangle.width();

                        x += m_iImageSpacing;

                     }

                  }
                  else if (eelement == ::user::list::element_image)
                  {

                     return_(pdrawitem->m_bOk, false);

                  }

               }

            }
            else if (eelement == ::user::list::element_image)
            {

               return_(pdrawitem->m_bOk, false);

            }

            if (eelement == ::user::mesh::e_element_text)
            {

               pdrawitem->m_rectText.left = x;
               pdrawitem->m_rectText.right = pdrawitem->m_rectSubItem.right;
               pdrawitem->m_rectText.top = pdrawitem->m_rectSubItem.top;
               pdrawitem->m_rectText.bottom = pdrawitem->m_rectSubItem.bottom;

               return_(pdrawitem->m_bOk, true);

            }

         }

         pdrawitem->m_bOk = false;

      }

   }


   void list::LayoutHeaderCtrl()
   {

      synchronous_lock synchronouslock(mutex());

      if (m_plistheader == nullptr)
      {

         return;

      }

      if (m_bHeaderCtrl)
      {

         ::rectangle_i32 rectFocus;

         GetFocusRect(&rectFocus);

         m_plistheader->order_bottom();

         m_plistheader->set_dim(0, 0, (int)maximum(m_iItemWidth + 10, rectFocus.width()), (int)m_dItemHeight);

         m_plistheader->display();;

      }
      else
      {

         m_plistheader->display(e_display_none);

      }

   }


   void list::_001OnKeyDown(::message::message * pmessage)
   {

      __pointer(::message::key) pkey(pmessage);

      if (pkey->previous()) // give chance to child
         return;

      synchronous_lock synchronouslock(mutex());

      if (pkey->m_ekey == ::user::e_key_down || pkey->m_ekey == ::user::e_key_up ||
            pkey->m_ekey == ::user::e_key_next || pkey->m_ekey == ::user::e_key_prior)
      {
         if (m_nItemCount > 0)
         {
            range range = m_rangeSelection;
            m_rangeSelection.clear();

            auto iItem = m_iDisplayItemFocus;

            if (iItem < 0)
            {
               if (pkey->m_ekey == ::user::e_key_down || pkey->m_ekey == ::user::e_key_next)
               {
                  iItem = 0;
               }
               else if (pkey->m_ekey == ::user::e_key_up || pkey->m_ekey == ::user::e_key_prior)
               {
                  iItem = m_nItemCount - 1;
               }
            }
            else
            {
               if (pkey->m_ekey == ::user::e_key_down)
               {
                  iItem++;
               }
               else if (pkey->m_ekey == ::user::e_key_next)
               {
                  iItem += m_nDisplayCount;
               }
               else if (pkey->m_ekey == ::user::e_key_up)
               {
                  iItem--;
               }
               else if (pkey->m_ekey == ::user::e_key_prior)
               {
                  iItem -= m_nDisplayCount;
               }
               else
               {
                  ASSERT(false);
                  pmessage->m_bRet = false;
                  return;
               }
            }

            if (iItem < 0)
            {
               iItem = m_nItemCount - 1;
            }
            else if (iItem >= m_nItemCount)
            {
               iItem = 0;
            }

            m_iShiftFirstSelection = iItem;
            m_iDisplayItemFocus = iItem;

            item_range itemrange;
            itemrange.set(iItem, iItem, 0, m_columna.get_count() - 1, -1, -1);
            m_rangeSelection.add_item(itemrange);

            _001EnsureVisible(iItem, range);

            range.add_item(itemrange);

            set_need_redraw();

            _001OnSelectionChange();

         }

      }
      else if (pkey->m_ekey == ::user::e_key_delete)
      {

         ::user::range range;

         _001GetSelection(range);

         _001DeleteRange(range);

         pmessage->m_bRet = true;

      }

      pmessage->m_bRet = false;

   }


   void list::on_hover_select_timer()
   {

      mesh::on_hover_select_timer();

   }


   void list::on_message_mouse_move(::message::message * pmessage)
   {

      __pointer(::message::mouse) pmouse(pmessage);

      pmouse->m_lresult = 1;

      auto point = pmouse->m_point;

      _001ScreenToClient(point);

      synchronous_lock synchronouslock(mutex());

      if (m_bDrag)
      {

         if (!m_bLButtonDown)
         {

            m_bDrag = false;

         }
         else if (pmouse->is_left_button_pressed())
         {

            m_bLButtonDown = false;

            m_bDrag = false;

         }

      }

      if (m_bDrag)
      {

         m_pointLButtonUp = point;

         set_need_redraw();

      }
      else if (m_bHoverSelect2)
      {

         if (m_bLButtonDown)
         {

            bool bShouldStartDrag = d_distance(point, m_pointLButtonDown1) > m_dItemHeight;

            if (bShouldStartDrag)
            {

               m_bDrag = true;

            }

         }

      }

      if (m_bDrag)
      {

         if (m_iItemLButtonDown < 0)
         {

            if (m_eview == impact_icon)
            {

               ::rectangle_i32 rectClient;

               get_client_rect(&rectClient);

               index iIconSize = maximum(32, m_columna[0]->m_sizeIcon.cy);

               index iItemSize = iIconSize * 2;

               ::count iItemColumnCount = maximum(1, rectClient.width() / iItemSize);

               m_pointLButtonUp = point;

               index iDisplayBeg;

               index iDisplayEnd;

               if (_001DisplayHitTest(m_pointLButtonDown1, iDisplayBeg))
               {

                  if (_001DisplayHitTest(point, iDisplayEnd))
                  {

                     index iCol1 = iDisplayBeg % iItemColumnCount;

                     index iCol2 = iDisplayEnd % iItemColumnCount;

                     __sort(iCol1, iCol2);

                     index iRow1 = iDisplayBeg / iItemColumnCount;

                     index iRow2 = iDisplayEnd / iItemColumnCount;

                     __sort(iRow1, iRow2);

                     m_rangeSelection.clear();

                     for (index i = iRow1; i <= iRow2; i++)
                     {

                        for (index j = iCol1; j <= iCol2; j++)
                        {

                           index iDisplayItem = i * iItemColumnCount + j;

                           index iStrict = _001DisplayToStrict(iDisplayItem);

                           if(iStrict >= 0)
                           {

                              item_range itemrange;

                              itemrange.set_lower_bound(iDisplayItem);

                              itemrange.set_upper_bound(iDisplayItem);

                              m_rangeSelection.add_item(itemrange);

                           }

                        }

                     }

                     _001OnSelectionChange();

                  }

               }

               pmouse->m_bRet = true;

               pmouse->m_lresult = 1;

               return;

            }

         }

      }

      track_mouse_leave();

      {

         update_hover(pmouse);

         pmessage->m_bRet = true;

         index iItemEnter;

         index iSubItemEnter;

         if (_001DisplayHitTest(point, iItemEnter, iSubItemEnter))
         {

            if (m_bSelect && m_bHoverSelect2 &&
               (m_iSubItemEnter != iSubItemEnter ||
                  m_iItemEnter != iItemEnter)
               && !m_rangeSelection.has_item(iItemEnter))
            {

               m_iMouseFlagEnter = pmouse->m_nFlags;

               m_iItemEnter = iItemEnter;

               m_iSubItemEnter = iSubItemEnter;

               m_iTimerHoverSelect = 0;

               //SetTimer(e_timer_hover_select, 800, nullptr);

            }

         }

      }


   }


   void list::on_message_left_button_down(::message::message * pmessage)
   {

      __pointer(::message::mouse) pmouse(pmessage);

      set_mouse_capture();

      index iDisplayItem;

      auto point = pmouse->m_point;

      _001ScreenToClient(point);

      synchronous_lock synchronouslock(mutex());

      auto psession = get_session();

      m_bLButtonDown = true;

      auto tickNow = ::millis::now();

      auto tick2 = tickNow - m_millisLButtonDownStart2;

      auto tick1 = tickNow - m_millisLButtonDownStart1;

      auto tickDoubleClick = DBLCLKMS;

      if(tick2 < tickDoubleClick)
      {

         m_millisLButtonDownStart1 = m_millisLButtonDownStart2;

         m_millisLButtonDownStart2 = tickNow;

         m_pointLButtonDown1 = m_pointLButtonDown2;

         m_pointLButtonDown2 = point;

         m_iClick = 2;

      }
      else if(tick1 < tickDoubleClick)
      {

         m_millisLButtonDownStart2 = tickNow;

         m_pointLButtonDown2 = point;

         m_iClick = 2;

      }
      else
      {

         m_millisLButtonDownStart1 = tickNow;

         m_pointLButtonDown1 = point;

         m_iClick = 1;

      }

      if (!has_keyboard_focus())
      {

         set_keyboard_focus();

      }

      set_mouse_capture();

      index iItem;

      if (dynamic_cast <list *>(this) == nullptr)
      {

         auto tickNow = ::millis::now();

         if (tickNow - m_millisLButtonDownStart2 < DBLCLKMS)
         {

            m_millisLButtonDownStart1 = m_millisLButtonDownStart2;

            m_millisLButtonDownStart2 = tickNow;

            m_pointLButtonDown1 = m_pointLButtonDown2;

            m_pointLButtonDown2 = point;

            m_iClick = 2;

         }
         else if (tickNow - m_millisLButtonDownStart1 < DBLCLKMS)
         {

            m_millisLButtonDownStart2 = tickNow;

            m_pointLButtonDown2 = point;

            m_iClick = 2;

         }
         else
         {

            m_millisLButtonDownStart1 = tickNow;

            m_pointLButtonDown1 = point;

            m_iClick = 1;

         }

      }

      if (!has_keyboard_focus())
      {

         set_keyboard_focus();

      }

      set_keyboard_focus();

      psession->user()->set_mouse_focus_LButtonDown(this);

      if (!_001DisplayHitTest(point, m_iDisplayItemLButtonDown1))
      {

         m_iDisplayItemLButtonDown1 = -1;

      }

      if (m_bSelect)
      {

         if (m_bHoverSelect2)
         {

            if (_001DisplayHitTest(point, iItem))
            {

               // In "Hover Select"/"Single Click to Open" mode
               // the "Last Button UP flag" from a double-click
               // doesn't exist! So cannot "magically" take a
               // possibly quite old or inexisting "Last Button UP flag" (filled
               // with garbage in this later inexisting case),
               // and use as parameter for on_click.
               // And if it is actually from a double-click,
               // because "Hover Select"/"Single Click to Open"
               // mode is active, the "Last Button UP flag"
               // shouldn't be regarded, as it is not directly
               // related with further click other than the
               // current click, i.e., there is no interpretation
               // for double-click in "Hover Select"/"Single Click to Open"
               // mode, and every click must be regarded as single
               // independent click.
               // Action. Remove.
               // uptr nFlags = m_uiLButtonUpFlags;

               // uptr nFlags = 0;

               // const ::point_i32 & point = point;

               // on_click(item);

               // set_need_redraw();

               // m_iClick = 0;

            }
            else
            {

               m_rangeSelection.clear();

               _001OnSelectionChange();

            }

         }
         else
         {

            if (m_bMultiSelect && psession->is_key_pressed(::user::e_key_shift))
            {

               if (_001DisplayHitTest(point, iDisplayItem))
               {

                  item_range itemrange;

                  auto iLItem = minimum(m_iShiftFirstSelection, iDisplayItem);

                  auto iUItem = maximum(m_iShiftFirstSelection, iDisplayItem);

                  itemrange.set(iLItem, iUItem, 0, m_columna.get_count() - 1, -1, -1);

                  m_rangeSelection.add_item(itemrange);

                  m_iShiftFirstSelection = iDisplayItem;

               }

            }
            else if (m_bMultiSelect && psession->is_key_pressed(::user::e_key_control))
            {

               if (_001DisplayHitTest(point, iDisplayItem))
               {

                  item_range itemrange;

                  auto iLItem = minimum(m_iShiftFirstSelection, iDisplayItem);

                  auto iUItem = maximum(m_iShiftFirstSelection, iDisplayItem);

                  itemrange.set(iLItem, iUItem, 0, m_columna.get_count() - 1, -1, -1);

                  m_rangeSelection.add_item(itemrange);

                  m_iShiftFirstSelection = iDisplayItem;

               }

            }
            else
            {

               m_rangeSelection.clear();

               index iDisplayItem;

               if (_001DisplayHitTest(point, iDisplayItem))
               {

                  m_iShiftFirstSelection = iDisplayItem;

                  m_iDisplayItemFocus = iDisplayItem;

                  if(m_iClick == 1)
                  {

                     m_iDisplayItemLButtonDown1 = iDisplayItem;

                  }
                  else
                  {

                     m_iDisplayItemLButtonDown2 = iDisplayItem;

                  }

                  SetTimer(e_timer_drag_start, 1200);

                  item_range itemrange;

                  itemrange.set(iDisplayItem, iDisplayItem, 0, m_columna.get_count() - 1, -1, -1);

                  _001AddSelection(itemrange);

                  pmessage->m_bRet = true;

                  pmouse->m_lresult = 1;

                  return;

               }

               _001OnSelectionChange();

            }

         }

      }
      else
      {

         if (_001DisplayHitTest(point, iDisplayItem))
         {

            if(m_iClick == 1)
            {

               m_iDisplayItemLButtonDown1 = iDisplayItem;

            }
            else
            {

               m_iDisplayItemLButtonDown2 = iDisplayItem;

            }

            m_iItemLButtonDown = _001DisplayToStrict(iDisplayItem);

            if (m_eview == impact_icon)
            {

               auto point = pmouse->m_point;

               _001ScreenToClient(point);

               draw_list_item item(this);

               item.m_iItem = m_iItemLButtonDown;

               item.m_iDisplayItem = m_iDisplayItemLButtonDown1;

               _001GetItemRect(&item);

               payload("offx") = point.x - item.m_rectItem.left;

               payload("offy") = point.y - item.m_rectItem.top;

               if (!m_rangeSelection.has_item(item.m_iDisplayItem))
               {

                  m_rangeSelection.clear();

                  _001OnSelectionChange();

               }

               pmessage->m_bRet = true;

               pmouse->m_lresult = 1;

               set_need_redraw();

               return;

            }

         }
         else
         {

            m_iItemLButtonDown = -1;

            m_iDisplayItemLButtonDown1 = -1;

            m_iDisplayItemLButtonDown2 = -1;

         }

      }

      pmouse->previous(); // give chance to base views

      pmessage->m_bRet = true;

      pmouse->m_lresult = 1;

   }


   void list::on_message_left_button_up(::message::message * pmessage)
   {

      __pointer(::message::mouse) pmouse(pmessage);

      auto point = pmouse->m_point;

      _001ScreenToClient(point);

      auto psession = get_session();

      auto puser = psession->user();

      auto pwindowing = puser->windowing();

      pwindowing->release_mouse_capture();

      KillTimer(e_timer_drag_start);

      KillTimer(224455);

      synchronous_lock synchronouslock(mutex());


      if (m_bDrag)
      {

         m_pointLButtonUp = point;

         set_need_redraw();

      }
      else if(m_bHoverSelect2)
      {

         if (m_bLButtonDown)
         {

            bool bShouldStartDrag = d_distance(point, m_pointLButtonDown1) > m_dItemHeight;

            if (bShouldStartDrag)
            {

               m_bDrag = true;

            }

         }

      }


      if (m_bDrag)
      {

         m_bDrag = false;

         if (m_eview == impact_icon)
         {

            if (m_iItemLButtonDown >= 0)
            {

               index iDisplayItemDrag = m_iDisplayItemLButtonDown1;

               index iDisplayItemDrop;

               if (_001DisplayHitTest(point, iDisplayItemDrop))
               {

                  if(defer_drop(iDisplayItemDrop, iDisplayItemDrag))
                  {

                     string strSort(m_pmeshdata ? m_pmeshdata->m_strMeshSort.c_str() : "");

                     if (strSort.has_char())
                     {

                        defer_update_display();

                        strSort += "-" + get_display_tag() + ".icon_list_view_sort";

                        synchronouslock.lock();

                        string_array stra;

                        for (index a = 0; a <= m_plist->m_piconlayout->m_iaDisplayToStrict.m_iMaxA; a++)
                        {

                           index b = m_plist->m_piconlayout->m_iaDisplayToStrict.get_b(a);

                           stra.add(_001GetItemId(b));

                        }

                        auto pcontext = get_context();

                        pcontext->m_papexcontext->file().put_contents(strSort, stra.implode("\r\n"));

                        synchronouslock.unlock();

                        update_icon_list_view_sort();

                     }

                  }

               }

            }

         }

      }
      else
      {

         if (m_bLButtonDown)
         {

            index iDisplayItemLButtonUp = -1;

            if (_001DisplayHitTest(point, iDisplayItemLButtonUp) && iDisplayItemLButtonUp >= 0)
            {

               if (iDisplayItemLButtonUp == m_iDisplayItemLButtonDown1)
               {

                  if (!m_rangeSelection.has_item(iDisplayItemLButtonUp))
                  {

                     m_rangeSelection.clear();

                     item_range itemrange;

                     itemrange.set(iDisplayItemLButtonUp, iDisplayItemLButtonUp, 0, m_nColumnCount - 1, -1, -1);

                     _001AddSelection(itemrange);

                  }

                  synchronouslock.unlock();

                  if(m_iClick == 1)
                  {

                     if (!on_click({::user::e_element_item, _001DisplayToStrict(iDisplayItemLButtonUp)}))
                     {

                        //index iItem = _001DisplayToStrict(iDisplayItemLButtonUp);

                        //_001OnItemClick(iItem);

                     }

                  }
                  else
                  {

                     send_message(e_message_left_button_double_click, pmouse->m_nFlags, MAKELPARAM(point.x, point.y));

                  }

               }

            }

         }

      }

      if (m_bDrag)
      {

         if (!m_bLButtonDown)
         {

            m_bDrag = false;

         }
         else
         {

            m_bLButtonDown = false;

            m_bDrag = false;

         }

      }
      m_iItemLButtonDown = -1;

      m_iDisplayItemLButtonDown1 = -1;

      m_iDisplayItemLButtonDown2 = -1;

      pmessage->m_bRet = true;

      pmouse->m_lresult = 1;

      m_bLButtonDown = false;

   }


   void list::on_message_right_button_down(::message::message * pmessage)
   {

      __pointer(::message::mouse) pmouse(pmessage);

      pmouse->previous();

      auto psession = get_session();

      auto point = pmouse->m_point;

      _001ScreenToClient(point);

      synchronous_lock synchronouslock(mutex());

      if (!has_keyboard_focus())
      {
         
         set_keyboard_focus();

      }
      if (psession->is_key_pressed(::user::e_key_shift))
      {
      }
      else if (psession->is_key_pressed(::user::e_key_control))
      {
      }
      else
      {
         //      m_rangeSelection.clear();
         index iItem;
         if (_001DisplayHitTest(point, iItem))
         {
            if (!m_rangeSelection.has_item(iItem))
            {
               m_rangeSelection.clear();
               m_iShiftFirstSelection = iItem;
               item_range itemrange;
               itemrange.set(iItem, iItem, 0, m_columna.get_count() - 1, -1, -1);
               m_rangeSelection.add_item(itemrange);
               set_need_redraw();
            }
         }
         m_uiRButtonUpFlags = (::u32)pmouse->m_nFlags;
         m_pointRButtonUp = pmouse->m_point;
         SetTimer(8477, 500, nullptr);
      }


      pmessage->m_bRet = true;
   }



   bool list::on_click(const ::user::item & item)
   {

      ::user::control_event ev;

      ev.m_puie = this;

      ev.m_eevent = ::user::e_event_list_clicked;

      route_control_event(&ev);

      //if (m_pformcallback != nullptr)
      //{

      //   m_pformcallback->on_control_event(&ev);

      //}
      //else if (get_form() != nullptr)
      //{

      //   get_form()->send_message(e_message_event, 0, (LPARAM)&ev);

      //}
      //else
      //{

      //   get_parent()->send_message(e_message_event, 0, (LPARAM)&ev);

      //}

      return ev.m_bRet;

   }


   bool list::on_right_click(const ::user::item & item)
   {

      UNREFERENCED_PARAMETER(item);

      return false;

   }



   void list::_001GetSelection(range &range)
   {

      range = m_rangeSelection;

   }


   index list::_001GetCurItem()
   {

      if (m_rangeSelection.get_item_count() != 1)
      {

         return -1;

      }

      return m_rangeSelection.ItemAt(0).m_iLowerBound;

   }


   void list::_001SelectItem(index iItem)
   {

      m_rangeSelection.clear();

      if (iItem < 0 || iItem >= _001GetItemCount())
      {

         return;

      }

      item_range itemrange;

      itemrange.m_iLowerBound = iItem;
      itemrange.m_iUpperBound = iItem;

      m_rangeSelection.add_item(itemrange);

   }


   void list::_001GetSelection(::database::key & key, ::database::selection &selection)
   {

      if (!_001HasConfigId(key))
      {

         return;

      }

      auto iFilterSubItem = _001ConfigIdToColumnKey(key);

      range & range = m_rangeSelection;

      for (index i = 0; i < range.get_item_count(); i++)
      {

         auto & itemrange = range.ItemAt(i);

         if (itemrange.has_sub_item(iFilterSubItem))
         {

            for (index iLine = itemrange.get_lower_bound(); iLine <= itemrange.get_upper_bound(); iLine++)
            {

               selection.add_item(key.m_strDataKey + "/" + __str(iLine));

            }

         }

      }

   }


   /*index user::range::get_item(index iItemIndex)
   {
   index iFirst = 0;
   index i = 0;
   index iItem;

   while(true)
   {
   if(i >= m_itemrangea.get_size())
   return -1;
   iItem = iItemIndex - iFirst;
   auto & itemrange = m_itemrangea[i];
   if(iItem < itemrange.get_count())
   {
   return itemrange.get_item(iItem);
   }
   iFirst += itemrange.get_count();
   i++;
   }



   }*/

   /*index user::range::get_count()
   {
   return m_iItemEnd - m_iItemStart + 1;
   }*/

   /*index user::range::get_item(index iItemIndex)
   {
   return m_iItemStart + iItemIndex;
   }*/

   //::count user::range::get_item_count() const
   //{
   //   return m_itemrangea.get_size();
   //   /*   index iCount = 0;

   //   for(index i = 0; i < m_itemrangea.get_size(); i++)
   //   {
   //   auto & itemrange = m_itemrangea[i];
   //   iCount += itemrange.get_count();
   //   }

   //   return iCount;*/
   //}

   //user::range & user::range::ItemAt(index iItem)
   //{
   //   return m_itemrangea.element_at(iItem);
   //}


   ::count list::_001GetSelectedItemCount()
   {

      return m_rangeSelection.get_item_count();

   }


   ::count list::_001GetSelectedItems(index_array & ia)
   {

      return m_rangeSelection.get_items(ia);

   }


   id list::_001GetColumnTextId(index iColumn)
   {

      list_column * pcolumn = m_columna.get_visible(iColumn);

      if (pcolumn == nullptr)
      {

         return id();

      }

      return pcolumn->m_uiText;

   }


   void list::_001OnLButtonDblClk(::message::message * pmessage)
   {

      __pointer(::message::mouse) pmouse(pmessage);

      m_iClick = 2;

      auto point = pmouse->m_point;

      _001ScreenToClient(point);

      index iDisplayItem = -1;

      if(!m_bHoverSelect2)
      {

         if (_001DisplayHitTest(point, iDisplayItem))
         {

            if (iDisplayItem >= 0 && m_iDisplayItemLButtonDown1 == iDisplayItem)
            {

               index iItem = _001DisplayToStrict(iDisplayItem);

               if (iItem >= 0)
               {

                  //_001OnItemClick(iItem);
                  on_click({ ::user::e_element_item, iItem });

               }

            }

         }

      }

      /* trans window_id wndidNotify = puserinteraction->get_owner()->GetSafeoswindow_();
      if(wndidNotify == nullptr)
      wndidNotify = puserinteraction->get_parent()->GetSafeoswindow_();*/

      lresult lresult = 0;

      /* trans if(wndidNotify)
      {
      NMLISTVIEW nm;
      nm.hdr.idFrom = puserinteraction->GetDlgCtrlId();
      nm.hdr.code =   NM_DBLCLK;
      nm.hdr.oswindowFrom = puserinteraction->GetSafeoswindow_();
      lresult = ::SendMessage(
      wndidNotify,
      WM_NOTIFY,
      nm.hdr.idFrom,
      (LPARAM) &nm);


      }*/

      if (lresult == 0)
      {
         pmouse->m_bRet = false;
         return;
      }
      else
      {
         pmouse->m_bRet = true;
         return;
      }
   }

   void list::HeaderCtrlLayout()
   {

      if (m_plistheader == nullptr)
         return;

      auto pointOffset = get_viewport_offset();

      m_plistheader->order_top();
      m_plistheader->move_to(-pointOffset.x, 0);
      m_plistheader->display();

   }


   index list::HeaderCtrlMapColumnToOrder(index iColumn)
   {

      if (m_plistheader == nullptr)
      {

         return iColumn;

      }

      return m_plistheader->MapItemToOrder(iColumn);

   }


   bool list::_001OnHeaderCtrlEndDrag(wparam wparam, lparam lparam)

   {

      UNREFERENCED_PARAMETER(wparam);

      UNREFERENCED_PARAMETER(lparam);


      for (index iColumn = 0; iColumn < m_columna.VisibleGetCount(); iColumn++)
      {

         list_column * pcolumn = m_columna.get_visible(iColumn);

         pcolumn->m_iOrder = HeaderCtrlMapColumnToOrder(iColumn);

      }

      _001OnColumnChange();

      DISaveOrder();

      set_need_redraw();

      return true;

   }


   /*LRESULT list::OnEndColumnHeaderDragMessage(wparam wparam, lparam lparam)

   {
   HeaderCtrlOnEndDrag();
   return 0;
   }*/

   /*LRESULT list::OnEndColumnHeaderTrackMessage(wparam wparam, lparam lparam)

   {
   HeaderCtrlOnEndTrack();
   return 0;
   }*/

   /*LRESULT list::OnColumnHeaderTrackMessage(wparam wparam, lparam lparam)

   {
   HeaderCtrlOnTrack();
   return 0;
   }*/


   bool list::_001OnHeaderCtrlEndTrack(wparam wparam, lparam lparam)

   {

      UNREFERENCED_PARAMETER(wparam);

      UNREFERENCED_PARAMETER(lparam);


      _001OnHeaderCtrlTrack(0, 0);

      string str;

      index i;

      index width;

      for (i = 0; i < m_columna.get_count(); i++)
      {

         str.Format("list_column[%d].width", i);

         width = m_columna.element_at(i)->m_iWidth;

         //data_set(str, width);

      }

      return true;

   }


   bool list::_001OnHeaderCtrlTrack(wparam wparam, lparam lparam)

   {

      UNREFERENCED_PARAMETER(wparam);

      UNREFERENCED_PARAMETER(lparam);


      //    for(index iColumn = 0; iColumn < m_columna.VisibleGetCount(); iColumn++)
      //  {
      //         list_column & column = m_columna.get_visible(iColumn);
      //pcolumn->m_iWidth = m_plistheader->GetItemWidth(iColumn);
      //}

      _001OnColumnChange();

      set_need_redraw();

      return true;

   }


   void list::_001ShowSubItem(index iSubItem, bool bShow)
   {

      string str;

      str.Format("SubItem[%d].Visible", iSubItem);

      //data_set(str, bShow ? 1 : 0);

      m_columna.ShowSubItem(iSubItem, bShow);

      _001OnColumnChange();

      set_need_redraw();

   }



   ::index list_column_array::get_index(const list_column * pcolumn) const
   {

      return find_first(pcolumn);

   }


   ::index list_column_array::get_visible_index(const list_column * pcolumn) const
   {

      ::count cVisible = 0;

      for (index i = 0; i < this->get_size(); i++)
      {

         list_column * pcolumn = element_at(i);

         if (pcolumn->m_bVisible)
         {

            if (pcolumn == element_at(i))
            {

               return cVisible;

            }

            cVisible++;

         }

      }

      return -1;

   }


   list_column * list_column_array::get_visible(index iIndex)
   {

      ::count cVisible = 0;

      for (index i = 0; i < this->get_size(); i++)
      {

         list_column * pcolumn = element_at(i);

         if (::is_null(pcolumn))
         {

            continue;

         }

         if (pcolumn->m_bVisible)
         {

            if (iIndex == cVisible)
            {

               return pcolumn;

            }

            cVisible++;

         }

      }

      return nullptr;

   }


   list_column * list_column_array::get_by_index(index iIndex)
   {

      if (iIndex < 0)
      {

         return nullptr;

      }

      if (iIndex >= get_count())
      {

         return nullptr;

      }

      return element_at(iIndex);

   }

   index list_column_array::subitem_index(index iSubItem)
   {

      for (index iIndex = 0; iIndex < this->get_size(); iIndex++)
      {

         list_column * pcolumn = element_at(iIndex);

         if (pcolumn != nullptr && pcolumn->m_iSubItem == iSubItem)
         {

            return iIndex;

         }

      }

      return -1;

   }

   index list_column_array::subitem_visible_index(index iSubItem)
   {

      ::count cVisible = 0;

      for (index iIndex = 0; iIndex < this->get_size(); iIndex++)
      {

         list_column * pcolumn = element_at(iIndex);

         if (pcolumn == nullptr)
         {

            continue;

         }

         if (pcolumn->m_bVisible)
         {

            if (pcolumn->m_iSubItem == iSubItem)
            {

               return cVisible;

            }

            cVisible++;

         }

      }

      return -1;

   }


   index list_column_array::control_id_index(const ::id & id)
   {

      for (index iIndex = 0; iIndex < this->get_size(); iIndex++)
      {

         list_column * pcolumn = element_at(iIndex);

         if (pcolumn != nullptr && pcolumn->m_id == id)
         {

            return iIndex;

         }

      }

      return -1;

   }

   list_column * list_column_array::get_by_subitem(index iSubItem)
   {

      index iIndex = subitem_index(iSubItem);

      return get_by_index(iIndex);

   }


   list_column * list_column_array::get_by_control_id(const ::id & id)
   {

      index iIndex = subitem_index(id);

      return get_by_index(iIndex);

   }


   list_column * list_column_array::get_by_control(::user::interaction * pinteraction)
   {

      return get_by_control_id(pinteraction->m_id);

   }


   index list_column_array::add(list_column * pcolumn)
   {

      ::pointer_array < list_column >::add(pcolumn);

      pcolumn->m_iOrder = this->get_upper_bound();

      pcolumn->m_pcontainer = this;

      OnChange();

      return pointer_array < list_column >::get_upper_bound();

   }


   void list_column_array::erase_all()
   {

      pointer_array < list_column >::erase_all();

      OnChange();

   }

   ::count list_column_array::get_count()
   {
      return this->get_size();
   }

   list_column_array::list_column_array()
   {
      m_plist = nullptr;
   }

   void list_column_array::Initialize(list * plist)
   {
      ASSERT(plist != nullptr);
      m_plist = plist;
   }


   void list_column_array::OnChange()
   {


      predicate_sort(predicate_list_compare_key);
//      sort::array::quick_sort(*this, list_column::CompareKey);

      //index iKeyVisible = 0;
      //index iKeyNonVisible = 0;

      //for (index i = 0; i < this->get_size(); i++)
      //{
      //   list_column * pcolumn = element_at(i);
      //   if (pcolumn->m_bVisible)
      //   {
      //      pcolumn->m_iKeyVisible = iKeyVisible;
      //      pcolumn->m_iKeyNonVisible = -1;
      //      iKeyVisible++;
      //   }
      //   else
      //   {
      //      pcolumn->m_iKeyNonVisible = iKeyNonVisible;
      //      pcolumn->m_iKeyVisible = -1;
      //      iKeyNonVisible++;
      //   }
      //}

      predicate_sort(list_column::less_SectEndNonVisible);

      for (index iOrder = 0; iOrder < this->get_size(); iOrder++)
      {

         auto pcolumn = this->element_at(iOrder);

         pcolumn->m_iOrder = iOrder;

      }

   }


   void list_column_array::erase(index iColumn)
   {
      ASSERT(iColumn >= 0);
      ASSERT(iColumn < this->get_size());

      erase_at(iColumn);

      OnChange();
   }

   ::count list_column_array::VisibleGetCount()
   {
      index iCount = 0;
      for (index i = 0; i < this->get_size(); i++)
      {
         list_column * pcolumn = element_at(i);
         if (pcolumn == nullptr)
         {
            continue;

         }
         if (pcolumn->m_bVisible)
            iCount++;
      }
      return iCount;
   }

   //::count list_column_array::NonVisibleGetCount()
   //{
   //   index iCount = 0;
   //   for (index i = 0; i < this->get_size(); i++)
   //   {
   //      list_column * pcolumn = element_at(i);
   //      if (!pcolumn->m_bVisible)
   //         iCount++;
   //   }
   //   return iCount;
   //}

   void list_column_array::ShowSubItem(index iSubItem, bool bShow)
   {

      index iColumn = subitem_index(iSubItem);

      if (iColumn >= 0)
      {

         list_column * pcolumn = get_by_index(iColumn);

         pcolumn->m_bVisible = bShow;

         OnChange();

      }

   }


   //index list_column_array::subitem_index(index iSubItem)
   //{

   //   for (index iIndex = 0; iIndex < get_count(); iIndex++)
   //   {

   //      list_column * pcolumn = element_at(iIndex);

   //      if (pcolumn != nullptr && pcolumn->m_iSubItem == iSubItem)
   //      {

   //         return iIndex;

   //      }

   //   }

   //
   //}


   //index list_column_array::subitem_visible_index(index iSubItem)
   //{
   //   list_column * pcolumn = get_by_subitem(iSubItem);
   //   if (pcolumn == nullptr)
   //      return -1;
   //   return pcolumn->get_visible_index();
   //}


   //index list_column_array::subitem_visible_index(index iSubItem)
   //{
   //   i32 iVisible = 0;
   //   for (index iColumn = 0; iColumn < this->get_count(); iColumn++)
   //   {
   //      list_column * pcolumn = element_at(iColumn);
   //      if (pcolumn != nullptr && pcolumn->m_bVisible)
   //      {
   //         if (pcolumn->m_iSubItem == iSubItem)
   //         {
   //            return iVisible;
   //         }
   //         else
   //         {
   //            iVisible++;
   //         }
   //      }
   //   }
   //   return -1;
   //}

   //index list_column_array::NonVisibleMapSubItemToColumn(index iSubItem)
   //{
   //   i32 iNonVisible = 0;
   //   for (index iColumn = 0; iColumn < this->get_count(); iColumn++)
   //   {
   //      list_column * pcolumn = element_at(iColumn);
   //      if (!pcolumn->m_bVisible)
   //      {
   //         if (pcolumn->m_iSubItem == iSubItem)
   //         {
   //            return iNonVisible;
   //         }
   //         else
   //         {
   //            iNonVisible++;
   //         }
   //      }
   //   }
   //   return -1;

   //}



   //void list_column_array::GlobalToVisibleOrder()
   //{
   //   iptr iVisibleCount = VisibleGetCount();
   //   for (index iVisibleKey = 0; iVisibleKey < iVisibleCount; iVisibleKey++)
   //   {
   //      list_column * pcolumn = get_visible(iVisibleKey);
   //      pcolumn->m_iOrder = VisibleGetOrderFromKey(pcolumn->m_iKey);
   //   }


   //}

   //void list_column_array::VisibleToGlobalOrder(index iKeyA, index iKeyB)
   //{
   //   if (iKeyA == iKeyB)
   //      return;
   //   list_column * columnA = _001GetByKey(iKeyA);
   //   list_column * columnAPrevious = GlobalOrderGetPrevious(iKeyA);
   //   list_column * columnANext = GlobalOrderGetNext(iKeyA);
   //   list_column * columnB = _001GetByKey(iKeyB);
   //   list_column * columnBPrevious = GlobalOrderGetPrevious(iKeyB);
   //   list_column * columnBNext = GlobalOrderGetNext(iKeyB);

   //   if (columnA == nullptr)
   //      return;

   //   if (columnB == nullptr)
   //      return;

   //   if (columnAPrevious == nullptr)
   //   {
   //      m_iFirstGlobalOrderKey = iKeyB;
   //   }
   //   else
   //   {
   //      if (columnAPrevious->m_iKey != iKeyB)
   //      {
   //         columnAPrevious->m_iNextGlobalOrderKey = iKeyB;
   //      }
   //   }


   //   if (columnBPrevious == nullptr)
   //   {
   //      m_iFirstGlobalOrderKey = iKeyA;
   //   }
   //   else
   //   {
   //      if (columnBPrevious->m_iKey != iKeyA)
   //      {
   //         columnBPrevious->m_iNextGlobalOrderKey = iKeyA;
   //      }
   //   }

   //   if (columnANext == nullptr)
   //   {
   //      columnB->m_iNextGlobalOrderKey = -1;
   //   }
   //   else
   //   {
   //      if (columnANext->m_iKey == columnB->m_iKey)
   //      {
   //         columnB->m_iNextGlobalOrderKey = iKeyA;
   //      }
   //      else
   //      {
   //         columnB->m_iNextGlobalOrderKey = columnANext->m_iKey;
   //      }
   //   }

   //   if (columnBNext == nullptr)
   //   {
   //      columnA->m_iNextGlobalOrderKey = -1;
   //   }
   //   else
   //   {
   //      if (columnBNext->m_iKey == columnA->m_iKey)
   //      {
   //         columnB->m_iNextGlobalOrderKey = iKeyB;
   //      }
   //      else
   //      {
   //         columnA->m_iNextGlobalOrderKey = columnBNext->m_iKey;
   //      }
   //   }



   //}

   //void list_column_array::VisibleToGlobalOrder()
   //{
   //   list * plist = m_plist;
   //   //detects change
   //   iptr iVisibleCount = VisibleGetCount();
   //   iptr iChangeCount = 0;
   //   iptr iNew = 0;
   //   iptr iOld = 0;
   //   for (iptr iVisibleKey = 0; iVisibleKey < iVisibleCount; iVisibleKey++)
   //   {
   //      list_column * column = get_visible(iVisibleKey);
   //      if (VisibleGetOrderFromKey(column->m_iKey) != plist->HeaderCtrlMapColumnToOrder(iVisibleKey))
   //      {
   //         iChangeCount++;
   //         if (iChangeCount == 1)
   //         {
   //            iNew = iVisibleKey;
   //         }
   //         else if (iChangeCount == 2)
   //         {
   //            iOld = iVisibleKey;
   //         }
   //      }
   //   }
   //   if (iChangeCount == 2)
   //   {
   //      VisibleToGlobalOrder(iNew, iOld);
   //   }
   //   else
   //   {
   //      if (this->get_size() == VisibleGetCount())
   //      {
   //         for (index iColumn = 0; iColumn < VisibleGetCount(); iColumn++)
   //         {
   //            list_column * column = get_visible(iColumn);
   //            column->m_iOrder = plist->HeaderCtrlMapColumnToOrder(iColumn);
   //         }

   //         m_iFirstGlobalOrderKey = OrderToKey(0);
   //         if (m_iFirstGlobalOrderKey >= 0)
   //         {
   //            index iKey = m_iFirstGlobalOrderKey;
   //            index iNextKey;
   //            index iOrder = 1;

   //            while (true)
   //            {
   //               iNextKey = OrderToKey(iOrder);
   //               _001GetByKey(iKey)->m_iNextGlobalOrderKey = iNextKey;
   //               if (iNextKey < 0)
   //               {
   //                  break;
   //               }
   //               iOrder++;
   //               iKey = iNextKey;
   //            }
   //         }
   //      }

   //   }
   //}

   void list_column_array::DISaveOrder()
   {

//      auto iCount = this->get_size();
//
//      string str;
//
//      for (index i = 0; i < iCount; i++)
//      {
//
//         list_column * pcolumn = element_at(i);
//
//         str.Format("list_column[%d].Next", i);
//
//         //m_plist->data_set(str, pcolumn->m_iOrder);
//
//      }

   }


   void list_column_array::DILoadOrder()
   {

//      auto iCount = this->get_size();
//
//      string str;
//
//      for (index i = 0; i < iCount; i++)
//      {
//
//         list_column * pcolumn = element_at(i);
//
//         str.Format("list_column[%d].Next", i);
//
//         //m_plist->data_get(str, pcolumn->m_iOrder);
//
//      }

      OnChange();

   }


   //index list_column_array::VisibleIndexOrder(index iIndex)
   //{

   //   list_column * pcolumn = get_visible(iIndex);

   //   if (pcolumn == nullptr)
   //   {

   //      return -1;

   //   }

   //   return pcolumn->m_iOrder;

   //}


   index list_column_array::order_index(index iOrder)
   {

      for (index iIndex = 0; iIndex < this->get_count(); iIndex++)
      {

         list_column * column = element_at(iIndex);

         if (column->m_iOrder == iOrder)
         {

            return iIndex;

         }

      }

      return -1;

   }


   void list::DISaveOrder()
   {

      m_columna.DISaveOrder();

   }

   void list::DILoadOrder()
   {
      m_columna.DILoadOrder();
      _001OnColumnChange();
   }









   void list::_001UpdateColumns()
   {

      _001RemoveAllColumns();

      auto keepLockViewUpdate = keep(m_bLockViewUpdate);

      _001InsertColumns();

      keepLockViewUpdate.KeepAway();

      DIDDXHeaderLayout(false);

      _001OnColumnChange();

   }


   void list::_001InsertColumns()
   {


   }


   void list::_001RemoveAllColumns()
   {

      {

         synchronous_lock synchronouslock(mutex());

         m_columna.erase_all();

      }

      _001OnColumnChange();

   }


   void list::PreSubClassWindow()
   {

      if (is_window_visible())
      {

         set_need_redraw();

      }

   }


   void list::on_message_create(::message::message * pmessage)
   {

      __pointer(::message::create) pcreate(pmessage);

      pmessage->previous();

      if (pcreate->m_lresult == -1)
      {

         pmessage->m_bRet = false;

         return;

      }

      if (m_bAutoCreateListHeader)
      {

         if (m_plistheader.is_null())
         {

            m_plistheader = create_list_header();

            if (m_plistheader.is_set())
            {

               m_plistheader->SetBaseListCtrlInterface(this);

            }

         }

         if (m_plistheader != nullptr)
         {

            if (!CreateHeaderCtrl())
            {

               pcreate->m_lresult = -1;

               pmessage->m_bRet = true;

               return;

            }

         }

      }

      pcreate->m_lresult = 0;

      //on_ui_event(event_create, object_list, this);

      pmessage->m_bRet = false;

      _001UpdateColumns();

   }






   void list::_001CreateImageList(list_column * pcolumn)
   {

      if (pcolumn == nullptr)
      {

         return;

      }

      if (pcolumn->m_uiSmallBitmap == (::u32)-1)
      {

         return;

      }

      if (pcolumn->m_pil == nullptr)
      {

         pcolumn->m_pil = __new(::image_list);

      }

      ::exception::throw_not_implemented();

      /*
      if(!pil->create(
         MAKEINTRESOURCE(pcolumn->m_uiSmallBitmap),
         pcolumn->m_iSmallImageWidth,
         0,
         pcolumn->m_colorSmallMask))
      {
      }
      */

   }


   void list::_001OnTimer(::timer * ptimer)
   {

      ::user::mesh::_001OnTimer(ptimer);

      ptimer->m_bRet = false;

   }


   bool list::_001IsItemVisible(index iItem)
   {

      draw_list_item item(this);

      item.m_iItem = iItem;

      item.m_iDisplayItem = iItem;

      _001GetItemRect(&item);

      if (!item.m_bOk)
      {

         return false;

      }

      ::rectangle_i32 rectClient;

      get_client_rect(&rectClient);

      return rectClient.intersect(rectClient, item.m_rectItem) != 0;

   }


   void list::_001ClearSelection()
   {

      m_rangeSelection.clear();

      _001OnSelectionChange();

   }


   void list::_001SetSelection(const range &range)
   {
      m_rangeSelection = range;
      on_select();
      _001OnSelectionChange();
   }

   
   void list::_001AddSelection(const item_range & itemrange)
   {
   
      m_rangeSelection.add_item(itemrange);

//      on_select();

      _001OnSelectionChange();

   }


   void list::_001SetHighlightRange(range & range)
   {
      m_rangeHighlight = range;
   }


   bool list::DIDDXHeaderLayout(bool bSave)
   {

      if (m_plistheader == nullptr)
      {

         return false;

      }

      return m_plistheader->DIDDXLayout(bSave);

   }


   void list::_001SetTopText(const widechar * pcwsz)
   {

      m_strTopText = pcwsz;

      auto pgraphics = ::draw2d::create_memory_graphics();

      _001LayoutTopText(pgraphics);

   }


   void list::_001LayoutTopText(::draw2d::graphics_pointer& pgraphics)
   {

      pgraphics->set_font(this, ::user::e_element_none);

      ::size_array sizea;

      m_dcextension.GetTextExtent(pgraphics, m_strTopText, sizea);
      ::rectangle_i32 rectClient;
      get_client_rect(rectClient);
      index x = 0;
      index right = rectClient.right;
      index y = 0;
      for (index i = 0; i < sizea.get_size(); i++)
      {
         if ((sizea[i].cx - x > right)
               || i == sizea.get_upper_bound())
         {
            if (i == 0)
            {
               x = sizea[0].cx;
               y += sizea[0].cy;
            }
            else
            {
               x = sizea[i - 1].cx;
               y += sizea[i - 1].cy;
            }
         }
      }

      m_rectTopText.left = 0;
      m_rectTopText.top = 0;
      m_rectTopText.right = rectClient.right;
      m_rectTopText.bottom = (::i32)y;


   }

   void list::_001ShowTopText(bool bShow)
   {
      m_bTopText = bShow;
   }




   void list::CacheHint()
   {

      synchronous_lock synchronouslock(mutex());

      if (m_pcache.is_set())
      {

         auto iItemCount = m_nDisplayCount;

         auto iItemFirst = m_iTopDisplayIndex;

         m_pcache->_001CacheHint(this, iItemFirst, iItemCount);

      }

   }


   void list::SetDataInterface(::user::mesh_data *pchannel)
   {

      mesh::SetDataInterface(pchannel);

      m_psimplelistdata = m_pmeshdata;

   }



   //bool list::_001InsertColumn(list_column * pcolumn)
   //{

   //

   //   return true;

   //}


   void list::_001SetSingleColumnMode(bool bHeaderCtrl)
   {

      m_bSingleColumnMode = true;

      m_bHeaderCtrl = bHeaderCtrl;
      _001RemoveAllColumns();


      {

         auto pcolumn = new_list_column();
         pcolumn->m_iWidth = -1;
         pcolumn->m_iSubItem = 0;
         pcolumn->m_iSmallImageWidth = 16;
         pcolumn->m_colorSmallMask = argb(255, 255, 0, 255);



      }

      set_need_redraw();

   }


   //i32 list::_001CalcItemWidth(::draw2d::graphics_pointer & pgraphics, index iItem, index iSubItem)
   //{

   //   pgraphics->set_font(this, ::user::e_element_none);

   //   index cx = _001CalcItemWidth(pgraphics, iItem, iSubItem);

   //   return (i32)cx;

   //}


   i32 list::_001CalcItemWidth(::draw2d::graphics_pointer & pgraphics, ::write_text::font * pfont, index iItem, index iSubItem)
   {

      pgraphics->set(pfont);

      return _001CalcItemWidth(pgraphics, iItem, iSubItem);

   }


   i32 list::_001CalcItemWidth(::draw2d::graphics_pointer & pgraphics, index iItem, index iSubItem)
   {

      ::image_list::info ii;

      ::rectangle_i32 rectangle;

      ::size_i32 size;

      index cx = 0;

      list_column * pcolumn = m_columna.get_by_subitem(iSubItem);

      draw_list_item item(this);

      item.m_iItem = iItem;

      item.m_iSubItem = iSubItem;

      item.m_iListItem = -1;

      if (pcolumn->m_pil != nullptr)
      {

         _001GetItemImage(&item);

         if (item.m_bOk && item.m_iImage >= 0)
         {

            pcolumn->m_pil->get_image_info((i32)item.m_iImage, &ii);

            rectangle = ii.m_rectangle;

            cx += rectangle.width();

            cx += 2;

         }

      }

      _001GetItemText(&item);

      if (item.m_bOk)
      {

         pgraphics->set_font(this, ::user::e_element_none);

         m_dcextension.GetTextExtent(pgraphics, item.m_strText, item.m_strText.get_length(), size);

         cx += size.cx;

      }

      auto pstyle = get_style(pgraphics);

      return (i32)(cx * get_double(pstyle, ::user::e_double_width_rate, ::user::e_state_none, 1.2));

   }




   bool list::_001HasConfigId(const ::database::key & key)
   {
      return _001ConfigIdToColumnKey(key) >= 0;
   }

   index list::_001ConfigIdToSubItem(const ::database::key & key)
   {
      list_column * column = m_columna.get_by_config_id(key);
      if (column == nullptr)
         return -1;
      return column->m_iSubItem;
   }


   index list::config_id_index(const ::database::key & key)
   {

      return m_columna.config_id_index(key);

   }



   list_column * list_column_array::get_by_config_id(const ::database::key & key)
   {
      index iKey = config_id_index(key);
      if (iKey >= 0)
         return element_at(iKey);
      else
         return nullptr;

   }


   index list_column_array::config_id_index(const ::database::key & key)
   {

      for (index iIndex = 0; iIndex < this->get_size(); iIndex++)
      {

         if (this->element_at(iIndex)->m_datakey == key)
         {

            return iIndex;

         }

      }

      return -1;

   }


   index list_column_array::config_id_visible_index(const ::database::key & key)
   {

      ::count cVisible = 0;

      for (index iIndex = 0; iIndex < this->get_size(); iIndex++)
      {

         if (this->element_at(iIndex)->m_bVisible)
         {

            if (this->element_at(iIndex)->m_datakey == key)
            {

               return cVisible;

            }

            cVisible++;

         }

      }

      return -1;

   }



   //void user::range::set(index iLowerBoundItem, index iUpperBoundItem, index iLowerBoundSubItem, index iUpperBoundSubItem, index iLowerBoundListItem, index iUpperBoundListItem)
   //{

   //   m_iLowerBound = iLowerBoundItem;
   //   m_iUpperBound = iUpperBoundItem;
   //   m_subitemrange.set(
   //      iLowerBoundSubItem,
   //      iUpperBoundSubItem,
   //      iLowerBoundListItem,
   //      iUpperBoundListItem);
   //}

   //void user::range::set_lower_bound(index iLowerBoundItem)
   //{
   //   m_iLowerBound = iLowerBoundItem;
   //}

   //void user::range::set_upper_bound(index iUpperBoundItem)
   //{
   //   m_iUpperBound = iUpperBoundItem;
   //}

   //void user::sub_item_range::set(index iLowerBoundSubItem, index iUpperBoundSubItem, index iLowerBoundListItem, index iUpperBoundListItem)
   //{
   //   m_iLowerBound = iLowerBoundSubItem;
   //   m_iUpperBound = iUpperBoundSubItem;
   //   m_meshitemrange.set(
   //      iLowerBoundListItem,
   //      iUpperBoundListItem);
   //}

   //void user::list_item_range::set(index iLowerBoundListItem, index iUpperBoundListItem)
   //{
   //   m_iLowerBound = iLowerBoundListItem;
   //   m_iUpperBound = iUpperBoundListItem;

   //}


   void list::_001EnsureVisible(index iItem, ::e_align ealign, bool bRedraw)
   {

      auto pointOffset = get_viewport_offset();

      if (ealign & e_align_vertical_center)
      {

         iItem = iItem - (maximum(0, m_nDisplayCount - 2) / 2);

      }
      else if (ealign & e_align_bottom)
      {

         iItem = minimum(iItem + m_nDisplayCount - 1, _001GetItemCount() - 1);

      }

      if (iItem >= (_001GetItemCount() - m_nDisplayCount))
      {

         iItem = (_001GetItemCount() - m_nDisplayCount);

      }

      if (iItem < 0)
      {

         iItem = 0;

      }

      if (m_dItemHeight > 0
            &&
            (iItem < pointOffset.y / m_dItemHeight ||
             iItem >= pointOffset.y / m_dItemHeight + m_nDisplayCount))
      {

         pointOffset.y = (::i32)(iItem * m_dItemHeight);

         queue_graphics_call([this, pointOffset](::draw2d::graphics_pointer & pgraphics)
            {

               set_viewport_offset_y(pgraphics, pointOffset.y);

               on_change_viewport_offset(pgraphics);

            });

         if (bRedraw)
         {

            set_need_redraw();

         }

      }

   }


   void list::_001ItemScroll(index iItem, bool bRedraw)
   {

      if (iItem < m_nItemCount)
      {

         auto pointOffset = get_viewport_offset();

         pointOffset.y = (::i32)(iItem * m_dItemHeight);

         queue_graphics_call([this, pointOffset](::draw2d::graphics_pointer & pgraphics)
            {

               set_viewport_offset_y(pgraphics, pointOffset.y);

               on_change_viewport_offset(pgraphics);

            });

         if (bRedraw)
         {

            set_need_redraw();

         }

      }

   }

   void list::_001EnsureVisible(index iItem, range & range)
   {

      auto pointOffset = get_viewport_offset();

      index iyScroll = (index) ( pointOffset.y / maximum(1, m_dItemHeight));

      if (iItem < iyScroll)
      {

         iyScroll = iItem - m_nDisplayCount + 1;

      }
      else if (iItem >= iyScroll + m_nDisplayCount)
      {

         iyScroll = iItem;

      }

      if (pointOffset.y / maximum(1, m_dItemHeight) != iyScroll)
      {

         item_range item;

         pointOffset.y = (::i32)(iyScroll * m_dItemHeight);

         queue_graphics_call([this](::draw2d::graphics_pointer & pgraphics)
            {

               on_change_viewport_offset(pgraphics);

            });

         item.set_lower_bound(iyScroll);

         item.set_upper_bound(minimum(iyScroll + m_nDisplayCount - 1, m_nItemCount - 1));

         range.add_item(item);

      }

   }

   void list::_001Highlight(index iItem, bool bRedraw)
   {
      m_rangeHighlight.clear();
      item_range itemrange;
      itemrange.set(iItem, iItem, 0, m_columna.get_count() - 1, -1, -1);
      m_rangeHighlight.add_item(itemrange);
      if (bRedraw)
      {
         set_need_redraw();
      }
      _001OnSelectionChange();
   }


   bool list::_001OnRemoveItem(index iItem)
   {
      UNREFERENCED_PARAMETER(iItem);
      return false;
   }

   bool list::_001RemoveItem(index iItem, bool bRedraw)
   {
      if (!_001OnRemoveItem(iItem))
         return false;
      m_rangeSelection.OnRemoveItem(iItem);
      if (bRedraw)
      {
         set_need_redraw();
      }
      return true;
   }

   //void user::range::offset(index iOffset)
   //{
   //   m_iLowerBound += iOffset;
   //   m_iUpperBound += iOffset;
   //}

   void list::_001RemoveSelection()
   {
      ::user::range range;

      _001GetSelection(range);


      while (range.get_item_count() > 0)
      {
         index iItem = range.ItemAt(0).get_lower_bound();
         if (!_001RemoveItem(iItem, false))
            break;
         _001GetSelection(range);
      }

      set_need_redraw();
   }


   void list::_001Select(index iItem, index iSubItem)
   {
      m_rangeSelection.clear();
      item_range itemrange;
      itemrange.set(iItem, iItem, iSubItem, iSubItem, -1, -1);
      m_rangeSelection.add_item(itemrange);
      _001OnSelectionChange();
   }


   index list::_001StrictToDisplay(index iStrict)
   {

      UNREFERENCED_PARAMETER(iStrict);

      return -1;

   }


   index list::_001DisplayToStrict(index iDisplay)
   {

      if (iDisplay < 0)
      {

         return -1;

      }

      if (m_eview == impact_icon)
      {

         return m_piconlayout->m_iaDisplayToStrict[iDisplay];

      }
      else
      {
         if (iDisplay < 0)
            return -1;
         if (m_pmeshlayout->m_iaDisplayToStrict.get_count() <= 0)
         {
            if (iDisplay < m_nItemCount)
               return iDisplay;
         }
         //if(m_pmeshlayout->m_iaDisplayToStrict.get_count() != m_nItemCount)
         // return iDisplay;
         if (iDisplay >= m_pmeshlayout->m_iaDisplayToStrict.get_count())
         {
            return -1;
         }
         return m_pmeshlayout->m_iaDisplayToStrict[iDisplay];
      }
   }

   void list::FilterBegin()
   {
      m_efilterstate = FilterStateSetup;

      index iItemCount = m_nItemCount;

      if (m_eview == impact_icon)
      {
         m_piaFilterIcon->erase_all();

         for (index i = 0; i < iItemCount; i++)
         {
            m_piaFilterIcon->add(i);
         }
      }
      else
      {
         m_piaFilterMesh->erase_all();

         for (index i = 0; i < iItemCount; i++)
         {
            m_piaFilterMesh->add(i);
         }
      }

   }

   void list::FilterApply()
   {

      //      ASSERT(m_efilterstate == FilterStateSetup);

      m_iFilter1Step = 0;

      SetTimer(0xfffffffe, 50, nullptr);

      queue_graphics_call([this](::draw2d::graphics_pointer & pgraphics)
         {

            set_viewport_offset(pgraphics, 0, 0);

         });

      m_efilterstate = FilterStateFilter;

      set_need_layout();

      set_need_redraw();

   }


   void list::FilterClose()
   {

      m_bFilter1 = false;

      KillTimer(0xfffffffe);

      ASSERT(m_efilterstate == FilterStateSetup
             || m_efilterstate == FilterStateFilter);

      index iItemCount = m_nItemCount;

      if (m_eview == impact_icon)
      {
         m_piconlayout->m_iaDisplayToStrict.erase_all();

         for (index i = 0; i < iItemCount; i++)
         {
            m_piconlayout->m_iaDisplayToStrict.add(i);
         }
      }
      else
      {
         m_pmeshlayout->m_iaDisplayToStrict.erase_all();

         for (index i = 0; i < iItemCount; i++)
         {
            m_pmeshlayout->m_iaDisplayToStrict.add(i);
         }
      }

      set_need_layout();

      set_need_redraw();

   }


   void list::FilterExcludeAll()
   {

      if (m_eview == impact_icon)
      {

         m_piaFilterIcon->erase_all();

      }
      else
      {

         m_piaFilterMesh->erase_all();

      }

   }


   void list::FilterInclude(index iItem)
   {
      ASSERT(m_efilterstate == FilterStateSetup);
      if (m_eview == impact_icon)
      {
         m_piaFilterIcon->add_unique(iItem);
      }
      else
      {
         m_piaFilterMesh->add_unique(iItem);
      }
   }

   void list::FilterInclude(int_array & array)
   {
      ASSERT(m_efilterstate == FilterStateSetup);
      for (index i = 0; i < array.get_size(); i++)
      {
         FilterInclude(array[i]);
      }
   }


   bool list::Filter1Step()
   {

      auto tickIn = ::millis::now();

      TRACE("list::Filter1Step");

      TRACE("tickIn = " __prtick, __pr(tickIn));

      if (!m_bFilter1)
      {

         return false;

      }

      string wstrItem;

      index iItemCount = minimum(m_nItemCount, m_iFilter1Step + 1000);

      index iFilter1Step;

      draw_list_item item(this);

      for (
      iFilter1Step = m_iFilter1Step;
      iFilter1Step < iItemCount;
      iFilter1Step++)
      {
         for (index j = 0; j < m_columna.get_count(); j++)
         {
            list_column * pcolumn = m_columna.get_by_index(j);
            item.m_strText.Empty();
            item.m_iItem = iFilter1Step;
            item.m_iSubItem = pcolumn->m_iSubItem;
            item.m_iListItem = -1;
            _001SearchGetItemText(&item);
            if (item.m_bOk)
            {
               item.m_strText.make_lower();
               item.m_strText.replace("_", " ");
               if (m_pregexFilter1->matches(item.m_strText))
               {
                  if (m_eview == impact_icon)
                  {
                     m_piaFilterIcon->add_unique(iFilter1Step);
                  }
                  else
                  {
                     m_piaFilterMesh->add_unique(iFilter1Step);
                  }
                  break;
               }
            }
         }
      }

      m_iFilter1Step = (i32)iFilter1Step;

      if (m_eview == impact_icon)
      {
         m_piconlayout->m_iaDisplayToStrict = (*m_piaFilterIcon);
      }
      else
      {
         m_pmeshlayout->m_iaDisplayToStrict = (*m_piaFilterMesh);
      }

      queue_graphics_call([this](::draw2d::graphics_pointer & pgraphics)
         {

            set_viewport_offset(pgraphics, 0, 0);

         });

      m_efilterstate = FilterStateFilter;

      set_need_layout();

      set_need_redraw();

      auto tickOut = ::millis::now();

      TRACE("tickOut = " __prtick, __pr(tickOut));
      TRACE("(delta) = " __prtick, __pr(tickOut - tickIn));

      return m_nItemCount != iItemCount;

   }


   void list::Filter1(string & strFilter)
   {

      if (m_eview == impact_icon)
      {
         m_piaFilterIcon->erase_all();
      }
      else
      {
         m_piaFilterMesh->erase_all();
      }

      string_array stra;

      stra.add_tokens(strFilter, " ", false);

      //m_pregexFilter1->setPositionMoves(1);

      auto psystem = m_psystem->m_paxissystem;

      m_pregexFilter1 = psystem->create_pcre("/.*" + stra.implode(".*") + ".*/i");

      m_bFilter1 = m_pregexFilter1;//m_pregexFilter1->setRE();

      if (m_bFilter1)
      {
         FilterApply();
      }
      else
      {
         FilterClose();
      }

   }

   void list::_001OnListHeaderItemClick(index iHeaderItem)
   {
      if (!m_bSortEnable)
         return;
      _001OnSort(_001MapColumnToSubItem(iHeaderItem));
   }

   void list::_001OnListHeaderItemDblClk(index iHeaderItem)
   {

      auto pgraphics = create_memory_graphics();

      _001MaximizeColumnWidth(pgraphics, iHeaderItem);
   }


   void list::_001OnSort()
   {
      if (!m_bSortEnable)
         return;
      if (m_eview != impact_icon)
      {
         ::sort::quick_sort(m_pmeshlayout->m_iaDisplayToStrict, this, (::sort::compare_interface::_FUNCTION_Compare) &::user::mesh::_001Compare);
      }
      else
      {
      }
   }

   void list::_001OnSort(index iSubItem)
   {

      index iFound = -1;
      for (index i = 0; i < m_sortinfo.m_itema.get_size(); i++)
      {
         CSortInfoItem & item = m_sortinfo.m_itema[i];
         if (item.m_iSubItem == iSubItem)
         {
            iFound = i;
            break;
         }
      }
      if (iFound >= 0)
      {
         CSortInfoItem newItem = m_sortinfo.m_itema[iFound];
         m_sortinfo.m_itema.erase_at(iFound);
         newItem.m_bAscendent = !newItem.m_bAscendent;
         m_sortinfo.m_itema.insert_at(0, newItem);
      }
      else
      {
         CSortInfoItem newItem;
         newItem.m_iSubItem = iSubItem;
         newItem.m_bAscendent = true;
         m_sortinfo.m_itema.insert_at(0, newItem);
      }

      _001OnSort();

   }




   index list::_002Compare(index iItem1, index iItem2, index iSubItem)
   {
      draw_list_item item1(this);
      draw_list_item item2(this);

      item1.m_iItem = iItem1;
      item2.m_iItem = iItem2;
      item1.m_iSubItem = iSubItem;
      item2.m_iSubItem = iSubItem;

      _001GetItemText(&item1);
      _001GetItemText(&item2);

      if (item1.m_bOk && item2.m_bOk)
      {
         return item1.m_strText.compare_ci(item2.m_strText);
      }
      else
      {
         if (item1.m_bOk)
            return 1;
         else if (item2.m_bOk)
            return -1;
         else
            return 0;
      }

   }

   index list::_001Compare(index iItem1, index iItem2)
   {
      CSortInfoItem * pitem = nullptr;
      index iCompare = 0;
      for (index i = 0; i < m_sortinfo.m_itema.get_size(); i++)
      {
         pitem = &m_sortinfo.m_itema[i];
         iCompare = _002Compare(iItem1, iItem2, pitem->m_iSubItem);
         if (iCompare != 0)
            break;
      }
      if (pitem == nullptr)
         return 0;
      else
      {
         if (pitem->m_bAscendent)
            return iCompare;
         else
            return -iCompare;
      }
   }


   index list::_001DisplayCompare(index iDisplayItem1, index iDisplayItem2)
   {

      return _001Compare(_001DisplayToStrict(iDisplayItem1), _001DisplayToStrict(iDisplayItem2));

   }


   i32 list::_001CalcListWidth(::draw2d::graphics_pointer & pgraphics)
   {

      ASSERT(false);

      return -1;

   }


   i32 list::_001CalcColumnWidth(::draw2d::graphics_pointer& pgraphics, index iColumn)
   {

      UNREFERENCED_PARAMETER(iColumn);

      pgraphics->set_font(this, ::user::e_element_none);

      i32 iMaxWidth = 0;

      ::count iCount = m_nItemCount;

      i32 iWidth;

      for (index i = 0; i < iCount; i++)
      {

         iWidth = _001CalcItemWidth(pgraphics, i, 0);

         if (iWidth > iMaxWidth)
         {

            iMaxWidth = iWidth;

         }

      }

      return iMaxWidth;

   }


   void list::_001MaximizeColumnWidth(::draw2d::graphics_pointer& pgraphics, index iColumn)
   {

      _001SetColumnWidth(iColumn, _001CalcColumnWidth(pgraphics, iColumn));

   }


   void list::_OnDraw(::draw2d::graphics_pointer & pgraphics)
   {

      UNREFERENCED_PARAMETER(pgraphics);

   }


   i32 list::get_wheel_scroll_delta()
   {

      return (::i32) (3.* m_dItemHeight);

   }


   void list::on_change_viewport_offset(::draw2d::graphics_pointer & pgraphics)
   {

      synchronous_lock synchronouslock(mutex());

      auto point = get_viewport_offset();

      m_iTopDisplayIndex = _001CalcDisplayTopIndex();

      index iLow = 0;

      for (m_iTopGroup = 0; m_iTopGroup < m_nGroupCount; m_iTopGroup++)
      {

         if (m_iTopDisplayIndex >= iLow && m_iTopDisplayIndex < (iLow + _001GetGroupItemCount(m_iTopGroup)))
         {

            break;

         }

      }

      m_nDisplayCount = _001CalcDisplayItemCount();


      if (m_iTopDisplayIndex < 0 && m_dItemHeight > 0 && m_eview == impact_report && point.y != 0 && m_nDisplayCount > 0)
      {

         ::rectangle_i32 rectScroll;

         auto pscrollbar = get_horizontal_scroll_bar();

         if (pscrollbar)
         {

            pscrollbar->get_window_rect(rectScroll);

            if (point.y > (_001GetItemCount() - m_nDisplayCount) * m_dItemHeight + (m_bHeaderCtrl ? m_dItemHeight : 0))
            {

               point.y = (::i32) ((_001GetItemCount() - m_nDisplayCount) * m_dItemHeight + (m_bHeaderCtrl ? m_dItemHeight : 0));

            }

            if (point.y < 0)
            {

               point.y = 0;

            }

            m_pointScroll.y = point.y;

            m_iTopDisplayIndex = _001CalcDisplayTopIndex();

         }

      }

      HeaderCtrlLayout();

      CacheHint();

      auto psession = get_session();

      auto puser = psession->user();

      auto pwindowing = puser->windowing();

      auto pointCursor = pwindowing->get_cursor_position();

      update_hover(pointCursor);

      ::user::scroll_base::on_change_viewport_offset(pgraphics);

      set_need_redraw();

   }



   //::draw2d::pen * list::_001GetPenHighlight()
   //{
   //   return m_penHighlight;
   //}

   //::draw2d::pen * list::_001GetPenFocused()
   //{
   //   return m_penFocused;

   //}

   //::write_text::font * list::_001GetFont()
   //{
   //   return m_font;
   //}

   //::write_text::font * list::_001GetFontHover()
   //{
   //   return m_fontHover;
   //}

   void list::on_message_mouse_leave(::message::message * pmessage)
   {
      m_iDisplayItemHover = -1;
      m_iSubItemHover = -1;
      set_need_redraw();
      pmessage->m_bRet = true;
   }


   bool list::update_hover(const ::point_i32 & point, bool bAvoidRedraw)
   {

      index iItemHover;

      index iSubItemHover;

      auto pointClient = point;

      _001ScreenToClient(pointClient);

      bool bAnyHoverChange = false;

      if (_001DisplayHitTest(pointClient, iItemHover, iSubItemHover))
      {

         if (m_iSubItemHover != iSubItemHover || m_iDisplayItemHover != iItemHover)
         {

            m_iDisplayItemHover = iItemHover;

            m_iSubItemHover = iSubItemHover;

            bAnyHoverChange = true;

         }

      }
      else
      {

         if (m_iDisplayItemHover != -1 || m_iSubItemHover != -1)
         {

            m_iDisplayItemHover = -1;

            m_iSubItemHover = -1;

            bAnyHoverChange = true;

         }

      }

      if (!bAvoidRedraw)
      {

         if (bAnyHoverChange)
         {

            set_need_redraw();

            post_redraw();

         }

      }

      return bAnyHoverChange;

   }


   void list::data_get_DisplayToStrict()
   {

      if (m_eview == impact_icon)
      {

         //data_get(data_get_current_sort_id() + "." + data_get_current_list_layout_id(), m_piconlayout);

      }
      else
      {

         //data_get(data_get_current_sort_id() + "." + data_get_current_list_layout_id(), m_pmeshlayout);

      }

   }


   void list::data_set_DisplayToStrict()
   {
      if (m_eview == impact_icon)
      {
         //data_set(data_get_current_sort_id() + "." + data_get_current_list_layout_id(), m_piconlayout);
      }
      else
      {
         //data_set(data_get_current_sort_id() + "." + data_get_current_list_layout_id(), m_pmeshlayout);
      }
   }

   id list::data_get_current_sort_id()
   {
      return data_get_sort_id(m_eview);
   }

   id list::data_get_sort_id(EView eview)
   {

      return ::user::mesh::data_get_sort_id(eview);

      //UNREFERENCED_PARAMETER(eview);
      //switch(m_eview)
      //{
      //case impact_grid:
      //   return "sort-grid";
      //   break;
      //case impact_report:
      //   return "sort-report";
      //   break;
      //case impact_list:
      //   return "sort-list";
      //   break;
      //case impact_icon:
      //   return "sort-icon";
      //   break;
      //default:
      //   ASSERT(false);
      //   return "sort";
      //}
   }


   list::EView list::_001GetView()
   {

      return m_eview;

   }


   void list::_001OnAfterSort()
   {
      data_set_DisplayToStrict();
   }

   bool list::_001IsEditing()
   {
      return false;
   }


   void list::_001OnVScroll(::message::message * pmessage)
   {

      pmessage->previous();

   }


   void list::_001OnHScroll(::message::message * pmessage)
   {
      //      __pointer(::message::scroll) pscroll(pmessage);

      pmessage->previous();

      m_iTopDisplayIndex = _001CalcDisplayTopIndex();

      index iLow = 0;

      for (m_iTopGroup = 0; m_iTopGroup < m_nGroupCount; m_iTopGroup++)
      {
         if (m_iTopDisplayIndex >= iLow && m_iTopDisplayIndex < (iLow + _001GetGroupItemCount(m_iTopGroup)))
            break;
      }

      m_nDisplayCount = _001CalcDisplayItemCount();

      HeaderCtrlLayout();

      CacheHint();

   }


   id list::data_get_current_list_layout_id()
   {

      return "list";

   }


   bool list::query_drop(index iDisplayDrop, index iDisplayDrag)
   {

      if (iDisplayDrag < 0)
      {

         return false;

      }

      if (iDisplayDrop < 0)
      {

         return false;

      }

      if (iDisplayDrag != iDisplayDrop)
      {

         if (m_eview == impact_icon)
         {

            return _001DisplayToStrict(iDisplayDrag) != -1;

         }
         else
         {

            if (_001DisplayToStrict(iDisplayDrop) == -1 || _001DisplayToStrict(iDisplayDrop) >= m_nItemCount)
            {

               return true;

            }

         }

      }

      return false;

   }


   bool list::do_drop(index iDisplayDrop, index iDisplayDrag)
   {

      if (m_eview == impact_icon)
      {

         if (m_rangeSelection.get_item_count() > 0)
         {

            ::rectangle_i32 rectClient;

            get_client_rect(&rectClient);

            index iIconSize = maximum(32, m_columna[0]->m_sizeIcon.cy);

            index iItemSize = iIconSize * 2;

            int iItemColumnCount = (int)maximum(1, rectClient.width() / iItemSize);

            index iCol1 = iDisplayDrag % iItemColumnCount;

            index iRow1 = iDisplayDrag / iItemColumnCount;

            index iCol2 = iDisplayDrop % iItemColumnCount;

            index iRow2 = iDisplayDrop / iItemColumnCount;

            index iColOffset = iCol2 - iCol1;

            index iRowOffset = iRow2 - iRow1;

            index_array iaDrop;

            index_array iaDrag;

            range rangeNew;

            for (index i = 0; i < m_rangeSelection.get_item_count(); i++)
            {

               auto & itemrange = m_rangeSelection.ItemAt(i);

               for (index iItem = itemrange.m_iLowerBound; iItem <= itemrange.m_iUpperBound; iItem++)
               {

                  index iStrict = _001DisplayToStrict(iItem);

                  if(iStrict >= 0)
                  {

                     index iCol = (iItem + iColOffset) % iItemColumnCount;

                     index iRow = (iItem + iColOffset) / iItemColumnCount + iRowOffset;

                     index iDrop = iRow * iItemColumnCount + iCol;

                     iaDrop.add(iDrop);

                     iaDrag.add(iItem);

                     item_range itemrange;

                     itemrange.set_lower_bound(iDrop);

                     itemrange.set_upper_bound(iDrop);

                     rangeNew.add_item(itemrange);

                  }

               }

            }

            m_rangeSelection = rangeNew;

            array_translate_a_array(m_piconlayout->m_iaDisplayToStrict, iaDrop, iaDrag);

         }
         else
         {

            array_translate_a(m_piconlayout->m_iaDisplayToStrict, iDisplayDrop, iDisplayDrag);

         }


      }
      else
      {

         m_pmeshlayout->m_iaDisplayToStrict.__swap(iDisplayDrag,iDisplayDrop);

      }

      _001OnAfterSort();

      return true;

   }


   bool list::defer_drop(index iDisplayDrop, index iDisplayDrag)
   {

      if (!query_drop(iDisplayDrop, iDisplayDrag))
      {

         return false;

      }

      return do_drop(iDisplayDrop, iDisplayDrag);

   }


   //list::list_layout::list_layout()
   //{
   //}

   //list::list_layout::~list_layout()
   //{
   //}

   //void list::list_layout::write(stream & ostream) const
   //{
   //   //ostream << m_iaDisplayToStrict;
   //   ostream << m_iWidth;
   //}

   //void list::list_layout::read(stream & istream)
   //{
   //   //istream >> m_iaDisplayToStrict;
   //   istream >> m_iWidth;
   //}

   //list::icon_layout::icon_layout()
   //{
   //}

   //list::icon_layout::~icon_layout()
   //{
   //}

   //void list::icon_layout::write(stream & ostream) const
   //{
   //   ostream << m_iaDisplayToStrict;
   //   ostream << m_iWidth;
   //}

   //void list::icon_layout::read(stream & istream)
   //{
   //   istream >> m_iaDisplayToStrict;
   //   istream >> m_iWidth;
   //}


   ::size_i32 list::get_item_size()
   {

      if (m_eview == impact_icon)
      {

         if (m_columna.get_count() == 0)
         {

            return ::size_i32(32, 32);

         }

         index iIconSize = maximum(32, m_columna[0]->m_sizeIcon.cy);

         index iItemSize = iIconSize * 2;

         return ::size_i32((i32) iItemSize, (i32) iItemSize);

      }
      else
      {

         // not implemented

         ASSERT(false);

         return nullptr;

      }

   }


   void list::auto_arrange(bool bAutoArrange)
   {
      if (bAutoArrange)
      {
         m_flags.add(flag_auto_arrange);
      }
      else
      {
         m_flags.erase(flag_auto_arrange);
      }
      if (bAutoArrange)
      {
         index iMaxStrict = m_piconlayout->m_iaDisplayToStrict.get_max_b();
         for (index iStrict = 0; iStrict <= iMaxStrict; iStrict++)
         {
            m_piconlayout->m_iaDisplayToStrict.set(iStrict, iStrict);
         }

         set_need_redraw();

      }

   }


   bool list::get_auto_arrange()
   {
      return m_flags.has(flag_auto_arrange);
   }

   void list::_001OnListViewAutoArrange(::message::message * pmessage)
   {
      UNREFERENCED_PARAMETER(pmessage);
      auto_arrange(!get_auto_arrange());
   }

   void list::_001OnUpdateListViewAutoArrange(::message::message * pmessage)
   {
      __pointer(::message::command) pcommand(pmessage);
      pcommand->_001SetCheck(get_auto_arrange());
      pcommand->enable();
   }

   bool list::is_valid_display_item(index iDisplayItem)
   {
      if (iDisplayItem < 0)
         return false;
      if (iDisplayItem >= m_nItemCount)
         return false;
      return true;
   }

   bool list::is_valid_strict_item(index iStrictItem)
   {
      if (iStrictItem < 0)
         return false;
      if (iStrictItem >= m_nItemCount)
         return false;
      return true;

   }


   bool list::keyboard_focus_is_focusable() const
   {

      return true;

   }


   void list::_001OnSelectionChange()
   {

      ::user::control_event ev;

      ev.m_puie = this;
      ev.m_eevent = ::user::e_event_after_change_cur_sel;

      on_control_event(&ev);

      set_need_redraw();

   }


   void list::set_current_item(const ::user::item & item, const ::action_context & context)
   {

      m_rangeSelection.clear();

      if (!item.is_set())
      {

         return;

      }

      item_range itemrange;

      itemrange.set_lower_bound(item);

      itemrange.set_upper_bound(item);

      m_rangeSelection.add_item(itemrange);

      _001OnSelectionChange();

   }


   void list::set_current_item(const index_array & iaSel, const ::action_context & context)
   {

      m_rangeSelection.clear();

      for (index i = 0; i < iaSel.get_count(); i++)
      {

         item_range itemrange;
         itemrange.set_lower_bound(iaSel[i]);
         itemrange.set_upper_bound(iaSel[i]);
         m_rangeSelection.add_item(itemrange);
      }
      _001OnSelectionChange();
   }


   item list::current_item()
   {
      if (m_rangeSelection.get_item_count() != 1)
         return -1;
      if (m_rangeSelection.ItemAt(0).get_lower_bound() == m_rangeSelection.ItemAt(0).get_upper_bound() && m_rangeSelection.ItemAt(0).get_lower_bound() >= 0)
         return m_rangeSelection.ItemAt(0).get_lower_bound();
      return -1;
   }


   void list::get_cur_sel(index_array & iaSel)
   {

      for (index i = 0; i < m_rangeSelection.get_item_count(); i++)
      {

         for (index iItem = m_rangeSelection.ItemAt(i).get_lower_bound(); iItem <= m_rangeSelection.ItemAt(i).get_upper_bound(); iItem++)
         {

            iaSel.add_unique(iItem);

         }

      }

   }


   ::count list::_001GetGroupItemCount(index iGroup)
   {
      UNREFERENCED_PARAMETER(iGroup);
      return -1;
   }


   i32 list::_001GetGroupHeight(index iGroup)
   {

      i32 iListHeight = (i32)(_001GetGroupItemCount(iGroup) * m_dItemHeight);

      return maximum(m_iGroupMinHeight, iListHeight);

   }


   list_item::list_item(list * plist) :
      mesh_item(plist)
   {
      m_plistitem = this;
      m_plist = plist;
      m_iGroup = -1;
      m_iItem = -1;
      m_iDisplayItem = -1;
      m_iColumn = -1;
      //m_iColumnKey = -1;
      m_iOrder = -1;
      m_iSubItem = -1;
      m_iListItem = -1;
      m_colorText = __indexed_color(-1);
      m_colorTextBackground = argb(255, 0, 0, 0);
      m_colorItemBackground = 0;
      m_iState = -1;
      m_iImage = -1;
      m_bOk = false;

      m_iGroupTopDisplayIndex = -1;
      m_iGroupCount = -1;

   }

   draw_list_item::draw_list_item(list * plist) :
      list_item(plist),
      mesh_item(plist),
      draw_mesh_item(plist)
   {

      m_prectClient = nullptr;

      m_iColumn = -1;
      m_iColumnWidth = 0;
      m_pcolumn = nullptr;

      m_iItemRectItem = -1;

      m_iSubItemRectItem = -1;
      m_iSubItemRectSubItem = -1;
      m_iSubItemRectOrder = -1;
      m_iSubItemRectColumn = -1;
      m_pcolumn = nullptr;

      m_iListItemRectItem = -1;
      m_iListItemRectSubItem = -1;
      m_iListItemRectListItem = -1;

   }


   __pointer(::image_list) draw_list_item::get_image_list()
   {

      if (m_bListItemHover && m_pcolumn->m_pilHover != nullptr)
      {

         return m_pcolumn->m_pilHover;

      }
      else
      {

         return m_pcolumn->m_pil;

      }

   }


   bool draw_list_item::draw_image()
   {
      if (m_pcolumn->m_bIcon)
      {
         draw2d::icon * picon;
         if (m_pcolumn->m_mapIcon.lookup((i32)m_iImage, picon))
         {
            m_pgraphics->set_alpha_mode(::draw2d::alpha_mode_blend);
            return m_pgraphics->draw(m_rectImage, picon) != false;
         }
      }
      else
      {

         synchronous_lock synchronouslock(get_image_list()->mutex());

         if(get_image_list()->m_pimage->is_null()
               || get_image_list()->m_pimage->area() <= 0)
         {

            return false;

         }

         if ((m_plist->m_iIconBlur > 0 && m_plist->m_iIconBlurRadius > 0)
               || (m_plist->m_dIconSaturation < 1.0)
            || (m_plist->m_dIconLightness < 1.0)
            || (m_plist->m_dIconOpacity < 1.0))
         {

            auto & pimage = m_plist->m_mapIconBlur[m_iImage];

            __defer_construct(pimage);

            int iRate = 3;

            if (pimage.nok() && m_iImage >= 0 && m_iImage < get_image_list()->get_image_count())
            {

               if (m_plist->m_iIconBlur > 0 && m_plist->m_iIconBlurRadius > 0)
               {


                  pimage->create(m_rectImage.size() +size_i32(m_plist->m_iIconBlurRadius * iRate * 2, m_plist->m_iIconBlurRadius * iRate * 2));
                  //m_plist->m_blurIcon.initialize(m_rectImage.size() , m_plist.m_iIconBlurRadius);

               }
               else
               {

                  pimage->create(m_rectImage.size());

               }

               pimage->get_graphics()->set_alpha_mode(::draw2d::alpha_mode_set);

               pimage->get_graphics()->fill_rectangle(pimage->size(), 0);

               get_image_list()->draw(pimage->g(), (i32)m_iImage,
                                      point_i32(m_plist->m_iIconBlurRadius*iRate, m_plist->m_iIconBlurRadius *iRate), m_rectImage.size(), ::point_i32(), 0);

               if (m_plist->m_dIconSaturation < 1.0)
               {

                  pimage->saturation(m_plist->m_dIconSaturation);

               }

               if (m_plist->m_dIconLightness < 1.0)
               {

                  pimage->lightness(m_plist->m_dIconLightness);

               }


               if (m_plist->m_dIconOpacity < 1.0)
               {

                  pimage->opacity(m_plist->m_dIconOpacity);

               }


               //pimage->g()->fill_rectangle(::rectangle_i32(pimage->size()), argb(255, 200, 220, 255));
               if (m_plist->m_iIconBlur > 0 && m_plist->m_iIconBlurRadius > 0)
               {

                  for (index i = 0; i < m_plist->m_iIconBlur; i++)
                  {

                     m_plist->m_blurIcon.blur(pimage, m_plist->m_iIconBlurRadius);

                  }

               }


            }

            m_pgraphics->set_alpha_mode(::draw2d::alpha_mode_blend);

            ::rectangle_i32 rectDib(m_rectImage.top_left() - size_i32(m_plist->m_iIconBlurRadius *iRate, m_plist->m_iIconBlurRadius * iRate),
                      m_rectImage.size() + size_i32(m_plist->m_iIconBlurRadius *iRate * 2, m_plist->m_iIconBlurRadius * iRate * 2));

            m_pgraphics->draw(rectDib, pimage->get_graphics());

            ::rectangle_i32 rectI;

            if (m_plist->m_pimageSpot->is_set() && m_plist->m_pimageSpot->area() > 0 && rectI.intersect(m_rectImage, m_plist->m_rectSpot)
                  && m_iImage >= 0 && m_iImage < get_image_list()->get_image_count()   )
            {
               ///return true;

               m_plist->m_pimageTime = create_image(m_plist->m_pimageSpot->size());

               ::rectangle_i32 rectangle = rectI;

               rectangle.offset(-m_rectImage.top_left());

               //m_plist->m_pimageTime->get_graphics()->set_alpha_mode(::draw2d::alpha_mode_set);

               //m_plist->m_pimageTime->get_graphics()->fill_rectangle(r, 0);

               ::rectangle_i32 rect2 = rectI;

               rect2.offset(-m_plist->m_rectSpot.top_left());

               m_plist->m_pimageTime->get_graphics()->set_alpha_mode(::draw2d::alpha_mode_set);

               get_image_list()->draw(m_plist->m_pimageTime->get_graphics(), (i32)m_iImage,
                                      rect2.top_left(),
                                      rectangle.size(), rectangle.top_left(), 0);

               //m_pgraphics->draw(rectI + point_i32(200,200), m_plist->m_pimageTime->get_graphics(), rect2.top_left());

               //m_plist->m_pimageTime->div_alpha(rect2->top_left(), rect2->size());

               m_plist->m_pimageTime->channel_multiply(::color::e_channel_alpha, m_plist->m_pimageSpot, rect2);

               //m_plist->m_pimageTime->mult_alpha(rect2->top_left(), rect2->size());

               m_pgraphics->set_alpha_mode(::draw2d::alpha_mode_blend);

               m_pgraphics->draw(rectI, m_plist->m_pimageTime->get_graphics(),rect2.top_left());

            }

            return true;

         }
         //if(m_plist->m_bMorePlain)
         //{

         //   m_pgraphics->set_alpha_mode(::draw2d::alpha_mode_set);
         //   return m_pgraphics->BitBlt(m_rectImage.left, m_rectImage.top, m_rectImage.width(), m_rectImage.height(),get_image_list()->m_pimage->g(), m_iImage * m_rectImage->width());

         //}
         else
         {
            m_pgraphics->set_alpha_mode(::draw2d::alpha_mode_blend);
            return get_image_list()->draw(m_pgraphics, (i32)m_iImage, m_rectImage.top_left(), m_rectImage.size(), ::point_i32(), 0);
         }
      }
      return false;
   }


   bool draw_list_item::draw_group_image()
   {
      return m_plist->m_pilGroup->draw(m_pgraphics, (i32)m_iImage, m_rectImage.top_left(), m_rectImage.size(), ::point_i32(), 0);
   }


   void draw_list_item::update_item_color()
   {

      m_plist->_001GetItemColor(this);

      auto estate = get_user_state();

      auto pstyle = m_plist->get_style(m_pgraphics);

      m_colorText = m_plist->get_color(pstyle, ::user::e_element_item_text, estate);

      m_colorItemBackground = m_plist->get_color(pstyle, ::user::e_element_item_background, estate);

   }


   void draw_list_item::set_text_color()
   {

      ::draw2d::brush_pointer brushText(e_create);

      if (!m_plist->m_bHighHighLight)
      {

         ::color::color color;

         color.set_COLORREF(m_colorText);

         color.alpha = color.alpha / 3;

         brushText->create_solid(color);

      }
      else
      {

         brushText->create_solid(m_colorText);

      }

      m_pgraphics->set(brushText);

   }


   void draw_list_item::draw_text()
   {

      if (m_bOk)
      {

         if (m_plist->m_eview == list::impact_icon && m_plist->m_bEmboss && ((m_plist->m_iTextBlurRadius > 0 && m_plist->m_iTextBlur > 0) || m_plist->m_iTextSpreadRadius > 0))
         {

            if (m_strText.has_char())
            {

               ::image_pointer & pimage2 = m_plist->m_mapBlur[m_iItem];

               __defer_construct(pimage2);

               auto psystem = m_psystem->m_paurasystem;

               auto pdraw2d = psystem->draw2d();

               if (pdraw2d->embossed_text_out(
                     m_pgraphics,
                     m_rectText,
                     m_strText,
                     m_plist->m_blur,
                     pimage2,
                     m_pgraphics->m_pfont,
                     m_ealign,
                     m_edrawtext,
                     m_colorText,
                     m_colorTextBackground,
                     m_plist->m_iTextSpreadRadius, m_plist->m_iTextBlurRadius,
                     m_plist->m_iTextBlur,
                     m_strText != m_plist->m_mapText[m_iItem] || m_colorTextBackground != m_plist->m_mapBackColor[m_iItem]))
               {

                  m_plist->m_mapText[m_iItem] = m_strText;

                  m_plist->m_mapBackColor[m_iItem] = m_colorTextBackground;

               }

            }

         }
         else
         {

            //::draw2d::brush_pointer brushText(e_create);

            update_item_color();

            //brushText->create_solid(m_colorText);

            //m_pgraphics->set(brushText);

            m_pgraphics->set_text_rendering_hint(::write_text::e_rendering_anti_alias);

            auto pstyle = m_plist->get_style(m_pgraphics);

            auto ealign = (::enum_align) m_plist->get_int(pstyle, e_int_list_item_text_align);

            auto edrawtext = (::enum_draw_text) m_plist->get_int(pstyle, e_int_list_item_draw_text_flags);

            set_text_color();

            m_pgraphics->draw_text(m_strText, m_rectText, ealign, edrawtext);

            //m_pgraphics->fill_rectangle(m_rectText.left, m_rectText.top, 100, 100, argb(128, 100, 125, 255));

            if (m_strText == "LOVE OR NOTHING")
            {

               output_debug_string("LOVE OR NOTHING");

            }

         }

      }

   }


   ::count list::_001GetGroupMetaItemCount(index iGroup)
   {
      if (m_pmeshdata != nullptr)
      {
         return m_pmeshdata->_001GetGroupMetaItemCount(iGroup);
      }
      return 0;
   }


   void list::_001OnBeforeDeleteRange(range & range)
   {

   }


   void list::_001OnDeleteRange(range & range)
   {

      if (m_pmeshdata != nullptr)
      {

         m_pmeshdata->_001OnDeleteRange(range);

      }

   }


   void list::_001DeleteRange(range & range)
   {

      _001OnBeforeDeleteRange(range);

      _001OnDeleteRange(range);

   }


   void list::defer_create_mesh_data()
   {

      __pointer(::user::list_data) plistdata = create_mesh_data();

      if (plistdata.is_null())
      {

         return;

      }

      auto estatus = plistdata->initialize(this);

      if (!estatus)
      {

         return;

      }

      SetDataInterface(plistdata);

   }


   void list::on_create_draw_item()
   {

      m_pdrawlistitem = new draw_list_item(this);

      m_pdrawmeshitem = m_pdrawlistitem;

   }


   void list::on_viewport_offset(::draw2d::graphics_pointer & pgraphics)
   {

   }


   void list::_001OnClip(::draw2d::graphics_pointer & pgraphics)
   {

      mesh::_001OnClip(pgraphics);

      return;
//      if (m_bHeaderCtrl && m_plistheader != nullptr)
//      {
//
//         try
//         {
//
//            ::rectangle_i32 rectClient;
//
//            get_client_rect(rectClient);
//
//            ::rectangle_i32 rectClientHeader;
//
//            m_plistheader->get_client_rect(rectClientHeader);
//
//            m_plistheader->_001ClientToScreen(rectClientHeader);
//
//            _001ScreenToClient(rectClientHeader);
//
//            rectClient.top = rectClientHeader.bottom;
//
//            pgraphics->IntersectClipRect(rectClient);
//
//         }
//         catch (...)
//         {
//
//            TRACE("Exception : ::list::_001OnClip");
//
//         }
//
//      }

   }


   ::e_align list::get_draw_text_align(EView eview)
   {

      return m_pdrawmeshitem->m_ealign;

   }


   ::e_draw_text list::get_draw_text_flags(EView eview)
   {

      return m_pdrawmeshitem->m_edrawtext;

   }


   //::index list::item_index(::user::interaction * pinteractionControl)
   //{

   //   m_

   //}


   ::index list::subitem_index(::user::interaction * pinteractionControl)
   {

      auto pcolumn = m_columna.get_by_control(pinteractionControl);

      if (!pcolumn)
      {

         return -1;

      }

      return pcolumn->m_iSubItem;

   }


   //::index list::list_item_index(::user::interaction * pinteractionControl)
   //{


   //}


   ::index list::column_index(::user::interaction * pinteractionControl) 
   {

      auto pcolumn = m_columna.get_by_control(pinteractionControl);

      if (!pcolumn)
      {

         return -1;

      }

      return pcolumn->m_iColumn;

   }


   //bool list::get_client_rect(RECTANGLE_I32 * prectangle)

   //{

      //mesh::get_client_rect(prectangle);


    //  if (m_bHeaderCtrl && m_plistheader != nullptr)
      //{

      //   ::rectangle_i32 rectClient;

      //   m_plistheader->get_client_rect(rectClient);

      //   m_plistheader->_001ClientToScreen(rectClient);

      //   _001ScreenToClient(rectClient);

      //   prectangle->top += rectClient.bottom;


      //}

//      return true;

  // }




   void list::update_icon_list_view_sort()
   {

      if (m_eview != impact_icon)
      {

         return;

      }

      synchronous_lock synchronouslock(mutex());

      string strSort(m_pmeshdata ? m_pmeshdata->m_strMeshSort.c_str() : "");

      if (strSort.has_char())
      {

         defer_update_display();

         strSort += "-" + get_display_tag() + ".icon_list_view_sort";

         auto pcontext = get_context();

         string str = pcontext->m_papexcontext->file().as_string(strSort);
         string_array stra;
         stra.add_lines(str);
         for (index a = 0; a < stra.get_size(); a++)
         {
            index b = _001GetItemById(stra[a]);
            if (b >= 0 && b < m_nItemCount)
            {
               m_piconlayout->m_iaDisplayToStrict.set(a, b);
            }
         }

      }


      for (index b = 0; b < m_nItemCount; b++)
      {

         if (m_piconlayout->m_iaDisplayToStrict.get_a(b) == -1)
         {

            m_piconlayout->m_iaDisplayToStrict.set(m_piconlayout->m_iaDisplayToStrict.get_free_a(), b);

         }

      }

   }





} // namespace user



