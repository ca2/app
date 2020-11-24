#include "framework.h"
#include "acme/os/_c.h"
#include "acme/os/_.h"
#include "acme/os/_os.h"
#include "mq.h"

#define WM_KICKIDLE         0x036A  // (params unused) causes idles to kick in
#if defined(LINUX) // || defined(ANDROID)


bool apex_defer_process_x_message(hthread_t hthread,LPMESSAGE pMsg,oswindow oswindow,bool bPeek);


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


int_bool mq::post_message(oswindow oswindow, const ::id & id, WPARAM wParam, LPARAM lParam)
{

   if (m_bQuit)
   {

      return FALSE;

   }

   mq_message message(id);

   message.m_message.hwnd = oswindow;
   message.m_message.wParam = wParam;
   message.m_message.lParam = lParam;
   message.m_message.pt.x = 0x80000000;
   message.m_message.pt.y = 0x80000000;

   return post_message(message);

}


int_bool mq::post_message(const mq_message & message)
{

   if(m_bQuit)
   {

      return FALSE;

   }

   sync_lock sl(mutex());

   m_messagea.add(message);

   m_eventNewMessage.set_event();

   return TRUE;

}



int_bool mq::get_message(LPMESSAGE pMsg, oswindow oswindow, ::u32 wMsgFilterMin, ::u32 wMsgFilterMax)
{

   if (wMsgFilterMax == 0)
   {

      wMsgFilterMax = (::u32)-1;

   }

   sync_lock sl(mutex());

   while (true)
   {

      for (i32 i = 0; i < m_messagea.get_count();)
      {

         auto & msg = m_messagea[i];

         if (msg.m_message.message == e_message_quit)
         {

            m_bQuit = true;

            m_messagea.remove_at(i);

            continue;

         }

         if ((oswindow == nullptr || msg.m_message.hwnd == oswindow) && msg.m_message.message >= wMsgFilterMin && msg.m_message.message <= wMsgFilterMax)
         {

            *pMsg = msg.m_message;

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


int_bool mq::peek_message(MESSAGE * pMsg, oswindow oswindow,::u32 wMsgFilterMin,::u32 wMsgFilterMax,::u32 wRemoveMsg)
{

   if(wMsgFilterMax == 0)
   {

      wMsgFilterMax = (::u32)-1;

   }

   sync_lock sl(mutex());

   ::count count = m_messagea.get_count();

   for(i32 i = 0; i < count; i++)
   {

      MESSAGE & msg = m_messagea[i].m_message;

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

map < ithread_t, ithread_t, ＿＿pointer(mq), ＿＿pointer(mq) > * g_pmapMq;


mq * get_mq(ithread_t ithread, bool bCreate)
{

   sync_lock sl(g_pmutexMq);

   auto p = g_pmapMq->plookup(ithread);

   if(p)
   {

      return p->m_element2;

   }

   if(!bCreate)
   {

      return nullptr;

   }

   auto pmq = ＿＿new(mq);

   pmq->m_ithread = ithread;

   g_pmapMq->set_at(ithread, pmq);

   return pmq;

}


void clear_mq(ithread_t idthread)
{

   sync_lock sl(g_pmutexMq);

   g_pmapMq->remove_key(idthread);

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
////   ithread_t idthread = pinteraction->m_pthreadUserInteraction->get_os_int();
////
////   auto pmq = ::get_mq(idthread, message.message != e_message_quit);
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
////   ithread_t idthread = pinteraction->get_context_application()->get_os_int();
////
////   mq * pmq = ＿＿get_mq(idthread, false);
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
////   pmq->m_messagea.λremove([=](MESSAGE & item)
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

CLASS_DECL_ACME void mq_clear(ithread_t idthread)
{

   auto pmq = ::get_mq(idthread, false);

   if (pmq == nullptr)
   {

      return;

   }

   sync_lock ml(g_pmutexMq);

   pmq->m_messagea.remove_all();

}


int_bool mq_post_thread_message(ithread_t idthread, const ::id & id, WPARAM wparam, LPARAM lparam)
{

   if (id.m_etype != ::id::e_type_message)
   {

      ＿＿throw(invalid_argument_exception);

   }

   auto pmq = get_mq(idthread, true);

   if (::is_null(pmq))
   {

      return FALSE;

   }

   return pmq->post_message(nullptr, id.m_emessage, wparam, lparam);

}




CLASS_DECL_ACME int_bool mq_peek_message(LPMESSAGE pMsg, oswindow oswindow, ::u32 wMsgFilterMin, ::u32 wMsgFilterMax, ::u32 wRemoveMsg)
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


CLASS_DECL_ACME int_bool mq_get_message(LPMESSAGE pMsg, oswindow oswindow, ::u32 wMsgFilterMin, ::u32 wMsgFilterMax)
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

   g_pmapMq = new map < ithread_t, ithread_t, ＿＿pointer(mq), ＿＿pointer(mq) >();

}


void term_global_mq()
{

   ::acme::del(g_pmutexMq);

   ::acme::del(g_pmapMq);

}



