#include "framework.h"


void ace_main_struct::application_initialize()
{

   m_bConsole = false;
   m_bDraw2d = true;
   m_bUser = true;
   m_bUserEx = true;
   m_bShowApplicationInformation = false;

}


void ace_main_struct::console_initialize()
{

   m_bConsole = true;
   m_bDraw2d = false;
   m_bUser = false;
   m_bUserEx = false;
   m_bShowApplicationInformation = false;

}



