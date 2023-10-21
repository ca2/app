#include "framework.h"
#include "menu.h"
#include "item.h"
#include "interaction.h"
#include "item_ptra.h"
////#include "acme/exception/exception.h"
#include "acme/constant/id.h"
#include "acme/constant/timer.h"
#include "acme/constant/message.h"
#include "acme/parallelization/synchronous_lock.h"
#include "acme/platform/sequencer.h"
#include "acme/platform/timer.h"
#include "acme/primitive/geometry2d/_text_stream.h"
#include "acme/user/nano/nano.h"
#include "aqua/xml/document.h"
#include "aqua/xml/xml.h"
#include "aura/graphics/draw2d/draw2d.h"
#include "aura/graphics/image/image.h"
#include "aura/platform/application.h"
#include "aura/message/user.h"
#include "aura/user/menu/command.h"
#include "aura/user/user/button.h"
#include "aura/user/user/calc_size.h"
#include "base/user/user/style.h"
#include "base/platform/session.h"
#include "base/user/user/user.h"


#define SWP_NOSIZE          0x0001
#define SWP_NOMOVE          0x0002




namespace user
{


   menu::menu()
   {

      m_econtroltype = e_control_type_menu;

      m_ewindowflag += e_window_flag_arbitrary_positioning;

      m_bCloseButton = true;

      //m_econtroltype = e_control_type_menu;
      m_bCloseButton = true;

      m_iFlags = 0;
      m_bPositionHint = false;
      //m_itemClose.m_atom = "close_menu";
      //m_itemClose.m_pmenu = this;
      m_bAutoDelete = true;
      m_bOwnItem = true;
      m_puserinteractionParent = nullptr;
      m_pchannelNotify = nullptr;
      m_pmenuParent = nullptr;
      m_psubmenu = nullptr;
      m_iHoverSubMenu = -1;
      m_bInline = false;
      m_bMenuOk = false;
      m_pmenuitemSub = nullptr;

      m_bEnableDragClient = true;
      m_bDefaultParentMouseMessageHandling = true;

   }


   menu::menu(::user::menu_item * pitem)
   {

      m_pmenuitem = pitem;

      m_ewindowflag += e_window_flag_arbitrary_positioning;

      //m_econtroltype = e_control_type_menu;

      m_iFlags = 0;
      m_bPositionHint = false;
      m_iHoverSubMenu = -1;
      m_puserinteractionParent = nullptr;
      m_pchannelNotify = nullptr;
      m_pmenuParent = nullptr;
      m_psubmenu = nullptr;
      m_bAutoDelete = true;
      m_bOwnItem = false;
      m_bInline = false;
      m_bMenuOk = false;

      

   }


   menu::~menu()
   {

   }


   void menu::install_message_routing(::channel * pchannel)
   {

      ::user::interaction::install_message_routing(pchannel);

      MESSAGE_LINK(MESSAGE_CREATE, pchannel, this, &menu::on_message_create);
      MESSAGE_LINK(MESSAGE_DESTROY, pchannel, this, &menu::on_message_destroy);
      MESSAGE_LINK(e_message_non_client_activate, pchannel, this, &menu::_001OnNcActivate);
      MESSAGE_LINK(e_message_non_client_calc_size, pchannel, this, &menu::on_message_non_client_calculate_size);
      MESSAGE_LINK(e_message_enable, pchannel, this, &menu::_001OnEnable);
      MESSAGE_LINK(e_message_show_window, pchannel, this, &menu::on_message_show_window);
      MESSAGE_LINK(MESSAGE_CLOSE, pchannel, this, &menu::on_message_close);
      MESSAGE_LINK(e_message_mouse_activate, pchannel, this, &menu::_001OnMouseActivate);
      MESSAGE_LINK(e_message_activate, pchannel, this, &menu::_001OnActivate);
      MESSAGE_LINK(e_message_non_client_create, pchannel, this, &menu::_001OnNcCreate);

   }


   void menu::update_flags(int iFlags)
   {

      m_iFlags = iFlags;

   }


   void menu::update_position(const ::point_i32 & point)
   {

      m_bPositionHint = true;

      m_pointPositionHint = point;

   }


   void menu::hints(int iFlags, const ::point_i32 & point)
   {

      update_flags(iFlags);

      update_position(point);

   }


   bool menu::create_menu(const string_array & straCommand, const string_array & straCommandTitle)
   {

      if (m_pmenuitem.is_null())
      {

         m_pmenuitem = __create <  menu_item  > ();

      }

      return m_pmenuitem->create_menu(straCommand, straCommandTitle);

   }


   void menu::destroy()
   {

      set_finish();

      //if (m_puserinteractionParent)
      //{

      //   m_puserinteractionParent->erase_child(this);

      //}

//      try
//      {
//
//         interaction_pointer_array uiptra = m_uiptraChild;
//
//         {
//
//            synchronous_lock synchronouslock(mutex_children());
//
//            m_uiptraChild.erase_all();
//
//         }
//
//         for (index i = 0; i < uiptra.get_count(); i++)
//         {
//
//            try
//            {
//
//               uiptra[i]->DestroyWindow();
//
//            }
//            catch (...)
//            {
//
//            }
//
//         }
//
//      }
//      catch (...)
//      {
//
//
//      }
//
//
//
      {

        // synchronous_lock synchronouslock(mutex_children());

         // m_uiptraChild.interactiona().erase_all();

         synchronous_lock synchronouslock(this->synchronization());

         m_puserinteractionpointeraChild.release();

      }

      m_pmenuitem.release();

      //return ::success;

   }


