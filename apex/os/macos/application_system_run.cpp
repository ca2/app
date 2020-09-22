//
//  macos_main.cpp
//  apex
//
//  Created by Camilo Sasuke Tsumanuma on 8/2/15.
//
//

//
//  main.cpp
//  app
//
//  Created by Camilo Sasuke Tsumanuma on 15/05/14.
//  Copyright (c) 2014 Camilo Sasuke Tsumanuma. All rights reserved.
//



//u32 __run_system_main_param(main_param * pparam)
//{
//   
//   string strCommandLine;
//   
//   bool bColon = false;
//   
//   for(i32 i = 0; i < pparam->argc; i++)
//   {
//      
//      if(i > 0)
//      {
//         
//         strCommandLine += " ";
//         
//      }
//      
//      if(strcmp(pparam->argv[i], ":") == 0)
//      {
//         
//         strCommandLine     += ":";
//         
//         bColon = true;
//         
//      }
//      else if(bColon)
//      {
//         
//         strCommandLine     += pparam->argv[i];
//         
//         
//      }
//      else
//      {
//         
//         strCommandLine     += "\"";
//         
//         strCommandLine     += pparam->argv[i];
//         
//         strCommandLine     += "\"";
//         
//      }
//      
//   }
//   
//   
//   
//   strCommandLine
//   
//   return __run_system_command_line();
//   
//}


// bool os_init_application()
// {
   
//    return true;
   
// }




//void os_post_quit()
//{
//   
//   ns_app_terminate();
//   
//}


::estatus os_application_system_run(::apex::system * psystem)
{

//   ::estatus estatus = psystem->begin_synch();
//   
//   if(!estatus)
//   {
//      
//      return estatus;
//      
//   }
   
//   set_main_hthread(psystem->m_hthread);
//
//   set_main_ithread(psystem->m_uThread);
//
   
   psystem->application_main(psystem->m_argc, psystem->m_argv, psystem->m_strCommandLine);
   
   return ::success;

}



