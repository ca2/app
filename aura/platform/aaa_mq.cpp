#include "framework.h"
#if !BROAD_PRECOMPILED_HEADER
#include "aura/user/_user.h"
#endif
#include "aura/os/_c.h"
#include "aura/os/_.h"
#include "aura/os/_os.h"
#include "mq.h"


#if defined(LINUX) // || defined(ANDROID)


bool aura_defer_process_x_message(HTHREAD hthread,LPMESSAGE pMsg,oswindow oswindow,bool bPeek);


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
//   if(aura_defer_process_x_message(hthread,pMsg,oswindow,!(wRemoveMsg & PM_REMOVE)))
//   {
//
//      return TRUE;
//
//   }
//
//#endif

   return FALSE;

}


__pointer(mq) get_mq(ITHREAD idthread, bool bCreate)
{

   ::thread * pthread = ::get_context_system()->get_thread(idthread);

   if (!pthread)
   {

      return nullptr;

   }

   if(pthread->m_bClosedMq)
   {

      string strType = pthread->type_name();

      if(::str::begins(strType, "multimedia::"))
      {

         if(strType.contains("wave_player"))
         {

            output_debug_string("xxCLOSED_MQ xx__get_mq from xxwave_player");

         }
         else if(strType.ends_ci("out"))
         {

            output_debug_string("xxCLOSED_MQ xx__get_mq from xxout");

         }
         else if(strType.contains("output_thread"))
         {

            output_debug_string("xxCLOSED_MQ xx__get_mq from xxoutput_thread");

         }
         else
         {

            output_debug_string("xxCLOSED_MQ xx__get_mq from xxmultimedia::*");

         }

      }

      return nullptr;

   }

   if(pthread->m_pmq)
   {

      return pthread->m_pmq;

   }

   if(!bCreate)
   {

      string strType = pthread->type_name();

      if(::str::begins(strType, "multimedia::"))
      {

         if(strType.contains("wave_player"))
         {

            output_debug_string("notxxbCreate xx__get_mq from xxwave_player");

         }
         else if(strType.ends_ci("out"))
         {

            output_debug_string("notxxbCreate xx__get_mq from xxout");

         }
         else if(strType.contains("output_thread"))
         {

            output_debug_string("notxxbCreate xx__get_mq from xxoutput_thread");

         }
         else
         {

            output_debug_string("notxxbCreate xx__get_mq from xxmultimedia::*");

         }

      }

      return nullptr;

   }

   pthread->__raw_compose_new(pthread->m_pmq);

   pthread->m_pmq->m_ithread = idthread;

   return pthread->m_pmq;

}


CLASS_DECL_AURA int_bool post_ui_message(const MESSAGE & message)
{

#ifdef WINDOWS_DESKTOP

   return ::PostMessage(message.hwnd, message.message, message.wParam, message.lParam);

#else

   return message.hwnd->m_pmq->post_message(message);

#endif

//   ::user::interaction * pinteraction = oswindow_interaction(message.hwnd);
//
//   if(pinteraction == nullptr)
//   {
//
//      return FALSE;
//
//   }
//
//   ITHREAD idthread = pinteraction->m_pthreadUserInteraction->get_os_int();
//
//   auto pmq = ::get_mq(idthread, message.message != WM_QUIT);
//
//   if(pmq == nullptr)
//   {
//
//      return FALSE;
//
//   }
//
//   return pmq->post_message(message);

}


CLASS_DECL_AURA int_bool mq_remove_window_from_all_queues(oswindow oswindow)
{

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
//   ITHREAD idthread = pinteraction->get_context_application()->get_os_int();
//
//   mq * pmq = __get_mq(idthread, false);
//
//   if(pmq == nullptr)
//   {
//
//      return FALSE;
//
//   }
//
//   sync_lock ml(&pmq->m_mutex);
//
//   pmq->m_messagea.pred_remove([=](MESSAGE & item)
//   {
//
//      return item.hwnd == oswindow;
//
//   });

   return TRUE;

}


CLASS_DECL_AURA void mq_clear(ITHREAD idthread)
{

   auto pmq = ::get_mq(idthread, false);

   if (pmq == nullptr)
   {

      return;

   }

   sync_lock ml(pmq->mutex());

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


CLASS_DECL_AURA int_bool mq_post_message(oswindow oswindow, UINT message, WPARAM wparam, LPARAM lparam)
{

   ::user::interaction* pinteraction = oswindow_interaction(oswindow);

   if (pinteraction == nullptr)
   {

      return FALSE;

   }

   auto pmq = pinteraction->m_pthreadUserInteraction->get_mq();

   if (!pmq)
   {

      return FALSE;

   }

   if (!pmq->post_message(oswindow, message, wparam, lparam))
   {

      return FALSE;

   }

   return TRUE;

}


CLASS_DECL_AURA int_bool mq_peek_message(LPMESSAGE pMsg, oswindow oswindow, UINT wMsgFilterMin, UINT wMsgFilterMax, UINT wRemoveMsg)
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


CLASS_DECL_AURA int_bool mq_get_message(LPMESSAGE pMsg, oswindow oswindow, UINT wMsgFilterMin, UINT wMsgFilterMax)
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



