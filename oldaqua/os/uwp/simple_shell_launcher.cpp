#include "framework.h"
//#include "uwp.h"

#ifndef _UWP

//#include <Shellapi.h>


void ::aqua::shell_launcher::execute()
{

   if(m_iMode == 0)
   {

      m_h = ::ShellExecute(m_hwnd, m_vssOperation, m_vssFile, m_vssParameters, m_vssDirectory, m_iShow);

   }
      
}



bool ::aqua::shell_launcher::succeeded()
{
 
   return ((int) m_h) >= 32;

}






#endif




