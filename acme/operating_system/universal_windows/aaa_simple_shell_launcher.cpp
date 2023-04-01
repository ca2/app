#include "framework.h"
//#include "universal_windows.h"

#ifndef UNIVERSAL_WINDOWS

//#include <Shellapi.h>


void ::acme::shell_launcher::execute()
{

   if(m_iMode == 0)
   {

      m_h = ::ShellExecute(m_hwnd, m_vssOperation, m_vssFile, m_vssParameters, m_vssDirectory, m_iShow);

   }
      
}



bool ::acme::shell_launcher::succeeded()
{
 
   return ((int) m_h) >= 32;

}






#endif




