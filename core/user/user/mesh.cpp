#include "framework.h"
#include "mesh.h"
#include "list.h"
#include "mesh_cache_interface.h"
#include "list_data.h"
#include "list_item.h"
#include "list_column.h"
#include "acme/constant/id.h"
#include "acme/constant/message.h"
#include "acme/constant/timer.h"
#include "acme/constant/user_key.h"
#include "acme/exception/interface_only.h"
#include "acme/handler/item.h"
#include "acme/handler/topic.h"
#include "acme/parallelization/synchronous_lock.h"
#include "acme/prototype/collection/_range.h"
#include "acme/prototype/data/listener.h"
#include "acme/prototype/data/tree_item.h"
#include "acme/prototype/time/_text_stream.h"
#include "acme/platform/keep.h"
#include "acme/platform/timer.h"
#include "apex/database/selection.h"
#include "apex/platform/savings.h"
#include "aura/graphics/draw2d/pen.h"
#include "aura/graphics/image/list.h"
#include "aura/graphics/draw2d/brush.h"
#include "aura/graphics/draw2d/graphics_extension.h"
#include "aura/graphics/draw2d/draw2d.h"
#include "aura/graphics/image/context.h"
#include "aura/graphics/image/image.h"
#include "aura/graphics/image/imaging.h"
#include "aura/graphics/image/drawing.h"
#include "aura/windowing/window.h"
#include "aura/message/user.h"
#include "axis/platform/system.h"
#include "base/user/user/user.h"
#include "core/user/simple/mesh_data.h"
#include "core/platform/session.h"


#define DBLCLKMS 500


//CLASS_DECL_CORE index array_translate_a(index_biunique & ia, index aNew, index aOld);
//CLASS_DECL_CORE index_array array_translate_a_array(index_biunique & ia, index_array iaNew, index_array iaOld);


namespace user
{

   const ::enum_message mesh::MESSAGE_ENDCOLUMNHEADERDRAG = (::enum_message)(WM_USER + 25);
   const ::enum_message mesh::MESSAGE_COLUMNHEADERTRACK = (::enum_message) (WM_USER + 26);
   const ::enum_message mesh::MESSAGE_ENDCOLUMNHEADERTRACK = (::enum_message) (WM_USER + 27);

   mesh::mesh()
   {

      m_sizeMaximumImage.cx() = 16;
      m_sizeMaximumImage.cy() = 16;
      m_dItemHeight = 0.;
      m_plist = nullptr;
      m_piaFilterIcon = ___new index_biunique();
      m_piaFilterMesh = ___new index_array();

      m_econtroltype = ::user::e_control_type_mesh;

      __construct_new(m_piconlayout);

      __construct_new(m_pmeshlayout);

      m_piconlayout->m_iaDisplayToStrict.set_empty_a(-1);
      m_piconlayout->m_iaDisplayToStrict.set_empty_b(-1);

      m_bDrag = false;
      m_eview = impact_grid;
      m_iDisplayItemFocus = -1;
      //m_iDisplayItemHover = -1;
      //m_iSubItemHover = -2;
      m_bDefaultEditHandling = true;
      m_bDefaultKeyboardMultipleSelectionHandling = true;
      m_bSortEnable              = true;
      m_bFilter1                 = false;
      m_nColumnCount             = 1;
      m_iTimerHoverSelect        = 0;

      m_bTopText                 = false;

      m_bEmboss                  = true;
      m_bHoverSelect2            = true;
      m_bMultiSelect             = true;
      m_iLateralGroupWidth       = 200;

      //m_pdrawmeshitem            = nullptr;

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

      m_bLockImpactUpdate = false;


      //m_dItemHeight = 0;
      m_iItemWidth = 0;

      m_iLastItemSel = 0;
      m_iLastSubItemSel = 0;
      m_iItemSel = 0;
      m_iSubItemSel = 0;
      m_iSubItemEnter = -1;
      m_iItemEnter = -1;

      //   m_iItemCount = 0;

      m_pimagelistGroup        = nullptr;
      m_pimagelistGroupHover   = nullptr;


      m_iLeftMargin                       = 0;
      m_iTopMargin                        = 0;

      m_bAutoCreateMeshHeader = true;
      m_bAutoCreateMeshData = true;

      m_nGridItemCount = 0;
      m_nGridColumnCount = 0;

      m_ecachehinting += e_cache_hinting_subitem_color_per_theme_and_state;

      //m_sizeTotal.cx() = 0;
      //m_sizeTotal.cy() = 0;

   }

   mesh::~mesh()
   {
      ::acme::del(m_piaFilterIcon);
      ::acme::del(m_piaFilterMesh);
   }



   // ::core::application* mesh::get_app()
   // {
   //
   //    auto papplication = application();
   //
   //    return ::is_set(papplication) ? papplication : nullptr;
   //
   // }
   //
   //
   // ::core::session* mesh::get_session()
   // {
   //
   //    auto pacmesession = session();
   //
   //    return ::is_set(pacmesession) ? pacmesession : nullptr;
   //
   // }
   //
   //
   // ::core::system* mesh::get_system()
   // {
   //
   //    auto pacmesystem = system();
   //
   //    return ::is_set(pacmesystem) ? pacmesystem : nullptr;
   //
   // }

   void mesh::install_message_routing(::channel * pchannel)
   {

      ::user::interaction::install_message_routing(pchannel);
      ::user::scroll_base::install_message_routing(pchannel);

      bool bList = dynamic_cast <list *> (this) != nullptr;

      MESSAGE_LINK(e_message_size, pchannel, this,&mesh::on_message_size);
      MESSAGE_LINK(e_message_scroll_y, pchannel, this,&mesh::on_message_scroll_y);
      MESSAGE_LINK(e_message_scroll_x, pchannel, this,&mesh::on_message_scroll_x);
      MESSAGE_LINK(e_message_mouse_leave, pchannel, this,&mesh::on_message_mouse_leave);

      if (!bList)
      {
         MESSAGE_LINK(e_message_left_button_down, pchannel, this, &mesh::on_message_left_button_down);
         MESSAGE_LINK(e_message_left_button_up, pchannel, this, &mesh::on_message_left_button_up);
         MESSAGE_LINK(e_message_left_button_double_click, pchannel, this, &mesh::on_message_left_button_double_click);
      }
      MESSAGE_LINK(e_message_right_button_down, pchannel, this,&mesh::on_message_right_button_down);
      MESSAGE_LINK(e_message_right_button_down, pchannel, this, &mesh::on_message_right_button_up);

      MESSAGE_LINK(e_message_mouse_move, pchannel, this,&mesh::on_message_mouse_move);

      MESSAGE_LINK(e_message_key_down, pchannel, this,&mesh::on_message_key_down);

      MESSAGE_LINK(e_message_create, pchannel, this,&mesh::on_message_create);

      add_command_handler("mesh_impact_auto_arrange", { this,  &mesh::_001OnMeshImpactAutoArrange });

      add_command_prober("mesh_impact_auto_arrange", { this,  &mesh::_001OnUpdateMeshImpactAutoArrange });

   }


   void mesh::_001OnDraw(::draw2d::graphics_pointer & pgraphics)
   {

      m_ppenFocused->create_solid(2,argb(255,0,255,255));

      m_ppenHighlight->create_solid(2,argb(255,0,255,255));

      pgraphics->set_text_rendering_hint(::write_text::e_rendering_anti_alias_grid_fit);

      if(m_bLockImpactUpdate)
         return;

      ::user::interaction::_001OnDraw(pgraphics);

      draw_framing(pgraphics);

      auto rectangleX = this->rectangle();


      auto pointScroll = get_context_offset();


      //      pgraphics->SetBkMode(TRANSPARENT);

      if(m_bTopText)
      {

         auto pstyle = get_style(pgraphics);

         auto pbrushText = __øcreate < ::draw2d::brush > ();

         pbrushText->create_solid(get_color(pstyle, ::e_element_text));

         auto offsetContext = pgraphics->offset_context();

         pgraphics->set(pbrushText);
         ::double_size_array sizea;
         m_pgraphicsextension->get_text_extent(pgraphics,m_strTopText,sizea);
         ::collection::index x = 0;
         ::collection::index right = (::collection::index)rectangleX.right();
         double y = m_dItemHeight;
         ::collection::index iStart = 0;
         ::collection::index iNewStart = 0;
         //index w;
         for(::collection::index i = 0; i < sizea.get_size(); i++)
         {

            if((sizea[i].cx() - x > right)
                  || i == sizea.get_upper_bound())
            {
               ::int_rectangle rectangle;
               rectangle.top() = int(y - pointScroll.y());
               if(i == 0)
               {
                  //w = (::collection::index) (sizea[0].cx() - x);
                  x = (::collection::index) (sizea[0].cx());
                  y += sizea[0].cy();
                  iNewStart = 0;

               }
               else
               {
                  //w = (::collection::index) (sizea[i - 1].cx() - x);
                  x = (::collection::index) (sizea[i - 1].cx());
                  y += sizea[i - 1].cy();
                  iNewStart = i - 1;
               }
               rectangle.left() = int(- pointScroll.x());
               rectangle.right() = rectangleX.right();
               rectangle.bottom() = int(y - pointScroll.y());

               pgraphics->_DrawText(m_strTopText.substr(iStart,i - iStart),rectangle,e_align_left);
               iStart = iNewStart;
            }
         }
         //pgraphics->set_origin(pointContextOrg);
      }


//      if(m_pmeshdata != nullptr)
//      {
//         if(m_pmeshdata->is_locked())
//         {
//            return;
//         }
//      }




//      m_pdrawmeshitem->m_pgraphics              = pgraphics;
//      m_pdrawmeshitem->m_iItemRectItem          = -1;
//      m_pdrawmeshitem->m_iSubItemRectOrder      = -1;
//      m_pdrawmeshitem->m_iSubItemRectSubItem    = -1;
//      m_pdrawmeshitem->m_iSubItemRectItem       = -1;
//      m_pdrawmeshitem->m_iSubItemRectColumn     = -1;
////      m_pdrawmeshitem->m_iWidthColumn           = -1;
//      m_pdrawmeshitem->m_iColumnWidth           = 0;

      ::int_rectangle rectangleItem;
      ::int_rectangle rectangleIntersect;
      auto iItemCount = m_nDisplayCount;
      auto iItemFirst = m_iTopDisplayIndex;
      decltype(iItemCount) iItemLast;
      if(m_eview == impact_icon)
      {
         iItemLast = iItemCount;
      }
      else
      {
         iItemLast = minimum(m_nItemCount - 1,iItemFirst + m_nDisplayCount - 1);
      }

      if (iItemFirst < 0)
      {

         return;

      }

      _001DrawItems(pgraphics, (::collection::index) iItemFirst, (::collection::index) iItemLast);

      if(m_bGroup && m_bLateralGroup)
      {

         ::collection::index iGroupFirst = 0;
         ::collection::index iGroupFirstTopIndex = 0;
         for(; iGroupFirst < m_nGroupCount; iGroupFirst++)
         {
            if(iItemFirst >= iGroupFirstTopIndex && iItemFirst < (iGroupFirstTopIndex + _001GetGroupItemCount((::collection::index) iGroupFirst)))
               break;
         }
         ::collection::index iGroupLast = iGroupFirst;
         ::collection::index iGroupLastTopIndex = iGroupFirstTopIndex;
         for(; iGroupLast < m_nGroupCount; iGroupLast++)
         {
            if(iItemLast >= iGroupLastTopIndex && iItemLast < (iGroupLastTopIndex + _001GetGroupItemCount((::collection::index) iGroupLast)))
               break;
         }

         //_001DrawGroups(pgraphics, (::collection::index) iGroupFirst, (::collection::index) iGroupLast, (::collection::index) iItemFirst, (::collection::index) iItemLast);
         _001DrawGroups(pgraphics, (::collection::index)iGroupFirst, (::collection::index)iGroupLast);

      }

   }


   //void mesh::_001DrawGroups(::draw2d::graphics_pointer & pgraphics, ::collection::index iGroupFirst, ::collection::index iGroupLast, ::collection::index iItemFirst, ::collection::index iItemLast)
   void mesh::_001DrawGroups(::draw2d::graphics_pointer & pgraphics, ::collection::index iGroupFirst, ::collection::index iGroupLast)
   {

      //__UNREFERENCED_PARAMETER(iItemFirst);
      //__UNREFERENCED_PARAMETER(iItemLast);

      ::collection::index iGroup;

      ::int_rectangle rectangleX;

      ::int_rectangle rectangleIntersect;

      rectangleX = this->rectangle();

      bool bHoverFont = false;

      for(iGroup = iGroupFirst; iGroup <= iGroupLast; iGroup++)
      {

         auto & pgroup = m_mapGroup[iGroup];

         if (!pgroup)
         {

            auto pdrawgroup = __allocate draw_mesh_group();

            pdrawgroup->initialize_draw_mesh_group(this);

            pdrawgroup->m_iGroup = iGroup;

            pgroup = pdrawgroup;

         }

         pgroup->m_pdrawmeshgroup->m_pgraphics = pgraphics;

         pgroup->m_pdrawmeshgroup->m_pgraphics->set_font(this, ::e_element_none);
         //pdrawitem->m_pgraphics->set(pfont);

         pgroup->m_pdrawmeshgroup->m_pfont = pgroup->m_pdrawmeshgroup->m_pgraphics->m_pfont;

         pgroup->m_iGroup          = iGroup;

         _001GetGroupRect(*pgroup);

         if(!pgroup->m_bOk)
            continue;

         if(!rectangleIntersect.intersect(pgroup->m_pdrawmeshgroup->m_rectangleGroup,rectangleX))
            continue;

         if(iGroup == m_iGroupHover)
         {
            
            if(!bHoverFont)
            {
               
               pgroup->m_pdrawmeshgroup->m_pgraphics->set_font(this, ::e_element_none, ::user::e_state_hover);

            }

         }
         else
         {
            
            if(bHoverFont)
            {

               pgroup->m_pdrawmeshgroup->m_pgraphics->set_font(this, ::e_element_none);

            }

         }

         _001DrawGroup(*pgroup);

      }

   }


   void mesh::_001DrawGroup(draw_mesh_group * pdrawgroup)
   {

      /*if(m_bGroupCustomDraw)
      {
      pdrawitem->m_bMeshSubItemHover = pdrawitem->m_bListItemHover && (pdrawitem->m_iSubItem == m_iSubItemHover);
      pdrawitem->m_bFocus = false;
      return;
      }*/

      _001GetGroupElementRect(pdrawgroup,::user::mesh::e_group_element_image);

      if(pdrawgroup->m_bOk)
      {

         pdrawgroup->draw_group_image();

      }

      ::collection::count nItem = _001GetGroupMetaItemCount((::collection::index)pdrawgroup->m_iGroup);

      for(pdrawgroup->m_iItem = 0; pdrawgroup->m_iItem < nItem; pdrawgroup->m_iItem++)
      {
         
         _001GetGroupElementRect(pdrawgroup,::user::mesh::e_group_element_item_text);
         
         if(pdrawgroup->m_bOk)
         {
            
            _001GetGroupItemText(pdrawgroup);
            
            pdrawgroup->draw_text();

         }

      }

   }


   void mesh::_001DrawItems(::draw2d::graphics_pointer & pgraphics, ::collection::index iItemFirst, ::collection::index iItemLast)
   {

      auto rectangleX = this->rectangle();

      ::int_rectangle rectangleVisible(rectangleX);

      //rectangleVisible.deflate(2,2);

      ::int_rectangle rectangleIntersect;

      bool bHoverFont = false;

      ::collection::index iDisplayItem;

      for(iDisplayItem = iItemFirst; iDisplayItem <= iItemLast; iDisplayItem++)
      {

         auto iItem = display_to_strict(iDisplayItem);

         auto pitem = get_item(iItem);

         if (m_eview == impact_icon)
         {

            pitem->m_pdrawmeshitem->m_ealign = e_align_top_center;

            pitem->m_pdrawmeshitem->m_edrawtext = { e_draw_text_end_ellipsis, e_draw_text_word_break };

         }
         else
         {

            pitem->m_pdrawmeshitem->m_ealign = e_align_left_center;

            pitem->m_pdrawmeshitem->m_edrawtext = { e_draw_text_end_ellipsis, e_draw_text_single_line };

         }

         pitem->m_pdrawmeshitem->m_pgraphics = pgraphics;

         pitem->m_pdrawmeshitem->m_pgraphics->set_font(this, ::e_element_none);

         pitem->m_pdrawmeshitem->m_pfont = pitem->m_pdrawmeshitem->m_pgraphics->m_pfont;

         pitem->m_iDisplayItem = iDisplayItem;

         //if(m_bGroup)
         //{

         //   m_pdrawmeshitem->m_iGroupTopDisplayIndex = 0;

         //   for(m_pdrawmeshitem->m_iGroup = 0; m_pdrawmeshitem->m_iGroup < m_nGroupCount; m_pdrawmeshitem->m_iGroup++)
         //   {

         //      m_pdrawmeshitem->m_iGroupCount = _001GetGroupItemCount((::collection::index) m_pdrawmeshitem->m_iGroup);

         //      if(iDisplayItem >= m_pdrawmeshitem->m_iGroupTopDisplayIndex && iDisplayItem < (m_pdrawmeshitem->m_iGroupTopDisplayIndex + m_pdrawmeshitem->m_iGroupCount))
         //      {

         //         break;

         //      }

         //   }

         //}

         index_item_rectangle(*pitem);

         if(!pitem->m_bOk)
         {

            continue;

         }

         if(!rectangleIntersect.intersect(pitem->m_pdrawmeshitem->m_rectangleItem,rectangleVisible))
         {

            continue;

         }

         if(m_pitemHover && iDisplayItem == m_pitemHover->m_item.m_iItem)
         {

            if(!bHoverFont)
            {

               bHoverFont = true;

               pitem->m_pdrawmeshitem->m_pgraphics->set_font(this, ::e_element_none, ::user::e_state_hover);

            }

         }
         else
         {

            if(bHoverFont)
            {

               bHoverFont = false;

               pitem->m_pdrawmeshitem->m_pgraphics->set_font(this, ::e_element_none);

            }

         }

         _001DrawItem(*pitem);

      }

   }


