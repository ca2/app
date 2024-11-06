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
      ::int_size                       m_size;
      ::int_point                      m_point;
      bool                       m_bLButtonDown;
      ::int_point                      m_pointLButtonDown;
      ::int_point                      m_pointLButtonDownPos;

      bool                       m_bShiftKey;

      oswindow                   m_window;
      bool                       m_bDrag;
      manual_reset_event         m_eventReady;


      ::int_rectangle                     m_rectangleDesktop;

      bool                       m_bNoDecorations;

      int_point                      m_pointCursor;


      simple_ui(::particle * pparticle);
      virtual ~simple_ui();



      virtual void get_cursor_position(::int_point * ppt);

      //void draw(ID2D1DeviceContext * pctx);



      //virtual string interactive_auth(::int_rectangle * lprect, string & strUsername, string & strSessId, string & strServerId, string & strLoginUrl, string strFontopusServer);


      virtual bool create_window(const ::int_rectangle * lpcrect);

      virtual bool prepare_window(const ::int_rectangle * lpcrect);


      virtual bool show_window(bool bShow = true);


      virtual bool destroy_window();

      virtual bool run_loop();


      virtual void window_rectangle(::int_rectangle * prectangle);
      virtual void this->rectangle(::int_rectangle * prectangle);


      /*
      virtual bool on_lbutton_up(int x, int y);
      virtual bool on_lbutton_down(int x, int y);
      virtual bool on_mouse_move(int x, int y);
      virtual bool on_char(int iKey, const ::string & strChar);
      */

      //virtual bool on_windows_key_down(wparam wparam, lparam lparam);
      //virtual bool on_windows_key_up(wparam wparam, lparam lparam);


      virtual bool set_window_position(int x, int y, int cx, int cy, bool bShow);
      virtual bool move_window(int x, int y);

      void viewport_client_to_screen(::int_point * ppt);
      void viewport_screen_to_client(::int_point * ppt);

      void client_to_screen(::int_point * ppt);
      void screen_to_client(::int_point * ppt);

      void client_to_screen(::int_rectangle * prectangle);
      void screen_to_client(::int_rectangle * prectangle);

      void window_rectangle(::int_rectangle * prectangle);

      virtual void set_capture();
      virtual void release_capture();


   };

  


} // namespace account






