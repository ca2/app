#include "framework.h"
#include "core/user/user/_user.h"
#include "_data.h"
#include "_tree.h"
#include "acme/constant/timer.h"
#include "aura/message.h"
#include "aura/graphics/draw2d/_draw2d.h"
#include "aura/graphics/image/list.h"


namespace user
{


   tree::tree()
   {

      user_tree_common_construct();

   }


   tree::~tree()
   {

   }


   void tree::user_tree_common_construct()
   {

      __compose_new(m_pitemptraSelected);

      m_bHoverStart = false;

      m_flagNonClient += ::user::interaction::non_client_hover_rect;

      m_econtroltype = ::user::e_control_type_tree;

      m_pitemFirstVisible        = nullptr;
      m_pitemHover                = nullptr;
      m_iItemCount               = 0;
      m_dItemHeight              = 0.;
      m_iImageExpand             = -1;
      m_iImageCollapse           = -1;
      m_uchHoverAlphaInit        = 0;
      m_ealignText = e_align_left_center;
      m_edrawtext = e_draw_text_none;
      m_evOpen.m_eobject += e_object_alertable_wait;
      m_evExpand.m_eobject += e_object_alertable_wait;

      m_sizeItemMaximum.cx = 16;
      m_sizeItemMaximum.cy = 16;

   }


   void tree::on_message_create(::message::message * pmessage)
   {

      __pointer(::message::create) pcreate(pmessage);

      if (pmessage->previous())
      {

         return;

      }


      //auto estatus =
      
      __compose_new(m_ptree);

      //if (!estatus)
      //{

      //   _ERROR(pcreate, "Error creating tree data at ::user::tree::on_message_create");

      //   return;

      //}

      //estatus = 
      
      __construct_new(m_pimagelist);

      //if (!estatus)
      //{

      //   _ERROR(pcreate, "Error creating image list at ::user::tree::on_message_create");

      //   return;

      //}

      //estatus = 
      
      m_pimagelist->create(16, 16, 0, 10, 10);

      //if (!estatus)
      //{

      //   _ERROR(pcreate, "Error creating image list (2) at ::user::tree::on_message_create");

      //   return;

      //}

      fork([this]()
         {

            _001SetExpandImage("matter://list/expand.png");

            task_set_name(__type_name(this) + "::Expand");

            auto pthread = ::get_task();

            while (pthread->task_get_run())
            {

               m_evExpand.wait(500_ms);

               if (m_treeitemaExpand.has_element())
               {

                  auto pitem = m_treeitemaExpand.pop();

                  _001ExpandItem(pitem, ::e_source_user, !(pitem->m_dwState & ::data::tree_item_state_expanded));

                  m_treeitemaExpand.erase_all();

               }

               m_evExpand.ResetEvent();

            }

         });


      fork([this]()
         {

            _001SetCollapseImage("matter://list/collapse.png");

            task_set_name(__type_name(this) + "::Open");

            auto pthread = ::get_task();

            while (pthread->task_get_run())
            {

               m_evOpen.wait(500_ms);

               if (m_treeitemaOpen.has_element())
               {

                  auto pitem = m_treeitemaOpen.pop();

                  _001OnOpenItem(pitem, ::e_source_user);

               }
               else
               {

                  m_evOpen.ResetEvent();

               }

            }

         });



   }


