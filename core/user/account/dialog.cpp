#include "framework.h"
#include "login.h"
#include "dialog.h"
#include "acme/constant/user_message.h"
#include "acme/constant/user_key.h"
#include "acme/constant/timer.h"
#include "acme/parallelization/synchronous_lock.h"
#include "acme/platform/hyperlink.h"
#include "acme/platform/timer.h"
#include "aura/graphics/image/context.h"
#include "aura/windowing/windowing.h"
#include "aura/windowing/display.h"
#include "aura/message/user.h"
#include "aura/user/user/plain_edit.h"
#include "axis/account/credentials.h"
#include "axis/account/department.h"
#include "core/platform/application.h"
#include "core/platform/session.h"


namespace account
{


   dialog::dialog()
   {

      //m_etheme = ::user::e_theme_lite;

      m_bLButtonDown = false;

      m_bFontopusSimpleUiLayout = false;


   }


   dialog::~dialog()
   {


   }


   void dialog::initialize_account_dialog(::account::credentials * pcredentials)
   {

      //auto estatus =
      
      
      initialize(pcredentials);

      //if (!estatus)
      //{

      //   return estatus;

      //}

      //estatus = 
      
      m_pcredentials = pcredentials;

      //if (!estatus)
      //{

      //   return estatus;

      //}

      //estatus = 
      
      øconstruct_new(m_plogin);

      //if (!estatus)
      //{

      //   return estatus;

      //}

      //return estatus;

   }


   void dialog::install_message_routing(::channel * pchannel)
   {

      ::user::interaction::install_message_routing(pchannel);

      USER_MESSAGE_LINK(::user::e_message_create,pchannel,this,&dialog::on_message_create);
      USER_MESSAGE_LINK(::user::e_message_char,pchannel,this,&dialog::on_message_character);
      USER_MESSAGE_LINK(::user::e_message_left_button_down,pchannel,this,&dialog::on_message_left_button_down);
      USER_MESSAGE_LINK(::user::e_message_left_button_up,pchannel,this,&dialog::on_message_left_button_up);
      USER_MESSAGE_LINK(::user::e_message_mouse_move,pchannel,this,&dialog::on_message_mouse_move);
      USER_MESSAGE_LINK(::user::e_message_show_window, pchannel, this, &dialog::on_message_show_window);

   }


   void dialog::on_message_create(::message::message * pmessage)
   {

      ::pointer<::message::create>pcreate(pmessage);

      if(pcreate->previous())
      {

         return;

      }

      m_plogin->create_child(this);

      //if(!m_plogin->create_child(this))
      //{

      //   pcreate->m_lresult = -1;

      //   pcreate->m_bRet = true;

      //   return;

      //}

      string strUser;

      string strPass;

      string strOpen;

      //strUser = lstr("account::login::email","e-mail");

      //strPass = lstr("account::login::password","password");

      //strOpen = lstr("account::login::open","open");

      m_plogin->defer_translate(strUser,strPass,strOpen);

   }


   void dialog::on_message_character(::message::message * pmessage)
   {

      auto pkey = pmessage->m_union.m_pkey;

      if(pkey->m_ekey == ::user::e_key_return)
      {

         m_plogin->on_action("submit");

         pmessage->m_bRet = true;

      }
      else if(pkey->m_ekey == ::user::e_key_escape)
      {

         m_plogin->on_action("escape");

         pmessage->m_bRet = true;

      }

   }


   void dialog::on_timer(::timer * ptimer)
   {

      ::user::interaction::on_timer(ptimer);

      if(ptimer->m_uTimer == e_timer_check_cached_credentials)
      {

         try
         {

            if (m_plogin->m_bSubmitted)
            {

               kill_timer(e_timer_check_cached_credentials);

            }
            else
            {

               ::pointer<::account::credentials>pcredentials;

               {

                  synchronous_lock slInteractive(m_pcredentials->synchronization(), DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);

                  pcredentials = øallocate ::account::credentials(*m_pcredentials);

               }

               pcredentials->m_estatus = pcredentials->load_from_storage(1);

               if (pcredentials->m_estatus == ::success_credentials
                  || pcredentials->m_estatus == ::success_authenticated)
               {

                  pcredentials->m_estatus = ::success_credentials;

                  kill_timer(e_timer_check_cached_credentials);

                  m_plogin->on_action("submit_timer");

               }

            }

         }
         catch(...)
         {

         }

         m_iDelay++;

         if (m_iDelay >= 6 && !is_window_visible())
         {

            order(e_zorder_top);

            place(m_rectangleFontopus);

            m_plogin->m_peditUser->set_keyboard_focus();

            display(e_display_normal, { ::user::e_activation_set_foreground });

            set_need_redraw();

            post_redraw();

         }

      }

   }


