#include "framework.h"
//#include "ios_window.h"


#define MAX_LOADSTRING 100

/*
namespace account
{


   class account :
      virtual public ::spa::style,
      virtual public ::simple_ui,
      virtual public ::spa_login::callback,
      virtual public ::boot_window
   {
   public:

      static account s_account;

      spa_login::e_result  m_eresult;

      string               m_strTitle;
      string               m_strWindowClass;

      int                  m_w;
      int                  m_h;
      spa_login            m_login;
      simple_graphics      m_graphics;
      simple_bitmap        m_bitmap;
      ::size_i32                 m_size;
      ::point_i32                m_point;
      bool                 m_bLButtonDown;
      ::point_i32                m_pointLButtonDown;
      ::point_i32                m_pointLButtonDownPos;

      oswindow             m_oswindow;

      bool                 m_bShiftKey;

      bool                 m_bDrag;
      ::rectangle_i32               m_rectangleDesktop;

      manual_reset_event   m_eventReady;


      bool                 m_bVisible;


      account();

      virtual ~account();

      virtual string show_auth_window(::rectangle_i32 * lprect, string & strUsername, string & strSessId, string & strServerId, string & strLoginUrl, string strFontopusServer);

      virtual bool prepare_window(bool bShow);

      virtual void client_to_screen(::point_i32 * ppt);

      virtual void screen_to_client(::point_i32 * ppt);

      virtual void window_rectangle(::rectangle_i32 * prectangle);

      virtual void this->rectangle(::rectangle_i32 * prectangle);

      virtual void draw_dark_glass(simple_graphics & g);
      virtual void draw_pestana(simple_graphics &g);
      virtual void draw_auth_box(simple_graphics &g);


      virtual void draw(simple_graphics & g);


      virtual void draw_fuzzy_color_spread(simple_graphics & g);

      virtual bool on_lbutton_down(i32 x, i32 y);
      virtual bool on_lbutton_up(i32 x, i32 y);
      virtual bool on_mouse_move(i32 x, i32 y);


//      virtual bool on_windows_key_down(wparam wparam, lparam lparam);
  //    virtual bool on_windows_key_up(wparam wparam, lparam lparam);

    //  virtual void on_windows_gdi_draw_framebuffer();

      //virtual bool on_windows_move(i32 x, i32 y);
      //virtual bool on_windows_size(i32 cx, i32 cy);

      virtual bool on_action(const ::scoped_string & scopedstrId);

      virtual void login_result(::spa_login::e_result eresult);




   };







   ::u8 brate(double dRate, double dMin, double dMax)
   {

      return (::u8)(dRate * (dMax - dMin) + dMin);

   }


   void account::draw_auth_box(simple_graphics & g)
   {

      ::rectangle_i32 rectangle;

      this->rectangle(rectangle);

      g.set_alpha_mode(draw2d::e_alpha_mode_blend);

      // front
      point_i32 pa[4];  //  0       1
      //
      //
      //  3       2

      // back
      point_i32 pb[4];


      // guards
      point_i32 pc[4];


      pa[0].x() = rectangle.left();
      pa[0].y() = rectangle.top();
      pa[1].x() = rectangle.right() - rectangle.width() / 10;
      pa[1].y() = rectangle.top() + rectangle.height() / 10;
      pa[2].x() = rectangle.right() - rectangle.width() / 8;
      pa[2].y() = rectangle.bottom() - rectangle.height() / 10;
      pa[3].x() = rectangle.left();
      pa[3].y() = rectangle.bottom();


      pb[0].x() = rectangle.left() + rectangle.width() / 6;
      pb[0].y() = rectangle.top() + rectangle.height() / 6;
      pb[1].x() = rectangle.right() - rectangle.width() / 6;
      pb[1].y() = rectangle.top() + rectangle.height() / 6;
      pb[2].x() = rectangle.right() - rectangle.width() / 5;
      pb[2].y() = rectangle.bottom() - rectangle.height() / 4;
      pb[3].x() = rectangle.left() + rectangle.width() / 5;
      pb[3].y() = rectangle.bottom() - rectangle.height() / 4;

      {

         simple_brush b;

         b.create_solid(g, argb(184, 220, 220, 220));

         g.select(b);

         g.fill_polygon(pb, 4, ::draw2d::e_fill_mode_winding);

         simple_pen p;

         p.create_solid(g, argb(192, 192, 192, 192));

         g.select(p);

         g.draw_polygon(pb, 4, ::draw2d::e_fill_mode_winding);


      }













      // top
      ::memory_copy(pc, pa, sizeof(pb));
      pc[2].x() = pb[1].x();
      pc[2].y() = pb[1].y();
      pc[3].x() = pb[0].x();
      pc[3].y() = pb[0].y();

      {

         simple_brush b;

         b.create_solid(g, argb(177, 210, 210, 210));

         g.select(b);

         g.fill_polygon(pc, 4, ::draw2d::e_fill_mode_winding);

         simple_pen p;

         p.create_solid(g, argb(177, 177, 177, 177));

         g.select(p);

         g.draw_polygon(pc, 4, ::draw2d::e_fill_mode_winding);


      }
      // left
      ::memory_copy(pc, pa, sizeof(pb));
      pc[1].x() = pb[0].x();
      pc[1].y() = pb[0].y();
      pc[2].x() = pb[3].x();
      pc[2].y() = pb[3].y();
      {

         simple_brush b;

         b.create_solid(g, argb(123, 123, 123, 123));

         g.select(b);

         g.fill_polygon(pc, 4, ::draw2d::e_fill_mode_winding);

         simple_pen p;

         p.create_solid(g, argb(123, 90, 90, 90));

         g.select(p);

         g.draw_polygon(pc, 4, ::draw2d::e_fill_mode_winding);


      }
      // bottom
      ::memory_copy(pc, pa, sizeof(pb));
      pc[0].x() = pb[3].x();
      pc[0].y() = pb[3].y();
      pc[1].x() = pb[2].x();
      pc[1].y() = pb[2].y();
      {

         simple_brush b;

         b.create_solid(g, argb(149, 192, 192, 192));

         g.select(b);

         g.fill_polygon(pc, 4, ::draw2d::e_fill_mode_winding);

         simple_pen p;

         p.create_solid(g, argb(149, 177, 177, 177));

         g.select(p);

         g.draw_polygon(pc, 4, ::draw2d::e_fill_mode_winding);


      }
      // right
      ::memory_copy(pc, pa, sizeof(pb));
      pc[0].x() = pb[1].x();
      pc[0].y() = pb[1].y();
      pc[3].x() = pb[2].x();
      pc[3].y() = pb[2].y();
      {

         simple_brush b;

         b.create_solid(g, argb(84, 149, 149, 149));

         g.select(b);

         g.fill_polygon(pc, 4, ::draw2d::e_fill_mode_winding);

         simple_pen p;

         p.create_solid(g, argb(84, 123, 123, 123));

         g.select(p);

         g.draw_polygon(pc, 4, ::draw2d::e_fill_mode_winding);


      }





      {

         simple_pen p;

         p.create_solid(g, argb(184, 90, 90, 90));

         g.select(p);

         g.draw_polygon(pa, 4, ::draw2d::e_fill_mode_winding);

      }


   }


   void account::draw_pestana(simple_graphics & g)
   {

      ::rectangle_i32 rectangleWindow;

      window_rectangle(rectangleWindow);

      g.set_alpha_mode(draw2d::e_alpha_mode_blend);

      int iCount = rectangleWindow.height();
      simple_pen p;
      for (int i = 0; i < iCount; i += 2)
      {
         double dRate = (double)i / (double)iCount;
         dRate = 1.0 - dRate;
         ::u8 a1 = brate(1.0 - dRate, 23, 90);
         ::u8 r1 = brate(dRate, 23, 127);
         ::u8 g1 = brate(dRate, 23, 127);
         ::u8 b1 = brate(dRate, 23, 127);
         p.create_solid(g, argb(a1, r1, g1, b1));
         g.draw_line(rectangleWindow.left(), i, rectangleWindow.right(), i, p);

      }


   }









   account::account() :
      m_login(0, 0),
      m_eventReady(nullptr)
   {

      m_eschema = schema_normal;
      m_login.set_parent(this);
      m_login.m_pstyle = this;
      m_login.m_pcallback = this;
      m_bLButtonDown = false;
      m_w = 840;
      m_h = 284;

      m_eresult = ::spa_login::result_fail;
      m_oswindow = nullptr;

      m_bVisible = false;

   }

   account::~account()
   {
   }

   string account::show_auth_window(::rectangle_i32 * lprect, string & strUsername, string & strSessId, string & strServerId, string & strLoginUrl, string strRequestingServer)
   {

      if (lprect == nullptr)
      {
         m_rectangleDesktop.left() = 0;
         m_rectangleDesktop.top() = 0;
         m_rectangleDesktop.right() = 800;
         m_rectangleDesktop.bottom() = 600;

//         ::window_rectangle(::get_desktop_window(), &m_rectangleDesktop);

      }
      else
      {

         m_rectangleDesktop = *lprect;

      }

      // TODO: Place code here.

      m_strTitle = "account Auth Windows";
      m_strWindowClass = "account Auth Windows";


      // Perform application initialization:
      if (!prepare_window(true))
      {
         return "";
      }

      m_login.m_strRequestingServer = strRequestingServer;





      m_eventReady.wait();


      if (m_eresult == ::spa_login::result_ok)
      {

         strUsername = m_login.m_editUser.m_strText;
         strSessId = m_login.m_strSessId;
         strServerId = m_login.m_strSecureId;
         strLoginUrl = m_login.m_strLoginUrl;

         return "ok";

      }
      else
      {

         return "fail";

      }


   }




   //
   //   FUNCTION: prepare_window(HINSTANCE, int)
   //
   //   PURPOSE: Saves instance handle and creates main window
   //
   //   COMMENTS:
   //
   //        In this function, we save the instance handle in a global variable and
   //        create and display the main program window.
   //
   bool account::prepare_window(bool bShow)
   {

      rectangle_i32 & rectangleDesktop = m_rectangleDesktop;

      CGRect rectangleFontopus;

      int w = m_w + 184;
      int h = m_h + 284;

      rectangleFontopus.origin.x() = rectangleDesktop.left() + (width(rectangleDesktop) - w) / 2;
      rectangleFontopus.origin.y() = rectangleDesktop.top() + (height(rectangleDesktop) - h) / 3;
      rectangleFontopus.size.width = w;
      rectangleFontopus.size.height = h;


      m_login.m_rectangle.left() = (w - m_w) / 2;
      m_login.m_rectangle.top() = (h - m_h) / 2;
      m_login.m_rectangle.right() = m_w;
      m_login.m_rectangle.bottom() = m_h;

      m_login.defer_translate(this);

      m_oswindow = oswindow_get(new_boot_window(this, rectangleFontopus));



      if (!m_oswindow)
      {
         return false;
      }

      m_login.on_layout(pgraphics);

//      SetTimer(m_oswindow, 123, 23, nullptr);

      XXXShowWindow(m_oswindow, e_display_normal);



      return true;

   }

   void account::boot_window_draw(CGContextRef pgraphics)
   {

      simple_graphics g;

      g.m_pdc = pgraphics;

      draw(g);

      g.m_pdc = nullptr;

   }

   void account::boot_window_mouse_down(double x, double y)
   {
      on_lbutton_down(x, y);
   }

   void account::boot_window_mouse_up(double x, double y)
   {
      on_lbutton_up(x, y);
   }

   void account::boot_window_mouse_moved(double x, double y)
   {
      on_mouse_move(x, y);
   }

   void account::boot_window_mouse_dragged(double x, double y)
   {
      set_window_position(m_oswindow, nullptr, x, y, 0, 0, SWP_NOZORDER | SWP_NOSIZE);
   }

   bool account::boot_window_key_down(::user::enum_key ekey)
   {
      return true;
   }

   bool account::boot_window_key_up(::user::enum_key ekey)
   {
      return true;
   }




   void account::client_to_screen(::point_i32 * ppt)
   {
      ::client_to_screen(m_oswindow, ppt);
   }

   void account::screen_to_client(::point_i32 * ppt)
   {
      ::screen_to_client(m_oswindow, ppt);
   }

   bool account::on_lbutton_down(i32 x, i32 y)
   {

      ::client_to_screen(m_oswindow, &m_pointLButtonDown);

      if (m_login.on_lbutton_down(x, y))
         return true;

      m_bLButtonDown = true;
      m_bDrag = false;

      m_pointLButtonDownPos = m_point;
      ::GetCursorPos(&m_pointLButtonDown);

      return true;
   }

   bool account::on_lbutton_up(i32 x, i32 y)
   {

      m_bLButtonDown = false;

      if (m_login.on_lbutton_up(x, y))
         return true;


      ::rectangle_i32 rectangleLogin;

      m_login.window_rectangle(rectangleLogin);

      ::point_i32 point(x, y);

      if (rectangleLogin.is_empty().contains(point))
      {
      release_capture();
      DestroyWindow(m_oswindow);
      }


            {
      ::rectangle_i32 rectangleWindow;
      m_login.window_rectangle(&rectangleWindow);
      ::point_i32 pointCursor;
      ::GetCursorPos(&pointCursor);
      if (rectangleWindow.is_empty().contains(pointCursor))
      DestroyWindow(hWnd);
      }

      return true;


   }

   bool account::on_mouse_move(i32 x, i32 y)
   {

      if (m_bLButtonDown)
      {
         if (!m_bDrag)
         {
            m_bDrag = true;
            ::point_i32 ptNow;
            ::GetCursorPos(&ptNow);
            m_point.x() = ptNow.x() - m_pointLButtonDown.x() + m_pointLButtonDownPos.x();
            m_point.y() = ptNow.y() - m_pointLButtonDown.y() + m_pointLButtonDownPos.y();
            set_window_position(m_oswindow, nullptr, m_point.x(), m_point.y(), 0, 0, SWP_NOSIZE | SWP_NOZORDER);
            m_bDrag = false;
         }
         return true;
      }

      if (m_login.on_mouse_move(x, y))
         return true;

      return true;

   }


   void account::window_rectangle(::rectangle_i32 * prectangle)
   {
      ::window_rectangle(m_oswindow, prectangle);
   }
   void account::this->rectangle(::rectangle_i32 * prectangle)
   {

      ::this->rectangle(m_oswindow, prectangle);

   }

   void account::draw_dark_glass(simple_graphics & g)
   {

      ::rectangle_i32 rectangleWindow;

      window_rectangle(rectangleWindow);


      g.fill_rectangle(rectangleWindow, argb(84, 127, 127, 127));

   }


   void account::draw(simple_graphics & g)
   {

      //draw_pestana(g);

      draw_auth_box(g);

      simple_ui::draw(g);

   }


   void account::draw_fuzzy_color_spread(simple_graphics & g)
   {

      ::rectangle_i32 rectangleWindow;

      window_rectangle(rectangleWindow);

      int i = 0;
      int j = 0;
      int iCount = rectangleWindow.width();
      int jCount = rectangleWindow.height();

      ::u8 * p = (::u8 *) m_bitmap.m_pdata;

      for (i = 0; i < iCount; i++)
      {
         for (j = 0; j < jCount; j++)
         {
            double dPhase = fmod((((double) ::get_tick() * 360 * 0.5984 / 1000.0) + (i * 360.0 / (double)iCount) + (j * 360.0 / (double)jCount) + ((double)(sin(((double) ::get_tick() * 3.1415 * 2.0  *0.0484 / 1000.0) + i * 3.1415 * 2.0 * 2.0 / (double)(iCount)) * sin(((double) ::get_tick() * 3.1415 * 2.0  * 0.0484 / 1000.0) + j * 3.1415 * 2.0 * 2.0 / (double)(jCount)) * 360))), 360.0);
            i32 iR;
            i32 iG;
            i32 iB;
            double dRate = fmod(dPhase, 60.0) / 60.0;
            i32 iColor = (i32)(dRate * 155.0);
            if (dPhase < 60)
            {
               // purple to blue
               iR = 255 - iColor;
               iG = 100;
               iB = 255;
            }
            else if (dPhase < (120))
            {
               // blue to cyan
               iR = 100;
               iG = 100 + iColor;
               iB = 255;
            }
            else if (dPhase < (180))
            {
               // cyan to green
               iR = 100;
               iG = 255;
               iB = 255 - iColor;
            }
            else if (dPhase < (240))
            {
               // green to yellow
               iR = 100 + iColor;
               iG = 255;
               iB = 100;
            }
            else if (dPhase < (300))
            {
               // yellow to red
               iR = 255;
               iG = 255 - iColor;
               iB = 100;
            }
            else
            {
               // red to purple
               iR = 255;
               iG = 100;
               iB = 100 + iColor;
            }

            p[0] = iR;
            p[1] = iG;
            p[2] = iB;
            p[3] = 84;
            p += 4;

         }
      }



   }



   bool account::on_action(const ::scoped_string & scopedstrId)
   {

      if (!strcmp(pszId, "submit"))
      {


         ::XXXShowWindow(m_oswindow, SW_HIDE);

         m_login.login_result(m_login.login());

         if (m_eresult == ::spa_login::result_fail)
         {
            ::XXXShowWindow(m_oswindow, e_display_normal);
         }
         else
         {
            m_eventReady.set_event();
         }

         return true;

      }
      else if (!strcmp(pszId, "escape"))
      {
         m_eventReady.set_event();
      }

      return false;


   }


   void account::login_result(::spa_login::e_result eresult)
   {

      m_eresult = eresult;

   }



   account account::s_account;

   string CLASS_DECL_BOOT show_auth_window(::rectangle_i32 * lprect, string & strUsername, string & strSessId, string & strServerId, string & strLoginUrl, string strFontopusServer)
   {

      return ::account::account::s_account.show_auth_window(lprect, strUsername, strSessId, strServerId, strLoginUrl, strFontopusServer);

   }




} // namespace account


*/

