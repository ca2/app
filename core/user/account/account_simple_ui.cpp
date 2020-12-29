#include "framework.h"
#if !BROAD_PRECOMPILED_HEADER
#include "core/user/account/_account.h"
#endif
#include "acme/const/timer.h"


namespace account
{


   simple_ui::simple_ui()
   {

#ifdef _UWP



#else

      //set_prodevian(false);

#endif

//    m_eschema = ::user::schema_default;

//    m_plogin->m_pstyle = this;

      m_bFontopusSimpleUiLayout = false;

   }


   simple_ui::~simple_ui()
   {

   }


   ::e_status simple_ui::initialize_simple_ui(::account::credentials * pcredentials)
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



   void simple_ui::install_message_routing(::channel * pchannel)
   {

      ::simple_ui::top::install_message_routing(pchannel);

      MESSAGE_LINK(e_message_create,pchannel,this,&simple_ui::_001OnCreate);
      MESSAGE_LINK(e_message_char,pchannel,this,&simple_ui::_001OnChar);
//      MESSAGE_LINK(e_message_left_button_down,pchannel,this,&simple_ui::_001OnLButtonDown);
//      MESSAGE_LINK(e_message_left_button_up,pchannel,this,&simple_ui::_001OnLButtonUp);
//      MESSAGE_LINK(e_message_mouse_move,pchannel,this,&simple_ui::_001OnMouseMove);

   }


   void simple_ui::_001OnCreate(::message::message * pmessage)
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


   void simple_ui::_001OnChar(::message::message * pmessage)
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


   void simple_ui::_001OnTimer(::timer * ptimer)
   {

      ::user::interaction::_001OnTimer(ptimer);

      if(ptimer->m_uEvent == e_timer_check_cached_credentials && !m_plogin->m_bCred)
      {

         try
         {

            if(m_pcredentials->m_estatus == ::success_credentials)
            {

               KillTimer(e_timer_check_cached_credentials);

               m_plogin->on_action("submit");

            }

         }
         catch(...)
         {

         }

      }

   }


   string simple_ui::do_account(const ::rect & rectParam)
   {

      m_pcredentials->m_iPasswordOriginalLength = -1;

      auto psession = Session;

      ::user::interaction * puiParent = psession->value("plugin_parent").cast < ::user::interaction >();

      ::rect rectDesktop;

      if(puiParent != nullptr)
      {

         puiParent->get_window_rect(rectDesktop);

      }
      else if (is_empty(&rectParam))
      {

         psession->get_main_monitor(rectDesktop);

      }
      else
      {

         rectDesktop = rectParam;

      }

      ::rect rectFontopus;

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

      rectFontopus.left = rectDesktop.left + (rectDesktop.width() - w) / 2;
      rectFontopus.top = rectDesktop.top + (rectDesktop.height() - h) / 3;
      rectFontopus.right = rectFontopus.left + w;
      rectFontopus.bottom = rectFontopus.top + h;

      if(puiParent != nullptr)
         puiParent->_001ScreenToClient(rectFontopus);

      if((rectFontopus.width() < 300 || rectFontopus.height() < 300) && puiParent != nullptr)
      {

         ::hyperlink hyperlink;

         hyperlink.open_link("ca2account:this", "", "");

         return "";

      }

      auto pcreatestruct = __new(::user::create_struct (0, nullptr, nullptr, 0, rectFontopus));

      if (!create_window_ex(pcreatestruct, puiParent))
      {

         return "";

      }

      set_window_text( "account Auth Windows");

      order(zorder_top);

      place(rectFontopus);

      m_plogin->m_peditUser->SetFocus();

      //m_plogin->on_layout(::draw2d::graphics_pointer & pgraphics);

      m_plogin->display();

      SetForegroundWindow();

      //BringWindowToTop();

      display(e_display_normal);

      SetTimer(2000, 300,nullptr);

      id idResult = RunModalLoop();

      return idResult;

   }


