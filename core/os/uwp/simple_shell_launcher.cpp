#include "framework.h"
//#include "universal_windows.h"

#ifndef _UWP

//#include <Shellapi.h>


void ::aura::shell_launcher::execute()
{

   if(m_iMode == 0)
   {

      m_h = ::ShellExecute(m_hwnd, m_vssOperation, m_vssFile, m_vssParameters, m_vssDirectory, m_iShow);

   }
      
}



bool ::aura::shell_launcher::succeeded()
{
 
   return ((int) m_h) >= 32;

}






#endif




