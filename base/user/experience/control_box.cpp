#include "framework.h"
#include "control_box.h"
#include "frame_window.h"
#include "frame.h"
#include "button.h"
#include "experience.h"
#include "acme/constant/message.h"
#include "acme/constant/timer.h"
#include "acme/platform/system.h"
#include "acme/platform/timer.h"
#include "acme/prototype/geometry2d/_text_stream.h"
#include "acme/windowing/windowing.h"
#include "aura/graphics/draw2d/brush.h"
#include "aura/graphics/draw2d/pen.h"
#include "aura/graphics/write_text/font.h"
#include "aura/message/user.h"
#include "base/platform/session.h"
#include "aura/graphics/draw2d/graphics.h"


namespace experience
{


   control_box::control_box()
   {

      m_bVisibleIfWindowActive = true;

      m_strInteractionTag = "control_box";

      set_control_box_button_id(e_button_close, "frame::ButtonClose");
      set_control_box_button_id(e_button_up, "frame::e_button_up");
      set_control_box_button_id(e_button_down, "frame::e_button_down");
      set_control_box_button_id(e_button_minimize, "frame::e_button_minimize");
      set_control_box_button_id(e_button_maximize, "frame::e_button_maximize");
      set_control_box_button_id(e_button_restore, "frame::e_button_restore");
      set_control_box_button_id(e_button_notify_icon, "frame::e_button_notify_icon");
      set_control_box_button_id(e_button_transparent_frame, "frame::e_button_transparent_frame");
      set_control_box_button_id(e_button_dock, "frame::e_button_dock");
      m_bDrag = false;
      m_iDefaultButtonMargin = 3;

   }


   control_box::~control_box()
   {

   }


   void control_box::on_message_left_button_down(::message::message * pmessage)
   {

      auto pmouse = pmessage->m_union.m_pmouse;

      if (m_pframewindow != nullptr
          && m_pframewindow->m_pframe != nullptr
          && m_pframewindow->m_pframe->is_control_box_moveable())
      {

         m_bDrag = true;

         m_pointDrag = pmouse->m_pointHost;

         host_to_client()(m_pointDrag);

         set_mouse_capture();

         pmouse->m_bRet = true;

      }

   }


   void control_box::on_message_left_button_up(::message::message * pmessage)
   {

      auto pmouse = pmessage->m_union.m_pmouse;

      if (m_pframewindow != nullptr
          && m_pframewindow->m_pframe != nullptr
          && m_pframewindow->m_pframe->is_control_box_moveable())
      {

         ::int_point point = pmouse->m_pointAbsolute;

         m_pframewindow->screen_to_client()(point);

         drag(point);

         m_bDrag = false;

         defer_release_mouse_capture();

         pmouse->m_bRet = true;

      }

   }


   void control_box::on_message_mouse_move(::message::message * pmessage)
   {

      auto pmouse = pmessage->m_union.m_pmouse;

      auto_hide_on_message_mouse_move(pmessage);

      if (m_pframewindow != nullptr
          && m_pframewindow->m_pframe != nullptr
          && m_pframewindow->m_pframe->is_control_box_moveable())
      {

         if (m_bDrag)
         {

            ::int_point point = pmouse->m_pointHost;

            m_pframewindow->host_to_client()(point);

            drag(point);

         }

         pmouse->m_bRet = true;

      }

   }


   void control_box::on_message_mouse_leave(::message::message * pmessage)
   {

      auto_hide_on_message_mouse_leave(pmessage);

   }


