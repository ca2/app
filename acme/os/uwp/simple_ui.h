#pragma once


namespace os
{


   class CLASS_DECL_ACME simple_ui :
      virtual public ::user::interaction
   {
   public:


      string                     m_strTitle;
      string                     m_strWindowClass;

      int                        m_w;
      int                        m_h;
      SIZE                       m_size;
      POINT                      m_point;
      bool                       m_bLButtonDown;
      POINT                      m_pointLButtonDown;
      POINT                      m_pointLButtonDownPos;

      bool                       m_bShiftKey;

      oswindow                   m_window;
      bool                       m_bDrag;
      manual_reset_event         m_eventReady;


      ::rect                     m_rectDesktop;

      bool                       m_bNoDecorations;

      point                      m_pointCursor;


      simple_ui(::elemental * pobject);
      virtual ~simple_ui();



      virtual void get_cursor_pos(POINT * ppt);

      //void draw(ID2D1DeviceContext * pctx);



      //virtual string interactive_auth(LPRECT lprect, string & strUsername, string & strSessId, string & strServerId, string & strLoginUrl, string strFontopusServer);


      virtual bool create_window(LPCRECT lpcrect);

      virtual bool prepare_window(LPCRECT lpcrect);


      virtual bool show_window(bool bShow = true);


      virtual bool destroy_window();

      virtual bool run_loop();


      virtual void get_window_rect(RECT * prect);
      virtual void get_client_rect(RECT * prect);


      /*
      virtual bool on_lbutton_up(i32 x, i32 y);
      virtual bool on_lbutton_down(i32 x, i32 y);
      virtual bool on_mouse_move(i32 x, i32 y);
      virtual bool on_char(i32 iKey, const string & strChar);
      */

      //virtual bool on_windows_key_down(WPARAM wparam, LPARAM lparam);
      //virtual bool on_windows_key_up(WPARAM wparam, LPARAM lparam);


      virtual bool set_window_pos(int x, int y, int cx, int cy, bool bShow);
      virtual bool move_window(int x, int y);

      void viewport_client_to_screen(POINT * ppt);
      void viewport_screen_to_client(POINT * ppt);

      void _001ClientToScreen(POINT * ppt);
      void _001ScreenToClient(POINT * ppt);

      void _001ClientToScreen(RECT * prect);
      void _001ScreenToClient(RECT * prect);

      void get_window_rect(RECT * prect);

      virtual void set_capture();
      virtual void release_capture();


   };

  


} // namespace account






