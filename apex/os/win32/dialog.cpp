#include "framework.h"
#include "apex/operating_system.h"


namespace win32
{


   dialog::dialog()
   {

      m_bCreated = false;
      m_bNew = true;
      m_pszResource = nullptr;

   }


   dialog::dialog(::layered* pobjectContext, const widechar * pszResource)
   {

      m_bCreated = false;
      m_bNew = true;
      m_pszResource = nullptr;

      auto estatus = initialize_dialog(pobjectContext, pszResource);

      if (!estatus)
      {

         __throw(estatus);

      }

   }

   ::e_status dialog::initialize_dialog(::layered * pobjectContext, const widechar * pszResource)
   {

      auto estatus = ::object::initialize(pobjectContext);

      if (!estatus)
      {

         return estatus;

      }

      m_pszResource = pszResource;

      return estatus;

   }


   dialog::~dialog()
   {


   }

   bool dialog::create_dialog(window * pwnd)
   {

      int i = GetThreadLocale();
      SetThreadLocale(65001);
      int i2 = GetThreadLocale();


      CreateDialogParamW((HINSTANCE) System->m_hinstance, m_pszResource,
                         pwnd == nullptr ? nullptr : pwnd->m_hwnd, &DialogProc, (LPARAM)this);

      m_bCreated = true;
      return true;

   }


#ifdef WINDOWS


   INT_PTR CALLBACK dialog::DialogProc(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam)
   {

      dialog * pdialog;

      if (message == WM_INITDIALOG)
      {

         SetWindowLongPtr(hwnd, GWLP_USERDATA, lparam);

         pdialog = (dialog *)lparam;

         pdialog->m_hwnd = hwnd;

      }
      else
      {

         pdialog = (dialog *)GetWindowLongPtr(hwnd, GWLP_USERDATA);

      }

      if (pdialog != nullptr)
      {

         return pdialog->on_dialog_message((enum_message) message, wparam, lparam);

      }

      return 0;

   }


   INT_PTR dialog::on_dialog_message(const ::id & id, wparam wparam, lparam lparam)
   {

      if (!id.is_message())
      {

         __throw(error_invalid_argument);

      }

      if (id == WM_INITDIALOG)
      {

         if (!on_init_dialog())
         {

            return 0;

         }
         //m_bCreated = true;
         return true;

      }
      else if (id == e_message_command)
      {

         if (m_bCreated)
         {

            if (HIWORD(wparam) > 3)
            {
               on_notify(HIWORD(wparam), LOWORD(wparam));
            }
            else
            {
               on_command(LOWORD(wparam));

            }

         }

      }
      else if (id == WM_NOTIFY)
      {

         on_notify((NMHDR *)lparam.m_lparam);

      }
      else if (id == e_message_close)
      {

         on_close();

         return 1;

      }

      return 0;

   }

#endif

   bool dialog::on_init_dialog()
   {

      HWND hwnd = ::GetWindow(m_hwnd, GW_CHILD);

      while (hwnd != NULL)
      {

         {

            window w;

            w.m_hwnd = hwnd;

            string strText = w.get_window_text();

            if (strText.has_char())
            {

               if (!w.m_bTranslated)
               {

                  string str = _(strText);

                  w._set_window_text(str);

                  w.m_bTranslated = true;

               }

            }

         }



         hwnd = ::GetWindow(hwnd, GW_HWNDNEXT);
      }




      return true;

   }

   void dialog::on_close()
   {

   }
   void dialog::on_notify(NMHDR * p)
   {


   }

   void dialog::on_notify(int iCode, int iId)
   {

   }


} // namespace os




