#include "framework.h"
#include "shell_launcher.h"
#include "acme/exception/interface_only.h"


namespace apex
{


#ifndef _UWP


   shell_launcher::shell_launcher()
   {


   }
      

   shell_launcher::~shell_launcher()
   {


   }


   void shell_launcher::launch()
   {

      throw ::interface_only();

   }


//   bool shell_launcher::succeeded()
//   {
//
//      return false;
//
//   }



   void shell_launcher::setup(const class time & timeTimeout)
   {

      m_iMode = 1;

      //return ::success;

   }


   void shell_launcher::setup(oswindow oswindow, const scoped_string & strOperation, const scoped_string & strFile, const scoped_string & strParameters, const scoped_string & strDirectory, ::e_display edisplay, const class time & timeTimeout)
   {

      m_iMode = 0;
      m_oswindow = oswindow;
      m_strOperation = pszOperation;
      m_strFile = pszFile;
      m_strParameters = pszParameters;
      m_strDirectory = pszDirectory;
      m_edisplay = edisplay;

      //return ::success;

   }


#endif


} // namespace apex