   void dialog::do_modal(::int_rectangle rectangle)
   {

      m_iDelay = 0;

      m_pcredentials->m_iPasswordOriginalLength = -1;

      m_pcredentials->m_estatus = error_credentials;

      auto psession = session();

      ::user::interaction * puiParent = psession->cast < ::user::interaction > ("plugin_parent");

      ::int_rectangle rectangleDesktop;

      if(puiParent != nullptr)
      {

         puiParent->window_rectangle(rectangleDesktop);

      }
      else if (rectangle.is_empty())
      {

         auto pwindowing = windowing();

         auto pdisplay = pwindowing->display();

         pdisplay->get_main_monitor(rectangleDesktop);

      }
      else
      {

         rectangleDesktop = rectangle;

      }

      ::int_rectangle rectangleLogin;

      int stdw = 800;

      int stdh = 400;

      int w = stdw;

      int h = stdh;

      if(w > rectangleDesktop.width())
      {

         w = rectangleDesktop.width();

      }

      if(h > rectangleDesktop.height())
      {

         h = rectangleDesktop.height();

      }

      ::int_rectangle rectangleFontopus;

      rectangleFontopus.left() = rectangleDesktop.left() + (rectangleDesktop.width() - w) / 2;

      rectangleFontopus.top() = rectangleDesktop.top() + (rectangleDesktop.height() - h) / 3;

      rectangleFontopus.right() = rectangleFontopus.left() + w;

      rectangleFontopus.bottom() = rectangleFontopus.top() + h;

      if (puiParent != nullptr)
      {

         puiParent->screen_to_client()(rectangleFontopus);

      }

      if((rectangleFontopus.width() < 300 || rectangleFontopus.height() < 300) && puiParent != nullptr)
      {

         ::pointer<::apex::application>papp = puiParent->get_app();

         if(papp != nullptr)
         {

            auto phyperlink = øcreate_new < ::hyperlink >();

            phyperlink->m_strLink = "ca2account:this";

            phyperlink->run();

            sleep(5000_ms);

         }
         else
         {

            auto phyperlink = øcreate_new < ::hyperlink >();

            phyperlink->m_strLink = "ca2account:this";

            phyperlink->run();

         }

         return;

      }

#if !MOBILE_PLATFORM

      single_lock synchronouslock(&psession->account()->m_semaphoreDialog);

      bool bWasWaiting = false;

      while (!synchronouslock.wait(1_s))
      {

         preempt();

         bWasWaiting = true;

      }

      if (bWasWaiting)
      {

         if (!task_sleep(5000_ms))
         {

            return;

         }

      }

#endif

      // auto pusersystem = øallocate ::user::system(rectangleFontopus);
      create_child(puiParent);
      //if(!create_child(puiParent))
      //{

      //   return;

      //}

      m_rectangleFontopus = rectangleFontopus;

      set_window_text("account Auth Windows");

      set_timer(e_timer_check_cached_credentials, 5_min);

      auto result = wait_for_dialog_result();

      if(result == "ok")
      {

         string strUser;

         strUser = m_plogin->m_peditUser->as_text();

         string strPass;

         strPass = m_plogin->m_peditPassword->as_text();

         m_pcredentials->m_puser->m_strLogin = strUser;

         m_pcredentials->m_strPassword = strPass;

         m_pcredentials->m_iPasswordOriginalLength = m_plogin->m_iPasswordOriginalLength;

         if(m_pcredentials->m_puser->m_strLogin.has_character()
               && m_pcredentials->m_strPassword.has_character()
               && m_pcredentials->m_iPasswordOriginalLength > 0)
         {

            m_pcredentials->m_estatus = ::success_credentials;

         }
         else
         {

            m_pcredentials->m_estatus = error_credentials_invalid;

         }

      }
      else if(result == "cancel")
      {

         m_pcredentials->m_estatus = error_credentials_user_cancelled;

      }
      else
      {

         m_pcredentials->m_estatus = error_credentials;

      }

   }


