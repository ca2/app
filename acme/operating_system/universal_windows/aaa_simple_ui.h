#pragma once


namespace os
{


   class CLASS_DECL_ACME simple_ui :
      virtual public ::user::interaction
   {
   public:


      string                     m_strTitle;
      string                     m_strWindowClass;

      ::i32                        m_w;
      ::i32                        m_h;
      ::i32_size                       m_size;
      ::i32_point                      m_point;
      bool                       m_bLButtonDown;
      ::i32_point                      m_pointLButtonDown;
      ::i32_point                      m_pointLButtonDownPos;

      bool                       m_bShiftKey;

      oswindow                   m_window;
      bool                       m_bDrag;
      manual_reset_happening         m_happeningReady;


      ::i32_rectangle                     m_rectangleDesktop;

      bool                       m_bNoDecorations;

      i32_point                      m_pointCursor;


      simple_ui(::particle * pparticle);
      virtual ~simple_ui();



      virtual void get_cursor_position(::i32_point * ppt);

      //void draw(ID2D1DeviceContext * pctx);



      //virtual string interactive_auth(::i32_rectangle * lprect, string & strUsername, string & strSessId, string & strServerId, string & strLoginUrl, string strFontopusServer);


      virtual bool create_window(const ::i32_rectangle * lpcrect);

      virtual bool prepare_window(const ::i32_rectangle * lpcrect);


      virtual bool show_window(bool bShow = true);


      virtual bool destroy_window();

      virtual bool run_loop();


      virtual void window_rectangle(::i32_rectangle * prectangle);
      virtual void this->rectangle(::i32_rectangle * prectangle);


      /*
      virtual bool on_lbutton_up(::i32 x, ::i32 y);
      virtual bool on_lbutton_down(::i32 x, ::i32 y);
      virtual bool on_mouse_move(::i32 x, ::i32 y);
      virtual bool on_char(::i32 iKey, const ::scoped_string & scopedstrChar);
      */

      //virtual bool on_windows_key_down(wparam wparam, lparam lparam);
      //virtual bool on_windows_key_up(wparam wparam, lparam lparam);


      virtual bool set_window_position(::i32 x, ::i32 y, ::i32 cx, ::i32 cy, bool bShow);
      virtual bool move_window(::i32 x, ::i32 y);

      void viewport_client_to_screen(::i32_point * ppt);
      void viewport_screen_to_client(::i32_point * ppt);

      void client_to_screen(::i32_point * ppt);
      void screen_to_client(::i32_point * ppt);

      void client_to_screen(::i32_rectangle * prectangle);
      void screen_to_client(::i32_rectangle * prectangle);

      void window_rectangle(::i32_rectangle * prectangle);

      virtual void set_capture();
      virtual void release_capture();


   };

  


} // namespace account