   void tree::_001OnDraw(::draw2d::graphics_pointer & pgraphics)
   {

      pgraphics->set_text_rendering_hint(::write_text::e_rendering_anti_alias);

      pgraphics->set_alpha_mode(::draw2d::e_alpha_mode_blend);

      {

         ::duration tickStart;

         tickStart.Now();

         ::user::interaction::_001OnDraw(pgraphics);

         auto tickElapsed = tickStart.elapsed();

         if (tickElapsed > 50_ms)
         {

            //WARNING("tree drawing took more than 50ms");

         }

      }

      {

         ::duration tickStart;

         tickStart.Now();

         ::rectangle_i32 rectangleClient;

         get_client_rect(rectangleClient);

         //pgraphics->set_alpha_mode(::draw2d::e_alpha_mode_blend);

         //pgraphics->fill_rectangle(rectangleClient, m_colorTreeBackground);


         auto psession = get_session();

         auto puser = psession->user();

         auto pwindowing = puser->windowing();

         auto pointCursor = _001ScreenToClient(pwindowing->get_cursor_position());

         auto dwHoverIn = 300_ms;

         auto dwHoverOut = 1200_ms;

         bool bTreeHover = rectangleClient.contains(pointCursor);

         if(bTreeHover)
         {
            if(!m_bHoverStart)
            {
               m_bHoverStart = true;
               m_uchHoverAlphaInit = m_uchHoverAlpha;

               m_durationHoverStart.Now();

            }
            if(m_durationHoverStart.elapsed() > dwHoverIn)
            {
               m_uchHoverAlpha = 255;
            }
            else
            {
               auto 😁 = MATH_PI;
               auto f = 1.0 / duration(dwHoverIn).floating_second().m_d;
               auto 😃 = -😁 * f; // omega pi
               auto t = m_durationHoverStart.elapsed().floating_second().m_d;
               ::u32 dwCurve =  (::u32) (255.0 * (1.0 - exp(😃 * t)));
               if(m_uchHoverAlphaInit + dwCurve > 255)
                  m_uchHoverAlpha = 255;
               else
                  m_uchHoverAlpha =  (byte) (m_uchHoverAlphaInit + dwCurve);
            }
         }
         else
         {
            if(m_bHoverStart)
            {
               m_bHoverStart = false;
               m_uchHoverAlphaInit = m_uchHoverAlpha;

               m_durationHoverEnd.Now();

            }

            if(m_durationHoverEnd.elapsed()  > dwHoverOut)
            {
               m_uchHoverAlpha = 0;
            }
            else
            {
               auto 😁 = MATH_PI;
               auto f = 1.0 / ::duration(dwHoverOut).floating_second().m_d;
               auto 😃 = -😁 * f; // omega pi
               auto t = m_durationHoverStart.elapsed().floating_second().m_d;
               ::u32 dwCurve = (::u32)(255.0 * (1.0 - exp(😃 * t)));
               if(m_uchHoverAlphaInit < dwCurve)
                  m_uchHoverAlpha = 0;
               else
                  m_uchHoverAlpha = (byte) (m_uchHoverAlphaInit - dwCurve);
            }
         }

         ::user::tree_draw_item drawitemdata;

         drawitemdata.m_pdc = pgraphics;

         drawitemdata.m_iIndentation = _001GetIndentation();

         drawitemdata.m_dItemHeight = _001GetItemHeight();

         drawitemdata.m_rectangleClient = get_client_rect();

         auto pitem = m_pitemFirstVisible;

         synchronous_lock synchronouslock(!pitem ? nullptr : pitem->m_ptree->mutex());

         index iItem = m_iFirstVisibleItemProperIndex;

         auto iVisibleCount = _001GetVisibleItemCount();

         index iIndex = 0;

         for(; pitem != nullptr; pitem = pitem->get_item(::data::TreeNavigationProperForward))
         {

            drawitemdata.m_pitem = pitem;

            drawitemdata.m_iItem = iItem;

            drawitemdata.m_rectangle = drawitemdata.m_rectangleClient;

            drawitemdata.m_rectangle.left = (::i32) (drawitemdata.m_iIndentation * pitem->m_iLevel);

            drawitemdata.m_rectangle.top = (::i32) (iItem * drawitemdata.m_dItemHeight);

            drawitemdata.m_rectangle.bottom = (::i32) (drawitemdata.m_rectangle.top + drawitemdata.m_dItemHeight);

            drawitemdata.m_rectangle.right = m_iCurrentImpactWidth;

            {
               ::duration tickItem;
               tickItem.Now();
               _001DrawItem(drawitemdata);
               auto tickElapsed = tickStart.elapsed();

               if (tickElapsed > 20_ms)
               {

                  //WARNING("tree item drawing took more than 20ms");

               }

            }


            iItem++;

            iIndex++;

            if (iIndex > iVisibleCount)
            {

               break;

            }

         }


         auto tickElapsed = tickStart.elapsed();

         if (tickElapsed > 50_ms)
         {

            //WARNING("tree drawing took more than 50ms");

         }

      }

   }


   void tree::_001DrawItem(tree_draw_item & data)
   {

      auto start = duration(e_now);

      ::rectangle_i32 rectangle;

      __pointer(tree) ptree = this;

      __pointer(::data::tree_item) pitem = data.m_pitem;

      __pointer(::image_list) pimagelistItem = pitem->get_image_list();

      if (pimagelistItem->m_size > m_sizeItemMaximum)
      {

         m_sizeItemMaximum = pimagelistItem->m_size;

         set_need_layout();

      }

      __pointer(::image_list) pimagelistTree = get_image_list();

      bool bSelected    = ptree->is_selected(pitem.m_p);

      bool bHover       = ptree->is_hover(pitem);

      data.m_pdc->set_alpha_mode(::draw2d::e_alpha_mode_blend);

      if(m_uchHoverAlpha > 0)
      {

         if(ptree != nullptr && pimagelistTree.is_set() && data.m_pitem->m_dwState & ::data::tree_item_state_expandable)
         {

            _001GetItemElementRect(rectangle, data, e_tree_element_expand_box);

            i32 iImage;

            if(data.m_pitem->m_dwState & ::data::tree_item_state_expanded)
            {

               iImage = (i32) ptree->m_iImageCollapse;

            }
            else
            {

               iImage = (i32) ptree->m_iImageExpand;

            }

            pimagelistTree->draw(data.m_pdc, iImage, rectangle.top_left(), 0, m_uchHoverAlpha);

         }

      }

      auto elapsed = start.elapsed();
      start.Now();
      if (elapsed > 2_ms)
      {

         //WARNING("tree item drawing section took more than 2ms");

      }

      //FORMATTED_TRACE("(1)TreeItemElapsed %d", ::duration.elapsed());

      //      ::aura::savings & savings = psession->m_paurasession->savings();

      if (bHover) // selected
      {

         auto rectangleFill = ::rectangle_f64(data.m_rectangleClient.left, data.m_rectangle.top, data.m_rectangleClient.right, data.m_rectangle.bottom);

         data.m_pdc->fill_rectangle(rectangleFill, argb(127, 125, 166, 228));

      }

      if(bSelected) // selected
      {

         //if(psession->m_paurasession->savings().is_trying_to_save(::e_resource_processing))
         //{

            data.m_pdc->fill_rectangle(data.m_rectangle, argb(127, 96,96,96));

         //}
         //else
         //{

         //   ::rectangle_i32 rectangleUnion;

         //   if (_001GetItemElementRect(rectangle, data, e_tree_element_image))
         //   {

         //      rectangleUnion = rectangle;

         //   }

         //   if (_001GetItemElementRect(rectangle, data, e_tree_element_text))
         //   {

         //      rectangleUnion.unite(rectangle, rectangleUnion);

         //   }

         //   class imaging & imaging = psystem->imaging();

         //   ::color::color crTranslucid = rgb(0, 0, 0);

         //   imaging.color_blend(data.m_pdc,    rectangleUnion.left, rectangleUnion.top,
         //   rectangleUnion.width(), rectangleUnion.height(),
         //   crTranslucid, 127);

         //}

      }

      if(pimagelistItem != nullptr)
      {

         i32 iImage = (i32) data.m_pitem->get_image();

         if(iImage >= 0)
         {

            if (_001GetItemElementRect(rectangle, data, e_tree_element_image))
            {

               pimagelistItem->draw(data.m_pdc, iImage, rectangle.top_left(), 0);

            }

         }

      }

      auto pitemData = data.m_pitem;

      string strItem = pitemData->get_text();

      if(strItem.has_char() && _001GetItemElementRect(rectangle, data, e_tree_element_text))
      {

         ::draw2d::brush_pointer pbrushText;

         if(bSelected) // selected
         {

            if(bHover)
            {

               pbrushText = m_pbrushTextSelectedHighlight;

            }
            else
            {

               pbrushText = m_pbrushTextSelected;

            }

         }
         else
         {

            if(bHover)
            {

               pbrushText = m_pbrushTextSelected;

            }
            else
            {

               pbrushText = m_pbrushText;

            }

         }

         data.m_pdc->set(pbrushText);

         data.m_pdc->set(m_pfontTreeItem);

         data.m_pdc->_DrawText(strItem, rectangle, m_ealignText, m_edrawtext);

      }

   }