   void mesh::_001DrawItem(draw_mesh_item * pdrawitem)
   {

      pdrawitem->m_iState = 0;

      range & rangeSelection = m_rangeSelection;

      range & rangeHighlight = m_rangeHighlight;

      auto rectangleX = this->rectangle();

      if (pdrawitem->m_iItem < 0)
      {

         return;

      }

      pdrawitem->m_bListItemHover = m_pitemHover &&
         pdrawitem->m_iDisplayItem == m_pitemHover->m_item.m_iItem &&
                                    (m_eview != impact_icon ||
                                     ((m_piconlayout->m_iaDisplayToStrict.get_a((::collection::index)m_pitemHover->m_item.m_iItem) >= 0 && m_piconlayout->m_iaDisplayToStrict.get_a((::collection::index)m_pitemHover->m_item.m_iItem) < m_nItemCount)));

      if(pdrawitem->m_bListItemHover)
      {
         pdrawitem->m_pgraphics->fill_rectangle(pdrawitem->m_rectangleItem,argb(128,255,255,255));
         pdrawitem->m_pgraphics->set_font(this, ::e_element_none, ::user::e_state_hover);
      }
      else
      {
         pdrawitem->m_pgraphics->set_font(this, ::e_element_none);
      }
//      pdrawitem->m_pgraphics->set_font(pfont);

      pdrawitem->m_bListItemSelected = (m_eview != impact_icon || is_valid_display_item((::collection::index) pdrawitem->m_iItem)) && rangeSelection.has_item((::collection::index) pdrawitem->m_iDisplayItem);

      if(pdrawitem->m_bListItemHover)
         pdrawitem->m_iState |= ItemStateHover;
      if(pdrawitem->m_bListItemSelected)
         pdrawitem->m_iState |= ItemStateSelected;

      

      if(pdrawitem->m_bListItemSelected)
      {
         if(session()->savings()->is_trying_to_save(::e_resource_processing))
         {
            pdrawitem->m_pgraphics->fill_rectangle(pdrawitem->m_rectangleItem,argb(255,96,96,96));
         }
         else
         {
            
            ::color::color crTranslucid = rgb(0,0,0);
            
            ::int_rectangle rectangle = pdrawitem->m_rectangleItem;
         
            rectangle.inflate(8,0,8,-1);
            
            pdrawitem->m_pgraphics->fill_rectangle(rectangle, crTranslucid & ::opacity(127));
            
         }
         
      }

      // pdrawitem->update_color();
      //pdrawitem->set_text_color();

      string str;

      ::collection::index iColumnCount;

      if(m_eview == impact_icon)
      {
         iColumnCount = 1;
      }
      else
      {
         iColumnCount = m_nColumnCount;
      }

      //pdrawitem->m_iSubItemRectOrder      = -1;
      //pdrawitem->m_iSubItemRectSubItem    = -1;
      //pdrawitem->m_iSubItemRectColumn     = -1;

      ::int_rectangle rectangleIntersect;

      //if(m_eview == impact_grid)
      //{

      //   pdrawitem->m_iOrder = maximum(get_context_offset().x(), 0);

      //}
      //else
      //{

      //   pdrawitem->m_iOrder = 0;

      //}

      ::collection::index iOrder = 0;

      for(; iOrder < iColumnCount; iOrder++)
      {

         auto psubitem = get_subitem(pdrawitem, iOrder);

         //pdrawitem->m_iColumn    = _001MapOrderToColumn((::collection::index) iOrder);

         //if(pdrawitem->m_iColumn < 0)
         //   continue;


         //_001GetSubItemRect(pdrawitem);

         //if(!rectangleIntersect.intersect(m_pdrawmeshitem->m_rectangleSubItem,rectangleX))
         //   break;

         //if(!pdrawitem->m_bOk)
         //   continue;


         //_001DrawSubItem(pdrawitem);

      }

      if(rangeHighlight.has_item((::collection::index) pdrawitem->m_iDisplayItem))
      {

         auto ppenHighlight = _001GetPenHighlight();

         ::int_rectangle rectangleHighlight(pdrawitem->m_rectangleItem);

         rectangleHighlight.inflate(8,0,8,-1);

         pdrawitem->m_pgraphics->set(ppenHighlight);

         pdrawitem->m_pgraphics->draw_rectangle(rectangleHighlight);

      }

   }


   void mesh::draw_framing(::draw2d::graphics_pointer & pgraphics)
   {

   }


   void mesh::_001DrawSubItem(draw_mesh_subitem * psubitem)
   {

      //pdrawitem->m_iListItem = -1;

      index_element_rectangle(psubitem,::user::mesh::e_element_image);

      if(psubitem->m_bOk)
      {
         try
         {
            _001GetSubItemImage(psubitem);
         }
         catch(...)
         {
            psubitem->m_bOk = false;
         }
         psubitem->draw_image();
      }
      
      //psubitem->m_iListItem = -1;
      
      index_element_rectangle(psubitem,::user::mesh::e_element_text);

      if(psubitem->m_bOk)
      {

         try
         {

            _001GetSubItemText(psubitem);

         }
         catch(...)
         {
            
            psubitem->m_bOk = false;

         }

         if(psubitem->m_bOk)
         {

            psubitem->draw_text();

         }

      }

   }


   ::pointer<mesh_item>& mesh::get_item(::collection::index iItem)
   {

      auto & pitem = m_mapItem[iItem];

      if (!pitem)
      {

         auto pdrawmeshitem = __allocate draw_mesh_item();

         pdrawmeshitem->initialize_draw_mesh_item(this);

         pdrawmeshitem->m_iItem = iItem;

         //pdrawmeshitem->m_iItemRectItem = -1;
         //pdrawmeshitem->m_iSubItemRectOrder = -1;
         //pdrawmeshitem->m_iSubItemRectSubItem = -1;
         //pdrawmeshitem->m_iSubItemRectItem = -1;
         //pdrawmeshitem->m_iSubItemRectColumn = -1;
         //pdrawmeshitem->m_iColumn = -1;
         pdrawmeshitem->m_iColumnWidth = 0;
         //pdrawmeshitem->m_ealign = get_draw_text_align(m_eview);
         //pdrawmeshitem->m_edrawtext = get_draw_text_flags(m_eview);

         pitem = pdrawmeshitem;

      }

      return pitem;

   }


   ::pointer<mesh_subitem>& mesh::get_subitem(mesh_item * pitem, ::collection::index iSubItem)
   {

      auto & psubitem = pitem->m_mapSubItem[iSubItem];

      if (!psubitem)
      {

         psubitem = __allocate draw_mesh_subitem();

         psubitem->m_pitem = pitem;

         //psubitem->m_pcolumn = m_columna.get_by_subitem(iSubItem);

         psubitem->m_iSubItem = iSubItem;

      }

      return psubitem;

   }


   ::pointer<mesh_subitem>& mesh::get_subitem(::collection::index iItem, ::collection::index iSubItem)
   {

      auto & pitem = get_item(iItem);

      return get_subitem(pitem.m_p, iSubItem);

   }


   void mesh::_001GetSubItemImage(::user::mesh_subitem * psubitem)
   {

      if(m_pmeshdata != nullptr)
      {

//         psubitem->m_pmesh = this;

         try
         {

            return m_pmeshdata->_001GetSubItemImage(psubitem);

         }
         catch(...)
         {

            informationf("_001GetItemImage exception");

         }

      }
      /*LVITEM lvi;
      lvi.mask = LVIF_IMAGE;
      lvi.iItem = iItem;
      lvi.iSubItem = 0;
      get_item(&lvi);
      return lvi.iImage;*/
      psubitem->m_bOk = false;

   }


   void mesh::_001SetSubItemText(::user::mesh_subitem * pitem)
   {

      pitem->m_bOk = false;

   }


   void mesh::_001GetSubItemText(::user::mesh_subitem * psubitem)
   {
      
      psubitem->m_bOk = false;

      if(::is_set(m_pmeshcache))
      {
         
         m_pmeshcache->_001GetSubItemText(psubitem);

         if (psubitem->m_bOk)
         {

            return;

         }

      }

      if(m_pmeshdata != nullptr)
      {

         m_pmeshdata->_001GetSubItemText(psubitem);

      }

   }


   // Purpose:
   // Provide Item Text for Search Purposes.
   void mesh::_001SearchGetSubItemText(::user::mesh_subitem * psubitem)
   {

      _001GetSubItemText(psubitem);

   }


   /*bool mesh::pre_create_window(::user::system * pusersystem)
   {

   //pusersystem->m_createstruct.style |= LVS_NOSCROLL;

   return window::pre_create_window(pusersystem);
   }*/

   /*void mesh::OnSize(unsigned int nType, index cx, index cy)
   {
   window::OnSize(nType, cx, cy);

   set_need_layout();
   }*/

   void mesh::on_message_size(::message::message * pmessage)
   {
      __UNREFERENCED_PARAMETER(pmessage);
      //::pointer<::message::size>psize(pmessage);
      //set_need_layout();
      //psize->m_bRet = false;
   }


   void mesh::on_layout(::draw2d::graphics_pointer & pgraphics)
   {

      _synchronous_lock synchronouslock(this->synchronization());

      _001CalculateItemHeight(pgraphics);

      //m_dItemHeight = m_sizeMaximumItem.cy() + 1;

      if(m_bTopText)
      {

         _001LayoutTopText(pgraphics);

      }

      m_iTopDisplayIndex       = _001CalcDisplayTopIndex();

      if(m_eview == impact_grid)
      {

         m_iItemWidth      = (int) (m_nColumnCount * m_iDefaultColumnWidth);

      }

      ::collection::index iLow = 0;

      for(m_iTopGroup = 0; m_iTopGroup < m_nGroupCount; m_iTopGroup++)
      {

         if(m_iTopDisplayIndex >= iLow && m_iTopDisplayIndex < (iLow + _001GetGroupItemCount((::collection::index) m_iTopGroup)))
            break;

      }

      m_nDisplayCount   = _001CalcDisplayItemCount();

      on_would_change_total_size(::user::e_layout_design);



      //if (m_eview == impact_icon)
      //{
      //   //            if(m_piconlayout->m_iWidth <= 0)
      //   {
      //      ::int_rectangle rectangleX;
      //      this->rectangle(rectangleX);
      //      index iIconSize;
      //      if (m_nColumnCount > 0)
      //         //                  iIconSize = maximum(32,m_columna[0]->m_sizeIcon.cy());
      //         iIconSize = 32;
      //      else
      //         iIconSize = 32;
      //      index iItemSize = iIconSize * 2;
      //      m_piconlayout->m_iWidth = (int)(maximum(1, rectangleX.width() / iItemSize));
      //   }
      //}


   }


   void mesh::insert_columns()
   {

      on_insert_columns();

   }


   void mesh::on_insert_columns()
   {


   }


   void mesh::erase_columns()
   {


   }


   void mesh::set_pending_column_layout()
   {

      m_bPendingColumnLayout = true;

   }


   void mesh::set_pending_column_update()
   {

      m_bPendingColumnUpdate = true;

   }


   void mesh::on_column_update()
   {

      erase_columns();

      auto keepLockImpactUpdate = keep(m_bLockImpactUpdate);

      on_insert_columns();

      keepLockImpactUpdate.KeepAway();

      DIDDXHeaderLayout(false);

      //_001OnColumnChange();


//      __UNREFERENCED_PARAMETER(dwFlags);

      if(m_eview == impact_grid)
      {

         auto rectangleX = this->rectangle();

         ::int_size sizePage = rectangleX.size();

         m_nGridColumnCount = _001GetColumnCount();

         m_nColumnCount = maximum(m_nColumnCount,sizePage.cx() * 2);

         m_nColumnCount = minimum(m_nColumnCount,m_nGridColumnCount);

      }
      else
      {

         m_nColumnCount = _001GetColumnCount();

      }

      if(m_nColumnCount < 0)
      {

         return;

      }

      set_need_layout();

   }


   void mesh::on_update_item_count()
   {

      _synchronous_lock synchronouslock(this->synchronization());

      //__UNREFERENCED_PARAMETER(dwFlags);

      if(m_eview == impact_grid)
      {

         auto rectangleX = this->rectangle();

         ::int_size sizePage = rectangleX.size();

         m_nGridItemCount = _001GetItemCount();

         m_nItemCount = maximum(m_nItemCount, sizePage.cy() * 2);

         m_nItemCount = minimum(m_nItemCount,m_nGridItemCount);

      }
      else
      {

         m_nItemCount = _001GetItemCount();

         if(m_nItemCount > 0)
         {

            information() << "m_nItemCount > 0";

         }

      }

      if(m_nItemCount < 0)
      {

         return;

      }

      if(m_bGroup)
      {

         m_nGroupCount = _001GetGroupCount();

         if(m_nGroupCount < 0)
         {

            return;

         }

      }

      if(m_eview == impact_icon)
      {
         for(::collection::index iStrict = 0; iStrict < m_nItemCount; iStrict++)
         {
            if(m_piconlayout->m_iaDisplayToStrict.get_a(iStrict) == -1)
            {
               m_piconlayout->m_iaDisplayToStrict.set(m_piconlayout->m_iaDisplayToStrict.get_free_a(),iStrict);
            }
         }
      }
      else
      {
         ::collection::index iStart = m_pmeshlayout->m_iaDisplayToStrict.get_count();
         ::collection::index iEnd = m_nItemCount - 1;
         m_pmeshlayout->m_iaDisplayToStrict.set_size((::collection::count) m_nItemCount);
         for(::collection::index iStrict = iStart; iStrict <= iEnd; iStrict++)
         {
            m_pmeshlayout->m_iaDisplayToStrict.set_at((::collection::index) iStrict, (::collection::index) iStrict);
         }
      }

      if(m_bFilter1)
      {
         FilterApply();
      }

      cache_hint();

      set_need_layout();

      set_need_redraw();

      //auto psystem = system();

      //auto pdraw2d = psystem->draw2d();

      //auto pgraphics = pdraw2d->create_memory_graphics(this);

      //on_change_impact_size(pgraphics);

      //informationf("mesh::_001OnUpdateItemCount ItemCount %d\n",m_nItemCount);
      //if(m_bGroup)
      //{
        // informationf("mesh::_001OnUpdateItemCount GroupCount %d\n",m_nGroupCount);
      //}

      //return true;
   }


   bool mesh::on_impact_update()
   {

      if (!::user::scroll_base::on_impact_update())
      {

         return false;

      }

      if (m_bPendingColumnUpdate)
      {

         m_bPendingColumnUpdate = false;

         on_column_update();

      }

      on_update_item_count();

      return true;

   }


   void mesh::on_would_change_total_size(::user::enum_layout elayout)
   {

      auto scrollstatex = get_scroll_state_x(elayout);

      auto scrollstatey = get_scroll_state_y(elayout);

      //::int_size sizeTotal = get_total_size(::user::e_layout_sketch);

      if(m_eview == impact_grid)
      {

         scrollstatey.set_dimension((int) m_nColumnCount);
         scrollstatex.set_dimension((int) m_nItemCount);

      }
      else if(m_eview == impact_list)
      {

         if(m_nItemCount == 0)
         {
            scrollstatey.set_dimension((int)0);
            scrollstatex.set_dimension((int)0);
         }
         else
         {

            auto rectangle = this->rectangle();

            scrollstatey.set_dimension(rectangle.height());

            auto pitemFirst = get_item(0);

            pitemFirst->m_iDisplayItem = 0;

            index_item_rectangle(*pitemFirst);

            if (m_dItemHeight <= 0)
            {

               scrollstatex.set_dimension(rectangle.right());

            }
            else
            {

               scrollstatex.set_dimension((int) minimum(
                       m_nItemCount * pitemFirst->m_pdrawlistitem->m_rectangleItem.width() * m_dItemHeight /
                       rectangle.height()
                       + pitemFirst->m_pdrawlistitem->m_rectangleItem.width(), I32_MAXIMUM));

            }

         }
      }
      else if(m_eview == impact_report)
      {
         if(m_nItemCount == 0)
         {
            scrollstatey.set_dimension(0);
            scrollstatex.set_dimension(0);
         }
         else
         {

            ::int_rectangle rectangle;

            auto pitemFirst = get_item(0);

            pitemFirst->m_iDisplayItem = 0;

            index_item_rectangle(*pitemFirst);

            auto pitemLast = get_item(m_nItemCount-1);

            pitemLast->m_iDisplayItem = m_nItemCount-1;

            if(m_bFilter1)
            {
               pitemLast->m_iDisplayItem       = m_piaFilterMesh->get_count() - 1;
               pitemLast->m_iItem              = m_piaFilterMesh->get_count() - 1;
            }
            else
            {
               pitemLast->m_iDisplayItem       = m_nItemCount - 1;
               pitemLast->m_iItem              = m_nItemCount - 1;
            }
            //if(m_bGroup)
            //{
            //   pitemLast->m_iGroupTopDisplayIndex = 0;
            //   //               int igroup;
            //   for(itemLast.m_iGroup = 0; itemLast.m_iGroup < m_nGroupCount; itemLast.m_iGroup++)
            //   {
            //      itemLast.m_iGroupCount = _001GetGroupItemCount((::collection::index) itemLast.m_iGroup);
            //      if(itemLast.m_iItem >= itemLast.m_iGroupTopDisplayIndex && itemLast.m_iItem < (itemLast.m_iGroupTopDisplayIndex + itemLast.m_iGroupCount))
            //         break;
            //   }
            //}
            index_item_rectangle(*pitemLast);

//            itemLast.m_rectangleItem.right()     -= (m_scrollstate.m_rectangleMargin.left() + m_scrollstate.m_rectangleMargin.right());
            //          itemLast.m_rectangleItem.bottom()    -= (m_scrollstate.m_rectangleMargin.top() + m_scrollstate.m_rectangleMargin.bottom());

            rectangle.unite(pitemFirst->m_pdrawlistitem->m_rectangleItem,pitemLast->m_pdrawlistitem->m_rectangleItem);

            scrollstatex.set_dimension(rectangle.size().cx());

            scrollstatey.set_dimension(rectangle.size().cy());

         }

      }
      else if(m_eview == impact_icon)
      {

         ::int_rectangle rectangle;

         auto pitemFirst = get_item(0);

         pitemFirst->m_iDisplayItem      = 0;

         index_item_rectangle(*pitemFirst);

         auto pitemLast = get_item(m_nItemCount - 1);

         pitemLast->m_iDisplayItem       = m_nItemCount - 1;

         index_item_rectangle(*pitemLast);

         //draw_mesh_item itemTopRight(this);
//         if(m_flags.has(flag_auto_arrange) || m_piconlayout->m_iWidth <= 0)
         //{
         //   ::int_rectangle rectangleX;

         //   this->rectangle(&rectangleX);

         //   itemTopRight.m_iItem = (index)maximum(1,rectangleX.width() / get_item_size().cx()) - 1;
         //}
         /*       else
                {
                   itemTopRight.m_iItem = maximum(1,m_piconlayout->m_iWidth) - 1;
                }
         */       
         //itemTopRight.m_iDisplayItem = itemTopRight.m_iDisplayItem;
         //index_item_rectangle(&itemTopRight);

         rectangle.unite(pitemFirst->m_pdrawlistitem->m_rectangleItem,pitemLast->m_pdrawlistitem->m_rectangleItem);

         //rectangle.unite(rectangle,itemTopRight.m_rectangleItem);

         scrollstatex.set_dimension(rectangle.size().cx());

         scrollstatey.set_dimension(rectangle.size().cy());

      }

      set_scroll_state_x(scrollstatex, elayout);

      set_scroll_state_y(scrollstatey, elayout);

      on_change_scroll_state(elayout);


//      ::user::box::on_change_impact_size();

   }


