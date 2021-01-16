#include "framework.h"
#if !BROAD_PRECOMPILED_HEADER
#include "base/user/experience/_experience.h"
#endif
#include "acme/const/timer.h"


namespace experience
{


   control_box::control_box() :
      m_fontMarlett(e_create),
      m_brushButtonBack(e_create),
      m_brushButtonBackSel(e_create),
      m_brushButtonBackFocus(e_create),
      m_brushButtonBackDisabled(e_create),
      m_penButtonBack(e_create),
      m_penButtonBackSel(e_create),
      m_penButtonBackFocus(e_create),
      m_penButtonBackDisabled(e_create)
   {

      m_strInteractionTag = "control_box";

      set_control_box_button_id(button_close, "frame::ButtonClose");
      set_control_box_button_id(button_up, "frame::button_up");
      set_control_box_button_id(button_down, "frame::button_down");
      set_control_box_button_id(button_minimize, "frame::button_minimize");
      set_control_box_button_id(button_maximize, "frame::button_maximize");
      set_control_box_button_id(button_restore, "frame::button_restore");
      set_control_box_button_id(button_notify_icon, "frame::button_notify_icon");
      set_control_box_button_id(button_transparent_frame,"frame::button_transparent_frame");
      set_control_box_button_id(button_dock,"frame::button_dock");
      m_bDrag = false;
      m_iDefaultButtonMargin = 3;

      m_fontMarlett->create_pixel_font("Marlett", 16.0);

   }


   control_box::~control_box()
   {

   }


   void control_box::_001OnLButtonDown(::message::message * pmessage)
   {

      __pointer(::message::mouse) pmouse(pmessage);


      if (m_pframewindow != nullptr
            && m_pframewindow->m_pframe != nullptr
            && m_pframewindow->m_pframe->is_control_box_moveable())
      {

         m_bDrag = true;

         m_pointDrag = pmouse->m_point;

         _001ScreenToClient(&m_pointDrag);

         SetCapture();

         pmouse->m_bRet = true;

      }

   }


   void control_box::_001OnLButtonUp(::message::message * pmessage)
   {

      __pointer(::message::mouse) pmouse(pmessage);

      if (m_pframewindow != nullptr
            && m_pframewindow->m_pframe != nullptr
            && m_pframewindow->m_pframe->is_control_box_moveable())
      {

         ::point point = pmouse->m_point;

         m_pframewindow->_001ScreenToClient(point);

         drag(point);

         m_bDrag = false;

         ReleaseCapture();

         pmouse->m_bRet = true;

      }

   }


   void control_box::_001OnMouseMove(::message::message * pmessage)
   {

      __pointer(::message::mouse) pmouse(pmessage);

      if (m_pframewindow != nullptr
            && m_pframewindow->m_pframe != nullptr
            && m_pframewindow->m_pframe->is_control_box_moveable())
      {

         if (m_bDrag)
         {

            ::point point = pmouse->m_point;

            m_pframewindow->_001ScreenToClient(point);

            drag(point);

         }

         pmouse->m_bRet = true;

      }

   }


   void control_box::drag(const ::point & point)
   {

      //int x = point.x - m_pointDrag.x;

      //if (x < 0)
      //{

      //   x = 0;

      //}

      //::rect rectParent;

      //get_parent()->get_client_rect(rectParent);

      //::rect rectClient;

      //get_client_rect(rectClient);

      //::rect rectWindow;

      //get_window_rect(rectWindow);

      //get_parent()->_001ScreenToClient(rectWindow);

      //m_pframewindow->m_pframe->m_iControlBoxRight = rectParent.right - x - rectWindow.width();

      //m_pframewindow->m_pframe->get_control_box_rect()->move_left_to(x);

      //x = m_pframewindow->m_pframe->calc_control_box_left(true);

      //::point point(x, rectWindow.top);

      //::point pointScreen(point);

      //get_parent()->_001ClientToScreen(pointScreen);

      //m_pframewindow->m_pframe->m_iControlBoxRight = rectParent.right - point.x - rectWindow.width();

      //int iControlBoxRight = m_pframewindow->m_pframe->m_iControlBoxRight;

      //m_pframewindow->prop("control_box_right_to_right") = iControlBoxRight;

      //order(zorder_top);

      //move_to(point);

   }


