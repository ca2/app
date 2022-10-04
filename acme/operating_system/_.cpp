//
//  _.cpp
//  acme
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 21/09/20.
//  Copyright © 2020 Camilo Sasuke Thomas Borregaard Sørensen. All rights reserved.
//
#include "framework.h"
#include "acme/platform/system_setup.h"


//
//
//
//
//CLASS_DECL_ACME void destroy_pointer(int_handle i)
//{
//
//   if(i >= 0)
//   {
//
//      ::close(i.m_i);
//
//   }
//
//}


CLASS_DECL_ACME void destroy_pointer(FILE * p)
{

   if(::is_set(p))
   {

      fclose(p);

   }

}


static PFN_factory g_pfnFactoryApp = nullptr;


app_factory::app_factory(PFN_factory pfnFactory)
{

    g_pfnFactoryApp = pfnFactory;

}


__pointer(::acme::application)app_factory::new_app()
{

   auto pfactory = __new(::factory::factory);

   g_pfnFactoryApp(pfactory);

   auto papp = pfactory->create<::acme::application>();

   return papp;

}

#ifdef WINDOWS


static bool stdin_has_input_events()
{

   HANDLE handleStdin = ::GetStdHandle(STD_INPUT_HANDLE);

   DWORD dwNumberOfEvents = 0;

   if (!GetNumberOfConsoleInputEvents(handleStdin, &dwNumberOfEvents))
   {

      return false;

   }

   return dwNumberOfEvents > 0;

}


static void flush_stdin_input_events()
{

   HANDLE handleStdin = ::GetStdHandle(STD_INPUT_HANDLE);

   ::FlushConsoleInputBuffer(handleStdin);

}


void flush_stdin()
{

   while (stdin_has_input_events())
   {

      flush_stdin_input_events();

   }

}


//void stdin_wait_char(void)
//{
//   WaitForSingleObject(GetStdHandle(STD_INPUT_HANDLE), INFINITE);
//}
//int stdin_read_char()
//{
//
//   HANDLE handleStdIn = GetStdHandle(STD_INPUT_HANDLE)
//
//   DWORD dwRead = 0;
//
//   ::byte b = 0;
//
//   ReadConsoleInputA(handleStdin, &b, 1, &dwRead);
//
//   if (dwRead == 0)
//   {
//
//      return -1;
//
//   }
//
//   return b
//
//}
#else
#include <unistd.h>
#include <stdio.h>
#include <sys/select.h>

bool stdin_has_char()
{

   
      // cc.byexamples.com calls this int kbhit(), to mirror the Windows console
      //  function of the same name.  Otherwise, the code is the same.
      struct timeval tv;
      fd_set fds;
      tv.tv_sec = 0;
      tv.tv_usec = 0;
      FD_ZERO(&fds);
      FD_SET(STDIN_FILENO, &fds);
      select(STDIN_FILENO + 1, &fds, NULL, NULL, &tv);
      return (FD_ISSET(0, &fds));
}

void stdin_wait_char(void)
{
   struct timeval tv;
   fd_set fds;
   tv.tv_sec = INT_MAX; // Almost infinite wait
   tv.tv_usec = 0;
   FD_ZERO(&fds);
   FD_SET(STDIN_FILENO, &fds);
   select(STDIN_FILENO + 1, &fds, NULL, NULL, &tv);
   return (FD_ISSET(0, &fds));
}


#endif


//void flush_stdin()
//{
//
//   while(stdin_has_char())
//   {
//
//      read_stdin_char();
//      
//   }
//
//}
//
//