   void control_box::drag(const ::int_point & point)
   {

      //int x = point.x() - m_pointDrag.x();

      //if (x < 0)
      //{

      //   x = 0;

      //}

      //::int_rectangle rectangleParent;

      //get_parent()->rectangle(rectangleParent);

      //::int_rectangle rectangleX;

      //this->rectangle(rectangleX);

      //::int_rectangle rectangleWindow;

      //window_rectangle(rectangleWindow);

      //get_parent()->screen_to_client(rectangleWindow);

      //m_pframewindow->m_pframe->m_iControlBoxRight = rectangleParent.right() - x - rectangleWindow.width();

      //m_pframewindow->m_pframe->get_control_box_rect()->move_left_to(x);

      //x = m_pframewindow->m_pframe->calc_control_box_left(true);

      //::int_point point(x, rectangleWindow.top());

      //::int_point pointScreen(point);

      //get_parent()->client_to_screen(pointScreen);

      //m_pframewindow->m_pframe->m_iControlBoxRight = rectangleParent.right() - point.x() - rectangleWindow.width();

      //int iControlBoxRight = m_pframewindow->m_pframe->m_iControlBoxRight;

      //m_pframewindow->prop("control_box_right_to_right") = iControlBoxRight;

      //order(e_zorder_top);

      //move_to(point);

   }


   void control_box::on_message_show_window(::message::message * pmessage)
   {

      ::pointer<::message::show_window> pshow(pmessage);

      m_bDrag = false;

      m_bShowAttempt = false;

      if (pshow->m_bShow)
      {

         m_timeShow.Now();

      } else
      {

         informationf(".");

      }

   }


   void control_box::on_timer(::timer * ptimer)
   {

      ::user::auto_hide::on_timer(ptimer);

      if (ptimer->m_uTimer == e_timer_check_hover)
      {

         if (top_level()->layout().is_moving())
         {

            //informationf("experience control_box : top level is moving : ignoring e_message_timer");

            return;

         } else if (top_level()->layout().is_sizing())
         {

            //informationf("experience control_box : top level is sizing : ignoring e_message_timer");

            return;

         }

         ::int_point pointCursorHost;

         pointCursorHost = host_mouse_cursor_position();

         if (is_window_visible())
         {

            if (m_bDrag)
            {

               m_timeShow.Now();

            } else
            {

               if (m_pframewindow != nullptr)
               {

                  if (m_pframewindow->layout().is_full_screen())
                  {

                     auto rectangleHost = host_rectangle();

                     if (rectangleHost.contains(pointCursorHost))
                     {

                        m_timeShow.Now();

                     }
                     else
                     {

                        if (m_timeShow.elapsed() > 1_s)
                        {

                           display(e_display_none);

                        }

                     }

                  }

               }

            }

         } else if (m_bShowAttempt)
         {
            //if ((m_timeShowTime.elapsed()) > 284)
            {
               if (m_pframewindow != nullptr)
               {

                  if (m_pframewindow->layout().is_full_screen())
                  {

                     auto rectangleHost = host_rectangle();

                     if (pointCursorHost.x() >= rectangleHost.left()
                     && pointCursorHost.x() <= rectangleHost.right() &&
                        pointCursorHost.y() == 0)
                     {

                        order(e_zorder_top);

                        display();

                     }

                     m_bShowAttempt = false;

                  }

               }

            }
         } else
         {

            if (m_pframewindow->layout().is_full_screen())
            {

               auto rectangleHost = host_rectangle();

               if (pointCursorHost.x() >= rectangleHost.left()
                   && pointCursorHost.x() <= rectangleHost.right() &&
                   pointCursorHost.y() == 0)
               {

                  m_bShowAttempt = true;

                  m_timeShow.Now();

               }

            }

         }

      }

   }


   void control_box::on_message_create(::message::message * pmessage)
   {

      auto_hide_on_message_create(pmessage);

      __øconstruct(m_pbrushButtonBack);
      __øconstruct(m_pbrushButtonBackSel);
      __øconstruct(m_pbrushButtonBackFocus);
      __øconstruct(m_pbrushButtonBackDisabled);
      __øconstruct(m_ppenButtonBack);
      __øconstruct(m_ppenButtonBackSel);
      __øconstruct(m_ppenButtonBackFocus);
      __øconstruct(m_ppenButtonBackDisabled);


      pmessage->previous();

      if (pmessage->m_bRet)
      {

         return;

      }

      if (!m_pfontMarlett)
      {

         __øconstruct(m_pfontMarlett);

         m_pfontMarlett->create_font("Marlett", 16_px);

      }

      create_buttons();

   }