   void control_box::_001OnShowWindow(::message::message * pmessage)
   {

      __pointer(::message::show_window) pshow(pmessage);

      m_bDrag = false;

      m_bShowAttempt = false;

      if (pshow->m_bShow)
      {

         m_millisShow.Now();

      }

   }


   void control_box::_001OnTimer(::timer * ptimer)
   {

      if (ptimer->m_uEvent == e_timer_check_hover)
      {

         if (get_top_level()->layout().is_moving())
         {

            //TRACE("experience control_box : top level is moving : ignoring e_message_timer");

            return;

         }
         else if (get_top_level()->layout().is_sizing())
         {

            //TRACE("experience control_box : top level is sizing : ignoring e_message_timer");

            return;

         }

         ::point pointCursor;

         auto psession = Session;

         psession->get_cursor_pos(pointCursor);

         if (is_window_visible())
         {

            if (m_bDrag)
            {

               m_millisShow.Now();

            }
            else
            {

               if (m_pframewindow != nullptr)
               {

                  if (m_pframewindow->layout().is_full_screen())
                  {

                     ::rect rectWindow;

                     get_window_rect(rectWindow);

                     if (rectWindow.contains(pointCursor))
                     {

                        m_millisShow.Now();

                     }
                     else
                     {

                        if(m_millisShow.elapsed() > 1000)
                        {

                           display(e_display_none);

                        }

                     }

                  }


               }

            }
         }
         else if (m_bShowAttempt)
         {
            //if ((m_millisShowTime.elapsed()) > 284)
            {
               if (m_pframewindow != nullptr)
               {

                  if (m_pframewindow->layout().is_full_screen())
                  {

                     ::rect rectWindow;

                     get_window_rect(rectWindow);

                     rectWindow.left = min(rectWindow.left, rectWindow.right);
                     rectWindow.bottom = min(rectWindow.top, rectWindow.bottom);


                     if (pointCursor.x >= rectWindow.left && pointCursor.y <= rectWindow.right && pointCursor.y == 0)
                     {

                        order(zorder_top);

                        display();

                     }

                     m_bShowAttempt = false;

                  }

               }

            }
         }
         else
         {

            if (m_pframewindow->layout().is_full_screen())
            {

               ::rect rectWindow;

               get_window_rect(rectWindow);

               rectWindow.left = min(rectWindow.left, rectWindow.right);
               rectWindow.bottom = min(rectWindow.top, rectWindow.bottom);

               ::point point;

               try
               {

                  point = psession->m_pointCursor;

               }
               catch (...)
               {

               }

               if (point.x >= rectWindow.left && point.x <= rectWindow.right && point.y == 0)
               {

                  m_bShowAttempt = true;

                  m_millisShow.Now();

               }

            }

         }

      }

   }


   void control_box::_001OnCreate(::message::message * pmessage)
   {

      pmessage->previous();

      if (pmessage->m_bRet)
      {

         return;

      }

      create_buttons();

   }


   void control_box::install_message_routing(::channel *pframewindow)
   {

      ::user::interaction::install_message_routing(pframewindow);

      MESSAGE_LINK(e_message_show_window, pframewindow, this, &control_box::_001OnShowWindow);
      MESSAGE_LINK(e_message_create, pframewindow, this, &control_box::_001OnCreate);
      MESSAGE_LINK(e_message_mouse_move, pframewindow, this, &control_box::_001OnMouseMove);
      MESSAGE_LINK(e_message_left_button_down, pframewindow, this, &control_box::_001OnLButtonDown);
      MESSAGE_LINK(e_message_left_button_up, pframewindow, this, &control_box::_001OnLButtonUp);
      MESSAGE_LINK(e_message_move, pframewindow, this, &control_box::_001OnMove);
      MESSAGE_LINK(e_message_size, pframewindow, this, &control_box::_001OnSize);

   }