   void mesh::_001OnInitialize()
   {

   }





   void mesh::_thread_data_update_visible_subitem()
   {

      return;

//      _synchronous_lock synchronouslock(m_pmutexData);

//      index iColumn;

//      index_array iaVisible;


   }



   //void mesh::_001GetColumnWidth(draw_mesh_item * pitem)
   //{

   //   int iWidth;

   //   if(!m_mapColumnWidth.lookup((::collection::index) pitem->m_iColumn,iWidth))
   //   {

   //      iWidth = m_iDefaultColumnWidth;

   //   }

   //   pitem->m_iColumnWidth   = iWidth;

   //   pitem->m_bOk            = true;

   //}


   ::collection::index mesh::sub_item_to_order(::collection::index iSubItem)
   {
      return _001MapColumnToOrder(_001MapSubItemToColumn(iSubItem));
   }

   ::collection::index mesh::_001MapOrderToSubItem(::collection::index iOrder)
   {
      return _001MapColumnToSubItem(_001MapOrderToColumn(iOrder));
   }


   ::collection::index mesh::_001MapOrderToColumn(::collection::index iOrder)
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


   ::collection::index mesh::_001MapColumnToOrder(::collection::index iColumn)
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

   ::collection::index mesh::_001MapSubItemToColumn(::collection::index iSubItem)
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

   ::collection::index mesh::_001MapColumnToSubItem(::collection::index iColumn)
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


   ::collection::count mesh::_001GetItemCount()
   {

      if(m_pmeshdata.is_null())
         return -1;

      return m_pmeshdata->_001GetItemCount();

   }


   ::collection::count mesh::_001GetGroupCount()
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
   ::collection::index mesh::_001CalcDisplayTopIndex()
   {


      if(m_eview == impact_grid)
      {

         return (::collection::index) minimum(maximum(0,get_context_offset().y()),m_nGridItemCount);

      }
      else
      {

         auto pointScroll = get_context_offset();

         ::collection::index iItem;

         if(_001DisplayHitTest(::int_point((int)(pointScroll.x() < 0 ? -pointScroll.x() : 0), (int)(m_dItemHeight + (pointScroll.y() < -0 ? -pointScroll.y() : 0))),iItem))
         {

            return (::collection::index) iItem;

         }
         else
         {

            if(m_eview == impact_report || m_eview == impact_grid)
            {

               if(pointScroll.y() < 0)
               {

                  return 0;

               }

            }

            return -1;

         }

      }

   }

