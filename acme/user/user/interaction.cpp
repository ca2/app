//
// // Created from micro::interchange by
// // camilo on 2024-10-05 16:52 <3ThomasBorregaardSorensen!!
// Created by camilo on 31/01/2022 14:32 <3ThomasBorregaardSorensen!!
// renamed interchange from interchange by camilo on
//    2024-09-26 15:37 <3ThomasBorregaardSorensen!!
// 
// // // Merged from (acme)windowing and (acme)windowing_system by
// //   camilo on 2024-10-05 11:07 <3ThomasBorregaardSorensen!!
// //   (acme)windowing_system::windowing_system
// //       ---->windowing::windowing_base
// // //       ---->micro::user
// //   (acme)windowing::window_base
// //       ---->micro::interchange
//
// //// Child merged into interaction on 2024-10-05 05:17 <3ThomasBorregaardSorensen!!
// Created by camilo on 2022-01-21 05:10 PM <3ThomasBorregaardSorensen
//
// // merged from acme::user::interaction by camilo on 
// 2024-10-05 17:59 Odense Time <3ThomasBorregaardSorensen!!
// Created by camilo on 2024-09-26 22:59 Odense Time <3ThomasBorregaardSorensen!!
//
// acme::user::interaction Created by camilo on 31/01/2022 22:42 <3ThomasBorregaardSorensen!!
// From acme::user::interaction merged at ::user::interaction by
//    camilo on 2024-0926 15:04 <3ThomasBorregaardSorensen!!
//
#include "framework.h"
//#include "button.h"
#include "interaction.h"
//#include "user.h"
#include "acme/constant/id.h"
#include "acme/filesystem/filesystem/directory_system.h"
#include "acme/filesystem/filesystem/file_system.h"
#include "acme/handler/topic.h"
#include "acme/nano/graphics/device.h"
#include "acme/nano/nano.h"
#include "acme/user/micro/elemental.h"
#include "acme/user/micro/theme.h"
#include "acme/windowing/window.h"
#include "acme/operating_system/a_system_menu.h"
#include "acme/platform/application.h"
#include "acme/platform/node.h"
//#include "acme/handler/sequence.h"
#include "acme/platform/timer_array.h"
#include "acme/platform/system.h"
#include "acme/user/user/drag.h"
#include "acme/user/user/mouse.h"
#include "acme/user/user/tool.h"
#include "acme/windowing/windowing.h"


namespace acme
{


   namespace user
   {


      interaction::interaction()
      {
         //m_bMinimizeBox = true;
         //m_bMaximizeBox = true;
         //m_bResizeable = true;
         //m_bTopMost = false;
         //m_bStartCentered = false;
         //m_bArbitraryPositioning = false;

         //m_efont = e_font_sans;
         m_uFlagsAcmeUserInteraction = 0;
         auto pitemClient = stock_item(e_element_client);

         enable_drag(pitemClient, ::user::e_zorder_back);

      }


      interaction::~interaction()
      {


      }



      //::micro::theme * interaction::nano_user_theme()
      //{

      //   return system()->acme_windowing()->nano_user_theme();

      //}


      //enum_font interaction::nano_user_font()
      //{

      //   if (m_efont != e_font_none)
      //   {

      //      return m_efont;

      //   }

      //   return nano_user_theme()->m_efont;

      //}

      ///child


      void interaction::set_focus()
      {

         acme_windowing_window()->m_pacmeuserinteractionFocus = this;

         acme_windowing_window()->redraw();

      }


      bool interaction::is_focusable()
      {

         return false;

      }



      void interaction::set_capture()
      {

         acme_windowing_window()->m_pacmeuserinteractionCapture = this;

         acme_windowing_window()->set_capture();

      }


      bool interaction::has_capture()
      {

         if (!acme_windowing_window()->has_capture())
         {

            return false;

         }

         return acme_windowing_window()->m_pacmeuserinteractionCapture == this;

      }


