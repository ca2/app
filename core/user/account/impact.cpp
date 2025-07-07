#include "framework.h"
#include "impact.h"
#include "acme/constant/message.h"
#include "acme/crypto/crypto.h"
#include "aura/graphics/image/image.h"
#include "aura/graphics/image/icon.h"
#include "aura/graphics/image/drawing.h"
#include "aura/graphics/draw2d/graphics.h"
#include "aura/graphics/write_text/font.h"
#include "aura/message/user.h"
#include "aura/platform/system.h"
#include "aura/platform/node.h"
#include "aura/user/user/still.h"
#include "aura/user/user/plain_edit.h"
#include "aura/user/user/button.h"
#include "axis/account/credentials.h"
#include "axis/user/user/simple_ui_draw.h"


#include "acme/_operating_system.h"



namespace account
{


   //unsigned int c_cdecl thread_proc_pre_login(void * p);
   //   unsigned int c_cdecl thread_proc_defer_translate_login(void * p);


   impact::impact()
   {

      m_pstillUser = ___new ::user::still ();
      m_peditUser = ___new ::user::plain_edit ();
      m_pstillPassword = ___new ::user::still ();
      m_peditPassword = ___new ::user::plain_edit ();
      m_pbutton = ___new ::user::button ();
      m_pbuttonClose = ___new ::user::button ();

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
//            m_picon95 = ___new ::image::icon ();
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

   impact::~impact()
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

      ::acme::del(m_pstillUser);
      ::acme::del(m_peditUser);
      ::acme::del(m_pstillPassword);
      ::acme::del(m_peditPassword);
      ::acme::del(m_pbutton);
      ::acme::del(m_pbuttonClose);

   }


   void impact::install_message_routing(::channel * pchannel)
   {

      ::user::interaction::install_message_routing(pchannel);

      MESSAGE_LINK(e_message_create, pchannel, this, &impact::on_message_create);

   }


   void impact::defer_translate(const ::string & strUser, const ::string & strPass, const ::string & strOpen)
   {

      if (strUser.has_character())
         m_pstillUser->set_window_text(strUser);

      if (strPass.has_character())
         m_pstillPassword->set_window_text(strPass);

      if (strOpen.has_character())
         m_pbutton->set_window_text(strOpen);

   }


   void impact::initialize()
   {

   }


   void impact::on_layout(::draw2d::graphics_pointer & pgraphics)
   {


      int stdw = 800;
      int stdh = 400;

      int h;
      int w;

      auto rectangleX = this->rectangle();

      /*
      if (m_bSelfLayout)
      {


      double dwh = (double)stdw / (double)stdh;

      int availw = (int) (rectangleX.width() * (1.0 - 0.14));
      int availh = (int) (rectangleX.height() * (1.0 - 0.14));

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

      h = (int) minimum(stdh, availh);
      w = (int) minimum(stdw, h  * dwh);

      }
      else // remaining height
      {

      w = (int) minimum(stdw, availw);
      h = (int) minimum(stdh, w / dwh);

      }

      rectangleX.left() = (rectangleX.width() - w) / 2;
      rectangleX.top() = (rectangleX.height() - h) / 3;
      rectangleX.right() = rectangleX.left() + w;
      rectangleX.bottom() = rectangleX.top() + h;

      SetPlacement(rectangleX);

      }
      else
      {

      this->rectangle(rectangleX);

      }*/

      w = (int)(rectangleX.width());

      h = (int)(rectangleX.height());

      m_dRateX = (double)w / (double)stdw;

      m_dRateY = (double)h / (double)stdh;

      double rx = m_dRateX;

      double ry = m_dRateY;

      int x1 = (int)(49 * rx);
      int w2 = (int)((rectangleX.width() - 49 * 2 * rx));
      int h1 = (int)(23 * ry);
      int pad = (int)(5 * ry);

      int y = (int)((49 + 86) * ry);
      m_pstillUser->place(x1, y, w2, h1);
      y += h1 + pad;
      m_peditUser->place(x1, y, w2, h1);
      y += h1 + pad;
      m_pstillPassword->place(x1, y, w2, h1);
      y += h1 + pad;
      m_peditPassword->place(x1, y, w2, h1);
      y += h1 + pad;
      y += pad + h1 + pad;
      m_pbutton->place(x1, y, w2, h1 * 3);;

      m_pbuttonClose->place(w - 36, 12, 24, 24);

   }