   ::collection::count mesh::_001CalcDisplayItemCount()
   {

      if(m_eview == impact_grid)
      {

         ::int_rectangle rectangleScroll;

         rectangleScroll = this->rectangle();

         if(m_dItemHeight == 0)
         {

            return 0;

         }
         else
         {

            if(m_bTopText)
            {
               return (::collection::count) (rectangleScroll.height() - m_rectangleTopText.height() / m_dItemHeight);
            }
            else
            {
               return rectangleScroll.height();
            }

         }

      }
      if(m_eview == impact_icon)
      {
         
         ::int_rectangle rectangleImpact;

         rectangleImpact = this->rectangle();

         const ::int_size & sizeItem = get_item_size();

         return maximum((rectangleImpact.width() / sizeItem.cx()) * (rectangleImpact.height() / sizeItem.cy()),
                    m_piconlayout->m_iaDisplayToStrict.get_max_a() + 1);

      }
      else if(m_eview == impact_report || m_eview == impact_grid)
      {
         
         ::int_rectangle rectangleImpact;

         rectangleImpact = this->rectangle();
         
         if(m_dItemHeight == 0.)
         {
            
            return 0;

         }
         else
         {

            if(m_bTopText)
            {

               return (int)((rectangleImpact.height() - m_rectangleTopText.height()) / m_dItemHeight);

            }
            else
            {

               return (int)(rectangleImpact.height() / m_dItemHeight);

            }

         }

      }

      ::collection::index iItemCount;
      if(m_bFilter1 && (m_eview == impact_list || m_eview == impact_report || m_eview == impact_grid))
      {
         iItemCount = m_piaFilterMesh->get_count();
      }
      else
      {
         iItemCount = m_nItemCount;
      }
      ::collection::index iItemFirst = m_iTopDisplayIndex;
      ::collection::index iItemLast = iItemFirst;
      ::int_rectangle rectangleItem;
      ::int_rectangle rectangleIntersect;
      ::int_rectangle rectangleUpdate;
      rectangleUpdate = this->rectangle();
      auto pitem = get_item(iItemFirst);
      if(iItemFirst >= 0)
      {
         iItemLast = -1;
         for(::collection::index i = iItemFirst + 1; i < iItemCount; i++)
         {
            pitem->m_iDisplayItem  = i;
            //if(m_bGroup)
            //{
            //   item.m_iGroupTopDisplayIndex = 0;
            //   for(item.m_iGroup = 0; item.m_iGroup < m_nGroupCount; item.m_iGroup++)
            //   {
            //      item.m_iGroupCount = _001GetGroupItemCount((::collection::index) item.m_iGroup);
            //      if(i >= item.m_iGroupTopDisplayIndex && i < (item.m_iGroupTopDisplayIndex + item.m_iGroupCount))
            //         break;
            //   }
            //}

            index_item_rectangle(*pitem);
            if(pitem->m_bOk)
            {
               if(!rectangleIntersect.intersect(pitem->m_pdrawlistitem->m_rectangleItem,rectangleUpdate))
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


   bool mesh::_001HitTest_(const ::int_point & point, ::collection::index &iItem, ::collection::index&iSubItem, ::collection::index&iListItem,::user::mesh::enum_element &eelement)
   {
      __UNREFERENCED_PARAMETER(point);
      __UNREFERENCED_PARAMETER(iItem);
      __UNREFERENCED_PARAMETER(iSubItem);
      __UNREFERENCED_PARAMETER(iListItem);
      __UNREFERENCED_PARAMETER(eelement);
      return false;
   }


   bool mesh::_001HitTest_(const ::int_point & point, ::collection::index &iItem, ::collection::index&iSubItem)
   {

      if (!_001DisplayHitTest(point, iItem, iSubItem))
      {

         return false;

      }

      iItem = display_to_strict((::collection::index) iItem);

      return true;

   }


   bool mesh::_001HitTest_(const ::int_point & point, ::collection::index & iItem)
   {

      if (!_001DisplayHitTest(point, iItem))
      {

         return false;

      }

      iItem = (::collection::index) display_to_strict((::collection::index) iItem);

      return true;

   }


   bool mesh::_001DisplayHitTest(const ::int_point & point, ::collection::index & iItem, ::collection::index & iSubItem, ::collection::index & iListItem,::user::mesh::enum_element &eelement)
   {

      __UNREFERENCED_PARAMETER(point);
      __UNREFERENCED_PARAMETER(iItem);
      __UNREFERENCED_PARAMETER(iSubItem);
      __UNREFERENCED_PARAMETER(iListItem);
      __UNREFERENCED_PARAMETER(eelement);

      return false;

   }


   bool mesh::_001DisplayHitTest(const ::int_point & point, ::collection::index & iItemParam, ::collection::index & iSubItemParam)
   {

      ::collection::index iItem;

      if(!_001DisplayHitTest(point,iItem))
      {

         return false;

      }

      auto pointScroll = get_context_offset();

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
      ::collection::index iColumnCount = m_nColumnCount;
      int iLeft =(int)pointScroll.x();
      if(m_bGroup && m_bLateralGroup)
         iLeft += m_iLateralGroupWidth;
      //int iRight;
      // draw_mesh_item item(this);
      if(point.x() < iLeft)
         return false;
      //for(::collection::index iColumn = 0; iColumn < iColumnCount; iColumn++)
      //{
      //   //m_collumna->get_visible(iColumn)->m_iWid;
      //   if(!item.m_bOk)
      //      continue;
      //   iRight = iLeft + item.m_iColumnWidth;
      //   if(iLeft <= point.x() && point.x() < iRight)
      //   {
      //      iItemParam = iItem;
      //      iSubItemParam = _001MapColumnToSubItem(item.m_iColumn);
      //      return true;
      //   }
      //   iLeft = iRight;
      //}
      return false;
   }

   bool mesh::_001DisplayHitTest(const ::int_point & point, ::collection::index & iItemParam)
   {

      {

         auto rectangleX = this->rectangle();

         if(point.x() < 0
               || point.x() > rectangleX.right()
               || point.y() < 0
               || point.y() > rectangleX.bottom())
         {

            return false;

         }

      }

      auto pointScroll = get_context_offset();

      if(m_eview == impact_report || m_eview == impact_grid)
      {

         auto dy = point.y() + pointScroll.y();

         auto dItem = -1.;

         if (m_dItemHeight != 0)
         {

            dItem = dy / m_dItemHeight;

         }

         if (dItem < 0.)
         {

            return false;

         }

         dItem-=1.0;

         if(dItem < 0.0)
            return false;
         //}

         if(m_bFilter1)
         {
            if((::collection::index) dItem >= m_piaFilterMesh->get_count())
               return false;
         }

         if((::collection::index) dItem >= m_nItemCount)
            return false;

         iItemParam = (::collection::index)dItem;

         return true;
      }
      else if(m_eview == impact_list)
      {
         if(m_dItemHeight <= 0)
            return false;

         auto rectangleX = this->rectangle();
         if(m_bTopText)
         {
            rectangleX.top() += m_rectangleTopText.height();
         }
         //if(m_bHeaderCtrl)
         //{
         //   rectangleX.top() += m_dItemHeight;
         //}
         ::collection::index iRoundHeight = (::collection::index)((rectangleX.height() / m_dItemHeight) * m_dItemHeight);

         ::collection::index iy = (::collection::index)((point.y() + pointScroll.y()) + (((point.x() + pointScroll.x()) / m_iItemWidth)) * iRoundHeight);

         ::collection::index iItem = -1;

         if(m_dItemHeight != 0)
            iItem = (::collection::index) (iy / m_dItemHeight);

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
         */auto rectangleX = this->rectangle();
         if(m_bTopText)
         {
            rectangleX.top() += m_rectangleTopText.height();
         }
//         index iIconSize = maximum(32,m_columna[0]->m_sizeIcon.cy());
         auto dIconSize = 32.0;
         auto dItemSize = dIconSize * 2;

         auto dx = point.x() + pointScroll.x();
         dx = maximum(pointScroll.x(),dx);
         dx = minimum(rectangleX.right(),dx);
         dx = maximum(rectangleX.left(),dx);
         dx /= dItemSize;

         auto dy = point.y() + pointScroll.y();
         dy = maximum(pointScroll.y(),dy);
         dy = maximum(rectangleX.top(),dy);
         dy /= dItemSize;

         //if(m_flags.has(flag_auto_arrange))
         {
            iItemParam = (::collection::index) ( dy * (maximum(1,rectangleX.width() / dItemSize)) + dx);
         }
         //else
         {
            // iItemParam = iy * (maximum(1,m_piconlayout->m_iWidth)) + ix;
         }


         return true;
      }

      return false;
   }


   void mesh::_001GetGroupRect(::user::draw_mesh_group * pdrawmeshgroup)
   {
      if(pdrawmeshgroup->m_iGroup < 0)
         return_(pdrawmeshgroup->m_bOk,false);
      if(pdrawmeshgroup->m_iGroup >= m_nGroupCount)
         return_(pdrawmeshgroup->m_bOk,false);
      ::collection::index iItemFirst = 0;
      ::collection::index iItemLast = _001GetGroupItemCount(0) - 1;
      pdrawmeshgroup->m_iGroupRectGroup = 0;
      while(pdrawmeshgroup->m_iGroupRectGroup < pdrawmeshgroup->m_iGroup)
      {
         pdrawmeshgroup->m_iGroupRectGroup++;
         iItemFirst = iItemLast + 1;
         iItemLast = iItemFirst + _001GetGroupItemCount(pdrawmeshgroup->m_iGroupRectGroup) - 1;
      }

      auto pitemFirst = get_item(display_to_strict(iItemFirst));
      pitemFirst->m_iDisplayItem      = iItemFirst;
      //itemFirst.m_iGroup            = pdrawitem->m_iGroupRectGroup;

      index_item_rectangle(*pitemFirst);

      //draw_mesh_item itemLast(this);

      auto pitemLast = get_item(display_to_strict(iItemLast));
      pitemLast->m_iDisplayItem = iItemLast;
//      itemLast.m_iItem              = iItemLast;
  //    itemLast.m_iGroup             = pdrawitem->m_iGroupRectGroup;

      index_item_rectangle(*pitemLast);

      pdrawmeshgroup->m_rectangleGroup.unite(pitemFirst->m_pdrawlistitem->m_rectangleItem,pitemLast->m_pdrawlistitem->m_rectangleItem);
      pdrawmeshgroup->m_rectangleGroup.bottom() = maximum(pitemLast->m_pdrawlistitem->m_rectangleItem.bottom(),pitemFirst->m_pdrawlistitem->m_rectangleItem.top() + m_iGroupMinHeight);
      pdrawmeshgroup->m_rectangleGroup.left() = 0;
      pdrawmeshgroup->m_rectangleGroup.right() = m_iLateralGroupWidth;
      pdrawmeshgroup->m_bOk = true;

   }


   void mesh::index_item_rectangle(::user::draw_mesh_item * pdrawitem)
   {

      if(pdrawitem->m_iDisplayItem == (-1 - pdrawitem->m_iRectangleDisplayItem))
      {

         return_(pdrawitem->m_bOk,false);

      }

      if(pdrawitem->m_iRectangleDisplayItem == pdrawitem->m_iDisplayItem)
      {

         return_(pdrawitem->m_bOk,true);

      }

      if(pdrawitem->m_iDisplayItem < 0)
      {

         pdrawitem->m_rectangleItem.set(0);

         pdrawitem->m_iRectangleDisplayItem = (-1 - pdrawitem->m_iDisplayItem);

         return_(pdrawitem->m_bOk,false);

      }

      if(m_eview == impact_icon && pdrawitem->m_iDisplayItem >= m_nDisplayCount)
      {

         pdrawitem->m_rectangleItem.set(0);

         pdrawitem->m_iRectangleDisplayItem = (- 1 - pdrawitem->m_iDisplayItem);

         return_(pdrawitem->m_bOk,false);

      }

      auto pointScroll = get_context_offset();

      if(m_eview == impact_grid)
      {

         if(m_bGroup)
         {

            if(m_bLateralGroup)
            {

               if(pdrawitem->m_iRectangleDisplayItem < 0)
               {

                  pdrawitem->m_rectangleItem.left()    = (int) m_iLateralGroupWidth;
                  pdrawitem->m_rectangleItem.right()   = (int)(pdrawitem->m_rectangleItem.left() + m_iItemWidth);
                  pdrawitem->m_iRectangleDisplayItem = 0;
                  pdrawitem->m_rectangleItem.top()  = 0;
                  //if(m_bHeaderCtrl)
                  //{
                  //   pdrawitem->m_rectangleItem.top() += m_dItemHeight;
                  //}
                  if(m_bTopText)
                  {
                     pdrawitem->m_rectangleItem.top() += m_rectangleTopText.height();
                  }
                  pdrawitem->m_rectangleItem.bottom() = (int)(pdrawitem->m_rectangleItem.top() + m_dItemHeight);
                  pdrawitem->m_rectangleItem.offset(-pointScroll.x(),-pointScroll.y());
               }

               if(pdrawitem->m_iDisplayItem > pdrawitem->m_iRectangleDisplayItem)
               {
                  int iOffset                               = (int)((pdrawitem->m_iRectangleDisplayItem - pdrawitem->m_iGroupTopDisplayIndex) * m_dItemHeight);
                  pdrawitem->m_rectangleItem.top()                -= iOffset;
                  pdrawitem->m_rectangleItem.bottom()              = (int)(pdrawitem->m_rectangleItem.top() + m_dItemHeight);
                  //while(pdrawitem->m_iGroupTopDisplayIndex + pdrawitem->m_iGroupCount < pdrawitem->m_iDisplayItem)
                  //{
                  //   //                     int iHeight                            = _001GetGroupHeight(pdrawitem->m_iGroup);
                  //   pdrawitem->m_rectangleItem.top()             += iOffset;
                  //   pdrawitem->m_rectangleItem.bottom()           = (int)(pdrawitem->m_rectangleItem.top() + m_dItemHeight);
                  //   if((pdrawitem->m_iGroup + 1) >= m_nGroupCount)
                  //   {
                  //      break;
                  //   }
                  //   pdrawitem->m_iGroup++;
                  //   pdrawitem->m_iGroupTopDisplayIndex            += pdrawitem->m_iGroupCount;
                  //   pdrawitem->m_iGroupCount               = _001GetGroupItemCount(pdrawitem->m_iGroup);
                  //   pdrawitem->m_iItemRectItem             = pdrawitem->m_iGroupTopDisplayIndex;
                  //}
               }
               else
               {
                  int iOffset                               = (int)((pdrawitem->m_iRectangleDisplayItem - pdrawitem->m_iGroupTopDisplayIndex) * m_dItemHeight);
                  pdrawitem->m_rectangleItem.top()                -= iOffset;
                  pdrawitem->m_rectangleItem.bottom()              = (int)(pdrawitem->m_rectangleItem.top() + m_dItemHeight);
               //   while(pdrawitem->m_iGroupTopDisplayIndex + pdrawitem->m_iGroupCount > pdrawitem->m_iDisplayItem)
               //   {
               //      if((pdrawitem->m_iGroup - 1) < 0)
               //      {
               //         break;
               //      }
               //      pdrawitem->m_iGroup--;
               //      int iHeight                         = _001GetGroupHeight(pdrawitem->m_iGroup);
               //      pdrawitem->m_rectangleItem.top()          -= iHeight;
               //      pdrawitem->m_rectangleItem.bottom()        = (int)(pdrawitem->m_rectangleItem.top() + m_dItemHeight);
               //      pdrawitem->m_iGroupCount            = _001GetGroupItemCount(pdrawitem->m_iGroup);
               //      pdrawitem->m_iGroupTopDisplayIndex        -= pdrawitem->m_iGroupCount;
               //      pdrawitem->m_iItemRectItem          = pdrawitem->m_iGroupTopDisplayIndex;
               //   }
               }
               //if(pdrawitem->m_iGroup < m_nGroupCount && pdrawitem->m_iGroup >= 0)
               //{
               //   pdrawitem->m_iItemRectItem       = pdrawitem->m_iDisplayItem;
               //   pdrawitem->m_rectangleItem.top()       += (int)((pdrawitem->m_iItemRectItem - pdrawitem->m_iGroupTopDisplayIndex) * m_dItemHeight);
               //   pdrawitem->m_rectangleItem.bottom()     = (int)(pdrawitem->m_rectangleItem.top() + m_dItemHeight);
               //}
            }
            else
            {
               throw ::interface_only();
            }
         }
         else
         {

            pdrawitem->m_rectangleItem.left()    = m_iLeftMargin;

            pdrawitem->m_rectangleItem.right()   = (int)(m_iLeftMargin + m_iItemWidth);

            pdrawitem->m_rectangleItem.top() = 0;
            //if(m_bHeaderCtrl)
            //{
            //   pdrawitem->m_rectangleItem.top() += m_dItemHeight;
            //}
            pdrawitem->m_rectangleItem.top() += (int)(m_dItemHeight * pdrawitem->m_iDisplayItem);
            if(m_bTopText)
            {
               pdrawitem->m_rectangleItem.top() += m_rectangleTopText.height();
            }
            pdrawitem->m_rectangleItem.bottom() = (int)(pdrawitem->m_rectangleItem.top() + m_dItemHeight);
            pdrawitem->m_rectangleItem.offset(0, (int)(m_iTopMargin -pointScroll.y() * m_dItemHeight));
            pdrawitem->m_iRectangleDisplayItem = pdrawitem->m_iDisplayItem;
         }
      }
      else if(m_eview == impact_report)
      {

         if(m_bGroup)
         {

            if(m_bLateralGroup)
            {

               if(pdrawitem->m_iRectangleDisplayItem < 0)
               {

                  pdrawitem->m_rectangleItem.left()    = (int)m_iLateralGroupWidth;
                  pdrawitem->m_rectangleItem.right()   = (int)(pdrawitem->m_rectangleItem.left() + m_iItemWidth);
                  pdrawitem->m_iRectangleDisplayItem = 0;
                  pdrawitem->m_rectangleItem.top()  = 0;
                  //if(m_bHeaderCtrl)
                  //{
                  //   pdrawitem->m_rectangleItem.top() += m_dItemHeight;
                  //}
                  if(m_bTopText)
                  {
                     pdrawitem->m_rectangleItem.top() += m_rectangleTopText.height();
                  }
                  pdrawitem->m_rectangleItem.bottom() = (int)(pdrawitem->m_rectangleItem.top() + m_dItemHeight);
                  pdrawitem->m_rectangleItem.offset(-pointScroll.x(),-pointScroll.y());
               }

               if(pdrawitem->m_iDisplayItem > pdrawitem->m_iRectangleDisplayItem)
               {
                  int iOffset                               = (int)((pdrawitem->m_iRectangleDisplayItem - pdrawitem->m_iGroupTopDisplayIndex) * m_dItemHeight);
                  pdrawitem->m_rectangleItem.top()                -= iOffset;
                  pdrawitem->m_rectangleItem.bottom()              = (int)(pdrawitem->m_rectangleItem.top() + m_dItemHeight);
                  //while(pdrawitem->m_iGroupTopDisplayIndex + pdrawitem->m_iGroupCount < pdrawitem->m_iDisplayItem)
                  //{
                  //   //                     int iHeight                            = _001GetGroupHeight(pdrawitem->m_iGroup);
                  //   pdrawitem->m_rectangleItem.top()             += iOffset;
                  //   pdrawitem->m_rectangleItem.bottom()           = (int)(pdrawitem->m_rectangleItem.top() + m_dItemHeight);
                  //   if((pdrawitem->m_iGroup + 1) >= m_nGroupCount)
                  //   {
                  //      break;
                  //   }
                  //   pdrawitem->m_iGroup++;
                  //   pdrawitem->m_iGroupTopDisplayIndex            += pdrawitem->m_iGroupCount;
                  //   pdrawitem->m_iGroupCount               = _001GetGroupItemCount(pdrawitem->m_iGroup);
                  //   pdrawitem->m_iItemRectItem             = pdrawitem->m_iGroupTopDisplayIndex;
                  //}
               }
               else
               {
                  int iOffset                               = (int)((pdrawitem->m_iRectangleDisplayItem - pdrawitem->m_iGroupTopDisplayIndex) * m_dItemHeight);
                  pdrawitem->m_rectangleItem.top()                -= iOffset;
                  pdrawitem->m_rectangleItem.bottom()              = (int)(pdrawitem->m_rectangleItem.top() + m_dItemHeight);
                  //while(pdrawitem->m_iGroupTopDisplayIndex + pdrawitem->m_iGroupCount > pdrawitem->m_iDisplayItem)
                  //{
                  //   if((pdrawitem->m_iGroup - 1) < 0)
                  //   {
                  //      break;
                  //   }
                  //   pdrawitem->m_iGroup--;
                  //   int iHeight                         = _001GetGroupHeight(pdrawitem->m_iGroup);
                  //   pdrawitem->m_rectangleItem.top()          -= iHeight;
                  //   pdrawitem->m_rectangleItem.bottom()        = (int)(pdrawitem->m_rectangleItem.top() + m_dItemHeight);
                  //   pdrawitem->m_iGroupCount            = _001GetGroupItemCount(pdrawitem->m_iGroup);
                  //   pdrawitem->m_iGroupTopDisplayIndex        -= pdrawitem->m_iGroupCount;
                  //   pdrawitem->m_iItemRectItem          = pdrawitem->m_iGroupTopDisplayIndex;
                  //}
               }
               //if(pdrawitem->m_iGroup < m_nGroupCount && pdrawitem->m_iGroup >= 0)
               //{
               //   pdrawitem->m_iItemRectItem       = pdrawitem->m_iDisplayItem;
               //   pdrawitem->m_rectangleItem.top()       += (int)((pdrawitem->m_iItemRectItem - pdrawitem->m_iGroupTopDisplayIndex) * m_dItemHeight);
               //   pdrawitem->m_rectangleItem.bottom()     = (int)(pdrawitem->m_rectangleItem.top() + m_dItemHeight);
               //}
            }
            else
            {
               throw ::interface_only();
            }
         }
         else
         {
            pdrawitem->m_rectangleItem.left()    = 0;
            pdrawitem->m_rectangleItem.right()   = (int)m_iItemWidth;

            pdrawitem->m_rectangleItem.top() = 0;
            //if(m_bHeaderCtrl)
            //{
            //   pdrawitem->m_rectangleItem.top() += m_dItemHeight;
            //}
            pdrawitem->m_rectangleItem.top() += (int)(m_dItemHeight * pdrawitem->m_iDisplayItem);
            if(m_bTopText)
            {
               pdrawitem->m_rectangleItem.top() += m_rectangleTopText.height();
            }
            pdrawitem->m_rectangleItem.bottom() = (int)(pdrawitem->m_rectangleItem.top() + m_dItemHeight);
            pdrawitem->m_rectangleItem.offset(-pointScroll.x(),-pointScroll.y());
            pdrawitem->m_iRectangleDisplayItem = pdrawitem->m_iDisplayItem;
         }
      }
      else if(m_eview == impact_list)
      {
         auto rectangleX = this->rectangle();
         if(m_bTopText)
         {
            rectangleX.top() += m_rectangleTopText.height();
         }
         //if(m_bHeaderCtrl)
         //{
         //   rectangleX.top() += m_dItemHeight;
         //}
         if (m_dItemHeight <= 0)
         {

            return_(pdrawitem->m_bOk, false);

         }

         double dHeight = rectangleX.height();
         if(dHeight >0.)
         {
            pdrawitem->m_rectangleItem.left() = (int)(pdrawitem->m_iItem * m_dItemHeight * m_iItemWidth / dHeight);
            pdrawitem->m_rectangleItem.top() = (int)(pdrawitem->m_iItem * m_dItemHeight);
         }
         if(m_bTopText)
         {
            pdrawitem->m_rectangleItem.top() += m_rectangleTopText.height();
         }
         //if(m_bHeaderCtrl)
         //{
         //   pdrawitem->m_rectangleItem.top() += m_dItemHeight;
         //}
         pdrawitem->m_rectangleItem.bottom() = (int)(pdrawitem->m_rectangleItem.top() + m_dItemHeight);
         pdrawitem->m_rectangleItem.right() = (int)(pdrawitem->m_rectangleItem.left() + m_iItemWidth);
         pdrawitem->m_rectangleItem.offset(-pointScroll.x(),-pointScroll.y());
      }
      else if(m_eview == impact_icon)
      {
//         if(m_flags.has(flag_auto_arrange) || m_piconlayout->m_iWidth <= 0)
         {
            auto rectangleX = this->rectangle();
            if(m_bTopText)
            {
               rectangleX.top() += m_rectangleTopText.height();
            }
            //index iIconSize = maximum(32,m_columna[0]->m_sizeIcon.cy());
            ::collection::index iIconSize = 32;
            ::collection::index iItemSize = iIconSize * 2;
            pdrawitem->m_rectangleItem.left() = (int)(iItemSize * (pdrawitem->m_iItem % (maximum(1,rectangleX.width() / iItemSize))));
            pdrawitem->m_rectangleItem.top() = (int)(iItemSize * (pdrawitem->m_iItem / (maximum(1,rectangleX.width() / iItemSize))));
            pdrawitem->m_rectangleItem.bottom() = (int)(pdrawitem->m_rectangleItem.top() + iItemSize);
            pdrawitem->m_rectangleItem.right() = (int)(pdrawitem->m_rectangleItem.left() + iItemSize);
         }
         //else
         //{
         //   ::int_rectangle rectangleX;
         //   this->rectangle(&rectangleX);
         //   if(m_bTopText)
         //   {
         //      rectangleX.top() += m_rectangleTopText.height();
         //   }
         //   index iItemSize = get_item_size().cy();
         //   pdrawitem->m_rectangleItem.left() = (int)(iItemSize * (pdrawitem->m_iDisplayItem % m_piconlayout.m_iWidth));
         //   pdrawitem->m_rectangleItem.top() = (int)(rectangleX.top() + iItemSize * (pdrawitem->m_iDisplayItem / m_piconlayout.m_iWidth));
         //   pdrawitem->m_rectangleItem.bottom() = (int)(pdrawitem->m_rectangleItem.top() + iItemSize);
         //   pdrawitem->m_rectangleItem.right() = (int)(pdrawitem->m_rectangleItem.left() + iItemSize);
         //}
         pdrawitem->m_rectangleItem.offset(-pointScroll.x(),-pointScroll.y());
      }

      pdrawitem->m_bOk = true;

   }


   void mesh::_001GetSubItemRect(::user::draw_mesh_subitem * pdrawmeshsubitem)
   {

      if(pdrawmeshsubitem->m_pitem->m_iDisplayItem != pdrawmeshsubitem->m_pitem->m_pdrawmeshitem->m_iRectangleDisplayItem)
      {

         index_item_rectangle(*pdrawmeshsubitem->m_pitem);

         if (!pdrawmeshsubitem->m_bOk)
         {

            return;

         }

      }

      if(pdrawmeshsubitem->m_iRectangleOrder == pdrawmeshsubitem->m_iOrder)
      {

         return_(pdrawmeshsubitem->m_bOk,true);

      }

      if(m_eview == impact_icon)
      {

         pdrawmeshsubitem->m_rectangleSubItem     = pdrawmeshsubitem->m_pitem->m_pdrawlistitem->m_rectangleItem;

         return_(pdrawmeshsubitem->m_bOk,true);

         //return;
         //throw ::exception(::exception("subitem int_rectangle on icon impact? why are you asking for that now?"));
      }

      //pdrawmeshsubitem->m_bOk = false;

      pdrawmeshsubitem->m_rectangleSubItem.top()     = pdrawmeshsubitem->m_pitem->m_pdrawmeshitem->m_rectangleItem.top();
      pdrawmeshsubitem->m_rectangleSubItem.bottom()  = pdrawmeshsubitem->m_pitem->m_pdrawmeshitem->m_rectangleItem.bottom();
      pdrawmeshsubitem->m_rectangleSubItem.left()    = pdrawmeshsubitem->m_pcolumn->m_iPosition;
      pdrawmeshsubitem->m_rectangleSubItem.right()   = pdrawmeshsubitem->m_pcolumn->m_iPosition + pdrawmeshsubitem->m_pcolumn->m_iWidth;

      pdrawmeshsubitem->m_iRectangleOrder = pdrawmeshsubitem->m_iOrder;

      pdrawmeshsubitem->m_bOk = true;

      //index iLastOrder = m_nColumnCount - 1;

      //if (iLastOrder < 0)
      //{

      //   return_(pdrawmeshsubitem->m_bOk, false);

      //}

      //if(pdrawmeshsubitem->m_iRectangleOrder < 0 || pdrawmeshsubitem->m_iOrder == 0 || pdrawmeshsubitem->m_iRectangleOrder > pdrawmeshsubitem->m_iOrder)
      //{

      //   if(m_eview == impact_grid)
      //   {

      //      pdrawmeshsubitem->m_iRectangleOrder = pdrawmeshsubitem->m_iOrder;

      //   }
      //   else
      //   {

      //      pdrawmeshsubitem->m_iRectangleOrder = 0;

      //   }

      //   pdrawmeshsubitem->m_rectangleSubItem.left()          = pdrawmeshsubitem->m_pitem->m_pdrawlistitem->m_rectangleItem.left();
      //   //pdrawmeshsubitem->m_iSubItemRectColumn        = _001MapOrderToColumn(0);
      //   //pdrawitem->m_iColumn                    = pdrawitem->m_iSubItemRectColumn;
      //   //_001GetColumnWidth(pdrawitem);
      //   pdrawmeshsubitem->m_rectangleSubItem.right() = pdrawmeshsubitem->m_pitem->m_pdrawlistitem->m_rectangleItem.left() + pdrawmeshsubitem->m_pcolumn->m_iWidth;
      //   //pdrawmeshsubitem->m_iSubItemRectItem          = pdrawmeshsubitem->m_iItemRectItem;
      //   //pdrawmeshsubitem->m_iSubItemRectSubItem       = pdrawmeshsubitem->m_iSubItem;
      //   if(pdrawmeshsubitem->m_iOrder == 0)
      //   {
      //      pdrawmeshsubitem->m_bOk = true;
      //      return;
      //   }
      //}

      //if(pdrawmeshsubitem->m_iOrder <= iLastOrder)
      //{

      //   while(pdrawitem->m_iSubItemRectOrder < pdrawitem->m_iOrder)
      //   {
      //      pdrawitem->m_iColumn           = _001MapOrderToColumn(pdrawitem->m_iSubItemRectOrder);
      //      _001GetColumnWidth(pdrawitem);
      //      pdrawitem->m_rectangleSubItem.left()       += pdrawitem->m_iColumnWidth;
      //      pdrawitem->m_iSubItemRectOrder++;
      //   }
      //   pdrawitem->m_iColumn = _001MapOrderToColumn(pdrawitem->m_iSubItemRectOrder);
      //   pdrawitem->m_iSubItemRectColumn        = pdrawitem->m_iColumn;
      //   _001GetColumnWidth(pdrawitem);
      //   pdrawitem->m_rectangleSubItem.right()         = pdrawitem->m_rectangleSubItem.left() + pdrawitem->m_iColumnWidth;
      //   pdrawitem->m_iSubItemRectOrder         = pdrawitem->m_iOrder;
      //   pdrawitem->m_iSubItemRectItem          = pdrawitem->m_iItemRectItem;
      //   pdrawitem->m_iSubItemRectSubItem       = pdrawitem->m_iSubItem;
      //   pdrawitem->m_bOk = true;
      //}

   }


   void mesh::index_element_rectangle(::user::draw_mesh_subitem * pdrawmeshsubitem,::user::mesh::enum_element eelement)
   {

      //if(m_bGroup && m_bLateralGroup &&
      //      (eelement == ::user::mesh::element_group_image
      //       || eelement == ::user::mesh::element_group_item_text))
      //{
      //   int x = pdrawitem->m_rectangleGroup.left();
      //   int iImageBottom = pdrawitem->m_rectangleGroup.top();

      //   if(m_pimagelistGroup != nullptr)
      //   {


      //      ::image::image_list::info ii;

      //      _001GetGroupImage(pdrawitem);
      //      if(pdrawitem->m_bOk && pdrawitem->m_iImage >= 0)
      //      {
      //         m_pimagelistGroup->get_image_info((int)pdrawitem->m_iImage,&ii);
      //         if(eelement == ::user::mesh::element_group_image)
      //         {
      //            pdrawitem->m_rectangleImage.left()      = x;
      //            pdrawitem->m_rectangleImage.right()     = x + ii.m_rectangle.width();
      //            pdrawitem->m_rectangleImage.top()       = pdrawitem->m_rectangleGroup.top();
      //            pdrawitem->m_rectangleImage.bottom()    = pdrawitem->m_rectangleImage.top() + ii.m_rectangle.height();
      //            return_(pdrawitem->m_bOk,true);
      //         }
      //         else
      //         {
      //            x += ii.m_rectangle.width();
      //            x += 2;
      //            iImageBottom += ii.m_rectangle.height() + 2;
      //         }
      //      }
      //      else if(eelement == ::user::mesh::element_group_image)
      //      {
      //         return_(pdrawitem->m_bOk,false);
      //      }

      //   }
      //   else if(eelement == ::user::mesh::element_group_image)
      //   {
      //      return_(pdrawitem->m_bOk,false);
      //   }
      //   if(eelement == ::user::mesh::element_group_item_text)
      //   {
      //      pdrawitem->m_rectangleText.top()       = (int)(pdrawitem->m_rectangleGroup.top() + m_dItemHeight * pdrawitem->m_iItem);
      //      if(pdrawitem->m_rectangleText.top() >= iImageBottom)
      //      {
      //         pdrawitem->m_rectangleText.left()      = pdrawitem->m_rectangleGroup.left();
      //      }
      //      else
      //      {
      //         pdrawitem->m_rectangleText.left()      = x;
      //      }
      //      pdrawitem->m_rectangleText.right()     = pdrawitem->m_rectangleGroup.right();
      //      pdrawitem->m_rectangleText.bottom()    = (int)(pdrawitem->m_rectangleText.top() + m_dItemHeight);
      //      return_(pdrawitem->m_bOk,true);
      //   }
      //   pdrawitem->m_bOk = false;
      //}
      //else
      {

         if(pdrawmeshsubitem->m_pitem->m_iDisplayItem != pdrawmeshsubitem->m_pitem->m_pdrawmeshitem->m_iRectangleDisplayItem)
         {
            
            index_item_rectangle(*pdrawmeshsubitem->m_pitem);

            if (!pdrawmeshsubitem->m_pitem->m_bOk)
            {

               return;

            }

         }

         if(eelement == ::user::mesh::e_element_item)
         {

            return_(pdrawmeshsubitem->m_bOk,true);

         }

         if(m_eview == impact_icon)
         {

            if(eelement == ::user::mesh::e_element_image)
            {

               int iIconSize                  = 32;

               pdrawmeshsubitem->m_rectangleImage.left()      = pdrawmeshsubitem->m_pitem->m_pdrawmeshitem->m_rectangleItem.left() + iIconSize / 2;
               pdrawmeshsubitem->m_rectangleImage.top()       = pdrawmeshsubitem->m_pitem->m_pdrawmeshitem->m_rectangleItem.top();
               pdrawmeshsubitem->m_rectangleImage.right()     = pdrawmeshsubitem->m_rectangleImage.left() + iIconSize;
               pdrawmeshsubitem->m_rectangleImage.bottom()    = pdrawmeshsubitem->m_rectangleImage.top() + iIconSize;

               return_(pdrawmeshsubitem->m_bOk,true);

            }
            else if(eelement == ::user::mesh::e_element_text)
            {
               
               int iIconSize               = 32;
               
               pdrawmeshsubitem->m_rectangleText.left()    = pdrawmeshsubitem->m_pitem->m_pdrawmeshitem->m_rectangleItem.left();                
               pdrawmeshsubitem->m_rectangleText.top()     = pdrawmeshsubitem->m_pitem->m_pdrawmeshitem->m_rectangleItem.top() + iIconSize;                
               pdrawmeshsubitem->m_rectangleText.right()   = pdrawmeshsubitem->m_rectangleText.left() + iIconSize * 2;                
               pdrawmeshsubitem->m_rectangleText.bottom()  = pdrawmeshsubitem->m_rectangleText.top() + iIconSize;                
               
               return_(pdrawmeshsubitem->m_bOk,true);

            }
            
            return_(pdrawmeshsubitem->m_bOk,false);

         }

         _001GetSubItemRect(*pdrawmeshsubitem);

         if (!pdrawmeshsubitem->m_bOk)
         {

            return;

         }

         int x = pdrawmeshsubitem->m_rectangleSubItem.left();

         //if(pdrawmeshsubitem->m_iListItem == -1)
         {

            if(eelement == ::user::mesh::e_element_sub_item)
            {

               return_(pdrawmeshsubitem->m_bOk,true);

            }
            //if(pdrawitem->m_pcolumnSubItemRect->m_bIcon)
            //{
            //   _001GetItemImage(pdrawitem);
            //   if(pdrawitem->m_bOk && pdrawitem->m_iImage >= 0)
            //   {
            //      if(eelement == ::user::mesh::element_image)
            //      {
            //         pdrawitem->m_rectangleImage.left()      = x;
            //         pdrawitem->m_rectangleImage.right()     = x + pdrawitem->m_pcolumnSubItemRect.m_sizeIcon.cx();
            //         pdrawitem->m_rectangleImage.bottom()    = pdrawitem->m_rectangleSubItem.bottom();
            //         pdrawitem->m_rectangleImage.top()       = pdrawitem->m_rectangleImage.bottom() - pdrawitem->m_pcolumnSubItemRect.m_sizeIcon.cx();
            //         return_(pdrawitem->m_bOk,true);
            //      }
            //      else
            //      {
            //         x += pdrawitem->m_pcolumnSubItemRect->m_sizeIcon.cx();
            //         x += 2;
            //      }
            //   }
            //   else if(eelement == ::user::mesh::element_image)
            //   {
            //      return_(pdrawitem->m_bOk,false);
            //   }
            //}
            //else if(pdrawitem->m_pcolumnSubItemRect->m_pimagelist != nullptr)
            //{

            //   ::image::image_list::info ii;

            //   _001GetItemImage(pdrawitem);
            //   if(pdrawitem->m_bOk && pdrawitem->m_iImage >= 0)
            //   {
            //      pdrawitem->m_pcolumnSubItemRect->m_pimagelist->get_image_info((int)pdrawitem->m_iImage,&ii);
            //      if(eelement == ::user::mesh::element_image)
            //      {
            //         pdrawitem->m_rectangleImage.left()      = x;
            //         pdrawitem->m_rectangleImage.right()     = x + ii.m_rectangle.width();
            //         pdrawitem->m_rectangleImage.bottom()    = pdrawitem->m_rectangleSubItem.bottom();
            //         pdrawitem->m_rectangleImage.top()       = pdrawitem->m_rectangleImage.bottom() - ii.m_rectangle.height();
            //         return_(pdrawitem->m_bOk,true);
            //      }
            //      else
            //      {
            //         x += ii.m_rectangle.width();
            //         x += 2;
            //      }
            //   }
            //   else if(eelement == ::user::mesh::element_image)
            //   {
            //      return_(pdrawitem->m_bOk,false);
            //   }

            //}
            else if(eelement == ::user::mesh::e_element_image)
            {
               return_(pdrawmeshsubitem->m_bOk,false);
            }
            if(eelement == ::user::mesh::e_element_text)
            {
               pdrawmeshsubitem->m_rectangleText.left()      = x;
               pdrawmeshsubitem->m_rectangleText.right()     = pdrawmeshsubitem->m_rectangleSubItem.right();
               pdrawmeshsubitem->m_rectangleText.top()       = pdrawmeshsubitem->m_rectangleSubItem.top();
               pdrawmeshsubitem->m_rectangleText.bottom()    = pdrawmeshsubitem->m_rectangleSubItem.bottom();
               return_(pdrawmeshsubitem->m_bOk,true);
            }
         }
         pdrawmeshsubitem->m_bOk = false;
      }

   }


   void mesh::_001GetGroupElementRect(::user::draw_mesh_group * pdrawmeshgroup, ::user::mesh::enum_group_element egroupelement)
   {

      if (m_bGroup && m_bLateralGroup &&
         (egroupelement == ::user::mesh::e_group_element_image
            || egroupelement == ::user::mesh::e_group_element_item_text))
      {
         int x = pdrawmeshgroup->m_rectangleGroup.left();
         int iImageBottom = pdrawmeshgroup->m_rectangleGroup.top();

         if (m_pimagelistGroup != nullptr)
         {


            ::image::image_list::info ii;

            _001GetGroupImage(pdrawmeshgroup);
            if (pdrawmeshgroup->m_bOk && pdrawmeshgroup->m_iImage >= 0)
            {
               m_pimagelistGroup->get_image_info((int)pdrawmeshgroup->m_iImage, &ii);
               if (egroupelement == ::user::mesh::e_group_element_image)
               {
                  pdrawmeshgroup->m_rectangleImage.left() = x;
                  pdrawmeshgroup->m_rectangleImage.right() = x + ii.m_rectangle.width();
                  pdrawmeshgroup->m_rectangleImage.top() = pdrawmeshgroup->m_rectangleGroup.top();
                  pdrawmeshgroup->m_rectangleImage.bottom() = pdrawmeshgroup->m_rectangleImage.top() + ii.m_rectangle.height();
                  return_(pdrawmeshgroup->m_bOk, true);
               }
               else
               {
                  x += ii.m_rectangle.width();
                  x += 2;
                  iImageBottom += ii.m_rectangle.height() + 2;
               }

            }
            else if (egroupelement == ::user::mesh::e_group_element_image)
            {
               
               return_(pdrawmeshgroup->m_bOk, false);

            }

         }
         else if (egroupelement == ::user::mesh::e_group_element_image)
         {
            
            return_(pdrawmeshgroup->m_bOk, false);

         }

         if (egroupelement == ::user::mesh::e_group_element_item_text)
         {
            pdrawmeshgroup->m_rectangleText.top() = (int)(pdrawmeshgroup->m_rectangleGroup.top() + m_dItemHeight * pdrawmeshgroup->m_iItem);
            if (pdrawmeshgroup->m_rectangleText.top() >= iImageBottom)
            {
               
               pdrawmeshgroup->m_rectangleText.left() = pdrawmeshgroup->m_rectangleGroup.left();

            }
            else
            {
               
               pdrawmeshgroup->m_rectangleText.left() = x;

            }
            
            pdrawmeshgroup->m_rectangleText.right() = pdrawmeshgroup->m_rectangleGroup.right();
            
            pdrawmeshgroup->m_rectangleText.bottom() = (int)(pdrawmeshgroup->m_rectangleText.top() + m_dItemHeight);
            
            return_(pdrawmeshgroup->m_bOk, true);

         }

         pdrawmeshgroup->m_bOk = false;

      }

   }


   void mesh::on_message_key_down(::message::message * pmessage)
   {

      auto pkey = pmessage->m_union.m_pkey;

      if (pkey->previous()) // give chance to child
      {

         return;

      }

      if(pkey->m_ekey == ::user::e_key_down || pkey->m_ekey == ::user::e_key_up ||
            pkey->m_ekey == ::user::e_key_page_down || pkey->m_ekey == ::user::e_key_page_up)
      {

         if(m_nItemCount > 0)
         {

            range range = m_rangeSelection;

            m_rangeSelection.clear();

            ::collection::index iItem = m_iDisplayItemFocus;

            if(iItem < 0)
            {
               if(pkey->m_ekey == ::user::e_key_down || pkey->m_ekey == ::user::e_key_page_down)
               {
                  iItem = 0;
               }
               else if(pkey->m_ekey == ::user::e_key_up || pkey->m_ekey == ::user::e_key_page_up)
               {
                  iItem = m_nItemCount - 1;
               }
            }
            else
            {
               if(pkey->m_ekey == ::user::e_key_down)
               {
                  iItem++;
               }
               else if(pkey->m_ekey == ::user::e_key_page_up)
               {
                  iItem += m_nDisplayCount;
               }
               else if(pkey->m_ekey == ::user::e_key_up)
               {
                  iItem--;
               }
               else if(pkey->m_ekey == ::user::e_key_page_down)
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

            ensure_item_visible(iItem,range);

            //range.add_item(itemrange);

            set_need_redraw();

            on_selection_change();
         }
      }
      else if(pkey->m_ekey == ::user::e_key_delete)
      {

         ::user::range range;

         get_selection(range);

         _001DeleteRange(range);

         pmessage->m_bRet = true;

      }

      pmessage->m_bRet = false;

   }


   void mesh::on_message_mouse_move(::message::message * pmessage)
   {

      auto pmouse = pmessage->m_union.m_pmouse;

      pmouse->m_lresult = 1;

      ::int_point point = pmouse->m_pointHost;

      host_to_client()(point);

      pmouse->previous(); // give chance to child control

      _synchronous_lock synchronouslock(this->synchronization());

      

      if (m_bDrag)
      {

         if (!m_bLButtonDown)
         {

            m_bDrag = false;

         }
         else if (pmouse->m_ebuttonstate == ::user::e_button_state_none)
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

            bool bShouldStartDrag = f64_distance(point, m_pointLButtonDown1) > m_dItemHeight;

            if (bShouldStartDrag)
            {

               m_bDrag = true;

            }

         }

      }

      track_mouse_leave();

      {

         auto pointCursor = host_mouse_cursor_position();

         auto pmouse = __create_new < ::message::mouse >();

         pmouse->m_pointHost = pointCursor;

         update_hover(pmouse, ::user::e_zorder_any);

         pmessage->m_bRet = true;

         ::collection::index iItemEnter;

         ::collection::index iSubItemEnter;

         if (_001DisplayHitTest(point, iItemEnter, iSubItemEnter))
         {

            if (m_bMeshSelect && m_bHoverSelect2 &&
                  (m_iSubItemEnter != iSubItemEnter ||
                   m_iItemEnter != iItemEnter)
                  && !m_rangeSelection.has_item((::collection::index) iItemEnter))
            {

               m_iMouseFlagEnter = pmouse->m_ebuttonstate;

               m_iItemEnter = iItemEnter;

               m_iSubItemEnter = iSubItemEnter;

               m_iTimerHoverSelect = 0;

            }

         }

      }

   }


   void mesh::on_message_left_button_down(::message::message * pmessage)
   {

      auto pmouse = pmessage->m_union.m_pmouse;

      pmouse->previous(); // give chance to child control and to base views

      m_bLButtonDown = true;

      set_mouse_capture();

      ::collection::index iItem;

      ::int_point point = pmouse->m_pointHost;

      host_to_client()(point);

      if(dynamic_cast < list * >(this) == nullptr)
      {

         auto tickNow = ::time::now();

         if(tickNow - m_timeLButtonDownStart2 < millisecond_time(DBLCLKMS))
         {

            m_timeLButtonDownStart1 = m_timeLButtonDownStart2;

            m_timeLButtonDownStart2 = tickNow;

            m_pointLButtonDown1 = m_pointLButtonDown2;

            m_pointLButtonDown2 = point;

            m_iClick = 2;

         }
         else if(tickNow - m_timeLButtonDownStart1 < millisecond_time(DBLCLKMS))
         {

            m_timeLButtonDownStart2 = tickNow;

            m_pointLButtonDown2 = point;

            m_iClick = 2;

         }
         else
         {

            m_timeLButtonDownStart1 = tickNow;

            m_pointLButtonDown1 = point;

            m_iClick = 1;

         }

      }

      if (!has_keyboard_focus())
      {

         set_keyboard_focus();

      }

      

      set_keyboard_focus();

      user()->set_mouse_focus_LButtonDown(this);

      if (!_001DisplayHitTest(point, m_iDisplayItemLButtonDown1))
      {

         m_iDisplayItemLButtonDown1 = -1;

      }

      auto psession = session();

      if(m_bMeshSelect || does_drag_reorder())
      {

         if(m_bHoverSelect2 && !does_drag_reorder())
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

               // const ::int_point & point = point;

               // on_click(item);

               // set_need_redraw();

               // m_iClick = 0;

            }
            else
            {

               m_rangeSelection.clear();

               on_selection_change();

            }

         }
         else
         {

            if(m_bMultiSelect && psession->is_key_pressed(::user::e_key_shift))
            {

               if(_001DisplayHitTest(point,iItem))
               {

                  item_range itemrange;

                  ::collection::index iLItem = minimum(m_iShiftFirstSelection,iItem);

                  ::collection::index iUItem = maximum(m_iShiftFirstSelection,iItem);

                  itemrange.set(iLItem,iUItem,0,m_nColumnCount - 1,- 1,-1);

                  _001AddSelection(itemrange);

                  m_iShiftFirstSelection = iItem;

                  on_selection_change();

               }

            }
            else if(m_bMultiSelect && psession->is_key_pressed(::user::e_key_control))
            {

               if(_001DisplayHitTest(point,iItem))
               {

                  item_range itemrange;

                  ::collection::index iLItem = minimum(m_iShiftFirstSelection,iItem);

                  ::collection::index iUItem = maximum(m_iShiftFirstSelection,iItem);

                  itemrange.set(iLItem,iUItem,0,m_nColumnCount - 1,- 1,-1);

                  _001AddSelection(itemrange);

                  m_iShiftFirstSelection = iItem;

                  on_selection_change();

               }

            }
            else
            {

               m_rangeSelection.clear();

               ::collection::index iItem;

               if(_001DisplayHitTest(point,iItem))
               {

                  m_iShiftFirstSelection = iItem;

                  m_iDisplayItemFocus = iItem;

                  _001DisplayHitTest(point, m_iDisplayItemLButtonDown1);

                  m_uiLButtonDownFlags = pmouse->m_ebuttonstate;

                  m_pointLButtonDown1 = point;

                  set_timer(e_timer_drag_start, 1.2_s, nullptr);

                  item_range itemrange;

                  itemrange.set(iItem,iItem,0,m_nColumnCount - 1,- 1,-1);

                  _001AddSelection(itemrange);

               }

               on_selection_change();

            }

         }

      }

      set_need_redraw();

      pmessage->m_bRet = true;

      pmouse->m_lresult = 1;

   }


   void mesh::on_message_left_button_up(::message::message * pmessage)
   {

      auto pmouse = pmessage->m_union.m_pmouse;

      ::int_point point = pmouse->m_pointHost;

      host_to_client()(point);

      defer_release_mouse_capture();

      if (m_bDrag)
      {

         m_bDrag = false;

         if (m_eview != impact_icon)
         {

            ::collection::index iDisplayItemDrop;

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

            ::collection::index iDisplayItemLButtonUp = -1;

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

                     on_click(__allocate ::item(::e_element_item, iDisplayItemLButtonUp), pmouse);

                  }
                  else
                  {

                      auto pmessage = __create_new < ::message::mouse >();

                      pmessage->m_oswindow = oswindow();

                      pmessage->m_pwindow = window();

                      pmessage->m_emessage = e_message_left_button_double_click;

                      pmessage->m_ebuttonstate = pmouse->m_ebuttonstate;

                      pmessage->m_pointHost = pmouse->m_pointHost;

                      post_message(pmessage);

                  }

               }

            }

         }

      }

