#include "framework.h"
#include "tree.h"
#include "tree_data.h"
#include "acme/constant/message.h"
#include "acme/constant/timer.h"
#include "acme/exception/interface_only.h"
#include "acme/prototype/data/item.h"
#include "acme/prototype/data/listener.h"
#include "acme/prototype/time/frequency.h"
#include "aura/message/user.h"
#include "aura/graphics/draw2d/draw2d.h"
#include "aura/graphics/image/list.h"
#include "aura/graphics/image/drawing.h"
//#include "aura/user/user/primitive_impl.h"
#include "aura/user/user/scroll_state.h"
#include "aura/user/user/style.h"
#include "berg/user/user/impact.h"
#include "berg/user/user/document.h"



namespace user
{


   tree::tree()
   {

      user_tree_common_construct();

   }


   tree::~tree()
   {

   }


   // ::core::application* tree::get_app()
   // {
   //
   //    auto papplication = application();
   //
   //    return ::is_set(papplication) ? papplication : nullptr;
   //
   // }
   //
   //
   // ::core::session* tree::get_session()
   // {
   //
   //    auto pacmesession = session();
   //
   //    return ::is_set(pacmesession) ? pacmesession : nullptr;
   //
   // }
   //
   //
   // ::core::system* tree::get_system()
   // {
   //
   //    auto pacmesystem = system();
   //
   //    return ::is_set(pacmesystem) ? pacmesystem : nullptr;
   //
   // }


   ::data::tree_item_base * tree::tree_item_base(::item * pitem)
   {

      return m_ptreedata->_find(pitem);

   }


   void tree::user_tree_common_construct()
   {

      __construct_new(m_ptreeitemptraSelected);

      m_bHover = false;
      m_iHoverAlphaInit = 0;
      m_iLeaveAlphaInit = 0;

      m_flagNonClient += ::user::interaction::e_non_client_hover_rect;

      m_econtroltype = ::user::e_control_type_tree;

      m_ptreeitemFirstVisible = nullptr;
      m_ptreeitemHover = nullptr;
      m_iItemCount = 0;
      m_dItemHeight = 0.;
      m_iImageExpand = -1;
      m_iImageCollapse = -1;
      m_iImageExpandDark = -1;
      m_iImageCollapseDark = -1;
      m_iHoverAlphaInit = 0;
      m_iHoverAlpha = 0;
      m_ealignText = e_align_left_center;
      m_edrawtext = e_draw_text_none;
      m_happeningOpen.m_eflagElement += e_flag_alertable_wait;
      m_happeningExpand.m_eflagElement += e_flag_alertable_wait;

      m_sizeItemMaximum.cx() = 16;
      m_sizeItemMaximum.cy() = 16;

   }



   void tree::on_message_create(::message::message * pmessage)
   {

      ::pointer<::message::create>pcreate(pmessage);

      if (pmessage->previous())
      {

         return;

      }


      //auto estatus =

      //m_ptreedata = create_tree_data();

      //if (!estatus)
      //{

      //   pcreate->error() << "Error creating tree data at ::user::tree::on_message_create";

      //   return;

      //}

      //estatus = 

      __construct_new(m_pimagelist);

      //if (!estatus)
      //{

      //   pcreate->error() << "Error creating image list at ::user::tree::on_message_create";

      //   return;

      //}

      //estatus = 

      m_pimagelist->create(16, 16, 0, 10, 10);

      //if (!estatus)
      //{

      //   pcreate->error() << "Error creating image list (2) at ::user::tree::on_message_create";

      //   return;

      //}
      _user_post([this]
         {
            fork([this]()
               {

                  _001SetExpandImage("matter://list/expand.png");
                  _001SetExpandImageDark("matter://list/expand_dark.png");

                  task_set_name(::type(this).name() + "::Expand");

                  auto pthread = ::get_task();

                  while (pthread->task_get_run())
                  {

                     m_happeningExpand.wait(500_ms);

                     if (m_treeitemaExpand.has_element())
                     {

                        auto ptreeitem = m_treeitemaExpand.pop();

                        _001ExpandItem(ptreeitem, ::e_source_user, !(ptreeitem->m_etreeitemstate & ::data::e_tree_item_state_expanded));

                        m_treeitemaExpand.erase_all();

                     }

                     m_happeningExpand.reset_happening();

                  }

               });

               });

      _user_post([this]
   {

      fork([this]()
         {

            _001SetCollapseImage("matter://list/collapse.png");
            _001SetCollapseImageDark("matter://list/collapse_dark.png");

            task_set_name(::type(this).name() + "::Open");

            auto pthread = ::get_task();

            while (pthread->task_get_run())
            {

               m_happeningOpen.wait(500_ms);

               if (m_treeitemaOpen.has_element())
               {

                  auto ptreeitem = m_treeitemaOpen.pop();

                  information() << "user::tree has open item";

                  _001OnOpenItem(ptreeitem, ::e_source_user);

               }
               else
               {

                  m_happeningOpen.reset_happening();

               }

            }

         });

      });

   }