      void interaction::release_capture()
      {

         if (acme_windowing_window()->m_pacmeuserinteractionCapture == this)
         {

            acme_windowing_window()->m_pacmeuserinteractionCapture.release();

            acme_windowing_window()->release_capture();

         }

      }


      //void interaction::draw(::nano::graphics::device * pnanodevice)
      //{

      //   ::pointer<::nano::graphics::pen>pnanopenBorder;

      //   if (acme_windowing_window()->is_active_window())
      //   {

      //      pnanopenBorder = nano_user_theme()->m_ppenBorderFocus;

      //   }
      //   else
      //   {

      //      pnanopenBorder = nano_user_theme()->m_ppenBorder;

      //   }

      //   ::int_rectangle rectangleX;

      //   rectangleX = get_client_rectangle();

      //   pnanodevice->rectangle(rectangleX, nano_user_theme()->m_pbrushWindow, pnanopenBorder);

      //   on_draw(pnanodevice);

      //   draw_children(pnanodevice);

      //}


      //void interaction::draw_children(::nano::graphics::device * pnanodevice)
      //{

      //   for (auto & pchild : m_nanouserinteractionaChildren)
      //   {

      //      pchild->on_draw(pnanodevice);

      //   }

      //}



      //void interaction::resize_to_fit()
      //{

      //   auto pdevice = __øcreate < ::nano::graphics::device >();

      //   auto size = pdevice->get_text_extents(m_strText, nano_user_theme()->m_pfont);

      //   m_rectangle.right() = m_rectangle.left() + size.cx();

      //   m_rectangle.bottom() = m_rectangle.top() + size.cy();

      //}

//      //
//// Created by camilo on 2024-09-26 18:52 Odense Time <3ThomasBorregaardSorensen!!
////
//// acme::user::interaction Created by camilo on 31/01/2022 22:42 <3ThomasBorregaardSorensen!!
//// From acme::user::interaction merged at ::user::interaction by
////    camilo on 2024-0926 15:04 <3ThomasBorregaardSorensen!!
////
//#include "framework.h"
//#include "drag.h"
//#include "interaction.h"
//#include "acme/constant/id.h"
//#include "acme/handler/topic.h"
//#include "acme/operating_system/a_system_menu.h"
//#include "acme/platform/application.h"
//#include "acme/platform/system.h"
//#include "acme/windowing/window_base.h"
//#include "platform/node.h"
//
//
//      namespace user
//      {


         //interaction::interaction()
         //{

         //   m_bMinimizeBox = true;
         //   m_bMaximizeBox = true;
         //   m_bResizeable = true;
         //   m_bTopMost = false;
         //   m_bStartCentered = false;
         //   m_bArbitraryPositioning = false;

         //}


   /*      interaction::~interaction()
         {


         }*/


         bool interaction::is_window_zoomed()
         {

            if (!m_pacmewindowingwindow)
            {

               return false;

            }

            bool bIsWindowZoomed = acme_windowing_window()->is_window_zoomed();

            if (!bIsWindowZoomed)
            {

               return false;

            }

            return true;

         }


         //void interaction::window_minimize()
         //{

         //   if (!acme_windowing_window())
         //   {

         //      throw ::exception(error_wrong_state);

         //   }

         //   acme_windowing_window()->window_minimize();

         //}


         //void interaction::window_maximize()
         //{

         //   if (!acme_windowing_window())
         //   {

         //      throw ::exception(error_wrong_state);

         //   }

         //   acme_windowing_window()->window_maximize();

         //}


         //void interaction::window_full_screen()
         //{

         //   if (!acme_windowing_window())
         //   {

         //      throw ::exception(error_wrong_state);

         //   }

         //   acme_windowing_window()->window_full_screen();

         //}


         //void interaction::window_restore()
         //{

         //   if (!acme_windowing_window())
         //   {

         //      throw ::exception(error_wrong_state);

         //   }

         //   acme_windowing_window()->window_restore();

         //}


         //void interaction::window_close()
         //{

         //   if (!acme_windowing_window())
         //   {

         //      throw ::exception(error_wrong_state);

         //   }

         //   acme_windowing_window()->window_close();