   index tree::_001GetIndentation()
   {
      return 24;
   }




   void tree::on_message_mouse_move(::message::message * pmessage)
   {

      auto pmouse = pmessage->m_union.m_pmouse;

      //if (!m_bTrackMouseLeave)
      {

         track_mouse_leave();

      }

      update_tree_hover(pmouse->m_point);

      pmessage->m_bRet = true;

   }


   void tree::on_message_mouse_leave(::message::message * pmessage)
   {
      m_pitemHover = nullptr;
      set_need_redraw();
      pmessage->m_bRet = true;
   }

   void tree::on_message_left_button_double_click(::message::message * pmessage)
   {

      auto pmouse = pmessage->m_union.m_pmouse;

      //on_click(item);

      __pointer(::data::tree_item) pitem;

      ::user::enum_tree_element eelement;

      pitem = _001HitTest(pmouse->m_point, eelement);

      if(pitem != nullptr)
      {

         if(eelement == e_tree_element_expand_box || eelement == e_tree_element_image || eelement == e_tree_element_text)
         {

            _001ExpandItem(pitem, ::e_source_user, !(pitem->m_dwState & ::data::tree_item_state_expanded));

         }

      }

   }


   void tree::on_message_left_button_down(::message::message * pmessage)
   {

      auto pmouse = pmessage->m_union.m_pmouse;

      //pmouse->previous();

      auto point = pmouse->m_point;

      __pointer(::data::tree_item) pitem;

      ::user::enum_tree_element eelement;

      screen_to_client(point);

      pitem = _001HitTest(point, eelement);

      _001SelectItem(pitem);

      pmessage->m_bRet = true;

      pmouse->m_lresult = 1;

   }


   void tree::on_message_left_button_up(::message::message * pmessage)
   {

      auto pmouse = pmessage->m_union.m_pmouse;

      m_uiLButtonUpFlags = (::u32) pmouse->m_nFlags;

      m_pointLButtonUp = pmouse->m_point;

      perform_click();

      pmessage->m_bRet = true;

      pmouse->m_lresult = 1;

   }

   void tree::perform_click()
   {

      auto point = m_pointLButtonUp;

      __pointer(::data::tree_item) pitem;

      ::user::enum_tree_element eelement;

      screen_to_client(point);

      pitem = _001HitTest(point, eelement);

      if(pitem != nullptr)
      {

         if (eelement == e_tree_element_expand_box)
         {

            synchronous_lock synchronouslock(mutex());

            m_treeitemaExpand.add_unique(pitem);

            m_evExpand.set_event();

         }
         else if (eelement == e_tree_element_image || eelement == e_tree_element_text)
         {

            synchronous_lock synchronouslock(mutex());

            m_treeitemaOpen.add_unique(pitem);

            m_evOpen.set_event();

         }


      }

   }


   void tree::perform_right_click(uptr nFlags, const ::point_i32 & pointCursor)
   {

      //_001OnRightClick(nFlags, pointCursor);

      auto point(pointCursor);

      __pointer(::data::tree_item) pitem;

      ::user::enum_tree_element eelement;

      screen_to_client(point);

      pitem = _001HitTest(point, eelement);

      if (pitem != nullptr)
      {

         if (eelement == e_tree_element_image || eelement == e_tree_element_text)
         {

            _001OnItemContextMenu(pitem, ::e_source_user, this, pointCursor);

         }

      }

   }


   void tree::on_message_right_button_down(::message::message * pmessage)
   {

      auto pmouse = pmessage->m_union.m_pmouse;

      pmouse->previous();

      pmessage->m_bRet = true;

      pmouse->m_lresult = 1;

   }


   void tree::on_message_right_button_up(::message::message * pmessage)
   {

      auto pmouse = pmessage->m_union.m_pmouse;

      perform_right_click(pmouse->m_nFlags, pmouse->m_point);

      pmessage->m_bRet = true;

      pmouse->m_lresult = 1;

   }


   void tree::_001OnTimer(::timer * ptimer)
   {

      ::user::interaction::_001OnTimer(ptimer);

   }


