#include "framework.h"
#if !BROAD_PRECOMPILED_HEADER
#include "core/user/account/_account.h"
#endif
#ifdef WINDOWS_DESKTOP
#include "aura/os/windows/_windows.h"
#endif
#include "axis/user/simple_ui_draw.h"

namespace account
{


   //UINT c_cdecl thread_proc_pre_login(void * p);
   //   UINT c_cdecl thread_proc_defer_translate_login(void * p);


   view::view()
   {

      m_plabelUser = new ::simple_ui::label;
      m_peditUser = new ::simple_ui::edit_box;
      m_plabelPassword = new ::simple_ui::label;
      m_ppassword = new ::simple_ui::password;
      m_ptap = new ::simple_ui::tap;
      m_ptapClose = new ::simple_ui::tap;

      m_bSelfLayout = false;

      m_picon95 = nullptr;

#if defined(WINDOWS_DESKTOP)

      {

         HICON hicon95 = (HICON) ::LoadImage(::GetModuleHandle(nullptr), MAKEINTRESOURCE(95), IMAGE_ICON, 95, 95, LR_VGACOLOR);

         if (hicon95 != nullptr)
         {

            m_picon95 = new ::draw2d::icon;

            m_picon95->attach_os_data(hicon95);

         }

      }

#endif
      m_bCred = false;


   }

   view::~view()
   {
      /*
      if(m_pploginDeferTranslate != nullptr)
      {

      try
      {

      *m_pploginDeferTranslate = nullptr;

      }
      catch(...)
      {

      }

      }

      Sleep(49);*/

      ::acme::del(m_plabelUser);
      ::acme::del(m_peditUser);
      ::acme::del(m_plabelPassword);
      ::acme::del(m_ppassword);
      ::acme::del(m_ptap);
      ::acme::del(m_ptapClose);

   }


   void view::install_message_routing(::channel * pchannel)
   {

      ::user::interaction::install_message_routing(pchannel);

      IGUI_MSG_LINK(WM_CREATE, pchannel, this, &view::_001OnCreate);

   }


   void view::defer_translate(const string & strUser, const string & strPass, const string & strOpen)
   {

      if (strUser.has_char())
         m_plabelUser->set_window_text(strUser);

      if (strPass.has_char())
         m_plabelPassword->set_window_text(strPass);

      if (strOpen.has_char())
         m_ptap->set_window_text(strOpen);

   }


   void view::initialize()
   {

   }


   void view::on_layout(::draw2d::graphics_pointer & pgraphics)
   {


      int stdw = 800;
      int stdh = 400;

      int h;
      int w;

      ::rect rectClient;

      get_client_rect(rectClient);

      /*
      if (m_bSelfLayout)
      {


      double dwh = (double)stdw / (double)stdh;

      int availw = (int) (rectClient.width() * (1.0 - 0.14));
      int availh = (int) (rectClient.height() * (1.0 - 0.14));

      double davailwh;

      if (availh == 0.0)
      {
      davailwh = 1.0;
      }
      else
      {
      davailwh = (double)availw / (double)availh;
      }


      if (davailwh > dwh) // remaining width
      {

      h = (int) min(stdh, availh);
      w = (int) min(stdw, h  * dwh);

      }
      else // remaining height
      {

      w = (int) min(stdw, availw);
      h = (int) min(stdh, w / dwh);

      }

      rectClient.left = (rectClient.width() - w) / 2;
      rectClient.top = (rectClient.height() - h) / 3;
      rectClient.right = rectClient.left + w;
      rectClient.bottom = rectClient.top + h;

      SetPlacement(rectClient);

      }
      else
      {

      get_client_rect(rectClient);

      }*/

      w = (int)(rectClient.width());

      h = (int)(rectClient.height());

      m_dRateX = (double)w / (double)stdw;

      m_dRateY = (double)h / (double)stdh;

      double rx = m_dRateX;

      double ry = m_dRateY;

      i32 x1 = (int)(49 * rx);
      i32 w2 = (int)((rectClient.width() - 49 * 2 * rx));
      i32 h1 = (int)(23 * ry);
      i32 pad = (int)(5 * ry);

      i32 y = (int)((49 + 86) * ry);
      m_plabelUser->set_dim(x1, y, w2, h1);
      y += h1 + pad;
      m_peditUser->set_dim(x1, y, w2, h1);
      y += h1 + pad;
      m_plabelPassword->set_dim(x1, y, w2, h1);
      y += h1 + pad;
      m_ppassword->set_dim(x1, y, w2, h1);
      y += h1 + pad;
      y += pad + h1 + pad;
      m_ptap->set_dim(x1, y, w2, h1 * 3);;

      m_ptapClose->set_dim(w - 36, 12, 24, 24);

   }


