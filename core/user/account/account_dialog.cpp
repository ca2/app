#include "framework.h"
#if !BROAD_PRECOMPILED_HEADER
#include "core/user/account/_account.h"
#endif
#include "acme/const/timer.h"


namespace account
{


   dialog::dialog()
   {

      m_etheme = ::user::theme_lite;

      m_bLButtonDown = false;

      m_bFontopusSimpleUiLayout = false;

#ifdef WINDOWS_DESKTOP

      LockSetForegroundWindow(LSFW_LOCK);

#endif

   }


   dialog::~dialog()
   {

#ifdef WINDOWS_DESKTOP

      LockSetForegroundWindow(LSFW_UNLOCK);

#endif

   }


   ::estatus dialog::initialize_account_dialog(::account::credentials * pcredentials)
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

      MESSAGE_LINK(e_message_create,pchannel,this,&dialog::_001OnCreate);
      MESSAGE_LINK(e_message_char,pchannel,this,&dialog::_001OnChar);
      MESSAGE_LINK(e_message_left_button_down,pchannel,this,&dialog::_001OnLButtonDown);
      MESSAGE_LINK(e_message_left_button_up,pchannel,this,&dialog::_001OnLButtonUp);
      MESSAGE_LINK(e_message_mouse_move,pchannel,this,&dialog::_001OnMouseMove);

   }


   void dialog::_001OnCreate(::message::message * pmessage)
   {

      SCAST_PTR(::message::create,pcreate,pmessage);

      if(pcreate->previous())
      {

         return;

      }

      if(!m_plogin->create_window(this,"pane_first"))
      {

         pcreate->m_lresult = -1;

         pcreate->m_bRet = true;

         return;

      }

      string strUser;

      string strPass;

      string strOpen;

      strUser = lstr("account::login::email","e-mail");

      strPass = lstr("account::login::password","password");

      strOpen = lstr("account::login::open","open");

      m_plogin->defer_translate(strUser,strPass,strOpen);

   }


   void dialog::_001OnChar(::message::message * pmessage)
   {

      SCAST_PTR(::message::key, pkey, pmessage);

      if(pkey->m_ekey == ::user::key_return)
      {

         m_plogin->on_action("submit");

         pmessage->m_bRet = true;

      }
      else if(pkey->m_ekey == ::user::key_escape)
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

                  sync_lock slInteractive(m_pcredentials->mutex());

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

            order(zorder_top);

            place(m_rectFontopus);

            m_plogin->m_peditUser->SetFocus();

            display(e_display_restore, e_activation_set_foreground);

            set_need_redraw();

            post_redraw();

         }

      }

   }


   void dialog::do_modal(::rect rect)
   {

      m_iDelay = 0;

      m_pcredentials->m_iPasswordOriginalLength = -1;

      m_pcredentials->m_estatus = error_credentials;

      auto psession = Session;

      ::user::interaction * puiParent = psession->cast < ::user::interaction > ("plugin_parent");

      ::rect rectDesktop;

      if(puiParent != nullptr)
      {

         puiParent->get_window_rect(rectDesktop);

      }
      else if (rect.is_empty())
      {

         psession->get_main_monitor(rectDesktop);

      }
      else
      {

         rectDesktop = rect;

      }

      ::rect rectLogin;

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

      ::rect rectFontopus;

      rectFontopus.left = rectDesktop.left + (rectDesktop.width() - w) / 2;

      rectFontopus.top = rectDesktop.top + (rectDesktop.height() - h) / 3;

      rectFontopus.right = rectFontopus.left + w;

      rectFontopus.bottom = rectFontopus.top + h;

      if (puiParent != nullptr)
      {

         puiParent->_001ScreenToClient(rectFontopus);

      }

      if((rectFontopus.width() < 300 || rectFontopus.height() < 300) && puiParent != nullptr)
      {

         __pointer(::apex::application) papp = puiParent->get_context_application();

         if(papp != nullptr)
         {

            ::hyperlink hyperlink;

            hyperlink.open_link("ca2account:this", "", "");

            sleep(5000);

         }
         else
         {

            ::hyperlink hyperlink;

            hyperlink.open_link("ca2account:this", "", "");

         }

         return;

      }

#if !MOBILE_PLATFORM

      single_lock sl(&psession->account()->m_semaphoreDialog);

      bool bWasWaiting = false;

      while (!sl.wait(one_second()).signaled())
      {

         if (!::thread_get_run())
         {

            return;

         }

         bWasWaiting = true;

      }

      if (bWasWaiting)
      {

         if (!task_sleep(5000))
         {

            return;

         }

      }

#endif

      ::user::create_struct createstruct(rectFontopus);

      if(!create_window_ex(createstruct, puiParent))
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

         m_plogin->m_ppassword->_001GetText(strPass);

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

            m_plogin->m_pimage = Application.image().load_matter_image(stra[0]);

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

      auto rectClient = get_client_rect();

      if(rectClient.is_empty())
      {

         return;

      }

      get_client_rect(rectClient);

      ::user::interaction::on_layout(pgraphics);

      m_plogin->place(rectClient);

      m_plogin->display(::e_display_normal);

   }


   void dialog::_001OnLButtonDown(::message::message * pmessage)
   {

      SCAST_PTR(::message::mouse,pmouse, pmessage);

      if (pmessage->previous())
      {

         return;

      }

      get_wnd()->show_keyboard(false);

      m_bLButtonDown = true;

      m_bDrag = false;

      m_pointLButtonDown = pmouse->m_point;

      m_pointLButtonDownPos = m_pointLButtonDown;

      _001ScreenToClient(m_pointLButtonDownPos);

      SetCapture();

      pmouse->m_bRet = true;

   }


   void dialog::_001OnLButtonUp(::message::message * pmessage)
   {

      m_bLButtonDown = false;

      SCAST_PTR(::message::mouse,pmouse, pmessage);

      ReleaseCapture();

      m_bDrag = false;

      if (pmouse->previous())
      {

         return;

      }

      pmessage->m_bRet = true;

   }


   void dialog::_001OnMouseMove(::message::message * pmessage)
   {

      SCAST_PTR(::message::mouse,pmouse, pmessage);

      if (m_bLButtonDown)
      {

         if (!m_bDrag)
         {

            m_bDrag = true;

            const point & pointNow = pmouse->m_point;

            ::point point;

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