   bool tree::on_click(::item * pitem)
   {

      return false;

   }


   bool tree::on_right_click(::item * pitem)
   {

      return false;

   }


   __pointer(::data::tree_item) tree::_001HitTest(const ::point_i32 & point, ::user::enum_tree_element & eelement)
   {

      index iy = point.y;

      index iItem = -1;

      index iItemHeight = (::index) _001GetItemHeight();

      auto pointOffset = get_viewport_offset();

      if(iItemHeight != 0)
      {

         iItem = (i32) ((iy + pointOffset.y) / iItemHeight);

      }

      if (iItem < 0)
      {

         return nullptr;

      }

      synchronous_lock synchronouslock(m_ptree ? m_ptree->mutex() : nullptr);

      __pointer(::data::tree_item) pitem = get_proper_item(iItem);

      if (pitem == nullptr)
      {

         return nullptr;

      }

      index iLevel = pitem->m_iLevel;

      index x = (i32) (point. x - _001GetIndentation() * (iLevel) + pointOffset.x);
      if(x >= 0 && x < 16)
         eelement = e_tree_element_expand_box;
      if(x >= 18 && x < 34)
         eelement = e_tree_element_image;
      if(x >= 36)
         eelement = e_tree_element_text;

      return pitem;


   }


   double tree::_001GetItemHeight()
   {

      return m_dItemHeight;

   }


   void tree::install_message_routing(::channel * pchannel)
   {

      ::user::interaction::install_message_routing(pchannel);
      ::user::scroll_base::install_message_routing(pchannel);

      MESSAGE_LINK(e_message_create, pchannel, this, &tree::on_message_create);
      MESSAGE_LINK(e_message_left_button_double_click, pchannel, this, &tree::on_message_left_button_double_click);
      MESSAGE_LINK(e_message_left_button_up, pchannel, this, &tree::on_message_left_button_up);
      MESSAGE_LINK(e_message_left_button_down, pchannel, this, &tree::on_message_left_button_down);
      MESSAGE_LINK(e_message_right_button_up, pchannel, this, &tree::on_message_right_button_up);
      MESSAGE_LINK(e_message_right_button_down, pchannel, this, &tree::on_message_right_button_down);
      MESSAGE_LINK(e_message_mouse_move, pchannel, this, &tree::on_message_mouse_move);
      MESSAGE_LINK(e_message_mouse_leave, pchannel, this, &tree::on_message_mouse_leave);
      MESSAGE_LINK(e_message_hscroll, pchannel, this, &tree::_001OnHScroll);
      MESSAGE_LINK(e_message_vscroll, pchannel, this, &tree::_001OnVScroll);
      MESSAGE_LINK(e_message_change_experience, pchannel, this, &tree::_001OnChangeExperience);
//      //MESSAGE_LINK(e_message_timer         , pchannel, this, &tree::_001OnTimer);

   }


   void tree::on_change_view_size(::draw2d::graphics_pointer & pgraphics)
   {

      ::size_f64 sizeTotal;

      sizeTotal.cx = m_iCurrentImpactWidth;

      sizeTotal.cy = (::i32)(get_proper_item_count() * _001GetItemHeight());

      m_scrolldataVertical.m_iLine = (::i32) m_dItemHeight;

      set_total_size(sizeTotal);

      ::user::scroll_base::on_change_view_size(pgraphics);

   }


   bool tree::_001GetItemElementRect(
   RECTANGLE_I32 * prectangle,

   ::user::tree_draw_item &drawitem,
   ::user::enum_tree_element eelement)
   {
      switch(eelement)
      {
      case e_tree_element_expand_box:
      {
         prectangle->left   = (::i32)(drawitem.m_rectangle.left);

         prectangle->right  = (::i32)minimum(prectangle->left + 16, drawitem.m_rectangle.right);

         prectangle->top    = (::i32)(drawitem.m_rectangle.top);

         prectangle->bottom = (::i32)(drawitem.m_rectangle.bottom);

      }
      break;
      case e_tree_element_image:
      {
         prectangle->left   = (::i32)(drawitem.m_rectangle.left + 18);

         prectangle->right  = (::i32)minimum(prectangle->left + 16, drawitem.m_rectangle.right);

         int iHDiff = 0;

         if (m_pimagelist != nullptr)
         {

            iHDiff = (::i32) (drawitem.m_rectangle.height() - m_pimagelist->m_size.cy);

         }

         prectangle->top    = (::i32)(drawitem.m_rectangle.top +iHDiff/2);

         prectangle->bottom = (::i32)(drawitem.m_rectangle.bottom - iHDiff / 2);

      }
      break;
      case e_tree_element_text:
      {
         prectangle->left   = (::i32)(drawitem.m_rectangle.left + 38);

         prectangle->right  = (::i32)(drawitem.m_rectangle.right);

         prectangle->top    = (::i32)(drawitem.m_rectangle.top);

         prectangle->bottom = (::i32)(drawitem.m_rectangle.bottom);

      }
      break;
      }
      return true;

   }


   void tree::_001SelectItem(::data::tree_item * pitem)
   {

      if (is_selected(pitem))
      {

         return;

      }

      selection_set(pitem);

      set_need_redraw();

      post_redraw();

   }