         //}


         void interaction::_on_window_simple_action(const char * pszActionName)
         {

            ::string strActionName(pszActionName);

            if (strActionName == "minimize")
            {

               //display(e_display_iconic);

               window_minimize();

            }
            else if (strActionName == "maximize")
            {

               window_maximize();

            }
            else if (strActionName == "restore")
            {

               display(e_display_normal);

            }
            else if (strActionName == "about_box")
            {

               application()->show_about_box();

            }
            else if (strActionName == "close")
            {

               window_close();

            }
            //else if (strActionName == "***move")
            //{

            //   print_line("reaching here?!");
            //   //defer_perform_entire_reposition_process(nullptr);

            //   acme_windowing_window()->set_mouse_capture();
            //   acme_windowing_window()->m_bRepositioningWindowFromCenter = true;

            //}
            //else if (strActionName == "***size")
            //{

            //   print_line("also here");

            //   acme_windowing_window()->set_mouse_capture();
            //   acme_windowing_window()->m_bResizingWindowFromBottomRight = true;

            //   //defer_perform_entire_resizing_process(::experience::e_frame_sizing_top_left, nullptr);

            //}

         }


         ::pointer < ::operating_system::a_system_menu > interaction::create_system_menu(bool bContextual)
         {

            return nullptr;

         }


         void interaction::set_mouse_capture()
         {

            if (!acme_windowing_window())
            {

               throw ::exception(error_wrong_state);

            }

            acme_windowing_window()->set_mouse_capture();

         }


         bool interaction::is_mouse_captured()
         {

            if (!acme_windowing_window())
            {

               throw ::exception(error_wrong_state);

            }

            return acme_windowing_window()->is_mouse_captured();

         }


         bool interaction::has_mouse_capture()
         {

            if (!acme_windowing_window())
            {

               throw ::exception(error_wrong_state);

            }

            return acme_windowing_window()->has_mouse_capture();

         }


         void interaction::release_mouse_capture()
         {

            if (!acme_windowing_window())
            {

               throw ::exception(error_wrong_state);

            }

            acme_windowing_window()->release_mouse_capture();

         }



         void interaction::on_initialize_particle()
         {


         }


         void interaction::create_window()
         {
            
            auto pwindowHost = system()->acme_windowing()->get_application_host_window();
            
            if(pwindowHost)
            {
               
               ::cast <::micro::elemental > pelemental = pwindowHost->m_pacmeuserinteraction;
               
               ::cast <::micro::elemental > pelementalThis = this;
               
               if(pelemental && pelementalThis)
               {
                  
                  pelementalThis->m_bChild = true;
                  
                  pelemental->add_child(pelementalThis);
                  
                  redraw();
                  
               }
               
            }
            else
            {
               
               auto pwindow = acme_windowing_window();
               
               pwindow->create_window();
               
            }

         }


         void interaction::_create_window()
         {


         }


         void interaction::destroy_window()
         {
            
            if(m_pacmewindowingwindow)
            {

               __check_refdbg

               m_pacmewindowingwindow->destroy_window();

               __check_refdbg

            }

            __check_refdbg

            auto pchildren = ::transfer(m_pacmeuserinteractionaChildren);

            __check_refdbg

            if (pchildren)
            {

               __check_refdbg

               auto childrena = ::transfer(*pchildren);

               __check_refdbg

               for (auto & pchild : childrena)
               {

                  if (pchild)
                  {

                     try
                     {

                        __check_refdbg

                        pchild->destroy_window();

                        __check_refdbg

                     }
                     catch (...)
                     {


                     }

                     try
                     {

                        pchild.release();

                     }
                     catch (...)
                     {


                     }

                  }

               }


            }
            
            if(m_pacmeuserinteractionParent)
            {
               
               if(m_pacmeuserinteractionParent->m_pacmeuserinteractionaChildren)
               {
                
                  m_pacmeuserinteractionParent->m_pacmeuserinteractionaChildren->erase(this);
                  
               }
               
            }

//            destroy();

         }


