#pragma once


namespace os
{


   class CLASS_DECL_AURA simple_ui :
      virtual public ::user::interaction
   {
   public:


      string                     m_strTitle;
      string                     m_strWindowClass;

      int                        m_w;
      int                        m_h;
      SIZE_I32                       m_size;
      POINT_I32                      m_point;
      bool                       m_bLButtonDown;
      POINT_I32                      m_pointLButtonDown;
      POINT_I32                      m_pointLButtonDownPos;

      bool                       m_bShiftKey;

      oswindow                   m_window;
      bool                       m_bDrag;
      manual_reset_event         m_eventReady;


      ::rectangle_i32                     m_rectDesktop;

      bool                       m_bNoDecorations;

      point_i32                      m_pointCursor;


      simple_ui(::layered * pobjectContext);
      virtual ~simple_ui();



      virtual void get_cursor_position(POINT_I32 * ppt);

      //void draw(ID2D1DeviceContext * pctx);



      //virtual string interactive_auth(RECTANGLE_I32 * lprect, string & strUsername, string & strSessId, string & strServerId, string & strLoginUrl, string strFontopusServer);


      virtual bool create_window(const RECTANGLE_I32 * lpcrect);

      virtual bool prepare_window(const RECTANGLE_I32 * lpcrect);


      virtual bool show_window(bool bShow = true);


      virtual bool destroy_window();

      virtual bool run_loop();


      virtual void get_window_rect(RECTANGLE_I32 * prectangle);
      virtual void get_client_rect(RECTANGLE_I32 * prectangle);


      /*
      virtual bool on_lbutton_up(i32 x, i32 y);
      virtual bool on_lbutton_down(i32 x, i32 y);
      virtual bool on_mouse_move(i32 x, i32 y);
      virtual bool on_char(i32 iKey, const string & strChar);
      */

      //virtual bool on_windows_key_down(wparam wparam, lparam lparam);
      //virtual bool on_windows_key_up(wparam wparam, lparam lparam);


      virtual bool set_window_position(int x, int y, int cx, int cy, bool bShow);
      virtual bool move_window(int x, int y);

      void viewport_client_to_screen(POINT_I32 * ppt);
      void viewport_screen_to_client(POINT_I32 * ppt);

      void _001ClientToScreen(POINT_I32 * ppt);
      void _001ScreenToClient(POINT_I32 * ppt);

      void _001ClientToScreen(RECTANGLE_I32 * prectangle);
      void _001ScreenToClient(RECTANGLE_I32 * prectangle);

      void get_window_rect(RECTANGLE_I32 * prectangle);

      virtual void set_capture();
      virtual void release_capture();


   };

  


} // namespace account