   void tree::_001ExpandItem(::data::tree_item * pitem, const ::action_context & context, bool bExpand, /* = true */ bool bRedraw, /*=true*/ bool bLayout /*=true*/)
   {

      //::data::simple_lock lock(pitem->m_pitem);

      __UNREFERENCED_PARAMETER(bLayout);

      auto pointOffset = get_viewport_offset();

      if(bExpand)
      {

         if(!(pitem->m_dwState & ::data::tree_item_state_expanded))
         {

            pitem->m_dwState |= ::data::tree_item_state_expanded;

            _001OnItemExpand(pitem, context);


            // scroll properly to show the highest possible number
            // of children while trying to preserve the old position and
            // never passing
            index iLevel = 0;
            index iParentIndex = get_proper_item_index(pitem, &iLevel);

            index iLastChildIndex = iParentIndex + pitem->get_proper_descendant_count();

            index iDivision;

            if (_001GetItemHeight() == 0)
            {

               // height is zero?!?!
               iDivision = 1;

            }
            else
            {

               iDivision = (::index) (pointOffset.y / _001GetItemHeight());

            }

            index iLastVisibleIndex = (index) (iDivision + _001GetVisibleItemCount()) + 1;



            index iObscured; // obscured proper descendants
            iObscured = iLastChildIndex  - iLastVisibleIndex;

            if(iObscured > 0)
            {

               index iNewScroll = (i32) (pointOffset.y + iObscured * _001GetItemHeight());

               if (iNewScroll > (iParentIndex * _001GetItemHeight()))
               {

                  iNewScroll = (::index)(iParentIndex * _001GetItemHeight());

               }

               queue_graphics_call([this, iNewScroll](::draw2d::graphics_pointer & pgraphics)
                  {


                     set_viewport_offset_y(pgraphics, (int)maximum(iNewScroll, 0));

                  });
               //            _001SetYScroll(maximum(iNewScroll, 0), false);
               //m_pscrollbarVertical->_001SetScrollPos(pointOffset.y);
            }
         }
      }
      else
      {
         if ((pitem->m_dwState & ::data::tree_item_state_expanded))
         {

            pitem->m_dwState &= ~::data::tree_item_state_expanded;

            _001OnItemCollapse(pitem, context);

         }
      }

      set_need_layout();
      if(bRedraw)
      {
         set_need_redraw();
      }

   }


   __pointer(::data::tree) tree::find_tree(::data::tree_item * pitem) const
   {

      //return m_ptree->contains(pitem);

      return m_ptree;

   }


   __pointer(::data::tree_item) tree::find(::data::item * pitem, index * piIndex)
   {

      return  m_ptree->find(pitem, piIndex);

   }


   bool tree::contains(::data::item * pitem)
   {

      return find(pitem).is_set();

   }


   bool tree::contains(::data::tree_item * pitem)
   {

      if (m_ptree->contains(pitem))
         return true;

      return false;

   }


   void tree::_001OnItemExpand(::data::tree_item * pitem, const ::action_context & context)
   {

      __pointer(::data::tree) ptree = find_tree(pitem);

      if (ptree.is_set())
      {

         ptree->_001OnItemExpand(pitem, context);

      }

   }

   void tree::_001OnItemCollapse(::data::tree_item * pitem, const ::action_context & context)
   {

      __pointer(::data::tree) ptree = find_tree(pitem);

      if (ptree.is_set())
      {

         ptree->_001OnItemCollapse(pitem, context);

      }

   }

   void tree::_001OnVScroll(::message::message * pmessage)
   {

      pmessage->previous();


   }


   void tree::_001OnHScroll(::message::message * pmessage)
   {

      pmessage->previous();

   }


   void tree::_001OnChangeExperience(::message::message* pmessage)
   {

      pmessage->previous();

//      style_context context(this);

      auto psystem = m_psystem->m_paurasystem;

      auto pdraw2d = psystem->draw2d();

      auto pgraphics = pdraw2d->create_memory_graphics(this);

      auto pstyle = get_style(pgraphics);

      m_colorTreeBackground = get_color(pstyle, ::e_element_background);

      __defer_construct(m_pbrushTextSelectedHighlight);
      __defer_construct(m_pbrushTextSelected);
      __defer_construct(m_pbrushTextHighlight);
      __defer_construct(m_pbrushText);

      __defer_construct(m_pfontTreeItem);

      m_pbrushTextSelectedHighlight->create_solid(get_color(pstyle, ::e_element_hilite_text, ::user::e_state_selected));
      m_pbrushTextSelected->create_solid(get_color(pstyle, ::e_element_item_text, ::user::e_state_selected));
      m_pbrushTextHighlight->create_solid(get_color(pstyle, ::e_element_item_text, ::user::e_state_selected));
      m_pbrushText->create_solid(get_color(pstyle, ::e_element_item_text));

      m_pfontTreeItem = get_font(pstyle);

   }


   void tree::on_change_viewport_offset(::draw2d::graphics_pointer & pgraphics)
   {

      m_pitemFirstVisible = CalcFirstVisibleItem(m_iFirstVisibleItemProperIndex);

      ::user::scroll_base::on_change_viewport_offset(pgraphics);

//      auto psession = get_session();
//
//      auto puser = psession->user();
//
//      auto pwindowing = puser->windowing();
//
//      auto pointCursor = pwindowing->get_cursor_position();
//
//      auto pmouse = __create_new < ::user::mouse >();
//
//      pmouse->m_point = pointCursor;
//
//      update_hover(pmouse);
//
//      set_need_redraw();
//
//      post_redraw();

   }