         void interaction::SetTimer(uptr uEvent, const class ::time & timeEllapse, PFN_TIMER pfnTimer, bool bPeriodic, void * pdata)
         {

            if (timeEllapse < 500_ms)
            {

               //         string str;
               //
               //         str.formatf("creating fast timer: %d\n", nEllapse);
               //
               //         ::information(str);

            }

            if (m_ptimerarray.is_null())
            {

               __construct_new(m_ptimerarray);

               m_ptimerarray->m_pcallback = this;

               //m_ptimerarray->set_context_thread(m_puserinteraction->m_pthreadUserInteraction);

            }

            m_ptimerarray->create_timer(this, uEvent, timeEllapse, pfnTimer, bPeriodic, pdata);

         }


         void interaction::KillTimer(uptr uEvent)
         {

            if (m_ptimerarray.is_null())
            {

               return;

            }

            m_ptimerarray->delete_timer(uEvent);

         }





         void interaction::show()
         {



         }


         void interaction::hide()
         {


         }


         //void interaction::create()
         //{


         //}


         //void interaction::show_window()
         //{


         //}


   /*      void interaction::hide_window()
         {


         }*/


         //void interaction::message_loop()
         //{


         //}


         void interaction::implementation_message_loop_step()
         {


         }


         //::payload interaction::do_synchronously(const class time & timeWait)
         //{

         //   do_asynchronously();

         //   auto pmanualresethappening = __allocate manual_reset_happening();

         //   if (m_psequencer)
         //   {

         //      m_psequencer->then([pmanualresethappening](auto psequencer)
         //      {

         //            pmanualresethappening->set_happening();

         //      });

         //   }
         //   else
         //   {

         //      auto pwindow = acme_windowing_window();

         //      auto functionCloseExisting = pwindow->m_functionClose;

         //      pwindow->m_functionClose = [pmanualresethappening, functionCloseExisting](auto pinterchange)
         //         {

         //            if (functionCloseExisting)
         //            {

         //               functionCloseExisting(pinterchange);

         //            }

         //            pmanualresethappening->set_happening();

         //         };

         //   }

         //   if (m_payloadResult.is_new())
         //   {

         //      pmanualresethappening->wait();

         //   }

         //   return m_payloadResult;

         //}


         //void interaction::draw(::nano::graphics::device * pnanodevice)
         //{


         //}


         //void interaction::on_draw(::nano::graphics::device * pnanodevice)
         //{


         //}


         //void interaction::on_char(int iChar)
         //{

         //   if (iChar == '\t' && m_nanouserinteractionaChildren.has_element())
         //   {

         //      auto iFind = m_nanouserinteractionaChildren.find_first(acme_windowing_window()->m_pacmeuserinteractionFocus);

         //      iFind++;

         //      acme_windowing_window()->m_pacmeuserinteractionFocus = m_nanouserinteractionaChildren % iFind;

         //      redraw();

         //   }
         //   else if (acme_windowing_window()->m_pacmeuserinteractionFocus)
         //   {

         //      acme_windowing_window()->m_pacmeuserinteractionFocus->on_char(iChar);

         //   }

         //}


         //::acme::user::interaction * interaction::hit_test(::user::mouse * pmouse, ::user::e_zorder ezorder)
         //{

         //   auto point = pmouse->m_pointHost;

         //   host_to_client()(point);

         //   return on_hit_test(point, ezorder);

         //}



         //::acme::user::interaction * interaction::on_hit_test(const ::int_point & point, ::user::e_zorder ezorder)
         //{

         //   for (auto & pchild : m_nanouserinteractionaChildren)
         //   {

         //      if (pchild->m_rectangle.contains(point))
         //      {

         //         return pchild;

         //      }

         //   }

         //   return nullptr;

         //}


         //void interaction::add_child(::acme::user::interaction * pinteractionChild)
         //{

         //   pinteractionChild->m_pacmeuserinteractionParent = this;

         //   m_nanouserinteractionaChildren.add(pinteractionChild);

         //}


