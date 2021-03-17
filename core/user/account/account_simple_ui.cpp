#include "framework.h"
#include "core/user/account/_account.h"
#include "acme/const/timer.h"


namespace account
{


   main_window::main_window()
   {

#ifdef _UWP



#else

      //set_prodevian(false);

#endif

//    m_eschema = ::user::schema_default;

//    m_plogin->m_pstyle = this;

      m_bFontopusSimpleUiLayout = false;

   }


   main_window::~main_window()
   {

   }


   ::e_status main_window::initialize_simple_ui(::account::credentials * pcredentials)
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



   void main_window::install_message_routing(::channel * pchannel)
   {

      ::user::main_window::install_message_routing(pchannel);

      MESSAGE_LINK(e_message_create,pchannel,this,&main_window::on_message_create);
      MESSAGE_LINK(e_message_char,pchannel,this,&main_window::_001OnChar);
//      MESSAGE_LINK(e_message_left_button_down,pchannel,this,&main_window::on_message_left_button_down);
//      MESSAGE_LINK(e_message_left_button_up,pchannel,this,&main_window::on_message_left_button_up);
//      MESSAGE_LINK(e_message_mouse_move,pchannel,this,&main_window::on_message_mouse_move);

   }


   void main_window::on_message_create(::message::message * pmessage)
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

      strUser = lstr("account::login::email","e-mail");

      strPass = lstr("account::login::password","password");

      strOpen = lstr("account::login::open","open");

      m_plogin->defer_translate(strUser,strPass,strOpen);

   }


   void main_window::_001OnChar(::message::message * pmessage)
   {

      __pointer(::message::key) pkey(pmessage);

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


   void main_window::_001OnTimer(::timer * ptimer)
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


   string main_window::do_account(const ::rectangle_i32 & rectParam)
   {

      m_pcredentials->m_iPasswordOriginalLength = -1;

      auto psession = get_session();

      ::user::interaction * puiParent = psession->payload("plugin_parent").cast < ::user::interaction >();

      ::rectangle_i32 rectDesktop;

      if(puiParent != nullptr)
      {

         puiParent->get_window_rect(rectDesktop);

      }
      else if (is_empty(&rectParam))
      {

         auto puser = psession->user();

         auto pwindowing = puser->windowing();

         auto pdisplay = pwindowing->display();

         pdisplay->get_main_monitor(rectDesktop);

      }
      else
      {

         rectDesktop = rectParam;

      }

      ::rectangle_i32 rectFontopus;

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

      rectFontopus.left = rectDesktop.left + (rectDesktop.width() - w) / 2;
      rectFontopus.top = rectDesktop.top + (rectDesktop.height() - h) / 3;
      rectFontopus.right = rectFontopus.left + w;
      rectFontopus.bottom = rectFontopus.top + h;

      if(puiParent != nullptr)
         puiParent->_001ScreenToClient(rectFontopus);

      if((rectFontopus.width() < 300 || rectFontopus.height() < 300) && puiParent != nullptr)
      {

         auto phyperlink = __create_new < ::hyperlink >();

         phyperlink->m_strLink = "ca2account:this";

         phyperlink->open_link();

         return "";

      }

      //auto pusersystem = __new(::user::system (0, nullptr, nullptr, 0, rectFontopus));

      if (!create_host())
      {

         return "";

      }

      set_window_text( "account Auth Windows");

      order(e_zorder_top);

      place(rectFontopus);

      m_plogin->m_peditUser->set_keyboard_focus();

      //m_plogin->on_layout(::draw2d::graphics_pointer & pgraphics);

      m_plogin->display();

      set_foreground_window();

      //BringWindowToTop();

      display(e_display_normal);

      SetTimer(2000, 300,nullptr);

      id idResult = RunModalLoop();

      return idResult;

   }


   string main_window::get_cred(const ::rectangle_i32 & rectangle,string & strUsername,string & strPassword,string strToken,string strTitle)
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

      id idResult = do_account(rectangle);

      if(idResult == "ok")
      {

         m_plogin->m_peditUser->_001GetText(strUsername);

         m_plogin->m_peditPassword->_001GetText(strPassword);

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


   void main_window::on_layout(::draw2d::graphics_pointer & pgraphics)
   {

      /*

      if(!m_bFontopusSimpleUiLayout)
      {

         keep < bool > keepLayout(&m_bFontopusSimpleUiLayout,true,false,true);

         ::rectangle_i32 rectClient1;

         get_client_rect(rectClient1);

         bool bParentChange = false;

         if(get_parent() != nullptr)
         {

            ::rectangle_i32 rectParent;

            get_parent()->get_window_rect(rectParent);

            if(rectParent != m_rectParent)
            {

               bParentChange = true;

            }

         }


         if(rectClient1.area() < 100 * 100 || bParentChange)
         {

            ::rectangle_i32 rectDesktop;

            if(get_parent() != nullptr)
            {

               get_parent()->get_window_rect(rectDesktop);

            }
            else
            {

               auto puser = psession->user();

               auto pwindowing = puser->windowing();

               auto pdisplay = pwindowing->display();

               pdisplay->get_main_monitor(rectDesktop);

            }

            ::rectangle_i32 rectFontopus;

            ::rectangle_i32 rectLogin;

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


            if(get_parent() != nullptr)
               get_parent()->_001ScreenToClient(rectFontopus);


            set_window_position(e_zorder_top,rectFontopus,SWP_SHOWWINDOW);

         }

      }
      */


      ::rectangle_i32 rectClient;

      get_client_rect(rectClient);

      m_plogin->layout().sketch() = rectClient;

      //m_plogin->on_layout(::draw2d::graphics_pointer & pgraphics);

   }


   void main_window::on_message_left_button_down(::message::message * pmessage)
   {

      __pointer(::message::mouse) pmouse(pmessage);

      if (pmessage->previous())
      {

         return;

      }

      //get_wnd()->show_keyboard(false);

      //m_bLButtonDown = true;
      //m_bDrag = false;

      //m_pointLButtonDown = pmouse->m_point;

      //auto pointOffset = m_pointLButtonDown;

      //_001ScreenToClient(pointOffset);

      //m_sizeLButtonDownOffset = pointOffset;

      //set_mouse_capture();

      //pmouse->m_bRet = true;

   }


   void main_window::on_message_left_button_up(::message::message * pmessage)
   {

      //m_bLButtonDown = false;

      //__pointer(::message::mouse) pmouse(pmessage);

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

      __pointer(::message::mouse) pmouse(pmessage);

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
         if(pmessage->previous())
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


   bool main_window::has_pending_graphical_update()
   {

      return is_window_visible();

   }


} // namespace account