   void tree::on_layout(::draw2d::graphics_pointer & pgraphics)
   {

      ::user::interaction::on_layout(pgraphics);

      ::rectangle_i32 rectangleClient;

      get_client_rect(rectangleClient);

      if (rectangleClient.area() <= 0)
      {

         return;

      }

//      auto preferredDensity = preferred_density();

//      m_dItemHeight = 18.0 * preferredDensity;

      //if (m_puserstyle == nullptr)
      //{

      //   m_puserstyle = get_top_level();

      //}

      //if (m_puserstyle == nullptr)
      //{

      //   m_puserstyle = papp->userstyle();

      //}

      _001CalculateItemHeight(pgraphics);

      m_iCurrentImpactWidth = _001CalcTotalImpactWidth(pgraphics);

      m_pitemFirstVisible = CalcFirstVisibleItem(m_iFirstVisibleItemProperIndex);

      size_f64 sizeTotal;

      sizeTotal.cx = m_iCurrentImpactWidth;

      sizeTotal.cy = _001CalcTotalImpactHeight();

      set_total_size(sizeTotal);

      on_change_view_size(pgraphics);

      on_change_viewport_offset(pgraphics);

   }


   void tree::_001OnOpenItem(::data::tree_item * pitem, const ::action_context & context)
   {

      if (context.contains(this))
      {

         return;

      }

      _001SelectItem(pitem);

      set_need_redraw();

      post_redraw();

      pitem->m_ptree->_001OnOpenItem(pitem, context + this);

   }


   void tree::_001OnItemContextMenu(::data::tree_item * pitem, const ::action_context & context, ::user::tree * ptree, const ::point_i32 & point)
   {

      if (context.contains(this))
      {

         return;

      }

      pitem->m_ptree->_001OnItemContextMenu(pitem, context + this, ptree, point);

   }


   void tree::update_tree_hover()
   {

      auto psession = get_session();

      auto puser = psession->user();

      auto pwindowing = puser->windowing();

      auto pointCursor = pwindowing->get_cursor_position();

      update_tree_hover(pointCursor);

   }


   void tree::update_tree_hover(point_i32 point)
   {

      screen_to_client(point);

      ::user::enum_tree_element eelement;

      __pointer(::data::tree_item) pitem = _001HitTest(point, eelement);

      //if(eelement != e_tree_element_image && eelement != e_tree_element_text)
      //{

      //   pitem = nullptr;

      //}

      if(pitem != m_pitemHover)
      {

         m_pitemHover = pitem;

         set_need_redraw();

         post_redraw();

      }

   }


   void tree::_001SetExpandImage(const ::string & pszMatter)
   {

      m_iImageExpand = m_pimagelist->add(image_payload(this, pszMatter));

   }


   void tree::_001SetCollapseImage(const ::string & pszMatter)
   {

      m_iImageCollapse = m_pimagelist->add(image_payload(this, pszMatter));

   }


   ::count tree::_001GetVisibleItemCount()
   {

      if (_001GetItemHeight() == 0)
      {

         return 0;

      }

      ::rectangle_i32 rectangle;

      get_client_rect(rectangle);

      return (::count)(rectangle.height() / _001GetItemHeight() - 1);

   }


   i32 tree::_001CalcCurrentImpactWidth()
   {

      ::rectangle_i32 rectangleClient;

      get_client_rect(rectangleClient);

      ::count iCount = _001GetVisibleItemCount();

      i32 iMaxWidth = rectangleClient.width();

      i32 iWidth;

      index iIndent  = _001GetIndentation();

      __pointer(::data::tree_item) pitem = m_pitemFirstVisible;

      if (pitem == nullptr)
      {

         return iMaxWidth;

      }

      for(i32 i = 0; i < iCount; i++)
      {

         iWidth = (i32) (200 + iIndent * pitem->m_iLevel);

         if(iWidth > iMaxWidth)
         {

            iMaxWidth = iWidth;

         }

         pitem = pitem->get_item(::data::TreeNavigationProperForward);

         if (pitem == nullptr)
         {

            break;

         }

      }

      return iMaxWidth;

   }


   __pointer(::data::tree_item) tree::CalcFirstVisibleItem(index & iProperIndex)
   {

      synchronous_lock synchronouslock(m_ptree ? m_ptree->mutex() : nullptr);

      index nOffset;

      if (_001GetItemHeight() == 0)
      {

         return nullptr;

      }

      if (!m_ptree)
      {

         return nullptr;

      }

      auto pointOffset = get_viewport_offset();

      int iItemHeight = (int)(_001GetItemHeight());

      nOffset = pointOffset.y / iItemHeight;

      ::data::tree_item * pitem = nullptr;

      iProperIndex = 0;

         pitem = m_ptree->get_base_item();

         for (;;)
         {

            ::data::tree_item * pitemNext = pitem->get_item(::data::TreeNavigationProperForward);

            if (pitemNext == nullptr)
            {

               break;

            }

            pitem = pitemNext;

            if (nOffset <= 0)
            {

               return pitem;

            }

            nOffset--;

            iProperIndex++;

         }

         return pitem;

   }


   void tree::_001CalculateItemHeight(::draw2d::graphics_pointer & pgraphics)
   {

      auto dFontHeight = _001GetDefaultFontHeight(pgraphics);

      auto pstyle = get_style(pgraphics);

      m_dItemHeight = dFontHeight * get_double(pstyle, ::user::e_double_tree_item_height_rate, ::user::e_state_none, 1.0);

   }