   void control_box::on_message_destroy(::message::message * pmessage)
   {

      m_pbrushButtonBack.release();
      m_pbrushButtonBackSel.release();
      m_pbrushButtonBackFocus.release();
      m_pbrushButtonBackDisabled.release();
      m_ppenButtonBack.release();
      m_ppenButtonBackSel.release();
      m_ppenButtonBackFocus.release();
      m_ppenButtonBackDisabled.release();

      m_pfontMarlett.release();

      destroy_buttons();

   }


   void control_box::install_message_routing(::channel * pframewindow)
   {

      ::user::interaction::install_message_routing(pframewindow);

      MESSAGE_LINK(e_message_show_window, pframewindow, this, &control_box::on_message_show_window);
      MESSAGE_LINK(e_message_create, pframewindow, this, &control_box::on_message_create);
      MESSAGE_LINK(e_message_destroy, pframewindow, this, &control_box::on_message_destroy);
      MESSAGE_LINK(e_message_mouse_move, pframewindow, this, &control_box::on_message_mouse_move);
      MESSAGE_LINK(e_message_mouse_leave, pframewindow, this, &control_box::on_message_mouse_leave);
      MESSAGE_LINK(e_message_left_button_down, pframewindow, this, &control_box::on_message_left_button_down);
      MESSAGE_LINK(e_message_left_button_up, pframewindow, this, &control_box::on_message_left_button_up);
      MESSAGE_LINK(e_message_reposition, pframewindow, this, &control_box::on_message_move);
      MESSAGE_LINK(e_message_size, pframewindow, this, &control_box::on_message_size);

   }


   bool control_box::should_show_button(enum_button ebutton) const
   {

      if (!has_button(ebutton))
      {

         return false;

      }

      if (::system()->is_sandboxed() && m_pframewindow->get_parent() == nullptr)
      {

         return false;

      }

      if (ebutton == e_button_close)
      {

         return true;

      } else if (ebutton == e_button_up)
      {

         return m_pframewindow->updown_get_up_enable();

      } else if (ebutton == e_button_down)
      {

         return m_pframewindow->updown_get_down_enable();

      } else if (ebutton == e_button_maximize)
      {

         if (m_pframewindow->updown_get_up_enable())
         {

            return false;

         }

         return !m_pframewindow->layout().is_zoomed(user::e_layout_lading);

      } else if (ebutton == e_button_restore)
      {

         if (m_pframewindow->updown_get_up_enable())
         {

            return false;

         }

         auto pacmewindowing = system()->acme_windowing();

         auto ewindowing = pacmewindowing->get_ewindowing();

         if(ewindowing == ::windowing::e_windowing_wayland)
         {

            return m_pframewindow->layout().is_zoomed(user::e_layout_lading);

         }

         return true;

         //auto edisplay = m_pframewindow->layout().sketch().display();

         //return is_iconic(edisplay)
         // || is_full_screen(edisplay)
         //|| is_zoomed(edisplay)
         //|| is_docking_appearance(edisplay);

      } else if (ebutton == e_button_minimize)
      {

         if (m_pframewindow->updown_get_up_enable())
         {

            return false;

         }

         return true;

      } else if (ebutton == e_button_notify_icon)
      {

         if (m_pframewindow->updown_get_up_enable())
         {

            return false;

         }

         return m_pframewindow->window_is_notify_icon_enabled();

      } else if (ebutton == e_button_transparent_frame)
      {

         if (m_pframewindow->updown_get_up_enable())
         {

            return false;

         }

         return true;

      } else if (ebutton == e_button_dock)
      {

         if(system()->acme_windowing()->get_ewindowing() == ::windowing::e_windowing_wayland)
         {

            return false;

         }
         if (!m_pframewindow->is_docking_enabled())
         {

            return false;

         }

         return true;

      }

      return false;

   }


   int control_box::auto_hide_threshold_height()
   {

      return this->height();

   }


