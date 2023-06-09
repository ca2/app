//
// Created by camilo on 11/04/2022. 11:30 <3ThomasBorregaardSorensen!!
//
#include "framework.h"
#include <X11/Xlib.h>


//void x11_init_threads()
//{
//
//   XInitThreads();
//
//}




void x11_check_status(int status, unsigned long window)
{
   if (status == BadWindow)
   {
      printf("window atom # 0x%lx does not exists!", window);
      //   exit(1);
   }

   if (status != Success)
   {
      printf("XGetWindowProperty failed!");
      // exit(2);
   }
}