   i32 tree::_001CalcTotalImpactWidth(::draw2d::graphics_pointer & pgraphics)
   {

      index nOffset;

      if (_001GetItemHeight() == 0)
      {

         return 0;

      }

      if (!m_ptree)
      {

         return 0;

      }

      defer_graphics(pgraphics);

      auto pointOffset = get_viewport_offset();

      nOffset = (::index)(pointOffset.y / _001GetItemHeight());

      nOffset = INT_MAX;

      ::data::tree_item * pitem = nullptr;

      int iWidth;

      int iMaxWidth = 0;

      index iLevel = 0;

      auto iIndent = _001GetIndentation();

      //auto psystem = m_psystem->m_paurasystem;

      //auto pdraw2d = psystem->draw2d();

      //auto pgraphics = pdraw2d->create_memory_graphics(this);

      //pgraphics->CreateCompatibleDC(nullptr);

      //auto pfont = __create < ::write_text::font > ();
      //pfont->operator=(*pdraw2d->fonts().GetListCtrlFont());
      //pfont->set_bold();
      //g->set_font(font);


      //on_ui_event(event_calc_item_height, object_tree, this);

      __pointer_array(::data::tree_item) spitema;

      pitem = m_ptree->get_base_item();
      
      iLevel = 0;

      for (;;)
      {

         pitem = pitem->get_item(::data::TreeNavigationProperForward, &iLevel);

         if (pitem == nullptr)
         {

            break;

         }

         if (spitema.find_first(pitem)>= 0)
         {

            //output_debug_string("what!?!");

            break;

         }

         spitema.add(pitem);

         if (nOffset <= 0)
         {

            break;

         }

         nOffset--;

         string strText = pitem->get_text();

         size_f64 s = pgraphics->get_text_extent(strText);

         iWidth = (i32)(48 + s.cx + iIndent * (iLevel + 1));

         if (iWidth > iMaxWidth)
         {

            iMaxWidth = iWidth;

         }

      }

      return iMaxWidth;

   }


   int tree::_001CalcTotalImpactHeight()
   {

      return (int) (_001GetProperItemCount() * _001GetItemHeight());

   }


   count tree::_001GetProperItemCount()
   {

      if (!m_ptree)
      {

         return 0;

      }

      ::count iProperCount = 0;

      index iLevel;

      ::data::tree_item * ptreeitem = nullptr;

      __pointer_array(::data::tree_item) treeitema;

      ptreeitem = m_ptree->get_base_item();

      for (;;)
      {

         ptreeitem = ptreeitem->get_item(::data::TreeNavigationProperForward, &iLevel);

         if (!ptreeitem)
         {

            break;

         }

         if (ptreeitem == m_ptree->get_base_item())
         {

            break;

         }

         if (treeitema.find_first(ptreeitem) >= 0)
         {

            //output_debug_string("what!!?");

            break;

         }

         treeitema.add(ptreeitem);

         iProperCount++;

      }

      return iProperCount;

   }


   void tree::_001OnTreeDataChange()
   {

      set_need_layout();

   }


   __pointer(::image_list) tree::get_image_list()
   {

      return m_pimagelist;

   }


   i32 tree::get_wheel_scroll_delta()
   {

      return (::i32) (3.0 * m_dItemHeight);

   }


   bool tree::selection_add(::data::item * pitemdata, index i)
   {

      auto  pitem = find(pitemdata, &i);

      if (!pitem)
      {

         return false;

      }

      return selection_add(pitem);

   }


   ::count tree::selection_add(::data::tree_item_ptr_array & itemptra)
   {

      ::count count = 0;

      for (i32 i = 0; i < itemptra.get_count(); i++)
      {

         if (selection_add(itemptra[i]))
         {

            count++;

         }

      }

      return count;

   }


   bool tree::selection_add(::data::tree_item * pitem)
   {
      if (!contains(pitem))
      {

         return false;

      }

      return m_pitemptraSelected->add_unique(pitem);

   }


   bool tree::selection_set(::data::item * pitemdata, bool bIfNotInSelection, bool bIfParentInSelection)
   {

      return selection_set(0, pitemdata, bIfNotInSelection, bIfParentInSelection);

   }


   bool tree::selection_set(index i, ::data::item * pitemdata, bool bIfNotInSelection, bool bIfParentInSelection)
   {

      auto pitem = find(pitemdata, &i);

      if (!pitem)
      {

         return false;

      }

      return selection_set(pitem, bIfNotInSelection, bIfParentInSelection);

   }


   ::count tree::selection_set(::data::tree_item_ptr_array & itemptra)
   {

      ::count count = 0;

      for (i32 i = 0; i < itemptra.get_count(); i++)
      {

         if (contains(itemptra[i]) && m_pitemptraSelected->add_unique(itemptra[i]))
         {

            count++;

         }

      }

      return count;

   }


   bool tree::selection_set(::data::tree_item * pitem, bool bIfNotInSelection, bool bIfParentInSelection)
   {

      if (!contains(pitem))
      {

         return false;

      }

      if (bIfNotInSelection && is_selected(pitem))
      {

         return true;

      }

      if (bIfParentInSelection && !is_selected(pitem->m_pparent))
      {

         return true;

      }

      bool bContains = m_pitemptraSelected->contains(pitem);

      m_pitemptraSelected->erase_all();

      m_pitemptraSelected->add(pitem);

      return bContains;

   }


   bool tree::selection_erase(::data::item * pitemdata, index i)
   {

      auto pitem = find(pitemdata, &i);

      if (!pitem)
      {

         return false;

      }

      return selection_erase(pitem);

   }


   ::count tree::selection_erase(::data::tree_item_ptr_array & itemptra)
   {

      ::count count = 0;

      for (i32 i = 0; i < itemptra.get_count(); i++)
      {

         if (m_pitemptraSelected->erase(itemptra[i]))
         {

            count++;

         }

      }

      return count;

   }


   bool tree::selection_erase(::data::tree_item * pitem)
   {

      return m_pitemptraSelected->erase(pitem) >= 0;

   }


