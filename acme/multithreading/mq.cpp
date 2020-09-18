#include "framework.h"
#include "acme/os/_c.h"
#include "acme/os/_.h"
#include "acme/os/_os.h"
#include "mq.h"

#define WM_KICKIDLE         0x036A  // (params unused) causes idles to kick in
#if defined(LINUX) // || defined(ANDROID)


bool apex_defer_process_x_message(HTHREAD hthread,LPMESSAGE pMsg,oswindow oswindow,bool bPeek);


#endif


mq::mq()
{

   m_bQuit = false;

   m_bKickIdle = false;

   defer_create_mutex();

}


mq::~mq()
{

}


int_bool mq::post_message(oswindow oswindow, UINT uMessage, WPARAM wParam, LPARAM lParam)
{

   if(m_bQuit)
   {

      return FALSE;

   }

   MESSAGE message;

   message.hwnd = oswindow;
   message.message = uMessage;
   message.wParam = wParam;
   message.lParam = lParam;
   message.pt.x = 0x80000000;
   message.pt.y = 0x80000000;

   return post_message(message);

}


int_bool mq::post_message(const MESSAGE & message)
{

   if(m_bQuit)
   {

      return FALSE;

   }

   sync_lock ml(mutex());

   m_messagea.add(message);

   m_eventNewMessage.set_event();

   return TRUE;

}


int_bool mq::get_message(LPMESSAGE pMsg, oswindow oswindow, UINT wMsgFilterMin, UINT wMsgFilterMax)
{

   if (wMsgFilterMax == 0)
   {

      wMsgFilterMax = (UINT)-1;

   }

   sync_lock sl(mutex());

   while (true)
   {

      for (i32 i = 0; i < m_messagea.get_count();)
      {

         MESSAGE & msg = m_messagea[i];

         if (msg.message == WM_QUIT)
         {

            m_bQuit = true;

            m_messagea.remove_at(i);

            continue;

         }

         if ((oswindow == nullptr || msg.hwnd == oswindow) && msg.message >= wMsgFilterMin && msg.message <= wMsgFilterMax)
         {

            *pMsg = msg;

            m_messagea.remove_at(i);

            return TRUE;

         }

         i++;

      }

      if(m_bQuit)
      {

         return FALSE;

      }

      if (m_bKickIdle)
      {

         m_bKickIdle = false;

         pMsg->hwnd = nullptr;
         pMsg->message = WM_KICKIDLE;
         pMsg->wParam = 0;
         pMsg->lParam = 0;
         pMsg->pt.x = INT_MIN;
         pMsg->pt.y = INT_MIN;
         pMsg->time = 0;

         return TRUE;

      }

      {

         sl.unlock();

         m_eventNewMessage.wait();

         sl.lock();

         m_eventNewMessage.ResetEvent();

      }

   }

}


int_bool mq::peek_message(LPMESSAGE pMsg,oswindow oswindow,UINT wMsgFilterMin,UINT wMsgFilterMax,UINT wRemoveMsg)
{

   if(wMsgFilterMax == 0)
   {

      wMsgFilterMax = (UINT)-1;

   }

   sync_lock sl(mutex());

   ::count count = m_messagea.get_count();

   for(i32 i = 0; i < count; i++)
   {

      MESSAGE & msg = m_messagea[i];

      if((oswindow == nullptr || msg.hwnd == oswindow) && msg.message >= wMsgFilterMin && msg.message <= wMsgFilterMax)
      {

         *pMsg = msg;

         if(wRemoveMsg & PM_REMOVE)
         {

            m_messagea.remove_at(i);

         }

         return TRUE;

      }

   }

   sl.unlock();

//#if defined(LINUX) // || defined(ANDROID)
//
//   if(apex_defer_process_x_message(hthread,pMsg,oswindow,!(wRemoveMsg & PM_REMOVE)))
//   {
//
//      return TRUE;
//
//   }
//
//#endif

   return FALSE;

}

