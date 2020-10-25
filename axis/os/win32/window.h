#pragma once


namespace win32
{


   class CLASS_DECL_AXIS window :
      virtual public ::object
   {
   public:


#ifdef WINDOWS
      HWND m_hwnd;
#endif


      bool        m_bTranslated;


      window();
      virtual ~window();


      void attach(HWND hwnd);

      void destroy_window();

      void set_dlg_item_font(int iItem, font & font);

      void set_dlg_item_text(int iItem, string str);

      void set_font(font & font);

      virtual void get_dlg_item(window & w, int iItem, string strText = "");

      virtual void on_command(UINT nID);

      iptr send_message(const ::id & id, WPARAM wparam = 0, LPARAM lparam = 0);
      iptr send_message_w(const ::id & id, WPARAM wparam = 0, LPARAM lparam = 0);
      void post_message(const ::id & id, WPARAM wparam = 0, LPARAM lparam = 0);


      void enable_window(bool bEnable = true);

      void enable_children(bool bEnable = true);

      void _set_window_text(const char * psz);
      //void s_set_window_text(const char * psz);

      void set_parent(window * pwindow);

      void show_window(int nCmdShow);

      string get_window_text();
      void redraw_window();

      iptr get_combo_sel();
      void set_combo_sel(index iSel);
      void fill_combo(const string_array & stra);


      int get_check();

      void set_check();

      void uncheck();

      bool is_checked();

   };


} // namespace win32