   void impact::_001OnDraw(::draw2d::graphics_pointer & pgraphics)
   {



      //return;

      //::user::draw draw;

      ::int_rectangle r = this->rectangle();

      //draw.simple_ui_draw_frame_window_rect(r, pgraphics);



      ::color::color colorOut, colorIn, colorBorderOut, colorBorderIn, color, colorBackground;

      //       if (is_hover() || m_bDown || m_bMouseMove)
      /*       {

      #if CA2_PLATFORM_VERSION == CA2_BASIS

      colorOut = argb(1140, 255, 230, 255);

      colorIn = argb(255, 255, 133, 255);

      colorBorderOut = argb(190, 150, 100, 150);

      colorBorderIn = argb(190, 255, 240, 255);

      #else

      colorOut = argb(1140, 230, 255, 225);

      colorIn = argb(255, 133, 255, 80 + 49);

      colorBorderOut = argb(190, 100, 150, 100);

      colorBorderIn = argb(190, 240, 255, 235);

      #endif

      }
      else*/
      {

#if CA2_PLATFORM_VERSION == CA2_BASIS

         /*colorOut = argb(190, 255, 210, 255);

         colorIn = argb(255, 255, 1140, 255);

         colorBorderOut = argb(190, 90, 20, 90);

         colorBorderIn = argb(190, 255, 240, 255);*/

         colorOut = argb(255, 255, 210, 255);

         colorIn = argb(255, 255, 114, 255);

         colorBorderOut = argb(255, 90, 20, 90);

         colorBorderIn = argb(255, 255, 255, 255);

#else

         colorOut = argb(190, 210, 255, 205);

         colorIn = argb(255, 133, 255, 80 + 49);

         colorBorderOut = argb(190, 20, 90, 20);

         colorBorderIn = argb(190, 240, 255, 235);

#endif

      }


#if CA2_PLATFORM_VERSION == CA2_BASIS

      //color = argb(223, 90, 50, 80);
      color = argb(255, 90, 50, 80);

#else

      //color = argb(223, 49, 90, 23);
      color = argb(255, 49, 90, 23);

#endif

      colorBackground = colorOut.get_blend(colorIn, 0.5);

      double rx = m_dRateX;

      double ry = m_dRateY;

      if (m_bCred && m_strCred.has_character())
      {

         float fHeight = 18.0;

         ::write_text::font_pointer f(e_create, this);

         /*f->create_pixel_font(pnode->font_name(e_font_sans_ex), (int)height(rectangleX) * 0.7);

         float fMargin = (height(rectangleX) * ((1.0f - 0.7f) / 2.0f));*/

         //auto psystem = system();

         //auto pnode = psystem->node();

         f->create_font(e_font_sans_ex, ::write_text::font_size(fHeight, e_unit_point));

         pgraphics->set(f);

         pgraphics->set_text_color(colorBorderOut);

         pgraphics->text_out((int)(49 * rx), (int)(49 * ry), m_strCred);

      }
      else if (m_picon95)
      {

         pgraphics->draw_ca2_border2((int)(49 * rx), (int)(49 * ry) - 11, (int)((91 + 2 + 2) * ry), 1, 1, colorBackground, color, colorBorderOut, colorBorderIn);

         ::image::image_source imagesource(m_picon95);

         double_rectangle rectangle(::int_point((int)(49 * rx) + 2, (int)(49 * ry) + 2 - 11), ::int_size((int)((91 + 2 + 2) * ry), (int)((91 + 2 + 2) * ry)));

         ::image::image_drawing_options imagedrawingoptions(rectangle);

         ::image::image_drawing imagedrawing(imagedrawingoptions, imagesource);

         pgraphics->draw(imagedrawing);

      }
      else
      {

         pgraphics->draw_ca2_with_border2((int)(49 * rx), (int)(49 * ry) - 23, (int)((91 + 2 + 2) * ry), 1, 1, colorBackground, color, colorBorderOut, colorBorderIn);

      }

   }