   bool control_box::should_show_button(e_button ebutton)
   {

      if (!has_button(ebutton))
      {

         return false;

      }

      if (ebutton == button_close)
      {

         return true;

      }
      else if (ebutton == button_up)
      {

         return m_pframewindow->updown_get_up_enable();

      }
      else if (ebutton == button_down)
      {

         return m_pframewindow->updown_get_down_enable();

      }
      else if (ebutton == button_maximize)
      {

         if (m_pframewindow->updown_get_up_enable())
         {

            return false;

         }

         return !m_pframewindow->layout().is_zoomed();

      }
      else if (ebutton == button_restore)
      {

         if (m_pframewindow->updown_get_up_enable())
         {

            return false;

         }

         return true;

         //auto edisplay = m_pframewindow->layout().sketch().display();

         //return is_iconic(edisplay)
            // || is_full_screen(edisplay)
            //|| is_zoomed(edisplay)
            //|| is_docking_appearance(edisplay);

      }
      else if (ebutton == button_minimize)
      {

         if (m_pframewindow->updown_get_up_enable())
         {

            return false;

         }

         return true;

      }
      else if (ebutton == button_notify_icon)
      {

         if (m_pframewindow->updown_get_up_enable())
         {

            return false;

         }

         return m_pframewindow->window_is_notify_icon_enabled();

      }
      else if (ebutton == button_transparent_frame)
      {

         if (m_pframewindow->updown_get_up_enable())
         {

            return false;

         }

         return true;

      }
      else if (ebutton == button_dock)
      {

         if (m_pframewindow->updown_get_up_enable())
         {

            return false;

         }

         return true;

      }


      return false;

   }


   void control_box::_layout_button(e_button ebutton, ::rect& rect)
   {

      auto pbutton = get_box_button(ebutton);

      if(should_show_button(ebutton))
      {

         auto sizeButton = get_button_size(ebutton);

         auto rectMargin = get_button_margin(ebutton);

         rect.right = rect.left - rectMargin.right;
         rect.left = rect.right - sizeButton.cx;

         if (pbutton)
         {

            rect.top = rectMargin.top;
            rect.bottom = sizeButton.cy + rect.top;

            pbutton->order(zorder_top);
            pbutton->place(rect);
            pbutton->display();
            pbutton->UpdateWndRgn();

         }

         rect.left -= rectMargin.left;

      }
      else
      {

         if (pbutton)
         {

            pbutton->hide();

         }

      }

   }