   bool menu::add_menu(::xml::node * pnode)
   {

      if (m_pmenuitem.is_null())
      {

         m_pmenuitem = __create <  menu_item  > ();

      }

      if (m_pmenuitem.is_null())
      {

         return false;

      }

      m_bCloseButton = pnode->attribute("close_button").is_empty() ||

                       (bool)pnode->attribute("close_button").is_true();


      m_pmenuitem->m_pmenu = this;

      if (!m_pmenuitem->load_menu(pnode))

      {

         return false;

      }

      return true;

   }


   bool menu::load_xml_menu(const ::payload & payload)
   {

      acmesystem()->m_paquasystem->_xml();

      auto pxmldocument = __create_new < ::xml::document >();

      try
      {

         pxmldocument->load(payload);

      }
      catch(const ::exception & exception)
      {

         auto psequencer = nano()->exception_message_console(exception);

         psequencer->do_asynchronously();

         return false;

      }

      return add_menu(pxmldocument->root());

   }


   void menu::on_message_show_window(::message::message * pmessage)
   {

      ::pointer<::message::show_window>pshow(pmessage);

      if (pshow->m_bShow)
      {

         informationf("menu::on_message_show_window bShow = %d", pshow->m_bShow);

         if (m_puserinteractionParent)
         {

            host_post([this]()
            {

               set_foreground_window();

               host_post([this]()
                  {

                     set_active_window();

                     bring_to_front();

                     order(e_zorder_top_most);

                  });

            });

         }

      }
      else
      {

         informationf("menu::on_message_show_window bShow = %d", pshow->m_bShow);

      }

   }


   void menu::on_message_destroy(::message::message * pmessage)
   {

      if (m_pmenuParent != nullptr)
      {

         if (m_pmenuParent->m_psubmenu == this)
         {

            m_pmenuParent->m_psubmenu.release();

         }
         else
         {

            ::informationf("parent has other Topic Submenu");

         }

      }

      if (m_psubmenu.is_set())
      {

         m_psubmenu->start_destroying_window();

         m_psubmenu.release();

      }

      if (m_pmenuitem.is_set())
      {

         ::user::interaction * puserinteractionHost = m_pmenuitem->m_puserinteractionHost;

         if (::is_set(puserinteractionHost))
         {

            if (puserinteractionHost->m_menua.erase(this)
                  && m_pmenuitem->m_pmenuitemParent.is_null())
            {

               m_pmenuitem->menu_item_destruct();

            }

         }

      }

      //m_pmenuitem.release();

      m_pchannelNotify.release();

      m_puserinteractionParent.release();

      m_pmenuParent.release();

      m_pitemClose.release();

      m_psubmenu.release();

      m_pmenuitemSub.release();

   }


   ::user::menu_item * menu::GetSubMenu(i32 i)
   {

      return get_menu_item()->m_pmenuitema->element_at(i);

   }


   void menu::defer_initialize_user_menu()
   {

      information() << "::user::menu::defer_initialize_user_menu";

      if(!m_pmenuitem)
      {

         return;

      }

      initialize_user_menu();

   }


   void menu::initialize_user_menu()
   {

      information() << "::user::menu::initialize_user_menu";

      auto psystem = acmesystem()->m_paurasystem;

      auto pdraw2d = psystem->draw2d();

      auto pgraphics = pdraw2d->create_memory_graphics(this);

      if (m_bCloseButton)
      {

         if (m_pitemClose.is_null())
         {

            m_pitemClose = __new(menu_item);

            m_pitemClose->m_atom = "close_menu";

            m_pitemClose->m_pmenu = this;

            ::pointer<::user::interaction>pinteraction = m_pitemClose->m_puserinteraction;

            pinteraction = create_menu_button(pgraphics, m_pitemClose);

            m_pitemClose->m_puserinteraction = pinteraction;

            //if (!m_pitemClose->m_puserinteraction->create_interaction(this, "close_menu"))
            //if (!m_pitemClose->m_puserinteraction->create_child(this))
            m_pitemClose->m_puserinteraction->create_control(this, m_pitemClose->m_atom);
            //{

            //   return false;

            //}

         }

         ::pointer<::user::button>pbutton = m_pitemClose->m_puserinteraction;

         if (pbutton)
         {

            pbutton->set_stock_icon(e_stock_icon_close);

         }
         else
         {

            m_pitemClose->m_puserinteraction->set_window_text("x");

         }

      }

      if (!m_pmenuitem->create_buttons(pgraphics, this))
      {

         ASSERT(false);

         return;

      }

      //if(m_procedureOnAfterInitializeUserMenu)
      //{

      //   information() << "m_procedureOnAfterInitializeUserMenu set. gonna call it...";

      //   m_procedureOnAfterInitializeUserMenu();

      //}

   }


   bool menu::create_menu(::channel* pchannelNotify, ::user::interaction * puiParent)
   {

      if (m_pmenuitem.is_null())
      {

         m_pmenuitem = __create <  menu_item  >();

      }

      m_puserinteractionOwner = puiParent;

      information() << "::user::menu::create_menu parent window: " << (::iptr) m_puserinteractionOwner.m_p;

      ::string strType;

      strType = ::type(m_puserinteractionOwner).name();

      information() << "::user::menu::create_menu parent window type: " << strType;

#if defined(UNIVERSAL_WINDOWS) || defined(WINDOWS_DESKTOP) || defined(LINUX) || defined(FREEBSD) || defined(MACOS)

      auto pwindow = m_puserinteractionOwner->get_wnd();

      pwindow->m_menua.add(this);

#else

      m_puserinteractionOwner->m_menua.add(this);

#endif

      m_pmenuitem->m_puserinteractionHost = m_puserinteractionOwner;

      if (::is_null(pchannelNotify))
      {

         pchannelNotify = m_puserinteractionOwner;

      }

      m_pchannelNotify = pchannelNotify;

      m_pmatterCommandHandler = pchannelNotify;

      if (!is_window())
      {

//         int iStyleEx = 0;
//
//         if (puiParent == nullptr)
//         {
//
//
//         }

         set_tool_window();


#if defined(UNIVERSAL_WINDOWS)

         //create_interaction(puiParent);

         create_interaction(puiParent->top_level());

         //if (!create_interaction(puiParent))
         //{

         //   return false;

         //}

#else
         //auto pusersystem = __new(::user::system (iStyleEx, nullptr, nullptr, 0, nullptr, pcreate));

         //if (!create_window_ex(pusersystem, puiParent))
         //if (!create_host())

         create_host(e_parallelization_asynchronous);
         //{

         //   return false;

         //}

#endif

//         if (pchannelNotify != nullptr)
//         {
//
//            //set_owner(puiNotify);
//
//
//         }

      }
      else
      {

         defer_initialize_user_menu();

      }

      //::user::style_context stylecontext;

      return true;

   }


