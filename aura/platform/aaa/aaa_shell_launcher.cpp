#include "framework.h"


namespace aura
{


#ifndef _UWP


   shell_launcher::shell_launcher(duration durationTimeout)
   {

      m_iMode              = 1;

   }


   shell_launcher::shell_launcher(oswindow oswindow, const ::string & pszOperation, const ::string & pszFile, const ::string & pszParameters, const ::string & pszDirectory, ::e_display edisplay, duration durationTimeout)
   {

      m_iMode              = 0;
      m_oswindow           = oswindow;
      m_strOperation       = pszOperation;
      m_strFile            = pszFile;
      m_strParameters      = pszParameters;
      m_strDirectory       = pszDirectory;
      m_edisplay           = edisplay;

   }


#endif






} // namespace aura