   void control_box::on_layout(::draw2d::graphics_pointer & pgraphics)
   {

      //auto edisplay = m_pframewindow->layout().sketch().display();

      ::rect rectWindow;

      m_pframewindow->get_window_rect(rectWindow);

      ::rect rectParent(rectWindow);

      m_pframewindow->_001ScreenToClient(rectParent);

      ::rect rect;

      get_window_rect(rect);

      m_pframewindow->_001ScreenToClient(rect);

      m_pframewindow->m_pframe->m_iControlBoxRight = rectParent.right - rect.right;

      *m_pframewindow->m_pframe->get_control_box_rect() = rect;

      reset_layout(pgraphics);

      ::rect rectClient;

      get_client_rect(rectClient);

      int iWidth = rectClient.width();


      rect.left = iWidth;

      _layout_button(button_close, rect);

      //if(!has_button(button_close))
      //{

      //   get_box_button(button_close)->display(e_display_none);

      //}
      //else
      //{

      //   rect.top = rectMargin.top;
      //   rect.bottom = sizeButton.cy + rect.top;
      //   rect.right = iWidth - rectMargin.right;
      //   rect.left = rect.right - sizeButton.cx;
      //   auto pbutton = get_box_button(button_close);
      //   pbutton->order(zorder_top);
      //   pbutton->place(rect);
      //   pbutton->display();
      //   pbutton->UpdateWndRgn();
      //   rect.left -= rectMargin.left;

      //}

      //auto pframewindow = m_pframewindow;

      _layout_button(button_up, rect);

//            if(!has_button(button_up))
//            {
//
//               get_box_button(button_up)->display(e_display_none);
//
//            }
//            else if(pframewindow->updown_get_up_enable())
//            {
//
//               sizeButton = get_button_size(button_up);
//
//               rectMargin = get_button_margin(button_up);
//
//               rect.top = rectMargin.top;
//               rect.bottom = sizeButton.cy + rect.top;
//               rect.right = rect.left - rectMargin.right;
//               rect.left = rect.right - sizeButton.cx;
//
//               auto pbutton = get_box_button(button_up);
//
//               if (pbutton)
//               {
//
//                  pbutton->place(rect);
//                  pbutton->display();
//                  pbutton->UpdateWndRgn();
//
//               }
//
//               rect.left -= rectMargin.left;
//
//            }
//            else
//            {
//
//               get_box_button(button_up)->display(e_display_none);
//
//            }
//

      _layout_button(button_down, rect);

//            if(!has_button(button_down))
//            {
//
//               get_box_button(button_down)->display(e_display_none);
//
//            }
//            else if(pframewindow->updown_get_down_enable())
//            {
//
//               sizeButton = get_button_size(button_down);
//               rectMargin = get_button_margin(button_down);
//
//               rect.top = rectMargin.top;
//               rect.bottom = sizeButton.cy + rect.top;
//               rect.right = rect.left - rectMargin.right;
//               rect.left = rect.right - sizeButton.cx;
//
//               get_box_button(button_down)->place(rect);
//               get_box_button(button_down)->display();
//
////               get_box_button(button_down)->::user::interaction::set_window_pos(
////               zorder_top,
////               rect.left,
////               rect.top,
////               rect.width(),
////               rect.height(),
////               SWP_SHOWWINDOW);
//
//               get_box_button(button_down)->UpdateWndRgn();
//               rect.left -= rectMargin.left;
//            }
//            else
//            {
//               get_box_button(button_down)->display(e_display_none);
//            }

      _layout_button(button_maximize, rect);

//            if(!has_button(button_maximize))
//            {
//               get_box_button(button_maximize)->display(e_display_none);
//            }
//            else if (is_zoomed(edisplay))
//            {
//               get_box_button(button_maximize)->display(e_display_none);
//            }
//            else
//            {
//               sizeButton = get_button_size(button_maximize);
//               rectMargin = get_button_margin(button_maximize);
//
//               rect.top = rectMargin.top;
//               rect.bottom = sizeButton.cy + rect.top;
//               rect.right = rect.left - rectMargin.right;
//               rect.left = rect.right - sizeButton.cx;
//
////               get_box_button(button_maximize)->::user::interaction::set_window_pos(
////               zorder_top,
////               rect.left,
////               rect.top,
////               rect.width(),
////               rect.height(),
////               SWP_SHOWWINDOW);
//
//               auto pbutton = get_box_button(button_maximize);
//
//               if (pbutton)
//               {
//
//                  pbutton->place(rect);
//                  pbutton->display();
//                  pbutton->UpdateWndRgn();
//
//               }
//
//               rect.left -= rectMargin.left;
//            }

      _layout_button(button_restore, rect);

//            auto pbutton = get_box_button(button_restore);
//
//            if(!has_button(button_restore))
//            {
//
//               if (pbutton)
//               {
//
//                  pbutton->hide();
//
//               }
//
//            }
//            else if (is_iconic(edisplay)
//                     || is_full_screen(edisplay)
//                     || is_zoomed(edisplay)
//                     || is_docking_appearance(edisplay))
//            {
//               sizeButton = get_button_size(button_restore);
//               rectMargin = get_button_margin(button_restore);
//
//               rect.top = rectMargin.top;
//               rect.bottom = sizeButton.cy + rect.top;
//               rect.right = rect.left - rectMargin.right;
//               rect.left = rect.right - sizeButton.cx;
//
////               get_box_button(button_restore)->::user::interaction::set_window_pos(
////               zorder_top,
////               rect.left,
////               rect.top,
////               rect.width(),
////               rect.height(),
////               SWP_SHOWWINDOW);
//
//               if (pbutton)
//               {
//
//                  pbutton->place(rect);
//                  pbutton->display();
//                  pbutton->UpdateWndRgn();
//
//               }
//
//               rect.left -= rectMargin.left;
//            }
//            else
//            {
//
//               if (pbutton)
//               {
//
//                  pbutton->hide();
//
//               }
//
//            }

      _layout_button(button_minimize, rect);

      //pbutton = get_box_button(button_minimize);

      //if (is_iconic(edisplay) || !has_button(button_minimize))
      //{
      //
      //   pbutton->hide();

      //}
      //else
      //{
      //   sizeButton = get_button_size(button_minimize);
      //   rectMargin = get_button_margin(button_minimize);

      //   rect.top = rectMargin.top;
      //   rect.bottom = sizeButton.cy + rect.top;
      //   rect.right = rect.left - rectMargin.right;
      //   rect.left = rect.right - sizeButton.cx;

      //   //get_box_button(button_minimize)->::user::interaction::set_window_pos(zorder_top, rect, SWP_SHOWWINDOW);

      //   if (pbutton)
      //   {

      //      pbutton->place(rect);
      //      pbutton->display();
      //      pbutton->UpdateWndRgn();

      //   }

      //   rect.left -= rectMargin.left;
      //}

      _layout_button(button_notify_icon, rect);

      //if(!has_button(button_notify_icon))
      //{
      //   get_box_button(button_notify_icon)->display(e_display_none);
      //}
      //else if(m_pframewindow->window_is_notify_icon_enabled())
      //{
      //   sizeButton = get_button_size(button_notify_icon);
      //   rectMargin = get_button_margin(button_notify_icon);

      //   rect.top = rectMargin.top;
      //   rect.bottom = sizeButton.cy + rect.top;
      //   rect.right = rect.left - rectMargin.right;
      //   rect.left = rect.right - sizeButton.cx;

      //   //get_box_button(button_notify_icon)->::user::interaction::set_window_pos(zorder_top, rect, SWP_SHOWWINDOW);
      //   get_box_button(button_notify_icon)->place(rect);
      //   get_box_button(button_notify_icon)->display();

      //   get_box_button(button_notify_icon)->UpdateWndRgn();
      //   rect.left -= rectMargin.left;
      //}
      //else
      //{
      //   get_box_button(button_notify_icon)->display(e_display_none);
      //}

      _layout_button(button_transparent_frame, rect);

      //if(!has_button(button_transparent_frame))
      //{
      //   get_box_button(button_transparent_frame)->display(e_display_none);
      //}
      //else
      //{
      //   sizeButton = get_button_size(button_transparent_frame);
      //   rectMargin = get_button_margin(button_transparent_frame);

      //   rect.top = rectMargin.top;
      //   rect.bottom = sizeButton.cy + rect.top;
      //   rect.right = rect.left - rectMargin.right;
      //   rect.left = rect.right - sizeButton.cx;

      //   //get_box_button(button_transparent_frame)->::user::interaction::set_window_pos(zorder_top, rect,SWP_SHOWWINDOW);

      //   auto pbutton = get_box_button(button_transparent_frame);

      _layout_button(button_dock, rect);

      //   if (pbutton)
      //   {
      //
      //      pbutton->place(rect);
      //
      //      pbutton->display();

      //      pbutton->UpdateWndRgn();

      //   }

      //   rect.left -= rectMargin.left;
      //}

      //if(!has_button(button_dock))
      //{
      //   get_box_button(button_dock)->display(e_display_none);
      //}
      //else
      //{
      //   sizeButton = get_button_size(button_dock);
      //   rectMargin = get_button_margin(button_dock);

      //   rect.top = rectMargin.top;
      //   rect.bottom = sizeButton.cy + rect.top;
      //   rect.right = rect.left - rectMargin.right;
      //   rect.left = rect.right - sizeButton.cx;

      //   //get_box_button(button_dock)->::user::interaction::set_window_pos(zorder_top, rect, SWP_SHOWWINDOW);

      //   auto pbutton = get_box_button(button_dock);

      //   if (pbutton)
      //   {

      //      pbutton->place(rect);

      //      pbutton->display();

      //      pbutton->UpdateWndRgn();

      //   }

      //   rect.left -= rectMargin.left;

      //}

   }