   bool menu::create_inline_menu(::channel * pchannelNotify, ::user::interaction * puiParent)
   {

      m_bMenuOk = false;

      m_bInline = true;

      if (!create_menu(pchannelNotify, puiParent))
      {

         return false;

      }

      update_command(m_pmenuitem);

      m_bMenuOk = true;

      //      create_buttons(m_pmenuitem);

      //on_layout(pgraphics);

      //auto rectangleX = puiParent->rectangle();

      //place(rectangleX);

      //display();

      display(e_display_normal,  e_activation_set_foreground | e_activation_for_context_menu);

      set_need_layout();

      set_need_redraw();

      SetTimer(::e_timer_command_probe, 333_ms, nullptr);

      return true;

   }



   bool menu::track_popup_menu(::channel * pchannelNotify, ::user::interaction * puiParent)
   {

      m_procedureOnAfterCreate = [this]()
      {

      //   information() << "m_procedureOnAfterInitializeUserMenu menu::track_popup_menu.";

      //   if (!m_bPositionHint)
      //   {

      //      auto pointCursor = mouse_cursor_position();

      //      m_pointPositionHint = pointCursor;

      //   }

      //   auto psystem = acmesystem()->m_paurasystem;

      //   auto pdraw2d = psystem->draw2d();

      //   auto pgraphics = pdraw2d->create_memory_graphics(this);

      //   m_pointTrack = m_pointPositionHint;

      //   layout_menu(pgraphics);

      //   m_bMenuOk = true;

            display(e_display_normal, e_activation_set_foreground | e_activation_for_context_menu);

            order(e_zorder_top_most);

            set_need_layout();

            set_need_redraw();

            post_redraw();

      };


      if (!create_menu(pchannelNotify, puiParent))
      {

         return false;

      }

      return true;

   }


   bool menu::contains_menu_item(menu_item * pitem, bool bRecursive) const
   {

      if (m_pmenuitem.is_null())
      {

         return false;

      }

      return m_pmenuitem->contains_menu_item(pitem, bRecursive);

   }


   //void menu::layout_menu(::draw2d::graphics_pointer & pgraphics)
   //{

   //   ::point_i32 point = m_pointTrack;

   //   if (get_parent() != nullptr)
   //   {

   //      get_parent()->screen_to_client()(m_pointTrack);

   //   }

   //   auto pstyle = get_style(pgraphics);

   //   pgraphics->set(get_font(pstyle));

   //   auto metrics = pgraphics->get_text_metrics();

   //   auto dMaxHeight = metrics.get_line_height();

   //   m_dItemHeight = dMaxHeight;

   //   m_dCheckBoxSize = dMaxHeight;

   //   m_dHeaderHeight = dMaxHeight;

   //   ::pointer<::user::menu_item>pitem = get_menu_item();

   //   ::pointer<::user::menu_item_ptra>pmenuitema = pitem->m_pmenuitema;

   //   auto rectangleMargin = get_margin(pstyle);

   //   auto rectangleBorder = get_border(pstyle);

   //   auto rectanglePadding = get_padding(pstyle);

   //   //int iElementPadding = rectanglePadding.left();

   //   int x = (int) (rectangleMargin.left() + rectangleBorder.left() + rectanglePadding.left());

   //   int y = (int) (rectangleMargin.top() + rectangleBorder.top() + rectanglePadding.top());

   //   class calc_size calcsize;

   //   calcsize.m_pgraphics = pgraphics;

   //   if (m_bCloseButton)
   //   {

   //      m_pitemClose->m_puserinteraction->on_calc_size(&calcsize);

   //      m_pitemClose->m_rectangleUi.left() = x;
   //      m_pitemClose->m_rectangleUi.right() = x + calcsize.m_size.cx();
   //      m_pitemClose->m_rectangleUi.top() = y;
   //      m_pitemClose->m_rectangleUi.bottom() = y + calcsize.m_size.cy();

   //      y += calcsize.m_size.cy();

   //   }

   //   int yClose = y;

   //   m_iaColumnWidth.set_size(1);

   //   m_iaColumnHeight.set_size(1);

   //   m_iaColumnWidth[0] = calcsize.m_size.cx();

   //   m_iaColumnHeight[0] = yClose;

   //   index iColumn = 0;

   //   for (i32 i = 0; i < pmenuitema->get_size(); i++)
   //   {

   //      string strButtonText = pmenuitema->element_at(i)->m_puserinteraction->get_window_text();

   //      pmenuitema->element_at(i)->m_iColumn = (int) iColumn;

   //      pmenuitema->element_at(i)->m_puserinteraction->on_calc_size(&calcsize);

   //      pmenuitema->element_at(i)->m_rectangleUi.left() = x;
   //      pmenuitema->element_at(i)->m_rectangleUi.right() = x + calcsize.m_size.cx();
   //      pmenuitema->element_at(i)->m_rectangleUi.top() = y;
   //      pmenuitema->element_at(i)->m_rectangleUi.bottom() = y + calcsize.m_size.cy();