   void tree::_001OnDraw(::draw2d::graphics_pointer & pgraphics)
   {

      if (m_bPendingDrawingObjectsUpdate)
      {

         update_drawing_objects();

      }

      pgraphics->set_text_rendering_hint(::write_text::e_rendering_anti_alias);

      pgraphics->set_alpha_mode(::draw2d::e_alpha_mode_blend);

      {

         auto timeStart = ::time::now();

         ::user::interaction::_001OnDraw(pgraphics);

         auto tickElapsed = timeStart.elapsed();

         if (tickElapsed > 50_ms)
         {

            //warning() <<"tree drawing took more than 50ms";

         }

      }

      {

         double dTime = 0.3;

         if (m_bHover)
         {

            auto iAlpha = (int)(m_iHoverAlphaInit + m_timeHoverStart.elapsed().floating_second() * 255.f/ dTime);

            m_iHoverAlpha = constrained(iAlpha, 0, 255);

            if (m_iHoverAlpha >= 255)
            {

               erase_graphical_output_purpose(this);

            }


         }
         else
         {

            auto iAlpha = (int)(m_iLeaveAlphaInit - m_timeLeaveStart.elapsed().floating_second() * 255.f/dTime);

            m_iHoverAlpha = constrained(iAlpha, 0, 255);

            if (m_iHoverAlpha <= 0)
            {

               erase_graphical_output_purpose(this);

            }

         }

      }

      {

         auto timeStart = ::time::now();

         auto rectangleX = this->rectangle();

         //pgraphics->set_alpha_mode(::draw2d::e_alpha_mode_blend);

         //pgraphics->fill_rectangle(rectangleX, m_colorTreeBackground);

         //auto pointCursor = get_cursor_position();

         //screen_to_client()(pointCursor);

         auto dwHoverIn = 300_ms;

         auto dwHoverOut = 1200_ms;

         //bool bTreeHover = rectangleX.contains(pointCursor);

         //if (bTreeHover)
         //{
         //   if (!m_bHoverStart)
         //   {
         //      m_bHoverStart = true;
         //      m_uchHoverAlphaInit = m_uchHoverAlpha;

         //      m_timeHoverStart.Now();

         //   }
         //   if (m_timeHoverStart.elapsed() > dwHoverIn)
         //   {
         //      m_uchHoverAlpha = 255;
         //   }
         //   else
         //   {
         //      auto pi = MATH_PI;
         //      auto f = 1.0 / dwHoverIn;
         //      auto omega = -pi * f; // omega pi
         //      auto t = m_timeHoverStart;
         //      unsigned int dwCurve = (unsigned int)(255.0 * (1.0 - exp(omega * t)));
         //      if (m_uchHoverAlphaInit + dwCurve > 255)
         //         m_uchHoverAlpha = 255;
         //      else
         //         m_uchHoverAlpha = (unsigned char)(m_uchHoverAlphaInit + dwCurve);
         //   }
         //}
         //else
         //{
         //   if (m_bHoverStart)
         //   {
         //      m_bHoverStart = false;
         //      m_uchHoverAlphaInit = m_uchHoverAlpha;

         //      m_timeHoverEnd.Now();

         //   }

         //   if (m_timeHoverEnd.elapsed() > dwHoverOut)
         //   {
         //      m_uchHoverAlpha = 0;
         //   }
         //   else
         //   {
         //      auto pi = MATH_PI;
         //      auto f = 1.0 / dwHoverOut;
         //      auto omega = -pi * f; // omega pi
         //      auto t = m_timeHoverStart;
         //      unsigned int dwCurve = (unsigned int)(255.0 * (1.0 - exp(omega * t)));
         //      if (m_uchHoverAlphaInit < dwCurve)
         //         m_uchHoverAlpha = 0;
         //      else
         //         m_uchHoverAlpha = (unsigned char)(m_uchHoverAlphaInit - dwCurve);
         //   }
         //}

         ::user::tree_draw_item drawitemdata;

         drawitemdata.m_pdc = pgraphics;

         drawitemdata.m_iIndentation = _001GetIndentation();

         drawitemdata.m_dItemHeight = _001GetItemHeight();

         drawitemdata.m_rectangleX = this->rectangle();

         auto pitem = m_ptreeitemFirstVisible;

         synchronous_lock synchronouslock(!pitem ? nullptr : pitem->_get_tree()->synchronization());

         ::collection::index iItem = m_iFirstVisibleItemProperIndex;

         auto iVisibleCount = _001GetVisibleItemCount();

         ::collection::index iIndex = 0;

         for (; pitem != nullptr; pitem = pitem->_get_item(::data::e_tree_navigation_proper_forward))
         {

            drawitemdata.m_pitem = pitem;

            drawitemdata.m_iItem = iItem;

            drawitemdata.m_rectangle = drawitemdata.m_rectangleX;

            drawitemdata.m_rectangle.left() = (int)(drawitemdata.m_iIndentation * pitem->m_iLevel);

            drawitemdata.m_rectangle.top() = (int)(iItem * drawitemdata.m_dItemHeight);

            drawitemdata.m_rectangle.bottom() = (int)(drawitemdata.m_rectangle.top() + drawitemdata.m_dItemHeight);

            drawitemdata.m_rectangle.right() = m_iCurrentImpactWidth;

            {
               
               auto tickItem = ::time::now();
               
               _001DrawItem(drawitemdata);

               auto tickElapsed = tickItem.elapsed();

               if (tickElapsed > 20_ms)
               {

                  //warning() <<"tree item drawing took more than 20ms";

               }

            }


            iItem++;

            iIndex++;

            if (iIndex > iVisibleCount)
            {

               break;

            }

         }


         auto tickElapsed = timeStart.elapsed();

         if (tickElapsed > 50_ms)
         {

            //warning() <<"tree drawing took more than 50ms";

         }

      }

   }