   void control_box::update_control_box_button(e_button ebutton)
   {

      __pointer(button) pbutton;

      if (m_buttonmap.lookup(ebutton, pbutton))
      {

         string strCaption;

         get_control_box_button_caption(ebutton, strCaption);

         pbutton->set_stock_icon(get_control_box_button_stock_icon(ebutton));

         pbutton->set_parent(this);

         pbutton->set_window_text(strCaption);

         pbutton->m_pcontrolbox = this;

      }

   }


   bool control_box::create_button(e_button ebutton)
   {

      //auto pframewindow = m_pframewindow;

      __pointer(button) pbutton;

      if (!m_buttonmap.lookup(ebutton, pbutton))
      {

         pbutton = m_pframewindow->m_pframe->m_pexperience->m_plibrary->create_object(this, "button");

         m_buttonmap.set_at(ebutton, pbutton);

      }

      pbutton->m_ebutton = ebutton;

      string strCaption;

      get_control_box_button_caption(ebutton, strCaption);

      id id = get_control_box_button_id(ebutton);

      if (m_buttonmap.lookup(ebutton, pbutton))
      {

         if (!pbutton->is_window() && !pbutton->create_window(this, id))
         {

            return false;

         }

         string strTag = get_control_box_button_tag(ebutton);

         pbutton->m_strInteractionTag = strTag;

         update_control_box_button(ebutton);

      }
      else
      {

         return false;

      }

      return true;

   }


