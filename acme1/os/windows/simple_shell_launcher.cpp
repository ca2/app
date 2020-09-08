#include "framework.h"




namespace acme
{


   void shell_launcher::execute()
   {

      if(m_iMode == 0)
      {

         m_h = ::ShellExecuteW(
            m_oswindow,
            wstring(m_strOperation),
            wstring(m_strFile),
            wstring(m_strParameters),
            wstring(m_strDirectory),
            windows_show_window(m_edisplay, m_eactivation));

      }

   }


   bool shell_launcher::succeeded()
   {

      return ((iptr)m_h) >= 32;

   }


} // namespace acme










