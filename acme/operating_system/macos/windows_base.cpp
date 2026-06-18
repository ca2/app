#include "framework.h"

#include <string.h>
#include <stdio.h>

::u32
//WINAPI
GetTempPathA(
::u32 nBufferLength,
char_pointer pBuffer

)
{

   const_char_pointer ptmpdir = getenv("TMPDIR");

   if(ptmpdir != nullptr && *ptmpdir != '\0')
   {
      ansi_count_copy(pBuffer, ptmpdir, minimum(nBufferLength, strlen(ptmpdir) + 1));

      return (::u32) strlen(ptmpdir);
   }
   

   ptmpdir = P_tmpdir;

   if(ptmpdir != nullptr && *ptmpdir != '\0')
   {
      ansi_count_copy(pBuffer, ptmpdir, minimum(nBufferLength, strlen(ptmpdir) + 1));

      return (::u32) strlen(ptmpdir);
   }

   ansi_count_copy(pBuffer, "/tmp", minimum(nBufferLength, 5));

   return 5;


}


//
//CGWindowID as_CGWindowID(const ::operating_system::window & operatingsystemwindow);
////{
////
////   auto pwindow = (::windowing_macos::window *) oswindow->m_pWindow2;
////
////   auto pnswindow = pwindow->m_pnswindow;
////
////   auto windowId = ns_get_window_id(pnswindow);
////
////   return windowId;
////
////}
