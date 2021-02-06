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
      SIZE32                 m_size;
      POINT32                m_point;
      bool                 m_bLButtonDown;
      POINT32                m_pointLButtonDown;
      POINT32                m_pointLButtonDownPos;

      oswindow             m_oswindow;

      bool                 m_bShiftKey;

      bool                 m_bDrag;
      ::rect               m_rectDesktop;

      manual_reset_event   m_eventReady;


      bool                 m_bVisible;


      account();

      virtual ~account();

      virtual string show_auth_window(RECTANGLE_I32 * lprect, string & strUsername, string & strSessId, string & strServerId, string & strLoginUrl, string strFontopusServer);

      virtual bool prepare_window(bool bShow);

      virtual void _001ClientToScreen(POINT32 * ppt);

      virtual void _001ScreenToClient(POINT32 * ppt);

      virtual void get_window_rect(RECT32 * prect);

      virtual void get_client_rect(RECT32 * prect);

      virtual void draw_dark_glass(simple_graphics & g);
      virtual void draw_pestana(simple_graphics &g);
      virtual void draw_auth_box(simple_graphics &g);


      virtual void draw(simple_graphics & g);


      virtual void draw_fuzzy_color_spread(simple_graphics & g);

      virtual bool on_lbutton_down(i32 x, i32 y);
      virtual bool on_lbutton_up(i32 x, i32 y);
      virtual bool on_mouse_move(i32 x, i32 y);