   void control_box::update_control_box_buttons()
   {

      for (auto & ebutton : m_buttonmap.keys())
      {

         update_control_box_button(ebutton);

      }

   }



   bool control_box::create_buttons()
   {

      create_button(button_close);
      create_button(button_up);
      create_button(button_down);
      create_button(button_minimize);
      create_button(button_maximize);
      create_button(button_restore);
      create_button(button_notify_icon);
      create_button(button_transparent_frame);
      create_button(button_dock);

      return true;

   }


   bool control_box::get_control_box_button_caption(e_button ebutton, string &strCaption)
   {
      bool bOk = true;
      switch (ebutton)
      {
      case button_close:
         strCaption = (char)114;
         break;
      case button_up:
         strCaption = (char)53;
         break;
      case button_down:
         strCaption = (char)54;
         break;
      case button_minimize:
         strCaption = (char)48;
         break;
      case button_maximize:
         strCaption = (char)49;
         break;
      case button_restore:
         strCaption = (char)50;
         break;
      case button_notify_icon:
         strCaption = (char)0x69;
         break;
      case button_transparent_frame:
         strCaption = (char)' ';
         break;
      case button_dock:
         strCaption = (char)0x6E;
         break;

      default:
         bOk = false;
      }
      return bOk;

   }


   e_stock_icon control_box::get_control_box_button_stock_icon(e_button ebutton)
   {

      return (e_stock_icon)((int) ebutton - (int)button_begin + (int) stock_icon_control_box_begin);

   }


