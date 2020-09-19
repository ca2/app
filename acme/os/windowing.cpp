#include "framework.h"
#include "_os.h"
#include <stdio.h>

#undef ALOG_CONTEXT
#define ALOG_CONTEXT ::trace_object(::trace_category_windowing)



static oswindow g_oswindowSplash = nullptr;


void set_splash(oswindow oswindow)
{

   g_oswindowSplash = oswindow;

}


oswindow get_splash()
{

   return g_oswindowSplash;

}



bool g_bWindowingOutputDebugString = false;


void windowing_output_debug_string(const char * pszDebugString)
{

   if(g_bWindowingOutputDebugString)
   {

      output_debug_string(pszDebugString);

      fflush(stdout);

   }

}



//CLASS_DECL_ACME void update_application_session_cursor(void * pvoidApp, const point & pointCursor)
//{
//
//   ::acme::application * papp = (::acme::application *) pvoidApp;
//
//   if(::is_set(papp) && ::is_set(papp->get_context_session()))
//   {
//
//      Sess(papp).m_pointCursor = pointCursor;
//
//   }
//
//}





CLASS_DECL_ACME string message_box_result_to_string(int iResult)
{

   string strResult;

   if (iResult == IDNO)
   {

      strResult = "no";

   }
   else if (iResult == IDYES)
   {

      strResult = "yes";

   }
   else if (iResult == IDCANCEL)
   {

      strResult = "cancel";

   }
   else if (iResult == IDOK)
   {

      strResult = "ok";

   }
   else if (iResult == IDTRYAGAIN)
   {

      strResult = "tryagain";

   }
   else if (iResult == IDABORT)
   {

      strResult = "abort";

   }
   else if (iResult == IDRETRY)
   {

      strResult = "retry";

   }
   else if (iResult == IDCONTINUE)
   {

      strResult = "continue";

   }

   else if (iResult == IDIGNORE)
   {

      strResult = "retry";

   }

   return strResult;
}





CLASS_DECL_ACME color get_simple_ui_color(::user::e_element eelement, ::user::estate estate)
{

   ::color color;

   if(eelement == ::user::element_background)
   {

      if (::user::is_app_dark_mode())
      {

         color = ARGB(255, 0x50, 0x50, 0x58);

      }
      else
      {

         color = ARGB(255, 0xcd, 0xcd, 0xc8);

      }

   }
   else
   {

      if (::user::is_app_dark_mode())
      {

         color = ARGB(255, 255, 255, 255);

      }
      else
      {

         color = ARGB(255, 49, 50, 42);

      }

   }

   return color;

}



