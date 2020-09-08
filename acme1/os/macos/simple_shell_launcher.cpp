#include "framework.h"

namespace acme
{

   void shell_launcher::execute()
   {

      if(m_iMode == 0)
      {

         if(m_strOperation.is_empty())
         {
            
            property_set set;
            
            m_dwResult = call_sync(m_strFile, m_strParameters, m_strDirectory, m_edisplay, 1_min, set);

         }
         else if(m_strOperation.compare_ci("open") == 0)
         {
            
            property_set set;

            m_dwResult = call_sync("open", m_strFile, m_strDirectory, m_edisplay, 1_min, set);

         }

      }

   }




   bool shell_launcher::succeeded()
   {

      return m_dwResult >= 0;

   }


} // namespace acme


