#include "framework.h"
#include "login.h"
#include "acme/constant/message.h"
#include "apex/crypto/crypto.h"
#include "axis/user/user/simple_ui_draw.h"
#include "aura/graphics/image/image.h"
#include "aura/graphics/image/drawing.h"
#include "aura/graphics/image/source.h"
#include "aura/graphics/image/icon.h"
#include "aura/graphics/write_text/font.h"
#include "aura/message/user.h"
#include "aura/user/user/still.h"
#include "aura/user/user/button.h"
#include "aura/user/user/plain_edit.h"
#include "core/platform/system.h"
#include "aura/platform/node.h"


namespace account
{


   login::login()
   {

      m_bSubmitted = false;

      m_iPasswordOriginalLength = -1;


      m_bSelfLayout = false;

      m_picon95 = nullptr;

//#if defined(WINDOWS_DESKTOP)
//
//      {
//
//         HICON hicon95 = (HICON) ::LoadImage(::GetModuleHandle(nullptr),MAKEINTRESOURCE(95),IMAGE_ICON,95,95,LR_VGACOLOR);
//
//         if(hicon95 != nullptr)
//         {
//
//            m_picon95 = memory_new ::draw2d::icon;
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


   login::~login()
   {

   }


   void login::install_message_routing(::channel * pchannel)
   {

      ::user::interaction::install_message_routing(pchannel);

      MESSAGE_LINK(MESSAGE_CREATE, pchannel, this, &login::on_message_create);

   }


   void login::defer_translate(const ::string & strUser, const ::string & strPass, const ::string & strOpen)
   {

      if (strUser.has_char())
      {

         m_pstillUser->set_window_text(strUser);

      }

      if (strPass.has_char())
      {

         m_pstillPassword->set_window_text(strPass);

      }

      if (strOpen.has_char())
      {

         m_pbutton->set_window_text(strOpen);

      }

   }


   void login::initialize(::particle * pparticle)
   {

      //auto estatus = 
      
      ::user::interaction::initialize(pparticle);
      
      //if (!estatus)
      //{

      //   return estatus;

      //}
      //
      m_bSubmitted = false;

      //if (!(estatus = __construct_new(m_pstillUser))) return false;
      //if(!(estatus = __construct_new(m_peditUser))) return false;
      //if (!(estatus = __construct_new(m_pstillPassword))) return false;
      //if (!(estatus = __construct_new(m_peditPassword))) return false;
      //if (!(estatus = __construct_new(m_pbutton))) return false;
      //if (!(estatus = __construct_new(m_pbuttonClose))) return false;


      __construct_new(m_pstillUser);
      __construct_new(m_peditUser);
      __construct_new(m_pstillPassword);
      __construct_new(m_peditPassword);
      __construct_new(m_pbutton);
      __construct_new(m_pbuttonClose);

      //return estatus;

   }


   void login::on_layout(::draw2d::graphics_pointer & pgraphics)
   {

      auto rectangleClient = get_client_rect();

      if(rectangleClient.is_empty())
      {

         return;

      }

      int stdw = 800;

      int stdh = 400;

      int h;

      int w;

      w = (int)(rectangleClient.width());

      h = (int)(rectangleClient.height());

      m_dRateX = (double)w / (double)stdw;

      m_dRateY = (double)h / (double)stdh;

      double rx = m_dRateX;

      double ry = m_dRateY;

      i32 x1 = (int) (49 * rx);

      i32 w2 = (int) ((rectangleClient.width() - 49 * 2 * rx));

      i32 h1 = (int) (23 * ry);

      i32 pad = (int) (5 * ry);

      i32 y = (int) ((49 + 86) * ry);

      m_pstillUser->place(::rectangle_i32_dimension(x1,y,w2,h1));
      m_pstillUser->display(::e_display_restored, e_activation_no_activate);

      y += h1 + pad;

      m_peditUser->place(::rectangle_i32_dimension(x1,y,w2, h1));
      m_peditUser->display(::e_display_restored, e_activation_no_activate);

      y += h1 + pad;

      m_pstillPassword->place(::rectangle_i32_dimension(x1,y,w2, h1));
      m_pstillPassword->display(::e_display_restored, e_activation_no_activate);

      y += h1 + pad;

      m_peditPassword->set_placement(x1,y,w2,h1);
      m_peditPassword->display(::e_display_restored, e_activation_no_activate);

      y += h1 + pad;

      y += pad + h1 + pad;

      m_pbutton->set_placement(x1,y,w2,h1 * 3);
      m_pbutton->display(::e_display_restored, e_activation_no_activate);

      m_pbuttonClose->set_placement(w - 36,12,24,24);
      m_pbuttonClose->display(::e_display_restored, e_activation_no_activate);

   }


   void login::_001OnDraw(::draw2d::graphics_pointer & pgraphics)
   {

      ::simple_ui::draw draw;

      ::rectangle_i32 r = get_client_rect();

      draw.simple_ui_draw_frame_window_rect(r, pgraphics);

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

      if (m_pimage->is_set() && m_pimage->height() > 21)
      {

         double r = (double)(64) / (double)m_pimage->height();

         auto rectangleSource = rectangle_f64_dimension(0, 0, m_pimage->width(), m_pimage->height());

         image_source imagesource(m_pimage);

         auto rectangleTarget = rectangle_f64_dimension((int)(49 * rx), (int)(49 * ry) + 2 - 11,
                                                        i32 (m_pimage->width() * r), i32 (m_pimage->height() * r));

         image_drawing_options imagedrawingoptions(rectangleTarget);

         image_drawing imagedrawing(imagedrawingoptions, imagesource);

         pgraphics->draw(imagedrawing);

      }
      else if (m_bCred && m_strCred.has_char())
      {

         float fHeight = 18.0;

         ::write_text::font_pointer f(e_create, this);

         /*f->create_pixel_font(pnode->font_name(e_font_sans_ex), (i32)height(rectangleClient) * 0.7);

         float fMargin = (height(rectangleClient) * ((1.0f - 0.7f) / 2.0f));*/

         auto psystem = get_system()->m_pcoresystem;

         auto pnode = psystem->node();

         f->create_point_font(pnode->font_name(e_font_sans_ex), fHeight * 1.0);


         pgraphics->set(f);

         pgraphics->set_text_color(colorBorderOut);
         pgraphics->text_out((int)(49 * rx), (int)(49 * ry), m_strCred);
      }

      else if (m_picon95)
      {

         pgraphics->draw_ca2_border2((int)(49 * rx), (int)(49 * ry) - 11, (int)((91 + 2 + 2) * ry), 1, 1, colorBackground, color, colorBorderOut, colorBorderIn);

         image_source imagesource(m_picon95);

         auto rectangleTarget = rectangle_f64_dimension((int)(49 * rx) + 2, (int)(49 * ry) + 2 - 11, (int)((91 + 2 + 2) * ry), (int)((91 + 2 + 2) * ry));

         image_drawing_options imagedrawingoptions(rectangleTarget);

         image_drawing imagedrawing(imagedrawingoptions, imagesource);

         pgraphics->draw(imagedrawing);

      }
      else
      {

         pgraphics->draw_ca2_with_border2((int)(49 * rx), (int)(49 * ry) - 23, (int)((91 + 2 + 2) * ry), 1, 1, colorBackground, color, colorBorderOut, colorBorderIn);

      }

   }


   bool login::on_action(const ::string & pszId)
   {

      if (!strcmp(pszId, "submit"))
      {

         if (m_bSubmitted)
         {

            return true;

         }

         m_bSubmitted = true;

         auto puiParent = get_parent();
         
         if(puiParent)
         {

            puiParent->display(e_display_none);
            
         }

         string strText;

         m_peditPassword->_001GetText(strText);

         m_iPasswordOriginalLength = strText.get_length();

         if(!m_bCred)
         {

            auto psystem = acmesystem()->m_paurasystem;

            strText = psystem->crypto()->nessie(strText);

            m_peditPassword->_001SetText(strText,::e_source_database);

         }
         
         if(puiParent)
         {

            puiParent->EndModalLoop("ok");
            
         }

         return true;

      }
      else if (!strcmp(pszId, "submit_timer"))
      {

         if (m_bSubmitted)
         {

            return true;

         }

         m_bSubmitted = true;

         auto puiParent = get_parent();

         if (puiParent)
         {

            puiParent->display(e_display_none);

         }

         if (puiParent)
         {

            puiParent->EndModalLoop("ok");

         }

         return true;

      }
      else if (!strcmp(pszId, "escape"))
      {

         m_bSubmitted = true;

         get_parent()->display(e_display_none);

         m_peditPassword->_001SetText("",::e_source_database);

         get_parent()->EndModalLoop("cancel");

         return true;

      }

      return false;

   }


   void login::on_message_create(::message::message * pmessage)
   {

      ::pointer<::message::create>pcreate(pmessage);

      if(pcreate->previous())
      {

         return;

      }
      m_pstillUser->create_control(this, "label_user");
         m_peditUser->create_control(this, "edit_user");
         m_pstillPassword->create_control(this, "label_password");
         m_peditPassword->create_control(this, "password");
         m_pbutton->create_control(this, "submit");
         m_pbuttonClose->create_control(this, "escape");

      //if(!m_pstillUser->create_control(this,"label_user")
      //      || !m_peditUser->create_control(this,"edit_user")
      //      || !m_pstillPassword->create_control(this,"label_password")
      //      || !m_peditPassword->create_control(this,"password")
      //      || !m_pbutton->create_control(this,"submit")
      //      || !m_pbuttonClose->create_control(this,"escape"))
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

      int stdw = 800;
      int stdh = 177 + 23 + 1140;

      set_placement(0,0,stdw,stdh);

      m_peditUser->set_keyboard_focus();

      display(::e_display_restored, e_activation_no_activate);

   }


   void login::_000OnDraw(::draw2d::graphics_pointer & pgraphics)
   {

      return ::user::interaction::_000OnDraw(pgraphics);

   }


   void login::_001DrawChildren(::draw2d::graphics_pointer & pgraphics)
   {

      return ::user::interaction::_001DrawChildren(pgraphics);

   }


} // namespace account



