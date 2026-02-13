#include "framework.h"


namespace aura
{


#ifndef UNIVERSAL_WINDOWS


   shell_launcher::shell_launcher(duration durationTimeout)
   {

      m_iMode              = 1;

   }


   shell_launcher::shell_launcher(::acme::windowing::window * pacmewindowingwindow, const ::scoped_string & scopedstrOperation, const ::scoped_string & scopedstrFile, const ::scoped_string & scopedstrParameters, const ::scoped_string & scopedstrDirectory, ::e_display edisplay, duration durationTimeout)
   {

      m_iMode              = 0;
      m_pacmewindowingwindow           = oswindow;
      m_strOperation       = pszOperation;
      m_strFile            = pszFile;
      m_strParameters      = pszParameters;
      m_strDirectory       = pszDirectory;
      m_edisplay           = edisplay;

   }


#endif






} // namespace aura