   void control_box::_layout_button(enum_button ebutton, ::int_rectangle & rectangle)
   {

      auto pbutton = get_box_button(ebutton);

      if (should_show_button(ebutton))
      {

         auto sizeButton = get_button_size(ebutton);

         auto rectangleMargin = get_button_margin(ebutton);

         rectangle.right() = rectangle.left() - rectangleMargin.right();

         rectangle.left() = rectangle.right() - sizeButton.cx();

         if (rectangle.left() > 400)
         {

            informationf("rectangle.left() > 400");

         }

         if (pbutton)
         {

            rectangle.top() = rectangleMargin.top();

            rectangle.bottom() = rectangle.top() + sizeButton.cy();

            pbutton->order(e_zorder_top);

            //information() << "experience::control_box::_layout_button" << rectangle;

            pbutton->place(rectangle);

            pbutton->display();

            pbutton->UpdateWndRgn();

         }

         rectangle.left() -= rectangleMargin.left();

      }
      else
      {

         if (pbutton)
         {

            pbutton->hide();

         }

      }

   }


   void control_box::on_perform_top_down_layout(::draw2d::graphics_pointer & pgraphics)
   {

      auto_hide_calculate_control_visibility();
//      ::int_rectangle rectangleWindow = m_pframewindow->window_rectangle(::user::e_layout_lading);
//
//      ::int_rectangle rectangleParent(rectangleWindow);
//
//      m_pframewindow->screen_to_client(::user::e_layout_lading)(rectangleParent);
//
//      ::int_rectangle rectangle;
//
//      window_rectangle(rectangle, ::user::e_layout_lading);
//
//      m_pframewindow->screen_to_client(::user::e_layout_lading)(rectangle);

//      reset_layout(pgraphics);

      layout_control_box_buttons();

      order(e_zorder_top);

   }


   void control_box::layout_control_box_buttons()
   {

      auto rectangle = this->rectangle(::user::e_layout_lading);

//      int iWidth = rectangleX.width();
//
      rectangle.left() = rectangle.right();

      _layout_button(e_button_close, rectangle);

      _layout_button(e_button_up, rectangle);

      _layout_button(e_button_down, rectangle);

      _layout_button(e_button_maximize, rectangle);

      _layout_button(e_button_restore, rectangle);

      _layout_button(e_button_minimize, rectangle);

      _layout_button(e_button_notify_icon, rectangle);

      _layout_button(e_button_transparent_frame, rectangle);

      _layout_button(e_button_dock, rectangle);

   }


   control_box::item * control_box::get_item(enum_button ebutton, bool bCreate)
   {

      auto ppair = m_itemmap.plookup(ebutton);

      if (!ppair)
      {

         return nullptr;

      }

      if (bCreate)
      {

         __defer_construct_new(ppair->m_element2);

      }

      return ppair->m_element2;

   }


   bool control_box::create_button(enum_button ebutton)
   {

      auto pitem = get_item(ebutton, true);

      if (!pitem)
      {

         return false;

      }

      auto & pbutton = pitem->m_pbutton;

      auto pfactory = m_pframewindow->m_pframe->m_pexperience->m_pfactory;

      pfactory->__defer_construct(this, pbutton);

      pbutton->display(e_display_none);

      pbutton->m_pcontrolbox = this;

      pbutton->m_ebutton = ebutton;

      pbutton->add_handler(m_pframewindow);

      // if(ebutton == e_button_dock)
      // {

      //    pbutton->m_bSimpleUIDefaultMouseHandlingMouseCaptureOnLeftButtonDown = true;

      // }

      if (!pbutton->is_window())
      {

         pbutton->create_child(this);

      }

      return true;

   }


