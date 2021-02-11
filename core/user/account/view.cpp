#include "framework.h"
#include "aura/operating_system.h"
#include "core/user/account/_account.h"
#include "axis/user/simple_ui_draw.h"

namespace account
{


   //::u32 c_cdecl thread_proc_pre_login(void * p);
   //   ::u32 c_cdecl thread_proc_defer_translate_login(void * p);


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

//#if defined(WINDOWS_DESKTOP)
//
//      {
//
//         HICON hicon95 = (HICON) ::LoadImage(::GetModuleHandle(nullptr), MAKEINTRESOURCE(95), IMAGE_ICON, 95, 95, LR_VGACOLOR);
//
//         if (hicon95 != nullptr)
//         {
//
//            m_picon95 = new ::draw2d::icon;
//
//            m_picon95->attach_os_data(hicon95);
//
//         }
//
//      }
//
//#endif
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

      sleep(49_ms);*/

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

      MESSAGE_LINK(e_message_create, pchannel, this, &view::_001OnCreate);

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

      ::rectangle_i32 rectClient;

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

      ::rectangle_i32 r = get_client_rect();

      draw.simple_ui_draw_frame_window_rect(r, pgraphics);



      color32_t crOut, crIn, crBorderOut, crBorderIn, cr, crBk;

      //       if (is_hover() || m_bDown || m_bMouseMove)
      /*       {

      #if CA2_PLATFORM_VERSION == CA2_BASIS

      crOut = argb(1140, 255, 230, 255);

      crIn = argb(255, 255, 133, 255);

      crBorderOut = argb(190, 150, 100, 150);

      crBorderIn = argb(190, 255, 240, 255);

      #else

      crOut = argb(1140, 230, 255, 225);

      crIn = argb(255, 133, 255, 80 + 49);

      crBorderOut = argb(190, 100, 150, 100);

      crBorderIn = argb(190, 240, 255, 235);

      #endif

      }
      else*/
      {

#if CA2_PLATFORM_VERSION == CA2_BASIS

         /*crOut = argb(190, 255, 210, 255);

         crIn = argb(255, 255, 1140, 255);

         crBorderOut = argb(190, 90, 20, 90);

         crBorderIn = argb(190, 255, 240, 255);*/

         crOut = argb(255, 255, 210, 255);

         crIn = argb(255, 255, 114, 255);

         crBorderOut = argb(255, 90, 20, 90);

         crBorderIn = argb(255, 255, 255, 255);

#else

         crOut = argb(190, 210, 255, 205);

         crIn = argb(255, 133, 255, 80 + 49);

         crBorderOut = argb(190, 20, 90, 20);

         crBorderIn = argb(190, 240, 255, 235);

#endif

      }


#if CA2_PLATFORM_VERSION == CA2_BASIS

      //cr = argb(223, 90, 50, 80);
      cr = argb(255, 90, 50, 80);

#else

      //cr = argb(223, 49, 90, 23);
      cr = argb(255, 49, 90, 23);

#endif

      crBk = argb(
             (colorref_get_a_value(crOut) + colorref_get_a_value(crIn)) / 2,
             (colorref_get_r_value(crOut) + colorref_get_r_value(crIn)) / 2,
             (colorref_get_g_value(crOut) + colorref_get_g_value(crIn)) / 2,
             (colorref_get_b_value(crOut) + colorref_get_b_value(crIn)) / 2);

      double rx = m_dRateX;

      double ry = m_dRateY;

      if (m_bCred && m_strCred.has_char())
      {
         float fHeight = 18.0;

         ::write_text::font_pointer f(e_create);

         /*f->create_pixel_font(os_font_name(e_font_sans_ex), (i32)height(rectClient) * 0.7);

         float fMargin = (height(rectClient) * ((1.0f - 0.7f) / 2.0f));*/

         f->create_point_font(os_font_name(e_font_sans_ex), fHeight * 1.0);


         pgraphics->set(f);

         pgraphics->set_text_color(crBorderOut);
         pgraphics->text_out((int)(49 * rx), (int)(49 * ry), m_strCred);
      }
      else if (m_picon95)
      {

         pgraphics->draw_ca2_border2((int)(49 * rx), (int)(49 * ry) - 11, (int)((91 + 2 + 2) * ry), 1, 1, crBk, cr, crBorderOut, crBorderIn);

         pgraphics->draw(::rectangle_i32(::point_i32((int)(49 * rx) + 2, (int)(49 * ry) + 2 - 11), ::size_i32((int)((91 + 2 + 2) * ry), (int)((91 + 2 + 2) * ry))), m_picon95);

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
            m_ppassword->_001SetText(strText, ::e_source_database);
         }

         m_strResponse = "ok";

         m_evSubmit.SetEvent();

      }
      else if (!strcmp(pszId, "escape"))
      {

         get_parent()->display(e_display_none);
         m_ppassword->_001SetText("", ::e_source_database);
         get_parent()->EndModalLoop("cancel");

         return true;

      }

      return false;


   }



   void view::_001OnCreate(::message::message * pmessage)
   {

      __pointer(::message::create) pcreate(pmessage);

      if (pcreate->previous())
         return;

      if (!m_plabelUser->create_control(this, "label_user")
            || !m_peditUser->create_control(this, "edit_user")
            || !m_plabelPassword->create_control(this, "label_password")
            || !m_ppassword->create_control(this, "password")
            || !m_ptap->create_control(this, "submit")
            || !m_ptapClose->create_control(this, "escape"))
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

      m_peditUser->set_keyboard_focus();

      //m_pploginDeferTranslate = new view *;

      //*m_pploginDeferTranslate = this;

      //add_ref(OBJ_REF_DBG_ARGS);

      //__begin_thread(get_context_application(),thread_proc_pre_login,get_context_application());

   }



   //::u32 c_cdecl thread_proc_pre_login(void * p)
   //{

   //   ::aura::application * papp = (::aura::application *) point_i32;

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

      m_peditUser->_001SetText(pcredentials->m_puser->m_strLogin, ::e_source_initialize);

      m_ppassword->_001SetText(pcredentials->m_strPassword, ::e_source_initialize);

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