   //      y += calcsize.m_size.cy();

   //      m_iaColumnHeight[0] = y;

   //      if (calcsize.m_size.cx() > m_iaColumnWidth[0])
   //      {

   //         m_iaColumnWidth[0] = calcsize.m_size.cx();

   //      }

   //      if (pmenuitema->element_at(i)->m_bBreak)
   //      {

   //         x += m_iaColumnWidth[0];

   //         y = yClose;

   //         iColumn++;

   //         m_iaColumnWidth.add(0);

   //         m_iaColumnHeight.add(yClose);

   //      }

   //   }

   //   m_size.cx() = (int) (m_iaColumnWidth.get_sum()
   //               + rectangleMargin.left() + rectangleMargin.right()
   //               + rectangleBorder.left() + rectangleBorder.right()
   //               + rectanglePadding.left() + rectanglePadding.right());

   //   m_size.cy() = (int) (m_iaColumnHeight.get_maximum_value()
   //               + rectangleMargin.top() + rectangleMargin.bottom()
   //               + rectangleBorder.top() + rectangleBorder.bottom()
   //               + rectanglePadding.top() + rectanglePadding.bottom());


   //   m_size.cx() = maximum(m_sizeMinimum.cx(), m_size.cx());

   //   m_size.cy() = maximum(m_sizeMinimum.cy(), m_size.cy());

   //   ::count iItemCount = pmenuitema->get_size();

   //   ::pointer<::base::style>pbasestyle = pstyle;

   //   for (i32 i = 0; i < iItemCount; i++)
   //   {

   //      ::user::menu_item * pitem = pmenuitema->element_at(i);

   //      pmenuitema->element_at(i)->m_rectangleUi.right() = x + m_iaColumnWidth[pitem->m_iColumn];

   //      pbasestyle->prepare_menu(pgraphics, pitem);

   //      pitem->m_rectangleUi.right() = maximum(pitem->m_rectangleUi.right(), pitem->m_rectangleUi.left() + m_sizeMinimum.cx());

   //      pitem->m_puserinteraction->place(pitem->m_rectangleUi);

   //      pitem->m_puserinteraction->display();

   //   }

   //   if (pbasestyle && m_bCloseButton)
   //   {

   //      pbasestyle->prepare_menu(pgraphics, m_pitemClose);

   //      m_pitemClose->m_puserinteraction->place(m_pitemClose->m_rectangleUi);

   //      m_pitemClose->m_puserinteraction->display();

   //   }

   //   ::rectangle_i32 rectangleWindow;

   //   rectangleWindow.left() = point.x();
   //   rectangleWindow.top() = point.y();
   //   rectangleWindow.right() = rectangleWindow.left() + m_size.cx();
   //   rectangleWindow.bottom() = rectangleWindow.top() + m_size.cy();

   //   ::rectangle_i32 rectangleMonitor;

   //   auto iMonitor = get_best_monitor(&rectangleMonitor, rectangleWindow);
   //      
   //   if(iMonitor >= 0)
   //   {

   //      rectangleMonitor.deflate(16, 16);

   //      if (rectangleWindow.left() < rectangleMonitor.left())
   //      {

   //         rectangleWindow.offset(rectangleMonitor.left() - rectangleWindow.left(), 0);

   //      }
   //      else if (rectangleWindow.right() > rectangleMonitor.right())
   //      {

   //         rectangleWindow.offset(rectangleMonitor.right() - rectangleWindow.right(), 0);

   //      }

   //      if (rectangleWindow.top() < rectangleMonitor.top())
   //      {

   //         rectangleWindow.offset(0, rectangleMonitor.top() - rectangleWindow.top());

   //      }
   //      else if (rectangleWindow.bottom() > rectangleMonitor.bottom())
   //      {

   //         rectangleWindow.offset(0, rectangleMonitor.bottom() - rectangleWindow.bottom());

   //      }

   //   }

   //   order(e_zorder_top_most);

   //   information() << "::user::menu::layout_menu place : " << rectangleWindow;

   //   place(rectangleWindow);

   //   //display(e_display_normal, e_activation_no_activate);

   //   display(e_display_normal, 
   //      e_activation_set_foreground |
   //   e_activation_set_popup);

   //   set_need_redraw();

   //   post_redraw();

   //}


   void menu::_001OnDraw(::draw2d::graphics_pointer & pgraphics)
   {

      auto pstyle = get_style(pgraphics);

      auto crBackground = get_color(pstyle, e_element_background);

      if (crBackground.is_translucent())
      {

         ::rectangle_f64 rectangleClip;

         pgraphics->get_clip_box(rectangleClip);

         auto rectangleX = this->rectangle();

         //pgraphics->reset_clip();

         //auto pointOffset = pgraphics->get_origin();

         //memset(pgraphics->m_pimage->m_pimage32, 80, pgraphics->m_pimage->scan_area_in_bytes());

         pgraphics->fill_rectangle(rectangleX, argb(255, 255, 255, 255));

      }

      ::user::interaction::_001OnDraw(pgraphics);

   }




   void menu::on_message_left_button_down(::message::message * pmessage)
   {

      pmessage->previous();

   }


   void menu::defer_close()
   {

      auto ptopic = create_topic(id_context_menu_close);

      route(ptopic);

      if (!m_bInline && !ptopic->m_bRet)
      {

         post_message(MESSAGE_CLOSE);

      }

   }