   void tree::_001DrawItem(tree_draw_item & data)
   {

      auto timeStart = ::time::now();

      ::int_rectangle rectangle;

      ::pointer<tree>ptree = this;

      ::pointer<::data::tree_item_base>ptreeitem = data.m_pitem;

      auto pimagelistItem = ptreeitem->get_user_item_image_list();

      if (pimagelistItem)
      {

         if (pimagelistItem->m_size > m_sizeItemMaximum)
         {

            m_sizeItemMaximum = pimagelistItem->m_size;

            set_need_layout();

         }

      }

      auto pstyle = ptree->get_style(data.m_pdc);

      ::image::image_list_pointer pimagelistTree = get_image_list();

      bool bSelected = ptree->is_selected(ptreeitem.m_p);

      bool bHover = ptree->is_hover(ptreeitem);

      data.m_pdc->set_alpha_mode(::draw2d::e_alpha_mode_blend);


      if (m_iHoverAlpha > 0)
      {


         if (ptree != nullptr && pimagelistTree.is_set() && data.m_pitem->m_etreeitemstate & ::data::e_tree_item_state_expandable)
         {

            _001GetItemElementRect(&rectangle, data, e_tree_element_expand_box);

            int iImage;

            if (data.m_pitem->m_etreeitemstate & ::data::e_tree_item_state_expanded)
            {

               if (pstyle->is_dark_mode())
               {

                  iImage = (int)ptree->m_iImageCollapseDark;

               }
               else
               {

                  iImage = (int)ptree->m_iImageCollapse;
               }

            }
            else
            {

               if (pstyle->is_dark_mode())
               {

                  iImage = (int)ptree->m_iImageExpandDark;

               }
               else
               {

                  iImage = (int)ptree->m_iImageExpand;

               }

            }

            pimagelistTree->draw(data.m_pdc, iImage, rectangle.top_left(), 0, m_iHoverAlpha);

         }

      }

      auto elapsed = timeStart.elapsed();
      
      if (elapsed > 2_ms)
      {

         //warning() <<"tree item drawing section took more than 2ms";

      }

      //informationf("(1)TreeItemElapsed %d", ::time.elapsed());

      //      ::aura::savings & savings = session()->savings();

      if (bHover) // selected
      {

         auto rectangleFill = ::double_rectangle(data.m_rectangleX.left(), data.m_rectangle.top(), data.m_rectangleX.right(), data.m_rectangle.bottom());

         data.m_pdc->fill_rectangle(rectangleFill, argb(127, 125, 166, 228));

      }

      if (bSelected) // selected
      {

         //if(session()->savings()->is_trying_to_save(::e_resource_processing))
         //{

         data.m_pdc->fill_rectangle(data.m_rectangle, argb(127, 96, 96, 96));

         //}
         //else
         //{

         //   ::int_rectangle rectangleUnion;

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

         //   imaging.color_blend(data.m_pdc,    rectangleUnion.left(), rectangleUnion.top(),
         //   rectangleUnion.width(), rectangleUnion.height(),
         //   crTranslucid, 127);

         //}

      }

      if (pimagelistItem != nullptr)
      {

         int iImage = (int)data.m_pitem->get_user_item_image();

         if (iImage >= 0 && pimagelistItem && pimagelistItem->m_pimage.ok())
         {

            if (_001GetItemElementRect(&rectangle, data, e_tree_element_image))
            {

               pimagelistItem->draw(data.m_pdc, iImage, rectangle.top_left(), 0);

            }

         }

      }

      auto pitemData = data.m_pitem;

      string strItem = pitemData->get_user_item_text();

      if (strItem.has_character() && _001GetItemElementRect(&rectangle, data, e_tree_element_text))
      {

         ::draw2d::brush_pointer pbrushText;

         if (bSelected) // selected
         {

            if (bHover)
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

            if (bHover)
            {

               pbrushText = m_pbrushTextSelected;

            }
            else
            {

               pbrushText = m_pbrushText;

            }

         }

         data.m_pdc->set(pbrushText);

         if (!m_pfontTreeItem)
         {

            update_drawing_objects();

         }

         data.m_pdc->set(m_pfontTreeItem);

         data.m_pdc->_DrawText(strItem, rectangle, m_ealignText, m_edrawtext);

      }

   }


   ::collection::index tree::_001GetIndentation()
   {
      return 24;
   }




   void tree::on_message_mouse_move(::message::message * pmessage)
   {

      auto pmouse = pmessage->m_union.m_pmouse;

      if (!m_bHover)
      {

         m_bHover = true;

         m_iHoverAlphaInit = m_iHoverAlpha;

         m_timeHoverStart.Now();

         add_graphical_output_purpose(this, ::graphics::e_output_purpose_fps);

      }

      track_mouse_leave();

      auto point = pmouse->m_pointHost;

      host_to_client()(point);

      update_tree_hover(point);

      pmessage->m_bRet = true;

   }


   void tree::on_message_mouse_leave(::message::message * pmessage)
   {
      m_ptreeitemHover = nullptr;
      m_timeLeaveStart.Now();
      m_iLeaveAlphaInit = m_iHoverAlpha;
      add_graphical_output_purpose(this, ::graphics::e_output_purpose_fps);
      m_bHover = false;
      pmessage->m_bRet = true;
   }

   void tree::on_message_left_button_double_click(::message::message * pmessage)
   {

      auto pmouse = pmessage->m_union.m_pmouse;

      //on_click(item);

      ::pointer<::data::tree_item_base>pitem;

      ::user::enum_tree_element eelement;

      auto point = pmouse->m_pointHost;

      host_to_client()(point);

      pitem = _001HitTest(point, eelement);

      if (pitem != nullptr)
      {

         if (eelement == e_tree_element_expand_box || eelement == e_tree_element_image || eelement == e_tree_element_text)
         {

            _001ExpandItem(pitem, ::e_source_user, !(pitem->m_etreeitemstate & ::data::e_tree_item_state_expanded));

         }

      }

   }


   void tree::on_message_left_button_down(::message::message * pmessage)
   {

      auto pmouse = pmessage->m_union.m_pmouse;

      //pmouse->previous();

      auto point = pmouse->m_pointHost;

      ::pointer<::data::tree_item_base>pitem;

      ::user::enum_tree_element eelement;

      host_to_client()(point);

      pitem = _001HitTest(point, eelement);

      _001SelectItem(pitem);

      pmessage->m_bRet = true;

      pmouse->m_lresult = 1;

   }