   void dialog::get_credentials()
   {

      auto pcredentials = m_pcredentials;

      auto psession = session();

      ::pointer<::core::application>papp = get_app();

      if(pcredentials->m_strTitle == "ca2")
      {

         m_plogin->m_bCred = false;

         m_plogin->m_strCred = "";

      }
      else
      {

         m_plogin->m_bCred = true;

         string_array_base stra;

         stra.explode("|", pcredentials->m_strTitle);

         if (stra.get_size() >= 2)
         {

            m_plogin->m_pimage = image()->load_matter_image(stra[0]);

            m_plogin->m_strCred = stra.implode("|", 1);

         }
         else
         {

            m_plogin->m_strCred = pcredentials->m_strTitle;

         }

      }

      do_modal(pcredentials->m_rectangleDialog);

   }


   void dialog::on_layout(::draw2d::graphics_pointer & pgraphics)
   {

      auto rectangleX = this->rectangle();

      if(rectangleX.is_empty())
      {

         return;

      }

      rectangleX = this->rectangle();

      ::user::interaction::on_layout(pgraphics);

      m_plogin->place(rectangleX);

      m_plogin->display(::e_display_normal);

   }


   void dialog::on_message_left_button_down(::message::message * pmessage)
   {

      auto pmouse = pmessage->m_union.m_pmouse;

      if (pmessage->previous())
      {

         return;

      }

      get_wnd()->show_software_keyboard(this);

      m_bLButtonDown = true;

      m_bDrag = false;

      auto point = pmouse->m_pointHost;

      host_to_client()(point);

      m_pointLButtonDown = point;

      m_pointLButtonDownPos = m_pointLButtonDown;

      screen_to_client()(m_pointLButtonDownPos);

      set_mouse_capture();

      pmouse->m_bRet = true;

   }


   void dialog::on_message_left_button_up(::message::message * pmessage)
   {

      m_bLButtonDown = false;

      auto pmouse = pmessage->m_union.m_pmouse;
//
//auto pwindowing = windowing();
//
      defer_release_mouse_capture();

      m_bDrag = false;

      if (pmouse->previous())
      {

         return;

      }

      pmessage->m_bRet = true;

   }


   void dialog::on_message_mouse_move(::message::message * pmessage)
   {

      auto pmouse = pmessage->m_union.m_pmouse;

      if (m_bLButtonDown)
      {

         if (!m_bDrag)
         {

            m_bDrag = true;

            auto pointNow = pmouse->m_pointHost;

            host_to_client()(pointNow);

            ::int_point point;

            point.x = pointNow.x - m_pointLButtonDownPos.x;

            point.y = pointNow.y - m_pointLButtonDownPos.y;

            set_position(point);

            m_bDrag = false;

         }

         pmessage->m_bRet = true;

      }
      else
      {

         if (pmessage->previous())
         {

            return;

         }

         pmessage->m_bRet = true;

      }

   }


   void dialog::on_message_show_window(::message::message * pmessage)
   {

      ::pointer<::message::show_window>pshowwindow(pmessage);

auto pwindowing = windowing();

      if (pshowwindow->m_bShow)
      {

         pwindowing->lock_set_foreground_window();

      }
      else
      {

         pwindowing->lock_set_foreground_window(false);

      }


   }


   void dialog::_000OnDraw(::draw2d::graphics_pointer & pgraphics)
   {

      ::user::interaction::_000OnDraw(pgraphics);

   }


   void dialog::_001DrawChildren(::draw2d::graphics_pointer & pgraphics)
   {

      ::user::interaction::_001DrawChildren(pgraphics);

   }


   //bool dialog::has_pending_graphical_update()
   //{

   //   return is_window_visible();

   //}


} // namespace account