   bool control_box::update_control_box_button(enum_button ebutton)
   {

      auto pitem = get_item(ebutton);

      if (!pitem)
      {

         return false;

      }

      auto pbutton = pitem->m_pbutton;

      if (!pbutton)
      {

         return false;

      }

      pbutton->m_ebutton = ebutton;

      atom atom = get_control_box_button_id(ebutton);

      pbutton->id() = atom;

      string strTag = get_control_box_button_tag(ebutton);

      pbutton->m_strInteractionTag = strTag;

      string strCaption;

      get_control_box_button_caption(ebutton, strCaption);

      pbutton->set_stock_icon(get_control_box_button_stock_icon(ebutton));

      //pbutton->set_parent(this);

      pbutton->set_window_text(strCaption);

      pbutton->m_pcontrolbox = this;

      return true;

   }


   void control_box::update_control_box_buttons()
   {

      for (auto & ebutton: m_itemmap.items())
      {

         update_control_box_button(ebutton);

      }

   }


   bool control_box::create_buttons()
   {

      create_button(e_button_close);
      create_button(e_button_up);
      create_button(e_button_down);
      create_button(e_button_minimize);
      create_button(e_button_maximize);
      create_button(e_button_restore);
      create_button(e_button_notify_icon);
      create_button(e_button_transparent_frame);
      create_button(e_button_dock);

      return true;

   }


   void control_box::destroy_buttons()
   {

      for (auto & pcontrolboxitem : m_itemmap.payloads())
      {

         if (pcontrolboxitem)
         {

            if (pcontrolboxitem->m_pbutton)
            {

               pcontrolboxitem->m_pbutton.release();

            }

         }

         pcontrolboxitem.release();

      }

      m_itemmap.clear();

   }



   bool control_box::get_control_box_button_caption(enum_button ebutton, string & strCaption) const
   {

      bool bOk = true;

      switch (ebutton)
      {
         case e_button_close:
            strCaption = (char) 114;
            break;
         case e_button_up:
            strCaption = (char) 53;
            break;
         case e_button_down:
            strCaption = (char) 54;
            break;
         case e_button_minimize:
            strCaption = (char) 48;
            break;
         case e_button_maximize:
            strCaption = (char) 49;
            break;
         case e_button_restore:
            strCaption = (char) 50;
            break;
         case e_button_notify_icon:
            strCaption = (char) 0x69;
            break;
         case e_button_transparent_frame:
            strCaption = (char) ' ';
            break;
         case e_button_dock:
            strCaption = (char) 0x6E;
            break;

         default:
            bOk = false;
      }

      return bOk;

   }


   enum_stock_icon control_box::get_control_box_button_stock_icon(enum_button ebutton)
   {

      return (enum_stock_icon) ((int) ebutton - (int) e_button_begin + (int) e_stock_icon_control_box_begin);

   }


   void control_box::set_control_box_button_id(enum_button ebutton, atom atom)
   {

      auto & pitem = m_itemmap[ebutton];

      //auto estatus =

      __defer_construct_new(pitem);

      //if (!estatus)
      //{

      //   return estatus;

      //}

      pitem->id() = atom;

      m_idmap[atom] = ebutton;

      //return estatus;

   }


   atom control_box::get_control_box_button_id(enum_button ebutton) const
   {

      auto pitem = get_item(ebutton);

      if (!pitem)
      {

         return ::atom();

      }

      return m_itemmap[ebutton]->id();

   }


   string control_box::get_control_box_button_tag(enum_button ebutton) const
   {

      switch (ebutton)
      {
         case e_button_close: // stock_icon_close
            return "button_close";
         case e_button_up: // stock_icon_level_up
            return "button_up";
         case e_button_down: // stock_icon_level_down
            return "button_down";
         case e_button_minimize: // stock_icon_iconify
            return "button_minimize";
         case e_button_restore: // stock_icon_restore
            return "button_restore";
         case e_button_maximize: // stock_icon_maximize
            return "button_maximize";
         case e_button_notify_icon: // stock_icon_notify
            return "button_notify_icon";
         case e_button_transparent_frame: // stock_icon_transparent_frame
            return "button_transparent_frame";
         case e_button_dock: // stock_icon_dock
            return "button_dock";
         default:
            break;
      }

      return "(unknown)";

   }


   enum_button control_box::get_control_box_button_type(atom atom) const
   {

      return m_idmap[atom];

   }