   void menu::handle(::topic * ptopic, ::context * pcontext)
   {

      if (ptopic->m_atom == ::id_click)
      {

         auto puserinteractionTopic = ptopic->user_interaction();

         if (m_pitemClose.is_set() && puserinteractionTopic == m_pitemClose->m_puserinteraction)
         {

            defer_close();

         }
         else
         {

            ::pointer<::user::menu_item>pitem = ptopic->user_interaction()->m_pmenuitem;

            if (pitem != nullptr && !pitem->m_bPopup)
            {

               if (ptopic->user_interaction()->m_atom.begins("syscommand::"))
               {

                  auto pchannelNotify = get_notify_channel();

                  if (::is_set(pchannelNotify))
                  {

                     //::message::command command(ptopic->user_element_id());

                     //puiTarget->_001SendCommand(&command);

                     pchannelNotify->handle_command(ptopic->user_interaction()->m_atom);

                  }

               }
               else
               {

                  auto pchannelNotify = m_pchannelNotify;

                  atom idCommand = ptopic->user_interaction()->m_atom;

                  idCommand = translate_property_id(idCommand);

                  defer_close();

                  // this may be destroyed by MESSAGE_CLOSE above

                  if (::is_set(pchannelNotify))
                  {

                     ::message::command command(idCommand);

                     command.m_actioncontext = ptopic->m_actioncontext;

                     pchannelNotify->_001SendCommand(&command);

                     ptopic->m_bRet = command.m_bRet;

                     if (ptopic->m_bRet)
                     {

                        return;

                     }

                  }

               }

            }

         }

      }
//      else if (ptopic->m_atom == ::id_mouse_enter)
//      {
//
//         if (m_pitemClose.is_set()
//               && ptopic->user_interaction() != m_pitemClose->m_puserinteraction)
//         {
//
//            if (!m_bInline)
//            {
//
//               if (ptopic->user_interaction()->m_pmenuitem != m_pmenuitemSub)
//               {
//
//                  {
//
//                     ::pointer<::user::menu_item>pitem = ptopic->user_interaction()->m_pmenuitem;
//
//                     if (pitem)
//                     {
//
//                        if (pitem->m_bPopup)
//                        {
//
//                           if (m_psubmenu != nullptr)
//                           {
//
//                              m_psubmenu->start_destroying_window();
//
//                              m_psubmenu = nullptr;
//
//                              m_pmenuitemSub = nullptr;
//
//                           }
//
//                           m_pmenuitemSub = pitem;
//
//                           m_psubmenu = __new(menu(pitem));
//
//                           m_psubmenu->initialize(this);
//
//                           m_psubmenu->m_pmenuParent = this;
//
//                           ::rectangle_i32 rectangle;
//
//                           ptopic->user_interaction()->window_rectangle(rectangle);
//
//                           m_psubmenu->update_position(rectangle.top_right());
//
//                           m_psubmenu->track_popup_menu(m_pchannelNotify);
//
//                        }
//                        else
//                        {
//
//                           ::topic topic;
//
//                           topic.m_atom = ::id_menu_hover;
//
//                           topic.m_atom = pitem->m_atom;
//
//                           ::user::interaction * puiTarget = get_target_window();
//
//                           if (puiTarget == nullptr)
//                           {
//
//                              return;
//
//                           }
//
//                           return puiTarget->route(&topic);
//
//                        }
//
//                     }
//
//                  }
//
//               }
//
//            }
//
//         }
//
//         ptopic->m_bRet = true;
//
//         return;
//
//      }
//      else if (ptopic->m_atom == ::id_mouse_leave)
//      {
//         if (ptopic->user_element_id() == m_atomTimerMenu)
//         {
//            KillTimer(e_timer_menu);
//            m_atomTimerMenu.is_empty();
//         }
//
//         ptopic->m_bRet = true;
//
//         return;
//
//      }

      ::user::interaction::handle(ptopic, pcontext);

   }


   void menu::_001OnTimer(::timer * ptimer)
   {

      ::user::interaction::_001OnTimer(ptimer);

      ::pointer<::user::menu_item>pitemThis = get_menu_item();

      if (pitemThis == nullptr)
      {

         return;

      }

      ::pointer<::user::menu_item_ptra>pmenuitema = pitemThis->m_pmenuitema;

      if (ptimer->m_uEvent == e_timer_menu)
      {
         KillTimer(e_timer_menu);
         if (m_atomSubMenu.has_char())
         {
            m_psubmenu->send_message(MESSAGE_CLOSE);
            m_psubmenu = nullptr;
            m_atomSubMenu.is_empty();
         }

         if (m_atomTimerMenu.has_char())
         {

            m_atomSubMenu = m_atomTimerMenu;

            m_psubmenu = __new(menu(pmenuitema->find(m_atomTimerMenu)));

            m_psubmenu->initialize(this);

            ::rectangle_i32 rectangle;

            pmenuitema->find(m_atomTimerMenu)->m_puserinteraction->window_rectangle(rectangle);

            m_psubmenu->update_position(rectangle.top_right());

            m_psubmenu->track_popup_menu(m_pchannelNotify, this);

         }

         m_atomTimerMenu.is_empty();

      }
      else if (ptimer->m_uEvent == ::e_timer_command_probe)
      {

         {

            synchronous_lock synchronouslock(this->synchronization());

            update_command(m_pmenuitem);

         }

         //if(pmenuitema != nullptr)
         //{
         //   ::message::command commandui(this);
         //   commandui.m_pitema          = pmenuitema;
         //   for(i32 i = 0; i < pmenuitema->get_size(); i++)
         //   {
         //
         //      commandui.m_iIndex    = i;
         //      commandui.m_atom        = pmenuitema->element_at(i)->m_atom;
         //      commandui.m_pOther    = pmenuitema->element_at(i)->m_puserinteraction;
         //
         //      ::pointer<::user::interaction>puiTarget = get_target_window();
         //
         //      if(puiTarget != nullptr)
         //      {
         //         /* xxx if(puserinteractionParent->on_command(0,
         //          MAKELONG((i32)CN_UPDATE_::message::command, e_message_command+WM_REFLECT_BASE),
         //          &commandui, nullptr))
         //          continue;*/
         //         if(puiTarget->_001SendUpdateCmdUi(&commandui))
         //            continue;
         //      }
         //   }
         //}
      }


   }