   void view::_001OnDraw(::draw2d::graphics_pointer & pgraphics)
   {



      //return;

      ::simple_ui::draw draw;

      ::rect r = get_client_rect();

      draw.simple_ui_draw_frame_window_rect(r, pgraphics);



      COLORREF crOut, crIn, crBorderOut, crBorderIn, cr, crBk;

      //       if (is_hover() || m_bDown || m_bMouseMove)
      /*       {

      #if CA2_PLATFORM_VERSION == CA2_BASIS

      crOut = ARGB(1140, 255, 230, 255);

      crIn = ARGB(255, 255, 133, 255);

      crBorderOut = ARGB(190, 150, 100, 150);

      crBorderIn = ARGB(190, 255, 240, 255);

      #else

      crOut = ARGB(1140, 230, 255, 225);

      crIn = ARGB(255, 133, 255, 80 + 49);

      crBorderOut = ARGB(190, 100, 150, 100);

      crBorderIn = ARGB(190, 240, 255, 235);

      #endif

      }
      else*/
      {

#if CA2_PLATFORM_VERSION == CA2_BASIS

         /*crOut = ARGB(190, 255, 210, 255);

         crIn = ARGB(255, 255, 1140, 255);

         crBorderOut = ARGB(190, 90, 20, 90);

         crBorderIn = ARGB(190, 255, 240, 255);*/

         crOut = ARGB(255, 255, 210, 255);

         crIn = ARGB(255, 255, 1140, 255);

         crBorderOut = ARGB(255, 90, 20, 90);

         crBorderIn = ARGB(255, 255, 255, 255);

#else

         crOut = ARGB(190, 210, 255, 205);

         crIn = ARGB(255, 133, 255, 80 + 49);

         crBorderOut = ARGB(190, 20, 90, 20);

         crBorderIn = ARGB(190, 240, 255, 235);

#endif

      }


#if CA2_PLATFORM_VERSION == CA2_BASIS

      //cr = ARGB(223, 90, 50, 80);
      cr = ARGB(255, 90, 50, 80);

#else

      //cr = ARGB(223, 49, 90, 23);
      cr = ARGB(255, 49, 90, 23);

#endif

      crBk = ARGB(
             (colorref_get_a_value(crOut) + colorref_get_a_value(crIn)) / 2,
             (colorref_get_r_value(crOut) + colorref_get_r_value(crIn)) / 2,
             (colorref_get_g_value(crOut) + colorref_get_g_value(crIn)) / 2,
             (colorref_get_b_value(crOut) + colorref_get_b_value(crIn)) / 2);

      double rx = m_dRateX;

      double ry = m_dRateY;

      if (m_bCred && m_strCred.has_char())
      {
         float fHeight = 18.0;

         ::draw2d::font_pointer f(e_create);

         /*f->create_pixel_font(FONT_SANS_EX, (i32)height(rectClient) * 0.7);

         float fMargin = (height(rectClient) * ((1.0f - 0.7f) / 2.0f));*/

         f->create_point_font(FONT_SANS_EX, fHeight * 1.0);


         pgraphics->set(f);

         pgraphics->set_text_color(crBorderOut);
         pgraphics->text_out((int)(49 * rx), (int)(49 * ry), m_strCred);
      }
      else if (m_picon95)
      {

         pgraphics->draw_ca2_border2((int)(49 * rx), (int)(49 * ry) - 11, (int)((91 + 2 + 2) * ry), 1, 1, crBk, cr, crBorderOut, crBorderIn);

         pgraphics->DrawIcon((int)(49 * rx) + 2, (int)(49 * ry) + 2 - 11, m_picon95, (int)((91 + 2 + 2) * ry), (int)((91 + 2 + 2) * ry), 0, nullptr, 0);

      }
      else
      {

         pgraphics->draw_ca2_with_border2((int)(49 * rx), (int)(49 * ry) - 23, (int)((91 + 2 + 2) * ry), 1, 1, crBk, cr, crBorderOut, crBorderIn);

      }


   }


