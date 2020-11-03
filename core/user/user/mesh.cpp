#include "framework.h"
#if !BROAD_PRECOMPILED_HEADER
#include "core/user/user/_user.h"
#endif
#include "acme/const/timer.h"


#define DBLCLKMS 500


//CLASS_DECL_CORE index array_translate_a(index_biunique & ia, index aNew, index aOld);
//CLASS_DECL_CORE index_array array_translate_a_array(index_biunique & ia, index_array iaNew, index_array iaOld);


namespace user
{

   const UINT mesh::MESSAGE_ENDCOLUMNHEADERDRAG = WM_USER + 25;
   const UINT mesh::MESSAGE_COLUMNHEADERTRACK = WM_USER + 26;
   const UINT mesh::MESSAGE_ENDCOLUMNHEADERTRACK = WM_USER + 27;

   mesh::mesh():
      m_penFocused(e_create),
      m_penHighlight(e_create)
   {

      m_iItemHeight = 32;
      m_plist = nullptr;
      m_piaFilterIcon = new index_biunique();
      m_piaFilterMesh = new index_array();

      __construct_new(m_piconlayout);

      __construct_new(m_pmeshlayout);

      m_piconlayout->m_iaDisplayToStrict.set_empty_a(-1);
      m_piconlayout->m_iaDisplayToStrict.set_empty_b(-1);

      m_bDrag = false;
      m_eview = impact_grid;
      m_iDisplayItemFocus = -1;
      m_iDisplayItemHover = -1;
      m_iSubItemHover = -2;
      m_bSortEnable              = true;
      m_bFilter1                 = false;
      m_nColumnCount             = 1;
      m_iTimerHoverSelect = 0;

      m_pcache                   = nullptr;
      m_bTopText                 = false;

      m_bEmboss                  = true;
      m_bHoverSelect2            = true;
      m_bMultiSelect             = true;
      m_iLateralGroupWidth       = 200;

      m_pdrawmeshitem            = nullptr;

      m_bGroup                   = false;
      m_bLateralGroup            = false;

      // Simple Filter
      m_efilterstate             = FilterStateNoFilter;

      m_iGroupMinHeight          = 0;
      m_nGroupCount              = 0;
      m_nItemCount               = 0;
      m_iTopDisplayIndex                = -1;
      m_nDisplayCount            = 0;

      m_iClick = 0;

      m_iDefaultColumnWidth      = 200;

      m_bLockViewUpdate = false;


      //m_iItemHeight = 0;
      m_iItemWidth = 0;

      m_iLastItemSel = 0;
      m_iLastSubItemSel = 0;
      m_iItemSel = 0;
      m_iSubItemSel = 0;
      m_iSubItemEnter = -1;
      m_iItemEnter = -1;

      //   m_iItemCount = 0;

      m_pilGroup        = nullptr;
      m_pilGroupHover   = nullptr;


      m_iLeftMargin                       = 0;
      m_iTopMargin                        = 0;

      m_bAutoCreateMeshHeader = true;
      m_bAutoCreateMeshData = true;

      m_nGridItemCount = 0;
      m_nGridColumnCount = 0;

      //m_sizeTotal.cx = 0;
      //m_sizeTotal.cy = 0;

   }

   mesh::~mesh()
   {
      ::acme::del(m_piaFilterIcon);
      ::acme::del(m_piaFilterMesh);
   }


   void mesh::install_message_routing(::channel * pchannel)
   {

      ::user::scroll_base::install_message_routing(pchannel);

      bool bList = dynamic_cast <list *> (this) != nullptr;

      MESSAGE_LINK(e_message_size, pchannel, this,&mesh::_001OnSize);
      MESSAGE_LINK(WM_VSCROLL, pchannel, this,&mesh::_001OnVScroll);
      MESSAGE_LINK(WM_HSCROLL, pchannel, this,&mesh::_001OnHScroll);
      MESSAGE_LINK(WM_MOUSELEAVE, pchannel, this,&mesh::_001OnMouseLeave);

      if (!bList)
      {
         MESSAGE_LINK(e_message_lbutton_down, pchannel, this, &mesh::_001OnLButtonDown);
         MESSAGE_LINK(e_message_lbutton_up, pchannel, this, &mesh::_001OnLButtonUp);
         MESSAGE_LINK(WM_LBUTTONDBLCLK, pchannel, this, &mesh::_001OnLButtonDblClk);
      }
      MESSAGE_LINK(e_message_rbutton_down, pchannel, this,&mesh::_001OnRButtonDown);
      MESSAGE_LINK(e_message_rbutton_down, pchannel, this, &mesh::_001OnRButtonUp);

      MESSAGE_LINK(e_message_mouse_move, pchannel, this,&mesh::_001OnMouseMove);

      MESSAGE_LINK(WM_KEYDOWN, pchannel, this,&mesh::_001OnKeyDown);

      MESSAGE_LINK(e_message_create, pchannel, this,&mesh::_001OnCreate);

      connect_command("mesh_view_auto_arrange",&mesh::_001OnMeshViewAutoArrange);

      connect_command_probe("mesh_view_auto_arrange",&mesh::_001OnUpdateMeshViewAutoArrange);

   }