      pmessage->m_bRet = true;

      pmouse->m_lresult = 1;

      m_bLButtonDown = false;

   }


   void mesh::on_message_right_button_down(::message::message * pmessage)
   {

      auto pmouse = pmessage->m_union.m_pmouse;

      pmouse->previous();

      ::int_point point = pmouse->m_pointHost;

      host_to_client()(point);

      if(!has_keyboard_focus())
      {

         set_keyboard_focus();

      }

      auto psession = session();

      if(psession->is_key_pressed(::user::e_key_shift))
      {

      }
      else if(psession->is_key_pressed(::user::e_key_control))
      {

      }
      else
      {

         ::collection::index iItem;
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


   void mesh::on_message_right_button_up(::message::message * pmessage)
   {

      auto pmouse = pmessage->m_union.m_pmouse;

      pmouse->previous();

      ::int_point point = pmouse->m_pointHost;

      host_to_client()(point);

      if (!has_keyboard_focus())
      {

         set_keyboard_focus();

      }

      _001OnRightClick(pmouse->m_ebuttonstate, point);

      pmessage->m_bRet = true;

   }


   bool mesh::on_click(::item * pitem, ::user::mouse * pmouse)
   {

      auto ptopic = create_topic(::id_list_clicked);

      ptopic->m_actioncontext.m_pmessage = pmouse;

      ptopic->m_puserelement = this;

      route(ptopic);

      /*if(m_pformcallback != nullptr)
      {

         m_p->route(&topic);

      }
      else if(get_form() != nullptr)
      {

         get_form()->send_message(e_message_event,0,(LPARAM)&ev);

      }
      else
      {

         get_parent()->send_message(e_message_event,0,(LPARAM)&ev);

      }*/
      return true;
   }


   bool mesh::_001OnRightClick(uptr nFlag,const ::int_point & point)
   {

      __UNREFERENCED_PARAMETER(nFlag);
      __UNREFERENCED_PARAMETER(point);
      return false;

   }



   void mesh::get_selection(range &range)
   {
      range = m_rangeSelection;
   }


   void mesh::get_data_selection(const ::scoped_string & scopedstrDataKey, ::string_array & straSelection)
   {

      if (!has_data_key(scopedstrDataKey))
      {

         return;

      }

      ::collection::index iFilterSubItem = data_key_to_column_key(scopedstrDataKey);

      range & range = m_rangeSelection;

      for(::collection::index i = 0; i < range.get_item_count(); i++)
      {
         
         auto & itemrange = range.ItemAt(i);

         if(itemrange.has_sub_item(iFilterSubItem))
         {
           
            for(::collection::index iLine = itemrange.get_lower_bound(); iLine <= itemrange.get_upper_bound(); iLine++)
            {

               straSelection.add_item(scopedstrDataKey + "/" + ::as_string(iLine));

            }

         }

      }

   }


   /*index range::get_item(::collection::index iItemIndex)
   {
   ::collection::index iFirst = 0;
   ::collection::index i = 0;
   ::collection::index iItem;

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

   /*index item_range::get_item(::collection::index iItemIndex)
   {
   return m_iItemStart + iItemIndex;
   }*/


   ::collection::count mesh::_001GetSelectedItemCount()
   {
      return m_rangeSelection.get_item_count();
   }


   string mesh::_001GetColumnText(::collection::index iColumn)
   {

      __UNREFERENCED_PARAMETER(iColumn);
      
      return "";

   }


   void mesh::on_message_left_button_double_click(::message::message * pmessage)
   {

      auto pmouse = pmessage->m_union.m_pmouse;

      m_iClick = 2;

      auto item = hit_test(pmouse, ::user::e_zorder_any);

      on_click(item, pmouse);

      //   on_click(item);
      set_need_redraw();

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


   void mesh::_001ShowSubItem(::collection::index iSubItem, bool bShow)
   {

   }


   void mesh::DISaveOrder()
   {

   }


   void mesh::DILoadOrder()
   {

   }


   void mesh::on_highlight_change()
   {


   }


   void mesh::PreSubClassWindow()
   {

      if(is_window_visible())
      {

         //RedrawWindow(nullptr,nullptr,RDW_INVALIDATE);
         RedrawWindow({},nullptr,0);

      }

   }


   void mesh::on_message_create(::message::message * pmessage)
   {


      __øconstruct(m_ppenFocused);
      __øconstruct(m_ppenHighlight);

      ::pointer<::message::create>pcreate(pmessage);

      pmessage->previous();

      on_enable_hover_select();


      __defer_construct_new(m_pgraphicsextension);

      //m_pgraphicsextension->initialize(this);

      //on_create_draw_item();


      //if (m_eview == ::user::mesh::impact_icon)
      //{

      //   m_pdrawmeshitem->m_ealign = e_align_top_center;

      //   m_pdrawmeshitem->m_edrawtext = { e_draw_text_end_ellipsis, e_draw_text_word_break };
      //}
      //else
      //{

      //   m_pdrawmeshitem->m_ealign = e_align_left_center;

      //   m_pdrawmeshitem->m_edrawtext = { e_draw_text_end_ellipsis, e_draw_text_single_line };

      //}


      //m_pfont->operator=(*pdraw2d->fonts().GetMeshCtrlFont());

      //m_pfontHover->operator=(*pdraw2d->fonts().GetMeshCtrlFont());

      //m_pfontHover->set_underline();
      ////m_pfontHover->set_bold();

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

      ::int_rectangle rectangle;

      //rectangle.null();

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

   //   if(pcolumn->m_uiSmallBitmap == (unsigned int)-1)
   //   {
   //      return;
   //   }
   //   if(pcolumn->m_pimagelist == nullptr)
   //   {
   //      pcolumn->m_pimagelist = ___new ::image::image_list (this);
   //   }
   //   //      ::image::image_list_pointer pil = pcolumn->m_pimagelist;
   //   //   if(pil != nullptr)
   //   //      pil->DeleteImageMesh();
   //   throw ::interface_only();
   //   /*if(!pil->create(
   //   MAKEINTRESOURCE(pcolumn->m_uiSmallBitmap),
   //   pcolumn->m_iSmallImageWidth,
   //   0,
   //   pcolumn->m_colorSmallMask))
   //   {
   //   }*/
   //}


   void mesh::on_hover_select_timer()
   {

      ::collection::index iItemSel;

      ::collection::index iSubItemSel;

      auto pointCursor = host_mouse_cursor_position();

      host_to_client()(pointCursor);

      try
      {

         if (_001DisplayHitTest(pointCursor, iItemSel, iSubItemSel))
         {

            if (m_iSubItemEnter == iSubItemSel && m_iItemEnter == iItemSel)
            {

               m_iSubItemEnter = -1;

               m_iItemEnter = -1;

               auto psession = session();

               bool bLShiftKeyDown = psession->is_key_pressed(::user::e_key_left_shift);
               bool bRShiftKeyDown = psession->is_key_pressed(::user::e_key_right_shift);
               bool bLControlKeyDown = psession->is_key_pressed(::user::e_key_left_control);
               bool bRControlKeyDown = psession->is_key_pressed(::user::e_key_right_control);
               bool bShiftKeyDown = bLShiftKeyDown || bRShiftKeyDown;
               bool bControlKeyDown = bLControlKeyDown || bRControlKeyDown;

               if (m_bMultiSelect && bShiftKeyDown)
               {

                  if (bControlKeyDown)
                  {

                     item_range itemrange;

                     itemrange.set(
                        minimum(iItemSel, m_iItemSel),
                        maximum(iItemSel, m_iItemSel),
                        minimum(iSubItemSel, m_iSubItemSel),
                        maximum(iSubItemSel, m_iSubItemSel),
                        -1,
                        -1);

                     _001AddSelection(itemrange);

                  }
                  else
                  {

                     item_range itemrange;

                     itemrange.set(
                        minimum(iItemSel, m_iItemSel),
                        maximum(iItemSel, m_iItemSel),
                        minimum(iSubItemSel, m_iSubItemSel),
                        maximum(iSubItemSel, m_iSubItemSel),
                        -1,
                        -1);

                     ::user::range range;

                     range.add_item(itemrange);

                     set_selection(range);

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
                     display_to_strict(m_iItemSel),
                     display_to_strict(m_iItemSel),
                     m_iSubItemSel,
                     m_iSubItemSel,
                     -1,
                     -1);

                  ::user::range range;

                  range.add_item(itemrange);

                  set_selection(range);

               }

            }

            if (get_keyboard_focus() != this)
            {

               set_keyboard_focus();

            }

         }

      }
      catch (...)
      {

      }

      m_iSubItemEnter = -1;

      m_iItemEnter = -1;

   }


   void mesh::on_timer(::timer * ptimer)
   {

      ::user::interaction::on_timer(ptimer);

      if (ptimer->m_uTimer == e_timer_hover_select)
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
      else if(ptimer->m_uTimer == 12345679) // left click
      {

         kill_timer(12345679);

         if(m_bMeshSelect)
         {

            if(m_bHoverSelect2)
            {

            }

         }

      }
      else if(ptimer->m_uTimer == 8477) // right click
      {

         kill_timer(8477);

         //if(!_001IsEditing())
         {
            uptr nFlags = m_uiRButtonUpFlags;
            auto & point = m_pointRButtonUp;
            _001OnRightClick(nFlags,point);
            set_need_redraw();


            /* trans
            window_id wndidNotify = puserinteraction->get_owner()->GetSafeoswindow_();
            if(wndidNotify == nullptr)
            wndidNotify = puserinteraction->get_parent()->GetSafeoswindow_(); */

            //            LRESULT lresult = 0;

            /* trans            if(wndidNotify)
            {
            NMLISTVIEW nm;
            nm.hdr.idFrom = puserinteraction->GetDlgCtrlId();
            nm.hdr.code =   NM_CLICK;
            nm.hdr.oswindowFrom = puserinteraction->GetSafeoswindow_();
            lresult = ::SendMessage(
            wndidNotify,
            WM_NOTIFY,
            nm.hdr.idFrom,
            (LPARAM) &nm);
            }*/
         }
      }
      else if(ptimer->m_uTimer == 0xfffffffe)
      {

         if(!Filter1Step())
         {

            kill_timer(ptimer->m_uTimer);

         }

      }
      else if (ptimer->m_uTimer == 224455)
      {

         kill_timer(ptimer->m_uTimer);

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
      else if(ptimer->m_uTimer == e_timer_drag_start) // 12345678
      {

         kill_timer(ptimer->m_uTimer);

         if(!m_bHoverSelect2)
         {

         }
         else
         {

            m_bDrag = true;

         }

      }
      //else if(ptimer->m_uTimer == 12321)
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

         if (!m_ptaskHoverSelect)
         {

            m_ptaskHoverSelect = fork([this]()
               {

                  try
                  {

                     _task_hover_select();

                  }
                  catch (...)
                  {


                  }

                  m_ptaskHoverSelect.release();

               });

         }

         m_timeLastHoverSelect.Now();

         m_bPendingHoverSelect = true;

      }
      else
      {

         //kill_timer(e_timer_hover_select);

         m_bPendingHoverSelect = false;

      }

   }


   void mesh::_task_hover_select()
   {

      auto ptask = ::get_task();

      while (ptask->task_get_run())
      {

         ptask->task_sleep(100_ms);

         if (m_bPendingHoverSelect)
         {

            if (m_timeLastHoverSelect.elapsed() > 800_ms)
            {

               m_bPendingHoverSelect = false;

               on_hover_select_timer();

            }

         }
         else
         {

            if (m_timeLastHoverSelect.elapsed() > 30_s)
            {

               break;

            }

         }


      }


   }



   bool mesh::_001IsItemVisible(::collection::index iItem)
   {
      
      draw_mesh_item item;

      item.m_iItem         = iItem;

      item.m_iDisplayItem  = iItem;

      index_item_rectangle(&item);

      if(!item.m_bOk)
      {
      
         return false;

      }

      auto rectangleX = this->rectangle();

      return rectangleX.intersect(rectangleX,item.m_rectangleItem) != 0;

   }


   void mesh::clear_selection()
   {

      m_rangeSelection.clear();

      on_selection_change();

   }

   
   void mesh::set_selection(const range &range)
   {
   
      m_rangeSelection = range;
      
      on_select();

      on_selection_change();

   }


   void mesh::_001AddSelection(const item_range & itemrange)
   {
      m_rangeSelection.add_item(itemrange);
      on_select();
      on_selection_change();
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


   void mesh::_001SetTopText(const ::wide_character * pcwsz)
   {

      m_strTopText = pcwsz;

      auto psystem = system();

      auto pdraw2d = psystem->draw2d();

      auto pgraphics = pdraw2d->create_memory_graphics(this);

      _001LayoutTopText(pgraphics);

   }


   void mesh::_001LayoutTopText(::draw2d::graphics_pointer& pgraphics)
   {

      pgraphics->set_font(this, ::e_element_none);

      ::double_size_array sizea;

      m_pgraphicsextension->get_text_extent(pgraphics,m_strTopText,sizea);

      auto rectangleX = this->rectangle();

      ::collection::index x = 0;
      ::collection::index right = rectangleX.right();
      ::collection::index y = 0;
      for(::collection::index i = 0; i < sizea.get_size(); i++)
      {
         if((sizea[i].cx() - x > right)
               || i == sizea.get_upper_bound())
         {
            if(i == 0)
            {
               x = (::collection::index) (sizea[0].cx());
               y += (::collection::index) (sizea[0].cy());
            }
            else
            {
               x = (::collection::index) (sizea[i - 1].cx());
               y += (::collection::index) (sizea[i - 1].cy());
            }
         }
      }

      m_rectangleTopText.left() = 0;
      m_rectangleTopText.top() = 0;
      m_rectangleTopText.right() = rectangleX.right();
      m_rectangleTopText.bottom() = (int)y;


   }

   void mesh::_001ShowTopText(bool bShow)
   {
      m_bTopText = bShow;
   }


   void mesh::set_cache_interface(mesh_cache_interface * pinterface)
   {
      
      m_pmeshcache = pinterface;

   }


   void mesh::cache_hint()
   {

      if(m_pmeshcache != nullptr)
      {

         ::collection::index iItemCount = m_nDisplayCount;

         ::collection::index iItemFirst = m_iTopDisplayIndex;

         m_pmeshcache->_001CacheHint(this, iItemFirst, iItemCount);

      }

   }


   void mesh::set_data_interface(::user::mesh_data *pinterface)
   {

      m_pmeshdata = pinterface;

      m_psimplemeshdata = m_pmeshdata;

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
   //   //pcolumn->m_colorSmallMask = argb(255,255,0,255);


   //   //_001InsertColumn(column);

   //   set_need_layout();



   //}


   //int mesh::_001CalcItemWidth(::draw2d::graphics_pointer& pgraphics, ::collection::index iItem, ::collection::index iSubItem)
   //{

   //   pgraphics->set_font(this, ::e_element_none);

   //   index cx = _001CalcItemWidth(pgraphics,iItem,iSubItem);

   //   return (int)cx;

   //}


   //int mesh::_001CalcItemWidth(::draw2d::graphics_pointer & pgraphics,::write_text::font * pfont, ::collection::index iItem, ::collection::index iSubItem)
   //{
   //   pgraphics->set(pfont);
   //   return _001CalcItemWidth(pgraphics,iItem,iSubItem);
   //}


   void mesh::_001CalculateItemHeight(::draw2d::graphics_pointer & pgraphics)
   {

      auto dFontHeight = _001GetDefaultFontHeight(pgraphics);

      auto pstyle = get_style(pgraphics);

      double dItemHeight = maximum(m_sizeMaximumImage.cy(), dFontHeight);

      m_dItemHeight = dItemHeight * get_double(pstyle, ::user::e_double_list_item_height_rate, ::user::e_state_none, 1.0);

      for (auto & pitem : m_mapItem.payloads())
      {

         if (pitem)
         {

            if (pitem->m_pdrawmeshitem)
            {

               pitem->m_pdrawmeshitem->m_iRectangleDisplayItem = -1;

            }

         }

      }

   }


   int mesh::_001CalcSubItemWidth(::draw2d::graphics_pointer & pgraphics, ::collection::index iItem, ::collection::index iSubItem)
   {

      pgraphics->set_font(this, ::e_element_none);

      //::image::image_list::info ii;
      //::int_rectangle rectangle;
      //::int_size size;
      int cx = 0;
      //mesh_column * pcolumn = m_columna._001GetByKey(iSubItem);
      auto psubitem = get_subitem(iItem, iSubItem);
      //item.m_iItem = iItem;
      //item.m_iSubItem = iSubItem;
      //item.m_iListItem = -1;
      //if(pcolumn->m_pimagelist != nullptr)
      //{
      //   _001GetItemImage(&item);
      //   if(item.m_bOk && item.m_iImage >= 0)
      //   {
      //      pcolumn->m_pimagelist->get_image_info((int)item.m_iImage,&ii);
      //      rectangle = ii.m_rectangle;
      //      cx += rectangle.width();
      //      cx += 2;
      //   }
      //}

      _001GetSubItemText(psubitem);

      if(psubitem->m_bOk)
      {

         ::double_size size{};
         
         m_pgraphicsextension->get_text_extent(pgraphics, psubitem->m_strText, size);

         cx += (int) (size.cx());

      }

      return (int)cx;

   }


   bool mesh::has_data_key(const ::scoped_string & scopedstrDataKey)
   {

      return data_key_to_column_key(scopedstrDataKey) >= 0;

   }


   ::collection::index mesh::data_key_to_sub_item(const ::scoped_string & scopedstrDataKey)
   {
      //mesh_column * column = m_columna._001GetByConfigId(key);
      //if(column == nullptr)
      //   return -1;
      //return column->m_iSubItem;
      return -1;
   }


   ::collection::index mesh::data_key_to_column_key(const ::scoped_string & scopedstrDataKey)
   {
      //mesh_column * column = m_columna._001GetByConfigId(key);
      //if(column == nullptr)
      //   return -1;
      //return column->m_iKey;
      return -1;
   }

   //mesh_column * mesh_column_array::_001GetByConfigId(const ::scoped_string & strDataKey)
   //{
   //   //index iKey = MapConfigIdToKey(key);
   //   //if(iKey >= 0)
   //   //   return element_at(iKey);
   //   //else
   //   //   return nullptr;



   //}

   //index mesh_column_array::MapConfigIdToKey(const ::scoped_string & strDataKey)
   //{
   //   for(::collection::index iKey = 0; iKey < this->get_size(); iKey++)
   //   {
   //      if(this->element_at(iKey)->m_strDataKey == key)
   //         return iKey;
   //   }
   //   return -1;
   //}


   void mesh::ensure_item_visible(::collection::index iItem,bool bRedraw)
   {

      auto pointScroll = get_context_offset();

      if(iItem < pointScroll.y() || (m_dItemHeight > 0 && iItem >= pointScroll.y() / m_dItemHeight + m_nDisplayCount))
      {

         auto dy = iItem * m_dItemHeight;

         //queue_graphics_call([this, iy](::draw2d::graphics_pointer & pgraphics)
           // {

               //set_context_offset_y(pgraphics, iy);
         set_context_offset_y(dy);

            //});

         if(bRedraw)
         {

            set_need_redraw();

         }

      }

   }


   void mesh::scroll_to_item(::collection::index iItem,bool bRedraw)
   {

      //auto pointScroll = get_context_offset();

      if(iItem < m_nItemCount)
      {

         auto dy = iItem * m_dItemHeight;

         //queue_graphics_call([this, iy](::draw2d::graphics_pointer & pgraphics)
           // {

              // set_context_offset_y(pgraphics, iy);
         set_context_offset_y(dy);

            //});

         if(bRedraw)
         {

            set_need_redraw();

         }

      }

   }


   void mesh::ensure_item_visible(::collection::index iItem,range & range)
   {

      auto pointScroll = get_context_offset();

      auto iyScroll = pointScroll.y() / maximum(1,m_dItemHeight);
      if(iItem < iyScroll)
      {
         iyScroll = iItem - (double) m_nDisplayCount + 1;
      }
      else if(iItem >= iyScroll + m_nDisplayCount)
      {
         iyScroll = (double) iItem;
      }
      if(pointScroll.y() / maximum(1,m_dItemHeight) != iyScroll)
      {
         item_range item;

         auto dy = iyScroll * m_dItemHeight;

         //queue_graphics_call([this, iy](::draw2d::graphics_pointer & pgraphics)
           // {

         set_context_offset_y(dy);
              // set_context_offset_y(pgraphics, iy);

             //  on_change_context_offset(pgraphics);

            //});

         item.set_lower_bound((::collection::index)iyScroll);
         item.set_upper_bound(minimum((::collection::index)(iyScroll + m_nDisplayCount - 1), (::collection::index)(m_nItemCount - 1)));
         range.add_item(item);
      }
   }


   void mesh::highlight_item(::collection::index iItem,bool bRedraw)
   {

      m_rangeHighlight.clear();
      
      item_range itemrange;
      
      itemrange.set(iItem,iItem,0,m_nColumnCount - 1,- 1,-1);
      
      m_rangeHighlight.add_item(itemrange);

      if(bRedraw)
      {
         
         set_need_redraw();

      }

      on_highlight_change();

   }


   bool mesh::on_erase_item(::collection::index iItem)
   {

      __UNREFERENCED_PARAMETER(iItem);

      return false;

   }


   bool mesh::erase_item(::collection::index iItem,bool bRedraw)
   {

      if (!on_erase_item(iItem))
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


   void mesh::erase_selection()
   {

      ::user::range range;

      get_selection(range);

      while(range.get_item_count() > 0)
      {
         ::collection::index iItem = range.ItemAt(0).get_lower_bound();
         if(!erase_item(iItem,false))
            break;
         get_selection(range);
      }

      set_need_redraw();
   }


   void mesh::select_item(::collection::index iItem, ::collection::index iSubItem)
   {

      m_rangeSelection.clear();

      item_range itemrange;

      itemrange.set(iItem,iItem,iSubItem,iSubItem,- 1,-1);

      _001AddSelection(itemrange);

   }


   ::collection::index mesh::strict_to_display(::collection::index iStrict)
   {

      __UNREFERENCED_PARAMETER(iStrict);

      return -1;

   }


   ::collection::index mesh::display_to_strict(::collection::index iDisplay)
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

      ::collection::index iItemCount = m_nItemCount;

      if(m_eview == impact_icon)
      {

         m_piaFilterIcon->erase_all();

         for(::collection::index i = 0; i < iItemCount; i++)
         {

            m_piaFilterIcon->add(i);

         }

      }
      else
      {

         m_piaFilterMesh->erase_all();

         for(::collection::index i = 0; i < iItemCount; i++)
         {

            m_piaFilterMesh->add(i);

         }

      }

   }


   void mesh::FilterApply()
   {

      m_iFilter1Step = 0;

      set_timer(0xfffffffe,50_ms,nullptr);

      //queue_graphics_call([this](::draw2d::graphics_pointer & pgraphics)
      //   {

      //      set_context_offset(pgraphics, 0, 0);

      //   });

      m_efilterstate = FilterStateFilter;

      auto psystem = system();

      auto pdraw2d = psystem->draw2d();

      auto pgraphics = pdraw2d->create_memory_graphics(this);

      //on_change_sketch_scroll_state();

      set_context_offset({ 0, 0 });

      set_need_layout();

      set_need_redraw();

   }


   void mesh::FilterClose()
   {

      m_bFilter1 = false;

      kill_timer(0xfffffffe);

      ASSERT(m_efilterstate == FilterStateSetup || m_efilterstate == FilterStateFilter);

      ::collection::index iItemCount = m_nItemCount;

      if(m_eview == impact_icon)
      {

         m_piconlayout->m_iaDisplayToStrict.erase_all();

         for(::collection::index i = 0; i < iItemCount; i++)
         {

            m_piconlayout->m_iaDisplayToStrict.add(i);

         }

      }
      else
      {

         m_pmeshlayout->m_iaDisplayToStrict.erase_all();

         for(::collection::index i = 0; i < iItemCount; i++)
         {

            m_pmeshlayout->m_iaDisplayToStrict.add(i);

         }

      }

      auto psystem = system();

      auto pdraw2d = psystem->draw2d();

      auto pgraphics = pdraw2d->create_memory_graphics(this);

      //on_change_scroll_state();

      on_would_change_total_size();

      set_need_layout();

      set_need_redraw();

   }


   void mesh::FilterExcludeAll()
   {

      if(m_eview == impact_icon)
      {

         m_piaFilterIcon->erase_all();

      }
      else
      {

         m_piaFilterMesh->erase_all();

      }

   }


   void mesh::FilterInclude(::collection::index iItem)
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


   void mesh::FilterInclude(::int_array & array)
   {

      ASSERT(m_efilterstate == FilterStateSetup);

      for(::collection::index i = 0; i < array.get_size() ; i++)
      {

         FilterInclude(array[i]);

      }

   }


   bool mesh::Filter1Step()
   {

      auto tickIn = ::time::now();

      informationf("mesh::Filter1Step");

      information() << "tickIn = " << tickIn.integral_millisecond();

      if(!m_bFilter1)
      {

         return false;

      }

      string wstrItem;

      ::collection::index iItemCount = minimum(m_nItemCount,m_iFilter1Step + 1000);

      ::collection::index iFilter1Step;

      draw_mesh_item item;

      for(iFilter1Step =  m_iFilter1Step; iFilter1Step < iItemCount; iFilter1Step++)
      {
         //for(::collection::index j = 0; j < m_nColumnCount; j++)
         /*{
            mesh_column * pcolumn = m_columna._001GetByKey(j);
            item.m_strText.empty();
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

      m_iFilter1Step = (int)iFilter1Step;

      if(m_eview == impact_icon)
      {

         m_piconlayout->m_iaDisplayToStrict = (*m_piaFilterIcon);

      }
      else
      {

         m_pmeshlayout->m_iaDisplayToStrict = (*m_piaFilterMesh);

      }

      //queue_graphics_call([this](::draw2d::graphics_pointer & pgraphics)
        // {

            //set_context_offset(pgraphics, 0, 0);

      set_context_offset({});

         //});

      m_efilterstate = FilterStateFilter;

      auto psystem = system();

      auto pdraw2d = psystem->draw2d();

      auto pgraphics = pdraw2d->create_memory_graphics(this);

      //
      // 
      // on_change_sketch_scroll_state();

      on_would_change_total_size();

      set_need_layout();

      set_need_redraw();

      auto tickOut = ::time::now();

      information() << "tickOut = " << tickOut.integral_millisecond();
      information() << "(delta) = " << (tickOut - tickIn).integral_millisecond();

      return m_nItemCount != iItemCount;
   }


   void mesh::Filter1(const ::scoped_string & scopedstrFilter)
   {

      if(m_eview == impact_icon)
      {

         m_piaFilterIcon->erase_all();

      }
      else
      {

         m_piaFilterMesh->erase_all();

      }

      string_array stra;

      stra.add_tokens(scopedstrFilter," ",false);

      //m_pregexFilter1->setPositionMoves(1);

      auto psystem = system();

      m_pregexFilter1 = psystem->compile_pcre("/.*" + stra.implode(".*") + ".*/i");

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

   void mesh::_001OnMeshHeaderItemClick(::collection::index iHeaderItem)
   {
      if(!m_bSortEnable)
         return;
      _001OnSort(_001MapColumnToSubItem(iHeaderItem));
   }


   void mesh::_001OnMeshHeaderItemDblClk(::collection::index iHeaderItem)
   {
      
      auto psystem = system();

      auto pdraw2d = psystem->draw2d();

      auto pgraphics = pdraw2d->create_memory_graphics(this);

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

         ::generic::range::quick_sort(m_pmeshlayout->m_iaDisplayToStrict,this,&::user::mesh::_001Compare);

      }
      else
      {

      }

   }


   void mesh::_001OnSort(::collection::index iSubItem)
   {

      ::collection::index iFound = -1;
      for(::collection::index i = 0; i < m_sortinfo.m_itema.get_size(); i++)
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
         m_sortinfo.m_itema.erase_at(iFound);
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


   ::std::strong_ordering mesh::_002Compare(::collection::index iItem1, ::collection::index iItem2, ::collection::index iSubItem)
   {

      //draw_mesh_item item1;

      //draw_mesh_item item2;

      //item1.m_iItem     = iItem1;
      //item2.m_iItem     = iItem2;
      //item1.m_iSubItem  = iSubItem;
      //item2.m_iSubItem  = iSubItem;

      //_001GetItemText(&item1);
      //_001GetItemText(&item2);

      //if(item1.m_bOk && item2.m_bOk)
      //{
      //   return item1.m_strText.case_insensitive_order(item2.m_strText);
      //}
      //else
      //{
      //   if(item1.m_bOk)
      //      return 1;
      //   else if(item2.m_bOk)
      //      return -1;
      //   else
      //      return 0;
      //}

      return ::std::strong_ordering::equal;

   }


   ::std::strong_ordering mesh::_001Compare(::collection::index iItem1, ::collection::index iItem2)
   {
      //CSortInfoItem * pitem = nullptr;
      //index iCompare = 0;
      //for(::collection::index i = 0; i < m_sortinfo.m_itema.get_size(); i++)
      //{
      //   pitem = &m_sortinfo.m_itema[i];
      //   iCompare = _002Compare(iItem1,iItem2,pitem->m_item.m_iSubItem);
      //   if(iCompare != 0)
      //      break;
      //}
      //if(pitem == nullptr)
      //   return 0;
      //else
      //{
      //   if(pitem->m_bAscendent)
      //      return iCompare;
      //   else
      //      return -iCompare;
      //}
      
      return ::std::strong_ordering::equal;

   }


   ::std::strong_ordering mesh::_001DisplayCompare(::collection::index iDisplayItem1, ::collection::index iDisplayItem2)
   {

      return _001Compare(display_to_strict(iDisplayItem1),display_to_strict(iDisplayItem2));

   }


   int mesh::_001CalcMeshWidth(::draw2d::graphics_pointer& pgraphics)
   {

      ASSERT(false);

      return -1;

   }


   int mesh::_001CalcColumnWidth(::draw2d::graphics_pointer& pgraphics, ::collection::index iColumn)
   {

      __UNREFERENCED_PARAMETER(iColumn);

      pgraphics->set_font(this, ::e_element_none);

      int iMaxWidth = 0;

      ::collection::count iCount = m_nItemCount;

      int iWidth;

      for(::collection::index i = 0; i < iCount; i++)
      {

         iWidth = _001CalcSubItemWidth(pgraphics,i,0);

         if(iWidth > iMaxWidth)
         {

            iMaxWidth = iWidth;

         }

      }

      return iMaxWidth;

   }


   bool mesh::_001SetColumnWidth(::collection::index iColumn,int iWidth)
   {

      m_mapColumnWidth[iColumn] = iWidth;

      return true;

   }



   void mesh::_001MaximizeColumnWidth(::draw2d::graphics_pointer& pgraphics, ::collection::index iColumn)
   {
      
      _001SetColumnWidth(iColumn,_001CalcColumnWidth(pgraphics, iColumn));

   }


   void mesh::_OnDraw(::draw2d::graphics_pointer & pgraphics)
   {

      __UNREFERENCED_PARAMETER(pgraphics);

   }


   int mesh::get_wheel_scroll_delta()
   {

      if(m_eview == impact_grid)
      {

         return 1;

      }
      else
      {

         return (int) m_dItemHeight;

      }

   }


   //int_rectangle mesh::get_scroll_margin()
   //{

   //   if(m_eview == impact_grid && m_dItemHeight > 0)
   //   {

   //      return int_rectangle(m_scrollstate.m_rectangleMargin.left(),m_scrollstate.m_rectangleMargin.top()/m_dItemHeight, m_scrollstate.m_rectangleMargin.right(),m_scrollstate.m_rectangleMargin.bottom() / m_dItemHeight);

   //   }
   //   else
   //   {

   //      return scroll_control::get_scroll_margin();

   //   }

   //}


   void mesh::on_change_context_offset(::user::enum_layout elayout)
   {

//      ::user::interaction::on_change_context_offset();

      m_iTopDisplayIndex = _001CalcDisplayTopIndex();
      ::collection::index iLow = 0;
      for(m_iTopGroup = 0; m_iTopGroup < m_nGroupCount; m_iTopGroup++)
      {
         if(m_iTopDisplayIndex >= iLow && m_iTopDisplayIndex < (iLow + _001GetGroupItemCount(m_iTopGroup)))
            break;
      }

      m_nDisplayCount = _001CalcDisplayItemCount();

      cache_hint();

      auto pointCursor = host_mouse_cursor_position();

      auto pmouse = __create_new < ::message::mouse >();

      pmouse->m_pointHost = pointCursor;

      update_hover(pmouse, ::user::e_zorder_any);

   }


   ::draw2d::pen * mesh::_001GetPenHighlight()
   {

      return m_ppenHighlight;

   }


   ::draw2d::pen * mesh::_001GetPenFocused()
   {

      return m_ppenFocused;

   }


   //::write_text::font * mesh::_001GetFont()
   //{
   //   return m_pfont;
   //}

   //::write_text::font * mesh::_001GetFontHover()
   //{
   //   return m_pfontHover;
   //}


   void mesh::on_message_mouse_leave(::message::message * pmessage)
   {
      
      //m_iDisplayItemHover = -1;
      
      //m_iSubItemHover = -1;
      
      //set_need_redraw();
      
      //pmessage->m_bRet = true;

   }


   //::item_pointer mesh::update_hover(::user::mouse * pmouse, ::user::e_zorder ezorder)
   //{

   //   ::item_pointer pitemHitTest = __allocate ::item();
   //   
   //   auto pointClient = screen_to_client().get(pmouse->m_point);

   //   bool & bAnyHoverChange = pitemHitTest->m_bAnyHoverChange;

   //   if(_001DisplayHitTest(pointClient, pitemHitTest->m_item.m_iItem, pitemHitTest->m_item.m_iSubItem))
   //   {

   //      if(m_iSubItemHover != pitemHitTest->m_item.m_iSubItem || m_iDisplayItemHover != pitemHitTest->m_item.m_iItem)
   //      {

   //         m_iDisplayItemHover = pitemHitTest->m_item.m_iItem;

   //         m_iSubItemHover = pitemHitTest->m_item.m_iSubItem;

   //         bAnyHoverChange = true;

   //      }

   //   }

   //   if (!bAvoidRedraw)
   //   {

   //      if (bAnyHoverChange)
   //      {

   //         set_need_redraw();

   //         post_redraw();

   //      }

   //   }

   //   return pitemHitTest;

   //}


   ::item_pointer mesh::on_hit_test(const ::int_point& point, e_zorder ezorder)
   {

      ::item_pointer pitemHitTest = __allocate ::item();

      //auto pointClient = screen_to_client().get(pmouse->m_point);

      //bool& bAnyHoverChange = pitemHitTest->m_bAnyHoverChange;

      if (!_001DisplayHitTest(point, pitemHitTest->m_item.m_iItem, pitemHitTest->m_item.m_iSubItem))
      {

         pitemHitTest->m_item.m_eelement = e_element_none;

         pitemHitTest->m_item.m_iItem = -1;

         pitemHitTest->m_item.m_iSubItem = -1;

         //if (m_iSubItemHover != pitemHitTest->m_item.m_iSubItem || m_iDisplayItemHover != pitemHitTest->m_item.m_iItem)
         //{

         //   m_iDisplayItemHover = pitemHitTest->m_item.m_iItem;

         //   m_iSubItemHover = pitemHitTest->m_item.m_iSubItem;

         //   //bAnyHoverChange = true;

         //}

      }

      //if (!bAvoidRedraw)
      //{

      //   if (bAnyHoverChange)
      //   {

      //      set_need_redraw();

      //      post_redraw();

      //   }

      //}

      return pitemHitTest;


   }


   ::user::mesh_data * mesh::GetDataInterface()
   {

      return m_pmeshdata;

   }


   void mesh::_001SetImpact(EImpact eview, bool bLayout)
   {

      m_eview = eview;

      //if (m_eview == ::user::mesh::impact_icon)
      //{

      //   m_pdrawmeshitem->m_ealign = e_align_top_center;

      //   m_pdrawmeshitem->m_edrawtext = { e_draw_text_end_ellipsis, e_draw_text_word_break };
      //}
      //else
      //{

      //   m_pdrawmeshitem->m_ealign = e_align_left_center;

      //   m_pdrawmeshitem->m_edrawtext = { e_draw_text_end_ellipsis, e_draw_text_single_line };

      //}


      //on_ui_event(event_change_impact_style, object_list, this);

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

         //datastream()->get(data_get_current_sort_id() + "." + data_get_current_mesh_layout_id(),m_piconlayout);

      }
      else
      {

         //datastream()->get(data_get_current_sort_id() + "." + data_get_current_mesh_layout_id(),m_pmeshlayout);

      }

   }


   void mesh::data_set_DisplayToStrict()
   {
      if(m_eview == impact_icon)
      {
         //datastream()->set(data_get_current_sort_id() + "." + data_get_current_mesh_layout_id(),m_piconlayout);
      }
      else
      {
         //datastream()->set(data_get_current_sort_id() + "." + data_get_current_mesh_layout_id(),m_pmeshlayout);
      }
   }

   atom mesh::data_get_current_sort_id()
   {
      return data_get_sort_id(m_eview);
   }

   atom mesh::data_get_sort_id(EImpact eview)
   {
      __UNREFERENCED_PARAMETER(eview);
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
         ASSERT(false);
         return "sort";
      }
   }

   mesh::EImpact mesh::_001GetImpact()
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


   void mesh::_001GetSubItemColor(::user::mesh_subitem * psubitem)
   {

      if (m_pmeshdata != nullptr)
      {

         m_pmeshdata->_001GetSubItemColor(psubitem);

         if (psubitem->m_bOk)
         {

            return;

         }

      }

      psubitem->m_bOk = false;

   }


   void mesh::on_message_scroll_y(::message::message * pmessage)
   {

      ::pointer<::message::scroll>pscroll(pmessage);

      pmessage->previous();

      _synchronous_lock synchronouslock(this->synchronization());

      if(m_eview == impact_grid)
      {

         if(pscroll->m_ecommand != e_scroll_command_thumb_track)
         {

            auto pointScroll = get_context_offset();

            auto sizePage = get_page_size();

            auto sizeTotal = get_total_size();

            if((sizeTotal.cy() - pointScroll.y() - sizePage.cy()) <= 1)
            {

               m_nItemCount = minimum(m_nGridItemCount,m_nItemCount + (::collection::count)(sizePage.cy() / m_dItemHeight));

               //auto psystem = system();

               //auto pdraw2d = psystem->draw2d();

               //auto pgraphics = pdraw2d->create_memory_graphics(this);

               //on_change_sketch_scroll_state();

            }

         }

      }

   }

   void mesh::on_message_scroll_x(::message::message * pmessage)
   {

      ::pointer<::message::scroll>pscroll(pmessage);

      pmessage->previous();

      if(m_eview == impact_grid)
      {

         if(pscroll->m_ecommand != e_scroll_command_thumb_track)
         {

            auto pointScroll = get_context_offset();

            auto sizePage = get_page_size();

            auto sizeTotal = get_total_size();

            if((sizeTotal.cx() - pointScroll.x() - sizePage.cx()) <= 1)
            {

///               m_nColumnCount = minimum(m_nGridColumnCount,m_nColumnCount + sizePage.cx());
/// 
               m_nColumnCount = m_nGridColumnCount;

               //auto psystem = system();

               //auto pdraw2d = psystem->draw2d();

               //auto pgraphics = pdraw2d->create_memory_graphics(this);

               //on_change_impact_size(pgraphics);

            }

         }

      }

      m_iTopDisplayIndex = _001CalcDisplayTopIndex();
      
      ::collection::index iLow = 0;

      for(m_iTopGroup = 0; m_iTopGroup < m_nGroupCount; m_iTopGroup++)
      {

         if (m_iTopDisplayIndex >= iLow && m_iTopDisplayIndex < (iLow + _001GetGroupItemCount(m_iTopGroup)))
         {

            break;

         }

      }

      m_nDisplayCount = _001CalcDisplayItemCount();

      cache_hint();

   }


   atom mesh::data_get_current_mesh_layout_id()
   {

      return "mesh";

   }


   bool mesh::query_drop(::collection::index iDisplayDrop, ::collection::index iDisplayDrag)
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

      if(display_to_strict(iDisplayDrop) != -1 && display_to_strict(iDisplayDrop) < m_nItemCount)
      {

         return false;

      }

      return true;

   }


   bool mesh::do_drop(::collection::index iDisplayDrop, ::collection::index iDisplayDrag)
   {

      __UNREFERENCED_PARAMETER(iDisplayDrop);

      __UNREFERENCED_PARAMETER(iDisplayDrag);

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


   bool mesh::defer_drop(::collection::index iDisplayDrop, ::collection::index iDisplayDrag)
   {
      if(query_drop(iDisplayDrop,iDisplayDrag))
      {
         if(m_eview == impact_icon)
         {
//            if(m_piconlayout->m_iWidth <= 0)
//            {
//               ::int_rectangle rectangleX;
//               this->rectangle(rectangleX);
//               index iIconSize;
//               if(m_nColumnCount > 0)
////                  iIconSize = maximum(32,m_columna[0]->m_sizeIcon.cy());
//                     iIconSize = 32;
//               else
//                  iIconSize = 32;
//               index iItemSize = iIconSize * 2;
//               m_piconlayout->m_iWidth = (int)(maximum(1,rectangleX.width() / iItemSize));
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



   ::int_size mesh::get_item_size()
   {

      if(m_eview == impact_icon)
      {

         if(m_nColumnCount == 0)
         {

            return ::int_size(32,32);

         }

//         index iIconSize = maximum(32,m_columna[0]->m_sizeIcon.cy());

         ::collection::index iIconSize = 32;

         ::collection::index iItemSize = iIconSize * 2;

         return ::int_size((int) iItemSize, (int) iItemSize);

      }
      else
      {

         // not implemented

         ASSERT(false);

         return {};

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
         m_flags.erase(flag_auto_arrange);
      }
      if(bAutoArrange)
      {
         ::collection::index iMaxStrict = m_piconlayout->m_iaDisplayToStrict.get_max_b();
         for(::collection::index iStrict = 0; iStrict <= iMaxStrict; iStrict++)
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

   void mesh::_001OnMeshImpactAutoArrange(::message::message * pmessage)
   {
      __UNREFERENCED_PARAMETER(pmessage);
      auto_arrange(!get_auto_arrange());
   }

   void mesh::_001OnUpdateMeshImpactAutoArrange(::message::message * pmessage)
   {
      ::pointer<::message::command>pcommand(pmessage);
      pcommand->set_check(get_auto_arrange(), e_source_sync);
      pcommand->enable();
   }

   bool mesh::is_valid_display_item(::collection::index iDisplayItem)
   {
      if(iDisplayItem < 0)
         return false;
      if(iDisplayItem >= m_nItemCount)
         return false;
      return true;
   }

   bool mesh::is_valid_strict_item(::collection::index iStrictItem)
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


   void mesh::on_selection_change()
   {

      auto ptopic = create_topic(::id_after_change_cur_sel);

      ptopic->m_actioncontext = e_source_user;

      ptopic->m_puserelement = this;

      route(ptopic);

      set_need_redraw();

      post_redraw();

   }


   void mesh::set_current_item(::item * pitem, const ::action_context & context)
   {

      m_rangeSelection.clear();

      if (::is_set(pitem))
      {

         item_range itemrange;

         itemrange.set_lower_bound(pitem->m_item.m_iItem);

         itemrange.set_upper_bound(pitem->m_item.m_iItem);

         _001AddSelection(itemrange);

      }

      //return ::success;

   }


   void mesh::set_current_item(const index_array & iaSel, const ::action_context & context)
   {
      m_rangeSelection.clear();
      for(::collection::index i = 0; i < iaSel.get_count(); i++)
      {
         item_range itemrange;
         itemrange.set_lower_bound(iaSel[i]);
         itemrange.set_upper_bound(iaSel[i]);
         m_rangeSelection.add_item(itemrange);
      }

   }


   ::item_pointer mesh::current_item()
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


   void mesh::get_cur_sel(index_array & iaSel)
   {

      for(::collection::index i = 0; i < m_rangeSelection.get_item_count(); i++)
      {

         for(::collection::index iItem = m_rangeSelection.ItemAt(i).get_lower_bound(); iItem <= m_rangeSelection.ItemAt(i).get_upper_bound(); iItem++)
         {

            iaSel.add_unique(iItem);

         }

      }

   }


   ::collection::count mesh::_001GetGroupItemCount(::collection::index iGroup)
   {

      __UNREFERENCED_PARAMETER(iGroup);

      return -1;

   }


   int mesh::_001GetGroupHeight(::collection::index iGroup)
   {

      int iMeshHeight = (int)(_001GetGroupItemCount(iGroup) * m_dItemHeight);

      return maximum(m_iGroupMinHeight,iMeshHeight);

   }

   
   bool mesh::_001OnHeaderCtrlEndTrack(wparam, lparam)
   {

      return true;

   }


   bool mesh::_001OnHeaderCtrlTrack(wparam, lparam)
   {

      return true;

   }


   //bool draw_mesh_subitem::draw_image()
   //{

   //   //if(m_pcolumn->m_bIcon)
   //   //{
   //   //   ::image::icon * picon;
   //   //   if(m_pcolumn->m_mapIcon.lookup((int)m_iImage,picon))
   //   //   {
   //   //      m_pgraphics->set_alpha_mode(::draw2d::e_alpha_mode_blend);
   //   //      return m_pgraphics->DrawIcon(m_rectangleImage.top_left(),picon) != false;
   //   //   }
   //   //}
   //   //else
   //   //{
   //   //   m_pgraphics->set_alpha_mode(::draw2d::e_alpha_mode_blend);
   //   //   return get_image_list()->draw(m_pgraphics,(int)m_iImage,m_rectangleImage.top_left(),m_rectangleImage.size(),int_point(0,0),0);
   //   //}
   //   
   //   return false;

   //}


   bool draw_mesh_subitem::draw_image()
   {
     
      m_pitem->m_pmesh->m_pimagelistGroup->draw(m_pitem->m_pdrawlistitem->m_pgraphics,(int)m_iImage,m_rectangleImage.top_left(),m_rectangleImage.size(),int_point(0,0),0);

      return true;

   }


   void draw_mesh_subitem::update_color()
   {

      m_pitem->m_pmesh->_001GetSubItemColor(this);

      if(!m_bOk)
      {

         auto pstyle = m_pitem->m_pmesh->get_style(m_pitem->m_pdrawlistitem->m_pgraphics);

         auto estate = m_pitem->m_pdrawlistitem->get_user_state();

         m_colorText = m_pitem->m_pmesh->get_color(pstyle, ::e_element_text, estate);

      }

   }


   void draw_mesh_subitem::set_text_color()
   {
      
      //auto pbrushText = m_pmesh->__øcreate < ::draw2d::brush > ();

      //pbrushText->create_solid(m_colorText);

      //m_pgraphics->set(pbrushText);

   }



   void draw_mesh_subitem::draw_text()
   {

      if(m_bOk)
      {

         if(m_pitem->m_pmesh->m_eview == mesh::impact_icon && m_pitem->m_pmesh->m_bEmboss)
         {

            auto size = m_rectangleText.size();
            size.cx() += 4;
            size.cy() += 4;

            ::image::image_pointer pimage1;
            pimage1 = m_pitem->m_pmesh->image()->create_image(size);
            pimage1->clear(::color::transparent);
            auto pbrushText = m_pitem->m_pmesh->__øcreate < ::draw2d::brush > ();
            pbrushText->create_solid(argb(255,255,255,255));
            pimage1->get_graphics()->set(pbrushText);
            ::image::image_pointer pimage2;
            pimage2 = m_pitem->m_pmesh->image()->create_image(size);
            pimage2->clear(::color::transparent);

            ::int_rectangle rectangleCache;
            rectangleCache.left() = 2;
            rectangleCache.top() = 2;
            rectangleCache.right() = rectangleCache.left() + (int)m_rectangleText.width();
            rectangleCache.bottom() = rectangleCache.top() + (int)m_rectangleText.height();
            pimage1->get_graphics()->set(m_pcolumn->m_pdrawlistcolumn->m_pfont);
            pimage1->get_graphics()->_DrawText(m_strText,rectangleCache, m_pcolumn->m_pdrawlistcolumn->m_ealign, m_pcolumn->m_pdrawlistcolumn->m_edrawtext);

            //::aura::application * get_app() = m_pmesh->get_app();

            auto psystem = m_pitem->m_pmesh->system();

            psystem->imaging()->channel_spread_set_color(pimage2->get_graphics(),{}, size, pimage1->get_graphics(),{},0,2,argb(192,192,192,192));
            pimage1->clear(::color::transparent);
            psystem->imaging()->channel_alpha_gray_blur(pimage1->get_graphics(),{}, size, pimage2->get_graphics(),{},0,1);
            pimage2->clear(::color::transparent);
            psystem->imaging()->channel_alpha_gray_blur(pimage2->get_graphics(),{}, size, pimage1->get_graphics(),{},0,1);
            pimage2->clear(::color::transparent);

            ::image::image_source imagesource(pimage2, int_rectangle(1,1, m_rectangleText.width(), m_rectangleText.height()));

            ::image::image_drawing_options imagedrawingoptions(m_rectangleText);

            imagedrawingoptions.opacity(0.5);

            ::image::image_drawing imagedrawing(imagedrawingoptions, imagesource);

            m_pitem->m_pdrawlistitem->m_pgraphics->draw(imagedrawing);

            pbrushText->create_solid(argb(255,255,255,255));

            m_pitem->m_pdrawlistitem->m_pgraphics->set(pbrushText);

            m_pitem->m_pdrawlistitem->m_pgraphics->set(m_pcolumn->m_pdrawlistcolumn->m_pfont);

            m_pitem->m_pdrawlistitem->m_pgraphics->_DrawText(m_strText,m_rectangleText, m_pcolumn->m_pdrawlistcolumn->m_ealign, m_pcolumn->m_pdrawlistcolumn->m_edrawtext);

         }
         else
         {

            auto pbrushText = m_pitem->m_pmesh->__øcreate < ::draw2d::brush > ();

            pbrushText->create_solid(m_colorText);

            m_pitem->m_pdrawlistitem->m_pgraphics->set(pbrushText);

            m_pitem->m_pdrawlistitem->m_pgraphics->_DrawText(m_strText,m_rectangleText, m_pitem->m_pdrawmeshitem->m_ealign, m_pitem->m_pdrawmeshitem->m_edrawtext);

         }

      }

   }


   ::user::enum_state draw_mesh_item::get_user_state() const
   {

      ::user::e_state estate = e_state_none;

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


   ::collection::count mesh::_001GetGroupMetaItemCount(::collection::index iGroup)
   {
      if(m_pmeshdata != nullptr)
      {
         return m_pmeshdata->_001GetGroupMetaItemCount(iGroup);
      }
      
      return 0;

   }


   void mesh::_001GetGroupItemText(mesh_group * pgroup)
   {
      
      pgroup->m_bOk = false;

      if(::is_set(m_pmeshcache))
      {

         m_pmeshcache->_001GetGroupItemText(pgroup);

         if (pgroup->m_bOk)
         {

            return;

         }

      }

      if(::is_set(m_pmeshdata))
      {

         m_pmeshdata->_001GetGroupItemText(pgroup);

      }

   }


   void mesh::_001GetGroupImage(mesh_group * pgroup)
   {

      pgroup->m_bOk = false;

      pgroup->m_iImage = -1;

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


   //::pointer<::user::mesh_data>list::create_mesh_data()
   //{

   //   return __allocate mesh_data();

   //}



   void mesh::defer_create_mesh_data()
   {

      ::pointer<::user::list_data>pmeshdata = create_mesh_data();

      if(pmeshdata.is_null())
         return;

      set_data_interface(pmeshdata);

   }


   ::collection::count mesh::_001GetColumnCount()
   {

      if(m_pmeshdata.is_null())
         return -1;

      return m_pmeshdata->_001GetColumnCount(this);

   }


   ::double_point mesh::get_context_offset(::user::enum_layout elayout)
   {

      return ::user::scroll_base::get_context_offset(elayout);

   }


   //void mesh::on_change_impact_size()
   //{

   //   if(m_eview == impact_grid && m_dItemHeight > 0)
   //   {

   //      ::int_rectangle rectangleTotal;

   //      _001GetImpactRect(&rectangleTotal);

   //      int_size sizeTotal = rectangleTotal.size();

   //      m_sizeTotal.cx() = sizeTotal.cx();

   //      m_sizeTotal.cy() = sizeTotal.cy() / m_dItemHeight;

   //      ::int_rectangle rectangleImpactClient;

   //      this->rectangle(&rectangleImpactClient);

   //      m_scrollstate.m_sizePage.cx() = rectangleImpactClient.size().cx();

   //      m_scrollstate.m_sizePage.cy() = rectangleImpactClient.size().cy() / m_dItemHeight;

   //      if(m_scrollstate.m_pointScroll.y() > (m_sizeTotal.cy() - m_scrollstate.m_sizePage.cy()))
   //      {

   //         m_scrollstate.m_pointScroll.y() = (m_sizeTotal.cy() - m_scrollstate.m_sizePage.cy());

   //      }

   //   }
   //   else
   //   {
   //
   //      ::user::box::on_change_impact_size();

   //   }


   //}


   //double_size mesh::get_total_size()
   //{

   //   return m_sizeTotal;

   //}


   double_size mesh::get_page_size(::user::enum_layout elayout)
   {

      if(m_eview == impact_grid && m_dItemHeight > 0)
      {

         auto rectangleX = this->rectangle();

         //auto pointScroll = get_context_offset();

         ::int_size sizePage;

         sizePage.cx() = rectangleX.width() / m_iDefaultColumnWidth;

         sizePage.cy() = (int)(rectangleX.width() / m_dItemHeight);

         return sizePage;

      }
      else
      {

         return ::user::interaction::get_page_size();

      }

   }


   //bool mesh::this->rectangle(::int_rectangle * prectangle)
   //{

   //   if(m_eview == impact_grid && m_dItemHeight > 0)
   //   {

   //      ::user::interaction::this->rectangle(prectangle);

   //   }
   //   else
   //   {

   //      ::user::interaction::this->rectangle(prectangle);

   //   }

   //   return true;

   //}


   //void mesh::on_create_draw_item()
   //{

   //   //m_pdrawmeshitem            = ___new draw_mesh_item(this);


   //}


   string mesh::_001GetItemId(::collection::index iStrictItem)
   {

      return ::as_string(iStrictItem);

   }

   ::collection::index mesh::_001GetItemById(const ::scoped_string & scopedstrChar)
   {

      ::collection::count c = _001GetItemCount();

      string strId(scopedstrChar);

      for (::collection::index iItem = 0; iItem < c; iItem++)
      {

         if (strId == _001GetItemId(iItem))
         {

            return iItem;

         }

      }

      return -1;

   }



} // namespace user


