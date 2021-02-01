#include "framework.h"
#if !BROAD_PRECOMPILED_HEADER
#include "aura/user/_user.h"
#endif
#include "_os.h"
#include <stdio.h>
#include "acme/parallelization/mq.h"


#undef ALOG_CONTEXT
#define ALOG_CONTEXT ::trace_object(::trace_category_windowing)


CLASS_DECL_ACME mq * get_mq(ithread_t idthread, bool bCreate);


//static oswindow g_oswindowSplash = nullptr;


//void set_splash(oswindow oswindow)
//{
//
//   g_oswindowSplash = oswindow;
//
//}


//oswindow get_splash()
//{
//
//   return g_oswindowSplash;
//
//}
//


//bool g_bWindowingOutputDebugString = false;
//
//
//void windowing_output_debug_string(const char * pszDebugString)
//{
//
//   if(g_bWindowingOutputDebugString)
//   {
//
//      output_debug_string(pszDebugString);
//
//      fflush(stdout);
//
//   }
//
//}



//CLASS_DECL_AURA void update_application_session_cursor(void * pvoidApp, const point_i32 & pointCursor)
//{
//
//   ::aura::application * papp = (::aura::application *) pvoidApp;
//
//   if(::is_set(papp) && ::is_set(papp->get_context_session()))
//   {
//
//      Sess(papp).m_pointCursor = pointCursor;
//
//   }
//
//}



::user::interaction* oswindow_interaction(oswindow oswindow)
{

   auto pimpl = oswindow_interaction_impl(oswindow);

   if (::is_null(pimpl))
   {

      return nullptr;

   }

   return pimpl->m_puserinteraction;

}





//::user::interaction_impl * oswindow_interaction_impl(:: oswindow)
//{
//
//   if (::is_null(oswindow))
//   {
//
//      return nullptr;
//
//   }
//
//#ifndef WINDOWS_DESKTOP
//
//   if (::is_set(oswindow->m_pimpl))
//   {
//
//      return oswindow->m_pimpl;
//
//   }
//
//#endif
//
//   auto & system = System;
//
//   sync_lock slSystem(system.mutex());
//
//   auto pmap = system.m_pwindowmap;
//
//   if (!pmap)
//   {
//
//      return nullptr;
//
//   }
//
//   //sync_lock slMap(pmap->mutex());
//
//   ::user::primitive * pbase;
//
//   if (!pmap->m_map.lookup(oswindow, pbase))
//   {
//
//      auto ptask = ::get_task();
//
//      if(::is_set(ptask))
//      {
//
//         auto pimpl = ptask->payload("wnd_init").cast<::user::interaction_impl>();
//
//         if (::is_set(pimpl))
//         {
//
//            thread_property("wnd_init") = nullptr;
//
//            pimpl->attach(oswindow);
//
//            return oswindow_interaction_impl(oswindow);
//
//         }
//
//      }
//
//      return nullptr;
//
//   }
//
//   return dynamic_cast <::user::interaction_impl *>(pbase);
//
//}


//CLASS_DECL_AURA string message_box_result_to_string(int iResult)
//{
//
//   string strResult;
//
//   if (iResult == e_dialog_result_no)
//   {
//
//      strResult = "no";
//
//   }
//   else if (iResult == e_dialog_result_yes)
//   {
//
//      strResult = "yes";
//
//   }
//   else if (iResult == e_dialog_result_cancel)
//   {
//
//      strResult = "cancel";
//
//   }
//   else if (iResult == e_dialog_result_ok)
//   {
//
//      strResult = "ok";
//
//   }
//   else if (iResult == IDTRYAGAIN)
//   {
//
//      strResult = "tryagain";
//
//   }
//   else if (iResult == IDABORT)
//   {
//
//      strResult = "abort";
//
//   }
//   else if (iResult == IDRETRY)
//   {
//
//      strResult = "retry";
//
//   }
//   else if (iResult == IDCONTINUE)
//   {
//
//      strResult = "continue";
//
//   }
//
//   else if (iResult == IDIGNORE)
//   {
//
//      strResult = "retry";
//
//   }
//
//   return strResult;
//}
//
//
//
//
//
//

//CLASS_DECL_AURA int_bool mq_remove_window_from_all_queues(oswindow oswindow)
//{
//
//   ::user::interaction * pinteraction = oswindow_interaction(oswindow);
//
//   if(pinteraction == nullptr)
//   {
//
//      return FALSE;
//
//   }
//
//   if(pinteraction->get_context_application() == nullptr)
//   {
//
//      return false;
//
//   }
//
//   ithread_t idthread = pinteraction->get_context_application()->get_ithread();
//
//   mq * pmq = get_mq(idthread, false);
//
//   if(pmq == nullptr)
//   {
//
//      return FALSE;
//
//   }
//
//   sync_lock ml(pmq->mutex());
//
//   pmq->m_messagea.pred_remove([=](MESSAGE & item)
//   {
//
//      return item.hwnd == oswindow;
//
//   });
//
//   return true;
//
//}