   void mesh::_001OnDraw(::draw2d::graphics_pointer & pgraphics)
   {

      m_penFocused->create_solid(2,ARGB(255,0,255,255));

      m_penHighlight->create_solid(2,ARGB(255,0,255,255));

      pgraphics->set_text_rendering_hint(::draw2d::text_rendering_hint_anti_alias_grid_fit);

      if(m_bLockViewUpdate)
         return;

      ::user::interaction::_001OnDraw(pgraphics);

      draw_framing(pgraphics);

      ::rect rectClient;

      get_client_rect(rectClient);


      auto pointScroll = get_viewport_offset();


      //      pgraphics->SetBkMode(TRANSPARENT);

      if(m_bTopText)
      {

         auto pstyle = get_style(pgraphics);

         ::draw2d::brush_pointer brushText(e_create);

         brushText->create_solid(get_color(pstyle, ::user::element_text));

         const ::point & pointViewportOrg = pgraphics->GetViewportOrg();

         pgraphics->set(brushText);
         ::size_array sizea;
         m_dcextension.GetTextExtent(pgraphics,m_strTopText,sizea);
         index x = 0;
         index right = (index)rectClient.right;
         index y = m_iItemHeight;
         index iStart = 0;
         index iNewStart = 0;
         index w;
         for(index i = 0; i < sizea.get_size(); i++)
         {

            if((sizea[i].cx - x > right)
                  || i == sizea.get_upper_bound())
            {
               ::rect rect;
               rect.top = LONG(y - pointScroll.y);
               if(i == 0)
               {
                  w = sizea[0].cx - x      ;
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
               rect.left = LONG(- pointScroll.x);
               rect.right = rectClient.right;
               rect.bottom = LONG(y - pointScroll.y);

               pgraphics->_DrawText(m_strTopText.Mid(iStart,i - iStart),rect,e_align_left);
               iStart = iNewStart;
            }
         }
         pgraphics->SetViewportOrg(pointViewportOrg);
      }


//      if(m_pmeshdata != nullptr)
//      {
//         if(m_pmeshdata->is_locked())
//         {
//            return;
//         }
//      }




      m_pdrawmeshitem->m_pgraphics              = pgraphics;
      m_pdrawmeshitem->m_iItemRectItem          = -1;
      m_pdrawmeshitem->m_iSubItemRectOrder      = -1;
      m_pdrawmeshitem->m_iSubItemRectSubItem    = -1;
      m_pdrawmeshitem->m_iSubItemRectItem       = -1;
      m_pdrawmeshitem->m_iSubItemRectColumn     = -1;
//      m_pdrawmeshitem->m_iWidthColumn           = -1;
      m_pdrawmeshitem->m_iColumnWidth           = 0;

      ::rect rectItem;
      ::rect rectIntersect;
      auto iItemCount = m_nDisplayCount;
      auto iItemFirst = m_iTopDisplayIndex;
      decltype(iItemCount) iItemLast;
      if(m_eview == impact_icon)
      {
         iItemLast = iItemCount;
      }
      else
      {
         iItemLast = min(m_nItemCount - 1,iItemFirst + m_nDisplayCount - 1);
      }

      if(iItemFirst < 0)
         return;

      _001DrawItems(m_pdrawmeshitem, (::index) iItemFirst, (::index) iItemLast);

      if(m_bGroup && m_bLateralGroup)
      {

         index iGroupFirst = 0;
         index iGroupFirstTopIndex = 0;
         for(; iGroupFirst < m_nGroupCount; iGroupFirst++)
         {
            if(iItemFirst >= iGroupFirstTopIndex && iItemFirst < (iGroupFirstTopIndex + _001GetGroupItemCount((::index) iGroupFirst)))
               break;
         }
         index iGroupLast = iGroupFirst;
         index iGroupLastTopIndex = iGroupFirstTopIndex;
         for(; iGroupLast < m_nGroupCount; iGroupLast++)
         {
            if(iItemLast >= iGroupLastTopIndex && iItemLast < (iGroupLastTopIndex + _001GetGroupItemCount((::index) iGroupLast)))
               break;
         }

         _001DrawGroups(m_pdrawmeshitem, (::index) iGroupFirst, (::index) iGroupLast, (::index) iItemFirst, (::index) iItemLast);
      }


   }



















   void mesh::_001DrawGroups(draw_mesh_item * pdrawitem,index iGroupFirst,index iGroupLast,index iItemFirst,index iItemLast)
   {

      UNREFERENCED_PARAMETER(iItemFirst);
      UNREFERENCED_PARAMETER(iItemLast);

      index iGroup;

      ::rect rectClient;

      ::rect rectIntersect;

      get_client_rect(rectClient);

      bool bHoverFont = false;

      pdrawitem->m_pgraphics->set_font(this);

      m_pdrawmeshitem->m_pfont = pdrawitem->m_pgraphics->m_pfont;

      for(iGroup = iGroupFirst; iGroup <= iGroupLast; iGroup++)
      {

         m_pdrawmeshitem->m_iGroup          = iGroup;

         _001GetGroupRect(m_pdrawmeshitem);

         if(!m_pdrawmeshitem->m_bOk)
            continue;

         if(!rectIntersect.intersect(m_pdrawmeshitem->m_rectItem,rectClient))
            continue;

         if(iGroup == m_iGroupHover)
         {
            
            if(!bHoverFont)
            {
               
               pdrawitem->m_pgraphics->set_font(this, ::user::e_state_hover);

            }

         }
         else
         {
            
            if(bHoverFont)
            {

               pdrawitem->m_pgraphics->set_font(this);

            }

         }

         _001DrawGroup(m_pdrawmeshitem);

      }

   }



















   void mesh::_001DrawGroup(draw_mesh_item * pdrawitem)
   {

      /*if(m_bGroupCustomDraw)
      {
      pdrawitem->m_bMeshSubItemHover = pdrawitem->m_bListItemHover && (pdrawitem->m_iSubItem == m_iSubItemHover);
      pdrawitem->m_bFocus = false;
      return;
      }*/

      _001GetElementRect(pdrawitem,::user::mesh::element_group_image);
      if(pdrawitem->m_bOk)
      {
         pdrawitem->draw_group_image();
      }

      ::count nItem = _001GetGroupMetaItemCount((::index) pdrawitem->m_iGroup);

      for(pdrawitem->m_iItem = 0; pdrawitem->m_iItem < nItem; pdrawitem->m_iItem++)
      {
         _001GetElementRect(pdrawitem,::user::mesh::element_group_item_text);
         if(pdrawitem->m_bOk)
         {
            _001GetGroupText(pdrawitem);
            pdrawitem->draw_text();
         }
      }



   }
















   void mesh::_001DrawItems(draw_mesh_item * pdrawitem,index iItemFirst,index iItemLast)
   {

      ::rect rectClient;

      get_client_rect(rectClient);

      ::rect rectVisible(rectClient);

      //rectVisible.deflate(2,2);

      ::rect rectIntersect;

      if(m_eview == impact_icon)
      {

         m_pdrawmeshitem->m_ealign = e_align_top_center;

         m_pdrawmeshitem->m_edrawtext = { e_draw_text_end_ellipsis, e_draw_text_word_break };
      }
      else
      {
         
         m_pdrawmeshitem->m_ealign = e_align_left_center;

         m_pdrawmeshitem->m_edrawtext = { e_draw_text_end_ellipsis, e_draw_text_single_line };

      }

      bool bHoverFont = false;

      pdrawitem->m_pgraphics->set_font(this);

      pdrawitem->m_pfont = pdrawitem->m_pgraphics->m_pfont;

      index iDisplayItem;

      for(iDisplayItem = iItemFirst; iDisplayItem <= iItemLast; iDisplayItem++)
      {

         m_pdrawmeshitem->m_iItem           = _001DisplayToStrict(iDisplayItem);

         m_pdrawmeshitem->m_iDisplayItem    = iDisplayItem;

         if(m_bGroup)
         {

            m_pdrawmeshitem->m_iGroupTopDisplayIndex = 0;

            for(m_pdrawmeshitem->m_iGroup = 0; m_pdrawmeshitem->m_iGroup < m_nGroupCount; m_pdrawmeshitem->m_iGroup++)
            {

               m_pdrawmeshitem->m_iGroupCount = _001GetGroupItemCount((::index) m_pdrawmeshitem->m_iGroup);

               if(iDisplayItem >= m_pdrawmeshitem->m_iGroupTopDisplayIndex && iDisplayItem < (m_pdrawmeshitem->m_iGroupTopDisplayIndex + m_pdrawmeshitem->m_iGroupCount))
               {

                  break;

               }

            }

         }

         _001GetItemRect(m_pdrawmeshitem);

         if(!m_pdrawmeshitem->m_bOk)
         {

            continue;

         }

         if(!rectIntersect.intersect(m_pdrawmeshitem->m_rectItem,rectVisible))
         {

            continue;

         }

         if(iDisplayItem == m_iDisplayItemHover)
         {

            if(!bHoverFont)
            {

               bHoverFont = true;

               pdrawitem->m_pgraphics->set_font(this, ::user::e_state_hover);

            }

         }
         else
         {

            if(bHoverFont)
            {

               bHoverFont = false;

               pdrawitem->m_pgraphics->set_font(this);

            }

         }

         _001DrawItem(m_pdrawmeshitem);

      }

   }


   void mesh::_001DrawItem(draw_mesh_item * pdrawitem)
   {

      pdrawitem->m_iState = 0;

      range & rangeSelection = m_rangeSelection;
      range & rangeHighlight = m_rangeHighlight;

      ::rect rectClient;

      get_client_rect(rectClient);

      if(pdrawitem->m_iItem < 0)
         return;

      pdrawitem->m_bListItemHover = pdrawitem->m_iDisplayItem == m_iDisplayItemHover &&
                                    (m_eview != impact_icon ||
                                     ((m_piconlayout->m_iaDisplayToStrict.get_a((::index) m_iDisplayItemHover) >= 0 && m_piconlayout->m_iaDisplayToStrict.get_a((::index) m_iDisplayItemHover) < m_nItemCount)));

      if(pdrawitem->m_bListItemHover)
      {
         pdrawitem->m_pgraphics->fill_rect(pdrawitem->m_rectItem,ARGB(128,255,255,255));
         pdrawitem->m_pgraphics->set_font(this, ::user::e_state_hover);
      }
      else
      {
         pdrawitem->m_pgraphics->set_font(this);
      }
//      pdrawitem->m_pgraphics->set_font(pfont);

      pdrawitem->m_bListItemSelected = (m_eview != impact_icon || is_valid_display_item((::index) pdrawitem->m_iItem)) && rangeSelection.has_item((::index) pdrawitem->m_iDisplayItem);

      if(pdrawitem->m_bListItemHover)
         pdrawitem->m_iState |= ItemStateHover;
      if(pdrawitem->m_bListItemSelected)
         pdrawitem->m_iState |= ItemStateSelected;

      auto psession = Session;

      if(pdrawitem->m_bListItemSelected)
      {
         if(psession->savings().is_trying_to_save(::e_resource_processing))
         {
            pdrawitem->m_pgraphics->fill_rect(pdrawitem->m_rectItem,ARGB(255,96,96,96));
         }
         else
         {
            COLORREF crTranslucid = RGB(0,0,0);
            ::rect rect = pdrawitem->m_rectItem;
            rect.inflate(8,0,8,-1);
            System.imaging().color_blend(pdrawitem->m_pgraphics,rect,crTranslucid,127);
         }
      }

      pdrawitem->update_item_color();
      pdrawitem->set_text_color();

      string str;

      index iColumnCount;

      if(m_eview == impact_icon)
      {
         iColumnCount = 1;
      }
      else
      {
         iColumnCount = m_nColumnCount;
      }

      pdrawitem->m_iSubItemRectOrder      = -1;
      pdrawitem->m_iSubItemRectSubItem    = -1;
      pdrawitem->m_iSubItemRectColumn     = -1;

      ::rect rectIntersect;

      if(m_eview == impact_grid)
      {

         pdrawitem->m_iOrder = max(get_viewport_offset().x, 0);

      }
      else
      {

         pdrawitem->m_iOrder = 0;

      }

      for(; pdrawitem->m_iOrder < iColumnCount; pdrawitem->m_iOrder++)
      {


         pdrawitem->m_iColumn    = _001MapOrderToColumn((::index) pdrawitem->m_iOrder);


         if(pdrawitem->m_iColumn < 0)
            continue;


         _001GetSubItemRect(pdrawitem);

         if(!rectIntersect.intersect(m_pdrawmeshitem->m_rectSubItem,rectClient))
            break;

         if(!pdrawitem->m_bOk)
            continue;


         _001DrawSubItem(pdrawitem);

      }
      if(rangeHighlight.has_item((::index) pdrawitem->m_iDisplayItem))
      {
         ::draw2d::pen_pointer penHighlight(e_create);
         ::draw2d::pen * ppenHighlight = _001GetPenHighlight();
         ::rect rectHighlight(pdrawitem->m_rectItem);
         rectHighlight.inflate(8,0,8,-1);
         pdrawitem->m_pgraphics->set(ppenHighlight);
         pdrawitem->m_pgraphics->draw_rect(rectHighlight);
      }



   }

   void mesh::draw_framing(::draw2d::graphics_pointer & pgraphics)
   {

   }


   void   mesh::_001DrawSubItem(draw_mesh_item * pdrawitem)
   {


      pdrawitem->m_iListItem = -1;
      _001GetElementRect(pdrawitem,::user::mesh::element_image);
      if(pdrawitem->m_bOk)
      {
         try
         {
            _001GetItemImage(pdrawitem);
         }
         catch(...)
         {
            pdrawitem->m_bOk = false;
         }
         pdrawitem->draw_image();
      }
      pdrawitem->m_iListItem = -1;
      _001GetElementRect(pdrawitem,::user::mesh::element_text);
      if(pdrawitem->m_bOk)
      {
         try
         {
            _001GetItemText(pdrawitem);
         }
         catch(...)
         {
            pdrawitem->m_bOk = false;
         }
         if(pdrawitem->m_bOk)
         {
            pdrawitem->draw_text();
         }
      }

   }




   void mesh::_001GetItemImage(::user::mesh_item * pitem)
   {

      if(m_pmeshdata != nullptr)
      {

         pitem->m_pmesh = this;
         try
         {
            return m_pmeshdata->_001GetItemImage(pitem);
         }
         catch(...)
         {
            TRACE("_001GetItemImage exception");
         }
      }
      /*LVITEM lvi;
      lvi.mask = LVIF_IMAGE;
      lvi.iItem = iItem;
      lvi.iSubItem = 0;
      get_item(&lvi);
      return lvi.iImage;*/
      pitem->m_bOk = false;
   }

   void mesh::_001SetItemText(::user::mesh_item * pitem)
   {

      pitem->m_bOk = false;

   }

   void mesh::_001GetItemText(::user::mesh_item * pitem)
   {
      pitem->m_bOk = false;
      if(m_pcache != nullptr)
      {
         m_pcache->_001GetItemText(pitem);
         if(pitem->m_bOk)
            return;
      }
      if(m_pmeshdata != nullptr)
      {
         m_pmeshdata->_001GetItemText(pitem);
      }
   }

   // Purpose:
   // Provide Item Text for Search Purposes.
   void mesh::_001SearchGetItemText(::user::mesh_item * pitem)
   {
      _001GetItemText(pitem);
   }




   /*bool mesh::pre_create_window(::user::create_struct& cs)
   {

   //cs.style |= LVS_NOSCROLL;

   return window::pre_create_window(cs);
   }*/

   /*void mesh::OnSize(UINT nType, index cx, index cy)
   {
   window::OnSize(nType, cx, cy);

   set_need_layout();
   }*/

   void mesh::_001OnSize(::message::message * pmessage)
   {
      UNREFERENCED_PARAMETER(pmessage);
      //SCAST_PTR(::message::size,psize,pmessage);
      //set_need_layout();
      //psize->m_bRet = false;
   }


   void mesh::on_layout(::draw2d::graphics_pointer & pgraphics)
   {

      sync_lock sl(mutex());

      if(m_bTopText)
      {

         _001LayoutTopText(pgraphics);

      }

      m_iTopDisplayIndex       = _001CalcDisplayTopIndex();

      if(m_eview == impact_grid)
      {

         m_iItemWidth      = (::i32) (m_nColumnCount * m_iDefaultColumnWidth);

      }

      index iLow = 0;

      for(m_iTopGroup = 0; m_iTopGroup < m_nGroupCount; m_iTopGroup++)
      {

         if(m_iTopDisplayIndex >= iLow && m_iTopDisplayIndex < (iLow + _001GetGroupItemCount((::index) m_iTopGroup)))
            break;

      }

      m_nDisplayCount   = _001CalcDisplayItemCount();

      on_change_view_size();


      //if (m_eview == impact_icon)
      //{
      //   //            if(m_piconlayout->m_iWidth <= 0)
      //   {
      //      ::rect rectClient;
      //      get_client_rect(rectClient);
      //      index iIconSize;
      //      if (m_nColumnCount > 0)
      //         //                  iIconSize = max(32,m_columna[0]->m_sizeIcon.cy);
      //         iIconSize = 32;
      //      else
      //         iIconSize = 32;
      //      index iItemSize = iIconSize * 2;
      //      m_piconlayout->m_iWidth = (i32)(max(1, rectClient.width() / iItemSize));
      //   }
      //}


   }



   bool mesh::_001OnUpdateColumnCount(u32 dwFlags)
   {

      UNREFERENCED_PARAMETER(dwFlags);

      if(m_eview == impact_grid)
      {

         ::rect rectClient;

         get_client_rect(rectClient);

         ::size sizePage = rectClient.size();

         m_nGridColumnCount = _001GetColumnCount();

         m_nColumnCount = max(m_nColumnCount,sizePage.cx * 2);

         m_nColumnCount = min(m_nColumnCount,m_nGridColumnCount);

      }
      else
      {

         m_nColumnCount = _001GetColumnCount();

      }

      if(m_nColumnCount < 0)
      {

         return false;

      }

      set_need_layout();

      return true;

   }


   bool mesh::_001OnUpdateItemCount(u32 dwFlags)
   {

      sync_lock sl(mutex());

      UNREFERENCED_PARAMETER(dwFlags);

      if(m_eview == impact_grid)
      {

         ::rect rectClient;

         get_client_rect(rectClient);

         ::size sizePage = rectClient.size();

         m_nGridItemCount = _001GetItemCount();

         m_nItemCount = max(m_nItemCount, sizePage.cy * 2);

         m_nItemCount = min(m_nItemCount,m_nGridItemCount);

      }
      else
      {

         m_nItemCount = _001GetItemCount();

      }

      if(m_nItemCount < 0)
      {

         return false;

      }

      if(m_bGroup)
      {

         m_nGroupCount = _001GetGroupCount();

         if(m_nGroupCount < 0)
         {

            return false;

         }

      }

      if(m_eview == impact_icon)
      {
         for(index iStrict = 0; iStrict < m_nItemCount; iStrict++)
         {
            if(m_piconlayout->m_iaDisplayToStrict.get_a(iStrict) == -1)
            {
               m_piconlayout->m_iaDisplayToStrict.set(m_piconlayout->m_iaDisplayToStrict.get_free_a(),iStrict);
            }
         }
      }
      else
      {
         index iStart = m_pmeshlayout->m_iaDisplayToStrict.get_count();
         index iEnd = m_nItemCount - 1;
         m_pmeshlayout->m_iaDisplayToStrict.allocate((::count) m_nItemCount);
         for(index iStrict = iStart; iStrict <= iEnd; iStrict++)
         {
            m_pmeshlayout->m_iaDisplayToStrict.set_at((::index) iStrict, (::index) iStrict);
         }
      }

      if(m_bFilter1)
      {
         FilterApply();
      }

      CacheHint();

      on_change_view_size();

      //TRACE("mesh::_001OnUpdateItemCount ItemCount %d\n",m_nItemCount);
      //if(m_bGroup)
      //{
        // TRACE("mesh::_001OnUpdateItemCount GroupCount %d\n",m_nGroupCount);
      //}

      return true;
   }


   void mesh::on_change_view_size()
   {

      ::size sizeTotal = get_total_size();

      if(m_eview == impact_grid)
      {

         sizeTotal.cy = (LONG) m_nColumnCount;
         sizeTotal.cx = (LONG) m_nItemCount;

      }
      else if(m_eview == impact_list)
      {
         if(m_nItemCount == 0)
         {
            sizeTotal.cy = 0;
            sizeTotal.cx = 0;
         }
         else
         {

            ::rect rectClient;

            get_client_rect(&rectClient);

            sizeTotal.cy = rectClient.height();

            draw_mesh_item itemFirst(this);

            itemFirst.m_iItem          = 0;
            itemFirst.m_iDisplayItem   = 0;

            _001GetItemRect(&itemFirst);


            if(m_iItemHeight <= 0)
               sizeTotal.cx = rectClient.right;
            else
               sizeTotal.cx  = (LONG)min(
                               m_nItemCount * itemFirst.m_rectItem.width() * m_iItemHeight /
                               rectClient.height()
                               + itemFirst.m_rectItem.width(),MAXLONG);
         }
      }
      else if(m_eview == impact_report)
      {
         if(m_nItemCount == 0)
         {
            sizeTotal.cy = 0;
            sizeTotal.cx = 0;
         }
         else
         {

            ::rect rect;

            draw_mesh_item itemFirst(this);

            itemFirst.m_iItem             = 0;
            itemFirst.m_iDisplayItem      = 0;
            itemFirst.m_iGroup            = 0;
            _001GetItemRect(&itemFirst);

            draw_mesh_item itemLast(this);

            if(m_bFilter1)
            {
               itemLast.m_iDisplayItem       = m_piaFilterMesh->get_count() - 1;
               itemLast.m_iItem              = m_piaFilterMesh->get_count() - 1;
            }
            else
            {
               itemLast.m_iDisplayItem       = m_nItemCount - 1;
               itemLast.m_iItem              = m_nItemCount - 1;
            }
            if(m_bGroup)
            {
               itemLast.m_iGroupTopDisplayIndex = 0;
               //               i32 igroup;
               for(itemLast.m_iGroup = 0; itemLast.m_iGroup < m_nGroupCount; itemLast.m_iGroup++)
               {
                  itemLast.m_iGroupCount = _001GetGroupItemCount((::index) itemLast.m_iGroup);
                  if(itemLast.m_iItem >= itemLast.m_iGroupTopDisplayIndex && itemLast.m_iItem < (itemLast.m_iGroupTopDisplayIndex + itemLast.m_iGroupCount))
                     break;
               }
            }
            _001GetItemRect(&itemLast);

//            itemLast.m_rectItem.right     -= (m_scrolldata.m_rectMargin.left + m_scrolldata.m_rectMargin.right);
            //          itemLast.m_rectItem.bottom    -= (m_scrolldata.m_rectMargin.top + m_scrolldata.m_rectMargin.bottom);

            rect.unite(itemFirst.m_rectItem,itemLast.m_rectItem);

            sizeTotal = rect.size();

         }

      }
      else if(m_eview == impact_icon)
      {

         ::rect rect;

         draw_mesh_item itemFirst(this);

         itemFirst.m_iItem             = 0;
         itemFirst.m_iDisplayItem      = 0;

         _001GetItemRect(&itemFirst);

         draw_mesh_item itemLast(this);

         itemLast.m_iDisplayItem       = m_nItemCount - 1;
         itemLast.m_iItem              = m_nItemCount - 1;

         _001GetItemRect(&itemLast);

         draw_mesh_item itemTopRight(this);
//         if(m_flags.has(flag_auto_arrange) || m_piconlayout->m_iWidth <= 0)
         {
            ::rect rectClient;

            get_client_rect(&rectClient);

            itemTopRight.m_iItem = (index)max(1,rectClient.width() / get_item_size().cx) - 1;
         }
         /*       else
                {
                   itemTopRight.m_iItem = max(1,m_piconlayout->m_iWidth) - 1;
                }
         */       itemTopRight.m_iDisplayItem = itemTopRight.m_iDisplayItem;
         _001GetItemRect(&itemTopRight);

         rect.unite(itemFirst.m_rectItem,itemLast.m_rectItem);

         rect.unite(rect,itemTopRight.m_rectItem);

         sizeTotal = rect.size();

      }

//      ::user::box::on_change_view_size();

   }


   void mesh::_001OnInitialize()
   {

   }





   void mesh::_thread_data_update_visible_subitem()
   {

      return;

//      sync_lock sl(&m_mutexData);

//      index iColumn;

//      index_array iaVisible;


   }



   void mesh::_001GetColumnWidth(draw_mesh_item * pitem)
   {

      int iWidth;

      if(!m_mapColumnWidth.lookup((::index) pitem->m_iColumn,iWidth))
      {

         iWidth = m_iDefaultColumnWidth;

      }

      pitem->m_iColumnWidth   = iWidth;

      pitem->m_bOk            = true;

   }


   index mesh::_001MapSubItemToOrder(index iSubItem)
   {
      return _001MapColumnToOrder(_001MapSubItemToColumn(iSubItem));
   }

   index mesh::_001MapOrderToSubItem(index iOrder)
   {
      return _001MapColumnToSubItem(_001MapOrderToColumn(iOrder));
   }


   index mesh::_001MapOrderToColumn(index iOrder)
   {

      if(iOrder >= _001GetColumnCount())
      {

         return -1;

      }

      if(iOrder < 0)
      {

         return -1;

      }

      return iOrder;

   }


   index mesh::_001MapColumnToOrder(index iColumn)
   {

      if(iColumn >= _001GetColumnCount())
      {

         return -1;

      }

      if(iColumn < 0)
      {

         return -1;

      }

      return iColumn;

   }

   index mesh::_001MapSubItemToColumn(index iSubItem)
   {

      if(iSubItem >= _001GetColumnCount())
      {

         return -1;

      }

      if(iSubItem < 0)
      {

         return -1;

      }

      return iSubItem;

   }

   index mesh::_001MapColumnToSubItem(index iColumn)
   {

      if(iColumn >= _001GetColumnCount())
      {

         return -1;

      }

      if(iColumn < 0)
      {

         return -1;

      }

      return iColumn;
   }


   ::count mesh::_001GetItemCount()
   {

      if(m_pmeshdata.is_null())
         return -1;

      return m_pmeshdata->_001GetItemCount();

   }


   ::count mesh::_001GetGroupCount()
   {

      if(m_pmeshdata.is_null())
         return -1;

      return m_pmeshdata->_001GetGroupCount();

   }

   /////////////////////////////////////////////////////////////////
   //
   // Function: _001CalcDisplayTopIndex
   // Old Name: _001GetTopIndex
   //
   // Purpose:
   // Return the index of the first visible item in the mesh
   //
   // Output:
   // The index of the first visible item in the mesh
   //
   //
   /////////////////////////////////////////////////////////////////
   index mesh::_001CalcDisplayTopIndex()
   {


      if(m_eview == impact_grid)
      {

         return (::index) min(max(0,get_viewport_offset().y),m_nGridItemCount);

      }
      else
      {

         auto pointScroll = get_viewport_offset();

         index iItem;

         if(_001DisplayHitTest(::point(pointScroll.x < 0 ? -pointScroll.x : 0,m_iItemHeight + (pointScroll.y < -0 ? -pointScroll.y : 0)),iItem))
         {

            return (::index) iItem;

         }
         else
         {

            if(m_eview == impact_report || m_eview == impact_grid)
            {

               if(pointScroll.y < 0)
               {

                  return 0;

               }

            }

            return -1;

         }

      }

   }

   ::count mesh::_001CalcDisplayItemCount()
   {

      if(m_eview == impact_grid)
      {

         ::rect rectScroll;

         get_client_rect(&rectScroll);

         if(m_iItemHeight == 0)
         {

            return 0;

         }
         else
         {

            if(m_bTopText)
            {
               return rectScroll.height() - m_rectTopText.height() / m_iItemHeight;
            }
            else
            {
               return rectScroll.height();
            }

         }

      }
      if(m_eview == impact_icon)
      {
         ::rect rectView;
         get_client_rect(&rectView);
         const ::size & sizeItem = get_item_size();
         return max((rectView.width() / sizeItem.cx) * (rectView.height() / sizeItem.cy),
                    m_piconlayout->m_iaDisplayToStrict.get_max_a() + 1);
      }
      else if(m_eview == impact_report || m_eview == impact_grid)
      {
         ::rect rectView;
         get_client_rect(&rectView);
         if(m_iItemHeight == 0)
         {
            return 0;
         }
         else
         {
            if(m_bTopText)
            {
               return (rectView.height() - m_rectTopText.height()) / m_iItemHeight;
            }
            else
            {
               return rectView.height() / m_iItemHeight;
            }
         }
      }

      index iItemCount;
      if(m_bFilter1 && (m_eview == impact_list || m_eview == impact_report || m_eview == impact_grid))
      {
         iItemCount = m_piaFilterMesh->get_count();
      }
      else
      {
         iItemCount = m_nItemCount;
      }
      index iItemFirst = m_iTopDisplayIndex;
      index iItemLast = iItemFirst;
      ::rect rectItem;
      ::rect rectIntersect;
      ::rect rectUpdate;
      get_client_rect(&rectUpdate);
      draw_mesh_item item(this);
      if(iItemFirst >= 0)
      {
         iItemLast = -1;
         for(index i = iItemFirst + 1; i < iItemCount; i++)
         {
            item.m_iItem         = i;
            item.m_iDisplayItem  = i;
            if(m_bGroup)
            {
               item.m_iGroupTopDisplayIndex = 0;
               for(item.m_iGroup = 0; item.m_iGroup < m_nGroupCount; item.m_iGroup++)
               {
                  item.m_iGroupCount = _001GetGroupItemCount((::index) item.m_iGroup);
                  if(i >= item.m_iGroupTopDisplayIndex && i < (item.m_iGroupTopDisplayIndex + item.m_iGroupCount))
                     break;
               }
            }

            _001GetItemRect(&item);
            if(item.m_bOk)
            {
               if(!rectIntersect.intersect(item.m_rectItem,rectUpdate))
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
         if(iItemLast < 0)
            iItemLast = iItemCount - 1;
         return iItemLast - iItemFirst + 1;
      }
      else
      {
         return 0;
      }

   }


   bool mesh::_001HitTest_(const ::point & point,index &iItem, index&iSubItem, index&iListItem,::user::mesh::e_element &eelement)
   {
      UNREFERENCED_PARAMETER(point);
      UNREFERENCED_PARAMETER(iItem);
      UNREFERENCED_PARAMETER(iSubItem);
      UNREFERENCED_PARAMETER(iListItem);
      UNREFERENCED_PARAMETER(eelement);
      return false;
   }


   bool mesh::_001HitTest_(const ::point & point,index &iItem, index&iSubItem)
   {

      if (!_001DisplayHitTest(point, iItem, iSubItem))
      {

         return false;

      }

      iItem = _001DisplayToStrict((::index) iItem);

      return true;

   }


   bool mesh::_001HitTest_(const ::point & point, index& iItem)
   {

      if (!_001DisplayHitTest(point, iItem))
      {

         return false;

      }

      iItem = (::index) _001DisplayToStrict((::index) iItem);

      return true;

   }


   bool mesh::_001DisplayHitTest(const ::point & point, index& iItem, index& iSubItem, index& iListItem,::user::mesh::e_element &eelement)
   {

      UNREFERENCED_PARAMETER(point);
      UNREFERENCED_PARAMETER(iItem);
      UNREFERENCED_PARAMETER(iSubItem);
      UNREFERENCED_PARAMETER(iListItem);
      UNREFERENCED_PARAMETER(eelement);

      return false;

   }


   bool mesh::_001DisplayHitTest(const ::point & point, index&iItemParam, index&iSubItemParam)
   {

      index iItem;

      if(!_001DisplayHitTest(point,iItem))
      {

         return false;

      }

      auto pointScroll = get_viewport_offset();

      if(m_eview == impact_icon || m_eview == impact_list)
      {

         iItemParam = iItem;
         if(iItem == -1)
         {
            iSubItemParam = -1;
         }
         else
         {
            iSubItemParam = 0;
         }
         return true;
      }
      index iColumnCount = m_nColumnCount;
      i32 iLeft =(i32)pointScroll.x;
      if(m_bGroup && m_bLateralGroup)
         iLeft += m_iLateralGroupWidth;
      i32 iRight;
      draw_mesh_item item(this);
      if(point.x < iLeft)
         return false;
      for(item.m_iColumn = 0; item.m_iColumn < iColumnCount; item.m_iColumn++)
      {
         _001GetColumnWidth(&item);
         if(!item.m_bOk)
            continue;
         iRight = iLeft + item.m_iColumnWidth;
         if(iLeft <= point.x && point.x < iRight)
         {
            iItemParam = iItem;
            iSubItemParam = _001MapColumnToSubItem(item.m_iColumn);
            return true;
         }
         iLeft = iRight;
      }
      return false;
   }

   bool mesh::_001DisplayHitTest(const ::point & point, index&iItemParam)
   {

      {

         ::rect rectClient;

         get_client_rect(&rectClient);

         if(point.x < 0
               || point.x > rectClient.right
               || point.y < 0
               || point.y > rectClient.bottom)
         {

            return false;

         }

      }

      auto pointScroll = get_viewport_offset();

      if(m_eview == impact_report || m_eview == impact_grid)
      {
         index iy = point.y + pointScroll.y;

         index iItem = -1;

         if(m_iItemHeight != 0)
            iItem = iy / m_iItemHeight;

         if(iItem < 0)
            return false;

         //if(m_bHeaderCtrl)
         //{
         iItem--;

         if(iItem < 0)
            return false;
         //}

         if(m_bFilter1)
         {
            if(iItem >= m_piaFilterMesh->get_count())
               return false;
         }

         if(iItem >= m_nItemCount)
            return false;

         iItemParam = (index)iItem;

         return true;
      }
      else if(m_eview == impact_list)
      {
         if(m_iItemHeight <= 0)
            return false;

         ::rect rectClient;
         get_client_rect(&rectClient);
         if(m_bTopText)
         {
            rectClient.top += m_rectTopText.height();
         }
         //if(m_bHeaderCtrl)
         //{
         //   rectClient.top += m_iItemHeight;
         //}
         index iRoundHeight = (index)((rectClient.height() / m_iItemHeight) * m_iItemHeight);

         index iy = (index)((point.y + pointScroll.y) + (((point.x + pointScroll.x) / m_iItemWidth)) * iRoundHeight);

         index iItem = -1;

         if(m_iItemHeight != 0)
            iItem = iy / m_iItemHeight;

         if(iItem < 0)
            return false;

         //if(m_bHeaderCtrl)
         //{
         //   iItem--;

         //   if(iItem < 0)
         //      return false;
         //}

         if(m_bFilter1)
         {
            if(iItem >= m_piaFilterMesh->get_count())
               return false;
         }

         if(iItem >= m_nItemCount)
            return false;

         iItemParam = iItem;

         return true;

      }
      else if(m_eview == impact_icon)
      {
         /*if(_001GetColumnCount() == 0)
            return false;
         */::rect rectClient;
         get_client_rect(&rectClient);
         if(m_bTopText)
         {
            rectClient.top += m_rectTopText.height();
         }
//         index iIconSize = max(32,m_columna[0]->m_sizeIcon.cy);
         index iIconSize = 32;
         index iItemSize = iIconSize * 2;

         index ix = (index)(point.x + pointScroll.x);
         ix = (index)max(pointScroll.x,ix);
         ix = (index)min(rectClient.right,ix);
         ix = (index)max(rectClient.left,ix);
         ix /= iItemSize;

         index iy = point.y + pointScroll.y;
         iy = max(pointScroll.y,iy);
         iy = max(rectClient.top,iy);
         iy /= iItemSize;

         //if(m_flags.has(flag_auto_arrange))
         {
            iItemParam = iy * (max(1,rectClient.width() / iItemSize)) + ix;
         }
         //else
         {
            // iItemParam = iy * (max(1,m_piconlayout->m_iWidth)) + ix;
         }


         return true;
      }

      return false;
   }

   void mesh::_001GetGroupRect(::user::draw_mesh_item * pdrawitem)
   {
      if(pdrawitem->m_iGroup < 0)
         return_(pdrawitem->m_bOk,false);
      if(pdrawitem->m_iGroup >= m_nGroupCount)
         return_(pdrawitem->m_bOk,false);
      index iItemFirst = 0;
      index iItemLast = _001GetGroupItemCount(0) - 1;
      pdrawitem->m_iGroupRectGroup = 0;
      while(pdrawitem->m_iGroupRectGroup < pdrawitem->m_iGroup)
      {
         pdrawitem->m_iGroupRectGroup++;
         iItemFirst = iItemLast + 1;
         iItemLast = iItemFirst + _001GetGroupItemCount(pdrawitem->m_iGroupRectGroup) - 1;
      }

      draw_mesh_item itemFirst(this);

      itemFirst.m_iItem             = _001DisplayToStrict(iItemFirst);
      itemFirst.m_iDisplayItem      = iItemFirst;
      itemFirst.m_iGroup            = pdrawitem->m_iGroupRectGroup;

      _001GetItemRect(&itemFirst);

      draw_mesh_item itemLast(this);

      itemLast.m_iDisplayItem       = _001DisplayToStrict(iItemLast);
      itemLast.m_iItem              = iItemLast;
      itemLast.m_iGroup             = pdrawitem->m_iGroupRectGroup;

      _001GetItemRect(&itemLast);

      pdrawitem->m_rectGroup.unite(itemFirst.m_rectItem,itemLast.m_rectItem);
      pdrawitem->m_rectGroup.bottom = max(itemLast.m_rectItem.bottom,itemFirst.m_rectItem.top + m_iGroupMinHeight);
      pdrawitem->m_rectGroup.left = 0;
      pdrawitem->m_rectGroup.right = m_iLateralGroupWidth;
      pdrawitem->m_bOk = true;
   }

   void mesh::_001GetItemRect(::user::draw_mesh_item * pdrawitem)
   {

      if(pdrawitem->m_iDisplayItem == (-1 - pdrawitem->m_iItemRectItem) && pdrawitem->m_iItemRectItem >= 0)
      {
         return_(pdrawitem->m_bOk,false);
      }

      if(pdrawitem->m_iDisplayItem == pdrawitem->m_iItemRectItem)
      {
         return_(pdrawitem->m_bOk,true);
      }

      if(pdrawitem->m_iDisplayItem < 0)
      {
         pdrawitem->m_rectItem.left = 0;
         pdrawitem->m_rectItem.top = 0;
         pdrawitem->m_rectItem.right = 0;
         pdrawitem->m_rectItem.bottom = 0;
         pdrawitem->m_iItemRectItem = (-1 - pdrawitem->m_iDisplayItem);
         return_(pdrawitem->m_bOk,false);
      }
      if(m_eview == impact_icon && pdrawitem->m_iDisplayItem >= m_nDisplayCount)
      {
         pdrawitem->m_rectItem.left = 0;
         pdrawitem->m_rectItem.top = 0;
         pdrawitem->m_rectItem.right = 0;
         pdrawitem->m_rectItem.bottom = 0;
         pdrawitem->m_iItemRectItem = (-1 - pdrawitem->m_iDisplayItem);
         return_(pdrawitem->m_bOk,false);
      }

      auto pointScroll = get_viewport_offset();

      if(m_eview == impact_grid)
      {

         if(m_bGroup)
         {

            if(m_bLateralGroup)
            {

               if(pdrawitem->m_iItemRectItem < 0)
               {

                  pdrawitem->m_rectItem.left    = (LONG) m_iLateralGroupWidth;
                  pdrawitem->m_rectItem.right   = (LONG)(pdrawitem->m_rectItem.left + m_iItemWidth);
                  pdrawitem->m_iItemRectItem = 0;
                  pdrawitem->m_rectItem.top  = 0;
                  //if(m_bHeaderCtrl)
                  //{
                  //   pdrawitem->m_rectItem.top += m_iItemHeight;
                  //}
                  if(m_bTopText)
                  {
                     pdrawitem->m_rectItem.top += m_rectTopText.height();
                  }
                  pdrawitem->m_rectItem.bottom = pdrawitem->m_rectItem.top + m_iItemHeight;
                  pdrawitem->m_rectItem.offset(-pointScroll.x,-pointScroll.y);
               }

               if(pdrawitem->m_iDisplayItem > pdrawitem->m_iItemRectItem)
               {
                  i32 iOffset                               = (i32)((pdrawitem->m_iItemRectItem - pdrawitem->m_iGroupTopDisplayIndex) * m_iItemHeight);
                  pdrawitem->m_rectItem.top                -= iOffset;
                  pdrawitem->m_rectItem.bottom              = pdrawitem->m_rectItem.top + m_iItemHeight;
                  while(pdrawitem->m_iGroupTopDisplayIndex + pdrawitem->m_iGroupCount < pdrawitem->m_iDisplayItem)
                  {
                     //                     i32 iHeight                            = _001GetGroupHeight(pdrawitem->m_iGroup);
                     pdrawitem->m_rectItem.top             += iOffset;
                     pdrawitem->m_rectItem.bottom           = pdrawitem->m_rectItem.top + m_iItemHeight;
                     if((pdrawitem->m_iGroup + 1) >= m_nGroupCount)
                     {
                        break;
                     }
                     pdrawitem->m_iGroup++;
                     pdrawitem->m_iGroupTopDisplayIndex            += pdrawitem->m_iGroupCount;
                     pdrawitem->m_iGroupCount               = _001GetGroupItemCount(pdrawitem->m_iGroup);
                     pdrawitem->m_iItemRectItem             = pdrawitem->m_iGroupTopDisplayIndex;
                  }
               }
               else
               {
                  i32 iOffset                               = (i32)((pdrawitem->m_iItemRectItem - pdrawitem->m_iGroupTopDisplayIndex) * m_iItemHeight);
                  pdrawitem->m_rectItem.top                -= iOffset;
                  pdrawitem->m_rectItem.bottom              = pdrawitem->m_rectItem.top + m_iItemHeight;
                  while(pdrawitem->m_iGroupTopDisplayIndex + pdrawitem->m_iGroupCount > pdrawitem->m_iDisplayItem)
                  {
                     if((pdrawitem->m_iGroup - 1) < 0)
                     {
                        break;
                     }
                     pdrawitem->m_iGroup--;
                     i32 iHeight                         = _001GetGroupHeight(pdrawitem->m_iGroup);
                     pdrawitem->m_rectItem.top          -= iHeight;
                     pdrawitem->m_rectItem.bottom        = pdrawitem->m_rectItem.top + m_iItemHeight;
                     pdrawitem->m_iGroupCount            = _001GetGroupItemCount(pdrawitem->m_iGroup);
                     pdrawitem->m_iGroupTopDisplayIndex        -= pdrawitem->m_iGroupCount;
                     pdrawitem->m_iItemRectItem          = pdrawitem->m_iGroupTopDisplayIndex;
                  }
               }
               if(pdrawitem->m_iGroup < m_nGroupCount && pdrawitem->m_iGroup >= 0)
               {
                  pdrawitem->m_iItemRectItem       = pdrawitem->m_iDisplayItem;
                  pdrawitem->m_rectItem.top       += (LONG)((pdrawitem->m_iItemRectItem - pdrawitem->m_iGroupTopDisplayIndex) * m_iItemHeight);
                  pdrawitem->m_rectItem.bottom     =  pdrawitem->m_rectItem.top + m_iItemHeight;
               }
            }
            else
            {
               ::exception::throw_not_implemented();
            }
         }
         else
         {

            pdrawitem->m_rectItem.left    = m_iLeftMargin;

            pdrawitem->m_rectItem.right   = (LONG)(m_iLeftMargin + m_iItemWidth);

            pdrawitem->m_rectItem.top = 0;
            //if(m_bHeaderCtrl)
            //{
            //   pdrawitem->m_rectItem.top += m_iItemHeight;
            //}
            pdrawitem->m_rectItem.top += (LONG)(m_iItemHeight * pdrawitem->m_iDisplayItem);
            if(m_bTopText)
            {
               pdrawitem->m_rectItem.top += m_rectTopText.height();
            }
            pdrawitem->m_rectItem.bottom = pdrawitem->m_rectItem.top + m_iItemHeight;
            pdrawitem->m_rectItem.offset(0,m_iTopMargin -pointScroll.y * m_iItemHeight);
            pdrawitem->m_iItemRectItem = pdrawitem->m_iDisplayItem;
         }
      }
      else if(m_eview == impact_report)
      {

         if(m_bGroup)
         {

            if(m_bLateralGroup)
            {

               if(pdrawitem->m_iItemRectItem < 0)
               {

                  pdrawitem->m_rectItem.left    = (LONG)m_iLateralGroupWidth;
                  pdrawitem->m_rectItem.right   = (LONG)(pdrawitem->m_rectItem.left + m_iItemWidth);
                  pdrawitem->m_iItemRectItem = 0;
                  pdrawitem->m_rectItem.top  = 0;
                  //if(m_bHeaderCtrl)
                  //{
                  //   pdrawitem->m_rectItem.top += m_iItemHeight;
                  //}
                  if(m_bTopText)
                  {
                     pdrawitem->m_rectItem.top += m_rectTopText.height();
                  }
                  pdrawitem->m_rectItem.bottom = pdrawitem->m_rectItem.top + m_iItemHeight;
                  pdrawitem->m_rectItem.offset(-pointScroll.x,-pointScroll.y);
               }

               if(pdrawitem->m_iDisplayItem > pdrawitem->m_iItemRectItem)
               {
                  i32 iOffset                               = (i32)((pdrawitem->m_iItemRectItem - pdrawitem->m_iGroupTopDisplayIndex) * m_iItemHeight);
                  pdrawitem->m_rectItem.top                -= iOffset;
                  pdrawitem->m_rectItem.bottom              = pdrawitem->m_rectItem.top + m_iItemHeight;
                  while(pdrawitem->m_iGroupTopDisplayIndex + pdrawitem->m_iGroupCount < pdrawitem->m_iDisplayItem)
                  {
                     //                     i32 iHeight                            = _001GetGroupHeight(pdrawitem->m_iGroup);
                     pdrawitem->m_rectItem.top             += iOffset;
                     pdrawitem->m_rectItem.bottom           = pdrawitem->m_rectItem.top + m_iItemHeight;
                     if((pdrawitem->m_iGroup + 1) >= m_nGroupCount)
                     {
                        break;
                     }
                     pdrawitem->m_iGroup++;
                     pdrawitem->m_iGroupTopDisplayIndex            += pdrawitem->m_iGroupCount;
                     pdrawitem->m_iGroupCount               = _001GetGroupItemCount(pdrawitem->m_iGroup);
                     pdrawitem->m_iItemRectItem             = pdrawitem->m_iGroupTopDisplayIndex;
                  }
               }
               else
               {
                  i32 iOffset                               = (i32)((pdrawitem->m_iItemRectItem - pdrawitem->m_iGroupTopDisplayIndex) * m_iItemHeight);
                  pdrawitem->m_rectItem.top                -= iOffset;
                  pdrawitem->m_rectItem.bottom              = pdrawitem->m_rectItem.top + m_iItemHeight;
                  while(pdrawitem->m_iGroupTopDisplayIndex + pdrawitem->m_iGroupCount > pdrawitem->m_iDisplayItem)
                  {
                     if((pdrawitem->m_iGroup - 1) < 0)
                     {
                        break;
                     }
                     pdrawitem->m_iGroup--;
                     i32 iHeight                         = _001GetGroupHeight(pdrawitem->m_iGroup);
                     pdrawitem->m_rectItem.top          -= iHeight;
                     pdrawitem->m_rectItem.bottom        = pdrawitem->m_rectItem.top + m_iItemHeight;
                     pdrawitem->m_iGroupCount            = _001GetGroupItemCount(pdrawitem->m_iGroup);
                     pdrawitem->m_iGroupTopDisplayIndex        -= pdrawitem->m_iGroupCount;
                     pdrawitem->m_iItemRectItem          = pdrawitem->m_iGroupTopDisplayIndex;
                  }
               }
               if(pdrawitem->m_iGroup < m_nGroupCount && pdrawitem->m_iGroup >= 0)
               {
                  pdrawitem->m_iItemRectItem       = pdrawitem->m_iDisplayItem;
                  pdrawitem->m_rectItem.top       += (LONG)((pdrawitem->m_iItemRectItem - pdrawitem->m_iGroupTopDisplayIndex) * m_iItemHeight);
                  pdrawitem->m_rectItem.bottom     =  pdrawitem->m_rectItem.top + m_iItemHeight;
               }
            }
            else
            {
               ::exception::throw_not_implemented();
            }
         }
         else
         {
            pdrawitem->m_rectItem.left    = 0;
            pdrawitem->m_rectItem.right   = (LONG)m_iItemWidth;

            pdrawitem->m_rectItem.top = 0;
            //if(m_bHeaderCtrl)
            //{
            //   pdrawitem->m_rectItem.top += m_iItemHeight;
            //}
            pdrawitem->m_rectItem.top += (LONG)(m_iItemHeight * pdrawitem->m_iDisplayItem);
            if(m_bTopText)
            {
               pdrawitem->m_rectItem.top += m_rectTopText.height();
            }
            pdrawitem->m_rectItem.bottom = pdrawitem->m_rectItem.top + m_iItemHeight;
            pdrawitem->m_rectItem.offset(-pointScroll.x,-pointScroll.y);
            pdrawitem->m_iItemRectItem   = pdrawitem->m_iDisplayItem;
         }
      }
      else if(m_eview == impact_list)
      {
         ::rect rectClient;
         get_client_rect(&rectClient);
         if(m_bTopText)
         {
            rectClient.top += m_rectTopText.height();
         }
         //if(m_bHeaderCtrl)
         //{
         //   rectClient.top += m_iItemHeight;
         //}
         if(m_iItemHeight <= 0)
            return_(pdrawitem->m_bOk,false);
         index iRoundHeight = (rectClient.height() / m_iItemHeight) * m_iItemHeight;
         if(iRoundHeight != 0)
         {
            pdrawitem->m_rectItem.left = (LONG)(((pdrawitem->m_iItem * m_iItemHeight) / iRoundHeight) * m_iItemWidth);
            pdrawitem->m_rectItem.top = (LONG)((pdrawitem->m_iItem * m_iItemHeight) % iRoundHeight);
         }
         if(m_bTopText)
         {
            pdrawitem->m_rectItem.top += m_rectTopText.height();
         }
         //if(m_bHeaderCtrl)
         //{
         //   pdrawitem->m_rectItem.top += m_iItemHeight;
         //}
         pdrawitem->m_rectItem.bottom = (LONG)(pdrawitem->m_rectItem.top + m_iItemHeight);
         pdrawitem->m_rectItem.right = (LONG)(pdrawitem->m_rectItem.left + m_iItemWidth);
         pdrawitem->m_rectItem.offset(-pointScroll.x,-pointScroll.y);
      }
      else if(m_eview == impact_icon)
      {
//         if(m_flags.has(flag_auto_arrange) || m_piconlayout->m_iWidth <= 0)
         {
            ::rect rectClient;
            get_client_rect(&rectClient);
            if(m_bTopText)
            {
               rectClient.top += m_rectTopText.height();
            }
            //index iIconSize = max(32,m_columna[0]->m_sizeIcon.cy);
            index iIconSize = 32;
            index iItemSize = iIconSize * 2;
            pdrawitem->m_rectItem.left = (LONG)(iItemSize * (pdrawitem->m_iItem % (max(1,rectClient.width() / iItemSize))));
            pdrawitem->m_rectItem.top = (LONG)(iItemSize * (pdrawitem->m_iItem / (max(1,rectClient.width() / iItemSize))));
            pdrawitem->m_rectItem.bottom = (LONG)(pdrawitem->m_rectItem.top + iItemSize);
            pdrawitem->m_rectItem.right = (LONG)(pdrawitem->m_rectItem.left + iItemSize);
         }
         //else
         //{
         //   ::rect rectClient;
         //   get_client_rect(&rectClient);
         //   if(m_bTopText)
         //   {
         //      rectClient.top += m_rectTopText.height();
         //   }
         //   index iItemSize = get_item_size().cy;
         //   pdrawitem->m_rectItem.left = (LONG)(iItemSize * (pdrawitem->m_iDisplayItem % m_piconlayout.m_iWidth));
         //   pdrawitem->m_rectItem.top = (LONG)(rectClient.top + iItemSize * (pdrawitem->m_iDisplayItem / m_piconlayout.m_iWidth));
         //   pdrawitem->m_rectItem.bottom = (LONG)(pdrawitem->m_rectItem.top + iItemSize);
         //   pdrawitem->m_rectItem.right = (LONG)(pdrawitem->m_rectItem.left + iItemSize);
         //}
         pdrawitem->m_rectItem.offset(-pointScroll.x,-pointScroll.y);
      }

      pdrawitem->m_bOk = true;

   }

   void mesh::_001GetSubItemRect(::user::draw_mesh_item * pdrawitem)
   {

      if(pdrawitem->m_iDisplayItem != pdrawitem->m_iItemRectItem)
      {
         _001GetItemRect(pdrawitem);
         if(!pdrawitem->m_bOk)
            return;
      }

      if(pdrawitem->m_iSubItemRectOrder == pdrawitem->m_iOrder)
      {
         if(pdrawitem->m_iSubItemRectItem != pdrawitem->m_iItemRectItem)
         {
            pdrawitem->m_rectSubItem.top     = pdrawitem->m_rectItem.top;
            pdrawitem->m_rectSubItem.bottom  = pdrawitem->m_rectItem.bottom;
         }
         return_(pdrawitem->m_bOk,true);
      }

      if(m_eview == impact_icon)
      {

         pdrawitem->m_rectSubItem     = pdrawitem->m_rectItem;

         return_(pdrawitem->m_bOk,true);

         //return;
         //__throw(::exception::exception("subitem rectangle on icon view? why are you asking for that now?"));
      }

      pdrawitem->m_bOk = false;

      pdrawitem->m_rectSubItem.top     = pdrawitem->m_rectItem.top;
      pdrawitem->m_rectSubItem.bottom  = pdrawitem->m_rectItem.bottom;

      index iLastOrder = m_nColumnCount - 1;

      if(iLastOrder < 0)
         return_(pdrawitem->m_bOk,false);



      if(pdrawitem->m_iSubItemRectOrder < 0 || pdrawitem->m_iOrder == 0 || pdrawitem->m_iSubItemRectOrder > pdrawitem->m_iOrder)
      {

         if(m_eview == impact_grid)
         {

            pdrawitem->m_iSubItemRectOrder         = pdrawitem->m_iOrder;

         }
         else
         {

            pdrawitem->m_iSubItemRectOrder         = 0;

         }

         pdrawitem->m_rectSubItem.left          = pdrawitem->m_rectItem.left;
         pdrawitem->m_iSubItemRectColumn        = _001MapOrderToColumn(0);
         pdrawitem->m_iColumn                    = pdrawitem->m_iSubItemRectColumn;
         _001GetColumnWidth(pdrawitem);
         pdrawitem->m_rectSubItem.right         = pdrawitem->m_rectItem.left + pdrawitem->m_iColumnWidth;
         pdrawitem->m_iSubItemRectItem          = pdrawitem->m_iItemRectItem;
         pdrawitem->m_iSubItemRectSubItem       = pdrawitem->m_iSubItem;
         if(pdrawitem->m_iOrder == 0)
         {
            pdrawitem->m_bOk = true;
            return;
         }
      }

      if(pdrawitem->m_iOrder <= iLastOrder)
      {
         while(pdrawitem->m_iSubItemRectOrder < pdrawitem->m_iOrder)
         {
            pdrawitem->m_iColumn           = _001MapOrderToColumn(pdrawitem->m_iSubItemRectOrder);
            _001GetColumnWidth(pdrawitem);
            pdrawitem->m_rectSubItem.left       += pdrawitem->m_iColumnWidth;
            pdrawitem->m_iSubItemRectOrder++;
         }
         pdrawitem->m_iColumn = _001MapOrderToColumn(pdrawitem->m_iSubItemRectOrder);
         pdrawitem->m_iSubItemRectColumn        = pdrawitem->m_iColumn;
         _001GetColumnWidth(pdrawitem);
         pdrawitem->m_rectSubItem.right         = pdrawitem->m_rectSubItem.left + pdrawitem->m_iColumnWidth;
         pdrawitem->m_iSubItemRectOrder         = pdrawitem->m_iOrder;
         pdrawitem->m_iSubItemRectItem          = pdrawitem->m_iItemRectItem;
         pdrawitem->m_iSubItemRectSubItem       = pdrawitem->m_iSubItem;
         pdrawitem->m_bOk = true;
      }

   }

   void mesh::_001GetElementRect(::user::draw_mesh_item * pdrawitem,::user::mesh::e_element eelement)
   {

      if(m_bGroup && m_bLateralGroup &&
            (eelement == ::user::mesh::element_group_image
             || eelement == ::user::mesh::element_group_item_text))
      {
         i32 x = pdrawitem->m_rectGroup.left;
         i32 iImageBottom = pdrawitem->m_rectGroup.top;

         if(m_pilGroup != nullptr)
         {


            ::image_list::info ii;

            _001GetGroupImage(pdrawitem);
            if(pdrawitem->m_bOk && pdrawitem->m_iImage >= 0)
            {
               m_pilGroup->get_image_info((i32)pdrawitem->m_iImage,&ii);
               if(eelement == ::user::mesh::element_group_image)
               {
                  pdrawitem->m_rectImage.left      = x;
                  pdrawitem->m_rectImage.right     = x + ii.m_rect.width();
                  pdrawitem->m_rectImage.top       = pdrawitem->m_rectGroup.top;
                  pdrawitem->m_rectImage.bottom    = pdrawitem->m_rectImage.top + ii.m_rect.height();
                  return_(pdrawitem->m_bOk,true);
               }
               else
               {
                  x += ii.m_rect.width();
                  x += 2;
                  iImageBottom += ii.m_rect.height() + 2;
               }
            }
            else if(eelement == ::user::mesh::element_group_image)
            {
               return_(pdrawitem->m_bOk,false);
            }

         }
         else if(eelement == ::user::mesh::element_group_image)
         {
            return_(pdrawitem->m_bOk,false);
         }
         if(eelement == ::user::mesh::element_group_item_text)
         {
            pdrawitem->m_rectText.top       = (LONG)(pdrawitem->m_rectGroup.top + m_iItemHeight * pdrawitem->m_iItem);
            if(pdrawitem->m_rectText.top >= iImageBottom)
            {
               pdrawitem->m_rectText.left      = pdrawitem->m_rectGroup.left;
            }
            else
            {
               pdrawitem->m_rectText.left      = x;
            }
            pdrawitem->m_rectText.right     = pdrawitem->m_rectGroup.right;
            pdrawitem->m_rectText.bottom    = pdrawitem->m_rectText.top + m_iItemHeight;
            return_(pdrawitem->m_bOk,true);
         }
         pdrawitem->m_bOk = false;
      }
      else
      {
         if(pdrawitem->m_iDisplayItem != pdrawitem->m_iItemRectItem)
         {
            _001GetItemRect(pdrawitem);
            if(!pdrawitem->m_bOk)
               return;
         }
         if(eelement == ::user::mesh::element_item)
         {
            return_(pdrawitem->m_bOk,true);
         }
         if(m_eview == impact_icon)
         {
            if(eelement == ::user::mesh::element_image)
            {
               i32 iIconSize                  = 32;
               pdrawitem->m_rectImage.left      = pdrawitem->m_rectItem.left + iIconSize / 2;
               pdrawitem->m_rectImage.top       = pdrawitem->m_rectItem.top;
               pdrawitem->m_rectImage.right     = pdrawitem->m_rectImage.left + iIconSize;
               pdrawitem->m_rectImage.bottom    = pdrawitem->m_rectImage.top + iIconSize;
               return_(pdrawitem->m_bOk,true);
            }
            else if(eelement == ::user::mesh::element_text)
            {
               i32 iIconSize               = 32;
               pdrawitem->m_rectText.left    = pdrawitem->m_rectItem.left;
               pdrawitem->m_rectText.top     = pdrawitem->m_rectItem.top + iIconSize;
               pdrawitem->m_rectText.right   = pdrawitem->m_rectText.left + iIconSize * 2;
               pdrawitem->m_rectText.bottom  = pdrawitem->m_rectText.top + iIconSize;
               return_(pdrawitem->m_bOk,true);
            }
            return_(pdrawitem->m_bOk,false);
         }

         _001GetSubItemRect(pdrawitem);

         if(!pdrawitem->m_bOk)
            return;

         i32 x = pdrawitem->m_rectSubItem.left;

         if(pdrawitem->m_iListItem == -1)
         {
            if(eelement == ::user::mesh::element_sub_item)
            {
               return_(pdrawitem->m_bOk,true);
            }
            //if(pdrawitem->m_pcolumnSubItemRect->m_bIcon)
            //{
            //   _001GetItemImage(pdrawitem);
            //   if(pdrawitem->m_bOk && pdrawitem->m_iImage >= 0)
            //   {
            //      if(eelement == ::user::mesh::element_image)
            //      {
            //         pdrawitem->m_rectImage.left      = x;
            //         pdrawitem->m_rectImage.right     = x + pdrawitem->m_pcolumnSubItemRect.m_sizeIcon.cx;
            //         pdrawitem->m_rectImage.bottom    = pdrawitem->m_rectSubItem.bottom;
            //         pdrawitem->m_rectImage.top       = pdrawitem->m_rectImage.bottom - pdrawitem->m_pcolumnSubItemRect.m_sizeIcon.cx;
            //         return_(pdrawitem->m_bOk,true);
            //      }
            //      else
            //      {
            //         x += pdrawitem->m_pcolumnSubItemRect->m_sizeIcon.cx;
            //         x += 2;
            //      }
            //   }
            //   else if(eelement == ::user::mesh::element_image)
            //   {
            //      return_(pdrawitem->m_bOk,false);
            //   }
            //}
            //else if(pdrawitem->m_pcolumnSubItemRect->m_pil != nullptr)
            //{

            //   ::image_list::info ii;

            //   _001GetItemImage(pdrawitem);
            //   if(pdrawitem->m_bOk && pdrawitem->m_iImage >= 0)
            //   {
            //      pdrawitem->m_pcolumnSubItemRect->m_pil->get_image_info((i32)pdrawitem->m_iImage,&ii);
            //      if(eelement == ::user::mesh::element_image)
            //      {
            //         pdrawitem->m_rectImage.left      = x;
            //         pdrawitem->m_rectImage.right     = x + ii.m_rect.width();
            //         pdrawitem->m_rectImage.bottom    = pdrawitem->m_rectSubItem.bottom;
            //         pdrawitem->m_rectImage.top       = pdrawitem->m_rectImage.bottom - ii.m_rect.height();
            //         return_(pdrawitem->m_bOk,true);
            //      }
            //      else
            //      {
            //         x += ii.m_rect.width();
            //         x += 2;
            //      }
            //   }
            //   else if(eelement == ::user::mesh::element_image)
            //   {
            //      return_(pdrawitem->m_bOk,false);
            //   }

            //}
            else if(eelement == ::user::mesh::element_image)
            {
               return_(pdrawitem->m_bOk,false);
            }
            if(eelement == ::user::mesh::element_text)
            {
               pdrawitem->m_rectText.left      = x;
               pdrawitem->m_rectText.right     = pdrawitem->m_rectSubItem.right;
               pdrawitem->m_rectText.top       = pdrawitem->m_rectSubItem.top;
               pdrawitem->m_rectText.bottom    = pdrawitem->m_rectSubItem.bottom;
               return_(pdrawitem->m_bOk,true);
            }
         }
         pdrawitem->m_bOk = false;
      }

   }




   void mesh::_001OnKeyDown(::message::message * pmessage)
   {

      SCAST_PTR(::message::key,pkey,pmessage);

      if (pkey->previous()) // give chance to child
      {

         return;

      }

      if(pkey->m_ekey == ::user::key_down || pkey->m_ekey == ::user::key_up ||
            pkey->m_ekey == ::user::key_next || pkey->m_ekey == ::user::key_prior)
      {

         if(m_nItemCount > 0)
         {

            range range = m_rangeSelection;

            m_rangeSelection.clear();

            index iItem = m_iDisplayItemFocus;

            if(iItem < 0)
            {
               if(pkey->m_ekey == ::user::key_down || pkey->m_ekey == ::user::key_next)
               {
                  iItem = 0;
               }
               else if(pkey->m_ekey == ::user::key_up || pkey->m_ekey == ::user::key_prior)
               {
                  iItem = m_nItemCount - 1;
               }
            }
            else
            {
               if(pkey->m_ekey == ::user::key_down)
               {
                  iItem++;
               }
               else if(pkey->m_ekey == ::user::key_next)
               {
                  iItem += m_nDisplayCount;
               }
               else if(pkey->m_ekey == ::user::key_up)
               {
                  iItem--;
               }
               else if(pkey->m_ekey == ::user::key_prior)
               {
                  iItem -= m_nDisplayCount;
               }
               else
               {
                  ASSERT(FALSE);
                  pmessage->m_bRet = false;
                  return;
               }
            }

            if(iItem < 0)
            {
               iItem = m_nItemCount - 1;
            }
            else if(iItem >= m_nItemCount)
            {
               iItem = 0;
            }

            m_iShiftFirstSelection = iItem;
            m_iDisplayItemFocus = iItem;

            item_range itemrange;
//            itemrange.set(iItem,iItem,0,m_nColumnCount - 1,- 1,-1);
            itemrange.set(iItem,iItem,0,m_nColumnCount - 1,- 1,-1);
            m_rangeSelection.add_item(itemrange);

            _001EnsureVisible(iItem,range);

            //range.add_item(itemrange);

            set_need_redraw();

            _001OnSelectionChange();
         }
      }
      else if(pkey->m_ekey == ::user::key_delete)
      {

         ::user::range range;

         _001GetSelection(range);

         _001DeleteRange(range);

         pmessage->m_bRet = true;

      }

      pmessage->m_bRet = false;

   }


   void mesh::_001OnMouseMove(::message::message * pmessage)
   {

      SCAST_PTR(::message::mouse, pmouse, pmessage);

      pmouse->m_lresult = 1;

      ::point point = pmouse->m_point;

      _001ScreenToClient(point);

      pmouse->previous(); // give chance to child control

      sync_lock sl(mutex());

      auto psession = Session;

      if (m_bDrag)
      {

         if (!m_bLButtonDown)
         {

            m_bDrag = false;

         }
         else if (pmouse->m_nFlags == 0)
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
      else if(m_bHoverSelect2)
      {

         if (m_bLButtonDown)
         {

            bool bShouldStartDrag = d_distance(point, m_pointLButtonDown1) > m_iItemHeight;

            if (bShouldStartDrag)
            {

               m_bDrag = true;

            }

         }

      }

      track_mouse_leave();

      {

         update_hover(psession->get_cursor_pos());

         pmessage->m_bRet = true;

         index iItemEnter;

         index iSubItemEnter;

         if (_001DisplayHitTest(point, iItemEnter, iSubItemEnter))
         {

            if (m_bSelect && m_bHoverSelect2 &&
                  (m_iSubItemEnter != iSubItemEnter ||
                   m_iItemEnter != iItemEnter)
                  && !m_rangeSelection.has_item((::index) iItemEnter))
            {

               m_iMouseFlagEnter = pmouse->m_nFlags;

               m_iItemEnter = iItemEnter;

               m_iSubItemEnter = iSubItemEnter;

               m_iTimerHoverSelect = 0;

            }

         }

      }

   }


   void mesh::_001OnLButtonDown(::message::message * pmessage)
   {

      SCAST_PTR(::message::mouse, pmouse, pmessage);

      pmouse->previous(); // give chance to child control and to base views

      m_bLButtonDown = true;

      SetCapture();

      index iItem;

      ::point point = pmouse->m_point;

      _001ScreenToClient(point);

      if(dynamic_cast < list * >(this) == nullptr)
      {

         auto tickNow = ::tick::now();

         if(tickNow - m_tickLButtonDownStart2 < DBLCLKMS)
         {

            m_tickLButtonDownStart1 = m_tickLButtonDownStart2;

            m_tickLButtonDownStart2 = tickNow;

            m_pointLButtonDown1 = m_pointLButtonDown2;

            m_pointLButtonDown2 = point;

            m_iClick = 2;

         }
         else if(tickNow - m_tickLButtonDownStart1 < DBLCLKMS)
         {

            m_tickLButtonDownStart2 = tickNow;

            m_pointLButtonDown2 = point;

            m_iClick = 2;

         }
         else
         {

            m_tickLButtonDownStart1 = tickNow;

            m_pointLButtonDown1 = point;

            m_iClick = 1;

         }

      }

      if (!has_focus())
      {

         SetFocus();

      }

      auto psession = Session;

      psession->set_keyboard_focus(this);

      psession->user()->set_mouse_focus_LButtonDown(this);

      if (!_001DisplayHitTest(point, m_iDisplayItemLButtonDown1))
      {

         m_iDisplayItemLButtonDown1 = -1;

      }

      if(m_bSelect)
      {

         if(m_bHoverSelect2)
         {

            if(_001DisplayHitTest(point,iItem))
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

               // const ::point & point = point;

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

            if(m_bMultiSelect && psession->is_key_pressed(::user::key_shift))
            {

               if(_001DisplayHitTest(point,iItem))
               {

                  item_range itemrange;

                  index iLItem = min(m_iShiftFirstSelection,iItem);

                  index iUItem = max(m_iShiftFirstSelection,iItem);

                  itemrange.set(iLItem,iUItem,0,m_nColumnCount - 1,- 1,-1);

                  _001AddSelection(itemrange);

                  m_iShiftFirstSelection = iItem;

                  _001OnSelectionChange();

               }

            }
            else if(m_bMultiSelect && psession->is_key_pressed(::user::key_control))
            {

               if(_001DisplayHitTest(point,iItem))
               {

                  item_range itemrange;

                  index iLItem = min(m_iShiftFirstSelection,iItem);

                  index iUItem = max(m_iShiftFirstSelection,iItem);

                  itemrange.set(iLItem,iUItem,0,m_nColumnCount - 1,- 1,-1);

                  _001AddSelection(itemrange);

                  m_iShiftFirstSelection = iItem;

                  _001OnSelectionChange();

               }

            }
            else
            {

               m_rangeSelection.clear();

               index iItem;

               if(_001DisplayHitTest(point,iItem))
               {

                  m_iShiftFirstSelection = iItem;

                  m_iDisplayItemFocus = iItem;

                  _001DisplayHitTest(point, m_iDisplayItemLButtonDown1);

                  m_uiLButtonDownFlags = pmouse->m_nFlags;

                  m_pointLButtonDown1 = point;

                  SetTimer(e_timer_drag_start, 1200, nullptr);

                  item_range itemrange;

                  itemrange.set(iItem,iItem,0,m_nColumnCount - 1,- 1,-1);

                  _001AddSelection(itemrange);

               }

               _001OnSelectionChange();

            }

         }

      }

      set_need_redraw();

      pmessage->m_bRet = true;

      pmouse->m_lresult = 1;

   }


   void mesh::_001OnLButtonUp(::message::message * pmessage)
   {

      SCAST_PTR(::message::mouse, pmouse, pmessage);

      ::point point = pmouse->m_point;

      _001ScreenToClient(point);

      ReleaseCapture();

      if (m_bDrag)
      {

         m_bDrag = false;

         if (m_eview != impact_icon)
         {

            index iDisplayItemDrop;

            if (_001DisplayHitTest(point, iDisplayItemDrop))
            {

               if (m_iDisplayItemLButtonDown1 != iDisplayItemDrop && iDisplayItemDrop != -1)
               {

                  m_pmeshlayout->m_iaDisplayToStrict.__swap(m_iDisplayItemLButtonDown1, iDisplayItemDrop);

                  _001OnAfterSort();

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

                  if(m_iClick == 1)
                  {

                     on_click(iDisplayItemLButtonUp);

                  }
                  else
                  {

                     send_message(WM_LBUTTONDBLCLK, pmouse->m_nFlags, MAKELPARAM(point.x, point.y));

                  }

               }

            }

         }

      }

      pmessage->m_bRet = true;

      pmouse->m_lresult = 1;

      m_bLButtonDown = false;

   }


   void mesh::_001OnRButtonDown(::message::message * pmessage)
   {

      SCAST_PTR(::message::mouse, pmouse, pmessage);

      pmouse->previous();

      ::point point = pmouse->m_point;

      _001ScreenToClient(point);

      if(!has_focus())
      {

         SetFocus();

      }

      auto psession = Session;

      if(psession->is_key_pressed(::user::key_shift))
      {

      }
      else if(psession->is_key_pressed(::user::key_control))
      {

      }
      else
      {

         index iItem;
         if(_001DisplayHitTest(point,iItem))
         {
            if(!m_rangeSelection.has_item(iItem))
            {
               m_rangeSelection.clear();
               m_iShiftFirstSelection = iItem;
               item_range itemrange;
               itemrange.set(iItem,iItem,0,m_nColumnCount - 1,- 1,-1);
               _001AddSelection(itemrange);
               set_need_redraw();
            }
         }
      }


      pmessage->m_bRet = true;
   }


   void mesh::_001OnRButtonUp(::message::message * pmessage)
   {

      SCAST_PTR(::message::mouse, pmouse, pmessage);

      pmouse->previous();

      ::point point = pmouse->m_point;

      _001ScreenToClient(point);

      if (!has_focus())
      {

         SetFocus();

      }

      _001OnRightClick(pmouse->m_nFlags, point);


      pmessage->m_bRet = true;

   }


   bool mesh::on_click(const ::user::item & item)
   {

      ::user::control_event ev;

      ev.m_puie = this;

      ev.m_eevent = ::user::event_list_clicked;

      on_control_event(&ev);

      /*if(m_pformcallback != nullptr)
      {

         m_p->on_control_event(&ev);

      }
      else if(get_form() != nullptr)
      {

         get_form()->send_message(e_message_event,0,(LPARAM)&ev);

      }
      else
      {

         GetParent()->send_message(e_message_event,0,(LPARAM)&ev);

      }*/
      return true;
   }


   bool mesh::_001OnRightClick(uptr nFlag,const ::point & point)
   {

      UNREFERENCED_PARAMETER(nFlag);
      UNREFERENCED_PARAMETER(point);
      return false;

   }



   void mesh::_001GetSelection(range &range)
   {
      range = m_rangeSelection;
   }


   void mesh::_001GetSelection(::database::key & key, ::database::selection &selection)
   {

      if (!_001HasConfigId(key))
      {

         return;

      }

      index iFilterSubItem = _001ConfigIdToColumnKey(key);

      range & range = m_rangeSelection;

      for(index i = 0; i < range.get_item_count(); i++)
      {
         auto & itemrange = range.ItemAt(i);
         if(itemrange.has_sub_item(iFilterSubItem))
         {
            for(index iLine = itemrange.get_lower_bound(); iLine <= itemrange.get_upper_bound(); iLine++)
            {
               selection.add_item(key.m_strDataKey + "/" + __str(iLine));
            }
         }
      }
   }


   /*index range::get_item(index iItemIndex)
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

   /*index item_range::get_count()
   {
   return m_iItemEnd - m_iItemStart + 1;
   }*/

   /*index item_range::get_item(index iItemIndex)
   {
   return m_iItemStart + iItemIndex;
   }*/


   ::count mesh::_001GetSelectedItemCount()
   {
      return m_rangeSelection.get_item_count();
   }

   id mesh::_001GetColumnTextId(index iColumn)
   {
      UNREFERENCED_PARAMETER(iColumn);
      return -1;
   }

   void mesh::_001OnLButtonDblClk(::message::message * pmessage)
   {

      SCAST_PTR(::message::mouse, pmouse, pmessage);

      m_iClick = 2;

      auto item = hit_test(pmouse);

      on_click(item);


      //   on_click(item);
      set_need_redraw();


      /* trans window_id wndidNotify = pwnd->GetOwner()->GetSafeoswindow_();
      if(wndidNotify == nullptr)
      wndidNotify = pwnd->GetParent()->GetSafeoswindow_();*/


      LRESULT lresult = 0;

      /* trans if(wndidNotify)
      {
      NMLISTVIEW nm;
      nm.hdr.idFrom = pwnd->GetDlgCtrlId();
      nm.hdr.code =   NM_DBLCLK;
      nm.hdr.oswindowFrom = pwnd->GetSafeoswindow_();
      lresult = ::SendMessage(
      wndidNotify,
      WM_NOTIFY,
      nm.hdr.idFrom,
      (LPARAM) &nm);


      }*/

      if(lresult == 0)
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


   void mesh::_001ShowSubItem(index iSubItem, bool bShow)
   {

   }


   void mesh::DISaveOrder()
   {

   }


   void mesh::DILoadOrder()
   {

   }


   void mesh::PreSubClassWindow()
   {

      if(is_window_visible())
      {

         RedrawWindow(nullptr,nullptr,RDW_INVALIDATE);

      }

   }


   void mesh::_001OnCreate(::message::message * pmessage)
   {

      SCAST_PTR(::message::create,pcreate,pmessage);

      pmessage->previous();

      on_enable_hover_select();

      descriptor().set_control_type(::user::control_type_mesh);

      m_dcextension.initialize(this);

      on_create_draw_item();


      if (m_eview == ::user::mesh::impact_icon)
      {

         m_pdrawmeshitem->m_ealign = e_align_top_center;

         m_pdrawmeshitem->m_edrawtext = { e_draw_text_end_ellipsis, e_draw_text_word_break };
      }
      else
      {

         m_pdrawmeshitem->m_ealign = e_align_left_center;

         m_pdrawmeshitem->m_edrawtext = { e_draw_text_end_ellipsis, e_draw_text_single_line };

      }


      //m_font->operator=(*System.draw2d().fonts().GetMeshCtrlFont());

      //m_fontHover->operator=(*System.draw2d().fonts().GetMeshCtrlFont());

      //m_fontHover->set_underline();
      ////m_fontHover->set_bold();

      if(pcreate->m_lresult == -1)
      {
         pmessage->m_bRet = false;
         return;
      }


      //if(m_bAutoCreateMeshHeader)
      //{

      //   if(m_pmeshheader.is_null())
      //   {

      //      m_pmeshheader = create_mesh_header();

      //      if(m_pmeshheader.is_set())
      //      {

      //         m_pmeshheader->SetBaseMeshCtrlInterface(this);

      //      }

      //   }

      //   if(m_pmeshheader != nullptr)
      //   {

      //      if(!CreateHeaderCtrl())
      //      {
      //         pcreate->set_lresult(-1);
      //         pmessage->m_bRet = true;
      //         return;
      //      }
      //   }

      //}

      if(m_pmeshdata.is_null() && m_bAutoCreateMeshData)
      {

         defer_create_mesh_data();

      }

      ::rect rect;

      //rect.null();

      //set_need_layout();

      pcreate->m_lresult = 0;

      if(is_window_visible())
      {
         set_need_redraw();
      }

      pmessage->m_bRet = false;

   }


   //void mesh::_001CreateImageMesh(mesh_column * pcolumn)
   //{

   //   if(pcolumn == nullptr)
   //      return;

   //   if(pcolumn->m_uiSmallBitmap == (UINT)-1)
   //   {
   //      return;
   //   }
   //   if(pcolumn->m_pil == nullptr)
   //   {
   //      pcolumn->m_pil = new ::image_list(get_object());
   //   }
   //   //      __pointer(::image_list) pil = pcolumn->m_pil;
   //   //   if(pil != nullptr)
   //   //      pil->DeleteImageMesh();
   //   ::exception::throw_not_implemented();
   //   /*if(!pil->create(
   //   MAKEINTRESOURCE(pcolumn->m_uiSmallBitmap),
   //   pcolumn->m_iSmallImageWidth,
   //   0,
   //   pcolumn->m_crSmallMask))
   //   {
   //   }*/
   //}


   void mesh::on_hover_select_timer()
   {

      index iItemSel;

      index iSubItemSel;

      auto psession = Session;

      auto point = psession->get_cursor_pos();

      _001ScreenToClient(point);

      try
      {

         if (_001DisplayHitTest(point, iItemSel, iSubItemSel))
         {

            if (m_iSubItemEnter == iSubItemSel && m_iItemEnter == iItemSel)
            {

               m_iSubItemEnter = -1;

               m_iItemEnter = -1;

               bool bLShiftKeyDown = psession->is_key_pressed(::user::key_lshift);
               bool bRShiftKeyDown = psession->is_key_pressed(::user::key_rshift);
               bool bLControlKeyDown = psession->is_key_pressed(::user::key_lcontrol);
               bool bRControlKeyDown = psession->is_key_pressed(::user::key_rcontrol);
               bool bShiftKeyDown = bLShiftKeyDown || bRShiftKeyDown;
               bool bControlKeyDown = bLControlKeyDown || bRControlKeyDown;

               if (m_bMultiSelect && bShiftKeyDown)
               {

                  if (bControlKeyDown)
                  {

                     item_range itemrange;

                     itemrange.set(
                        min(iItemSel, m_iItemSel),
                        max(iItemSel, m_iItemSel),
                        min(iSubItemSel, m_iSubItemSel),
                        max(iSubItemSel, m_iSubItemSel),
                        -1,
                        -1);

                     _001AddSelection(itemrange);

                  }
                  else
                  {

                     item_range itemrange;

                     itemrange.set(
                        min(iItemSel, m_iItemSel),
                        max(iItemSel, m_iItemSel),
                        min(iSubItemSel, m_iSubItemSel),
                        max(iSubItemSel, m_iSubItemSel),
                        -1,
                        -1);

                     ::user::range range;

                     range.add_item(itemrange);

                     _001SetSelection(range);

                  }

               }
               else if (m_bMultiSelect && bControlKeyDown)
               {

                  m_iLastItemSel = m_iItemSel;

                  m_iLastSubItemSel = m_iSubItemSel;

                  m_iItemSel = iItemSel;

                  m_iSubItemSel = iSubItemSel;

                  item_range itemrange;

                  itemrange.set(
                     m_iItemSel,
                     m_iItemSel,
                     m_iSubItemSel,
                     m_iSubItemSel,
                     -1,
                     -1);

                  _001AddSelection(itemrange);

               }
               else
               {

                  m_iLastItemSel = m_iItemSel;

                  m_iLastSubItemSel = m_iSubItemSel;

                  m_iItemSel = iItemSel;

                  m_iSubItemSel = iSubItemSel;

                  item_range itemrange;

                  itemrange.set(
                     _001DisplayToStrict(m_iItemSel),
                     _001DisplayToStrict(m_iItemSel),
                     m_iSubItemSel,
                     m_iSubItemSel,
                     -1,
                     -1);

                  ::user::range range;

                  range.add_item(itemrange);

                  _001SetSelection(range);

               }

            }

         }

      }
      catch (...)
      {

      }

      m_iSubItemEnter = -1;

      m_iItemEnter = -1;

   }


   void mesh::_001OnTimer(::timer * ptimer)
   {

      ::user::interaction::_001OnTimer(ptimer);

      if (ptimer->m_uEvent == e_timer_hover_select)
      {

         int iHoverSelectTimeout = 3;

         if (m_iTimerHoverSelect < iHoverSelectTimeout)
         {

            m_iTimerHoverSelect++;

         }
         else if (m_iTimerHoverSelect == iHoverSelectTimeout)
         {

            on_hover_select_timer();

            m_iTimerHoverSelect++;

         }

         

      }
      else if(ptimer->m_uEvent == 12345679) // left click
      {

         KillTimer(12345679);

         if(m_bSelect)
         {

            if(m_bHoverSelect2)
            {

            }

         }

      }
      else if(ptimer->m_uEvent == 8477) // right click
      {

         KillTimer(8477);

         //if(!_001IsEditing())
         {
            uptr nFlags = m_uiRButtonUpFlags;
            const ::point & point = m_pointRButtonUp;
            _001OnRightClick(nFlags,point);
            set_need_redraw();


            /* trans
            window_id wndidNotify = pwnd->GetOwner()->GetSafeoswindow_();
            if(wndidNotify == nullptr)
            wndidNotify = pwnd->GetParent()->GetSafeoswindow_(); */

            //            LRESULT lresult = 0;

            /* trans            if(wndidNotify)
            {
            NMLISTVIEW nm;
            nm.hdr.idFrom = pwnd->GetDlgCtrlId();
            nm.hdr.code =   NM_CLICK;
            nm.hdr.oswindowFrom = pwnd->GetSafeoswindow_();
            lresult = ::SendMessage(
            wndidNotify,
            WM_NOTIFY,
            nm.hdr.idFrom,
            (LPARAM) &nm);
            }*/
         }
      }
      else if(ptimer->m_uEvent == 0xfffffffe)
      {

         if(!Filter1Step())
         {

            KillTimer(ptimer->m_uEvent);

         }

      }
      else if (ptimer->m_uEvent == 224455)
      {

         KillTimer(ptimer->m_uEvent);

         if (m_iItemLButtonDown >= 0)
         {

            m_bDrag = true;

         }
         else
         {

            m_iItemLButtonDown = -1;

            m_iDisplayItemLButtonDown1 = -1;

            m_iDisplayItemLButtonDown2 = -1;

            m_bDrag = false;

         }

      }
      else if(ptimer->m_uEvent == e_timer_drag_start) // 12345678
      {

         KillTimer(ptimer->m_uEvent);

         if(!m_bHoverSelect2)
         {

         }
         else
         {

            m_bDrag = true;

         }

      }
      //else if(ptimer->m_uEvent == 12321)
      //{


      //}

   }


   void mesh::enable_hover_select(bool bEnable)
   {

      if (is_different(bEnable, m_bEnableSaveWindowRect2))
      {

         on_enable_hover_select();

      }

   }


   void mesh::on_enable_hover_select()
   {

      if (m_bHoverSelect2)
      {

         SetTimer(e_timer_hover_select, 200);

      }
      else
      {

         KillTimer(e_timer_hover_select);

      }

   }


   bool mesh::_001IsItemVisible(index iItem)
   {
      draw_mesh_item item(this);
      item.m_iItem         = iItem;
      item.m_iDisplayItem  = iItem;
      _001GetItemRect(&item);
      if(!item.m_bOk)
      {
         return false;
      }
      ::rect rectClient;
      get_client_rect(&rectClient);
      return rectClient.intersect(rectClient,item.m_rectItem) != 0;
   }

   void mesh::_001ClearSelection()
   {
      m_rangeSelection.clear();
      _001OnSelectionChange();
   }

   void mesh::_001SetSelection(const range &range)
   {
      m_rangeSelection = range;
      on_select();
      _001OnSelectionChange();
   }

   void mesh::_001AddSelection(const item_range & itemrange)
   {
      m_rangeSelection.add_item(itemrange);
      on_select();
      _001OnSelectionChange();
   }

   void mesh::_001SetHighlightRange(range & range)
   {
      m_rangeHighlight = range;
   }


   bool mesh::DIDDXHeaderLayout(bool bSave)
   {

      //if(m_pmeshheader == nullptr)
      //   return false;

      //return m_pmeshheader->DIDDXLayout(bSave);
      return false;

   }


   void mesh::_001SetTopText(const widechar * pcwsz)
   {

      m_strTopText = pcwsz;

      auto pgraphics = ::draw2d::create_memory_graphics();

      _001LayoutTopText(pgraphics);

   }


   void mesh::_001LayoutTopText(::draw2d::graphics_pointer& pgraphics)
   {

      pgraphics->set_font(this);

      ::size_array sizea;

      m_dcextension.GetTextExtent(pgraphics,m_strTopText,sizea);

      ::rect rectClient;

      get_client_rect(rectClient);

      index x = 0;
      index right = rectClient.right;
      index y = 0;
      for(index i = 0; i < sizea.get_size(); i++)
      {
         if((sizea[i].cx - x > right)
               || i == sizea.get_upper_bound())
         {
            if(i == 0)
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
      m_rectTopText.bottom = (LONG)y;


   }

   void mesh::_001ShowTopText(bool bShow)
   {
      m_bTopText = bShow;
   }




   void mesh::SetCacheInterface(mesh_cache_interface * pinterface)
   {
      m_pcache = pinterface;
   }


   void mesh::CacheHint()
   {

      if(m_pcache != nullptr)
      {

         index iItemCount = m_nDisplayCount;

         index iItemFirst = m_iTopDisplayIndex;

         m_pcache->_001CacheHint(this, iItemFirst, iItemCount);

      }

   }


   void mesh::SetDataInterface(::user::mesh_data *pinterface)
   {

      m_pmeshdata = pinterface;

      __refer(m_psimplemeshdata,m_pmeshdata);

   }


   //bool mesh::_001InsertColumn(mesh_column &column)
   //{

   //   _001OnColumnChange();
   //   return true;
   //}

   //void mesh::_001SetSingleColumnMode(bool bHeaderCtrl)
   //{

   //   //m_bSingleColumnMode = true;

   //   //m_bHeaderCtrl = bHeaderCtrl;
   //   //_001RemoveAllColumns();

   //   //mesh_column column;
   //   //pcolumn->m_iWidth = -1;
   //   //pcolumn->m_iSubItem = 0;
   //   //pcolumn->m_iSmallImageWidth = 16;
   //   //pcolumn->m_crSmallMask = ARGB(255,255,0,255);


   //   //_001InsertColumn(column);

   //   set_need_layout();



   //}


   //i32 mesh::_001CalcItemWidth(::draw2d::graphics_pointer& pgraphics, index iItem,index iSubItem)
   //{

   //   pgraphics->set_font(this);

   //   index cx = _001CalcItemWidth(pgraphics,iItem,iSubItem);

   //   return (i32)cx;

   //}


   //i32 mesh::_001CalcItemWidth(::draw2d::graphics_pointer & pgraphics,::draw2d::font * pfont,index iItem,index iSubItem)
   //{
   //   pgraphics->set(pfont);
   //   return _001CalcItemWidth(pgraphics,iItem,iSubItem);
   //}


   i32 mesh::_001CalcItemWidth(::draw2d::graphics_pointer & pgraphics,index iItem,index iSubItem)
   {

#ifdef WINDOWS_DESKTOP

      pgraphics->set_font(this);

      ::image_list::info ii;
      ::rect rect;
      ::size size;
      index cx = 0;
      //mesh_column * pcolumn = m_columna._001GetByKey(iSubItem);
      draw_mesh_item item(this);
      item.m_iItem = iItem;
      item.m_iSubItem = iSubItem;
      item.m_iListItem = -1;
      //if(pcolumn->m_pil != nullptr)
      //{
      //   _001GetItemImage(&item);
      //   if(item.m_bOk && item.m_iImage >= 0)
      //   {
      //      pcolumn->m_pil->get_image_info((i32)item.m_iImage,&ii);
      //      rect = ii.m_rect;
      //      cx += rect.width();
      //      cx += 2;
      //   }
      //}
      _001GetItemText(&item);
      if(item.m_bOk)
      {
         m_dcextension.GetTextExtent(pgraphics,item.m_strText,size);
         cx += size.cx;
      }

      return (i32)cx;
#else
      __throw(todo());
#endif
   }




   bool mesh::_001HasConfigId(const ::database::key & key)
   {
      return _001ConfigIdToColumnKey(key) >= 0;
   }

   index mesh::_001ConfigIdToSubItem(const ::database::key & key)
   {
      //mesh_column * column = m_columna._001GetByConfigId(key);
      //if(column == nullptr)
      //   return -1;
      //return column->m_iSubItem;
      return -1;
   }

   index mesh::_001ConfigIdToColumnKey(const ::database::key & key)
   {
      //mesh_column * column = m_columna._001GetByConfigId(key);
      //if(column == nullptr)
      //   return -1;
      //return column->m_iKey;
      return -1;
   }

   //mesh_column * mesh_column_array::_001GetByConfigId(const ::database::key & key)
   //{
   //   //index iKey = MapConfigIdToKey(key);
   //   //if(iKey >= 0)
   //   //   return element_at(iKey);
   //   //else
   //   //   return nullptr;



   //}

   //index mesh_column_array::MapConfigIdToKey(const ::database::key & key)
   //{
   //   for(index iKey = 0; iKey < this->get_size(); iKey++)
   //   {
   //      if(this->element_at(iKey)->m_datakey == key)
   //         return iKey;
   //   }
   //   return -1;
   //}





   void mesh::_001EnsureVisible(index iItem,bool bRedraw)
   {

      auto pointScroll = get_viewport_offset();

      if(iItem < pointScroll.y || (m_iItemHeight > 0 && iItem >= pointScroll.y / m_iItemHeight + m_nDisplayCount))
      {

         set_viewport_offset_y((int) (iItem * m_iItemHeight));

         if(bRedraw)
         {

            set_need_redraw();

         }

      }

   }


   void mesh::_001ItemScroll(index iItem,bool bRedraw)
   {

      //auto pointScroll = get_viewport_offset();

      if(iItem < m_nItemCount)
      {

         set_viewport_offset_y((int)(iItem * m_iItemHeight));

         if(bRedraw)
         {

            set_need_redraw();

         }

      }

   }


   void mesh::_001EnsureVisible(index iItem,range & range)
   {

      auto pointScroll = get_viewport_offset();

      index iyScroll = pointScroll.y / max(1,m_iItemHeight);
      if(iItem < iyScroll)
      {
         iyScroll = iItem - m_nDisplayCount + 1;
      }
      else if(iItem >= iyScroll + m_nDisplayCount)
      {
         iyScroll = iItem;
      }
      if(pointScroll.y / max(1,m_iItemHeight) != iyScroll)
      {
         item_range item;
         set_viewport_offset_y((int)(iyScroll * m_iItemHeight));
         on_change_viewport_offset();
         item.set_lower_bound(iyScroll);
         item.set_upper_bound(min(iyScroll + m_nDisplayCount - 1,m_nItemCount - 1));
         range.add_item(item);
      }
   }

   void mesh::_001Highlight(index iItem,bool bRedraw)
   {
      m_rangeHighlight.clear();
      item_range itemrange;
      itemrange.set(iItem,iItem,0,m_nColumnCount - 1,- 1,-1);
      m_rangeHighlight.add_item(itemrange);
      if(bRedraw)
      {
         set_need_redraw();
      }
   }


   bool mesh::_001OnRemoveItem(index iItem)
   {

      UNREFERENCED_PARAMETER(iItem);

      return false;

   }


   bool mesh::_001RemoveItem(index iItem,bool bRedraw)
   {

      if (!_001OnRemoveItem(iItem))
      {

         return false;

      }

      m_rangeSelection.OnRemoveItem(iItem);

      if(bRedraw)
      {

         set_need_redraw();

      }

      return true;

   }

   void mesh::_001RemoveSelection()
   {
      ::user::range range;

      _001GetSelection(range);


      while(range.get_item_count() > 0)
      {
         index iItem = range.ItemAt(0).get_lower_bound();
         if(!_001RemoveItem(iItem,false))
            break;
         _001GetSelection(range);
      }

      set_need_redraw();
   }


   void mesh::_001Select(index iItem,index iSubItem)
   {
      m_rangeSelection.clear();
      item_range itemrange;
      itemrange.set(iItem,iItem,iSubItem,iSubItem,- 1,-1);
      _001AddSelection(itemrange);

   }


   index mesh::_001StrictToDisplay(index iStrict)
   {

      UNREFERENCED_PARAMETER(iStrict);

      return -1;

   }


   index mesh::_001DisplayToStrict(index iDisplay)
   {

      if(iDisplay < 0)
      {

         return -1;

      }

      if(m_eview == impact_icon)
      {

         return m_piconlayout->m_iaDisplayToStrict[iDisplay];

      }
      else
      {

         if(iDisplay < 0)
         {

            return -1;

         }

         if(m_pmeshlayout->m_iaDisplayToStrict.get_count() <= 0)
         {

            if(iDisplay < m_nItemCount)
            {

               return iDisplay;

            }

         }

         if(iDisplay >= m_pmeshlayout->m_iaDisplayToStrict.get_count())
         {

            return -1;

         }

         return m_pmeshlayout->m_iaDisplayToStrict[iDisplay];

      }

   }


   void mesh::FilterBegin()
   {

      m_efilterstate = FilterStateSetup;

      index iItemCount = m_nItemCount;

      if(m_eview == impact_icon)
      {

         m_piaFilterIcon->remove_all();

         for(index i = 0; i < iItemCount; i++)
         {

            m_piaFilterIcon->add(i);

         }

      }
      else
      {

         m_piaFilterMesh->remove_all();

         for(index i = 0; i < iItemCount; i++)
         {

            m_piaFilterMesh->add(i);

         }

      }

   }


   void mesh::FilterApply()
   {

      m_iFilter1Step = 0;

      SetTimer(0xfffffffe,50,nullptr);

      set_viewport_offset_x(0);

      set_viewport_offset_y(0);

      m_efilterstate = FilterStateFilter;

      on_change_view_size();

      set_need_layout();

      set_need_redraw();

   }


   void mesh::FilterClose()
   {

      m_bFilter1 = false;

      KillTimer(0xfffffffe);

      ASSERT(m_efilterstate == FilterStateSetup || m_efilterstate == FilterStateFilter);

      index iItemCount = m_nItemCount;

      if(m_eview == impact_icon)
      {

         m_piconlayout->m_iaDisplayToStrict.remove_all();

         for(index i = 0; i < iItemCount; i++)
         {

            m_piconlayout->m_iaDisplayToStrict.add(i);

         }

      }
      else
      {

         m_pmeshlayout->m_iaDisplayToStrict.remove_all();

         for(index i = 0; i < iItemCount; i++)
         {

            m_pmeshlayout->m_iaDisplayToStrict.add(i);

         }

      }

      on_change_view_size();

      set_need_layout();

      set_need_redraw();

   }


   void mesh::FilterExcludeAll()
   {

      if(m_eview == impact_icon)
      {

         m_piaFilterIcon->remove_all();

      }
      else
      {

         m_piaFilterMesh->remove_all();

      }

   }


   void mesh::FilterInclude(index iItem)
   {

      ASSERT(m_efilterstate == FilterStateSetup);

      if(m_eview == impact_icon)
      {

         m_piaFilterIcon->add_unique(iItem);

      }
      else
      {

         m_piaFilterMesh->add_unique(iItem);

      }

   }


   void mesh::FilterInclude(int_array & array)
   {

      ASSERT(m_efilterstate == FilterStateSetup);

      for(index i = 0; i < array.get_size() ; i++)
      {

         FilterInclude(array[i]);

      }

   }


   bool mesh::Filter1Step()
   {

      auto tickIn = ::tick::now();

      TRACE("mesh::Filter1Step");

      TRACE("tickIn = " __prtick, __pr(tickIn));

      if(!m_bFilter1)
      {

         return false;

      }

      string wstrItem;

      index iItemCount = min(m_nItemCount,m_iFilter1Step + 1000);

      index iFilter1Step;

      draw_mesh_item item(this);

      for(iFilter1Step =  m_iFilter1Step; iFilter1Step < iItemCount; iFilter1Step++)
      {
         //for(index j = 0; j < m_nColumnCount; j++)
         /*{
            mesh_column * pcolumn = m_columna._001GetByKey(j);
            item.m_strText.Empty();
            item.m_iItem = iFilter1Step;
            item.m_iSubItem = pcolumn->m_iSubItem;
            item.m_iListItem = -1;
            _001SearchGetItemText(&item);
            if(item.m_bOk)
            {
               item.m_strText.make_lower();
               item.m_strText.replace("_"," ");
               if(m_reFilter1.match(item.m_strText))
               {
                  if(m_eview == impact_icon)
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
         }*/
      }

      m_iFilter1Step = (i32)iFilter1Step;

      if(m_eview == impact_icon)
      {

         m_piconlayout->m_iaDisplayToStrict = (*m_piaFilterIcon);

      }
      else
      {

         m_pmeshlayout->m_iaDisplayToStrict = (*m_piaFilterMesh);

      }

      set_viewport_offset_x(0);

      set_viewport_offset_y(0);

      m_efilterstate = FilterStateFilter;

      on_change_view_size();

      set_need_layout();

      set_need_redraw();

      auto tickOut = ::tick::now();

      TRACE("tickOut = " __prtick, __pr(tickOut));
      TRACE("(delta) = " __prtick, __pr(tickOut - tickIn));

      return m_nItemCount != iItemCount;
   }


   void mesh::Filter1(string & strFilter)
   {

      if(m_eview == impact_icon)
      {
         m_piaFilterIcon->remove_all();
      }
      else
      {
         m_piaFilterMesh->remove_all();
      }

      string_array stra;

      stra.add_tokens(strFilter," ",false);

      //m_pregexFilter1->setPositionMoves(1);

      m_pregexFilter1 = System.create_pcre("/.*" + stra.implode(".*") + ".*/i");

      m_bFilter1 = m_pregexFilter1;

      if(m_bFilter1)
      {
         FilterApply();
      }
      else
      {
         FilterClose();
      }

   }

   void mesh::_001OnMeshHeaderItemClick(index iHeaderItem)
   {
      if(!m_bSortEnable)
         return;
      _001OnSort(_001MapColumnToSubItem(iHeaderItem));
   }


   void mesh::_001OnMeshHeaderItemDblClk(index iHeaderItem)
   {
      
      auto pgraphics = ::draw2d::create_memory_graphics();

      _001MaximizeColumnWidth(pgraphics, iHeaderItem);

   }


   bool mesh::does_drag_reorder()
   {

      return false;

   }


   void mesh::_001OnSort()
   {

      if(!m_bSortEnable)
      {

         return;

      }

      if(m_eview != impact_icon)
      {

         ::sort::quick_sort(m_pmeshlayout->m_iaDisplayToStrict,this,(::sort::compare_interface::_FUNCTION_Compare) &::user::mesh::_001Compare);

      }
      else
      {

      }

   }


   void mesh::_001OnSort(index iSubItem)
   {

      index iFound = -1;
      for(index i = 0; i < m_sortinfo.m_itema.get_size(); i++)
      {
         CSortInfoItem & item = m_sortinfo.m_itema[i];
         if(item.m_iSubItem == iSubItem)
         {
            iFound = i;
            break;
         }
      }
      if(iFound >= 0)
      {
         CSortInfoItem newItem = m_sortinfo.m_itema[iFound];
         m_sortinfo.m_itema.remove_at(iFound);
         newItem.m_bAscendent = !newItem.m_bAscendent;
         m_sortinfo.m_itema.insert_at(0,newItem);
      }
      else
      {
         CSortInfoItem newItem;
         newItem.m_iSubItem = iSubItem;
         newItem.m_bAscendent = true;
         m_sortinfo.m_itema.insert_at(0,newItem);
      }

      _001OnSort();

   }




   index mesh::_002Compare(index iItem1,index iItem2,index iSubItem)
   {
      draw_mesh_item item1(this);
      draw_mesh_item item2(this);

      item1.m_iItem     = iItem1;
      item2.m_iItem     = iItem2;
      item1.m_iSubItem  = iSubItem;
      item2.m_iSubItem  = iSubItem;

      _001GetItemText(&item1);
      _001GetItemText(&item2);

      if(item1.m_bOk && item2.m_bOk)
      {
         return item1.m_strText.compare_ci(item2.m_strText);
      }
      else
      {
         if(item1.m_bOk)
            return 1;
         else if(item2.m_bOk)
            return -1;
         else
            return 0;
      }

   }

   index mesh::_001Compare(index iItem1,index iItem2)
   {
      CSortInfoItem * pitem = nullptr;
      index iCompare = 0;
      for(index i = 0; i < m_sortinfo.m_itema.get_size(); i++)
      {
         pitem = &m_sortinfo.m_itema[i];
         iCompare = _002Compare(iItem1,iItem2,pitem->m_iSubItem);
         if(iCompare != 0)
            break;
      }
      if(pitem == nullptr)
         return 0;
      else
      {
         if(pitem->m_bAscendent)
            return iCompare;
         else
            return -iCompare;
      }
   }


   index mesh::_001DisplayCompare(index iDisplayItem1,index iDisplayItem2)
   {
      return _001Compare(_001DisplayToStrict(iDisplayItem1),_001DisplayToStrict(iDisplayItem2));
   }


   i32 mesh::_001CalcMeshWidth(::draw2d::graphics_pointer& pgraphics)
   {

      ASSERT(FALSE);

      return -1;

   }


   i32 mesh::_001CalcColumnWidth(::draw2d::graphics_pointer& pgraphics, index iColumn)
   {

      UNREFERENCED_PARAMETER(iColumn);

      pgraphics->set_font(this);

      i32 iMaxWidth = 0;

      ::count iCount = m_nItemCount;

      i32 iWidth;

      for(index i = 0; i < iCount; i++)
      {

         iWidth = _001CalcItemWidth(pgraphics,i,0);

         if(iWidth > iMaxWidth)
         {

            iMaxWidth = iWidth;

         }

      }

      return iMaxWidth;

   }


   bool mesh::_001SetColumnWidth(index iColumn,i32 iWidth)
   {

      m_mapColumnWidth[iColumn] = iWidth;

      return true;

   }



   void mesh::_001MaximizeColumnWidth(::draw2d::graphics_pointer& pgraphics, index iColumn)
   {
      
      _001SetColumnWidth(iColumn,_001CalcColumnWidth(pgraphics, iColumn));

   }


   void mesh::_OnDraw(::draw2d::graphics_pointer & pgraphics)
   {

      UNREFERENCED_PARAMETER(pgraphics);

   }


   i32 mesh::get_wheel_scroll_delta()
   {

      if(m_eview == impact_grid)
      {

         return 1;

      }
      else
      {

         return m_iItemHeight;

      }

   }


   //rect mesh::get_scroll_margin()
   //{

   //   if(m_eview == impact_grid && m_iItemHeight > 0)
   //   {

   //      return rect(m_scrolldata.m_rectMargin.left,m_scrolldata.m_rectMargin.top/m_iItemHeight, m_scrolldata.m_rectMargin.right,m_scrolldata.m_rectMargin.bottom / m_iItemHeight);

   //   }
   //   else
   //   {

   //      return scroll_control::get_scroll_margin();

   //   }

   //}


   void mesh::on_change_viewport_offset()
   {

//      ::user::interaction::on_change_viewport_offset();

      m_iTopDisplayIndex = _001CalcDisplayTopIndex();
      index iLow = 0;
      for(m_iTopGroup = 0; m_iTopGroup < m_nGroupCount; m_iTopGroup++)
      {
         if(m_iTopDisplayIndex >= iLow && m_iTopDisplayIndex < (iLow + _001GetGroupItemCount(m_iTopGroup)))
            break;
      }
      m_nDisplayCount = _001CalcDisplayItemCount();

//      HeaderCtrlLayout();

      CacheHint();

      auto psession = Session;

      update_hover(psession->get_cursor_pos());

   }



   ::draw2d::pen * mesh::_001GetPenHighlight()
   {
      return m_penHighlight;
   }

   ::draw2d::pen * mesh::_001GetPenFocused()
   {
      return m_penFocused;

   }

   //::draw2d::font * mesh::_001GetFont()
   //{
   //   return m_font;
   //}

   //::draw2d::font * mesh::_001GetFontHover()
   //{
   //   return m_fontHover;
   //}


   void mesh::_001OnMouseLeave(::message::message * pmessage)
   {
      
      m_iDisplayItemHover = -1;
      
      m_iSubItemHover = -1;
      
      set_need_redraw();
      
      pmessage->m_bRet = true;

   }


   bool mesh::update_hover(const ::point & point, bool bAvoidRedraw)
   {

      index iItemHover;
      
      index iSubItemHover;
      
      auto pointClient = point;

      _001ScreenToClient(pointClient);

      bool bAnyHoverChange = false;

      if(_001DisplayHitTest(point, iItemHover, iSubItemHover))
      {

         if(m_iSubItemHover != iSubItemHover || m_iDisplayItemHover != iItemHover)
         {

            m_iDisplayItemHover = iItemHover;

            m_iSubItemHover = iSubItemHover;

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


   ::user::mesh_data * mesh::GetDataInterface()
   {

      return m_pmeshdata;

   }


   void mesh::_001SetView(EView eview, bool bLayout)
   {

      m_eview = eview;

      if (m_eview == ::user::mesh::impact_icon)
      {

         m_pdrawmeshitem->m_ealign = e_align_top_center;

         m_pdrawmeshitem->m_edrawtext = { e_draw_text_end_ellipsis, e_draw_text_word_break };
      }
      else
      {

         m_pdrawmeshitem->m_ealign = e_align_left_center;

         m_pdrawmeshitem->m_edrawtext = { e_draw_text_end_ellipsis, e_draw_text_single_line };

      }


      //on_ui_event(event_change_view_style, object_list, this);

      data_get_DisplayToStrict();

      if (bLayout)
      {

         set_need_layout();

      }

   }


   void mesh::data_get_DisplayToStrict()
   {

      if(m_eview == impact_icon)
      {

         //data_get(data_get_current_sort_id() + "." + data_get_current_mesh_layout_id(),m_piconlayout);

      }
      else
      {

         //data_get(data_get_current_sort_id() + "." + data_get_current_mesh_layout_id(),m_pmeshlayout);

      }

   }


   void mesh::data_set_DisplayToStrict()
   {
      if(m_eview == impact_icon)
      {
         //data_set(data_get_current_sort_id() + "." + data_get_current_mesh_layout_id(),m_piconlayout);
      }
      else
      {
         //data_set(data_get_current_sort_id() + "." + data_get_current_mesh_layout_id(),m_pmeshlayout);
      }
   }

   id mesh::data_get_current_sort_id()
   {
      return data_get_sort_id(m_eview);
   }

   id mesh::data_get_sort_id(EView eview)
   {
      UNREFERENCED_PARAMETER(eview);
      switch(m_eview)
      {
      case impact_grid:
         return "sort-grid";
         break;
      case impact_report:
         return "sort-report";
         break;
      case impact_list:
         return "sort-mesh";
         break;
      case impact_icon:
         return "sort-icon";
         break;
      default:
         ASSERT(FALSE);
         return "sort";
      }
   }

   mesh::EView mesh::_001GetView()
   {
      return m_eview;
   }


   void mesh::_001OnAfterSort()
   {
      data_set_DisplayToStrict();
   }

   bool mesh::_001IsEditing()
   {
      return false;
   }

   void mesh::_001GetItemColor(::user::mesh_item * pitem)
   {

      if (m_pmeshdata != nullptr)
      {

         m_pmeshdata->_001GetItemColor(pitem);

         if (pitem->m_bOk)
         {

            return;

         }

      }

      pitem->m_bOk = false;

   }


   void mesh::_001OnVScroll(::message::message * pmessage)
   {

      SCAST_PTR(::message::scroll, pscroll, pmessage);

      pmessage->previous();

      sync_lock sl(mutex());

      if(m_eview == impact_grid)
      {

         if(pscroll->m_nSBCode != SB_THUMBTRACK)
         {

            auto pointScroll = get_viewport_offset();

            auto sizePage = get_page_size();

            auto sizeTotal = get_total_size();

            if((sizeTotal.cy - pointScroll.y - sizePage.cy) <= 1)
            {

               m_nItemCount = min(m_nGridItemCount,m_nItemCount + (::count)(sizePage.cy / m_iItemHeight));

               on_change_view_size();

            }

         }

      }

   }

   void mesh::_001OnHScroll(::message::message * pmessage)
   {

      SCAST_PTR(::message::scroll, pscroll, pmessage);

      pmessage->previous();

      if(m_eview == impact_grid)
      {

         if(pscroll->m_nSBCode != SB_THUMBTRACK)
         {

            auto pointScroll = get_viewport_offset();

            auto sizePage = get_page_size();

            auto sizeTotal = get_total_size();

            if((sizeTotal.cx - pointScroll.x - sizePage.cx) <= 1)
            {

///               m_nColumnCount = min(m_nGridColumnCount,m_nColumnCount + sizePage.cx);
/// 
               m_nColumnCount = m_nGridColumnCount;

               on_change_view_size();

            }

         }

      }

      m_iTopDisplayIndex = _001CalcDisplayTopIndex();
      index iLow = 0;
      for(m_iTopGroup = 0; m_iTopGroup < m_nGroupCount; m_iTopGroup++)
      {
         if(m_iTopDisplayIndex >= iLow && m_iTopDisplayIndex < (iLow + _001GetGroupItemCount(m_iTopGroup)))
            break;
      }
      m_nDisplayCount = _001CalcDisplayItemCount();

//      HeaderCtrlLayout();

      CacheHint();

   }


   id mesh::data_get_current_mesh_layout_id()
   {

      return "mesh";

   }


   bool mesh::query_drop(index iDisplayDrop,index iDisplayDrag)
   {

      if(iDisplayDrag < 0)
      {

         return false;

      }

      if(iDisplayDrop < 0)
      {

         return false;

      }

      if(iDisplayDrag == iDisplayDrop)
      {

         return false;

      }

      if(_001DisplayToStrict(iDisplayDrop) != -1 && _001DisplayToStrict(iDisplayDrop) < m_nItemCount)
      {

         return false;

      }

      return true;

   }


   bool mesh::do_drop(index iDisplayDrop,index iDisplayDrag)
   {

      UNREFERENCED_PARAMETER(iDisplayDrop);

      UNREFERENCED_PARAMETER(iDisplayDrag);

      if(m_eview == impact_icon)
      {

         m_piconlayout->m_iaDisplayToStrict.translate_a(iDisplayDrop,iDisplayDrag);

      }
      else
      {

         m_pmeshlayout->m_iaDisplayToStrict.__swap(iDisplayDrag, iDisplayDrop);

      }

      _001OnAfterSort();

      return true;

   }


   bool mesh::defer_drop(index iDisplayDrop,index iDisplayDrag)
   {
      if(query_drop(iDisplayDrop,iDisplayDrag))
      {
         if(m_eview == impact_icon)
         {
//            if(m_piconlayout->m_iWidth <= 0)
//            {
//               ::rect rectClient;
//               get_client_rect(rectClient);
//               index iIconSize;
//               if(m_nColumnCount > 0)
////                  iIconSize = max(32,m_columna[0]->m_sizeIcon.cy);
//                     iIconSize = 32;
//               else
//                  iIconSize = 32;
//               index iItemSize = iIconSize * 2;
//               m_piconlayout->m_iWidth = (i32)(max(1,rectClient.width() / iItemSize));
//            }
            return do_drop(iDisplayDrop,iDisplayDrag);
         }
         else
         {
            return do_drop(iDisplayDrop,iDisplayDrag);
         }
      }
      else
      {
         return false;
      }
   }

   mesh::mesh_layout::mesh_layout()
   {
   }

   mesh::mesh_layout::~mesh_layout()
   {
   }


   //void mesh::mesh_layout::io(::stream & stream)
   //{

   //   //ostream << m_iaDisplayToStrict;
   //   stream(m_iWidth);

   //}


   mesh::icon_layout::icon_layout()
   {

//      m_iWidth = -1;

   }


   mesh::icon_layout::~icon_layout()
   {
   }



   ::size mesh::get_item_size()
   {

      if(m_eview == impact_icon)
      {

         if(m_nColumnCount == 0)
         {

            return ::size(32,32);

         }

//         index iIconSize = max(32,m_columna[0]->m_sizeIcon.cy);

         index iIconSize = 32;

         index iItemSize = iIconSize * 2;

         return ::size((::i32) iItemSize, (::i32) iItemSize);

      }
      else
      {

         // not implemented

         ASSERT(FALSE);

         return size();

      }

   }


   void mesh::auto_arrange(bool bAutoArrange)
   {
      if(bAutoArrange)
      {
         m_flags.add(flag_auto_arrange);
      }
      else
      {
         m_flags.remove(flag_auto_arrange);
      }
      if(bAutoArrange)
      {
         index iMaxStrict = m_piconlayout->m_iaDisplayToStrict.get_max_b();
         for(index iStrict = 0; iStrict <= iMaxStrict; iStrict++)
         {
            m_piconlayout->m_iaDisplayToStrict.set(iStrict,iStrict);
         }
         set_need_layout();
      }
   }

   bool mesh::get_auto_arrange()
   {
      return m_flags.has(flag_auto_arrange);
   }

   void mesh::_001OnMeshViewAutoArrange(::message::message * pmessage)
   {
      UNREFERENCED_PARAMETER(pmessage);
      auto_arrange(!get_auto_arrange());
   }

   void mesh::_001OnUpdateMeshViewAutoArrange(::message::message * pmessage)
   {
      SCAST_PTR(::user::command,pcommand,pmessage);
      pcommand->_001SetCheck(get_auto_arrange());
      pcommand->enable();
   }

   bool mesh::is_valid_display_item(index iDisplayItem)
   {
      if(iDisplayItem < 0)
         return false;
      if(iDisplayItem >= m_nItemCount)
         return false;
      return true;
   }

   bool mesh::is_valid_strict_item(index iStrictItem)
   {
      if(iStrictItem < 0)
         return false;
      if(iStrictItem >= m_nItemCount)
         return false;
      return true;

   }


   bool mesh::keyboard_focus_is_focusable()
   {
      return true;
   }

   void mesh::_001OnSelectionChange()
   {
   }


   void mesh::set_current_item(const ::user::item & item, const ::action_context & context)
   {

      m_rangeSelection.clear();

      if (!item.is_set())
      {

         return;

      }

      item_range itemrange;

      itemrange.set_lower_bound(item);

      itemrange.set_upper_bound(item);

      _001AddSelection(itemrange);

   }


   void mesh::set_current_item(const index_array & iaSel, const ::action_context & context)
   {
      m_rangeSelection.clear();
      for(index i = 0; i < iaSel.get_count(); i++)
      {
         item_range itemrange;
         itemrange.set_lower_bound(iaSel[i]);
         itemrange.set_upper_bound(iaSel[i]);
         m_rangeSelection.add_item(itemrange);
      }

   }


   item mesh::current_item()
   {

      if (m_rangeSelection.get_item_count() != 1)
      {

         return -1;

      }

      if (m_rangeSelection.ItemAt(0).get_lower_bound() == m_rangeSelection.ItemAt(0).get_upper_bound() && m_rangeSelection.ItemAt(0).get_lower_bound() >= 0)
      {

         return m_rangeSelection.ItemAt(0).get_lower_bound();

      }

      return -1;

   }


   void mesh::get_cur_sel(index_array & iaSel)
   {

      for(index i = 0; i < m_rangeSelection.get_item_count(); i++)
      {

         for(index iItem = m_rangeSelection.ItemAt(i).get_lower_bound(); iItem <= m_rangeSelection.ItemAt(i).get_upper_bound(); iItem++)
         {

            iaSel.add_unique(iItem);

         }

      }

   }


   ::count mesh::_001GetGroupItemCount(index iGroup)
   {
      UNREFERENCED_PARAMETER(iGroup);
      return -1;
   }

   i32 mesh::_001GetGroupHeight(index iGroup)
   {
      i32 iMeshHeight = (i32)(_001GetGroupItemCount(iGroup) * m_iItemHeight);
      return max(m_iGroupMinHeight,iMeshHeight);
   }

   mesh_item::mesh_item(mesh * pmesh)
   {
      m_plistitem       = nullptr;
      m_pmesh           = pmesh;
      m_iGroup          = -1;
      m_iItem           = -1;
      m_iDisplayItem    = -1;
      m_iColumn         = -1;
      m_iOrder          = -1;
      m_iSubItem        = -1;
      m_iListItem       = -1;
      m_crText              = (COLORREF)-1;
      m_crTextBackground    = ARGB(255, 0, 0, 0);
      m_crItemBackground = 0;
      m_iState          = -1;
      m_iImage          = -1;
      m_bOk             = false;

      m_iGroupTopDisplayIndex  = -1;
      m_iGroupCount     = -1;

   }

   draw_mesh_item::draw_mesh_item(mesh * pmesh):
      mesh_item(pmesh)
   {

      m_prectClient              = nullptr;

      m_iColumn = -1;
      m_iColumnWidth             = 0;

      m_iItemRectItem            = -1;

      m_iSubItemRectItem         = -1;
      m_iSubItemRectSubItem      = -1;
      m_iSubItemRectOrder        = -1;
      m_iSubItemRectColumn       = -1;

      m_iListItemRectItem        = -1;
      m_iListItemRectSubItem     = -1;
      m_iListItemRectListItem    = -1;

   }


   __pointer(::image_list) draw_mesh_item::get_image_list()
   {
      //if(m_bListItemHover && m_pcolumn->m_pilHover != nullptr)
      //if(m_bListItemHover)
      //{
      //   return m_pcolumn->m_pilHover;
      //}
      //else
      //{
      //   return m_pcolumn->m_pil;
      //}

      return nullptr;

   }


   bool mesh::_001OnHeaderCtrlEndTrack(WPARAM, LPARAM)
   {

      return true;

   }


   bool mesh::_001OnHeaderCtrlTrack(WPARAM, LPARAM)
   {

      return true;

   }


   bool draw_mesh_item::draw_image()
   {
      //if(m_pcolumn->m_bIcon)
      //{
      //   draw2d::icon * picon;
      //   if(m_pcolumn->m_mapIcon.lookup((i32)m_iImage,picon))
      //   {
      //      m_pgraphics->set_alpha_mode(::draw2d::alpha_mode_blend);
      //      return m_pgraphics->DrawIcon(m_rectImage.top_left(),picon) != FALSE;
      //   }
      //}
      //else
      //{
      //   m_pgraphics->set_alpha_mode(::draw2d::alpha_mode_blend);
      //   return get_image_list()->draw(m_pgraphics,(i32)m_iImage,m_rectImage.top_left(),m_rectImage.size(),point(0,0),0);
      //}
      return false;
   }


   bool draw_mesh_item::draw_group_image()
   {
      return m_pmesh->m_pilGroup->draw(m_pgraphics,(i32)m_iImage,m_rectImage.top_left(),m_rectImage.size(),point(0,0),0);
   }


   void draw_mesh_item::update_item_color()
   {

      m_pmesh->_001GetItemColor(this);

      if(!m_bOk)
      {

         auto pstyle = m_pmesh->get_style(m_pgraphics);

         auto estate = get_user_state();

         m_crText = m_pmesh->get_color(pstyle, ::user::element_text, estate);

      }

   }


   void draw_mesh_item::set_text_color()
   {
      ::draw2d::brush_pointer brushText(e_create);
      brushText->create_solid(m_crText);
      m_pgraphics->set(brushText);
   }



   void draw_mesh_item::draw_text()
   {

      if(m_bOk)
      {

         if(m_pmesh->m_eview == mesh::impact_icon && m_pmesh->m_bEmboss)
         {

            auto size = m_rectText.size();
            size.cx += 4;
            size.cy += 4;

            ::image_pointer pimage1;
            pimage1 = create_image(size);
            pimage1->fill(0,0,0,0);
            ::draw2d::brush_pointer brushText(e_create);
            brushText->create_solid(ARGB(255,255,255,255));
            pimage1->get_graphics()->set(brushText);
            ::image_pointer pimage2;
            pimage2 = create_image(size);
            pimage2->fill(0,0,0,0);

            ::rect rectCache;
            rectCache.left = 2;
            rectCache.top = 2;
            rectCache.right = rectCache.left + (i32)m_rectText.width();
            rectCache.bottom = rectCache.top + (i32)m_rectText.height();
            pimage1->get_graphics()->set(m_pfont);
            pimage1->get_graphics()->_DrawText(m_strText,rectCache,m_ealign, m_edrawtext);

            //::aura::application * get_context_application() = m_pmesh->get_context_application();

            System.imaging().channel_spread_set_color(pimage2->get_graphics(),nullptr,size, pimage1->get_graphics(),nullptr,0,2,ARGB(192,192,192,192));
            pimage1->fill(0,0,0,0);
            System.imaging().channel_alpha_gray_blur(pimage1->get_graphics(),nullptr,size, pimage2->get_graphics(),nullptr,0,1);
            pimage2->fill(0,0,0,0);
            System.imaging().channel_alpha_gray_blur(pimage2->get_graphics(),nullptr,size, pimage1->get_graphics(),nullptr,0,1);
            pimage2->set_rgb(0,0,0);


            System.imaging().color_blend(m_pgraphics,m_rectText, pimage2->get_graphics(),point(1,1),0.50);


            brushText->create_solid(ARGB(255,255,255,255));
            m_pgraphics->set(brushText);
            m_pgraphics->set(m_pfont);
            m_pgraphics->_DrawText(m_strText,m_rectText,m_ealign, m_edrawtext);
         }
         else
         {
            ::draw2d::brush_pointer brushText(e_create);
            brushText->create_solid(m_crText);
            m_pgraphics->set(brushText);
            m_pgraphics->_DrawText(m_strText,m_rectText, m_ealign, m_edrawtext);
         }
      }
   }

   ::user::estate draw_mesh_item::get_user_state() const
   {

      ::user::estate estate = e_state_none;

      if (m_bListItemSelected)
      {

         estate |= e_state_selected;

      }
       
      if (m_bListItemHover)
      {

         estate |= e_state_hover;

      }

      return estate;

   }


   ::count mesh::_001GetGroupMetaItemCount(index iGroup)
   {
      if(m_pmeshdata != nullptr)
      {
         return m_pmeshdata->_001GetGroupMetaItemCount(iGroup);
      }
      return 0;
   }

   void mesh::_001GetGroupText(mesh_item * pitem)
   {
      pitem->m_bOk = false;
      if(m_pcache != nullptr)
      {
         m_pcache->_001GetGroupText(pitem);
         if(pitem->m_bOk)
            return;
      }
      if(m_pmeshdata != nullptr)
      {
         m_pmeshdata->_001GetGroupText(pitem);
      }
   }

   void mesh::_001GetGroupImage(mesh_item * pitem)
   {
      pitem->m_bOk = false;
      pitem->m_iImage = -1;
   }




   void mesh::_001OnBeforeDeleteRange(range & range)
   {
   }

   void mesh::_001OnDeleteRange(range & range)
   {

      if(m_pmeshdata != nullptr)
      {

         m_pmeshdata->_001OnDeleteRange(range);

      }

   }


   void mesh::_001DeleteRange(range & range)
   {

      _001OnBeforeDeleteRange(range);

      _001OnDeleteRange(range);

   }


   //__pointer(::user::mesh_data) list::create_mesh_data()
   //{

   //   return __new(mesh_data);

   //}



   void mesh::defer_create_mesh_data()
   {

      __pointer(::user::list_data) pmeshdata = create_mesh_data();

      if(pmeshdata.is_null())
         return;

      SetDataInterface(pmeshdata);

   }


   ::count mesh::_001GetColumnCount()
   {

      if(m_pmeshdata.is_null())
         return -1;

      return m_pmeshdata->_001GetColumnCount(this);

   }


   ::point mesh::get_viewport_offset()
   {

      return ::user::interaction::get_viewport_offset();

   }


   //void mesh::on_change_view_size()
   //{

   //   if(m_eview == impact_grid && m_iItemHeight > 0)
   //   {

   //      ::rect rectTotal;

   //      _001GetViewRect(&rectTotal);

   //      size sizeTotal = rectTotal.size();

   //      m_sizeTotal.cx = sizeTotal.cx;

   //      m_sizeTotal.cy = sizeTotal.cy / m_iItemHeight;

   //      ::rect rectViewClient;

   //      get_client_rect(&rectViewClient);

   //      m_scrolldata.m_sizePage.cx = rectViewClient.size().cx;

   //      m_scrolldata.m_sizePage.cy = rectViewClient.size().cy / m_iItemHeight;

   //      if(m_scrolldata.m_pointScroll.y > (m_sizeTotal.cy - m_scrolldata.m_sizePage.cy))
   //      {

   //         m_scrolldata.m_pointScroll.y = (m_sizeTotal.cy - m_scrolldata.m_sizePage.cy);

   //      }

   //   }
   //   else
   //   {
   //
   //      ::user::box::on_change_view_size();

   //   }


   //}


   //sized mesh::get_total_size()
   //{

   //   return m_sizeTotal;

   //}


   sized mesh::get_page_size()
   {

      if(m_eview == impact_grid && m_iItemHeight > 0)
      {

         ::rect rectClient;

         get_client_rect(rectClient);

         //auto pointScroll = get_viewport_offset();

         ::size sizePage;

         sizePage.cx = rectClient.width() / m_iDefaultColumnWidth;

         sizePage.cy = rectClient.width() / m_iItemHeight;

         return sizePage;

      }
      else
      {

         return ::user::interaction::get_page_size();

      }

   }


   //bool mesh::get_client_rect(RECT * prect)
   //{

   //   if(m_eview == impact_grid && m_iItemHeight > 0)
   //   {

   //      ::user::interaction::get_client_rect(prect);

   //   }
   //   else
   //   {

   //      ::user::interaction::get_client_rect(prect);

   //   }

   //   return true;

   //}


   void mesh::on_create_draw_item()
   {

      m_pdrawmeshitem            = new draw_mesh_item(this);


   }

   string mesh::_001GetItemId(index iStrictItem)
   {

      return __str(iStrictItem);

   }

   index mesh::_001GetItemById(const char * pszChar)
   {

      ::count c = _001GetItemCount();

      string strId(pszChar);

      for (index iItem = 0; iItem < c; iItem++)
      {

         if (strId == _001GetItemId(iItem))
         {

            return iItem;

         }

      }

      return -1;

   }



} // namespace user