   void control_box::set_control_box_button_id(e_button ebutton, id id)
   {

      m_mapButtonId[ebutton] = id;

      m_mapIdButton[id] = ebutton;

   }


   id control_box::get_control_box_button_id(e_button ebutton)
   {

      return m_mapButtonId[ebutton];

   }


   string control_box::get_control_box_button_tag(e_button ebutton)
   {

      switch(ebutton)
      {
         case button_close: // stock_icon_close
            return "button_close";
         case button_up: // stock_icon_level_up
            return "button_up";
         case button_down: // stock_icon_level_down
            return "button_down";
         case button_minimize: // stock_icon_iconify
            return "button_minimize";
         case button_restore: // stock_icon_restore
            return "button_restore";
         case button_maximize: // stock_icon_maximize
            return "button_maximize";
         case button_notify_icon: // stock_icon_notify
            return "button_notify_icon";
         case button_transparent_frame: // stock_icon_transparent_frame
            return "button_transparent_frame";
         case button_dock: // stock_icon_dock
            return "button_dock";
         default:
            break;
      }

      return "(unknown)";

   }


   e_button control_box::get_control_box_button_type(id id)
   {

      return m_mapIdButton[id];

   }


   void control_box::hide_button(e_button ebutton, bool bHide)
   {

      m_buttonmapPresent[ebutton] = !bHide;

   }


   bool control_box::has_button(e_button ebutton)
   {

      bool bPresent;

      if (m_pframewindow->m_ebuttonaHide.contains(ebutton))
      {

         return false;

      }
      else if (m_buttonmapPresent.lookup(ebutton, bPresent))
      {

         return bPresent;

      }
      else
      {

         m_buttonmapPresent[ebutton] = true;

         return true;

      }

   }


   void control_box::reset_layout(::draw2d::graphics_pointer & pgraphics)
   {

      int iDefaultButtonSize = calc_button_size(pgraphics);

      m_sizeButtonDefault = ::size(iDefaultButtonSize,iDefaultButtonSize);

      int iControlBoxRight = m_pframewindow->find_i32("control_box_right_to_right");

      m_pframewindow->m_pframe->m_iControlBoxRight = iControlBoxRight;

   }


   size control_box::get_button_size(e_button ebutton)
   {

      return m_sizeButtonDefault;

   }


   rect control_box::get_button_margin(e_button ebutton)
   {

      ::rect rectMargin;

      rectMargin.left = 0;
      rectMargin.top = m_iDefaultButtonMargin;
      rectMargin.right = m_iDefaultButtonMargin;
      rectMargin.bottom = m_iDefaultButtonMargin;

      return rectMargin;

   }


   i32 control_box::calc_button_size(::draw2d::graphics_pointer & pgraphics)
   {

      auto dFontHeight = m_fontMarlett->get_height(pgraphics);

      i32 iButtonSize = (::i32) (dFontHeight + m_iDefaultButtonMargin * 3);

      return iButtonSize;

   }


   i32 control_box::calc_control_box_height()
   {

      int iHeight = 0;

      auto point = m_buttonmap.get_start();

      for(; point != nullptr; point = m_buttonmap.get_next(point))
      {

         iHeight = max(iHeight,get_button_size(point->element1()).cy + get_button_margin(point->element1()).top + get_button_margin(point->element1()).bottom);

      }

      return iHeight;

   }


   i32 control_box::calc_control_box_normal_width()
   {

      int iWidth;

      iWidth = (m_sizeButtonDefault.cx + m_iDefaultButtonMargin) * 8;

      return iWidth;

   }


   i32 control_box::calc_control_box_zoomed_width()
   {

      int iWidth;

      iWidth = (m_sizeButtonDefault.cx + m_iDefaultButtonMargin) * 8;

      return iWidth;

   }


