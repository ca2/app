#include "framework.h"
// #include "acme/primitive/string/string.h"


#undef ALOG_CONTEXT
#define ALOG_CONTEXT ::trace_object(::trace_category_windowing)


//
//static oswindow g_oswindowSplash = nullptr;
//
//
//void set_splash(::windowing::window * pwindow)
//{
//
//   g_oswindowSplash = oswindow;
//
//}
//
//
//oswindow get_splash()
//{
//
//   return g_oswindowSplash;
//
//}



bool g_bWindowingOutputDebugString = false;


void windowing_output_debug_string(const ::scoped_string & scopedstrDebugString)
{

   if(g_bWindowingOutputDebugString)
   {

      information(scopedstrDebugString);

      fflush(stdout);

   }

}



//CLASS_DECL_ACME void update_application_session_cursor(void * pvoidApp, const point_i32 & pointCursor)
//{
//
//   ::acme::application * papp = (::acme::application *) pvoidApp;
//
//   if(::is_set(papp) && ::is_set(papp->get_session()))
//   {
//
//      Sess(papp).m_pointCursor = pointCursor;
//
//   }
//
//}





CLASS_DECL_ACME string message_box_result_to_string(enum_dialog_result edialogresult)
{

   string strResult;

   if (edialogresult == e_dialog_result_no)
   {

      strResult = "no";

   }
   else if (edialogresult == e_dialog_result_yes)
   {

      strResult = "yes";

   }
   else if (edialogresult == e_dialog_result_cancel)
   {

      strResult = "cancel";

   }
   else if (edialogresult == e_dialog_result_ok)
   {

      strResult = "ok";

   }
   else if (edialogresult == e_dialog_result_try_again)
   {

      strResult = "tryagain";

   }
   else if (edialogresult == e_dialog_result_abort)
   {

      strResult = "abort";

   }
   else if (edialogresult == e_dialog_result_retry)
   {

      strResult = "retry";

   }
   else if (edialogresult == e_dialog_result_continue)
   {

      strResult = "continue";

   }

   else if (edialogresult == e_dialog_result_ignore)
   {

      strResult = "retry";

   }

   return strResult;

}


static oswindow g_oswindowCapture;


oswindow get_capture()
{

   return g_oswindowCapture;

}



