//
//  ios_main.cpp
//  ios_ace
//
//  Created by Camilo Sasuke Tsumanuma on 21/01/18.
//

#include "framework.h"


bool os_init_application()
{
   
   return true;
   
}




::estatus os_application_system_run(::acme::system * psystem)
{

   ::estatus estatus = psystem->begin_synch();
   
   if(!estatus)
   {
      
      return estatus;
      
   }
   
   set_main_hthread(psystem->m_hthread);

   set_main_ithread(psystem->m_uThread);

   ns_application_main(psystem->m_argc, psystem->m_argv, psystem->m_strCommandLine);

   return ::success;

}





