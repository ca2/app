#include "framework.h"
#include "account_login.h"


namespace account
{


   login::login()
   {

      m_bSubmitted = false;

      m_iPasswordOriginalLength = -1;


      m_bSelfLayout = false;

      m_picon95 = nullptr;

#if defined(WINDOWS_DESKTOP)

      {

         HICON hicon95 = (HICON) ::LoadImage(::GetModuleHandle(nullptr),MAKEINTRESOURCE(95),IMAGE_ICON,95,95,LR_VGACOLOR);

         if(hicon95 != nullptr)
         {

            m_picon95 = new ::draw2d::icon;

            m_picon95->attach_os_data(hicon95);

         }

      }

#endif
      m_bCred = false;

   }


   login::~login()
   {

   }


   void login::install_message_routing(::channel * pchannel)
   {

      ::user::interaction::install_message_routing(pchannel);

      IGUI_MSG_LINK(WM_CREATE, pchannel, this, &login::_001OnCreate);

   }


   void login::defer_translate(const string & strUser,const string & strPass,const string & strOpen)
   {

      if (strUser.has_char())
      {

         m_plabelUser->set_window_text(strUser);

      }

      if (strPass.has_char())
      {

         m_plabelPassword->set_window_text(strPass);

      }

      if (strOpen.has_char())
      {

         m_ptap->set_window_text(strOpen);

      }

   }


   ::estatus login::initialize(::object * pobjectContext)
   {

      auto estatus = ::user::interaction::initialize(pobjectContext);
      
      if (!estatus)
      {

         return estatus;

      }
      
      m_bSubmitted = false;

      if (!(estatus = __compose_new(m_plabelUser))) return false;
      if(!(estatus = __compose_new(m_peditUser))) return false;
      if (!(estatus = __compose_new(m_plabelPassword))) return false;
      if (!(estatus = __compose_new(m_ppassword))) return false;
      if (!(estatus = __compose_new(m_ptap))) return false;
      if (!(estatus = __compose_new(m_ptapClose))) return false;

      return estatus;

   }


   void login::on_layout(::draw2d::graphics_pointer & pgraphics)
   {

      auto rectClient = get_client_rect();

      if(rectClient.is_empty())
      {

         return;

      }

      int stdw = 800;

      int stdh = 400;

      int h;

      int w;

      w = (int)(rectClient.width());

      h = (int)(rectClient.height());

      m_dRateX = (double)w / (double)stdw;

      m_dRateY = (double)h / (double)stdh;

      double rx = m_dRateX;

      double ry = m_dRateY;

      i32 x1 = (int) (49 * rx);

      i32 w2 = (int) ((rectClient.width() - 49 * 2 * rx));

      i32 h1 = (int) (23 * ry);

      i32 pad = (int) (5 * ry);

      i32 y = (int) ((49 + 86) * ry);

      m_plabelUser->set_dim(x1,y,w2,h1);
      m_plabelUser->display(::display_normal, false);

      y += h1 + pad;

      m_peditUser->set_dim(x1,y,w2, h1);
      m_peditUser->display(::display_normal, false);

      y += h1 + pad;

      m_plabelPassword->set_dim(x1,y,w2, h1);
      m_plabelPassword->display(::display_normal, false);

      y += h1 + pad;

      m_ppassword->set_dim(x1,y,w2,h1);
      m_ppassword->display(::display_normal, false);

      y += h1 + pad;

      y += pad + h1 + pad;

      m_ptap->set_dim(x1,y,w2,h1 * 3);
      m_ptap->display(::display_normal, false);

      m_ptapClose->set_dim(w - 36,12,24,24);
      m_ptapClose->display(::display_normal, false);

   }


   void login::_001OnDraw(::draw2d::graphics_pointer & pgraphics)
   {

      simple_ui_draw_frame_window_rect(pgraphics);

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

      if (m_pimage->is_set() && m_pimage->height() > 21)
      {

         double r = (double)(64) / (double)m_pimage->height();

         pgraphics->StretchBlt(
         (int)(49 * rx), (int)(49 * ry) + 2 - 11,
         i32 (m_pimage->width() * r), i32 (m_pimage->height() * r),
         m_pimage->g(),
         0, 0, m_pimage->width(), m_pimage->height(), 0);

      }
      else if (m_bCred && m_strCred.has_char())
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


   bool login::on_action(const char * pszId)
   {

      if (!strcmp(pszId, "submit"))
      {

         if (m_bSubmitted)
         {

            return true;

         }

         m_bSubmitted = true;

         auto puiParent = GetParent();
         
         if(puiParent)
         {

            puiParent->display(display_none);
            
         }

         string strText;

         m_ppassword->_001GetText(strText);

         m_iPasswordOriginalLength = strText.get_length();

         if(!m_bCred)
         {

            strText = System.crypto().nessie(strText);

            m_ppassword->_001SetText(strText,::source_database);

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

         auto puiParent = GetParent();

         if (puiParent)
         {

            puiParent->display(display_none);

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

         GetParent()->display(display_none);

         m_ppassword->_001SetText("",::source_database);

         GetParent()->EndModalLoop("cancel");

         return true;

      }

      return false;

   }


   void login::_001OnCreate(::message::message * pmessage)
   {

      SCAST_PTR(::message::create,pcreate,pmessage);

      if(pcreate->previous())
      {

         return;

      }

      if(!m_plabelUser->create_window(this,"label_user")
            || !m_peditUser->create_window(this,"edit_user")
            || !m_plabelPassword->create_window(this,"label_password")
            || !m_ppassword->create_window(this,"password")
            || !m_ptap->create_window(this,"submit")
            || !m_ptapClose->create_window(this,"escape"))
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

      int stdw = 800;
      int stdh = 177 + 23 + 1140;

      set_dim(0,0,stdw,stdh);

      m_peditUser->keyboard_set_focus();

      display(::display_normal, false);

   }


   void login::_000OnDraw1(::draw2d::graphics_pointer & pgraphics)
   {

      return ::user::interaction::_000OnDraw1(pgraphics);

   }


   void login::_001DrawChildren(::draw2d::graphics_pointer & pgraphics)
   {

      return ::user::interaction::_001DrawChildren(pgraphics);

   }


} // namespace account



