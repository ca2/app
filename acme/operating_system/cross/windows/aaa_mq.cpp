#include "framework.h"
//#include "acme/operating_system/_c.h"
//#include "acme/operating_system/_.h"
//#include "acme/operating_system/_os.h"
//#include "message_queue.h"
//
//#define WM_KICKIDLE         0x036A  // (params unused) causes idles to kick in
//#if defined(LINUX) // || defined(ANDROID)
//
//
//bool apex_defer_process_x_message(htask_t htask,MESSAGE * pMsg,oswindow oswindow,bool bPeek);
//
//
//#endif
//
//
//message_queue::message_queue()
//{
//
//   m_bQuit = false;
//
//   m_bKickIdle = false;
//
//   defer_create_mutex();
//
//}
//
//
//message_queue::~message_queue()
//{
//
//}
//
//
//int_bool message_queue::post_message(oswindow oswindow, const ::atom & atom, WPARAM wParam, LPARAM lParam)
//{
//
//   if (m_bQuit)
//   {
//
//      return false;
//
//   }
//
//   mq_message message(atom);
//
//   message.m_message.hwnd = oswindow;
//   message.m_message.wParam = wParam;
//   message.m_message.lParam = lParam;
//   message.m_message.pt.x = 0x80000000;
//   message.m_message.pt.y = 0x80000000;
//
//   return post_message(message);
//
//}
//
//
//int_bool message_queue::post_message(const mq_message & message)
//{
//
//   if(m_bQuit)
//   {
//
//      return false;
//
//   }
//
//   synchronous_lock synchronouslock(mutex());
//
//   m_messagea.add(message);
//
//   m_eventNewMessage.set_event();
//
//   return true;
//
//}
//
//
//
//int_bool message_queue::get_message(MESSAGE * pMsg, oswindow oswindow, ::u32 wMsgFilterMin, ::u32 wMsgFilterMax)
//{
//
//   if (wMsgFilterMax == 0)
//   {
//
//      wMsgFilterMax = (::u32)-1;
//
//   }
//
//   synchronous_lock synchronouslock(mutex());
//
//   while (true)
//   {
//
//      for (i32 i = 0; i < m_messagea.get_count();)
//      {
//
//         auto & msg = m_messagea[i];
//
//         if (msg.m_message.message == e_message_quit)
//         {
//
//            m_bQuit = true;
//
//            m_messagea.erase_at(i);
//
//            continue;
//
//         }
//
//         if ((oswindow == nullptr || msg.m_message.hwnd == oswindow) && msg.m_message.message >= wMsgFilterMin && msg.m_message.message <= wMsgFilterMax)
//         {
//
//            *pMsg = msg.m_message;
//
//            m_messagea.erase_at(i);
//
//            return true;
//
//         }
//
//         i++;
//
//      }
//
//      if(m_bQuit)
//      {
//
//         return false;
//
//      }
//
//      if (m_bKickIdle)
//      {
//
//         m_bKickIdle = false;
//
//         pMsg->hwnd = nullptr;
//         pMsg->message = WM_KICKIDLE;
//         pMsg->wParam = 0;
//         pMsg->lParam = 0;
//         pMsg->pt.x = INT_MIN;
//         pMsg->pt.y = INT_MIN;
//         pMsg->time = 0;
//
//         return true;
//
//      }
//
//      {
//
//         synchronouslock.unlock();
//
//         m_eventNewMessage.wait();
//
//         synchronouslock.lock();
//
//         m_eventNewMessage.ResetEvent();
//
//      }
//
//   }
//
//}
//
//
//int_bool message_queue::peek_message(MESSAGE * pMsg, oswindow oswindow,::u32 wMsgFilterMin,::u32 wMsgFilterMax,::u32 wRemoveMsg)
//{
//
//   if(wMsgFilterMax == 0)
//   {
//
//      wMsgFilterMax = (::u32)-1;
//
//   }
//
//   synchronous_lock synchronouslock(mutex());
//
//   ::count count = m_messagea.get_count();
//
//   for(i32 i = 0; i < count; i++)
//   {
//
//      MESSAGE & msg = m_messagea[i].m_message;
//
//      if((oswindow == nullptr || msg.hwnd == oswindow) && msg.message >= wMsgFilterMin && msg.message <= wMsgFilterMax)
//      {
//
//         *pMsg = msg;
//
//         if(wRemoveMsg & PM_REMOVE)
//         {
//
//            m_messagea.erase_at(i);
//
//         }
//
//         return true;
//
//      }
//
//   }
//
//   synchronouslock.unlock();
//
////#if defined(LINUX) // || defined(ANDROID)
////
////   if(apex_defer_process_x_message(htask,pMsg,oswindow,!(wRemoveMsg & PM_REMOVE)))
////   {
////
////      return true;
////
////   }
////
////#endif
//
//   return false;
//
//}
//
//
//::mutex * g_pmutexMq;
//
//
//map < itask_t, __pointer(message_queue) > * g_pmapMq;
//
//
//message_queue * get_message_queue(itask_t itask, bool bCreate)
//{
//
//   synchronous_lock synchronouslock(g_pmutexMq);
//
//   auto p = g_pmapMq->plookup(itask);
//
//   if(p)
//   {
//
//      return p->m_element2;
//
//   }
//
//   if(!bCreate)
//   {
//
//      return nullptr;
//
//   }
//
//   auto pmq = __new(message_queue);
//
//   pmq->m_itask = itask;
//
//   g_pmapMq->set_at(itask, pmq);
//
//   return pmq;
//
//}
//
//
//void clear_message_queue(itask_t idthread)
//{
//
//   synchronous_lock synchronouslock(g_pmutexMq);
//
//   g_pmapMq->erase_key(idthread);
//
//}
//
//
////CLASS_DECL_APEX int_bool post_ui_message(const MESSAGE & message)
////{
////
////#ifdef WINDOWS_DESKTOP
////
////   return ::PostMessage(message.hwnd, message.message, message.wParam, message.lParam);
////
////#else
////
////   return message.hwnd->m_pmq->post_message(message);
////
////#endif
////
//////   ::user::interaction * pinteraction = oswindow_interaction(message.hwnd);
//////
//////   if(pinteraction == nullptr)
//////   {
//////
//////      return false;
//////
//////   }
//////
//////   itask_t idthread = pinteraction->m_pthreadUserInteraction->get_os_int();
//////
//////   auto pmq = ::get_message_queue(idthread, message.message != e_message_quit);
//////
//////   if(pmq == nullptr)
//////   {
//////
//////      return false;
//////
//////   }
//////
//////   return pmq->post_message(message);
////
////}
//
//
////CLASS_DECL_APEX int_bool mq_erase_window_from_all_queues(oswindow oswindow)
////{
////
//////   ::user::interaction * pinteraction = oswindow_interaction(oswindow);
//////
//////   if(pinteraction == nullptr)
//////   {
//////
//////      return false;
//////
//////   }
//////
//////   if(pinteraction->get_application() == nullptr)
//////   {
//////
//////      return false;
//////
//////   }
//////
//////   itask_t idthread = pinteraction->get_application()->get_os_int();
//////
//////   message_queue * pmq = __get_mq(idthread, false);
//////
//////   if(pmq == nullptr)
//////   {
//////
//////      return false;
//////
//////   }
//////
//////   synchronous_lock ml(&pmq->m_mutex);
//////
//////   pmq->m_messagea.predicate_erase([=](MESSAGE & item)
//////   {
//////
//////      return item.hwnd == oswindow;
//////
//////   });
////
////   return true;
////
////}
////
//
//CLASS_DECL_ACME void mq_clear(itask_t idthread)
//{
//
//   auto pmq = ::get_message_queue(idthread, false);
//
//   if (pmq == nullptr)
//   {
//
//      return;
//
//   }
//
//   synchronous_lock ml(g_pmutexMq);
//
//   pmq->m_messagea.erase_all();
//
//}
//
//
//int_bool mq_post_thread_message(itask_t idthread, const ::atom & atom, wparam wparam, lparam lparam)
//{
//
//   if (atom.m_etype != ::atom::e_type_message)
//   {
//
//      throw ::exception(error_bad_argument);
//
//   }
//
//   auto pmq = get_message_queue(idthread, true);
//
//   if (::is_null(pmq))
//   {
//
//      return false;
//
//   }
//
//   return pmq->post_message(nullptr, atom.m_emessage, wparam, lparam);
//
//}
//
//
//
//
//CLASS_DECL_ACME int_bool mq_peek_message(MESSAGE * pMsg, oswindow oswindow, ::u32 wMsgFilterMin, ::u32 wMsgFilterMax, ::u32 wRemoveMsg)
//{
//
//   auto pmq = ::get_message_queue(::get_current_itask(), false);
//
//   if (pmq == nullptr)
//   {
//
//      return false;
//
//   }
//
//   if (!pmq->peek_message(pMsg, oswindow, wMsgFilterMin, wMsgFilterMax, wRemoveMsg))
//   {
//
//      return false;
//
//   }
//
//   return true;
//
//}
//
//
//CLASS_DECL_ACME int_bool mq_get_message(MESSAGE * pMsg, oswindow oswindow, ::u32 wMsgFilterMin, ::u32 wMsgFilterMax)
//{
//
//   auto pmq = ::get_message_queue(::get_current_itask(), true);
//
//   if (pmq == nullptr)
//   {
//
//      return false;
//
//   }
//
//   if (!pmq->get_message(pMsg, oswindow, wMsgFilterMin, wMsgFilterMax))
//   {
//
//      return false;
//
//   }
//
//   return true;
//
//}
//
//
//
//
//
//void initialize_global_message_queue()
//{
//
//   g_pmutexMq = new mutex();
//
//   g_pmapMq = new map < itask_t, __pointer(message_queue) >();
//
//}
//
//
//void finalize_global_message_queue()
//{
//
//   ::acme::del(g_pmutexMq);
//
//   ::acme::del(g_pmapMq);
//
//}
//
//
//
