#pragma once


#include "application_common.h"
#include "acme/inline/implement.h"


#ifdef WINDOWS

#include "apex/inline/implement/windows.h"

#else

#include "apex/inline/implement/ansi.h"

#endif


//
//
//int console_end(::e_status estatus)
//{
//
//   int iStatus = (int)estatus;
//
//   int iError = 0;
//
//   if (iStatus < 0)
//   {
//
//      iError = iStatus;
//
//   }
//   else if (iStatus > 1)
//   {
//
//      iError = 0;
//
//      if (get_system()->is_true("show_application_information"))
//      {
//
//         printf("return code is %d", iStatus);
//
//      }
//
//   }
//
//   get_system()->system_end();
//
//   return iError;
//
//}
//
//
//