   void tree::on_message_left_button_up(::message::message * pmessage)
   {

      auto pmouse = pmessage->m_union.m_pmouse;

      m_uiLButtonUpFlags = (unsigned int)pmouse->m_ebuttonstate;

      m_pointLButtonUp = pmouse->m_pointHost;

      perform_click();

      pmessage->m_bRet = true;

      pmouse->m_lresult = 1;

   }


   void tree::perform_click()
   {

      auto point = m_pointLButtonUp;

      ::pointer<::data::tree_item_base>pitem;

      ::user::enum_tree_element eelement;

      host_to_client()(point);

      pitem = _001HitTest(point, eelement);

      information() << "user::tree perform_click";

      if (pitem != nullptr)
      {

         if (eelement == e_tree_element_expand_box)
         {

            synchronous_lock synchronouslock(this->synchronization());

            information() << "user::tree perform_click expand_box";

            m_treeitemaExpand.add_unique(pitem);

            m_happeningExpand.set_happening();

         }
         else if (eelement == e_tree_element_image || eelement == e_tree_element_text)
         {

            synchronous_lock synchronouslock(this->synchronization());

            information() << "user::tree perform_click image or text";

            m_treeitemaOpen.add_unique(pitem);

            m_happeningOpen.set_happening();

         }


      }

   }


   void tree::perform_right_click(uptr nFlags, const ::int_point & pointCursor)
   {

      //_001OnRightClick(nFlags, pointCursor);

      auto point(pointCursor);

      ::pointer<::data::tree_item_base>pitem;

      ::user::enum_tree_element eelement;

      host_to_client()(point);

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

      auto point = pmouse->m_pointHost;

      host_to_client()(point);

      perform_right_click(pmouse->m_ebuttonstate, point);

      pmessage->m_bRet = true;

      pmouse->m_lresult = 1;

   }


   void tree::on_timer(::timer * ptimer)
   {

      ::user::interaction::on_timer(ptimer);

   }


   bool tree::on_click(::item * pitem, ::user::mouse * pmouse)
   {

      return false;

   }


   bool tree::on_right_click(::item * pitem, ::user::mouse * pmouse)
   {

      return false;

   }


