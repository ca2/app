#include "framework.h"


void simple_shell_launcher::execute()
{

   if(m_iMode == 0)
   {

      if(m_vssOperation.is_empty())
      {
         m_dwResult = call_sync(m_vssFile, m_vssParameters, m_vssDirectory, m_iShow, -1, 284, nullptr, 0);
      }
      else if(ansi_compare_ci(m_vssOperation, "open") == 0)
      {
         m_dwResult = call_sync("gnome-open", m_vssFile, m_vssDirectory, m_iShow, -1, 284, nullptr, 0);
      }

   }

}




bool simple_shell_launcher::succeeded()
{

   return m_dwResult >= 0;

}










