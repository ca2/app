#pragma once


namespace user
{


   template < typename PRED >
   class top_level_boolean_pred
   {
   public:


      PRED m_pred;
      oswindow m_oswindow;


      top_level_boolean_pred(PRED pred, oswindow oswindowDefault = nullptr) : m_pred(pred), m_oswindow(oswindowDefault) {}


      bool found(oswindow oswindow)
      {

         return m_pred(oswindow);

      }


#ifdef WINDOWS_DESKTOP

      static BOOL CALLBACK EnumWindowsProc(HWND hwnd, LPARAM lParam)
      {

         top_level_boolean_pred * ppred = (top_level_boolean_pred *) lParam;

         if (ppred->found(hwnd))
         {

            ppred->m_oswindow = hwnd;

            return FALSE;

         }

         return TRUE;

      }

#endif

   };


   template < typename PRED >
   bool top_level_contains_pred(PRED pred)
   {

      top_level_boolean_pred<PRED> boolean_pred(pred);

      EnumWindows(&top_level_boolean_pred<PRED>::EnumWindowsProc, (LPARAM)&boolean_pred);

      return boolean_pred.m_oswindow != nullptr;

   }


   inline string get_window_text_timeout(oswindow oswindow, const ::duration & durationSendMessageMax)
   {

      DWORD_PTR dw = 0;

      //if (!SendMessageTimeoutW(hwnd, WM_GETTEXTLENGTH, 0, 0, SMTO_ABORTIFHUNG | SMTO_NOTIMEOUTIFNOTHUNG, 100, &dw))
      if (!SendMessageTimeoutW(oswindow, WM_GETTEXTLENGTH, 0, 0, SMTO_ABORTIFHUNG, __os(durationSendMessageMax), &dw))
      {

         return "";

      }

      if (!dw)
      {

         return "";

      }

      wstring wstr;

      auto pwsz = wstr.get_string_buffer(dw);

      if (!SendMessageTimeoutW(oswindow, WM_GETTEXT, dw + 1, (LPARAM)pwsz, SMTO_ABORTIFHUNG, __os(durationSendMessageMax), &dw))
      {

         return "";

      }

      wstr.release_string_buffer();

      return wstr;

   }


   inline bool top_level_contains_name(string str)
   {

      return top_level_contains_pred([str](oswindow oswindow)
         {

            //PSEUDO-Code char sz[1024]; GetWindowTextA(sz,1024, oswindow); return !strcmp(sz, str.c_str());

            string strWindowText = get_window_text_timeout(oswindow, 50_ms);

            return strWindowText.contains_ci(str);

         });

   }


   inline bool visible_top_level_contains_name(string str)
   {

      return top_level_contains_pred([str](oswindow oswindow)
         {

            //PSEUDO-Code char sz[1024]; GetWindowTextA(sz,1024, oswindow); return !strcmp(sz, str.c_str());

            if (!::IsWindowVisible(oswindow))
            {

               return false;

            }

            string strWindowText = get_window_text_timeout(oswindow, 50_ms);

            return strWindowText.contains_ci(str);

         });

   }

   inline bool visible_top_level_contains_all_names(string_array & stra)
   {

      return top_level_contains_pred([&stra](oswindow oswindow)
         {

            //PSEUDO-Code char sz[1024]; GetWindowTextA(sz,1024, oswindow); return !strcmp(sz, str.c_str());

            if (!::IsWindowVisible(oswindow))
            {

               return false;

            }

            string strWindowText = get_window_text_timeout(oswindow, 50_ms);

            for (auto & str : stra)
            {

               if (!strWindowText.contains_ci(str))
               {

                  return false;

               }

            }

            return true;

         });

   }

} // namespace user



/// from top to bottom
class CLASS_DECL_AURA top_level_enum
{
public:


   __pointer(::user::oswindow_array)      m_poswindowa;
   bool                                   m_bVisible;


   top_level_enum(bool bDestkop = true, bool bVisible = true);
   ~top_level_enum();


   /// from top to bottom
   static BOOL CALLBACK EnumWindowsProc(oswindow oswindow, LPARAM lParam);


};