//      virtual bool on_windows_key_down(WPARAM wparam, LPARAM lparam);
  //    virtual bool on_windows_key_up(WPARAM wparam, LPARAM lparam);

    //  virtual void on_windows_gdi_draw_framebuffer();

      //virtual bool on_windows_move(i32 x, i32 y);
      //virtual bool on_windows_size(i32 cx, i32 cy);

      virtual bool on_action(const char * pszId);

      virtual void login_result(::spa_login::e_result eresult);




   };







   byte brate(double dRate, double dMin, double dMax)
   {

      return (byte)(dRate * (dMax - dMin) + dMin);

   }


   void account::draw_auth_box(simple_graphics & g)
   {

      ::rect rect;

      get_client_rect(rect);

      g.set_alpha_mode(draw2d::alpha_mode_blend);

      // front
      point pa[4];  //  0       1
      //
      //
      //  3       2

      // back
      point pb[4];


      // guards
      point pc[4];


      pa[0].x = rect.left;
      pa[0].y = rect.top;
      pa[1].x = rect.right - rect.width() / 10;
      pa[1].y = rect.top + rect.height() / 10;
      pa[2].x = rect.right - rect.width() / 8;
      pa[2].y = rect.bottom - rect.height() / 10;
      pa[3].x = rect.left;
      pa[3].y = rect.bottom;


      pb[0].x = rect.left + rect.width() / 6;
      pb[0].y = rect.top + rect.height() / 6;
      pb[1].x = rect.right - rect.width() / 6;
      pb[1].y = rect.top + rect.height() / 6;
      pb[2].x = rect.right - rect.width() / 5;
      pb[2].y = rect.bottom - rect.height() / 4;
      pb[3].x = rect.left + rect.width() / 5;
      pb[3].y = rect.bottom - rect.height() / 4;

      {

         simple_brush b;

         b.create_solid(g, ARGB(184, 220, 220, 220));

         g.select(b);

         g.fill_polygon(pb, 4, ::draw2d::fill_mode_winding);

         simple_pen p;

         p.create_solid(g, ARGB(192, 192, 192, 192));

         g.select(p);

         g.draw_polygon(pb, 4, ::draw2d::fill_mode_winding);


      }













      // top
      ::memcpy_dup(pc, pa, sizeof(pb));
      pc[2].x = pb[1].x;
      pc[2].y = pb[1].y;
      pc[3].x = pb[0].x;
      pc[3].y = pb[0].y;

      {

         simple_brush b;

         b.create_solid(g, ARGB(177, 210, 210, 210));

         g.select(b);

         g.fill_polygon(pc, 4, ::draw2d::fill_mode_winding);

         simple_pen p;

         p.create_solid(g, ARGB(177, 177, 177, 177));

         g.select(p);

         g.draw_polygon(pc, 4, ::draw2d::fill_mode_winding);


      }
      // left
      ::memcpy_dup(pc, pa, sizeof(pb));
      pc[1].x = pb[0].x;
      pc[1].y = pb[0].y;
      pc[2].x = pb[3].x;
      pc[2].y = pb[3].y;
      {

         simple_brush b;

         b.create_solid(g, ARGB(123, 123, 123, 123));

         g.select(b);

         g.fill_polygon(pc, 4, ::draw2d::fill_mode_winding);

         simple_pen p;

         p.create_solid(g, ARGB(123, 90, 90, 90));

         g.select(p);

         g.draw_polygon(pc, 4, ::draw2d::fill_mode_winding);


      }
      // bottom
      ::memcpy_dup(pc, pa, sizeof(pb));
      pc[0].x = pb[3].x;
      pc[0].y = pb[3].y;
      pc[1].x = pb[2].x;
      pc[1].y = pb[2].y;
      {

         simple_brush b;

         b.create_solid(g, ARGB(149, 192, 192, 192));

         g.select(b);

         g.fill_polygon(pc, 4, ::draw2d::fill_mode_winding);

         simple_pen p;

         p.create_solid(g, ARGB(149, 177, 177, 177));

         g.select(p);

         g.draw_polygon(pc, 4, ::draw2d::fill_mode_winding);


      }
      // right
      ::memcpy_dup(pc, pa, sizeof(pb));
      pc[0].x = pb[1].x;
      pc[0].y = pb[1].y;
      pc[3].x = pb[2].x;
      pc[3].y = pb[2].y;
      {

         simple_brush b;

         b.create_solid(g, ARGB(84, 149, 149, 149));

         g.select(b);

         g.fill_polygon(pc, 4, ::draw2d::fill_mode_winding);

         simple_pen p;

         p.create_solid(g, ARGB(84, 123, 123, 123));

         g.select(p);

         g.draw_polygon(pc, 4, ::draw2d::fill_mode_winding);


      }





      {

         simple_pen p;

         p.create_solid(g, ARGB(184, 90, 90, 90));

         g.select(p);

         g.draw_polygon(pa, 4, ::draw2d::fill_mode_winding);

      }


   }


   void account::draw_pestana(simple_graphics & g)
   {

      ::rect rectWindow;

      get_window_rect(rectWindow);

      g.set_alpha_mode(draw2d::alpha_mode_blend);

      int iCount = rectWindow.height();
      simple_pen p;
      for (int i = 0; i < iCount; i += 2)
      {
         double dRate = (double)i / (double)iCount;
         dRate = 1.0 - dRate;
         byte a1 = brate(1.0 - dRate, 23, 90);
         byte r1 = brate(dRate, 23, 127);
         byte g1 = brate(dRate, 23, 127);
         byte b1 = brate(dRate, 23, 127);
         p.create_solid(g, ARGB(a1, r1, g1, b1));
         g.draw_line(rectWindow.left, i, rectWindow.right, i, p);

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

   string account::show_auth_window(RECTANGLE_I32 * lprect, string & strUsername, string & strSessId, string & strServerId, string & strLoginUrl, string strRequestingServer)
   {

      if (lprect == nullptr)
      {
         m_rectDesktop.left = 0;
         m_rectDesktop.top = 0;
         m_rectDesktop.right = 800;
         m_rectDesktop.bottom = 600;

//         ::get_window_rect(::get_desktop_window(), &m_rectDesktop);

      }
      else
      {

         m_rectDesktop = *lprect;

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

      rect & rectDesktop = m_rectDesktop;

      CGRect rectFontopus;

      int w = m_w + 184;
      int h = m_h + 284;

      rectFontopus.origin.x = rectDesktop.left + (width(rectDesktop) - w) / 2;
      rectFontopus.origin.y = rectDesktop.top + (height(rectDesktop) - h) / 3;
      rectFontopus.size.width = w;
      rectFontopus.size.height = h;


      m_login.m_rect.left = (w - m_w) / 2;
      m_login.m_rect.top = (h - m_h) / 2;
      m_login.m_rect.right = m_w;
      m_login.m_rect.bottom = m_h;

      m_login.defer_translate(this);

      m_oswindow = oswindow_get(new_boot_window(this, rectFontopus));



      if (!m_oswindow)
      {
         return false;
      }

      m_login.on_layout(::draw2d::graphics_pointer & pgraphics);

//      SetTimer(m_oswindow, 123, 23, nullptr);

      ShowWindow(m_oswindow, e_display_normal);



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
      set_window_pos(m_oswindow, nullptr, x, y, 0, 0, SWP_NOZORDER | SWP_NOSIZE);
   }

   bool account::boot_window_key_down(::user::e_key ekey)
   {
      return true;
   }

   bool account::boot_window_key_up(::user::e_key ekey)
   {
      return true;
   }




   void account::_001ClientToScreen(POINT32 * ppt)
   {
      ::_001ClientToScreen(m_oswindow, ppt);
   }

   void account::_001ScreenToClient(POINT32 * ppt)
   {
      ::_001ScreenToClient(m_oswindow, ppt);
   }

   bool account::on_lbutton_down(i32 x, i32 y)
   {

      ::_001ClientToScreen(m_oswindow, &m_pointLButtonDown);

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


      ::rect rectLogin;

      m_login.get_window_rect(rectLogin);

      ::point point(x, y);

      if (rectLogin.is_empty().contains(point))
      {
      release_capture();
      DestroyWindow(m_oswindow);
      }


            {
      ::rect rectWindow;
      m_login.get_window_rect(&rectWindow);
      POINT32 pointCursor;
      ::GetCursorPos(&pointCursor);
      if (rectWindow.is_empty().contains(pointCursor))
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
            POINT32 ptNow;
            ::GetCursorPos(&ptNow);
            m_point.x = ptNow.x - m_pointLButtonDown.x + m_pointLButtonDownPos.x;
            m_point.y = ptNow.y - m_pointLButtonDown.y + m_pointLButtonDownPos.y;
            set_window_pos(m_oswindow, nullptr, m_point.x, m_point.y, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
            m_bDrag = false;
         }
         return true;
      }

      if (m_login.on_mouse_move(x, y))
         return true;

      return true;

   }


   void account::get_window_rect(RECT32 * prect)
   {
      ::get_window_rect(m_oswindow, prect);
   }
   void account::get_client_rect(RECT32 * prect)
   {

      ::get_client_rect(m_oswindow, prect);

   }

   void account::draw_dark_glass(simple_graphics & g)
   {

      ::rect rectWindow;

      get_window_rect(rectWindow);


      g.fill_rect(rectWindow, ARGB(84, 127, 127, 127));

   }


   void account::draw(simple_graphics & g)
   {

      //draw_pestana(g);

      draw_auth_box(g);

      simple_ui::draw(g);

   }


   void account::draw_fuzzy_color_spread(simple_graphics & g)
   {

      ::rect rectWindow;

      get_window_rect(rectWindow);

      int i = 0;
      int j = 0;
      int iCount = rectWindow.width();
      int jCount = rectWindow.height();

      byte * p = (byte *) m_bitmap.m_pdata;

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



   bool account::on_action(const char * pszId)
   {

      if (!strcmp(pszId, "submit"))
      {


         ::ShowWindow(m_oswindow, SW_HIDE);

         m_login.login_result(m_login.login());

         if (m_eresult == ::spa_login::result_fail)
         {
            ::ShowWindow(m_oswindow, e_display_normal);
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

   string CLASS_DECL_BOOT show_auth_window(RECTANGLE_I32 * lprect, string & strUsername, string & strSessId, string & strServerId, string & strLoginUrl, string strFontopusServer)
   {

      return ::account::account::s_account.show_auth_window(lprect, strUsername, strSessId, strServerId, strLoginUrl, strFontopusServer);

   }




} // namespace account


*/