   void menu::on_message_create(::message::message * pmessage)
   {

      information() << "::user::menu::on_messsage_create";

      /// descriptor().set_control_type(e_control_type_menu);

      pmessage->previous();

      UNREFERENCED_PARAMETER(pmessage);

      //create_color(color_background, argb(84 + 77, 185, 184, 177));

      //create_translucency(::user::e_translucency_present;

      defer_initialize_user_menu();

   }



   //    void menu::_001OnIdleUpdateCmdUI(::message::message * pmessage)
   //    {
   //       UNREFERENCED_PARAMETER(pmessage);
   //       //      ::pointer<::user::message>pusermessage(pmessage);

   //       ::pointer<::user::menu_item>pitemThis = get_item();

   //       ::pointer<::user::menu_item_ptra>pmenuitema = pitemThis->m_spmenuitema;

   //       if(pmenuitema != nullptr)
   //       {
   //          ::message::command commandui(this);
   //          commandui.m_pitema          = pmenuitema;
   //          for(i32 i = 0; i < pmenuitema->get_size(); i++)
   //          {

   //             commandui.m_iIndex    = i;
   //             commandui.m_atom        = pmenuitema->element_at(i)->m_atom;
   //             commandui.m_pOther    = pmenuitema->element_at(i)->m_puserinteraction;

   //             ::pointer<::user::interaction>puserinteractionParent = m_puiNotify;
   //             if(puserinteractionParent != nullptr)
   //             {
   //                /*
   //                 if(puserinteractionParent->on_command(0,
   //                 MAKELONG((i32)CN_UPDATE_::message::command, e_message_command+WM_REFLECT_BASE),
   //                 &commandui, nullptr))
   //                 continue;
   //                 */

   //                if(puserinteractionParent->_001SendUpdateCmdUi(&commandui))
   //                   continue;
   //             }

   //          }
   //       }
   //    }


   void menu::_001OnEnable(::message::message * pmessage)
   {
      UNREFERENCED_PARAMETER(pmessage);
   }


   void menu::_001OnNcCreate(::message::message * pmessage)
   {

      ::pointer<::user::message>pusermessage(pmessage);

      pusermessage->m_bRet = true;

      pusermessage->m_lresult = 1;

   }


   void menu::_001OnNcActivate(::message::message * /*pmessage */)
   {

      //::pointer<::message::nc_activate>pncactivate(pmessage);

//#ifdef WINDOWS_DESKTOP
//
//      if (::IsIconic(get_handle()))
//      {
//
//         pncactivate->m_bRet = false;
//
//      }
//      else
//      {
//
//         pncactivate->m_lresult = false;
//
//         pncactivate->m_bRet = true;
//
//
//      }
//
//#else
//
//      pncactivate->m_lresult = true;
//
//      pncactivate->m_bRet = true;
//
//#endif

   }


   void menu::_001OnActivate(::message::message * pmessage)
   {

      ::pointer<::message::activate>pactivate(pmessage);

      pactivate->m_lresult = 0;

      pactivate->m_bRet = true;

   }


   void menu::_001OnMouseActivate(::message::message * pmessage)
   {

      ::pointer<::message::mouse_activate>pmouseactivate(pmessage);

      pmouseactivate->m_lresult = e_mouse_activate_no_activate;

      pmouseactivate->m_bRet = true;

   }


   size_i32 menu::get_window_minimum_size()
   {

      return m_sizeMinimum;

   }


   void menu::on_message_non_client_calculate_size(::message::message * pmessage)
   {

      ///::pointer<::user::message>pusermessage(pmessage);

      pmessage->previous();

      return;

      //if (pusermessage->m_wparam == true)
      //{

      //   pusermessage->m_bRet = true;
      //   pusermessage->set_lresult(0);

      //}
      //else
      //{

      //   ::rectangle_i32 * prectangle = (::rectangle_i32 *)pusermessage->m_lparam.m_lparam;

      //   prectangle->left() = m_pointTrack.x();

      //   prectangle->top() = m_pointTrack.y();

      //   prectangle->right() = prectangle->left() + maximum(::user::interaction::get_window_minimum_size().cx(), m_size.cx());

      //   prectangle->bottom() = prectangle->left() + maximum(::user::interaction::get_window_minimum_size().cy(), m_size.cy());

      //   pusermessage->m_bRet = true;
      //   pusermessage->set_lresult(0);

      //}

   }


   void menu::on_message_close(::message::message * pmessage)
   {

      if (!m_bInline)
      {

         if (m_pmenuParent != nullptr)
         {

            m_pmenuParent->post_message(MESSAGE_CLOSE);

         }

         //DestroyWindow();
         set_finish();

      }

      pmessage->m_bRet = true;

   }


   bool menu::pre_create_window(::user::system * pusersystem)
   {


      return true;

   }


   ::pointer<::user::menu_item>menu::get_menu_item()
   {

      return m_pmenuitem;

   }


   //::pointer<::user::menu_item>menu::get_menu_item(::user::interaction * pinteraction)
   //{

   //   ::pointer<::user::interaction>pbutton = pinteraction;

   //   if (pbutton.is_null())
   //   {

   //      return nullptr;

   //   }

   //   return pbutton->m_pmenuitem;

   //}