         //void interaction::add_button(const ::scoped_string & scopedstrText, enum_dialog_result edialogresult, char chLetter)
         //{

         //   auto pbutton = __allocate ::micro::button();

         //   pbutton->m_strText = scopedstrText;
         //   pbutton->m_atom = edialogresult;
         //   pbutton->m_edialogresult1 = edialogresult;
         //   pbutton->m_chLetter = chLetter;
         //   //pbutton->m_bDefault = bDefault;

         //   m_nanouserinteractionaChildren.add(pbutton);

         //   add_child(pbutton);

         //}



         //::acme::user::interaction * interaction::get_child_by_id(const ::atom & atom)
         //{

         //   for (auto & pchild : m_nanouserinteractionaChildren)
         //   {

         //      if (pchild->m_atom == atom)
         //      {

         //         return pchild;

         //      }

         //   }

         //   return nullptr;

         //}


         //::payload interaction::get_result()
         //{

         //   return m_payloadResult;

         //}


         //void interaction::on_mouse_move(::user::mouse * pmouse)
         //{

         //   if (acme_windowing_window()->m_pacmeuserinteractionHover)
         //   {

         //      acme_windowing_window()->m_pacmeuserinteractionHover->on_mouse_move(pmouse);

         //      return;

         //   }

         //   if (acme_windowing_window()->m_pacmeuserinteractionCapture)
         //   {

         //      acme_windowing_window()->m_pacmeuserinteractionCapture->on_mouse_move(pmouse);

         //      return;

         //   }

         //   if (drag_on_mouse_move(pmouse))
         //   {

         //      return;

         //   }

         //   auto pchild = hit_test(pmouse, ::user::e_zorder_any);

         //   if (pchild)
         //   {

         //      pchild->on_mouse_move(pmouse);

         //   }

         //}


         //void interaction::on_left_button_down(::user::mouse * pmouse)
         //{

         //   auto pchild = hit_test(pmouse, ::user::e_zorder_any);

         //   if (pchild)
         //   {

         //      m_atomLeftButtonDown = pchild->m_atom;

         //   }
         //   else
         //   {

         //      m_atomLeftButtonDown = e_dialog_result_none;

         //   }

         //   auto pitemClient = tool().defer_item(e_element_client);

         //   auto pdragClient = drag(pitemClient);

         //   if (pdragClient && !pchild)
         //   {

         //      if (drag_on_button_down(pitemClient, pmouse))
         //      {

         //         return;

         //      }

         //   }

         //   if (::is_set(pchild) && pchild->is_focusable())
         //   {

         //      pchild->set_focus();

         //   }

         //}


         //void interaction::on_left_button_up(::user::mouse * pmouse)
         //{

         //   release_capture();

         //   if (drag_on_button_up(pmouse))
         //   {

         //      return;

         //   }

         //   auto pchild = hit_test(pmouse, ::user::e_zorder_any);

         //   if (pchild)
         //   {

         //      m_atomLeftButtonUp = pchild->m_atom;

         //   }
         //   else
         //   {

         //      m_atomLeftButtonUp = e_dialog_result_none;

         //   }

         //   if (m_atomLeftButtonUp == m_atomLeftButtonDown && m_atomLeftButtonUp != e_dialog_result_none)
         //   {

         //      m_payloadResult = m_atomLeftButtonUp;

         //      on_click(m_payloadResult, pmouse);

         //   }

         //   if (drag_on_button_up(pmouse))
         //   {

         //      return;

         //   }

         //}


         //void interaction::on_right_button_down(::user::mouse * pmouse)
         //{

         //   auto pchild = hit_test(pmouse, ::user::e_zorder_any);

         //   if (pchild)
         //   {

         //      m_atomRightButtonDown = pchild->m_atom;

         //   }
         //   else
         //   {

         //      m_atomRightButtonDown = e_dialog_result_none;

         //   }


         //   if (::is_set(pchild) && pchild->is_focusable())
         //   {

         //      pchild->set_focus();

         //   }

         //}


         //void interaction::on_right_button_up(::user::mouse * pmouse)
         //{