   ::count tree::clear_selection()
   {

      return m_pitemptraSelected->erase_all();

   }


   bool tree::hover(::data::item * pitemdata, index i)
   {

      auto pitem = find(pitemdata, &i);

      return hover(pitem);

   }


   bool tree::hover(::data::tree_item * pitem)
   {

      if (pitem == nullptr)
      {

         m_pitemHover = nullptr;

         return true;

      }

      if (!contains(pitem))
      {

         return false;

      }

      return m_pitemHover == pitem;

   }


   bool tree::is_selected(const ::data::tree_item * pitem) const
   {

      return m_pitemptraSelected->contains(pitem);

   }


   bool tree::is_selected(const ::data::item * pitemdata) const
   {

      if (!pitemdata)
      {

         return false;

      }

      for (i32 i = 0; i < m_pitemptraSelected->get_count(); i++)
      {

         if (m_pitemptraSelected->element_at(i)->m_pdataitem == pitemdata)
         {

            return true;

         }

      }

      return false;

   }


   bool tree::is_hover(const ::data::tree_item * pitem) const
   {

      return pitem && m_pitemHover == pitem;

   }


   bool tree::is_hover(const ::data::item * pitem) const
   {

      if (!pitem || !m_pitemHover)
      {

         return false;

      }

      if (m_pitemHover->m_pdataitem != pitem)
      {

         return false;

      }

      return true;

   }


   bool tree::can_merge(const ::data::tree * ptree) const
   {

      if (!m_ptree)
      {

         return false;

      }

      return !m_ptree->contains(ptree);

   }


   bool tree::merge(::data::tree * pdatatree, bool bBind)
   {

      if (pdatatree == nullptr)
      {

         return false;

      }

      ::user::tree_data * ptree = dynamic_cast <::user::tree_data *>  (pdatatree);

      if (ptree == nullptr)
      {

         return false;

      }

      if (!can_merge(ptree))
      {

         return false;

      }

      m_ptree->insert_item(ptree);

      ptree->on_merge_user_tree(this);

      if (bBind)
      {

         __refer(m_treeaBound.add_new(), ptree);

         ptree->m_usertreeaBound.add(this);

         ptree->on_bind_user_tree(this);

      }

      ptree->m_usertreea.add_unique(this);

      __pointer(::user::impact) pimpact = this;

      if(pimpact.is_set())
      {

         pimpact->get_document()->add_data(ptree);

      }

      ptree->install_message_routing(m_pprimitiveimpl);

      return true;


   }


   __pointer(::data::tree_item) tree::get_proper_item(index i, index * piLevel)
   {

      if (!m_ptree)
      {

         return nullptr;

      }

      ::data::tree_item * pitem = m_ptree->get_proper_item(i, piLevel);

      if (::is_set(pitem))
      {

         return pitem;

      }

      return nullptr;

   }


   __pointer(::data::tree_item) tree::_get_proper_item(index i, index* piLevel, index* piCount)
   {

      if (!m_ptree)
      {

         return nullptr;

      }

      index iCount = 0;

      __pointer(::data::tree_item) pitem;

      pitem = m_ptree->_get_proper_item(i, piLevel, &iCount);

      if (::is_set(pitem))
      {

         return pitem;

      }

      if (piCount)
      {

         *piCount += iCount;

      }

      return nullptr;

   }


   index tree::get_proper_item_index(::data::tree_item *pitemParam, index * piLevel)
   {

      index iCount = 0;

      index iFound;

      iFound = m_ptree->get_proper_item_index(pitemParam, piLevel, &iCount);

      if (iFound >= 0)
      {

         return iCount;

      }

      return -1;

   }


   index tree::get_proper_item_count()
   {

      synchronous_lock synchronouslock(mutex());

      if (!m_ptree)
      {

         return -1;

      }

      index iCount = 0;

      iCount += m_ptree->get_proper_item_count();

      return iCount;

   }


   void tree::_001EnsureVisible(::data::tree_item * pitem)
   {

      if (pitem == nullptr)
      {

         return;

      }

      ::data::tree_item * pitemExpand = pitem;

      while(pitemExpand != nullptr)
      {

         pitemExpand->m_dwState |= ::data::tree_item_state_expanded;

         pitemExpand = pitemExpand->m_pparent;

      }

      index iLevel = 0;

      index iIndex = get_proper_item_index(pitem, &iLevel);

      auto pointOffset = get_viewport_offset();

      if (m_dItemHeight <= 0.)
      {

         m_dItemHeight = 18.0;

      }

      index iMinVisibleIndex = (index)(pointOffset.y / m_dItemHeight);

      index iMaxVisibleIndex = (index)(iMinVisibleIndex + _001GetVisibleItemCount());

      if (iIndex < iMinVisibleIndex || iIndex > iMaxVisibleIndex)
      {

         index iNewScrollIndex = iIndex;

         int iy = (int)(maximum(iNewScrollIndex, 0) * m_dItemHeight);

         queue_graphics_call([this, iy](::draw2d::graphics_pointer & pgraphics)
            {

               set_viewport_offset_y(pgraphics, iy);

            });

         set_need_layout();

         set_need_redraw();

      }

   }


   void tree::handle(::topic * ptopic, ::context * pcontext)
   {

      if (m_ptree)
      {

         m_ptree->handle(ptopic, pcontext);

      }

   }


   bool tree::keyboard_focus_is_focusable() const
   {

      return true;

   }


   void tree::on_viewport_offset(::draw2d::graphics_pointer & pgraphics)
   {

   }


} // namespace aura



