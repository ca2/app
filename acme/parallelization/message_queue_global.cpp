//
// Created by camilo on 21/02/2021. 11:54 BRT <3TBS_!!
//
#include "framework.h"
#include "message_queue.h"


#define WM_KICKIDLE         0x036A  // (params unused) causes idles to kick in
#if defined(LINUX) // || defined(ANDROID)


bool apex_defer_process_x_message(htask_t htask,MESSAGE * pMsg,oswindow oswindow,bool bPeek);


#endif

mutex * g_pmutexMq;


map < itask_t, __pointer(message_queue) > * g_pmapMq;


message_queue * get_message_queue(itask_t itask, bool bCreate)
{

   if(itask == 0)
   {

      ASSERT(false);

      return nullptr;

   }

   synchronous_lock synchronouslock(g_pmutexMq);

   auto & pmessagequeue = (*g_pmapMq)[itask];

   if(!pmessagequeue)
   {

      if(bCreate)
      {

         pmessagequeue = __new(message_queue);

         pmessagequeue->m_itask = itask;

      }

   }

   return pmessagequeue;

}


void clear_message_queue(itask_t idthread)
{

   synchronous_lock synchronouslock(g_pmutexMq);

   g_pmapMq->erase_key(idthread);

}


//CLASS_DECL_ACME int_bool post_ui_message(const MESSAGE & message)
//{
//
//#ifdef WINDOWS_DESKTOP
//
//   return ::PostMessage(message.hwnd, message.message, message.wParam, message.lParam);
//
//#else
//
//   return message.hwnd->m_pmq->post_message(message);
//
//#endif
//
////   ::user::interaction * pinteraction = oswindow_interaction(message.hwnd);
////
////   if(pinteraction == nullptr)
////   {
////
////      return false;
////
////   }
////
////   itask_t idthread = pinteraction->m_pthreadUserInteraction->get_os_int();
////
////   auto pmq = ::get_message_queue(idthread, message.message != e_message_quit);
////
////   if(pmq == nullptr)
////   {
////
////      return false;
////
////   }
////
////   return pmq->post_message(message);
//
//}


//CLASS_DECL_ACME int_bool mq_erase_window_from_all_queues(::windowing::window * pwindow)
//{
//
////   ::user::interaction * pinteraction = oswindow_interaction(oswindow);
////
////   if(pinteraction == nullptr)
////   {
////
////      return false;
////
////   }
////
////   if(pinteraction->get_application() == nullptr)
////   {
////
////      return false;
////
////   }
////
////   itask_t idthread = pinteraction->get_application()->get_os_int();
////
////   message_queue * pmq = __get_mq(idthread, false);
////
////   if(pmq == nullptr)
////   {
////
////      return false;
////
////   }
////
////   synchronous_lock ml(&pmq->m_mutex);
////
////   pmq->m_messagea.predicate_erase([=](MESSAGE & item)
////   {
////
////      return item.hwnd == oswindow;
////
////   });
//
//   return true;
//
//}
//

CLASS_DECL_ACME void mq_clear(itask_t idthread)
{

   auto pmq = ::get_message_queue(idthread, false);

   if (pmq == nullptr)
   {

      return;

   }

   synchronous_lock ml(g_pmutexMq);

   pmq->m_messagea.erase_all();

}


void mq_post_thread_message(itask_t idthread, const ::atom & atom, wparam wparam, lparam lparam)
{

   if (atom.m_etype != ::atom::e_type_message)
   {

      throw ::exception(error_bad_argument);

   }

   auto pmq = get_message_queue(idthread, true);

   if (::is_null(pmq))
   {

      return;

   }

   pmq->post_message(nullptr, atom.m_emessage, wparam, lparam);

}


CLASS_DECL_ACME int_bool mq_peek_message(MESSAGE * pMsg, oswindow oswindow, ::u32 wMsgFilterMin, ::u32 wMsgFilterMax, ::u32 wRemoveMsg)
{

   auto pmq = ::get_message_queue(::get_current_itask(), false);

   if (pmq == nullptr)
   {

      return false;

   }

   if (!pmq->peek_message(pMsg, oswindow, wMsgFilterMin, wMsgFilterMax, wRemoveMsg))
   {

      return false;

   }

   return true;

}


CLASS_DECL_ACME void mq_get_message(MESSAGE * pMsg, oswindow oswindow, ::u32 wMsgFilterMin, ::u32 wMsgFilterMax)
{

   auto pmq = ::get_message_queue(::get_current_itask(), true);

   if (pmq == nullptr)
   {

      throw ::exception(error_failed);

   }

   pmq->get_message(pMsg, oswindow, wMsgFilterMin, wMsgFilterMax);

}





void initialize_global_message_queue()
{

   g_pmutexMq = new mutex();

   g_pmapMq = new map < itask_t, __pointer(message_queue) >();

}


void finalize_global_message_queue()
{

   ::acme::del(g_pmutexMq);

   ::acme::del(g_pmapMq);

}