   ::pointer<::data::tree_item_base>tree::_001HitTest(const ::int_point & point, ::user::enum_tree_element & eelement)
   {

      ::collection::index iy = point.y();

      ::collection::index iItem = -1;

      auto item_height = _001GetItemHeight();

      //auto pointOffset = get_context_offset();

      if (item_height != 0)
      {

         //iItem = (int)((iy + pointOffset.y()) / item_height);
         iItem = (int)((iy) / item_height);

      }

      if (iItem < 0)
      {

         return nullptr;

      }

      synchronous_lock synchronouslock(m_ptreedata ? m_ptreedata->synchronization() : nullptr);

      ::pointer<::data::tree_item_base>pitem = get_proper_item(iItem);

      if (pitem == nullptr)
      {

         return nullptr;

      }

      ::collection::index iLevel = pitem->m_iLevel;

      //index x = (int)(point.x() - _001GetIndentation() * (iLevel)+pointOffset.x());
      ::collection::index x = (int)(point.x() - _001GetIndentation() * (iLevel));
      if (x >= 0 && x < 16)
         eelement = e_tree_element_expand_box;
      if (x >= 18 && x < 34)
         eelement = e_tree_element_image;
      if (x >= 36)
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
      MESSAGE_LINK(e_message_scroll_x, pchannel, this, &tree::on_message_scroll_x);
      MESSAGE_LINK(e_message_scroll_y, pchannel, this, &tree::on_message_scroll_y);
      MESSAGE_LINK(e_message_change_experience, pchannel, this, &tree::_001OnChangeExperience);
      //      //MESSAGE_LINK(e_message_timer         , pchannel, this, &tree::on_timer);

   }

   
   void tree::update_drawing_objects()
   {

      _synchronous_lock synchronouslock(this->synchronization());
   
      //      style_context context(this);

      auto psystem = system();

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


   void tree::on_would_change_total_size(::user::enum_layout elayout)
   {

      auto scrollstatex = get_scroll_state_x(elayout);

      auto scrollstatey = get_scroll_state_x(elayout);

      scrollstatex.set_dimension(m_iCurrentImpactWidth);

      scrollstatey.set_dimension(get_proper_item_count() * _001GetItemHeight());

      scrollstatey.m_dLine = m_dItemHeight;

      set_scroll_state_x(scrollstatex);

      set_scroll_state_y(scrollstatex);

      on_change_scroll_state(elayout);

      //::user::scroll_base::on_change_sketch_scroll_state();

   }


   bool tree::_001GetItemElementRect(
      ::int_rectangle * prectangle,

      ::user::tree_draw_item & drawitem,
      ::user::enum_tree_element eelement)
   {
      switch (eelement)
      {
      case e_tree_element_expand_box:
      {
         prectangle->left() = (int)(drawitem.m_rectangle.left());

         prectangle->right() = (int)minimum(prectangle->left() + 16, drawitem.m_rectangle.right());

         prectangle->top() = (int)(drawitem.m_rectangle.top());

         prectangle->bottom() = (int)(drawitem.m_rectangle.bottom());

      }
      break;
      case e_tree_element_image:
      {
         prectangle->left() = (int)(drawitem.m_rectangle.left() + 18);

         prectangle->right() = (int)minimum(prectangle->left() + 16, drawitem.m_rectangle.right());

         int iHDiff = 0;

         if (m_pimagelist != nullptr)
         {

            iHDiff = (int)(drawitem.m_rectangle.height() - m_pimagelist->m_size.cy());

         }

         prectangle->top() = (int)(drawitem.m_rectangle.top() + iHDiff / 2);

         prectangle->bottom() = (int)(drawitem.m_rectangle.bottom() - iHDiff / 2);

      }
      break;
      case e_tree_element_text:
      {
         prectangle->left() = (int)(drawitem.m_rectangle.left() + 38);

         prectangle->right() = (int)(drawitem.m_rectangle.right());

         prectangle->top() = (int)(drawitem.m_rectangle.top());

         prectangle->bottom() = (int)(drawitem.m_rectangle.bottom());

      }
      break;
      }
      return true;

   }


   void tree::_001SelectItem(::data::tree_item_base * pitem)
   {

      if (is_selected(pitem))
      {

         return;

      }

      information() << "tree::_001SelectItem going to set selection";

      selection_set(pitem);

      set_need_redraw();

      post_redraw();

   }


   void tree::_001ExpandItem(::data::tree_item_base * ptreeitem, const ::action_context & context, bool bExpand, /* = true */ bool bRedraw, /*=true*/ bool bLayout /*=true*/)
   {

      //::data::simple_lock lock(pitem->m_pitem);

      __UNREFERENCED_PARAMETER(bLayout);

      auto pointOffset = get_context_offset();

      if (bExpand)
      {

         if (!(ptreeitem->m_etreeitemstate & ::data::e_tree_item_state_expanded))
         {

            ptreeitem->m_etreeitemstate |= ::data::e_tree_item_state_expanded;

            _001OnItemExpand(ptreeitem, context);


            // scroll properly to show the highest possible number
            // of children while trying to preserve the old position and
            // never passing
            ::collection::index iLevel = 0;
            ::collection::index iParentIndex = get_proper_item_index(ptreeitem, &iLevel);

            ::collection::index iLastChildIndex = iParentIndex + ptreeitem->get_proper_descendant_count();

            ::collection::index iDivision;

            if (_001GetItemHeight() == 0)
            {

               // height is zero?!?!
               iDivision = 1;

            }
            else
            {

               iDivision = (::collection::index)(pointOffset.y() / _001GetItemHeight());

            }

            ::collection::index iLastVisibleIndex = (::collection::index)(iDivision + _001GetVisibleItemCount()) + 1;



            ::collection::index iObscured; // obscured proper descendants
            iObscured = iLastChildIndex - iLastVisibleIndex;

            if (iObscured > 0)
            {

               auto dNewScroll = pointOffset.y() + iObscured * _001GetItemHeight();

               if (dNewScroll > (iParentIndex * _001GetItemHeight()))
               {

                  dNewScroll = iParentIndex * _001GetItemHeight();

               }

               //queue_graphics_call([this, iNewScroll](::draw2d::graphics_pointer & pgraphics)
                 // {


                     set_context_offset_y(maximum(dNewScroll, 0.));

                  //});
               //            _001SetYScroll(maximum(iNewScroll, 0), false);
               //m_pscrollbarY->_001SetScrollPos(pointOffset.y());
            }
         }
      }
      else
      {
         if ((ptreeitem->m_etreeitemstate & ::data::e_tree_item_state_expanded))
         {

            ptreeitem->m_etreeitemstate -= ::data::e_tree_item_state_expanded;

            _001OnItemCollapse(ptreeitem, context);
            bRedraw = true;

         }
      }

      set_need_layout();
      if (bRedraw)
      {
         set_need_redraw();
         post_redraw();
      }

   }


   ::pointer<::data::tree_base>tree::find_data_tree(::data::tree_item_base * pitem) const
   {

      //return m_ptreedata->contains(pitem);

      return m_ptreedata;

   }


   ::pointer<::data::tree_item_base>tree::find_data_tree_item(::item * pitem, ::collection::index * piIndex)
   {

      return m_ptreedata->_find(pitem, piIndex);

   }


   bool tree::contains(::item * pitem)
   {

      return find_data_tree_item(pitem).is_set();

   }


   bool tree::contains(::data::tree_item_base * pitem)
   {

      if (m_ptreedata->_contains(pitem))
      {

         return true;

      }

      return false;

   }


   void tree::_001OnItemExpand(::data::tree_item_base * pitem, const ::action_context & context)
   {

      ::pointer<::data::tree_base>ptreedata = find_data_tree(pitem);

      if (ptreedata.is_set())
      {

         ptreedata->_001OnItemExpand(pitem, context);

      }

   }

   void tree::_001OnItemCollapse(::data::tree_item_base * pitem, const ::action_context & context)
   {

      ::pointer<::data::tree_base>ptreedata = find_data_tree(pitem);

      if (ptreedata.is_set())
      {

         ptreedata->_001OnItemCollapse(pitem, context);

      }

   }


   void tree::on_message_scroll_y(::message::message * pmessage)
   {

      pmessage->previous();


   }


   void tree::on_message_scroll_x(::message::message * pmessage)
   {

      pmessage->previous();

   }


   void tree::_001OnChangeExperience(::message::message * pmessage)
   {

      pmessage->previous();

      m_bPendingDrawingObjectsUpdate = true;

   }


   //void tree::on_context_offset_layout(::draw2d::graphics_pointer & pgraphics)
   void tree::on_change_context_offset(::user::enum_layout elayout)
   {

      m_ptreeitemFirstVisible = CalcFirstVisibleItem(m_iFirstVisibleItemProperIndex);

      //::user::scroll_base::on_context_offset_layout(pgraphics);

      ::user::scroll_base::on_change_context_offset(elayout);

      //      
      //
      //      auto puser = user();
      //
      //      auto pwindowing = system()->windowing();
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

      auto rectangleX = this->rectangle();

      if (rectangleX.area() <= 0)
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

      m_ptreeitemFirstVisible = CalcFirstVisibleItem(m_iFirstVisibleItemProperIndex);

      auto scrollstatex = get_scroll_state_x(::user::e_layout_design);

      auto scrollstatey = get_scroll_state_y(::user::e_layout_design);

      scrollstatex.set_dimension(m_iCurrentImpactWidth);

      scrollstatey.set_dimension(_001CalcTotalImpactHeight());

      set_scroll_state_x(scrollstatex, ::user::e_layout_design);

      set_scroll_state_y(scrollstatey, ::user::e_layout_design);

      on_change_scroll_state(::user::e_layout_design);

      //on_change_context_offset(pgraphics);

   }


   void tree::_001OnOpenItem(::data::tree_item_base * pitem, const ::action_context & context)
   {

      information() << "tree::_001OnOpenItem";

      if (context.contains(this))
      {

         return;

      }

      information() << "tree::_001OnOpenItem going to select item";

      _001SelectItem(pitem);

      set_need_redraw();

      post_redraw();

      pitem->_get_tree()->_001OnOpenItem(pitem, context + this);

   }


   void tree::_001OnItemContextMenu(::data::tree_item_base * pitem, const ::action_context & context, ::user::tree * ptree, const ::int_point & point)
   {

      if (context.contains(this))
      {

         return;

      }

      pitem->_get_tree()->_001OnItemContextMenu(pitem, context + this, ptree, point);

   }


   void tree::update_tree_hover()
   {

      auto pointCursor = host_mouse_cursor_position();

      host_to_client()(pointCursor);

      update_tree_hover(pointCursor);

   }


   void tree::update_tree_hover(int_point point)
   {

      //host_to_client()(point);

      ::user::enum_tree_element eelement;

      ::pointer<::data::tree_item_base>pitem = _001HitTest(point, eelement);

      //if(eelement != e_tree_element_image && eelement != e_tree_element_text)
      //{

      //   pitem = nullptr;

      //}

      if (pitem != m_ptreeitemHover)
      {

         m_ptreeitemHover = pitem;

         set_need_redraw();

         post_redraw();

      }

   }


   void tree::_001SetExpandImage(const ::scoped_string & scopedstrMatter)
   {

      m_iImageExpand = m_pimagelist->add(::image::image_payload(this, scopedstrMatter));

   }


   void tree::_001SetCollapseImage(const ::scoped_string & scopedstrMatter)
   {

      m_iImageCollapse = m_pimagelist->add(::image::image_payload(this, scopedstrMatter));

   }


   void tree::_001SetExpandImageDark(const ::scoped_string & scopedstrMatter)
   {

      m_iImageExpandDark = m_pimagelist->add(::image::image_payload(this, scopedstrMatter));

   }


   void tree::_001SetCollapseImageDark(const ::scoped_string & scopedstrMatter)
   {

      m_iImageCollapseDark = m_pimagelist->add(::image::image_payload(this, scopedstrMatter));

   }


   ::collection::count tree::_001GetVisibleItemCount()
   {

      if (_001GetItemHeight() == 0)
      {

         return 0;

      }

      ::int_rectangle rectangle;

      rectangle = this->rectangle();

      return (::collection::count)(rectangle.height() / _001GetItemHeight() + 1);

   }


   int tree::_001CalcCurrentImpactWidth()
   {

      auto rectangleX = this->rectangle();

      ::collection::count iCount = _001GetVisibleItemCount();

      int iMaxWidth = rectangleX.width();

      int iWidth;

      ::collection::index iIndent = _001GetIndentation();

      ::pointer<::data::tree_item_base>pitem = m_ptreeitemFirstVisible;

      if (pitem == nullptr)
      {

         return iMaxWidth;

      }

      for (int i = 0; i < iCount; i++)
      {

         iWidth = (int)(200 + iIndent * pitem->m_iLevel);

         if (iWidth > iMaxWidth)
         {

            iMaxWidth = iWidth;

         }

         pitem = pitem->_get_item(::data::e_tree_navigation_proper_forward);

         if (pitem == nullptr)
         {

            break;

         }

      }

      return iMaxWidth;

   }


   ::pointer<::data::tree_item_base>tree::CalcFirstVisibleItem(::collection::index & iProperIndex)
   {

      synchronous_lock synchronouslock(m_ptreedata ? m_ptreedata->synchronization() : nullptr);

      if (_001GetItemHeight() == 0)
      {

         return nullptr;

      }

      if (!m_ptreedata)
      {

         return nullptr;

      }

      auto pointOffset = get_context_offset();

      auto dItemHeight = _001GetItemHeight();

      auto dOffset = pointOffset.y() / dItemHeight;

      ::data::tree_item_base * pitem = nullptr;

      iProperIndex = 0;

      pitem = m_ptreedata->_get_base_item();

      for (;;)
      {

         ::data::tree_item_base * pitemNext = pitem->_get_item(::data::e_tree_navigation_proper_forward);

         if (pitemNext == nullptr)
         {

            break;

         }

         pitem = pitemNext;

         dOffset-= 1.0;

         if (dOffset <= 0.)
         {

            return pitem;

         }

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


   int tree::_001CalcTotalImpactWidth(::draw2d::graphics_pointer & pgraphics)
   {

      ::collection::index nOffset;

      if (_001GetItemHeight() == 0)
      {

         return 0;

      }

      if (!m_ptreedata)
      {

         return 0;

      }

      defer_graphics(pgraphics);

      auto pointOffset = get_context_offset();

      nOffset = (::collection::index)(pointOffset.y() / _001GetItemHeight());

      nOffset = INT_MAX;

      ::data::tree_item_base * pitem = nullptr;

      int iWidth;

      int iMaxWidth = 0;

      ::collection::index iLevel = 0;

      auto iIndent = _001GetIndentation();

      //auto psystem = system();

      //auto pdraw2d = psystem->draw2d();

      //auto pgraphics = pdraw2d->create_memory_graphics(this);

      //pgraphics->CreateCompatibleDC(nullptr);

      //auto pfont = __øcreate < ::write_text::font > ();
      //pfont->operator=(*pdraw2d->fonts().GetListCtrlFont());
      //pfont->set_bold();
      //g->set_font(font);


      //on_ui_event(event_calc_item_height, object_tree, this);

      pointer_array < ::data::tree_item_base > spitema;

      pitem = m_ptreedata->_get_base_item();

      iLevel = 0;

      for (;;)
      {

         pitem = pitem->_get_item(::data::e_tree_navigation_proper_forward, &iLevel);

         if (pitem == nullptr)
         {

            break;

         }

         if (spitema.find_first(pitem) >= 0)
         {

            //informationf("what!?!");

            break;

         }

         spitema.add(pitem);

         if (nOffset <= 0)
         {

            break;

         }

         nOffset--;

         string strText = pitem->get_user_item_text();

         double_size s = pgraphics->get_text_extent(strText);

         iWidth = (int)(48 + s.cx() + iIndent * (iLevel + 1));

         if (iWidth > iMaxWidth)
         {

            iMaxWidth = iWidth;

         }

      }

      return iMaxWidth;

   }


   int tree::_001CalcTotalImpactHeight()
   {

      return (int)(_001GetProperItemCount() * _001GetItemHeight());

   }


   ::collection::count tree::_001GetProperItemCount()
   {

      if (!m_ptreedata)
      {

         return 0;

      }

      ::collection::count iProperCount = 0;

      ::collection::index iLevel;

      ::data::tree_item_base * ptreeitem = nullptr;

      pointer_array < ::data::tree_item_base > treeitema;

      ptreeitem = m_ptreedata->_get_base_item();

      for (;;)
      {

         ptreeitem = ptreeitem->_get_item(::data::e_tree_navigation_proper_forward, &iLevel);

         if (!ptreeitem)
         {

            break;

         }

         if (ptreeitem == m_ptreedata->_get_base_item())
         {

            break;

         }

         if (treeitema.find_first(ptreeitem) >= 0)
         {

            //informationf("what!!?");

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


   ::image::image_list_pointer tree::get_image_list()
   {

      return m_pimagelist;

   }


   int tree::get_wheel_scroll_delta()
   {

      return (int)(3.0 * m_dItemHeight);

   }


   bool tree::selection_add(::item * pitem, ::collection::index i)
   {

      auto ptreedataitem = find_data_tree_item(pitem, &i);

      if (!ptreedataitem)
      {

         return false;

      }

      return selection_add(ptreedataitem);

   }


   ::collection::count tree::selection_add(::pointer_array < ::data::tree_item_base > & itemptra)
   {

      ::collection::count count = 0;

      for (int i = 0; i < itemptra.get_count(); i++)
      {

         if (selection_add(itemptra[i]))
         {

            count++;

         }

      }

      return count;

   }


   bool tree::selection_add(::data::tree_item_base * pitem)
   {
      if (!contains(pitem))
      {

         return false;

      }

      return m_ptreeitemptraSelected->add_unique(pitem);

   }


   bool tree::selection_set(::item * pitem, bool bIfNotInSelection, bool bIfParentInSelection)
   {

      return selection_set(0, pitem, bIfNotInSelection, bIfParentInSelection);

   }


   bool tree::selection_set(::collection::index i, ::item * pitem, bool bIfNotInSelection, bool bIfParentInSelection)
   {

      auto ptreedataitem = find_data_tree_item(pitem, &i);

      if (!ptreedataitem)
      {

         return false;

      }

      return selection_set(ptreedataitem, bIfNotInSelection, bIfParentInSelection);

   }


   ::collection::count tree::selection_set(::pointer_array < ::data::tree_item_base > & itemptra)
   {

      ::collection::count count = 0;

      for (int i = 0; i < itemptra.get_count(); i++)
      {

         if (contains(itemptra[i]) && m_ptreeitemptraSelected->add_unique(itemptra[i]))
         {

            count++;

         }

      }

      return count;

   }


   bool tree::selection_set(::data::tree_item_base * pitem, bool bIfNotInSelection, bool bIfParentInSelection)
   {

      if (!contains(pitem))
      {

         return false;

      }

      if (bIfNotInSelection && is_selected(pitem))
      {

         return true;

      }

      if (bIfParentInSelection && !is_selected(pitem->_get_parent()))
      {

         return true;

      }

      bool bContains = m_ptreeitemptraSelected->contains(pitem);

      m_ptreeitemptraSelected->erase_all();

      m_ptreeitemptraSelected->add(pitem);

      information() << "m_ptreeitemptraSelected add item";

      return bContains;

   }


   bool tree::selection_erase(::item * pitem, ::collection::index i)
   {

      auto ptreedataitem = find_data_tree_item(pitem, &i);

      if (!ptreedataitem)
      {

         return false;

      }

      return selection_erase(ptreedataitem);

   }


   ::collection::count tree::selection_erase(::pointer_array < ::data::tree_item_base > & itemptra)
   {

      ::collection::count count = 0;

      for (int i = 0; i < itemptra.get_count(); i++)
      {

         if (m_ptreeitemptraSelected->erase(itemptra[i]))
         {

            count++;

         }

      }

      return count;

   }


   bool tree::selection_erase(::data::tree_item_base * pitem)
   {

      return m_ptreeitemptraSelected->erase(pitem) >= 0;

   }


   ::collection::count tree::clear_selection()
   {

      return m_ptreeitemptraSelected->erase_all();

   }


   bool tree::hover(::item * pitem, ::collection::index i)
   {

      auto ptreedataitem = find_data_tree_item(pitem, &i);

      return hover(ptreedataitem);

   }


   bool tree::hover(::data::tree_item_base * pitem)
   {

      if (pitem == nullptr)
      {

         m_ptreeitemHover = nullptr;

         return true;

      }

      if (!contains(pitem))
      {

         return false;

      }

      return m_ptreeitemHover == pitem;

   }


   bool tree::is_selected(const ::data::tree_item_base * pitem) const
   {

      return m_ptreeitemptraSelected->contains(pitem);

   }


   bool tree::is_selected(const ::item * pitem) const
   {

      if (!pitem)
      {

         return false;

      }

      for (int i = 0; i < m_ptreeitemptraSelected->get_count(); i++)
      {

         if (m_ptreeitemptraSelected->element_at(i)->_item() == pitem)
         {

            return true;

         }

      }

      return false;

   }


   bool tree::is_hover(const ::data::tree_item_base * pitem) const
   {

      return pitem && m_ptreeitemHover == pitem;

   }


   bool tree::is_hover(const ::item * pitem) const
   {

      if (!pitem || !m_ptreeitemHover)
      {

         return false;

      }

      if (m_ptreeitemHover->_item() != pitem)
      {

         return false;

      }

      return true;

   }


   bool tree::can_merge(const ::user::tree_data_base * ptree) const
   {

      if (!m_ptreedata)
      {

         return false;

      }

      return !m_ptreedata->_contains(ptree);

   }


   bool tree::merge(::user::tree_data_base * pdatatree, bool bBind)
   {

      if (pdatatree == nullptr)
      {

         return false;

      }

      if (!can_merge(pdatatree))
      {

         return false;

      }

      m_ptreedata->_insert_item(pdatatree);

      pdatatree->on_merge_user_tree(this);

      if (bBind)
      {

         m_treeaBound.add(pdatatree);

         pdatatree->m_usertreeaBound.add(this);

         pdatatree->on_bind_user_tree(this);

      }

      pdatatree->m_usertreea.add_unique(this);

      ::pointer<::user::impact>pimpact = this;

      if (pimpact.is_set())
      {

         pimpact->get_document()->add_data(pdatatree);

      }

      pdatatree->install_message_routing(this);

      return true;

   }


   ::pointer<::data::tree_item_base>tree::get_proper_item(::collection::index i, ::collection::index * piLevel)
   {

      if (!m_ptreedata)
      {

         return nullptr;

      }

      ::data::tree_item_base * pitem = m_ptreedata->_get_proper_item(i, piLevel);

      if (::is_set(pitem))
      {

         return pitem;

      }

      return nullptr;

   }


   ::pointer<::data::tree_item_base>tree::_get_proper_item(::collection::index i, ::collection::index * piLevel, ::collection::index * piCount)
   {

      if (!m_ptreedata)
      {

         return nullptr;

      }

      ::collection::index iCount = 0;

      ::pointer<::data::tree_item_base>pitem;

      pitem = m_ptreedata->__get_proper_item(i, piLevel, &iCount);

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


   ::collection::index tree::get_proper_item_index(::data::tree_item_base * pitemParam, ::collection::index * piLevel)
   {

      ::collection::index iCount = 0;

      ::collection::index iFound;

      iFound = m_ptreedata->_get_proper_item_index(pitemParam, piLevel, &iCount);

      if (iFound >= 0)
      {

         return iCount;

      }

      return -1;

   }


   ::collection::index tree::get_proper_item_count()
   {

      synchronous_lock synchronouslock(this->synchronization());

      if (!m_ptreedata)
      {

         return -1;

      }

      ::collection::index iCount = 0;

      iCount += m_ptreedata->get_proper_item_count();

      return iCount;

   }


   void tree::_001EnsureVisible(::data::tree_item_base * pitem)
   {

      if (pitem == nullptr)
      {

         return;

      }

      ::data::tree_item_base * pitemExpand = pitem;

      while (pitemExpand != nullptr)
      {

         pitemExpand->m_etreeitemstate |= ::data::e_tree_item_state_expanded;

         pitemExpand = pitemExpand->_get_parent();

      }

      ::collection::index iLevel = 0;

      ::collection::index iIndex = get_proper_item_index(pitem, &iLevel);

      auto pointOffset = get_context_offset();

      if (m_dItemHeight <= 0.)
      {

         m_dItemHeight = 18.0;

      }

      ::collection::index iMinVisibleIndex = (::collection::index)(pointOffset.y() / m_dItemHeight);

      ::collection::index iMaxVisibleIndex = (::collection::index)(iMinVisibleIndex + _001GetVisibleItemCount());

      if (iIndex < iMinVisibleIndex || iIndex > iMaxVisibleIndex)
      {

         ::collection::index iNewScrollIndex = iIndex;

         auto dy = maximum(iNewScrollIndex, 0) * m_dItemHeight;

         //queue_graphics_call([this, iy](::draw2d::graphics_pointer & pgraphics)
         //   {

               set_context_offset_y(dy);

      //});

         set_need_layout();

         set_need_redraw();

      }

   }


   void tree::handle(::topic * ptopic, ::handler_context * phandlercontext)
   {

      if (m_ptreedata)
      {

         m_ptreedata->handle(ptopic, phandlercontext);

      }

   }


   bool tree::keyboard_focus_is_focusable()
   {

      return true;

   }


   //void tree::on_context_offset(::draw2d::graphics_pointer & pgraphics)
   //{

   //}


} // namespace aura



