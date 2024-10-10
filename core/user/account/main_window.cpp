// From simple_ui.cpp by camilo on 2022-08-28 11:46 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "acme/constant/message.h"
#include "acme/constant/user_key.h"
#include "acme/constant/timer.h"
#include "acme/platform/timer.h"
#include "acme/platform/hyperlink.h"
#include "aura/windowing/windowing.h"
#include "aura/windowing/display.h"
#include "axis/account/credentials.h"
#include "aura/message/user.h"
#include "aura/user/user/plain_edit.h"
#include "login.h"
#include "main_window.h"
#include "aura/platform/session.h"



namespace account
{


   main_window::main_window()
   {

#ifdef UNIVERSAL_WINDOWS



#else

      //set_fps_interest(false);

#endif

//    m_eschema = ::user::schema_default;

//    m_plogin->m_pstyle = this;

      m_bFontopusSimpleUiLayout = false;

   }


   main_window::~main_window()
   {

   }


   void main_window::initialize_simple_ui(::account::credentials * pcredentials)
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

      __construct_new(m_plogin);

      //if (!estatus)
      //{

      //   return estatus;

      //}

      //return estatus;

   }


   void main_window::install_message_routing(::channel * pchannel)
   {

      ::user::main_window::install_message_routing(pchannel);

      MESSAGE_LINK(MESSAGE_CREATE, pchannel, this, &main_window::on_message_create);
      MESSAGE_LINK(e_message_char, pchannel, this, &main_window::on_message_character);
      //      MESSAGE_LINK(e_message_left_button_down,pchannel,this,&main_window::on_message_left_button_down);
      //      MESSAGE_LINK(e_message_left_button_up,pchannel,this,&main_window::on_message_left_button_up);
      //      MESSAGE_LINK(e_message_mouse_move,pchannel,this,&main_window::on_message_mouse_move);

   }


   void main_window::on_message_create(::message::message * pmessage)
   {

      ::pointer<::message::create>pcreate(pmessage);

      if (pcreate->previous())
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

      m_plogin->defer_translate(strUser, strPass, strOpen);

   }


   void main_window::on_message_character(::message::message * pmessage)
   {

      auto pkey = pmessage->m_union.m_pkey;

      if (pkey->m_ekey == ::user::e_key_return)
      {

         m_plogin->on_action("submit");

         pmessage->m_bRet = true;

      }
      else if (pkey->m_ekey == ::user::e_key_escape)
      {

         m_plogin->on_action("escape");

         pmessage->m_bRet = true;

      }

   }


   void main_window::_001OnTimer(::timer * ptimer)
   {

      ::user::interaction::_001OnTimer(ptimer);

      if (ptimer->m_uEvent == e_timer_check_cached_credentials && !m_plogin->m_bCred)
      {

         try
         {

            if (m_pcredentials->m_estatus == ::success_credentials)
            {

               KillTimer(e_timer_check_cached_credentials);

               m_plogin->on_action("submit");

            }

         }
         catch (...)
         {

         }

      }

   }


   string main_window::do_account(const ::rectangle_i32 & rectangleParam)
   {

      m_pcredentials->m_iPasswordOriginalLength = -1;

      auto psession = get_session();

      ::user::interaction * puiParent = psession->payload("plugin_parent").cast < ::user::interaction >();

      ::rectangle_i32 rectangleDesktop;

      if (puiParent != nullptr)
      {

         puiParent->window_rectangle(rectangleDesktop);

      }
      else if (is_empty(rectangleParam))
      {

         auto pwindowing = windowing();

         auto pdisplay = pwindowing->display();

         pdisplay->get_main_monitor(rectangleDesktop);

      }
      else
      {

         rectangleDesktop = rectangleParam;

      }

      ::rectangle_i32 rectangleFontopus;

      ::rectangle_i32 rectangleLogin;

      int stdw = 800;

      int stdh = 400;

      int w = stdw;

      int h = stdh;

      if (w > rectangleDesktop.width())
      {

         w = rectangleDesktop.width();

      }

      if (h > rectangleDesktop.height())
      {

         h = rectangleDesktop.height();

      }

      rectangleFontopus.left() = rectangleDesktop.left() + (rectangleDesktop.width() - w) / 2;
      rectangleFontopus.top() = rectangleDesktop.top() + (rectangleDesktop.height() - h) / 3;
      rectangleFontopus.right() = rectangleFontopus.left() + w;
      rectangleFontopus.bottom() = rectangleFontopus.top() + h;

      if (puiParent != nullptr)
         puiParent->screen_to_client()(rectangleFontopus);

      if ((rectangleFontopus.width() < 300 || rectangleFontopus.height() < 300) && puiParent != nullptr)
      {

         auto phyperlink = __create_new < ::hyperlink >();

         phyperlink->m_strLink = "ca2account:this";

         phyperlink->run();

         return "";

      }

      //auto pusersystem = __new ::user::system(0, nullptr, nullptr, 0, rectangleFontopus);

      //create_host(e_parallelization_synchronous);

      create_host();

      //if (!create_host())
      //{

      //   return "";

      //}

      set_window_text("account Auth Windows");

      order(e_zorder_top);

      place(rectangleFontopus);

      m_plogin->m_peditUser->set_keyboard_focus();

      //m_plogin->on_layout(pgraphics);

      m_plogin->display();

      set_foreground_window();

      //BringWindowToTop();

      display(e_display_normal);

      SetTimer(2000, 300_ms, nullptr);

      atom idResult = RunModalLoop();

      return idResult;

   }


   string main_window::get_cred(const ::rectangle_i32 & rectangle, string & strUsername, string & strPassword, string strToken, string strTitle)
   {

      if (strTitle == "ca2")
      {

         m_plogin->m_bCred = false;

         m_plogin->m_strCred = "";

      }
      else
      {

         m_plogin->m_bCred = true;

         m_plogin->m_strCred = strTitle;

      }

      atom idResult = do_account(rectangle);

      if (idResult == "ok")
      {

         strUsername = m_plogin->m_peditUser->as_text();

         strPassword = m_plogin->m_peditPassword->as_text();

         return "ok";

      }
      else if (idResult == "cancel")
      {

         return "cancel";

      }
      else
      {

         return "fail";

      }

   }


   void main_window::on_layout(::draw2d::graphics_pointer & pgraphics)
   {

      /*

      if(!m_bFontopusSimpleUiLayout)
      {

         keep < bool > keepLayout(&m_bFontopusSimpleUiLayout,true,false,true);

         ::rectangle_i32 rectangleX1;

         this->rectangle(rectangleX1);

         bool bParentChange = false;

         if(get_parent() != nullptr)
         {

            ::rectangle_i32 rectangleParent;

            get_parent()->window_rectangle(rectangleParent);

            if(rectangleParent != m_rectangleParent)
            {

               bParentChange = true;

            }

         }


         if(rectangleX1.area() < 100 * 100 || bParentChange)
         {

            ::rectangle_i32 rectangleDesktop;

            if(get_parent() != nullptr)
            {

               get_parent()->window_rectangle(rectangleDesktop);

            }
            else
            {

               auto puser = psession->user();

               auto pwindowing = puser->windowing();

               auto pdisplay = pwindowing->display();

               pdisplay->get_main_monitor(rectangleDesktop);

            }

            ::rectangle_i32 rectangleFontopus;

            ::rectangle_i32 rectangleLogin;

            int stdw = 800;

            int stdh = 184 + 23 + 184;

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

            rectangleFontopus.left() = rectangleDesktop.left() + (width(rectangleDesktop) - w) / 2;
            rectangleFontopus.top() = rectangleDesktop.top() + (height(rectangleDesktop) - h) / 3;
            rectangleFontopus.right() = rectangleFontopus.left() + w;
            rectangleFontopus.bottom() = rectangleFontopus.top() + h;


            if(get_parent() != nullptr)
               get_parent()->screen_to_client(rectangleFontopus);


            set_window_position(e_zorder_top,rectangleFontopus,SWP_SHOWWINDOW);

         }

      }
      */


      auto rectangleX = this->rectangle();

      m_plogin->place(rectangleX);

      //m_plogin->on_layout(pgraphics);

   }


   void main_window::on_message_left_button_down(::message::message * pmessage)
   {

      auto pmouse = pmessage->m_union.m_pmouse;

      if (pmessage->previous())
      {

         return;

      }

      //get_wnd()->show_keyboard(false);

      //m_bLButtonDown = true;
      //m_bDrag = false;

      //m_pointLButtonDown = pmouse->m_point;

      //auto pointOffset = m_pointLButtonDown;

      //screen_to_client(pointOffset);

      //m_sizeLButtonDownOffset = pointOffset;

      //set_mouse_capture();

      //pmouse->m_bRet = true;

   }


   void main_window::on_message_left_button_up(::message::message * pmessage)
   {

      //m_bLButtonDown = false;

      //auto pmouse = pmessage->m_union.m_pmouse;

      //if (pmouse->previous())
      //{

      //   return;

      //}

      //auto psession = get_session();

      //auto puser = psession->user();

      //auto pwindowing = puser->windowing();

      //pwindowing->release_mouse_capture();

      //m_bDrag = false;

      //pmessage->m_bRet = true;

   }


   void main_window::on_message_mouse_move(::message::message * pmessage)
   {

      auto pmouse = pmessage->m_union.m_pmouse;

      //if (m_bLButtonDown)
      //{

      //   if (!m_bDrag)
      //   {

      //      m_bDrag = true;

      //      auto pointNow = pmouse->m_point;

      //      auto point = pointNow - m_sizeLButtonDownOffset;

      //      move_to(point);

      //      m_bDrag = false;

      //   }

      //   pmessage->m_bRet = true;

      //}
      //else
      {
         if (pmessage->previous())
            return;

         pmessage->m_bRet = true;
      }

   }









   void main_window::_000OnDraw(::draw2d::graphics_pointer & pgraphics)
   {

      //pgraphics->FillSolidRect(0, 0, 100, 100, argb(255, 255, 0, 0));

      ::user::interaction::_000OnDraw(pgraphics);

      //pgraphics->FillSolidRect(100, 100, 100, 100, argb(255, 0, 255, 0));

   }


   void main_window::_001DrawChildren(::draw2d::graphics_pointer & pgraphics)
   {

      ::user::interaction::_001DrawChildren(pgraphics);

   }


   //bool main_window::has_pending_graphical_update()
   //{

   //   return is_window_visible();

   //}


} // namespace account