         //   release_capture();

         //   auto pchild = hit_test(pmouse, ::user::e_zorder_any);

         //   if (pchild)
         //   {

         //      m_atomRightButtonUp = pchild->m_atom;

         //   }
         //   else
         //   {

         //      m_atomRightButtonUp = e_dialog_result_none;

         //   }

         //   if (m_atomRightButtonUp == m_atomRightButtonDown)
         //   {

         //      on_right_click(m_atomLeftButtonUp, pmouse);

         //   }

         //}


         //void interaction::on_click(const ::payload & payload, ::user::mouse * pmouse)
         //{


         //}


         //void interaction::on_right_click(const ::payload & payload, ::user::mouse * pmouse)
         //{


         //}


         //bool interaction::is_active()
         //{

         //   return false;

         //}


         //void interaction::set_active()
         //{


         //}


         //void interaction::draw_children(::nano::graphics::device * pnanodevice)
         //{


         //}


         //void interaction::delete_drawing_objects()
         //{


         //}


         //bool interaction::get_dark_mode()
         //{

         //   return false;

         //}


  /*       void interaction::create_drawing_objects()
         {


         }*/


         //void interaction::update_drawing_objects()
         //{


         //}


         //::int_point interaction::origin()
         //{

         //   throw ::exception(error_wrong_state);

         //   return {};

         //}


         ::shift_int interaction::host_to_client()
         {

            return -client_to_host();

         }


         ::shift_int interaction::client_to_host()
         {

            return {};

         }


         ::shift_int interaction::absolute_to_client()
         {

            return -client_to_host();

         }


         ::shift_int interaction::client_to_absolute()
         {

            if (system()->acme_windowing()->get_ewindowing() == ::windowing::e_windowing_wayland)
            {

               return {};

            }

            auto r = get_window_rectangle();

            return r.top_left();

         }


         ::int_point interaction::origin()
         {
            auto r = get_window_rectangle();

            return r.top_left();

         }



         ::int_rectangle interaction::get_client_rectangle()
         {
            auto r = get_window_rectangle();

            r.offset(-r.top_left());

            return r;

         }


         //::collection::count interaction::nano_user_button_count()
         //{

         //   ::collection::count c = 0;

         //   for (auto & pnanouserinteraction : m_nanouserinteractionaChildren)
         //   {

         //      auto pbutton = pnanouserinteraction.cast < ::micro::button >();

         //      if (pbutton)
         //      {

         //         c++;

         //      }

         //   }

         //   return c;

         //}

         //::acme::user::interaction * interaction::nano_user_parent()
         //{

         //   return m_pacmeuserinteractionParent;

         //}

         //::micro::button * interaction::nano_user_button_at(::collection::index i)
         //{

         //   ::collection::count c = 0;

         //   for (auto & pnanouserinteraction : m_nanouserinteractionaChildren)
         //   {

         //      auto pbutton = pnanouserinteraction.cast < ::micro::button >();

         //      if (pbutton)
         //      {

         //         if (i == c)
         //         {

         //            return pbutton;

         //         }

         //         c++;

         //      }

         //   }

         //   return nullptr;

         //}



         //::int_point interaction::try_absolute_mouse_position(const ::int_point & point)
         //{
         //acme_windowing_window()
         //   auto p = point;

         //   client_to_absolute()(p);

         //   return p;

         //}


         void interaction::drag_set_capture()
         {

            set_capture();

         }


         bool interaction::on_drag_start(::int_point & point, ::user::mouse * pmouse, ::item * pitem)
         {

            if (pitem->m_item.m_eelement == e_element_client)
            {

               auto pdrag = drag(pitem);

               if (acme_windowing_window()->defer_perform_entire_reposition_process(pmouse))
               {

                  return false;

               }

               point = origin();

               return true;

            }

            return false;

         }


         ::int_point interaction::drag_mouse_cursor_position(::item * pitem, const ::int_point & point)
         {

            //auto p = try_absolute_mouse_position(point);

            //return p;

            return point;

         }


