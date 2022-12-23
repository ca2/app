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


   void shell_launcher::setup(
      oswindow oswindow, 
      const ::scoped_string & scopedstrOperation,
      const ::scoped_string & scopedstrFile, 
      const ::scoped_string & scopedstrParameters, 
      const ::scoped_string & scopedstrDirectory, 
      ::e_display edisplay, const class time & timeTimeout)
   {

      m_iMode = 0;
      m_oswindow = oswindow;
      m_strOperation = scopedstrOperation;
      m_strFile = scopedstrFile;
      m_strParameters = scopedstrParameters;
      m_strDirectory = scopedstrDirectory;
      m_edisplay = edisplay;

      //return ::success;

   }


#endif


} // namespace apex



