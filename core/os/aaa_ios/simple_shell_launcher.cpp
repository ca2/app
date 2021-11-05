#include "framework.h"
#include "_ios.h"


namespace aura
{


   void shell_launcher::execute()
   {

      if(m_iMode == 0)
      {
         
         property_set set;

         if(m_strOperation.is_empty())
         {
            
            m_dwResult = call_sync(m_strFile, m_strParameters, m_strDirectory, m_edisplay, 1_min, set);
            
         }
         else if(ansi_compare_ci(m_strOperation, "open") == 0)
         {
            
            m_dwResult = call_sync("open", m_strFile, m_strDirectory, m_edisplay, 1_min, set);
            
         }

      }

   }




   bool shell_launcher::succeeded()
   {

      return m_dwResult >= 0;

   }










} // namespace aura




