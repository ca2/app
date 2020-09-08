#include "framework.h"


void ::aqua::shell_launcher::execute()
{

   if(m_iMode == 0)
   {

      if(m_strOperation.is_empty())
      {

         property_set set;

         m_dwResult = call_sync(m_strFile, m_strParameters, m_strDirectory, m_edisplay, 1_min, set);

      }
      else if(ansi_compare_ci(m_strOperation, "open") == 0)
      {

         property_set set;

         m_dwResult = call_sync("gnome-open", m_strFile, m_strDirectory, m_edisplay, 1_min, set);

      }

   }

}




bool ::aqua::shell_launcher::succeeded()
{

   return m_dwResult >= 0;

}