         bool interaction::drag_shift(::item * pitem, ::user::mouse * pmouse)
         {

            if (pitem->m_item.m_eelement == e_element_client)
            {

               auto point = drag_point(pitem, pmouse);

               set_position(point);

               return true;

            }

            return false;

         }


         bool interaction::drag_hover(::item * pitem)
         {

            if (pitem->m_item.m_eelement == e_element_client)
            {

               set_cursor(e_cursor_hand);

               return true;

            }
            else if (pitem->m_item.m_eelement == e_element_resize)
            {

               set_cursor(e_cursor_size_bottom_right);

               return true;

            }

            return false;

         }


         void interaction::drag_release_capture()
         {

            release_capture();

         }


         void interaction::drag_set_cursor(::item * pitem, ::user::mouse * pmouse)
         {

            auto pdrag = drag(pitem);

            set_cursor(pdrag->m_ecursor);

         }


      /*   ::payload interaction::get_result()
         {

            return {};

         }*/


         //void interaction::on_mouse_move(::user::mouse * pmouse)
         //{


         //}


         //void interaction::on_left_button_down(::user::mouse * pmouse)
         //{


         //}


         //void interaction::on_left_button_up(::user::mouse * pmouse)
         //{


         //}


         //void interaction::on_click(const ::payload & payload, ::user::mouse * pmouse)
         //{


         //}


         //void interaction::on_right_button_down(::user::mouse * pmouse)
         //{


         //}


         //void interaction::on_right_button_up(::user::mouse * pmouse)
         //{


         //}


         //void interaction::on_right_click(const ::payload & payload, ::user::mouse * pmouse)
         //{


         //}


         void interaction::set_position(const ::int_point & point)
         {

            acme_windowing_window()->set_position(point);

         }


         void interaction::display_temporary_file_with_text(const ::string & str)
         {

            string strAppId;

            strAppId = application()->m_strAppId;

            ::file::path pathFolder = directory_system()->home() / "application" / strAppId / "details";

            auto pathDetails = file_system()->time_put_contents(pathFolder, "details", "txt", str);

            node()->shell_open(pathDetails, "");

         }



         void interaction::destroy()
         {

            ::user::element::destroy();

            ::user::drag_client::destroy();

            ::source::destroy();

            //system()->erase_signal_handler(this);

            m_pacmeuserinteractionParent.release();

            m_pacmeuserinteractionaChildren.release();

            m_pacmewindowingwindow.release();

         }



         //void interaction::on_position_window()
         //{


         //}


         /*void interaction::on_size_window()
         {


         }*/


         void interaction::redraw()
         {
            
            auto pwindow = acme_windowing_window();

            if (pwindow)
            {

               pwindow->redraw();

            }

         }


         //void interaction::get_client_rectangle(::int_rectangle & rectangle)
         //{


         //}


         int_rectangle interaction::get_window_rectangle()
         {

            return m_pacmewindowingwindow->get_window_rectangle();

         }


         int_rectangle interaction::get_rectangle()
         {

            return {};

         }



         //void interaction::set_capture()
         //{

         //   acme_windowing_window()->set_capture();

         //}


         //bool interaction::has_capture()
         //{

         //   return acme_windowing_window()->has_capture();

         //}


         //void interaction::release_capture()
         //{


         //}


         void interaction::set_cursor(enum_cursor ecursor)
         {


         }


         void interaction::synchronize_composited_nano_window()
         {


         }


         //void interaction::_run_modal_loop()
         //{


         //}


         bool interaction::is_popup_window() const
         {

            return false;

         }


         void interaction::handle(::topic * ptopic, ::context * pcontext)
         {

            if (ptopic->m_atom == id_operating_system_user_color_change)
            {

               redraw();

            }
            else if (ptopic->m_atom == id_set_application_dark_mode)
            {

               redraw();

            }
            else if (ptopic->m_atom == id_application_dark_mode_change)
            {

               redraw();

            }

         }


         //void interaction::do_asynchronously()
         //{

