#include "framework.h"
#include "menu.h"
#include "interaction.h"
#include "acme/constant/id.h"
#include "acme/constant/timer.h"
#include "acme/constant/message.h"
#include "acme/handler/topic.h"
#include "acme/parallelization/synchronous_lock.h"
#include "acme/platform/sequencer.h"
#include "acme/platform/timer.h"
#include "acme/primitive/geometry2d/_text_stream.h"
#include "acme/nano/nano.h"
#include "apex/user/menu/menu.h"
#include "aqua/xml/document.h"
#include "aqua/xml/xml.h"
#include "aura/graphics/draw2d/draw2d.h"
#include "aura/graphics/image/image.h"
#include "aura/platform/application.h"
#include "aura/message/user.h"
#include "aura/user/user/button.h"
#include "aura/user/user/calc_size.h"
#include "aura/user/menu/command.h"
#include "base/user/menu/item.h"
#include "base/user/menu/item_ptra.h"
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

      m_bCloseParentOnClose = true;

      m_bScreenHint = false;

      m_bCursorHint = false;
      m_bAutoDelete = true;
      m_bOwnItem = true;
      m_puserinteractionParent = nullptr;
      m_pchannelNotify = nullptr;
      m_pmenuParent = nullptr;
      //m_psubmenu = nullptr;
      m_iHoverSubMenu = -1;
      m_bInline = false;
      m_bMenuOk = false;
      m_pmenuitemSub = nullptr;

      m_bEnableDragClient = true;
      m_bDefaultParentMouseMessageHandling = true;

   }


   menu::menu(::menu::item * pmenuitem)
   {

      m_pmenuitem = pmenuitem;

      m_ewindowflag += e_window_flag_arbitrary_positioning;

      //m_econtroltype = e_control_type_menu;

      m_bScreenHint = false;
      m_bCursorHint = false;
      m_iHoverSubMenu = -1;
      m_puserinteractionParent = nullptr;
      m_pchannelNotify = nullptr;
      m_pmenuParent = pmenuitem->m_pmenu;
      //m_psubmenu = nullptr;
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


   void menu::update_track_flags(const ::menu::e_track_popup & etrackpopup)
   {

      m_etrackpopup = etrackpopup;

   }


   void menu::update_track_cursor(const ::point_i32 & pointCursorHint)
   {
      
      if(pointCursorHint.is_all(I32_MINIMUM))
      {
       
         return;
         
      }

      m_bCursorHint = true;

      m_pointCursorHint = pointCursorHint;

   }


   void menu::update_track_rectangle(const ::rectangle_i32 & rectangleScreenHint)
   {
      
      if(rectangleScreenHint.is_all(I32_MINIMUM))
      {
       
         return;
         
      }


      m_bScreenHint = true;

      m_rectangleScreenHint = rectangleScreenHint;

   }


   void menu::track_hints(::menu::track_popup * ptrackpopup)
   {
      
      if(ptrackpopup->m_rectangleScreenHint.is_all(I32_MINIMUM))
      {
         
         if(ptrackpopup->m_puserinteractionTarget)
         {
            
            auto rectangleWindow = ptrackpopup->m_puserinteractionTarget->window_rectangle();
            
            update_track_rectangle(rectangleWindow);
            
         }
         
      }
      else
      {
         
         update_track_rectangle(ptrackpopup->m_rectangleScreenHint);
         
      }

      update_track_cursor(ptrackpopup->m_pointCursorHint);

      update_track_flags(ptrackpopup->m_etrackpopup);
      
   }


   bool menu::create_menu(const string_array & straCommand, const string_array & straCommandTitle)
   {

      if (m_pmenuitem.is_null())
      {

         m_pmenuitem = __create <  ::menu::item  >();

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
//            _synchronous_lock synchronouslock(mutex_children());
//
//            m_uiptraChild.erase_all();
//
//         }
//
//         for (::collection::index i = 0; i < uiptra.get_count(); i++)
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

         // _synchronous_lock synchronouslock(mutex_children());

          // m_uiptraChild.interactiona().erase_all();

         _synchronous_lock synchronouslock(this->synchronization());

         m_puserinteractionpointeraChild.release();

      }

      m_pmenuitem.release();

   }


   bool menu::add_menu(::xml::node * pnode)
   {

      if (m_pmenuitem.is_null())
      {

         m_pmenuitem = __create <  ::menu::item  >();

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

      system()->m_paquasystem->_xml();

      auto pxmldocument = __create_new < ::xml::document >();

      try
      {

         pxmldocument->load(payload);

      }
      catch (const ::exception & exception)
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

         //if (m_puserinteractionParent)
         if(::is_null(get_parent()))
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

         if (m_pmenuParent->m_pmenuSubMenu == this)
         {

            m_pmenuParent->m_pmenuSubMenu.release();

         }
         else
         {

            ::acme::get()->platform()->informationf("parent has other Topic Submenu");

         }

      }

      if (m_pmenuSubMenu)
      {

         m_pmenuSubMenu->start_destroying_window();

         m_pmenuSubMenu.release();

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

      m_pchannelNotify.release();

      m_puserinteractionParent.release();

      m_pmenuParent.release();

      m_pitemClose.release();

      m_pmenuSubMenu.release();

      m_pmenuitemSub.release();

   }


   ::menu::item * menu::GetSubMenu(i32 i)
   {

      return get_menu_item()->m_pmenuitema->element_at(i);

   }


   void menu::defer_initialize_user_menu()
   {

      information() << "::user::menu::defer_initialize_user_menu";

      if (!m_pmenuitem)
      {

         return;

      }

      initialize_user_menu();

   }


   void menu::initialize_user_menu()
   {

      information() << "::user::menu::initialize_user_menu";

      auto psystem = system()->m_paurasystem;

      auto pdraw2d = psystem->draw2d();

      auto pgraphics = pdraw2d->create_memory_graphics(this);

      if (m_bCloseButton)
      {

         if (m_pitemClose.is_null())
         {

            m_pitemClose = ::place(new ::menu::item());

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

      m_bNeedPerformLayout = true;

   }


   void menu::set_minimum_width(::i32 iWidth)
   {
   
      m_sizeMinimum.cx() = iWidth;
      
   }


   bool menu::create_menu(::channel * pchannelNotify, ::user::interaction * puiParent)
   {

      if (m_pmenuitem.is_null())
      {

         m_pmenuitem = __create <  ::menu::item  >();

      }

      m_puserinteractionOwner = puiParent;

      information() << "::user::menu::create_menu parent window: " << (::iptr)m_puserinteractionOwner.m_p;

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
         //auto pusersystem = ::place(new ::user::system(iStyleEx, nullptr, nullptr, 0, nullptr, pcreate));

         //if (!create_window_ex(pusersystem, puiParent))
         //if (!create_host())

         //create_host(e_parallelization_asynchronous);
         // 
         create_host();
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

      display(e_display_normal, e_activation_set_foreground | e_activation_for_context_menu);

      set_need_layout();

      set_need_redraw();

      SetTimer(::e_timer_command_probe, 333_ms, nullptr);

      return true;

   }


   bool menu::track_popup_menu(::menu::track_popup * ptrackpopup)
   {

      m_procedureOnAfterCreate = [this]()
         {

            display(e_display_normal, e_activation_set_foreground | e_activation_for_context_menu);

            order(e_zorder_top_most);

            m_bNeedPerformLayout = true;

            set_need_layout();

            set_need_redraw();

            post_redraw();

         };

      add_graphical_output_purpose(this, ::graphics::e_output_purpose_screen);

      track_hints(ptrackpopup);
      
      if (!create_menu(ptrackpopup->m_pchannelNotify, ptrackpopup->m_puserinteractionTarget))
      {

         return false;

      }
      
      m_ptrackpopup = ptrackpopup;

      return true;

   }


   bool menu::contains_menu_item(::menu::item * pitem, bool bRecursive) const
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

   //   ::pointer<::menu::item>pitem = get_menu_item();

   //   ::pointer<::menu::item_ptra>pmenuitema = pitem->m_pmenuitema;

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

   //   ::collection::count iItemCount = pmenuitema->get_size();

   //   ::pointer<::base::style>pbasestyle = pstyle;

   //   for (i32 i = 0; i < iItemCount; i++)
   //   {

   //      ::menu::item * pitem = pmenuitema->element_at(i);

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

      auto pstyle = m_puserinteractionOwner->get_style(pgraphics);

      auto crBackground = get_color(pstyle, e_element_background);

      if (crBackground.is_translucent())
      {

         ::rectangle_f64 rectangleClip;

         pgraphics->get_clip_box(rectangleClip);

         auto rectangleX = this->rectangle();

         //pgraphics->reset_clip();

         //auto pointOffset = pgraphics->get_origin();

         //::memory_set(pgraphics->m_pimage->m_pimage32, 80, pgraphics->m_pimage->scan_area_in_bytes());

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

         post_message(e_message_close);

         if (m_pmenuParent)
         {

            m_pmenuParent->defer_close();

         }

      }
      
      if(m_ptrackpopup)
      {
       
         if(m_ptrackpopup->m_procedureCompleted)
         {
            
            m_ptrackpopup->m_procedureCompleted();
            
         }
         
         m_ptrackpopup.release();
         
      }

   }


   void menu::handle(::topic * ptopic, ::context * pcontext)
   {

      //if (ptopic->m_atom == ::id_click)
      //{

      //   auto puserinteractionTopic = ptopic->user_interaction();

      //   if (m_pitemClose.is_set() && puserinteractionTopic == m_pitemClose->m_puserinteraction)
      //   {

      //      defer_close();

      //   }
      //   else
      //   {

      //      ::pointer<::menu::item>pitem = ptopic->user_interaction()->m_pmenuitem;

      //      on_click(pitem);

      //   }

      //}
      ////      else if (ptopic->m_atom == ::id_mouse_enter)
      ////      {
      ////
      ////         if (m_pitemClose.is_set()
      ////               && ptopic->user_interaction() != m_pitemClose->m_puserinteraction)
      ////         {
      ////
      ////            if (!m_bInline)
      ////            {
      ////
      ////               if (ptopic->user_interaction()->m_pmenuitem != m_pmenuitemSub)
      ////               {
      ////
      ////                  {
      ////
      ////                     ::pointer<::menu::item>pitem = ptopic->user_interaction()->m_pmenuitem;
      ////
      ////                     if (pitem)
      ////                     {
      ////
      ////                        if (pitem->m_bPopup)
      ////                        {
      ////
      ////                           if (m_psubmenu != nullptr)
      ////                           {
      ////
      ////                              m_psubmenu->start_destroying_window();
      ////
      ////                              m_psubmenu = nullptr;
      ////
      ////                              m_pmenuitemSub = nullptr;
      ////
      ////                           }
      ////
      ////                           m_pmenuitemSub = pitem;
      ////
      ////                           m_psubmenu = ::place(new menu(pitem));
      ////
      ////                           m_psubmenu->initialize(this);
      ////
      ////                           m_psubmenu->m_pmenuParent = this;
      ////
      ////                           ::rectangle_i32 rectangle;
      ////
      ////                           ptopic->user_interaction()->window_rectangle(rectangle);
      ////
      ////                           m_psubmenu->update_position(rectangle.top_right());
      ////
      ////                           m_psubmenu->track_popup_menu(m_pchannelNotify);
      ////
      ////                        }
      ////                        else
      ////                        {
      ////
      ////                           ::topic topic;
      ////
      ////                           topic.m_atom = ::id_menu_hover;
      ////
      ////                           topic.m_atom = pitem->m_atom;
      ////
      ////                           ::user::interaction * puiTarget = get_target_window();
      ////
      ////                           if (puiTarget == nullptr)
      ////                           {
      ////
      ////                              return;
      ////
      ////                           }
      ////
      ////                           return puiTarget->route(&topic);
      ////
      ////                        }
      ////
      ////                     }
      ////
      ////                  }
      ////
      ////               }
      ////
      ////            }
      ////
      ////         }
      ////
      ////         ptopic->m_bRet = true;
      ////
      ////         return;
      ////
      ////      }
      ////      else if (ptopic->m_atom == ::id_mouse_leave)
      ////      {
      ////         if (ptopic->user_element_id() == m_atomTimerMenu)
      ////         {
      ////            KillTimer(e_timer_menu);
      ////            m_atomTimerMenu.is_empty();
      ////         }
      ////
      ////         ptopic->m_bRet = true;
      ////
      ////         return;
      ////
      ////      }

      ::user::interaction::handle(ptopic, pcontext);

   }


   bool menu::on_click(::item * pitem)
   {

      ::pointer<::menu::item>pmenuitem = pitem;

      if (pmenuitem)
      {

         if (pmenuitem->m_bPopup)
         {

            show_sub_menu(pmenuitem);

            return true;

         }
         else
         {

            if (pmenuitem->m_atom.begins("syscommand::"))
            {

               auto pchannelNotify = get_notify_channel();

               if (::is_set(pchannelNotify))
               {

                  //::message::command command(ptopic->user_element_id());

                  //puiTarget->_001SendCommand(&command);

                  pchannelNotify->handle_command(pmenuitem->m_atom);

               }

            }
            else if (pmenuitem->m_atom.begins("check://"))
            {

               ::string strId(pmenuitem->m_atom.as_string());

               if (strId.case_insensitive_begins_eat("check://"))
               {

                  if (strId.case_insensitive_begins_eat("application/"))
                  {

                     ::data::check_property checkproperty((::data::property_container*) this->application(), strId);

                     checkproperty.toggle(::e_source_user);

                  }

               }

            }
            else
            {

               auto pchannelNotify = m_pchannelNotify;

               atom idCommand = pmenuitem->m_atom;

               //idCommand = translate_property_id(idCommand);

               defer_close();

               // this may be destroyed by MESSAGE_CLOSE above

               if (::is_set(pchannelNotify))
               {

                  ::message::command command(idCommand);

                  //auto puseritem = user_item(pitem);

                  //command.m_actioncontext = puseritem->M_ac

                  pchannelNotify->_001SendCommand(&command);

                  //ptopic->m_bRet = command.m_bRet;

                  if (command.m_bRet)
                  {

                     return true;

                  }

               }

            }

         }

      }

      return false;

   }


   void menu::show_sub_menu(::menu::item * pmenuitem)
   {

      hide_sub_menu();
      
      auto pusermenu = ::place(new ::user::menu(pmenuitem));
      
      pusermenu->initialize(this);

      m_pmenuSubMenu = pusermenu;

      ::rectangle_i32 rectangle;

      pmenuitem->m_puserinteraction->window_rectangle(rectangle);

      m_pmenuSubMenu->update_track_rectangle(rectangle);
      
      auto ptrackpopup = ::place( new ::menu::track_popup (pusermenu,
                                                              pmenuitem->m_puserinteraction,
                                                              m_pchannelNotify,
                                                            mouse_cursor_position(),
                                                              rectangle));

      m_pmenuSubMenu->track_popup_menu(ptrackpopup);

   }


   void menu::hide_sub_menu()
   {

      if (m_pmenuSubMenu)
      {

         m_pmenuSubMenu->m_bCloseParentOnClose = false;

         m_pmenuSubMenu->post_message(MESSAGE_CLOSE);

         m_pmenuSubMenu = nullptr;
         //m_pitemSubMenu.release();

      }

   }


   void menu::show_sub_menu_delayed(::menu::item * pmenuitem)
   {

      if (::is_null(pmenuitem))
      {

         hide_sub_menu_delayed();

      }

      if (pmenuitem == m_pmenuitemShowSubMenu2)
      {

         return;

      }

      if (m_pmenuSubMenu && pmenuitem == m_pmenuSubMenu->m_pmenuitem)
      {

         return;

      }

      m_bHideSubMenu2 = false;

      m_pmenuitemShowSubMenu2 = pmenuitem;

      SetTimer(e_timer_menu, 300_ms);

   }


   void menu::hide_sub_menu_delayed()
   {

      m_bHideSubMenu2 = true;

      m_pmenuitemShowSubMenu2 = nullptr;

      SetTimer(e_timer_menu, 300_ms);

   }


   void menu::detach_sub_menu()
   {

      if (::is_set(m_pmenuitem))
      {

         m_pmenuitem->release_children_interaction();

         m_pmenuitem.release();

      }

   }

   
   
   void menu::_001OnTimer(::timer * ptimer)
      {

         ::user::interaction::_001OnTimer(ptimer);

         ::pointer<::menu::item>pitemThis = get_menu_item();

         if (pitemThis == nullptr)
         {

            return;

         }

         ::pointer<::menu::item_ptra>pmenuitema = pitemThis->m_pmenuitema;

         if (ptimer->m_uEvent == e_timer_menu)
         {

            KillTimer(e_timer_menu);

            //if (m_atomSubMenu.has_char())
            //{
            //   m_psubmenu->send_message(MESSAGE_CLOSE);
            //   m_psubmenu = nullptr;
            //   m_atomSubMenu.is_empty();
            //}

            _synchronous_lock synchronouslock(this->synchronization());

            if (m_pmenuitemShowSubMenu2)
            {

               show_sub_menu(m_pmenuitemShowSubMenu2);

               m_pmenuitemShowSubMenu2 = nullptr;

            }
            else if(m_bHideSubMenu2)
            {

               hide_sub_menu();

            }


            //if (m_pmenuitemClick)
            //{

            //}

//m_atomTimerMenu.is_empty();


            //}
            //if (m_atomTimerMenu.has_char())
            //{

            //   m_atomSubMenu = m_atomTimerMenu;

            //   m_psubmenu = ::place(new menu(pmenuitema->find(m_atomTimerMenu)));

            //   m_psubmenu->initialize(this);

            //   ::rectangle_i32 rectangle;

            //   pmenuitema->find(m_atomTimerMenu)->m_puserinteraction->window_rectangle(rectangle);

            //   m_psubmenu->update_position(rectangle.top_right());

            //   m_psubmenu->track_popup_menu(m_pchannelNotify, this);

            //}

            //m_atomTimerMenu.is_empty();

         }
         else if (ptimer->m_uEvent == ::e_timer_command_probe)
         {

            {

               _synchronous_lock synchronouslock(this->synchronization());

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

         __UNREFERENCED_PARAMETER(pmessage);

         //create_color(color_background, argb(84 + 77, 185, 184, 177));

         //create_translucency(::user::e_translucency_present;

         defer_initialize_user_menu();

      }



      //    void menu::_001OnIdleUpdateCmdUI(::message::message * pmessage)
      //    {
      //       __UNREFERENCED_PARAMETER(pmessage);
      //       //      ::pointer<::user::message>pusermessage(pmessage);

      //       ::pointer<::menu::item>pitemThis = get_item();

      //       ::pointer<::menu::item_ptra>pmenuitema = pitemThis->m_spmenuitema;

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
         __UNREFERENCED_PARAMETER(pmessage);
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


      bool menu::is_menu() const
      {

         return true;

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

            if (m_bCloseParentOnClose)
            {

               if (m_pmenuParent != nullptr)
               {

                  m_pmenuParent->post_message(MESSAGE_CLOSE);

               }

            }
            else
            {

               detach_sub_menu();

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


      ::pointer<::menu::item>menu::get_menu_item()
      {

         return m_pmenuitem;

      }


      //::pointer<::menu::item>menu::get_menu_item(::user::interaction * pinteraction)
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


//      bool menu::has_pending_graphical_update()
//      {
//
//         return ::user::interaction::has_pending_graphical_update();
//
//      }



      void menu::update_command(::menu::item * pitemParent)
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

         auto pmenucommand = __create_new< ::menu::command>();

         pmenucommand->m_pitema = pitemParent->m_pmenuitema;

         pmenucommand->m_iCount = pitemParent->m_pmenuitema->get_size();

         for (pmenucommand->m_iIndex = 0; pmenucommand->m_iIndex < pmenucommand->m_iCount; pmenucommand->m_iIndex++)
         {

            ::pointer<::menu::item>pitem = pitemParent->m_pmenuitema->element_at(pmenucommand->m_iIndex);

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

            ::pointer<::menu::item>pitem = pitemParent->m_pmenuitema->element_at(pmenucommand->m_iIndex);

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


      ::pointer<::user::menu_interaction>menu::create_menu_button(::draw2d::graphics_pointer & pgraphics, ::menu::item * pitem)
      {

         auto pstyle = m_puserinteractionOwner->get_style(pgraphics);

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
      void menu::route_command(::message::command * pcommand, bool bRouteToKeyDescendant)
      {

         if (m_pchannelNotify)
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
      void menu::handle_command(const ::atom & atom)
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

         ::pointer<::menu::item>pitem = get_menu_item();

         if (!pitem)
         {

            return;

         }

         ::point_i32 pointCursorHint;
         
         ::rectangle_i32 rectangleScreenHint;

         if (get_parent() == nullptr)
         {

            information() << "menu::on_perform_top_down_layout top level menu";

            if (m_bCursorHint)
            {
               
               pointCursorHint = m_pointCursorHint;
               
            }
            else
            {

               auto pointCursor = mouse_cursor_position();

               pointCursorHint = pointCursor;

            }
            
            if(m_bScreenHint)
            {
               
               rectangleScreenHint = m_rectangleScreenHint;
               
            }
            else
            {
               
               if(m_puserinteractionOwner)
               {
                  
                  rectangleScreenHint = m_puserinteractionOwner->window_rectangle();
                  
               }
               else
               {
                  
                  rectangleScreenHint.set_square_with_center(pointCursorHint, 8);
                  
               }
               
            }

            m_pointTrack = m_rectangleScreenHint.center();

            if (get_parent() != nullptr)
            {

               get_parent()->screen_to_client()(m_pointTrack);

            }

         }
         else
         {

            information() << "menu::on_perform_top_down_layout child menu";

         }
         
         rectangleScreenHint = m_rectangleScreenHint;

         //auto psystem = system()->m_paurasystem;

         //auto pdraw2d = psystem->draw2d();

         auto pstyle = m_puserinteractionOwner->get_style(pgraphics);

         pgraphics->set(get_font(pstyle));

         auto metrics = pgraphics->get_text_metrics();

         auto dMaxHeight = metrics.get_line_height();

         m_dItemHeight = dMaxHeight;

         m_dCheckBoxSize = dMaxHeight;

         m_dHeaderHeight = dMaxHeight;

         ::pointer<::menu::item_ptra>pmenuitema = pitem->m_pmenuitema;

         auto rectangleMargin = get_margin(pstyle);

         auto rectangleBorder = get_border(pstyle);

         auto rectanglePadding = get_padding(pstyle);

         //int iElementPadding = rectanglePadding.left();

         int x = (int)(rectangleMargin.left() + rectangleBorder.left() + rectanglePadding.left());

         int y = (int)(rectangleMargin.top() + rectangleBorder.top() + rectanglePadding.top());

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

         ::collection::index iColumn = 0;

         ::i32 iMaximumButtonHeight = 0;

         // Calculate buttons sizes

         for (i32 i = 0; i < pmenuitema->get_size(); i++)
         {

            auto pmenuitem = pmenuitema->element_at(i);

            if(pmenuitem->is_separator())
            {

               continue;

            }

            auto puserinteraction = pmenuitem->m_puserinteraction;



            string strButtonText = puserinteraction->get_window_text();

            if (puserinteraction)
            {

               size = puserinteraction->get_preferred_size(pgraphics);

               information() << "button text and size : \"" << strButtonText << "\", " << size;

               pmenuitem->m_rectangleUi.left() = 0;
               pmenuitem->m_rectangleUi.top() = 0;
               pmenuitem->m_rectangleUi.set_size(size);

               iMaximumButtonHeight = maximum(iMaximumButtonHeight, size.cy());

            }

         }

         ::i32 iSeparatorHeight = iMaximumButtonHeight / 3;

         ::i32 iRow = 0;

         for (i32 i = 0; i < pmenuitema->get_size(); i++)
         {

            auto pmenuitem = pmenuitema->element_at(i);

            pmenuitem->m_rectangleUi.move_to(x, y);

            size = pmenuitem->m_rectangleUi.size();

            if (!pmenuitem->m_puserinteraction)
            {

               pmenuitem->m_rectangleUi.set_height(iSeparatorHeight);

               size.cy() = iSeparatorHeight;

            }

            pmenuitem->m_iColumn = (::i32) iColumn;

            pmenuitem->m_iRow = iRow;

            y += size.cy();

            if (size.cx() > m_iaColumnWidth[iColumn])
            {

               m_iaColumnWidth[iColumn] = size.cx();

            }

            m_iaColumnHeight[iColumn] = y;

            iRow++;

            if (pmenuitema->element_at(i)->m_bBreak)
            {

               x += m_iaColumnWidth[iColumn];

               y = yClose;

               iColumn++;

               iRow = 0;

               m_iaColumnWidth.add(0);

               m_iaColumnHeight.add(yClose);

               iColumn = m_iaColumnWidth.get_upper_bound();

            }

         }

         for (i32 i = 0; i < pmenuitema->get_size(); i++)
         {

            auto pmenuitem = pmenuitema->element_at(i);

            if (!pmenuitem->m_puserinteraction)
            {

               pmenuitem->m_rectangleUi.set_width(m_iaColumnWidth[pmenuitem->m_iColumn]);

            }

         }

         //::size_i32 sizeSeparator;

         //for (i32 i = 0; i < pmenuitema->get_size(); i++)
         //{

         //   string strButtonText = pmenuitema->element_at(i)->m_puserinteraction->get_window_text();

         //   pmenuitema->element_at(i)->m_iColumn = (int)iColumn;

         //   auto puserinteraction = pmenuitema->element_at(i)->m_puserinteraction;

         //   if (puserinteraction)
         //   {

         //      size = pmenuitema->element_at(i)->m_puserinteraction->get_preferred_size(pgraphics);

         //      information() << "button text and size : \"" << strButtonText << "\", " << size;

         //      if (sizeSeparator.is_empty())
         //      {

         //         sizeSeparator.cx() = 

         //         sizeSeparator.cy() = size.cy() / 2;

         //      }

         //   }
         //   else
         //   {


         //   }

         //   pmenuitema->element_at(i)->m_rectangleUi.left() = x;
         //   pmenuitema->element_at(i)->m_rectangleUi.right() = x + size.cx();
         //   pmenuitema->element_at(i)->m_rectangleUi.top() = y;
         //   pmenuitema->element_at(i)->m_rectangleUi.bottom() = y + size.cy();

         //   y += size.cy();

         //   m_iaColumnHeight[iColumn] = y;

         //   if (size.cx() > m_iaColumnWidth[iColumn])
         //   {

         //      m_iaColumnWidth[iColumn] = size.cx();

         //   }

         //   if (pmenuitema->element_at(i)->m_bBreak)
         //   {

         //      x += m_iaColumnWidth[iColumn];

         //      y = yClose;

         //      iColumn++;

         //      m_iaColumnWidth.add(0);

         //      m_iaColumnHeight.add(yClose);

         //      iColumn = m_iaColumnWidth.get_upper_bound();

         //   }

         //}

         m_size.cx() = (int)(m_iaColumnWidth.get_sum()
                     + rectangleMargin.left() + rectangleMargin.right()
                     + rectangleBorder.left() + rectangleBorder.right()
                     + rectanglePadding.left() + rectanglePadding.right());

         m_size.cy() = (int)(m_iaColumnHeight.get_maximum_value()
                     + rectangleMargin.top() + rectangleMargin.bottom()
                     + rectangleBorder.top() + rectangleBorder.bottom()
                     + rectanglePadding.top() + rectanglePadding.bottom());

         m_size.cx() = maximum(m_sizeMinimum.cx(), m_size.cx());

         m_size.cy() = maximum(m_sizeMinimum.cy(), m_size.cy());

         ::collection::count iItemCount = pmenuitema->get_size();

         ::pointer<::base::style>pbasestyle = pstyle;

         for (i32 i = 0; i < iItemCount; i++)
         {

            ::menu::item * pitem = pmenuitema->element_at(i);

            pmenuitema->element_at(i)->m_rectangleUi.right() =
               pmenuitema->element_at(i)->m_rectangleUi.left() + m_iaColumnWidth[pitem->m_iColumn];

            if (pitem->is_separator())
            {

               continue;

            }

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

         if (get_parent() == nullptr)
         {

            ::rectangle_i32 rectangleWindow;

            rectangleWindow.left() = pointCursorHint.x();
            rectangleWindow.top() = rectangleScreenHint.bottom();
            rectangleWindow.right() = rectangleWindow.left() + m_size.cx();
            rectangleWindow.bottom() = rectangleWindow.top() + m_size.cy();

            ::rectangle_i32 rectangleMonitor;

            auto iMonitor = get_best_monitor(&rectangleMonitor, rectangleWindow);

            if (iMonitor >= 0)
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

            place(rectangleWindow, ::user::e_layout_layout, pgraphics);

            //display(e_display_normal, e_activation_no_activate);


         }
         else
         {

            set_size(m_size, ::user::e_layout_layout, pgraphics);

         }

         m_bMenuOk = true;

      }


//   bool menu::create_buttons(::draw2d::graphics_pointer & pgraphics)
//   {
//
//      ::user::style_pointer pstyle;
//
//      for (i32 iItem = 0; iItem < m_pmenuitem->m_pmenuitema->get_size(); iItem++)
//      {
//
//         auto pitem = m_pmenuitem->m_pmenuitema->element_at(iItem);
//         
//         if (!pitem)
//         {
//
//            continue;
//
//         }
//
//         if (pitem->is_separator())
//         {
//
//            continue;
//
//         }
//
//         ::pointer<::user::interaction>pinteraction = pitem->m_puserinteraction;
//
//         if (pinteraction.is_null())
//         {
//
//            pinteraction = create_menu_button(pgraphics, pitem);
//
//         }
//
//         if (pinteraction.is_null())
//         {
//
//            return false;
//
//         }
//
//         if (pinteraction->is_window())
//         {
//
//            pinteraction->start_destroying_window();
//
//         }
//
//         pinteraction->create_control(this, pitem->m_atom);
//
//         //if (!pinteraction->create_control(pmenu, pitem->m_atom))
//         //{
//
//         //   return false;
//
//         //}
//
//         pinteraction->m_pmenuitem = pitem;
//
//         if (!pinteraction->is_window())
//         {
//
//            return false;
//
//         }
//
//         //pitem->m_pmenu = this;
//
//         pinteraction->set_window_text(pitem->m_strTitle);
//
//         if(m_bInline)
//         {
//
//            if(pitem->m_pmenu)
//            
//            create_buttons(pgraphics);
//
//         }
//
//         pitem->m_puserinteraction = pinteraction;
//
//      }
//
//      return true;
//
//   }


} // namespace user