   string simple_ui::get_cred(const ::rect & rect,string & strUsername,string & strPassword,string strToken,string strTitle)
   {

      if(strTitle == "ca2")
      {

         m_plogin->m_bCred = false;

         m_plogin->m_strCred = "";

      }
      else
      {

         m_plogin->m_bCred = true;

         m_plogin->m_strCred = strTitle;

      }

      id idResult = do_account(rect);

      if(idResult == "ok")
      {

         m_plogin->m_peditUser->_001GetText(strUsername);

         m_plogin->m_ppassword->_001GetText(strPassword);

         return "ok";

      }
      else if(idResult == "cancel")
      {

         return "cancel";

      }
      else
      {

         return "fail";

      }

   }


   void simple_ui::on_layout(::draw2d::graphics_pointer & pgraphics)
   {

      /*

      if(!m_bFontopusSimpleUiLayout)
      {

         keep < bool > keepLayout(&m_bFontopusSimpleUiLayout,true,false,true);

         ::rect rectClient1;

         get_client_rect(rectClient1);

         bool bParentChange = false;

         if(GetParent() != nullptr)
         {

            ::rect rectParent;

            GetParent()->get_window_rect(rectParent);

            if(rectParent != m_rectParent)
            {

               bParentChange = true;

            }

         }


         if(rectClient1.area() < 100 * 100 || bParentChange)
         {

            ::rect rectDesktop;

            if(GetParent() != nullptr)
            {

               GetParent()->get_window_rect(rectDesktop);

            }
            else
            {

               psession->get_main_monitor(rectDesktop);

            }

            ::rect rectFontopus;

            ::rect rectLogin;

            int stdw = 800;

            int stdh = 184 + 23 + 184;

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

            rectFontopus.left = rectDesktop.left + (width(rectDesktop) - w) / 2;
            rectFontopus.top = rectDesktop.top + (height(rectDesktop) - h) / 3;
            rectFontopus.right = rectFontopus.left + w;
            rectFontopus.bottom = rectFontopus.top + h;


            if(GetParent() != nullptr)
               GetParent()->_001ScreenToClient(rectFontopus);


            set_window_pos(zorder_top,rectFontopus,SWP_SHOWWINDOW);

         }

      }
      */


      ::rect rectClient;

      get_client_rect(rectClient);

      m_plogin->layout().sketch() = rectClient;

      //m_plogin->on_layout(::draw2d::graphics_pointer & pgraphics);

   }


   void simple_ui::_001OnLButtonDown(::message::message * pmessage)
   {

      SCAST_PTR(::message::mouse, pmouse, pmessage);

      if (pmessage->previous())
         return;

      get_wnd()->show_keyboard(false);

      m_bLButtonDown = true;
      m_bDrag = false;

      m_pointLButtonDown = pmouse->m_point;

      auto pointOffset = m_pointLButtonDown;

      _001ScreenToClient(pointOffset);

      m_sizeLButtonDownOffset = pointOffset;

      SetCapture();

      pmouse->m_bRet = true;

   }


   void simple_ui::_001OnLButtonUp(::message::message * pmessage)
   {

      m_bLButtonDown = false;

      SCAST_PTR(::message::mouse, pmouse, pmessage);

      if(pmouse->previous())
         return;

      ReleaseCapture();

      m_bDrag = false;

      pmessage->m_bRet = true;

   }


   void simple_ui::_001OnMouseMove(::message::message * pmessage)
   {

      SCAST_PTR(::message::mouse, pmouse, pmessage);

      if (m_bLButtonDown)
      {

         if (!m_bDrag)
         {

            m_bDrag = true;

            auto pointNow = pmouse->m_point;

            auto point = pointNow - m_sizeLButtonDownOffset;

            move_to(point);

            m_bDrag = false;

         }

         pmessage->m_bRet = true;

      }
      else
      {
         if(pmessage->previous())
            return;

         pmessage->m_bRet = true;
      }

   }









   void simple_ui::_000OnDraw(::draw2d::graphics_pointer & pgraphics)
   {

      //pgraphics->FillSolidRect(0, 0, 100, 100, ARGB(255, 255, 0, 0));

      ::user::interaction::_000OnDraw(pgraphics);

      //pgraphics->FillSolidRect(100, 100, 100, 100, ARGB(255, 0, 255, 0));

   }


   void simple_ui::_001DrawChildren(::draw2d::graphics_pointer & pgraphics)
   {

      ::user::interaction::_001DrawChildren(pgraphics);

   }


   bool simple_ui::has_pending_graphical_update()
   {

      return is_window_visible();

   }


} // namespace account


