#include "framework.h"
#include "list.h"
#include "list_column.h"
#include "list_column_array.h"
#include "list_header.h"
#include "list_item.h"
#include "list_data.h"
#include "mesh_cache_interface.h"
#include "acme/handler/item.h"
#include "apex/filesystem/filesystem/file_context.h"
#include "apex/database/selection.h"
#include "aura/graphics/draw2d/brush.h"
#include "aura/graphics/draw2d/graphics_extension.h"
#include "aura/graphics/draw2d/draw2d.h"
#include "acme/platform/timer.h"
#include "acme/constant/timer.h"
#include "acme/primitive/collection/sort.h"
#include "aura/graphics/draw2d/pen.h"
#include "aura/graphics/image/list.h"
#include "aura/user/user/scroll_data.h"
#include "core/user/simple/list_data.h"
#include "core/platform/session.h"
#include "axis/platform/system.h"
#include "aura/message/user.h"
#include "base/user/user/user.h"
#include "aura/user/user/scroll_bar.h"


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

      m_bHeaderCtrl = true;
      m_bSingleColumnMode = false;

      //m_pdrawlistitem = nullptr;


      m_bAutoCreateListHeader = true;


      m_bMorePlain = false;

      m_bSelect = true;

   }


   list::~list()
   {

      //::acme::del(m_pdrawlistitem);

   }


   void list::install_message_routing(::channel * pchannel)
   {

      ::user::mesh::install_message_routing(pchannel);

      MESSAGE_LINK(e_message_size, pchannel, this, &list::on_message_size);
      MESSAGE_LINK(e_message_vscroll, pchannel, this, &list::_001OnVScroll);
      MESSAGE_LINK(e_message_hscroll, pchannel, this, &list::_001OnHScroll);
      MESSAGE_LINK(e_message_mouse_leave, pchannel, this, &list::on_message_mouse_leave);

      MESSAGE_LINK(e_message_left_button_down, pchannel, this, &list::on_message_left_button_down);
      MESSAGE_LINK(e_message_left_button_up, pchannel, this, &list::on_message_left_button_up);
      MESSAGE_LINK(e_message_left_button_double_click, pchannel, this, &list::on_message_left_button_double_click);
      MESSAGE_LINK(e_message_right_button_down, pchannel, this, &list::on_message_right_button_down);

      MESSAGE_LINK(e_message_mouse_move, pchannel, this, &list::on_message_mouse_move);

      MESSAGE_LINK(e_message_key_down, pchannel, this, &list::on_message_key_down);

      MESSAGE_LINK(e_message_create, pchannel, this, &list::on_message_create);
      //      //MESSAGE_LINK(e_message_timer,           pchannel, this, &list::_001OnTimer);
      add_command_handler("list_impact_auto_arrange", this, &list::_001OnListImpactAutoArrange);
      add_command_prober("list_impact_auto_arrange", this, &list::_001OnUpdateListImpactAutoArrange);

   }


   bool list::CreateHeaderCtrl()
   {
      if (m_plistheader != nullptr)
      {
         if (!m_plistheader->is_window())
         {
            //bool bOk = 
            m_plistheader->create_child(this);
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
            //   m_plistheader->m_pfont = m_pfont;
            //}
            return true;
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

      //throw ::exception(todo("scroll"));
      //defer_draw_scroll_gap(pgraphics);

   }


   void list::_001OnDraw(::draw2d::graphics_pointer & pgraphics)
   {

      m_ppenFocused->create_solid(2, argb(255, 0, 255, 255));

      if (m_bHighHighLight)
      {

         m_ppenHighlight->create_solid(2, argb(255, 0, 255, 255));

      }
      else
      {

         m_ppenHighlight->create_solid(2, argb(60, 0, 130, 130));

      }

      pgraphics->set_text_rendering_hint(::write_text::e_rendering_anti_alias_grid_fit);

      if (m_bLockImpactUpdate)
      {

         return;

      }

      ::user::interaction::_001OnDraw(pgraphics);

      if (is_null(m_pmeshdata.m_p))
      {

         return;

      }

      synchronous_lock synchronouslock(m_pmeshdata->mutex());

      ::rectangle_i32 rectangleClient = get_client_rect();

      auto pointOffset = get_context_offset();

      pgraphics->set_alpha_mode(::draw2d::e_alpha_mode_blend);

      if (m_bTopText)
      {

         auto pbrushText = __create < ::draw2d::brush > ();

         auto pstyle = get_style(pgraphics);

         pbrushText->create_solid(get_color(pstyle,::e_element_text));

         auto pointContextOrg = pgraphics->get_origin();

         pgraphics->set(pbrushText);

         ::size_array sizea;

         m_pdcextension->get_text_extent(pgraphics, m_strTopText, sizea);

         index x = 0;

         index right = (index)rectangleClient.right;

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
               rectangle.right = rectangleClient.right;
               rectangle.bottom = ::i32(y - pointOffset.y);

               pgraphics->_DrawText(m_strTopText.Mid(iStart, i - iStart), rectangle, e_align_left);
               iStart = iNewStart;
            }
         }

         pgraphics->set_origin(pointContextOrg);

      }

      //if (m_pdrawlistitem == nullptr)
      //{

      //   return;

      //}


      ::rectangle_i32 rectangleItem;
      ::rectangle_i32 rectangleIntersect;

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

      {

         pointer_array < synchronous_lock > slaImageList;

         for (auto & pcolumn : *m_pcolumna)
         {

            if (pcolumn)
            {

               if (pcolumn->m_pimagelist)
               {

                  slaImageList.add(__new(synchronous_lock(pcolumn->m_pimagelist)));

               }
               if (pcolumn->m_pimagelistHover)
               {

                  slaImageList.add(__new(synchronous_lock(pcolumn->m_pimagelist)));

               }

            }

         }

         _001DrawItems(pgraphics, (::index)iItemFirst, (::index)iItemLast);

      }

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

         //_001DrawGroups(m_pdrawlistitem, (::index) iGroupFirst, (::index) iGroupLast, (::index) iItemFirst, (::index) iItemLast);
         //_001DrawGroups(pgraphics, (::index)iGroupFirst, (::index)iGroupLast, (::index)iItemFirst, (::index)iItemLast);
         _001DrawGroups(pgraphics, (::index)iGroupFirst, (::index)iGroupLast);

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

            pgraphics->set_alpha_mode(::draw2d::e_alpha_mode_blend);
            
            pgraphics->fill_rectangle(::rectangle_f64(x1, y1, x2, y2), argb(90, 250, 250, 255));

            pgraphics->draw_inset_rectangle(::rectangle_f64(x1, y1, x2, y2), argb(192, 192, 192, 208));

         }

      }

   }



















   //void list::_001DrawGroups(draw_list_item * pdrawitem, index iGroupFirst, index iGroupLast, index iItemFirst, index iItemLast)
      void list::_001DrawGroups(::draw2d::graphics_pointer & pgraphics, index iGroupFirst, index iGroupLast)
   {

      //__UNREFERENCED_PARAMETER(iItemFirst);
      //__UNREFERENCED_PARAMETER(iItemLast);

      index iGroup;

      ::rectangle_i32 rectangleClient;

      ::rectangle_i32 rectangleIntersect;

      get_client_rect(rectangleClient);

      bool bHoverFont = false;

      for (iGroup = iGroupFirst; iGroup <= iGroupLast; iGroup++)
      {

         auto & pgroup = m_mapGroup[iGroup];

         if (!pgroup)
         {

            auto pdrawgroup = __new(draw_list_group);

            pdrawgroup->initialize_draw_list_group(this);

            pdrawgroup->m_iGroup = iGroup;

            pgroup = pdrawgroup;

         }

         pgroup->m_pdrawlistgroup->m_pgraphics = pgraphics;

         pgroup->m_pdrawlistgroup->m_pgraphics->set_font(this, ::e_element_none);
         //pdrawitem->m_pgraphics->set(pfont);

         pgroup->m_pdrawlistgroup->m_pfont = pgroup->m_pdrawlistgroup->m_pgraphics->m_pfont;

         _001GetGroupRect(*pgroup);

         if (!pgroup->m_bOk)
            continue;

         if (!rectangleIntersect.intersect(pgroup->m_pdrawlistgroup->m_rectangleGroup, rectangleClient))
            continue;

         if (iGroup == m_iGroupHover)
         {

            if (!bHoverFont)
            {

               pgroup->m_pdrawlistgroup->m_pgraphics->set_font(this, ::e_element_none, e_state_hover);

            }

         }
         else
         {

            if (bHoverFont)
            {

               pgroup->m_pdrawlistgroup->m_pgraphics->set_font(this, ::e_element_none);

            }

         }

         _001DrawGroup(pgraphics, *pgroup);

      }

   }


   void list::_001DrawGroup(::draw2d::graphics_pointer & pgraphics, draw_list_group * pdrawgroup)
   {

      /*if(m_bGroupCustomDraw)
      {
         pdrawitem->m_bListSubItemHover = pdrawitem->m_bListItemHover && (pdrawitem->m_iSubItem == m_iSubItemHover);
         pdrawitem->m_bFocus = false;
         return;
      }*/

      _001GetGroupElementRect(pdrawgroup, ::user::list::e_group_element_image);

      if (pdrawgroup->m_bOk)
      {

         pdrawgroup->draw_group_image(pgraphics);

      }

      ::count nItem = _001GetGroupMetaItemCount(pdrawgroup->m_iGroup);

      for (pdrawgroup->m_iItem = 0; pdrawgroup->m_iItem < nItem; pdrawgroup->m_iItem++)
      {

         _001GetGroupElementRect(pdrawgroup, ::user::list::e_group_element_item_text);

         if (pdrawgroup->m_bOk)
         {

            _001GetGroupItemText(pdrawgroup);

            pdrawgroup->draw_text();

         }

      }

   }


   void list::_001DrawItems(::draw2d::graphics_pointer & pgraphics, index iItemFirst, index iItemLast)
   {

      ::rectangle_i32 rectangleClient;

      get_client_rect(rectangleClient);

      ::rectangle_i32 rectangleIntersect;

      rectangleClient.offset(get_context_offset());

      bool bHoverFont = false;

      index iDisplayItem;

      ::index iDisplayIndex = 0;

      for (iDisplayItem = iItemFirst; iDisplayItem <= iItemLast; iDisplayItem++, iDisplayIndex++)
      {

         auto iItem = _001DisplayToStrict(iDisplayItem);

         auto & pitem = get_item(iItem);

         pitem->m_pdrawlistitem->m_pgraphics = pgraphics;

         pitem->m_pdrawlistitem->m_pgraphics->set_font(this, ::e_element_none);

         pitem->m_pdrawlistitem->m_pfont = pitem->m_pdrawlistitem->m_pgraphics->m_pfont;

         pitem->m_iDisplayItem = iDisplayItem;

         //if (m_bGroup)
         //{

         //   pdrawlistitem->m_iGroupTopDisplayIndex = 0;

         //   for (pdrawlistitem->m_iGroup = 0; pdrawlistitem->m_iGroup < m_nGroupCount; pdrawlistitem->m_iGroup++)
         //   {

         //      pdrawlistitem->m_iGroupCount = _001GetGroupItemCount(pdrawlistitem->m_iGroup);

         //      if (iDisplayItem >= pdrawlistitem->m_iGroupTopDisplayIndex
         //            && iDisplayItem < (pdrawlistitem->m_iGroupTopDisplayIndex + pdrawlistitem->m_iGroupCount))
         //      {

         //         break;

         //      }

         //   }

         //}

         index_item_rectangle(*pitem);

         if (!pitem->m_bOk)
         {

            continue;

         }

         if (!rectangleIntersect.intersect(pitem->m_pdrawlistitem->m_rectangleItem, rectangleClient))
         {

            continue;

         }

         if (iDisplayItem == m_iDisplayItemHover)
         {

            if (!bHoverFont)
            {

               bHoverFont = true;

               pitem->m_pdrawlistitem->m_pgraphics->set_font(this, ::e_element_none, ::user::e_state_hover);

            }

         }
         else
         {

            if (bHoverFont)
            {

               bHoverFont = false;

               pitem->m_pdrawlistitem->m_pgraphics->set_font(this, ::e_element_none);

            }

         }

         {

#ifdef _DEBUG

            auto tickStart = ::duration::now();

#endif

            _001DrawItem(pgraphics, *pitem);

#ifdef _DEBUG

            auto tickEnd = ::duration::now();

            auto tickElapsed = tickEnd - tickStart;

            if (tickElapsed > 100_ms)
            {

               INFORMATION("drawing took " << tickElapsed.integral_millisecond() << "!!");
               INFORMATION("drawing took more than 100ms to complete!!");
               INFORMATION("");

               // let's try to reproduce the offending scenario
               //_001DrawItem(m_pdrawlistitem);

            }

#endif

         }

      }

   }


   void list::_001DrawItem(::draw2d::graphics_pointer & pgraphics, draw_list_item * pdrawitem)
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

         if (!pdrawitem->m_pmesh->m_plist->m_bMorePlain)
         {

            pdrawitem->m_pgraphics->set_alpha_mode(::draw2d::e_alpha_mode_blend);

            pdrawitem->m_pgraphics->draw_inset_rectangle(pdrawitem->m_rectangleItem, argb(80, 235, 235, 255));

            pdrawitem->m_pgraphics->fill_rectangle(pdrawitem->m_rectangleItem, argb(40, 255, 255, 255));

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

//      pdrawitem->m_colorText = get_color(pstyle, ::e_element_item_text);

  //    pdrawitem->m_colorTextBackground = ::color::transparent;

      pdrawitem->m_colorItemBackground = ::color::transparent;

      pdrawitem->update_item_color(pgraphics);

      if (pdrawitem->m_bListItemSelected)
      {

         auto psession = get_session();

         if (pdrawitem->m_pmesh->m_plist->m_bMorePlain)
         {

         }
         else if (psession->m_paurasession->savings().is_trying_to_save(::e_resource_processing))
         {

            pdrawitem->m_pgraphics->fill_rectangle(pdrawitem->m_rectangleItem, argb(255, 96, 96, 96));

         }
         else
         {

            pdrawitem->m_pgraphics->fill_rectangle(pdrawitem->m_rectangleItem, pdrawitem->m_colorItemBackground);

         }

      }
      else if (pdrawitem->m_colorItemBackground.is_ok())
      {

         pdrawitem->m_pgraphics->fill_rectangle(pdrawitem->m_rectangleItem, pdrawitem->m_colorItemBackground);

      }
      string str;

      index iColumnCount;

      if (m_eview == impact_icon)
      {

         iColumnCount = 1;

      }
      else
      {

         iColumnCount = m_pcolumna->get_visible_count();

      }

      //pdrawitem->m_iSubItemRectOrder = -1;

      //pdrawitem->m_iSubItemRectSubItem = -1;

      //pdrawitem->m_iSubItemRectColumn = -1;

      for (index iVisible = 0; iVisible < iColumnCount; iVisible++)
      {

         auto iSubItem = _001MapOrderToSubItem(iVisible);

         auto psubitem = get_subitem(pdrawitem, iSubItem);

         psubitem->m_iOrder = _001MapColumnToOrder(psubitem->m_pcolumn->m_iColumn);

         if (psubitem->m_iOrder < 0)
         {

            continue;

         }

         _001GetSubItemRect(*psubitem);

         if (!psubitem->m_bOk)
         {

            continue;

         }

         _001DrawSubItem(pgraphics, *psubitem);

      }

      if (rangeHighlight.has_item(pdrawitem->m_iDisplayItem))
      {

         auto ppenHighlight = _001GetPenHighlight();

         ::rectangle_i32 rectangleHighlight(pdrawitem->m_rectangleItem);

         rectangleHighlight.inflate(8, 0, 8, -1);

         pdrawitem->m_pgraphics->set(ppenHighlight);

         pdrawitem->m_pgraphics->draw_rectangle(rectangleHighlight);

      }

      if (pdrawitem->m_bListItemSelected)
      {

         if (pdrawitem->m_pmesh->m_plist->m_bMorePlain)
         {

            auto color = get_color(pstyle, ::e_element_item_text);

            if (!color.is_ok())
            {

               color = argb(255, 96, 96, 96);

            }

            pdrawitem->m_pgraphics->set_alpha_mode(::draw2d::e_alpha_mode_blend);

            color.alpha = 90;

            pdrawitem->m_pgraphics->fill_rectangle(pdrawitem->m_rectangleItem, color);

         }

      }

   }


   void list::_001DrawSubItem(::draw2d::graphics_pointer & pgraphics, draw_list_subitem * pdrawlistsubitem)
   {

      if (pdrawlistsubitem->m_pcolumn->m_bCustomDraw)
      {

         //pdrawlistsubitem->m_bListSubItemHover = pdrawlistsubitem->m_bListItemHover && (pdrawlistsubitem->m_iSubItem == m_iSubItemHover);

         //pdrawlistsubitem->m_bFocus = false;

         return;

      }

      //if (pdrawlistsubitem->m_bListItemHover)
      //{

      //   pdrawlistsubitem->m_pgraphics->set_font(this, ::e_element_none, ::user::e_state_hover);

      //}
      //else
      //{

      //   pdrawlistsubitem->m_pgraphics->set_font(this, ::e_element_none);

      //}

      ////pdrawitem->m_iListItem = -1;

      pdrawlistsubitem->m_bOk = false;

      index_element_rectangle(pdrawlistsubitem, ::user::list::e_element_image);

      if (pdrawlistsubitem->m_bOk)
      {

         try
         {

            _001GetSubItemImage(pdrawlistsubitem);

         }
         catch (...)
         {

            pdrawlistsubitem->m_bOk = false;

         }

         pdrawlistsubitem->draw_image(pgraphics);

      }

      //pdrawlistsubitem->m_iListItem = -1;

      index_element_rectangle(pdrawlistsubitem, ::user::mesh::e_element_text);

      if (pdrawlistsubitem->m_bOk)
      {

         try
         {

            _001GetSubItemText(pdrawlistsubitem);

         }
         catch (...)
         {

            pdrawlistsubitem->m_bOk = false;

         }

         if (pdrawlistsubitem->m_bOk)
         {

            pdrawlistsubitem->draw_text(pgraphics);

         }

      }

   }


   ::count list::_001GetColumnCount()
   {

      return m_pcolumna->get_visible_count();

   }


   void list::on_message_size(::message::message * pmessage)
   {

      __UNREFERENCED_PARAMETER(pmessage);

   }


   void list::on_layout(::draw2d::graphics_pointer & pgraphics)
   {

      synchronous_lock synchronouslock(this->synchronization());

      //m_dItemHeight = m_sizeMaximumItem.cy + 1;

      _001CalculateItemHeight(pgraphics);

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

      //   m_puserstyle = papp->userstyle();

      //}

      if (m_bTopText)
      {

         _001LayoutTopText(pgraphics);

      }

      if (m_eview == impact_icon)
      {

         ::rectangle_i32 rectangleClient;

         get_client_rect(rectangleClient);

         index iIconSize;

         if (m_pcolumna->get_count() > 0)
         {

            iIconSize = maximum(32, (*m_pcolumna)[0]->m_sizeIcon.cy);

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

            iWidth = _001CalcSubItemWidth(pgraphics, i, 0);

            if (iWidth > iMaxWidth)
            {

               iMaxWidth = iWidth;

            }

         }

         m_iItemWidth = iMaxWidth;

         m_pcolumna->get_visible(0)->m_iWidth = iMaxWidth;

      }

      LayoutHeaderCtrl();

      on_change_impact_size(pgraphics);

      LayoutHeaderCtrl();

      update_icon_list_impact_sort();

   }


   bool list::_001OnUpdateItemCount(u32 dwFlags)
   {
      
      __UNREFERENCED_PARAMETER(dwFlags);

      auto pointOffset = get_context_offset();

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

         synchronous_lock synchronouslock(this->synchronization());

         m_nItemCount = nCount;

         if (m_bGroup)
         {
            m_nGroupCount = nGroupCount;
         }

         if (m_eview == impact_icon)
         {

            update_icon_list_impact_sort();

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

      cache_hint();

      set_need_layout();

      queue_graphics_call([this, pointOffset](::draw2d::graphics_pointer & pgraphics)
         {

            set_context_offset(pgraphics, pointOffset.x, pointOffset.y);

         });

      set_need_redraw();

      return true;

   }


   void list::on_change_impact_size(::draw2d::graphics_pointer & pgraphics)
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

            ::rectangle_i32 rectangleClient;

            get_client_rect(rectangleClient);

            auto pitem = get_item(0);

            //draw_list_item itemFirst(this);

            //itemFirst.m_iItem = 0;

            //itemFirst.m_iDisplayItem = 0;

            index_item_rectangle(*pitem);

            rectangle.top = rectangleClient.top;

            rectangle.bottom = rectangleClient.bottom;

            rectangle.left = rectangleClient.left;

            if (m_dItemHeight <= 0 || rectangleClient.height() <= 0)
            {

               rectangle.right = rectangleClient.right;

            }
            else
            {

               rectangle.right = (::i32)minimum(
                            rectangleClient.left +
                            m_nItemCount * pitem->m_pdrawlistitem->m_rectangleItem.width() * m_dItemHeight /
                            rectangleClient.height()
                            + pitem->m_pdrawlistitem->m_rectangleItem.width(), MAXI32);

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

            auto pitem = get_item(0);

            //draw_list_item itemFirst(this);

            //itemFirst.m_iItem = 0;

            //itemFirst.m_iDisplayItem = 0;

            index_item_rectangle(*pitem);

            rectangle = pitem->m_pdrawlistitem->m_rectangleItem;

            m_pscrolldataVertical->m_iLine = (::i32) m_dItemHeight;

            rectangle.top = 0;

            rectangle.bottom = (::i32) ((_001GetItemCount() + (m_bHeaderCtrl ? 1 : 0)) * m_dItemHeight);

         }

      }
      else if (m_eview == impact_icon)
      {

         rectangle = ::rectangle_i32(0, 0, 0, 0);

         auto pitemFirst = get_item(0);

         //draw_list_item itemFirst(this);

         //itemFirst.m_iItem = 0;

         //itemFirst.m_iDisplayItem = 0;

         index_item_rectangle(*pitemFirst);

         if (pitemFirst->m_bOk)
         {

            auto pitemLast = get_item(0);

            if (m_nItemCount <= 0)
            {

               pitemLast->m_iDisplayItem = 0;

               pitemLast->m_iItem = 0;

            }
            else
            {

               pitemLast->m_iDisplayItem = m_nItemCount - 1;

               pitemLast->m_iItem = m_nItemCount - 1;

            }

            index_item_rectangle(*pitemLast);

            if (pitemLast->m_bOk)
            {

               rectangle.unite(pitemFirst->m_pdrawlistitem->m_rectangleItem, pitemLast->m_pdrawlistitem->m_rectangleItem);

            }

         }

      }

      set_total_size(rectangle.size());

      ::user::scroll_base::on_change_impact_size(pgraphics);

   }


   void list::_001OnInitialize()
   {

   }


   ::pointer<mesh_item>& list::get_item(::index iItem)
   {

      auto & pitem = m_mapItem[iItem];

      if (!pitem)
      {

         auto pdrawlistitem = __new(draw_list_item);

         pdrawlistitem->initialize_draw_list_item(this);

         pdrawlistitem->m_iItem = iItem;

         //pdrawlistitem->m_iItemRectItem = -1;
         //pdrawlistitem->m_iSubItemRectOrder = -1;
         //pdrawlistitem->m_iSubItemRectSubItem = -1;
         //pdrawlistitem->m_iSubItemRectItem = -1;
         //pdrawlistitem->m_iSubItemRectColumn = -1;
         //pdrawlistitem->m_iColumn = -1;
         pdrawlistitem->m_iColumnWidth = 0;
         pdrawlistitem->m_ealign = get_draw_text_align(m_eview);
         pdrawlistitem->m_edrawtext = get_draw_text_flags(m_eview);

         pitem = pdrawlistitem;

      }

      return pitem;

   }


   ::pointer<mesh_subitem>& list::get_subitem(mesh_item * pitem, ::index iSubItem)
   {
      
      auto & psubitem = pitem->m_mapSubItem[iSubItem];

      if (!psubitem)
      {

         auto pdrawlistsubitem = __new(draw_list_subitem);

         pdrawlistsubitem->initialize_draw_list_subitem(*pitem);

         pdrawlistsubitem->m_pitem = pitem;

         pdrawlistsubitem->m_pcolumn = m_pcolumna->get_by_subitem(iSubItem);

         pdrawlistsubitem->m_iSubItem = iSubItem;

         psubitem = pdrawlistsubitem;

      }

      return psubitem;

   }


   ::pointer<list_column>list::new_list_column()
   {

      auto pcolumn = __new(list_column());

      m_pcolumna->add(pcolumn);

      pcolumn->m_iColumn = m_pcolumna->get_upper_bound();

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
   //   m_pimagelist = pcolumn->m_pimagelist;
   //   m_pimagelistHover = pcolumn->m_pimagelistHover;
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

      for (auto & pcolumn : m_pcolumna->ptra())
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

      auto iVisibleColumnCount = m_pcolumna->get_visible_count();

      ::i32 iPosition = 0;

      for (::index iColumn = 0; iColumn < iVisibleColumnCount; iColumn++)
      {

         auto pcolumn = m_pcolumna->get_visible(iColumn);

         pcolumn->m_iPosition = iPosition;

         iPosition += pcolumn->m_iWidth;

      }


      ::image_list::info ii;

      for (iColumn = 0; iColumn < iVisibleColumnCount; iColumn++)
      {

         list_column * pcolumn = m_pcolumna->get_visible(iColumn);

         iColumnWidth = pcolumn->m_iWidth;

         _001CreateImageList(pcolumn);

         if (iColumnWidth >= 0)
         {

            iItemWidth += iColumnWidth;

         }

         if (pcolumn->m_pimagelist != nullptr && pcolumn->m_pimagelist->get_image_count() > 0)
         {

            pcolumn->m_pimagelist->get_image_info(0, &ii);

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

      auto psystem = acmesystem()->m_paurasystem;

      auto pdraw2d = psystem->draw2d();

      auto pgraphics = pdraw2d->create_memory_graphics(this);

      //draw_select ds(this, pgraphics);

      pgraphics->set_font(this, ::e_element_none);

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

         for (index iOrder = 0; iOrder < m_pcolumna->get_visible_count(); iOrder++)
         {
            iColumn = _001MapOrderToColumn(iOrder);

            if (iColumn < 0)
            {

               continue;

            }

            list_column * pcolumn = m_pcolumna->get_visible(iColumn);

            //hditem.mask = HDI_WIDTH | HDI_TEXT | HDI_LPARAM | HDI_ORDER;
            //str.load_string(_001GetColumnText(iColumn));
            //hditem.pszText = (char *) (const ::string &) str;
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

      if (iColumn >= m_pcolumna->get_visible_count())
      {

         return false;

      }

      m_pcolumna->get_visible(iColumn)->m_iWidth = iWidth;

      m_plistheader->DIDDXColumn(true);

      _001OnColumnChange();

      return true;

   }


   //int list::_001GetColumnWidth(::index iColumn)
   //{

   //   auto  * pcolumn = m_pcolumna->get_visible(pitem->m_iColumn);

   //   if (pcolumn == nullptr)
   //   {

   //      return-1;

   //   }
   //   else
   //   {

   //      return pcolumn->m_iWidth;

   //   }

   //}


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

      for (index iColumn = 0; iColumn < m_pcolumna->get_size(); iColumn++)
      {

         list_column * pcolumn = m_pcolumna->element_at(iColumn);

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

      if (iColumn >= m_pcolumna->get_visible_count())
      {

         return -1;

      }

      auto pcolumn = m_pcolumna->get_visible(iColumn);

      if (!pcolumn)
      {

         return -1;

      }

      return (::index)pcolumn->m_iOrder;

   }


   index list::_001MapSubItemToColumn(index iSubItem)
   {

      return m_pcolumna->subitem_visible_index(iSubItem);

   }


   index list::_001MapColumnToSubItem(index iColumn)
   {

      ASSERT(iColumn >= 0);
      ASSERT(iColumn < m_pcolumna->get_visible_count());

      return m_pcolumna->get_visible(iColumn)->subitem_index();

   }


   void list::_001DeleteColumn(index iColumn)
   {

      ASSERT(iColumn >= 0);
      ASSERT(iColumn < m_pcolumna->get_visible_count());

      m_pcolumna->erase(iColumn);

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

      auto pointOffset = get_context_offset();

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

         ::rectangle_i32 rectangleImpact;

         get_client_rect(rectangleImpact);

         index dHeight = (::index) ((rectangleImpact.height() / m_dItemHeight) * m_dItemHeight);

         index iWidth = rectangleImpact.width();

         int iImpactRowCount = 1;

         if(m_dItemHeight > 0)
         {

            iImpactRowCount = (int) maximum(1, dHeight / m_dItemHeight);

         }

         int iColumnCount = 1;

         if(m_iItemWidth > 0)
         {

            iColumnCount = (int) (iWidth / m_iItemWidth);

         }

         return iImpactRowCount * iColumnCount;

      }
      else if (m_eview == impact_icon)
      {

         ::rectangle_i32 rectangleImpact;

         get_client_rect(rectangleImpact);

         const ::size_i32 & sizeItem = get_item_size();

         return maximum((rectangleImpact.width() / sizeItem.cx) * (rectangleImpact.height() / sizeItem.cy),
                    m_piconlayout->m_iaDisplayToStrict.get_max_a() + 1);

      }
      else if (m_eview == impact_report)
      {

         ::rectangle_i32 rectangleImpact;

         get_client_rect(rectangleImpact);

         if (m_dItemHeight == 0)
         {

            return 0;

         }
         else
         {

            double dHeight = rectangleImpact.height();

            if (m_bTopText)
            {

               dHeight -= m_rectangleTopText.height();

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

      ::rectangle_i32 rectangleItem;

      ::rectangle_i32 rectangleIntersect;

      ::rectangle_i32 rectangleUpdate;

      get_client_rect(rectangleUpdate);

      auto pitem = get_item(iItemFirst);

      if (iItemFirst >= 0)
      {

         iItemLast = -1;

         for (index i = iItemFirst + 1; i < iItemCount; i++)
         {

            pitem->m_iDisplayItem = i;

            //if (m_bGroup)
            //{

            //   item.m_iGroupTopDisplayIndex = 0;

            //   for (item.m_iGroup = 0; item.m_iGroup < m_nGroupCount; item.m_iGroup++)
            //   {

            //      item.m_iGroupCount = _001GetGroupItemCount(item.m_iGroup);

            //      if (i >= item.m_iGroupTopDisplayIndex && i < (item.m_iGroupTopDisplayIndex + item.m_iGroupCount))
            //      {

            //         break;

            //      }

            //   }

            //}

            index_item_rectangle(*pitem);

            if (pitem->m_bOk)
            {

               if (!rectangleIntersect.intersect(pitem->m_pdrawlistitem->m_rectangleItem, rectangleUpdate))
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

      __UNREFERENCED_PARAMETER(point);
      __UNREFERENCED_PARAMETER(iItem);
      __UNREFERENCED_PARAMETER(iSubItem);
      __UNREFERENCED_PARAMETER(iListItem);
      __UNREFERENCED_PARAMETER(eelement);

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

      __UNREFERENCED_PARAMETER(point);
      __UNREFERENCED_PARAMETER(iItem);
      __UNREFERENCED_PARAMETER(iSubItem);
      __UNREFERENCED_PARAMETER(iListItem);
      __UNREFERENCED_PARAMETER(eelement);

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

      auto pointOffset = get_context_offset();

      ::rectangle_i32 rectangleMargin;

      get_margin_rect(rectangleMargin);

      auto iLeft = (index)-pointOffset.x - (rectangleMargin.left * 2);

      if (m_bGroup && m_bLateralGroup)
      {

         iLeft += m_iLateralGroupWidth;

      }

      index iRight;

      //draw_list_item item(this);

      if (point.x < 0)
      {

         return false;

      }

      for (::index iColumn = 0; iColumn < iColumnCount; iColumn++)
      {

         //_001GetColumnWidth(&item);

         //if (!item.m_bOk)
         //{

           // continue;

         //}

         auto pcolumn = m_pcolumna->get_visible(iColumn);

         iRight = iLeft + pcolumn->m_iWidth;

         if (iLeft <= point.x && point.x < iRight)
         {

            iItemParam = iItem;

            iSubItemParam = pcolumn->m_iSubItem;

            return true;

         }

         iLeft = iRight;

      }

      return false;

   }


   bool list::_001DisplayHitTest(const ::point_i32 & point, index&iItemParam)
   {

      {

         ::rectangle_i32 rectangleClient;

         get_client_rect(rectangleClient);

         if (point.x < 0
               || point.x > rectangleClient.right
               || point.y < 0
               || point.y > rectangleClient.bottom)
         {

            return false;

         }

      }

      if (m_eview == impact_report)
      {

         auto pointOffset = get_context_offset();

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

         ::rectangle_i32 rectangleClient;

         get_client_rect(rectangleClient);

         if (m_bTopText)
         {

            rectangleClient.top += m_rectangleTopText.height();

         }

         if (m_bHeaderCtrl)
         {

            rectangleClient.top += (::i32) m_dItemHeight;

         }

         index dHeight = (::index) ((rectangleClient.height() / m_dItemHeight) * m_dItemHeight);

         auto pointOffset = get_context_offset();

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

         int iImpactRowCount = 1;

         if(m_dItemHeight > 0)
         {

            iImpactRowCount = (int) maximum(1, dHeight / m_dItemHeight);

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

         iItem = iColumn * iImpactRowCount + iRow;

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

         if (m_pcolumna->get_count() == 0)
         {

            return false;

         }

         ::rectangle_i32 rectangleClient;

         get_client_rect(rectangleClient);

         if (m_bTopText)
         {

            rectangleClient.top += m_rectangleTopText.height();

         }

         index iIconSize = maximum(32, (*m_pcolumna)[0]->m_sizeIcon.cy);

         index iItemSize = iIconSize * 2;

         auto pointOffset = get_context_offset();

         index ix = (index)(point.x + pointOffset.x);

         ix = (index)maximum(pointOffset.x, ix);

         ix = (index)minimum(rectangleClient.right, ix);

         ix = (index)maximum(rectangleClient.left, ix);

         ix /= iItemSize;

         index iy = point.y + pointOffset.y;

         iy = maximum(pointOffset.y, iy);

         iy = maximum(rectangleClient.top, iy);

         iy /= iItemSize;

         iItemParam = iy * (maximum(1, rectangleClient.width() / iItemSize)) + ix;

         return true;

      }

      return false;

   }


   void list::_001GetGroupRect(::user::draw_list_group * pdrawlistgroup)
   {

      if (pdrawlistgroup->m_iGroup < 0)
      {

         return_(pdrawlistgroup->m_bOk, false);

      }

      if (pdrawlistgroup->m_iGroup >= m_nGroupCount)
      {

         return_(pdrawlistgroup->m_bOk, false);

      }

      index iDisplayItemFirst = 0;

      index iDisplayItemLast = _001GetGroupItemCount(0) - 1;

      pdrawlistgroup->m_iGroupRectGroup = 0;

      while (pdrawlistgroup->m_iGroupRectGroup < pdrawlistgroup->m_iGroup)
      {

         pdrawlistgroup->m_iGroupRectGroup++;

         iDisplayItemFirst = iDisplayItemLast + 1;

         iDisplayItemLast = iDisplayItemFirst + _001GetGroupItemCount(pdrawlistgroup->m_iGroupRectGroup) - 1;

      }


      auto iItemFirst = _001DisplayToStrict(iDisplayItemFirst);

      auto pitemFirst = get_item(iItemFirst);

      pitemFirst->m_iDisplayItem = iDisplayItemFirst;

      //itemFirst.m_iGroup = pdrawitem->m_iGroupRectGroup;

      index_item_rectangle(*pitemFirst);

      auto iItemLast = _001DisplayToStrict(iDisplayItemLast);

      auto pitemLast = get_item(iItemLast);

      pitemLast->m_iDisplayItem = iDisplayItemLast;

      index_item_rectangle(*pitemLast);

      pdrawlistgroup->m_rectangleGroup.unite(pitemFirst->m_pdrawlistitem->m_rectangleItem, pitemLast->m_pdrawlistitem->m_rectangleItem);

      pdrawlistgroup->m_rectangleGroup.bottom = maximum(pitemLast->m_pdrawlistitem->m_rectangleItem.bottom, pitemFirst->m_pdrawlistitem->m_rectangleItem.top + m_iGroupMinHeight);

      pdrawlistgroup->m_rectangleGroup.left = 0;

      pdrawlistgroup->m_rectangleGroup.right = m_iLateralGroupWidth;

      pdrawlistgroup->m_bOk = true;

   }


   void list::index_item_rectangle(::user::draw_list_item * pdrawitem)
   {

      if (pdrawitem->m_iDisplayItem < 0)
      {

         return_(pdrawitem->m_bOk, false);

      }

      if (pdrawitem->m_iDisplayItem == pdrawitem->m_iRectangleDisplayItem)
      {

         return_(pdrawitem->m_bOk, true);

      }

      if (m_eview == impact_icon && pdrawitem->m_iDisplayItem >= m_nDisplayCount)
      {

         return_(pdrawitem->m_bOk, false);

      }

      auto pointOffset = get_context_offset();

      if (m_eview == impact_report)
      {

         if (m_bGroup)
         {

            if (m_bLateralGroup)
            {

               if (pdrawitem->m_iRectangleDisplayItem < 0)
               {

                  pdrawitem->m_rectangleItem.left = m_iLateralGroupWidth;

                  pdrawitem->m_rectangleItem.right = (::i32)(pdrawitem->m_rectangleItem.left + m_iItemWidth);

                  pdrawitem->m_iRectangleDisplayItem = 0;

                  pdrawitem->m_rectangleItem.top = 0;

                  if (m_bHeaderCtrl)
                  {

                     pdrawitem->m_rectangleItem.top += (::i32) (m_dItemHeight);

                  }

                  if (m_bTopText)
                  {

                     pdrawitem->m_rectangleItem.top += m_rectangleTopText.height();

                  }

                  pdrawitem->m_rectangleItem.bottom = (::i32) (pdrawitem->m_rectangleItem.top + m_dItemHeight);

              //    pdrawitem->m_rectangleItem.offset(-pointOffset.x, -pointOffset.y);

               }

               //if (pdrawitem->m_iDisplayItem > pdrawitem->m_iRectangleDisplayItem)
               //{

               //   i32 iOffset = (i32)((pdrawitem->m_iRectangleDisplayItem - pdrawitem->m_iGroupTopDisplayIndex) * m_dItemHeight);

               //   pdrawitem->m_rectangleItem.top -= iOffset;

               //   pdrawitem->m_rectangleItem.bottom = (::i32) (pdrawitem->m_rectangleItem.top + m_dItemHeight);

               //   while (pdrawitem->m_iGroupTopDisplayIndex + pdrawitem->m_iGroupCount < pdrawitem->m_iDisplayItem)
               //   {

               //      pdrawitem->m_rectangleItem.top += iOffset;

               //      pdrawitem->m_rectangleItem.bottom = (::i32) (pdrawitem->m_rectangleItem.top + m_dItemHeight);

               //      if ((pdrawitem->m_iGroup + 1) >= m_nGroupCount)
               //      {

               //         break;

               //      }

               //      pdrawitem->m_iGroup++;

               //      pdrawitem->m_iGroupTopDisplayIndex += pdrawitem->m_iGroupCount;

               //      pdrawitem->m_iGroupCount = _001GetGroupItemCount(pdrawitem->m_iGroup);

               //      pdrawitem->m_iItemRectItem = pdrawitem->m_iGroupTopDisplayIndex;

               //   }

               //}
               //else
               //{

               //   i32 iOffset = (i32)((pdrawitem->m_iItemRectItem - pdrawitem->m_iGroupTopDisplayIndex) * m_dItemHeight);

               //   pdrawitem->m_rectangleItem.top -= iOffset;

               //   pdrawitem->m_rectangleItem.bottom = (::i32)(pdrawitem->m_rectangleItem.top + m_dItemHeight);

               //   while (pdrawitem->m_iGroupTopDisplayIndex + pdrawitem->m_iGroupCount > pdrawitem->m_iDisplayItem)
               //   {

               //      if ((pdrawitem->m_iGroup - 1) < 0)
               //      {

               //         break;

               //      }

               //      pdrawitem->m_iGroup--;

               //      i32 dHeight = _001GetGroupHeight(pdrawitem->m_iGroup);

               //      pdrawitem->m_rectangleItem.top -= dHeight;

               //      pdrawitem->m_rectangleItem.bottom = (::i32)(pdrawitem->m_rectangleItem.top + m_dItemHeight);

               //      pdrawitem->m_iGroupCount = _001GetGroupItemCount(pdrawitem->m_iGroup);

               //      pdrawitem->m_iGroupTopDisplayIndex -= pdrawitem->m_iGroupCount;

               //      pdrawitem->m_iItemRectItem = pdrawitem->m_iGroupTopDisplayIndex;

               //   }

               //}

               //if (pdrawitem->m_iGroup < m_nGroupCount && pdrawitem->m_iGroup >= 0)
               //{

               //   pdrawitem->m_iItemRectItem = pdrawitem->m_iDisplayItem;

               //   pdrawitem->m_rectangleItem.top += (::i32)((pdrawitem->m_iItemRectItem - pdrawitem->m_iGroupTopDisplayIndex) * m_dItemHeight);

               //   pdrawitem->m_rectangleItem.bottom = (::i32)(pdrawitem->m_rectangleItem.top + m_dItemHeight);

               //}

            }
            else
            {

               throw ::interface_only();

            }

         }
         else
         {

            pdrawitem->m_rectangleItem.left = 0;

            pdrawitem->m_rectangleItem.right = (::i32)m_iItemWidth;

            pdrawitem->m_rectangleItem.top = 0;

            if (m_bHeaderCtrl)
            {

               pdrawitem->m_rectangleItem.top += (::i32)(m_dItemHeight);

            }

            pdrawitem->m_rectangleItem.top += (::i32)(m_dItemHeight * pdrawitem->m_iDisplayItem);

            if (m_bTopText)
            {

               pdrawitem->m_rectangleItem.top += m_rectangleTopText.height();

            }

            pdrawitem->m_rectangleItem.bottom = (::i32)(pdrawitem->m_rectangleItem.top + m_dItemHeight);

            pdrawitem->m_iRectangleDisplayItem = pdrawitem->m_iDisplayItem;

            pdrawitem->m_bOk = true;

         }

      }
      else if (m_eview == impact_list)
      {

         ::rectangle_i32 rectangleClient;

         get_client_rect(rectangleClient);

         if (m_bTopText)
         {

            rectangleClient.top += m_rectangleTopText.height();

         }

         if (m_bHeaderCtrl)
         {

            rectangleClient.top += (::i32)(m_dItemHeight);

         }

         if (m_dItemHeight <= 0)
         {

            return_(pdrawitem->m_bOk, false);

         }

         index dHeight = (::index) ((rectangleClient.height() / m_dItemHeight) * m_dItemHeight);

         if (dHeight != 0 && m_dItemHeight != 0)
         {

            int iImpactRowCount = (int) maximum(1, dHeight / m_dItemHeight);

            int iColumn = (int) (pdrawitem->m_iItem / iImpactRowCount);

            int iRow = pdrawitem->m_iItem % iImpactRowCount;

            pdrawitem->m_rectangleItem.left = iColumn * m_iItemWidth;

            pdrawitem->m_rectangleItem.top = (::i32)(iRow * m_dItemHeight);

         }

         if (m_bTopText)
         {

            pdrawitem->m_rectangleItem.top += m_rectangleTopText.height();

         }

         if (m_bHeaderCtrl)
         {

            pdrawitem->m_rectangleItem.top += (::i32)(m_dItemHeight);

         }

         pdrawitem->m_rectangleItem.bottom = (::i32)(pdrawitem->m_rectangleItem.top + m_dItemHeight);

         pdrawitem->m_rectangleItem.right = (::i32)(pdrawitem->m_rectangleItem.left + m_iItemWidth);

         pdrawitem->m_rectangleItem.offset(-pointOffset.x, -pointOffset.y);

      }
      else if (m_eview == impact_icon)
      {

         ::rectangle_i32 rectangleClient;

         get_client_rect(rectangleClient);

         if (rectangleClient.is_empty())
         {

            return_(pdrawitem->m_bOk, false);

         }

         if (m_bTopText)
         {

            rectangleClient.top += m_rectangleTopText.height();

         }

         index iIconSize = maximum(32, (*m_pcolumna)[0]->m_sizeIcon.cy);

         index iItemSize = iIconSize * 2;

         pdrawitem->m_rectangleItem.left = (::i32)(iItemSize * (pdrawitem->m_iDisplayItem % (maximum(1, rectangleClient.width() / iItemSize))));

         pdrawitem->m_rectangleItem.top = (::i32)(iItemSize * (pdrawitem->m_iDisplayItem / (maximum(1, rectangleClient.width() / iItemSize))));

         pdrawitem->m_rectangleItem.bottom = (::i32)(pdrawitem->m_rectangleItem.top + iItemSize);

         pdrawitem->m_rectangleItem.right = (::i32)(pdrawitem->m_rectangleItem.left + iItemSize);

         pdrawitem->m_rectangleItem.offset(-pointOffset.x, -pointOffset.y);

         if (m_bDrag && m_iItemLButtonDown >= 0)
         {

            if (pdrawitem->m_iItem == m_iItemLButtonDown || m_rangeSelection.has_item(pdrawitem->m_iDisplayItem))
            {

               ::point_i32 point = m_pointLButtonUp;

               ::point_i32 point2 = m_pointLButtonDown1;

               point -= point2;

               pdrawitem->m_rectangleItem.offset(point);

            }

         }

      }

      pdrawitem->m_bOk = true;

   }


   void list::_001GetSubItemRect(::user::draw_list_subitem * pdrawlistsubitem)
   {

      if (pdrawlistsubitem->m_pitem->m_iDisplayItem != pdrawlistsubitem->m_pitem->m_pdrawlistitem->m_iRectangleDisplayItem)
      {

         index_item_rectangle(*pdrawlistsubitem->m_pitem);

         if (!pdrawlistsubitem->m_pitem->m_bOk)
         {

            return;

         }

      }

      if (pdrawlistsubitem->m_iRectangleOrder == pdrawlistsubitem->m_iOrder)
      {

         return_(pdrawlistsubitem->m_bOk, true);

      }

      if (m_eview == impact_icon || m_eview == impact_list)
      {

         pdrawlistsubitem->m_rectangleSubItem = pdrawlistsubitem->m_pitem->m_pdrawlistitem->m_rectangleItem;

         return_(pdrawlistsubitem->m_bOk, true);

      }

      pdrawlistsubitem->m_bOk = true;

      pdrawlistsubitem->m_rectangleSubItem.top = pdrawlistsubitem->m_pitem->m_pdrawlistitem->m_rectangleItem.top;

      pdrawlistsubitem->m_rectangleSubItem.bottom = pdrawlistsubitem->m_pitem->m_pdrawlistitem->m_rectangleItem.bottom;

      pdrawlistsubitem->m_rectangleSubItem.left = pdrawlistsubitem->m_pcolumn->m_iPosition;

      pdrawlistsubitem->m_rectangleSubItem.right = pdrawlistsubitem->m_pcolumn->m_iPosition + pdrawlistsubitem->m_pcolumn->m_iWidth;

      //index iLastOrder = _001GetColumnCount() - 1;

      //if (iLastOrder < 0)
      //{

      //   return_(pdrawitem->m_bOk, false);

      //}

      //if (pdrawitem->m_iSubItemRectOrder < 0 || pdrawitem->m_iOrder == 0 || pdrawitem->m_iSubItemRectOrder > pdrawitem->m_iOrder)
      //{
      //   pdrawitem->m_iSubItemRectOrder = 0;
      //   pdrawitem->m_rectangleSubItem.left = pdrawitem->m_rectangleItem.left;
      //   pdrawitem->m_iSubItemRectColumn = _001MapOrderToColumn(pdrawitem->m_iOrder);
      //   pdrawitem->m_iColumn = pdrawitem->m_iSubItemRectColumn;
      //   _001GetColumnWidth(pdrawitem);
      //   pdrawitem->m_rectangleSubItem.right = pdrawitem->m_rectangleItem.left + pdrawitem->m_iColumnWidth;
      //   pdrawitem->m_iSubItemRectItem = pdrawitem->m_iItemRectItem;
      //   pdrawitem->m_iSubItemRectSubItem = pdrawitem->m_iSubItem;
      //   if (pdrawitem->m_iOrder == 0)
      //   {
      //      pdrawitem->m_bOk = true;
      //      return;
      //   }
      //}

      //if (pdrawitem->m_iOrder <= iLastOrder)
      //{
      //   while (pdrawitem->m_iSubItemRectOrder < pdrawitem->m_iOrder)
      //   {
      //      pdrawitem->m_iColumn = _001MapOrderToColumn(pdrawitem->m_iSubItemRectOrder);
      //      _001GetColumnWidth(pdrawitem);
      //      pdrawitem->m_rectangleSubItem.left += pdrawitem->m_iColumnWidth;
      //      pdrawitem->m_iSubItemRectOrder++;
      //   }
      //   pdrawitem->m_iColumn = _001MapOrderToColumn(pdrawitem->m_iSubItemRectOrder);
      //   pdrawitem->m_iSubItemRectColumn = pdrawitem->m_iColumn;
      //   _001GetColumnWidth(pdrawitem);
      //   pdrawitem->m_rectangleSubItem.right = pdrawitem->m_rectangleSubItem.left + pdrawitem->m_iColumnWidth;
      //   pdrawitem->m_iSubItemRectOrder = pdrawitem->m_iOrder;
      //   pdrawitem->m_iSubItemRectItem = pdrawitem->m_iItemRectItem;
      //   pdrawitem->m_iSubItemRectSubItem = pdrawitem->m_iSubItem;
      //   pdrawitem->m_bOk = true;
      //}

   }


   ::user::interaction * list::get_subitem_control(::index iSubItem)
   {

      auto pcolumn = m_pcolumna->get_by_subitem(iSubItem);

      if (!pcolumn)
      {

         return nullptr;

      }

      auto puserinteraction = get_child_by_id(pcolumn->m_atom);

      if (!puserinteraction)
      {

         return nullptr;

      }

      return puserinteraction;

   }


   void list::index_element_rectangle(::user::draw_list_subitem * pdrawlistsubitem, ::user::mesh::enum_element eelement)
   {

      if (pdrawlistsubitem->m_pitem->m_iDisplayItem != pdrawlistsubitem->m_pitem->m_pdrawlistitem->m_iRectangleDisplayItem)
      {

         pdrawlistsubitem->m_bOk = false;

         index_item_rectangle(*pdrawlistsubitem->m_pitem);

         if (!pdrawlistsubitem->m_pitem->m_bOk)
         {

            return;

         }

      }

      if (eelement == ::user::list::e_element_item)
      {

         return_(pdrawlistsubitem->m_bOk, true);

      }

      if (m_eview == impact_icon)
      {

         if (eelement == ::user::list::e_element_image)
         {

            i32 iIconSize = (*m_pcolumna)[0]->m_sizeIcon.cy;

            pdrawlistsubitem->m_rectangleImage.left = pdrawlistsubitem->m_pitem->m_pdrawlistitem->m_rectangleItem.left + iIconSize / 2;
            pdrawlistsubitem->m_rectangleImage.top = pdrawlistsubitem->m_pitem->m_pdrawlistitem->m_rectangleItem.top;
            pdrawlistsubitem->m_rectangleImage.right = pdrawlistsubitem->m_rectangleImage.left + iIconSize;
            pdrawlistsubitem->m_rectangleImage.bottom = pdrawlistsubitem->m_rectangleImage.top + iIconSize;

            return_(pdrawlistsubitem->m_bOk, true);

         }
         else if (eelement == ::user::mesh::e_element_text)
         {

            i32 iIconSize = (*m_pcolumna)[0]->m_sizeIcon.cy;

            pdrawlistsubitem->m_rectangleText.left = pdrawlistsubitem->m_pitem->m_pdrawlistitem->m_rectangleItem.left;
            pdrawlistsubitem->m_rectangleText.top = pdrawlistsubitem->m_pitem->m_pdrawlistitem->m_rectangleItem.top + iIconSize;
            pdrawlistsubitem->m_rectangleText.right = pdrawlistsubitem->m_rectangleText.left + iIconSize * 2;
            pdrawlistsubitem->m_rectangleText.bottom = pdrawlistsubitem->m_rectangleText.top + iIconSize;

            return_(pdrawlistsubitem->m_bOk, true);

         }

         return_(pdrawlistsubitem->m_bOk, false);

      }

      pdrawlistsubitem->m_bOk = false;

      _001GetSubItemRect(*pdrawlistsubitem);

      if (!pdrawlistsubitem->m_bOk)
      {

         return;

      }

      i32 x = pdrawlistsubitem->m_rectangleSubItem.left;

      //if (pdrawitem->m_iListItem == -1)
      {

         if (eelement == ::user::mesh::e_element_sub_item)
         {

            return_(pdrawlistsubitem->m_bOk, true);

         }

         if (::is_set(pdrawlistsubitem->m_pcolumn))
         {

            if (pdrawlistsubitem->m_pcolumn->m_bIcon)
            {

               pdrawlistsubitem->m_bOk = false;

               _001GetSubItemImage(*pdrawlistsubitem);

               if (pdrawlistsubitem->m_bOk && pdrawlistsubitem->m_iImage >= 0)
               {

                  if (eelement == ::user::list::e_element_image)
                  {

                     ::rectangle_i32 rectangleAlign(pdrawlistsubitem->m_rectangleSubItem);

                     rectangleAlign.left = x;
                     ::rectangle_i32 rectangleIcon;
                     rectangleIcon.set(0, 0, pdrawlistsubitem->m_pcolumn->m_sizeIcon.cx, pdrawlistsubitem->m_pcolumn->m_sizeIcon.cy);
                     rectangleIcon.Align(e_align_left_center, rectangleAlign);
                     pdrawlistsubitem->m_rectangleImage = rectangleIcon;

                     return_(pdrawlistsubitem->m_bOk, true);

                  }
                  else
                  {

                     x += pdrawlistsubitem->m_pcolumn->m_sizeIcon.cx;

                     x += m_iImageSpacing;

                  }

               }
               else if (eelement == ::user::list::e_element_image)
               {

                  return_(pdrawlistsubitem->m_bOk, false);

               }

            }
            else if (pdrawlistsubitem->m_pcolumn->m_pimagelist != nullptr)
            {

               ::image_list::info ii;

               pdrawlistsubitem->m_bOk = false;

               _001GetSubItemImage(pdrawlistsubitem);

               if (pdrawlistsubitem->m_bOk && pdrawlistsubitem->m_iImage >= 0)
               {

                  string strText = pdrawlistsubitem->m_strText;

                  pdrawlistsubitem->m_pcolumn->m_pimagelist->get_image_info((i32)pdrawlistsubitem->m_iImage, &ii);

                  if (eelement == ::user::list::e_element_image)
                  {

                     ::rectangle_i32 rectangleAlign(pdrawlistsubitem->m_rectangleSubItem);
                     rectangleAlign.left = x;
                     ::rectangle_i32 rectangleIcon;
                     rectangleIcon.set(0, 0, ii.m_rectangle.width(), ii.m_rectangle.height());
                     rectangleIcon.Align(e_align_left_center, rectangleAlign);
                     pdrawlistsubitem->m_rectangleImage = rectangleIcon;

                     if (ii.m_rectangle.size().cx > m_sizeMaximumImage.cx 
                        || ii.m_rectangle.size().cy > m_sizeMaximumImage.cy)
                     {

                        m_sizeMaximumImage.cx = maximum(m_sizeMaximumImage.cx, ii.m_rectangle.size().cx);

                        m_sizeMaximumImage.cy = maximum(m_sizeMaximumImage.cy, ii.m_rectangle.size().cy);

                        set_need_layout();

                     }

                     return_(pdrawlistsubitem->m_bOk, true);

                  }
                  else
                  {

                     x += ii.m_rectangle.width();

                     x += m_iImageSpacing;

                  }

               }
               else if (eelement == ::user::list::e_element_image)
               {

                  return_(pdrawlistsubitem->m_bOk, false);

               }

            }

         }
         else if (eelement == ::user::list::e_element_image)
         {

            return_(pdrawlistsubitem->m_bOk, false);

         }

         if (eelement == ::user::mesh::e_element_text)
         {

            pdrawlistsubitem->m_rectangleText.left = x;
            pdrawlistsubitem->m_rectangleText.right = pdrawlistsubitem->m_rectangleSubItem.right;
            pdrawlistsubitem->m_rectangleText.top = pdrawlistsubitem->m_rectangleSubItem.top;
            pdrawlistsubitem->m_rectangleText.bottom = pdrawlistsubitem->m_rectangleSubItem.bottom;

            return_(pdrawlistsubitem->m_bOk, true);

         }

      }

      pdrawlistsubitem->m_bOk = false;

   }


   void list::_001GetGroupElementRect(::user::draw_list_group * pdrawlistgroup, ::user::mesh::enum_group_element egroupelement)
   {

      if (m_bGroup && m_bLateralGroup && (egroupelement == ::user::list::e_group_element_image || egroupelement == ::user::list::e_group_element_item_text))
      {

         i32 x = pdrawlistgroup->m_rectangleGroup.left;

         i32 iImageBottom = pdrawlistgroup->m_rectangleGroup.top;

         if (m_pimagelistGroup != nullptr)
         {

            ::image_list::info ii;

            _001GetGroupImage(*pdrawlistgroup);

            if (pdrawlistgroup->m_bOk && pdrawlistgroup->m_iImage >= 0)
            {

               m_pimagelistGroup->get_image_info((i32)pdrawlistgroup->m_iImage, &ii);

               if (egroupelement == ::user::list::e_group_element_image)
               {

                  pdrawlistgroup->m_rectangleImage.left = x;
                  pdrawlistgroup->m_rectangleImage.right = x + ii.m_rectangle.width();
                  pdrawlistgroup->m_rectangleImage.top = pdrawlistgroup->m_rectangleGroup.top;
                  pdrawlistgroup->m_rectangleImage.bottom = pdrawlistgroup->m_rectangleImage.top + ii.m_rectangle.height();

                  return_(pdrawlistgroup->m_bOk, true);

               }
               else
               {

                  x += ii.m_rectangle.width();

                  x += 2;

                  iImageBottom += ii.m_rectangle.height() + 2;

               }

            }
            else if (egroupelement == ::user::list::e_group_element_image)
            {

               return_(pdrawlistgroup->m_bOk, false);

            }

         }
         else if (egroupelement == ::user::list::e_group_element_image)
         {

            return_(pdrawlistgroup->m_bOk, false);

         }

         if (egroupelement == ::user::list::e_group_element_item_text)
         {

            pdrawlistgroup->m_rectangleText.top = (::i32)(pdrawlistgroup->m_rectangleGroup.top + m_dItemHeight * pdrawlistgroup->m_iItem);

            if (pdrawlistgroup->m_rectangleText.top >= iImageBottom)
            {

               pdrawlistgroup->m_rectangleText.left = pdrawlistgroup->m_rectangleGroup.left;

            }
            else
            {

               pdrawlistgroup->m_rectangleText.left = x;

            }

            pdrawlistgroup->m_rectangleText.right = pdrawlistgroup->m_rectangleGroup.right;

            pdrawlistgroup->m_rectangleText.bottom = (::i32)(pdrawlistgroup->m_rectangleText.top + m_dItemHeight);

            return_(pdrawlistgroup->m_bOk, true);

         }

         pdrawlistgroup->m_bOk = false;

      }

   }


   void list::LayoutHeaderCtrl()
   {

      synchronous_lock synchronouslock(this->synchronization());

      if (m_plistheader == nullptr)
      {

         return;

      }

      if (m_bHeaderCtrl)
      {

         ::rectangle_i32 rectangleFocus;

         GetFocusRect(rectangleFocus);

         m_plistheader->order_bottom();

         m_plistheader->place(::rectangle_i32_dimension(0, 0, (int)maximum(m_iItemWidth + 10, rectangleFocus.width()), (int)m_dItemHeight));

         m_plistheader->display();;

      }
      else
      {

         m_plistheader->display(e_display_none);

      }

   }


   void list::on_message_key_down(::message::message * pmessage)
   {

      auto pkey = pmessage->m_union.m_pkey;

      if (pkey->previous()) // give chance to child
         return;

      synchronous_lock synchronouslock(this->synchronization());

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
            itemrange.set(iItem, iItem, 0, m_pcolumna->get_count() - 1, -1, -1);
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

      auto pmouse = pmessage->m_union.m_pmouse;

      pmouse->m_lresult = 1;

      auto point = pmouse->m_point;

      screen_to_client()(point);

      synchronous_lock synchronouslock(this->synchronization());

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

               ::rectangle_i32 rectangleClient;

               get_client_rect(rectangleClient);

               index iIconSize = maximum(32, (*m_pcolumna)[0]->m_sizeIcon.cy);

               index iItemSize = iIconSize * 2;

               ::count iItemColumnCount = maximum(1, rectangleClient.width() / iItemSize);

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

               on_enable_hover_select();

            }

         }

      }


   }




   void list::on_message_left_button_down(::message::message * pmessage)
   {

      auto pmouse = pmessage->m_union.m_pmouse;

      set_mouse_capture();

      index iDisplayItem;

      auto point = pmouse->m_point;

      screen_to_client()(point);

      synchronous_lock synchronouslock(this->synchronization());

      auto psession = get_session();

      m_bLButtonDown = true;

      auto tickNow = ::duration::now();

      auto tick2 = tickNow - m_durationLButtonDownStart2;

      auto tick1 = tickNow - m_durationLButtonDownStart1;

      auto tickDoubleClick = DBLCLKMS;

      if(tick2 < tickDoubleClick)
      {

         m_durationLButtonDownStart1 = m_durationLButtonDownStart2;

         m_durationLButtonDownStart2 = tickNow;

         m_pointLButtonDown1 = m_pointLButtonDown2;

         m_pointLButtonDown2 = point;

         m_iClick = 2;

      }
      else if(tick1 < tickDoubleClick)
      {

         m_durationLButtonDownStart2 = tickNow;

         m_pointLButtonDown2 = point;

         m_iClick = 2;

      }
      else
      {

         m_durationLButtonDownStart1 = tickNow;

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

         auto tickNow = ::duration::now();

         if (tickNow - m_durationLButtonDownStart2 < DBLCLKMS)
         {

            m_durationLButtonDownStart1 = m_durationLButtonDownStart2;

            m_durationLButtonDownStart2 = tickNow;

            m_pointLButtonDown1 = m_pointLButtonDown2;

            m_pointLButtonDown2 = point;

            m_iClick = 2;

         }
         else if (tickNow - m_durationLButtonDownStart1 < DBLCLKMS)
         {

            m_durationLButtonDownStart2 = tickNow;

            m_pointLButtonDown2 = point;

            m_iClick = 2;

         }
         else
         {

            m_durationLButtonDownStart1 = tickNow;

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

                  itemrange.set(iLItem, iUItem, 0, m_pcolumna->get_count() - 1, -1, -1);

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

                  itemrange.set(iLItem, iUItem, 0, m_pcolumna->get_count() - 1, -1, -1);

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

                  SetTimer(e_timer_drag_start, 1.2_s);

                  item_range itemrange;

                  itemrange.set(iDisplayItem, iDisplayItem, 0, m_pcolumna->get_count() - 1, -1, -1);

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

               screen_to_client()(point);

               draw_list_item item;

               item.m_iItem = m_iItemLButtonDown;

               item.m_iDisplayItem = m_iDisplayItemLButtonDown1;

               index_item_rectangle(&item);

               payload("offx") = point.x - item.m_rectangleItem.left;

               payload("offy") = point.y - item.m_rectangleItem.top;

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

      auto pmouse = pmessage->m_union.m_pmouse;

      auto point = pmouse->m_point;

      screen_to_client()(point);

      release_mouse_capture();

      KillTimer(e_timer_drag_start);

      KillTimer(224455);

      synchronous_lock synchronouslock(this->synchronization());


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

                        strSort += "-" + get_display_tag() + ".icon_list_impact_sort";

                        synchronouslock.lock();

                        string_array stra;

                        for (index a = 0; a <= m_plist->m_piconlayout->m_iaDisplayToStrict.m_iMaxA; a++)
                        {

                           index b = m_plist->m_piconlayout->m_iaDisplayToStrict.get_b(a);

                           stra.add(_001GetItemId(b));

                        }

                        auto pcontext = get_context();

                        pcontext->m_papexcontext->file().put_text(strSort, stra.implode("\n"));

                        synchronouslock.unlock();

                        update_icon_list_impact_sort();

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

                     if (!on_click(new_item_with_index(_001DisplayToStrict(iDisplayItemLButtonUp))))
                     {

                        //index iItem = _001DisplayToStrict(iDisplayItemLButtonUp);

                        //_001OnItemClick(iItem);

                     }

                  }
                  else
                  {

                     send_message(e_message_left_button_double_click, pmouse->m_nFlags, __MAKE_LPARAM(point.x, point.y));

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

      auto pmouse = pmessage->m_union.m_pmouse;

      pmouse->previous();

      auto psession = get_session();

      auto point = pmouse->m_point;

      screen_to_client()(point);

      synchronous_lock synchronouslock(this->synchronization());

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
               itemrange.set(iItem, iItem, 0, m_pcolumna->get_count() - 1, -1, -1);
               m_rangeSelection.add_item(itemrange);
               set_need_redraw();

            }

         }
         
         m_uiRButtonUpFlags = (::u32)pmouse->m_nFlags;
         
         m_pointRButtonUp = pmouse->m_point;
         
         SetTimer(8477, 500_ms, nullptr);

      }


      pmessage->m_bRet = true;
   }



   bool list::on_click(::item * pitem)
   {

      auto ptopic = create_topic(::id_list_clicked);

      ptopic->m_puserelement = this;

      route(ptopic);

      //if (m_pformcallback != nullptr)
      //{

      //   m_pformcallback->route(&topic);

      //}
      //else if (get_form() != nullptr)
      //{

      //   get_form()->send_message(e_message_event, 0, (LPARAM)&ev);

      //}
      //else
      //{

      //   get_parent()->send_message(e_message_event, 0, (LPARAM)&ev);

      //}

      return ptopic->m_bRet;

   }


   bool list::on_right_click(::item * pitem)
   {

      __UNREFERENCED_PARAMETER(pitem);

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

               selection.add_item(key.m_strDataKey + "/" + __string(iLine));

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


   string list::_001GetColumnText(index iColumn)
   {

      list_column * pcolumn = m_pcolumna->get_visible(iColumn);

      if (pcolumn == nullptr)
      {

         return atom();

      }

      return pcolumn->m_text.get_text();

   }


   void list::on_message_left_button_double_click(::message::message * pmessage)
   {

      auto pmouse = pmessage->m_union.m_pmouse;

      m_iClick = 2;

      auto point = pmouse->m_point;

      screen_to_client()(point);

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
                  on_click(new_item_with_index(iItem));

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

      auto pointOffset = get_context_offset();

      m_plistheader->order_top();
      //m_plistheader->move_to(-pointOffset.x, 0);
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

      __UNREFERENCED_PARAMETER(wparam);

      __UNREFERENCED_PARAMETER(lparam);


      for (index iColumn = 0; iColumn < m_pcolumna->get_visible_count(); iColumn++)
      {

         list_column * pcolumn = m_pcolumna->get_visible(iColumn);

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

      __UNREFERENCED_PARAMETER(wparam);

      __UNREFERENCED_PARAMETER(lparam);


      _001OnHeaderCtrlTrack(0, 0);

      string str;

      index i;

      index width;

      for (i = 0; i < m_pcolumna->get_count(); i++)
      {

         str.format("list_column[%d].width", i);

         width = m_pcolumna->element_at(i)->m_iWidth;

         //datastream()->set(str, width);

      }

      return true;

   }


   bool list::_001OnHeaderCtrlTrack(wparam wparam, lparam lparam)

   {

      __UNREFERENCED_PARAMETER(wparam);

      __UNREFERENCED_PARAMETER(lparam);


      //    for(index iColumn = 0; iColumn < m_pcolumna->get_visible_count(); iColumn++)
      //  {
      //         list_column & column = m_pcolumna->get_visible(iColumn);
      //pcolumn->m_iWidth = m_plistheader->GetItemWidth(iColumn);
      //}

      _001OnColumnChange();

      set_need_redraw();

      return true;

   }


   void list::_001ShowSubItem(index iSubItem, bool bShow)
   {

      string str;

      str.format("SubItem[%d].Visible", iSubItem);

      //datastream()->set(str, bShow ? 1 : 0);

      m_pcolumna->ShowSubItem(iSubItem, bShow);

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

      ::index iIndex = -1;

      if (!m_mapSubItemIndex.lookup(iSubItem, iIndex))
      {

         for (index i = 0; i < this->get_size(); i++)
         {

            list_column * pcolumn = element_at(i);

            if (pcolumn != nullptr && pcolumn->m_iSubItem == iSubItem)
            {

               iIndex = i;

               break;

            }

         }

         m_mapSubItemIndex.set_at(iSubItem, iIndex);

      }

      return iIndex;

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


   index list_column_array::control_id_index(const ::atom & atom)
   {

      for (index iIndex = 0; iIndex < this->get_size(); iIndex++)
      {

         list_column * pcolumn = element_at(iIndex);

         if (pcolumn != nullptr && pcolumn->m_atom == atom)
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


   list_column * list_column_array::get_by_control_id(const ::atom & atom)
   {

      auto iIndex = subitem_index((::index) atom);

      return get_by_index(iIndex);

   }


   list_column * list_column_array::get_by_control(::user::interaction * pinteraction)
   {

      return get_by_control_id(pinteraction->m_atom);

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


   void list_column_array::clear_cache()
   {

      m_mapSubItemIndex.clear();

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

   ::count list_column_array::get_visible_count()
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
   //   iptr iVisibleCount = get_visible_count();
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
   //   iptr iVisibleCount = get_visible_count();
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
   //      if (this->get_size() == get_visible_count())
   //      {
   //         for (index iColumn = 0; iColumn < get_visible_count(); iColumn++)
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
//         str.format("list_column[%d].Next", i);
//
//         //m_plist->datastream()->set(str, pcolumn->m_iOrder);
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
//         str.format("list_column[%d].Next", i);
//
//         //m_plist->datastream()->get(str, pcolumn->m_iOrder);
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

      m_pcolumna->DISaveOrder();

   }

   void list::DILoadOrder()
   {
      m_pcolumna->DILoadOrder();
      _001OnColumnChange();
   }


   void list::_001UpdateColumns()
   {

      _001RemoveAllColumns();

      auto keepLockImpactUpdate = keep(m_bLockImpactUpdate);

      _001InsertColumns();

      keepLockImpactUpdate.KeepAway();

      DIDDXHeaderLayout(false);

      _001OnColumnChange();

   }


   void list::_001InsertColumns()
   {


   }


   void list::_001RemoveAllColumns()
   {

      {

         synchronous_lock synchronouslock(this->synchronization());

         m_pcolumna->erase_all();

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

      ::pointer<::message::create>pcreate(pmessage);

      pmessage->previous();

      if (pcreate->m_lresult == -1)
      {

         pmessage->m_bRet = false;

         return;

      }

      __defer_construct_new(m_pcolumna);

      m_pcolumna->Initialize(this);



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

      if (pcolumn->m_pimagelist == nullptr)
      {

         pcolumn->m_pimagelist = __new(::image_list);

      }

      throw ::interface_only();

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

      draw_list_item item;

      item.m_iItem = iItem;

      item.m_iDisplayItem = iItem;

      index_item_rectangle(&item);

      if (!item.m_bOk)
      {

         return false;

      }

      ::rectangle_i32 rectangleClient;

      get_client_rect(rectangleClient);

      return rectangleClient.intersect(rectangleClient, item.m_rectangleItem) != 0;

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

      auto psystem = acmesystem()->m_paurasystem;

      auto pdraw2d = psystem->draw2d();

      auto pgraphics = pdraw2d->create_memory_graphics(this);

      _001LayoutTopText(pgraphics);

   }


   void list::_001LayoutTopText(::draw2d::graphics_pointer& pgraphics)
   {

      pgraphics->set_font(this, ::e_element_none);

      ::size_array sizea;

      m_pdcextension->get_text_extent(pgraphics, m_strTopText, sizea);
      ::rectangle_i32 rectangleClient;
      get_client_rect(rectangleClient);
      index x = 0;
      index right = rectangleClient.right;
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

      m_rectangleTopText.left = 0;
      m_rectangleTopText.top = 0;
      m_rectangleTopText.right = rectangleClient.right;
      m_rectangleTopText.bottom = (::i32)y;


   }

   void list::_001ShowTopText(bool bShow)
   {
      m_bTopText = bShow;
   }




   void list::cache_hint()
   {

      synchronous_lock synchronouslock(this->synchronization());

      if (m_pmeshcache.is_set())
      {

         auto iItemCount = m_nDisplayCount;

         auto iItemFirst = m_iTopDisplayIndex;

         m_pmeshcache->_001CacheHint(this, iItemFirst, iItemCount);

      }

   }


   void list::set_data_interface(::user::mesh_data * pmeshdata)
   {

      mesh::set_data_interface(pmeshdata);

      m_psimplelistdata = pmeshdata;

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

   //   pgraphics->set_font(this, ::e_element_none);

   //   index cx = _001CalcItemWidth(pgraphics, iItem, iSubItem);

   //   return (i32)cx;

   //}


   i32 list::_001CalcSubItemWidth(::draw2d::graphics_pointer & pgraphics, ::write_text::font * pfont, index iItem, index iSubItem)
   {

      pgraphics->set(pfont);

      return _001CalcSubItemWidth(pgraphics, iItem, iSubItem);

   }


   i32 list::_001CalcSubItemWidth(::draw2d::graphics_pointer & pgraphics, index iItem, index iSubItem)
   {

      ::image_list::info ii;

      ::rectangle_i32 rectangle;

      ::size_i32 size;

      index cx = 0;

      auto psubitem = get_subitem(iItem, iSubItem);

      //item.m_iItem = iItem;

      //item.m_iSubItem = iSubItem;

      //item.m_iListItem = -1;

      if (psubitem->m_pcolumn->m_pimagelist != nullptr)
      {

         _001GetSubItemImage(*psubitem);

         if (psubitem->m_bOk && psubitem->m_iImage >= 0)
         {

            psubitem->m_pcolumn->m_pimagelist->get_image_info((i32)psubitem->m_iImage, &ii);

            rectangle = ii.m_rectangle;

            cx += rectangle.width();

            cx += 2;

         }

      }

      _001GetSubItemText(*psubitem);

      if (psubitem->m_bOk)
      {

         pgraphics->set_font(this, ::e_element_none);

         m_pdcextension->get_text_extent(pgraphics, psubitem->m_strText, psubitem->m_strText.get_length(), size);

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
      list_column * column = m_pcolumna->get_by_config_id(key);
      if (column == nullptr)
         return -1;
      return column->m_iSubItem;
   }


   index list::config_id_index(const ::database::key & key)
   {

      return m_pcolumna->config_id_index(key);

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

      auto pointOffset = get_context_offset();

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

               set_context_offset_y(pgraphics, pointOffset.y);

               on_change_context_offset(pgraphics);

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

         auto pointOffset = get_context_offset();

         pointOffset.y = (::i32)(iItem * m_dItemHeight);

         queue_graphics_call([this, pointOffset](::draw2d::graphics_pointer & pgraphics)
            {

               set_context_offset_y(pgraphics, pointOffset.y);

               on_change_context_offset(pgraphics);

            });

         if (bRedraw)
         {

            set_need_redraw();

         }

      }

   }


   void list::_001EnsureVisible(index iItem, range & range)
   {

      auto pointOffset = get_context_offset();

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

               on_change_context_offset(pgraphics);

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
      itemrange.set(iItem, iItem, 0, m_pcolumna->get_count() - 1, -1, -1);
      m_rangeHighlight.add_item(itemrange);
      if (bRedraw)
      {
         set_need_redraw();
      }
      _001OnSelectionChange();
   }


   bool list::_001OnRemoveItem(index iItem)
   {
      __UNREFERENCED_PARAMETER(iItem);
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

      __UNREFERENCED_PARAMETER(iStrict);

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

      SetTimer(0xfffffffe, 50_ms, nullptr);

      queue_graphics_call([this](::draw2d::graphics_pointer & pgraphics)
         {

            set_context_offset(pgraphics, 0, 0);

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

      auto tickIn = ::duration::now();

      TRACE("list::Filter1Step");

      INFORMATION("tickIn = " << tickIn.integral_millisecond());

      if (!m_bFilter1)
      {

         return false;

      }

      string wstrItem;

      index iItemCount = minimum(m_nItemCount, m_iFilter1Step + 1000);

      //index iFilter1Step;

      //draw_list_item item(this);

      //for (
      //iFilter1Step = m_iFilter1Step;
      //iFilter1Step < iItemCount;
      //iFilter1Step++)
      //{
      //   for (index j = 0; j < m_pcolumna->get_count(); j++)
      //   {
      //      list_column * pcolumn = m_pcolumna->get_by_index(j);
      //      item.m_strText.Empty();
      //      item.m_iItem = iFilter1Step;
      //      item.m_iSubItem = pcolumn->m_iSubItem;
      //      item.m_iListItem = -1;
      //      _001SearchGetItemText(&item);
      //      if (item.m_bOk)
      //      {

      //         item.m_strText.make_lower();

      //         item.m_strText.find_replace("_", " ");

      //         auto presult = m_pregexFilter1->run(item.m_strText);

      //         if (presult)
      //         {

      //            if (m_eview == impact_icon)
      //            {

      //               m_piaFilterIcon->add_unique(iFilter1Step);

      //            }
      //            else
      //            {

      //               m_piaFilterMesh->add_unique(iFilter1Step);

      //            }

      //            break;

      //         }

      //      }

      //   }

      //}

      //m_iFilter1Step = (i32)iFilter1Step;

      //if (m_eview == impact_icon)
      //{
      //   m_piconlayout->m_iaDisplayToStrict = (*m_piaFilterIcon);
      //}
      //else
      //{
      //   m_pmeshlayout->m_iaDisplayToStrict = (*m_piaFilterMesh);
      //}

      //queue_graphics_call([this](::draw2d::graphics_pointer & pgraphics)
      //   {

      //      set_context_offset(pgraphics, 0, 0);

      //   });

      //m_efilterstate = FilterStateFilter;

      //set_need_layout();

      //set_need_redraw();

      //auto tickOut = ::duration::now();

      //INFORMATION("tickOut = " << integral_millisecond(tickOut));
      //INFORMATION("(delta) = " << integral_millisecond(tickOut - tickIn));

      //return m_nItemCount != iItemCount;

      return false;

   }


   void list::Filter1(const string & strFilter)
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

      auto psystem = acmesystem()->m_paxissystem;

      m_pregexFilter1 = psystem->compile_pcre("/.*" + stra.implode(".*") + ".*/i");

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
      {

         return;

      }

      _001OnSort(_001MapColumnToSubItem(iHeaderItem));

   }


   void list::_001OnListHeaderItemDblClk(index iHeaderItem)
   {

      auto psystem = acmesystem()->m_paurasystem;

      auto pdraw2d = psystem->draw2d();

      auto pgraphics = pdraw2d->create_memory_graphics(this);

      _001MaximizeColumnWidth(pgraphics, iHeaderItem);

   }


   void list::_001OnSort()
   {

      if (!m_bSortEnable)
      {

         return;

      }

      if (m_eview != impact_icon)
      {

         ::sort::quick_sort(m_pmeshlayout->m_iaDisplayToStrict, this, &list::_001Compare);

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
      //draw_list_item item1(this);
      //draw_list_item item2(this);

      //item1.m_iItem = iItem1;
      //item2.m_iItem = iItem2;
      //item1.m_iSubItem = iSubItem;
      //item2.m_iSubItem = iSubItem;

      //_001GetItemText(&item1);
      //_001GetItemText(&item2);

      //if (item1.m_bOk && item2.m_bOk)
      //{
      //   return item1.m_strText.compare_ci(item2.m_strText);
      //}
      //else
      //{
      //   if (item1.m_bOk)
      //      return 1;
      //   else if (item2.m_bOk)
      //      return -1;
      //   else
      //      return 0;
      //}

      return 0;

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

      __UNREFERENCED_PARAMETER(iColumn);

      pgraphics->set_font(this, ::e_element_none);

      i32 iMaxWidth = 0;

      ::count iCount = m_nItemCount;

      i32 iWidth;

      for (index i = 0; i < iCount; i++)
      {

         iWidth = _001CalcSubItemWidth(pgraphics, i, 0);

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

      __UNREFERENCED_PARAMETER(pgraphics);

   }


   i32 list::get_wheel_scroll_delta()
   {

      return (::i32) (3.* m_dItemHeight);

   }


   void list::on_change_context_offset(::draw2d::graphics_pointer & pgraphics)
   {

      synchronous_lock synchronouslock(this->synchronization());

      auto point = get_context_offset();

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

         ::rectangle_i32 rectangleScroll;

         auto pscrollbar = get_horizontal_scroll_bar();

         if (pscrollbar)
         {

            pscrollbar->get_window_rect(rectangleScroll);

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

      cache_hint();

      auto pointCursor = get_cursor_position();

      auto pmouse = __create_new < ::user::mouse >();

      pmouse->m_point = pointCursor;

      update_hover(pmouse);

      ::user::scroll_base::on_change_context_offset(pgraphics);

      set_need_redraw();

      post_redraw();

   }



   //::draw2d::pen * list::_001GetPenHighlight()
   //{
   //   return m_ppenHighlight;
   //}

   //::draw2d::pen * list::_001GetPenFocused()
   //{
   //   return m_ppenFocused;

   //}

   //::write_text::font * list::_001GetFont()
   //{
   //   return m_pfont;
   //}

   //::write_text::font * list::_001GetFontHover()
   //{
   //   return m_pfontHover;
   //}

   void list::on_message_mouse_leave(::message::message * pmessage)
   {
      m_iDisplayItemHover = -1;
      m_iSubItemHover = -1;
      set_need_redraw();
      pmessage->m_bRet = true;
   }


   ::item_pointer list::update_hover(::user::mouse * pmouse, bool bAvoidRedraw)
   {

      auto pitemHitTest = __new(::item);
      
      auto pointClient = screen_to_client().get(pmouse->m_point);

      bool & bAnyHoverChange = pitemHitTest->m_bAnyHoverChange;

      if (_001DisplayHitTest(pointClient, pitemHitTest->m_iItem, pitemHitTest->m_iSubItem))
      {

         if (m_iSubItemHover != pitemHitTest->m_iSubItem || m_iDisplayItemHover != pitemHitTest->m_iItem)
         {

            m_iDisplayItemHover = pitemHitTest->m_iItem;

            m_iSubItemHover = pitemHitTest->m_iSubItem;

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

      return pitemHitTest;

   }


   void list::data_get_DisplayToStrict()
   {

      if (m_eview == impact_icon)
      {

         //datastream()->get(data_get_current_sort_id() + "." + data_get_current_list_layout_id(), m_piconlayout);

      }
      else
      {

         //datastream()->get(data_get_current_sort_id() + "." + data_get_current_list_layout_id(), m_pmeshlayout);

      }

   }


   void list::data_set_DisplayToStrict()
   {
      if (m_eview == impact_icon)
      {
         //datastream()->set(data_get_current_sort_id() + "." + data_get_current_list_layout_id(), m_piconlayout);
      }
      else
      {
         //datastream()->set(data_get_current_sort_id() + "." + data_get_current_list_layout_id(), m_pmeshlayout);
      }
   }

   atom list::data_get_current_sort_id()
   {
      return data_get_sort_id(m_eview);
   }

   atom list::data_get_sort_id(EImpact eview)
   {

      return ::user::mesh::data_get_sort_id(eview);

      //__UNREFERENCED_PARAMETER(eview);
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


   list::EImpact list::_001GetImpact()
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
      //      ::pointer<::message::scroll>pscroll(pmessage);

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

      cache_hint();

   }


   atom list::data_get_current_list_layout_id()
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

            ::rectangle_i32 rectangleClient;

            get_client_rect(rectangleClient);

            index iIconSize = maximum(32, (*m_pcolumna)[0]->m_sizeIcon.cy);

            index iItemSize = iIconSize * 2;

            int iItemColumnCount = (int)maximum(1, rectangleClient.width() / iItemSize);

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

         if (m_pcolumna->get_count() == 0)
         {

            return ::size_i32(32, 32);

         }

         index iIconSize = maximum(32, (*m_pcolumna)[0]->m_sizeIcon.cy);

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

   void list::_001OnListImpactAutoArrange(::message::message * pmessage)
   {
      __UNREFERENCED_PARAMETER(pmessage);
      auto_arrange(!get_auto_arrange());
   }

   void list::_001OnUpdateListImpactAutoArrange(::message::message * pmessage)
   {
      ::pointer<::message::command>pcommand(pmessage);
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


   //void list::_001OnSelectionChange()
   //{

   //   auto ptopic = create_topic(::id_after_change_cur_sel);

   //   ptopic->m_puserelement = this;

   //   route(ptopic);

   //   set_need_redraw();

   //   post_redraw();

   //}


   void list::set_current_item(::item * pitem, const ::action_context & context)
   {

      auto iCurrentSelection = m_rangeSelection.get_current_item();

      if(iCurrentSelection >= 0)
      {

         if (::is_item(pitem, iCurrentSelection))
         {

            //return ::success;

            return;

         }

      }

      m_rangeSelection.clear();

      if (::is_set(pitem))
      {

         item_range itemrange;

         itemrange.set_lower_bound(pitem->item_index());

         itemrange.set_upper_bound(pitem->item_index());

         m_rangeSelection.add_item(itemrange);

      }

      _001OnSelectionChange();

      //return ::success;

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


   item_pointer list::current_item()
   {

      if (m_rangeSelection.get_item_count() != 1)
      {
       
         return nullptr;

      }
      
      if (m_rangeSelection.ItemAt(0).get_lower_bound() == m_rangeSelection.ItemAt(0).get_upper_bound() && m_rangeSelection.ItemAt(0).get_lower_bound() >= 0)
      {
      
         return new_item_with_index(m_rangeSelection.ItemAt(0).get_lower_bound());

      }

      return nullptr;

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
      
      __UNREFERENCED_PARAMETER(iGroup);

      return -1;

   }


   i32 list::_001GetGroupHeight(index iGroup)
   {

      i32 iListHeight = (i32)(_001GetGroupItemCount(iGroup) * m_dItemHeight);

      return maximum(m_iGroupMinHeight, iListHeight);

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

      ::pointer<::user::list_data>plistdata = create_mesh_data();

      if (plistdata.is_null())
      {

         return;

      }

      //auto estatus = 
      
      plistdata->initialize(this);

      //if (!estatus)
      //{

      //   return;

      //}

      set_data_interface(plistdata);

   }


   //void list::on_create_draw_item()
   //{

   //   m_pdrawlistitem = memory_new draw_list_item(this);

   //   m_pdrawlistitem->initialize(this);

   //   m_pdrawmeshitem = m_pdrawlistitem;

   //}


   void list::on_context_offset(::draw2d::graphics_pointer & pgraphics)
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
//            ::rectangle_i32 rectangleClient;
//
//            get_client_rect(rectangleClient);
//
//            ::rectangle_i32 rectangleClientHeader;
//
//            m_plistheader->get_client_rect(rectangleClientHeader);
//
//            m_plistheader->client_to_screen(rectangleClientHeader);
//
//            screen_to_client(rectangleClientHeader);
//
//            rectangleClient.top = rectangleClientHeader.bottom;
//
//            pgraphics->IntersectClipRect(rectangleClient);
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


   ::e_align list::get_draw_text_align(EImpact eview)
   {

      //return m_pdrawmeshitem->m_ealign;

      return ::e_align_none;

   }


   ::e_draw_text list::get_draw_text_flags(EImpact eview)
   {

      //return m_pdrawmeshitem->m_edrawtext;

      return e_draw_text_none;

   }


   //::index list::item_index(::user::interaction * pinteractionControl)
   //{

   //   m_

   //}


   ::index list::subitem_index(::user::interaction * pinteractionControl)
   {

      auto pcolumn = m_pcolumna->get_by_control(pinteractionControl);

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

      auto pcolumn = m_pcolumna->get_by_control(pinteractionControl);

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

      //   ::rectangle_i32 rectangleClient;

      //   m_plistheader->get_client_rect(rectangleClient);

      //   m_plistheader->client_to_screen(rectangleClient);

      //   screen_to_client(rectangleClient);

      //   prectangle->top += rectangleClient.bottom;


      //}

//      return true;

  // }




   void list::update_icon_list_impact_sort()
   {

      if (m_eview != impact_icon)
      {

         return;

      }

      synchronous_lock synchronouslock(this->synchronization());

      string strSort(m_pmeshdata ? m_pmeshdata->m_strMeshSort.c_str() : "");

      if (strSort.has_char())
      {

         defer_update_display();

         strSort += "-" + get_display_tag() + ".icon_list_impact_sort";

         auto pcontext = get_context();

         string str = pcontext->m_papexcontext->file().safe_get_string(strSort);
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