   ::channel * menu::get_notify_channel()
   {

      return m_pchannelNotify;

      //auto pchannelNotify = m_pchannelNotify;

      //if (::is_null(pchannelNotify))
      //{

      //   return nullptr;

      //}

      //if (dynamic_cast <::user::frame *> (puiTarget) == nullptr)
      //{

      //   puiTarget = puiTarget->get_parent_frame();

      //}

      //return puiTarget;

   }


   bool menu::has_pending_graphical_update()
   {

      return ::user::interaction::has_pending_graphical_update();

   }



   void menu::update_command(menu_item * pitemParent)
   {

      if (m_pchannelNotify == nullptr)
      {

         return;

      }

      if (pitemParent == nullptr)
      {

         return;

      }

      if (pitemParent->m_pmenuitema == nullptr)
      {

         return;

      }

      auto pmenucommand = __create_new< ::user::menu_command>();

      pmenucommand->m_pitema = pitemParent->m_pmenuitema;

      pmenucommand->m_iCount = pitemParent->m_pmenuitema->get_size();

      for (pmenucommand->m_iIndex = 0; pmenucommand->m_iIndex < pmenucommand->m_iCount; pmenucommand->m_iIndex++)
      {

         ::pointer<menu_item>pitem = pitemParent->m_pmenuitema->element_at(pmenucommand->m_iIndex);

         if (pitem->m_atom.is_empty())
         {

            continue;

         }

         pmenucommand->m_commandtargetptraHandle.clear();

         pmenucommand->m_atom = pitem->m_atom;

         pmenucommand->m_puiOther = pitem->m_puserinteraction;

         if (m_pchannelNotify.is_null())
         {

            return;

         }

         try
         {

            m_pchannelNotify->_001SendCommandProbe(pmenucommand);

         }
         catch (...)
         {

            return;

         }

      }

      for (pmenucommand->m_iIndex = 0; pmenucommand->m_iIndex < pmenucommand->m_iCount; pmenucommand->m_iIndex++)
      {

         ::pointer<menu_item>pitem = pitemParent->m_pmenuitema->element_at(pmenucommand->m_iIndex);

         pmenucommand->m_atom = pitem->m_atom;

         pmenucommand->m_puiOther = pitem->m_puserinteraction;

         if (pitem->m_pmenu != nullptr)
         {

            pitem->m_pmenu->update_command(pitem);

         }

      }
      if (pmenucommand->m_bEnableChanged || pmenucommand->m_bRadioChanged)
      {

         set_need_redraw();

      }

   }


   ::pointer<::user::menu_interaction>menu::create_menu_button(::draw2d::graphics_pointer & pgraphics, menu_item * pitem)
   {

      auto pstyle = get_style(pgraphics);

      ::pointer<::base::session>psession = get_session();

      auto puser = psession->baseuser();

      auto pinteraction = puser->create_menu_button(pstyle, pitem);

      if (!pinteraction)
      {

         return nullptr;

      }

      //auto estatus = 
      pinteraction->initialize(this);

      //if (!estatus)
      //{

      //   return nullptr;

      //}

      pinteraction->m_pmatterCommandHandler = this;
      
      pinteraction->add_handler(this);

      return pinteraction;

   }


   // <3ThomasBorregaardSorensen__!! (I need to suck you, back, middle, front .20211031)
   void menu::route_command(::message::command* pcommand, bool bRouteToKeyDescendant)
   {

      if(m_pchannelNotify)
      {

         m_pchannelNotify->route_command(pcommand, bRouteToKeyDescendant);

         if (pcommand->m_bRet)
         {

            return;

         }

      }

      ::user::interaction::route_command(pcommand, bRouteToKeyDescendant);

   }



   // <3ThomasBorregaardSorensen__!! (I need to suck you, back, middle, front)
   void menu::handle_command(const ::atom& atom)
   {

      if (m_pmatterCommandHandler)
      {

         defer_close();

         //auto estatus = 
         
         m_pmatterCommandHandler->handle_command(atom);

         //if (!estatus)
         //{

         //   return estatus;

         //}

         //return estatus;

      }

      //return ::error_failed;

   }