   bool view::on_action(const char * pszId)
   {

      if (!strcmp(pszId, "submit"))
      {


         if (!m_bCred)
         {
            string strText;
            m_ppassword->_001GetText(strText);
            strText = System.crypto().nessie(strText);
            m_ppassword->_001SetText(strText, ::source_database);
         }

         m_strResponse = "ok";

         m_evSubmit.SetEvent();

      }
      else if (!strcmp(pszId, "escape"))
      {

         GetParent()->display(display_none);
         m_ppassword->_001SetText("", ::source_database);
         GetParent()->EndModalLoop("cancel");

         return true;

      }

      return false;


   }



   void view::_001OnCreate(::message::message * pmessage)
   {

      SCAST_PTR(::message::create, pcreate, pmessage);

      if (pcreate->previous())
         return;

      if (!m_plabelUser->create_window(this, "label_user")
            || !m_peditUser->create_window(this, "edit_user")
            || !m_plabelPassword->create_window(this, "label_password")
            || !m_ppassword->create_window(this, "password")
            || !m_ptap->create_window(this, "submit")
            || !m_ptapClose->create_window(this, "escape"))
      {
         pcreate->m_lresult = -1;
         pcreate->m_bRet = true;
         return;
      }

      m_ptapClose->m_estockicon = stock_icon_close;

      //m_plabelUser->set_window_text("e-mail:");
      //m_plabelPassword->set_window_text("password:");
      //m_ptap->set_window_text("open");

      //m_plabelUser->set_window_text("@");
      //m_plabelPassword->set_window_text("********");
      //m_ptap->set_window_text("===>");

      m_plabelUser->set_window_text("");
      m_plabelPassword->set_window_text("");
      m_ptap->set_window_text("");

      set_dim(0, 0, 800, 450);

      m_peditUser->keyboard_set_focus();


      //m_pploginDeferTranslate = new view *;

      //*m_pploginDeferTranslate = this;

      //add_ref(OBJ_REF_DBG_ARGS);

      //__begin_thread(get_context_application(),thread_proc_pre_login,get_context_application());

   }



   //UINT c_cdecl thread_proc_pre_login(void * p)
   //{

   //   ::aura::application * papp = (::aura::application *) point;

   //   return 0;

   //   login_thread thread;
   //   thread.m_strRequestingServer = "account.ca2.cc";
   //   thread.m_strUsername = "";
   //   thread.m_strPassword = "";
   //   thread.run();

   //   return 0;

   //}


   void view::_000OnDraw(::draw2d::graphics_pointer & pgraphics)
   {

      //user::interaction::_000OnDraw(pgraphics);


      if (!is_this_visible())
         return;

      _001DrawThis(pgraphics);

      try
      {

         _001DrawChildren(pgraphics);

      }
      catch (...)
      {

         __throw(::exception::exception("no more a window"));

      }

   }


   void view::_001DrawChildren(::draw2d::graphics_pointer & pgraphics)
   {

      //single_lock sl(mutex(), true);

      //int i = 5;

      __pointer(::user::interaction) pinteraction;

      //while((pinteraction = get_child(pinteraction)).is_set() && i > 0)
      while (get_child(pinteraction))
      {

         //i--;

         try
         {

            if (pinteraction->is_this_visible() && !pinteraction->is_custom_draw())
            {

               pinteraction->_000CallOnDraw(pgraphics);

            }

         }
         catch (...)
         {

         }

      }

   }


   void view::interactive_credentials(::account::credentials * pcredentials)
   {

      pcredentials->m_estatus = error_credentials;

      sync_lock sl(&m_mutexResponse);

      m_strRequestUrl = pcredentials->m_puser->m_pathUrl;

      m_peditUser->_001SetText(pcredentials->m_puser->m_strLogin, ::source_initialize);

      m_ppassword->_001SetText(pcredentials->m_strPassword, ::source_initialize);

      m_strResponse.Empty();

      m_evSubmit.ResetEvent();

      m_evSubmit.wait();

      if (m_strResponse == "ok")
      {

         m_peditUser->_001GetText(pcredentials->m_puser->m_strLogin);

         m_ppassword->_001GetText(pcredentials->m_strPassword);

         if(pcredentials->m_puser->m_strLogin.has_char()
               && pcredentials->m_strPassword.has_char())
         {

            pcredentials->m_estatus = ::success_credentials;

         }
         else
         {

            pcredentials->m_estatus = error_failed;

         }

      }
      else

      {
         pcredentials->m_estatus = error_failed;
      }

   }


} // namespace account