mutex * g_pmutexMq;

map < ITHREAD, ITHREAD, __pointer(mq), __pointer(mq) > * g_pmapMq;


mq * get_mq(ITHREAD idthread, bool bCreate)
{

   sync_lock sl(g_pmutexMq);

   auto p = g_pmapMq->plookup(idthread);

   if(!p)
   {

      return nullptr;

   }

   return p->m_element2;

}


void set_mq(ITHREAD idthread, mq * pmq)
{

   sync_lock sl(g_pmutexMq);

   g_pmapMq->set_at(idthread, pmq);

}


//CLASS_DECL_APEX int_bool post_ui_message(const MESSAGE & message)
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
////      return FALSE;
////
////   }
////
////   ITHREAD idthread = pinteraction->m_pthreadUserInteraction->get_os_int();
////
////   auto pmq = ::get_mq(idthread, message.message != WM_QUIT);
////
////   if(pmq == nullptr)
////   {
////
////      return FALSE;
////
////   }
////
////   return pmq->post_message(message);
//
//}


//CLASS_DECL_APEX int_bool mq_remove_window_from_all_queues(oswindow oswindow)
//{
//
////   ::user::interaction * pinteraction = oswindow_interaction(oswindow);
////
////   if(pinteraction == nullptr)
////   {
////
////      return FALSE;
////
////   }
////
////   if(pinteraction->get_context_application() == nullptr)
////   {
////
////      return false;
////
////   }
////
////   ITHREAD idthread = pinteraction->get_context_application()->get_os_int();
////
////   mq * pmq = __get_mq(idthread, false);
////
////   if(pmq == nullptr)
////   {
////
////      return FALSE;
////
////   }
////
////   sync_lock ml(&pmq->m_mutex);
////
////   pmq->m_messagea.pred_remove([=](MESSAGE & item)
////   {
////
////      return item.hwnd == oswindow;
////
////   });
//
//   return TRUE;
//
//}
//

CLASS_DECL_ACME void mq_clear(ITHREAD idthread)
{

   auto pmq = ::get_mq(idthread, false);

   if (pmq == nullptr)
   {

      return;

   }

   sync_lock ml(g_pmutexMq);

   pmq->m_messagea.remove_all();

}


int_bool mq_post_thread_message(ITHREAD idthread, UINT message, WPARAM wparam, LPARAM lparam)
{

   auto pmq = get_mq(idthread, true);

   if (::is_null(pmq))
   {

      return FALSE;

   }

   return pmq->post_message(nullptr, message, wparam, lparam);

}




CLASS_DECL_ACME int_bool mq_peek_message(LPMESSAGE pMsg, oswindow oswindow, UINT wMsgFilterMin, UINT wMsgFilterMax, UINT wRemoveMsg)
{

   auto pmq = ::get_mq(::get_current_ithread(), false);

   if (pmq == nullptr)
   {

      return FALSE;

   }

   if (!pmq->peek_message(pMsg, oswindow, wMsgFilterMin, wMsgFilterMax, wRemoveMsg))
   {

      return FALSE;

   }

   return TRUE;

}


CLASS_DECL_ACME int_bool mq_get_message(LPMESSAGE pMsg, oswindow oswindow, UINT wMsgFilterMin, UINT wMsgFilterMax)
{

   auto pmq = ::get_mq(::get_current_ithread(), true);

   if (pmq == nullptr)
   {

      return FALSE;

   }

   if (!pmq->get_message(pMsg, oswindow, wMsgFilterMin, wMsgFilterMax))
   {

      return FALSE;

   }

   return TRUE;

}





void init_global_mq()
{

   g_pmutexMq = new mutex();

   g_pmapMq = new map < ITHREAD, ITHREAD, __pointer(mq), __pointer(mq) >();

}


void term_global_mq()
{

   ::acme::del(g_pmutexMq);

   ::acme::del(g_pmapMq);

}