   void menu::on_perform_top_down_layout(::draw2d::graphics_pointer & pgraphics)
   {

      ::pointer<::user::menu_item>pitem = get_menu_item();

      if(!pitem)
      {

         return;

      }

      ::point_i32 point;

      if(get_parent() == nullptr)
      {

         information() << "menu::on_perform_top_down_layout top level menu";

         if (!m_bPositionHint)
         {

            auto pointCursor = mouse_cursor_position();

            m_pointPositionHint = pointCursor;

         }

         //auto pgraphics = pdraw2d->create_memory_graphics(this);

         m_pointTrack = m_pointPositionHint;

         //void menu::layout_menu(::draw2d::graphics_pointer & pgraphics)
         //{

         point = m_pointTrack;

         if (get_parent() != nullptr)
         {

            get_parent()->screen_to_client()(m_pointTrack);

         }

      }
      else
      {

         information() << "menu::on_perform_top_down_layout child menu";

      }

      //auto psystem = acmesystem()->m_paurasystem;

      //auto pdraw2d = psystem->draw2d();

      auto pstyle = get_style(pgraphics);

      pgraphics->set(get_font(pstyle));

      auto metrics = pgraphics->get_text_metrics();

      auto dMaxHeight = metrics.get_line_height();

      m_dItemHeight = dMaxHeight;

      m_dCheckBoxSize = dMaxHeight;

      m_dHeaderHeight = dMaxHeight;

      ::pointer<::user::menu_item_ptra>pmenuitema = pitem->m_pmenuitema;

      auto rectangleMargin = get_margin(pstyle);

      auto rectangleBorder = get_border(pstyle);

      auto rectanglePadding = get_padding(pstyle);

      //int iElementPadding = rectanglePadding.left();

      int x = (int) (rectangleMargin.left() + rectangleBorder.left() + rectanglePadding.left());

      int y = (int) (rectangleMargin.top() + rectangleBorder.top() + rectanglePadding.top());

      //class calc_size calcsize;

      //calcsize.m_pgraphics = pgraphics;

      ::size_i32 size;

      if (m_bCloseButton)
      {

         size = m_pitemClose->m_puserinteraction->get_preferred_size(pgraphics);

         information() << "close_button size : " << size;

         m_pitemClose->m_rectangleUi.left() = x;
         m_pitemClose->m_rectangleUi.right() = x + size.cx();
         m_pitemClose->m_rectangleUi.top() = y;
         m_pitemClose->m_rectangleUi.bottom() = y + size.cy();

         y += size.cy();

      }

      int yClose = y;

      m_iaColumnWidth.set_size(1);

      m_iaColumnHeight.set_size(1);

      m_iaColumnWidth[0] = size.cx();

      m_iaColumnHeight[0] = yClose;

      index iColumn = 0;

      for (i32 i = 0; i < pmenuitema->get_size(); i++)
      {

         string strButtonText = pmenuitema->element_at(i)->m_puserinteraction->get_window_text();

         pmenuitema->element_at(i)->m_iColumn = (int) iColumn;

         size = pmenuitema->element_at(i)->m_puserinteraction->get_preferred_size(pgraphics);

         information() << "button text and size : \"" << strButtonText << "\", " << size;

         pmenuitema->element_at(i)->m_rectangleUi.left() = x;
         pmenuitema->element_at(i)->m_rectangleUi.right() = x + size.cx();
         pmenuitema->element_at(i)->m_rectangleUi.top() = y;
         pmenuitema->element_at(i)->m_rectangleUi.bottom() = y + size.cy();

         y += size.cy();

         m_iaColumnHeight[iColumn] = y;

         if (size.cx() > m_iaColumnWidth[iColumn])
         {

            m_iaColumnWidth[iColumn] = size.cx();

         }

         if (pmenuitema->element_at(i)->m_bBreak)
         {

            x += m_iaColumnWidth[iColumn];

            y = yClose;

            iColumn++;

            m_iaColumnWidth.add(0);

            m_iaColumnHeight.add(yClose);

            iColumn = m_iaColumnWidth.get_upper_bound();

         }

      }

      m_size.cx() = (int) (m_iaColumnWidth.get_sum()
                  + rectangleMargin.left() + rectangleMargin.right()
                  + rectangleBorder.left() + rectangleBorder.right()
                  + rectanglePadding.left() + rectanglePadding.right());

      m_size.cy() = (int) (m_iaColumnHeight.get_maximum_value()
                  + rectangleMargin.top() + rectangleMargin.bottom()
                  + rectangleBorder.top() + rectangleBorder.bottom()
                  + rectanglePadding.top() + rectanglePadding.bottom());

      m_size.cx() = maximum(m_sizeMinimum.cx(), m_size.cx());

      m_size.cy() = maximum(m_sizeMinimum.cy(), m_size.cy());

      ::count iItemCount = pmenuitema->get_size();

      ::pointer<::base::style>pbasestyle = pstyle;

      for (i32 i = 0; i < iItemCount; i++)
      {

         ::user::menu_item * pitem = pmenuitema->element_at(i);

         pmenuitema->element_at(i)->m_rectangleUi.right() =
            pmenuitema->element_at(i)->m_rectangleUi.left() + m_iaColumnWidth[pitem->m_iColumn];

         pbasestyle->prepare_menu(pgraphics, pitem);

         //pitem->m_rectangleUi.right() = maximum(pitem->m_rectangleUi.right(), pitem->m_rectangleUi.left() + m_sizeMinimum.cx());

         pitem->m_puserinteraction->place(pitem->m_rectangleUi);

         pitem->m_puserinteraction->display();

      }

      if (m_bCloseButton)
      {

         if (pbasestyle)
         {

            pbasestyle->prepare_menu(pgraphics, m_pitemClose);

         }

         m_pitemClose->m_puserinteraction->place(m_pitemClose->m_rectangleUi);

         m_pitemClose->m_puserinteraction->display();

      }

      if(get_parent() == nullptr)
      {

         ::rectangle_i32 rectangleWindow;

         rectangleWindow.left() = point.x();
         rectangleWindow.top() = point.y();
         rectangleWindow.right() = rectangleWindow.left() + m_size.cx();
         rectangleWindow.bottom() = rectangleWindow.top() + m_size.cy();

         ::rectangle_i32 rectangleMonitor;

         auto iMonitor = get_best_monitor(&rectangleMonitor, rectangleWindow);
            
         if(iMonitor >= 0)
         {

            rectangleMonitor.deflate(16, 16);

            if (rectangleWindow.left() < rectangleMonitor.left())
            {

               rectangleWindow.offset(rectangleMonitor.left() - rectangleWindow.left(), 0);

            }
            else if (rectangleWindow.right() > rectangleMonitor.right())
            {

               rectangleWindow.offset(rectangleMonitor.right() - rectangleWindow.right(), 0);

            }

            if (rectangleWindow.top() < rectangleMonitor.top())
            {

               rectangleWindow.offset(0, rectangleMonitor.top() - rectangleWindow.top());

            }
            else if (rectangleWindow.bottom() > rectangleMonitor.bottom())
            {

               rectangleWindow.offset(0, rectangleMonitor.bottom() - rectangleWindow.bottom());

            }

         }

         //order(e_zorder_top_most);

         information() << "::user::menu::layout_menu place : " << rectangleWindow;

         place(rectangleWindow);

         //display(e_display_normal, e_activation_no_activate);


      }
      else
      {

         set_size(m_size);

      }

      m_bMenuOk = true;

   }


} // namespace user