   i32 control_box::calc_control_box_full_screen_width()
   {

      int iWidth;

      iWidth = (m_sizeButtonDefault.cx + m_iDefaultButtonMargin) * 13;

      return iWidth;

   }


   //i32 control_box::get_button_margin()
   //{

   //   return m_iDefaultButtonSize;

   //}


   __pointer(button) control_box::get_button(e_button ebutton)
   {

      __pointer(button) pbutton;

      m_buttonmap.lookup(ebutton, pbutton);

      return pbutton;

   }


   __pointer(::experience::button) control_box::get_box_button(e_button ebutton)
   {

      return get_button(ebutton);

   }


   void control_box::set_button_color_system_default_001()
   {

      m_brushButtonBack->create_solid(ARGB(0, 0, 0, 0));
      m_brushButtonBackSel->create_solid(ARGB(255, 150, 220, 145));
      m_brushButtonBackFocus->create_solid(ARGB(255, 150, 220, 145));
      m_brushButtonBackDisabled->create_solid(ARGB(255, 180, 180, 175));

      m_penButtonBack->create_solid(2, ARGB(255, 255, 255, 255));
      m_penButtonBackSel->create_solid(2, ARGB(255, 255, 255, 255));
      m_penButtonBackFocus->create_solid(2, ARGB(255, 255, 255, 255));
      m_penButtonBackDisabled->create_solid(2, ARGB(255, 220, 220, 215));

      m_colorButtonFore = ARGB(255, 255, 255, 255);
      m_colorButtonForeSel = ARGB(255, 255, 255, 255);
      m_colorButtonForeFocus = ARGB(255, 255, 255, 255);
      m_colorButtonForeDisabled = ARGB(255, 220, 220, 215);

   }


   void control_box::_001OnMove(::message::message * pmessage)
   {

      ::rect rectWindow;

      m_pframewindow->get_window_rect(rectWindow);

      ::rect rect;

      get_window_rect(rect);

      m_pframewindow->_001ScreenToClient(rect);

      m_pframewindow->m_pframe->m_iControlBoxRight = rectWindow.width() - rect.right;

      m_pframewindow->m_pframe->m_bControlBoxAlignRight = rect.center().x > (rectWindow.width() / 2);

      if (rect != *m_pframewindow->m_pframe->get_control_box_rect())
      {

         *m_pframewindow->m_pframe->get_control_box_rect() = rect;

         m_pframewindow->m_millisLastVisualChange.Now();

         //auto pframe = m_pframewindow;

         //if (::is_set(pframe))
         //{

         //   pframe->defer_save_window_placement();

         //}

      }

   }


   void control_box::_001OnSize(::message::message * pmessage)
   {

      ::rect rectClient;

      get_client_rect(rectClient);

      output_debug_string("rectClient");

   }


   bool control_box::get_font(::draw2d::font_pointer & font)
   {

      font = m_fontMarlett;

      return true;

   }


   void control_box::_001OnClip(::draw2d::graphics_pointer & pgraphics)
   {
      
#ifdef MACOS
      
      // clip
      //return;
      
#endif

      try
      {

         ::rect rectClip;

         ::aura::draw_context * pdrawcontext = pgraphics->::aura::simple_chain < ::aura::draw_context >::get_last();

         ::rect rectClient;

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

            ::rect rectFocus;

            while (pinteraction != nullptr)
            {

               pinteraction->get_window_rect(rectFocus);

               _001ScreenToClient(rectFocus);

               m_pshapeaClip->add_item(__new(rect_shape(rectFocus)));

               m_pshapeaClip->add_item(__new(intersect_clip_shape));

               pinteraction = pinteraction->get_parent();
               
            }

         }
         
         pgraphics->reset_clip();

         pgraphics->add_shapes(*m_pshapeaClip);

      }
      catch (...)
      {

         __throw(::exception::exception("no more a u"));

      }

   }


} // namespace experience



