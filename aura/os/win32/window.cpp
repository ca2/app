#include "framework.h"
#include "_.h"


namespace win32
{


   window::window()
   {

      m_bTranslated = false;
      m_hwnd = nullptr;

   }


   window::~window()
   {


   }


   void window::attach(HWND hwnd)
   {

      m_hwnd = hwnd;

   }


   void window::destroy_window()
   {

      if (m_hwnd == nullptr)
      {

         return;

      }

      ::DestroyWindow(m_hwnd);

      m_hwnd = nullptr;

   }


   void window::set_dlg_item_font(int iItem, font & font)
   {

      window window;
      get_dlg_item(window, iItem);
      window.set_font(font);

   }

   void window::set_dlg_item_text(int iItem, string str)
   {

      window window;
      get_dlg_item(window, iItem);
      window._set_window_text(str);

   }


   void window::set_font(font & font)
   {

      ::SendMessageW(m_hwnd, WM_SETFONT, (WPARAM)font.get_os_data(), FALSE);

   }


   void window::on_command(UINT nID)
   {

   }


   iptr window::send_message(const ::id & id, WPARAM wparam, LPARAM lparam)
   {

      return ::SendMessage(m_hwnd, emessage, wparam, lparam);

   }


   iptr window::send_message_w(const ::id & id, WPARAM wparam, LPARAM lparam)
   {

      return ::SendMessageW(m_hwnd, emessage, wparam, lparam);

   }

   void window::post_message(const ::id & id, WPARAM wparam, LPARAM lparam)
   {
      ::PostMessageW(m_hwnd, emessage, wparam, lparam);
   }

   void window::enable_window(bool bEnable)
   {

      ::EnableWindow(m_hwnd, bEnable ? TRUE : FALSE);


   }

   void window::enable_children(bool bEnable)
   {

      HWND hwnd = GetWindow(m_hwnd, GW_CHILD);

      while (hwnd != nullptr)
      {

         ::EnableWindow(hwnd, bEnable ? TRUE : FALSE);

         RedrawWindow(hwnd, nullptr, nullptr, RDW_INVALIDATE | RDW_UPDATENOW | RDW_ALLCHILDREN);

         hwnd = GetWindow(hwnd, GW_HWNDNEXT);

      }


   }

   void window::_set_window_text(const char * psz)
   {

      ::SetWindowTextW(m_hwnd, wstring(psz));

   }
   void window::redraw_window()
   {

      RedrawWindow(m_hwnd, nullptr, nullptr, RDW_INVALIDATE | RDW_UPDATENOW | RDW_ALLCHILDREN);

   }
   string window::get_window_text()
   {

      strsize s = ::GetWindowTextLengthW(m_hwnd);

      wstring wstr;

      unichar * p = wstr.get_string_buffer(s + 1);

      GetWindowTextW(m_hwnd, p, (int) (s + 1));

      wstr.release_string_buffer();

      return wstr;

   }


   void window::get_dlg_item(window & w, int iItem, string strText)
   {

      w.set_context_object(get_context_object());

      w.attach(::GetDlgItem(m_hwnd, iItem));

      if (strText.has_char())
      {

         w._set_window_text(strText);

      }

   }



   void window::set_parent(window * pwindow)
   {

      if(::is_null(pwindow))
      {

         SetParent(m_hwnd, nullptr);
      }
      else
      {

         SetParent(m_hwnd, pwindow->m_hwnd);

      }


   }

   iptr window::get_combo_sel()
   {

      return send_message(CB_GETCURSEL);

   }

   int window::get_check()
   {

      return (int) send_message(BM_GETCHECK);

   }

   void window::set_check()
   {

      send_message(BM_SETCHECK, BST_CHECKED);

   }


   void window::uncheck()
   {

      send_message(BM_SETCHECK, BST_UNCHECKED);

   }

   bool window::is_checked()
   {

      return get_check() == BST_CHECKED;

   }

   void window::show_window(int nCmdShow)
   {

      ::ShowWindow(m_hwnd, nCmdShow);

   }


   void window::set_combo_sel(index iSel)
   {

      send_message(CB_SETCURSEL, (WPARAM) iSel);

   }


   void window::fill_combo(const string_array & stra)
   {

      for (index i = 0; i < stra.get_size(); i++)
      {

         string strItem = stra[i];

         wstring wstr(strItem);

         send_message_w(CB_ADDSTRING, 0, (LPARAM)wstr.c_str());

      }

   }


} // namespace win32


