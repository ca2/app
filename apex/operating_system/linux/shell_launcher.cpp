#include "framework.h"
#include "shell_launcher.h"
#include "acme/platform/node.h"
#include "acme/platform/system.h"
#include "acme/primitive/primitive/payload.h"


namespace ansios
{


   void shell_launcher::launch()
   {

      if (m_iMode == 0)
      {

         auto psystem = acmesystem();

         auto pnode = psystem->node();

         if (m_strOperation.is_empty())
         {

            property_set set;

            ///m_estatus =
            ///
            pnode->call_sync(m_strFile, m_strParameters, m_strDirectory, m_edisplay, 1_min, set);

         }
         else if (ansi_compare_ci(m_strOperation, "open") == 0)
         {

            property_set set;

            pnode->call_sync("gnome-open", m_strFile, m_strDirectory, m_edisplay, 1_min, set);

         }

      }

      //return m_estatus;

   }


} // namespace ansios



