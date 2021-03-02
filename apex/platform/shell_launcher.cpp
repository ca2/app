#include "framework.h"


namespace apex
{


#ifndef _UWP


   shell_launcher::shell_launcher()
   {


   }
      

   shell_launcher::~shell_launcher()
   {


   }


   ::e_status shell_launcher::launch()
   {

      __throw(error_interface_only);

      return error_interface_only;

   }


//   bool shell_launcher::succeeded()
//   {
//
//      return false;
//
//   }

#endif



   ::e_status shell_launcher::setup(duration durationTimeout)
   {

      m_iMode = 1;

      return ::success;

   }


   ::e_status shell_launcher::setup(oswindow oswindow, const char * pszOperation, const char * pszFile, const char * pszParameters, const char * pszDirectory, ::e_display edisplay, duration durationTimeout)
   {

      m_iMode = 0;
      m_oswindow = oswindow;
      m_strOperation = pszOperation;
      m_strFile = pszFile;
      m_strParameters = pszParameters;
      m_strDirectory = pszDirectory;
      m_edisplay = edisplay;

      return ::success;

   }


} // namespace apex




