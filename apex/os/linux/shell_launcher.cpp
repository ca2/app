#include "framework.h"
#include "shell_launcher.h"


namespace ansios
{


   ::e_status shell_launcher::launch()
   {

      if (m_iMode == 0)
      {

         if (m_strOperation.is_empty())
         {

            property_set set;

            m_estatus = call_sync(m_strFile, m_strParameters, m_strDirectory, m_edisplay, 1_min, set);

         }
         else if (ansi_compare_ci(m_strOperation, "open") == 0)
         {

            property_set set;

            m_estatus = call_sync("gnome-open", m_strFile, m_strDirectory, m_edisplay, 1_min, set);

         }

      }

      return m_estatus;

   }


} // namespace ansios



