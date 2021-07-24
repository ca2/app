#include "framework.h"
#include "core/user/account/_account.h"
#include "acme/const/timer.h"


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


   ::e_status dialog::initialize_account_dialog(::account::credentials * pcredentials)
   {

      auto estatus = initialize(pcredentials);

      if (!estatus)
      {

         return estatus;

      }

      estatus = __refer(m_pcredentials, pcredentials);

      if (!estatus)
      {

         return estatus;

      }

      estatus = __compose_new(m_plogin);

      if (!estatus)
      {

         return estatus;

      }

      return estatus;

   }


   void dialog::install_message_routing(::channel * pchannel)
   {

      ::user::interaction::install_message_routing(pchannel);

      MESSAGE_LINK(e_message_create,pchannel,this,&dialog::on_message_create);
      MESSAGE_LINK(e_message_char,pchannel,this,&dialog::on_message_character);
      MESSAGE_LINK(e_message_left_button_down,pchannel,this,&dialog::on_message_left_button_down);
      MESSAGE_LINK(e_message_left_button_up,pchannel,this,&dialog::on_message_left_button_up);
      MESSAGE_LINK(e_message_mouse_move,pchannel,this,&dialog::on_message_mouse_move);
      MESSAGE_LINK(e_message_show_window, pchannel, this, &dialog::on_message_show_window);

   }


   void dialog::on_message_create(::message::message * pmessage)
   {

      __pointer(::message::create) pcreate(pmessage);

      if(pcreate->previous())
      {

         return;

      }

      if(!m_plogin->create_child(this))
      {

         pcreate->m_lresult = -1;

         pcreate->m_bRet = true;

         return;

      }

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

      auto pkey = pmessage->m_pkey;

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


   void dialog::_001OnTimer(::timer * ptimer)
   {

      ::user::interaction::_001OnTimer(ptimer);

      if(ptimer->m_uEvent == e_timer_check_cached_credentials)
      {

         try
         {

            if (m_plogin->m_bSubmitted)
            {

               KillTimer(e_timer_check_cached_credentials);

            }
            else
            {

               __pointer(::account::credentials) pcredentials;

               {

                  synchronous_lock slInteractive(m_pcredentials->mutex());

                  pcredentials = __new(::account::credentials(*m_pcredentials));

               }

               pcredentials->m_estatus = pcredentials->load_from_storage(1);

               if (pcredentials->m_estatus == ::success_credentials
                  || pcredentials->m_estatus == ::success_authenticated)
               {

                  pcredentials->m_estatus = ::success_credentials;

                  KillTimer(e_timer_check_cached_credentials);

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

            place(m_rectFontopus);

            m_plogin->m_peditUser->set_keyboard_focus();

            display(e_display_restore, e_activation_set_foreground);

            set_need_redraw();

            post_redraw();

         }

      }

   }


   void dialog::do_modal(::rectangle_i32 rectangle)
   {

      m_iDelay = 0;

      m_pcredentials->m_iPasswordOriginalLength = -1;

      m_pcredentials->m_estatus = error_credentials;

      __pointer(::core::session) psession = get_session();

      ::user::interaction * puiParent = psession->cast < ::user::interaction > ("plugin_parent");

      ::rectangle_i32 rectDesktop;

      if(puiParent != nullptr)
      {

         puiParent->get_window_rect(rectDesktop);

      }
      else if (rectangle.is_empty())
      {

         auto puser = psession->user();

         auto pwindowing = puser->windowing();

         auto pdisplay = pwindowing->display();

         pdisplay->get_main_monitor(rectDesktop);

      }
      else
      {

         rectDesktop = rectangle;

      }

      ::rectangle_i32 rectLogin;

      int stdw = 800;

      int stdh = 400;

      int w = stdw;

      int h = stdh;

      if(w > rectDesktop.width())
      {

         w = rectDesktop.width();

      }

      if(h > rectDesktop.height())
      {

         h = rectDesktop.height();

      }

      ::rectangle_i32 rectFontopus;

      rectFontopus.left = rectDesktop.left + (rectDesktop.width() - w) / 2;

      rectFontopus.top = rectDesktop.top + (rectDesktop.height() - h) / 3;

      rectFontopus.right = rectFontopus.left + w;

      rectFontopus.bottom = rectFontopus.top + h;

      if (puiParent != nullptr)
      {

         puiParent->screen_to_client(rectFontopus);

      }

      if((rectFontopus.width() < 300 || rectFontopus.height() < 300) && puiParent != nullptr)
      {

         __pointer(::application) papp = puiParent->get_application();

         if(papp != nullptr)
         {

            auto phyperlink = __create_new < ::hyperlink >();

            phyperlink->m_strLink = "ca2account:this";

            phyperlink->run();

            sleep(5000_ms);

         }
         else
         {

            auto phyperlink = __create_new < ::hyperlink >();

            phyperlink->m_strLink = "ca2account:this";

            phyperlink->run();

         }

         return;

      }

#if !MOBILE_PLATFORM

      single_lock synchronouslock(&psession->account()->m_semaphoreDialog);

      bool bWasWaiting = false;

      while (!synchronouslock.wait(one_second()).signaled())
      {

         if (!::task_get_run())
         {

            return;

         }

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

      // auto pusersystem = __new(::user::system(rectFontopus));

      if(!create_child(puiParent))
      {

         return;

      }

      m_rectFontopus = rectFontopus;

      set_window_text("account Auth Windows");

      set_timer(e_timer_check_cached_credentials, millis(300));

      auto result = RunModalLoop();

      if(result == "ok")
      {

         string strUser;

         m_plogin->m_peditUser->_001GetText(strUser);

         string strPass;

         m_plogin->m_peditPassword->_001GetText(strPass);

         m_pcredentials->m_puser->m_strLogin = strUser;

         m_pcredentials->m_strPassword = strPass;

         m_pcredentials->m_iPasswordOriginalLength = m_plogin->m_iPasswordOriginalLength;

         if(m_pcredentials->m_puser->m_strLogin.has_char()
               && m_pcredentials->m_strPassword.has_char()
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

      __pointer(::core::session) psession = get_session();

      __pointer(::core::application) papplication = get_application();

      if(pcredentials->m_strTitle == "ca2")
      {

         m_plogin->m_bCred = false;

         m_plogin->m_strCred = "";

      }
      else
      {

         m_plogin->m_bCred = true;

         string_array stra;

         stra.explode("|", pcredentials->m_strTitle);

         if (stra.get_size() >= 2)
         {

            auto pcontext = m_pcontext->m_pauracontext;

            auto pcontextimage = pcontext->context_image();

            m_plogin->m_pimage = pcontextimage->load_matter_image(stra[0]);

            m_plogin->m_strCred = stra.implode("|", 1);

         }
         else
         {

            m_plogin->m_strCred = pcredentials->m_strTitle;

         }

      }

      do_modal(pcredentials->m_rectDialog);

   }


   void dialog::on_layout(::draw2d::graphics_pointer & pgraphics)
   {

      auto rectangleClient = get_client_rect();

      if(rectangleClient.is_empty())
      {

         return;

      }

      get_client_rect(rectangleClient);

      ::user::interaction::on_layout(pgraphics);

      m_plogin->place(rectangleClient);

      m_plogin->display(::e_display_normal);

   }


   void dialog::on_message_left_button_down(::message::message * pmessage)
   {

      auto pmouse = pmessage->m_pmouse;

      if (pmessage->previous())
      {

         return;

      }

      get_wnd()->show_keyboard(false);

      m_bLButtonDown = true;

      m_bDrag = false;

      m_pointLButtonDown = pmouse->m_point;

      m_pointLButtonDownPos = m_pointLButtonDown;

      screen_to_client(m_pointLButtonDownPos);

      set_mouse_capture();

      pmouse->m_bRet = true;

   }


   void dialog::on_message_left_button_up(::message::message * pmessage)
   {

      m_bLButtonDown = false;

      auto pmouse = pmessage->m_pmouse;

      auto psession = get_session();

      auto puser = psession->user();

      auto pwindowing = puser->windowing();

      pwindowing->release_mouse_capture();

      m_bDrag = false;

      if (pmouse->previous())
      {

         return;

      }

      pmessage->m_bRet = true;

   }


   void dialog::on_message_mouse_move(::message::message * pmessage)
   {

      auto pmouse = pmessage->m_pmouse;

      if (m_bLButtonDown)
      {

         if (!m_bDrag)
         {

            m_bDrag = true;

            const point_i32 & pointNow = pmouse->m_point;

            ::point_i32 point;

            point.x = pointNow.x - m_pointLButtonDownPos.x;

            point.y = pointNow.y - m_pointLButtonDownPos.y;

            move_to(point);

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

      __pointer(::message::show_window) pshowwindow(pmessage);

      auto psession = get_session();

      auto puser = psession->user();

      auto pwindowing = puser->windowing();

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


   bool dialog::has_pending_graphical_update()
   {

      return is_window_visible();

   }


} // namespace account



