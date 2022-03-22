#include "framework.h"
//#include "aura/user/_user.h"
//#include "_os.h"
#include <stdio.h>
#include "acme/parallelization/message_queue.h"


#undef ALOG_CONTEXT
#define ALOG_CONTEXT ::trace_object(::trace_category_windowing)


CLASS_DECL_ACME message_queue * get_message_queue(itask_t idthread, bool bCreate);


//static oswindow g_oswindowSplash = nullptr;


//void set_splash(::windowing::window * pwindow)
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
//void windowing_output_debug_string(const ::string & pszDebugString)
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
//   if(::is_set(papp) && ::is_set(papp->get_session()))
//   {
//
//      Sess(papp).m_pointCursor = pointCursor;
//
//   }
//
//}
//
//
//
//::user::interaction* oswindow_interaction(::windowing::window * pwindow)
//{
//
//   auto pimpl = oswindow_interaction_impl(oswindow);
//
//   if (::is_null(pimpl))
//   {
//
//      return nullptr;
//
//   }
//
//   return pimpl->m_puserinteraction;
//
//}
//
//



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
//   auto & system = ::aura::get_system();
//
//   synchronous_lock slSystem(system.mutex());
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
//   //synchronous_lock slMap(pmap->mutex());
//
//   ::user::primitive * pusermessage;
//
//   if (!pmap->m_map.lookup(oswindow, pusermessage))
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
//   return dynamic_cast <::user::interaction_impl *>(pusermessage);
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

//CLASS_DECL_AURA int_bool mq_erase_window_from_all_queues(::windowing::window * pwindow)
//{
//
//   ::user::interaction * pinteraction = oswindow_interaction(oswindow);
//
//   if(pinteraction == nullptr)
//   {
//
//      return false;
//
//   }
//
//   if(pinteraction->get_app() == nullptr)
//   {
//
//      return false;
//
//   }
//
//   itask_t idthread = pinteraction->get_app()->get_itask();
//
//   message_queue * pmq = get_message_queue(idthread, false);
//
//   if(pmq == nullptr)
//   {
//
//      return false;
//
//   }
//
//   synchronous_lock ml(pmq->mutex());
//
//   pmq->m_messagea.predicate_erase([=](MESSAGE & item)
//   {
//
//      return item.hwnd == oswindow;
//
//   });
//
//   return true;
//
//}