   bool control_box::hide_button(enum_button ebutton, bool bHide)
   {

      auto pitem = get_item(ebutton);

      if (!pitem)
      {

         return false;

      }

      pitem->m_bPresent = !bHide;

      return true;

   }


   bool control_box::has_button(enum_button ebutton) const
   {

      if (m_pframewindow->m_ebuttonaHide.contains(ebutton))
      {

         return false;

      }

      auto pitem = get_item(ebutton);

      if (!pitem)
      {

         return false;

      }

      return pitem->m_bPresent;

   }


//   void control_box::reset_layout(::draw2d::graphics_pointer & pgraphics)
//   {
//
//      int iDefaultButtonSize = calculate_button_size(pgraphics);
//
//      m_sizeButtonDefault = ::int_size(iDefaultButtonSize, iDefaultButtonSize);
//
//   }


   int_size control_box::get_button_size(enum_button ebutton)
   {

      return m_sizeButtonDefault;

   }


   int_rectangle control_box::get_button_margin(enum_button ebutton)
   {

      ::int_rectangle rectangleMargin;

      rectangleMargin.left() = 0;
      rectangleMargin.top() = m_iDefaultButtonMargin;
      rectangleMargin.right() = m_iDefaultButtonMargin;
      rectangleMargin.bottom() = m_iDefaultButtonMargin;

      return rectangleMargin;

   }


   int control_box::calculate_button_size(::draw2d::graphics_pointer & pgraphics)
   {

      auto dFontHeight = m_pfontMarlett->get_height(pgraphics);

      int iButtonSize = (int) (dFontHeight + m_iDefaultButtonMargin * 3);

      m_sizeButtonDefault = ::int_size(iButtonSize, iButtonSize);

      return iButtonSize;

   }


   ::collection::count control_box::get_visible_control_box_button() const
   {

      ::collection::count cVisible = 0;

      for (auto & pair: m_itemmap)
      {

         auto & ebutton = pair.m_element1;

         if (should_show_button(ebutton))
         {

            cVisible++;

         }

      }

      return cVisible++;

   }


   int control_box::calculate_control_box_width(::draw2d::graphics_pointer & pgraphics)
   {

      m_iDefaultButtonSize = calculate_button_size(pgraphics);

      int iWidth = 0;

      for (auto & pitem: m_itemmap.payloads())
      {

         auto & pbutton = pitem->m_pbutton;

         if (pbutton)
         {

            iWidth += m_iDefaultButtonSize;

            iWidth += m_iDefaultButtonMargin;

         }

      }

      return iWidth;

   }


   ::pointer<button> control_box::get_button(enum_button ebutton)
   {

      auto pitem = get_item(ebutton);

      if (!pitem)
      {

         return nullptr;

      }

      return pitem->m_pbutton;

   }


   ::pointer<::experience::button> control_box::get_box_button(enum_button ebutton)
   {

      return get_button(ebutton);

   }


   void control_box::set_button_color_system_default_001()
   {

      m_pbrushButtonBack->create_solid(argb(0, 0, 0, 0));
      m_pbrushButtonBackSel->create_solid(argb(255, 150, 220, 145));
      m_pbrushButtonBackFocus->create_solid(argb(255, 150, 220, 145));
      m_pbrushButtonBackDisabled->create_solid(argb(255, 180, 180, 175));

      m_ppenButtonBack->create_solid(2, argb(255, 255, 255, 255));
      m_ppenButtonBackSel->create_solid(2, argb(255, 255, 255, 255));
      m_ppenButtonBackFocus->create_solid(2, argb(255, 255, 255, 255));
      m_ppenButtonBackDisabled->create_solid(2, argb(255, 220, 220, 215));

      m_colorButtonFore = argb(255, 255, 255, 255);
      m_colorButtonForeSel = argb(255, 255, 255, 255);
      m_colorButtonForeFocus = argb(255, 255, 255, 255);
      m_colorButtonForeDisabled = argb(255, 220, 220, 215);

   }