   bool impact::on_action(const ::string & pszId)
   {

      if (!ansi_cmp(pszId, "submit"))
      {

         if (!m_bCred)
         {

            string strText;

            m_peditPassword->get_text(strText);

            auto psystem = system();

            strText = psystem->crypto()->nessie(strText);

            m_peditPassword->set_text(strText, ::e_source_database);

         }

         m_strResponse = "ok";

         m_happeningSubmit.set_happening();

      }
      else if (!ansi_cmp(pszId, "escape"))
      {

         get_parent()->display(e_display_none);
         m_peditPassword->set_text("", ::e_source_database);
         get_parent()->set_dialog_result("cancel");

         return true;

      }

      return false;


   }



   void impact::on_message_create(::message::message * pmessage)
   {

      ::pointer<::message::create>pcreate(pmessage);

      if (pcreate->previous())
         return;

      m_pstillUser->create_control(this, "label_user");
      m_peditUser->create_control(this, "edit_user");
      m_pstillPassword->create_control(this, "label_password");
      m_peditPassword->create_control(this, "password");
      m_pbutton->create_control(this, "submit");
      m_pbuttonClose->create_control(this, "escape");

      //if (!m_pstillUser->create_control(this, "label_user")
      //      || !m_peditUser->create_control(this, "edit_user")
      //      || !m_pstillPassword->create_control(this, "label_password")
      //      || !m_peditPassword->create_control(this, "password")
      //      || !m_pbutton->create_control(this, "submit")
      //      || !m_pbuttonClose->create_control(this, "escape"))
      //{
      //   pcreate->m_lresult = -1;
      //   pcreate->m_bRet = true;
      //   return;
      //}

      m_pbuttonClose->set_stock_icon(e_stock_icon_close);

      //m_pstillUser->set_window_text("e-mail:");
      //m_pstillPassword->set_window_text("password:");
      //m_pbutton->set_window_text("open");

      //m_pstillUser->set_window_text("@");
      //m_pstillPassword->set_window_text("********");
      //m_pbutton->set_window_text("===>");

      m_pstillUser->set_window_text("");
      m_pstillPassword->set_window_text("");
      m_pbutton->set_window_text("");

      place(0, 0, 800, 450);

      m_peditUser->set_keyboard_focus();

      //m_pploginDeferTranslate = aaa_memory_new impact *;

      //*m_pploginDeferTranslate = this;

      //increment_reference_count();

      //__begin_thread(get_app(),thread_proc_pre_login,get_app());

   }



   //unsigned int c_cdecl thread_proc_pre_login(void * p)
   //{

   //   ::aura::application * papp = (::aura::application *) int_point;

   //   return 0;

   //   login_thread thread;
   //   thread.m_strRequestingServer = "account.ca2.network";
   //   thread.m_strUsername = "";
   //   thread.m_strPassword = "";
   //   thread.run();

   //   return 0;

   //}


   void impact::_000OnDraw(::draw2d::graphics_pointer & pgraphics)
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

         throw ::exception(error_failed, "no more a window");

      }

   }


   void impact::_001DrawChildren(::draw2d::graphics_pointer & pgraphics)
   {

      //single_lock synchronouslock(mutex(), true);

      //int i = 5;

      //::pointer<::user::interaction>pinteraction;

      //while((pinteraction = get_child(pinteraction)).is_set() && i > 0)
      for_user_interaction_children(puserinteraction, this)
      {

         //i--;

         try
         {

            if (puserinteraction->is_this_visible() && !puserinteraction->is_custom_draw())
            {

               puserinteraction->_000CallOnDraw(pgraphics);

            }

         }
         catch (...)
         {

         }

      }

   }


   void impact::interactive_credentials(::account::credentials * pcredentials)
   {

      pcredentials->m_estatus = error_credentials;

      synchronous_lock synchronouslock(m_pmutexResponse);

      m_strRequestUrl = pcredentials->m_puser->m_pathUrl;

      m_peditUser->set_text(pcredentials->m_puser->m_strLogin, ::e_source_initialize);

      m_peditPassword->set_text(pcredentials->m_strPassword, ::e_source_initialize);

      m_strResponse.empty();

      m_happeningSubmit.reset_happening();

      m_happeningSubmit.wait();

      if (m_strResponse == "ok")
      {

         m_peditUser->get_text(pcredentials->m_puser->m_strLogin);

         m_peditPassword->get_text(pcredentials->m_strPassword);

         if(pcredentials->m_puser->m_strLogin.has_character()
               && pcredentials->m_strPassword.has_character())
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