         //   ::pointer<::acme::windowing::window> pwindow = acme_windowing_window();

         //   auto procedure = [pwindow]()
         //      {

         //         pwindow->create_window();

         //         pwindow->show_window();

         //      };

         //   if (is_main_thread())
         //   {

         //      procedure();

         //   }
         //   else
         //   {

         //      user_post(procedure);

         //   }

         //}



         ::acme::user::interaction * interaction::acme_user_interaction()
         {

            return this;

         }


         //::acme::windowing::window * interaction::acme_windowing_window()
         //{

         //   if (!acme_windowing_window())
         //   {

         //      if (nano_user_parent())
         //      {

         //         return nano_user_parent()->acme_windowing_window();

         //      }

         //   }

         //   return nullptr;

         //}


      void interaction::create_window_object()
      {

         on_create_window_object();

         if(m_pacmewindowingwindow)
         {

            m_pacmewindowingwindow->m_pacmeuserinteraction = this;

         }

      }


   bool interaction::is_child_interaction()
   {
      
      if(m_bChild)
      {
         
         return true;
         
      }
      
      if(system()->acme_windowing()->get_application_host_window())
      {
         
         if(system()->acme_windowing()->get_application_host_window()==m_pacmewindowingwindow)
         {
          
            return false;
            
         }
       
         return true;
         
      }
      
      return false;
      
   }

         ::acme::windowing::window * interaction::acme_windowing_window()
         {

            if (!m_pacmewindowingwindow)
            {

               if (m_pacmeuserinteractionParent)
               {

                  return m_pacmeuserinteractionParent->acme_windowing_window();

               }
               
               if(system()->acme_windowing()->get_application_host_window())
               {
                  
                  return system()->acme_windowing()->get_application_host_window();
                  
               }

               if (!is_child_interaction())
               {

                  create_window_object();

               }

            }

            return m_pacmewindowingwindow;

         }


         void interaction::on_create_window_object()
         {

            __øconstruct(m_pacmewindowingwindow, ::system()->m_pfactoryAcmeWindowing);

         }
         
         
         ::acme::user::interaction * interaction::acme_user_parent()
         {

            return m_pacmeuserinteractionParent;

         }


         void interaction::get_text_selection(character_count & iBeg, character_count & iEnd) const
         {


         }


         void interaction::get_text_selection(character_count & iBeg, character_count & iEnd, character_count & iComposingStart, character_count & iComposingEnd) const
         {


         }


         ::collection::index interaction::plain_edit_sel_to_column(::draw2d::graphics_pointer & pgraphics, character_count iSel)
         {

            return -1;

         }


         ::collection::index interaction::plain_edit_sel_to_column_x(::draw2d::graphics_pointer & pgraphics, character_count iSel, int & x)
         {

            return -1;

         }


         ::collection::index interaction::plain_edit_sel_to_line(::draw2d::graphics_pointer & pgraphics, character_count iSel)
         {

            return -1;

         }


         ::collection::index interaction::plain_edit_sel_to_line_x(::draw2d::graphics_pointer & pgraphics, character_count iSel, int & x)
         {

            return -1;

         }


         character_count interaction::plain_edit_line_column_to_sel(::draw2d::graphics_pointer & pgraphics, ::collection::index iLine, ::collection::index iColumn)
         {

            return -1;

         }


         character_count interaction::plain_edit_line_x_to_sel(::draw2d::graphics_pointer & pgraphics, ::collection::index iLine, int x)
         {

            return -1;

         }


         ::collection::index interaction::plain_edit_char_to_line(::draw2d::graphics_pointer & pgraphics, character_count iSel)
         {

            return -1;

         }


         ::trace_statement & interaction::raw_trace_statement_prefix(::trace_statement & statement) const
         {

            ::string strType = ::type(this).name();

            statement << strType;

            ::string strAtom = m_atom.as_string();

            if (strAtom.has_character() && strAtom != strType)
            {
               statement << "=" << strAtom;
            }

            statement << "  ";

            return statement;

         }





   } // namespace user


} // namespace acme