   void control_box::on_message_move(::message::message * pmessage)
   {

      ::int_rectangle rectangleWindow;

      m_pframewindow->window_rectangle(rectangleWindow);

      ::int_rectangle rectangle;

      window_rectangle(rectangle);

      m_pframewindow->screen_to_client()(rectangle);

      m_pframewindow->m_pframe->m_bControlBoxAlignRight = rectangle.center().x() > (rectangleWindow.width() / 2);

//      if (rectangle != *m_pframewindow->m_pframe->get_control_box_rect())
//      {
//
//         *m_pframewindow->m_pframe->get_control_box_rect() = rectangle;
//
//         m_pframewindow->m_timeLastVisualChange.Now();
//
//         //auto pframe = m_pframewindow;
//
//         //if (::is_set(pframe))
//         //{
//
//         //   pframe->defer_save_window_placement();
//
//         //}
//
//      }

   }


   void control_box::on_message_size(::message::message * pmessage)
   {

      //auto rectangleX = this->rectangle();

      informationf("rectangleX");

   }


   bool control_box::get_font(::write_text::font_pointer & font)
   {

      font = m_pfontMarlett;

      return true;

   }


   void control_box::_001OnClip(::draw2d::graphics_pointer & pgraphics)
   {

      //return ::user::box::_001OnClip(pgraphics);

//#ifdef MACOS
//
//      // clip
//      //return;
//
//#endif
//
//      try
//      {
//
//         ::int_rectangle rectangleClip;
//
//         ::aura::draw_context * pdrawcontext = pgraphics->::aura::simple_chain < ::aura::draw_context >::get_last();
//
//         ::int_rectangle rectangleX;
//
//         bool bFirst = true;
//
//         if (pdrawcontext != nullptr)
//         {
//
//            this->rectangle(rectangleX);
//
//            rectangleX.bottom()++;
//            rectangleX.right()++;
//
//            rectangleClip = rectangleX;
//
//            bFirst = false;
//
//         }
//
//         //auto pinterationdraw2d = get_draw2d();
//
//         if(!m_pshapeaClip)
//         {
//
//            __construct_new(m_pshapeaClip);
//
//            ::user::interaction * pinteraction = this;
//
//            ::int_rectangle rectangleFocus;
//
//            while (pinteraction != nullptr)
//            {
//
//               pinteraction->window_rectangle(rectangleFocus);
//
//               screen_to_client(rectangleFocus);
//
//               m_pshapeaClip->add_item(__allocate rectangle_shape(rectangleFocus));
//
//               m_pshapeaClip->add_item(__allocate intersect_clip_shape());
//
//               pinteraction = pinteraction->get_parent();
//
//            }
//
//         }
//
//         pgraphics->reset_clip();
//
//         pgraphics->add_shapes(*m_pshapeaClip);
//
//      }
//      catch (...)
//      {
//
//         throw ::exception(error_failed, "no more a u");
//
//      }

   }


   void control_box::_001OnDraw(::draw2d::graphics_pointer & pgraphics)
   {

      ::user::box::_001OnDraw(pgraphics);

      draw_display_normal_label(pgraphics);

   }


   void control_box::draw_display_normal_label(::draw2d::graphics_pointer & pgraphics)
   {

      auto pframewindow = m_pframewindow;

      if (::is_null(pframewindow))
      {

         return;

      }

      auto edisplay = pframewindow->const_layout().design().display();

      if (equivalence_sink(edisplay) == e_display_normal)
      {

         if (edisplay == e_display_normal)
         {

            pgraphics->text_out(0, 0, "Normal");

         }
         else if (edisplay == e_display_compact)
         {

            pgraphics->text_out(0, 0, "Compact");

         }
         else if (edisplay == e_display_broad)
         {

            pgraphics->text_out(0, 0, "Broad");

         }


      }

   }


   void control_box::handle(::topic * ptopic, ::handler_context * pcontext)
   {

      ::user::box::handle(ptopic, phandlercontext);

      ::user::auto_hide::handle(ptopic, phandlercontext);

   }


} // namespace experience



