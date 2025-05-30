#include "framework.h"
//#include "base/user/user/_component.h"
#include "aura/os/_c.h"
//#include "aura/os/_.h"
#include "aura/os/_os.h"
#include "message_queue.h"


#if defined(LINUX) // || defined(__ANDROID__)


bool aura_defer_process_x_message(htask htask,LPMESSAGE pMsg,oswindow oswindow,bool bPeek);


#endif


message_queue::message_queue()
{

   m_bQuit = false;

   m_bKickIdle = false;

   defer_create_synchronization();

}


message_queue::~message_queue()
{

}


int_bool message_queue::post_message(oswindow oswindow, unsigned int uMessage, WPARAM wParam, LPARAM lParam)
{

   if(m_bQuit)
   {

      return false;

   }

   MESSAGE message;

   message.hwnd = oswindow;
   message.message = uMessage;
   message.wParam = wParam;
   message.lParam = lParam;
   message.pt.x() = I32_MINIMUM;
   message.pt.y() = I32_MINIMUM;

   return post_message(message);

}


int_bool message_queue::post_message(const MESSAGE & message)
{

   if(m_bQuit)
   {

      return false;

   }

   synchronous_lock ml(synchronization());

   m_messagea.add(message);

   m_happeningNewMessage.set_happening();

   return true;

}


int_bool message_queue::get_message(LPMESSAGE pMsg, oswindow oswindow, unsigned int wMsgFilterMin, unsigned int wMsgFilterMax)
{

   if (wMsgFilterMax == 0)
   {

      wMsgFilterMax = (unsigned int)-1;

   }

   synchronous_lock synchronouslock(this->synchronization());

   while (true)
   {

      for (int i = 0; i < m_messagea.get_count();)
      {

         MESSAGE & msg = m_messagea[i];

         if (msg.message == e_message_quit)
         {

            m_bQuit = true;

            m_messagea.erase_at(i);

            continue;

         }

         if ((oswindow == nullptr || msg.hwnd == oswindow) && msg.message >= wMsgFilterMin && msg.message <= wMsgFilterMax)
         {

            *pMsg = msg;

            m_messagea.erase_at(i);

            return true;

         }

         i++;

      }

      if(m_bQuit)
      {

         return false;

      }

      if (m_bKickIdle)
      {

         m_bKickIdle = false;

         pMsg->hwnd = nullptr;
         pMsg->message = WM_KICKIDLE;
         pMsg->wParam = 0;
         pMsg->lParam = 0;
         pMsg->pt.x() = INT_MIN;
         pMsg->pt.y() = INT_MIN;
         pMsg->time = 0;

         return true;

      }

      {

         synchronouslock.unlock();

         m_happeningNewMessage.wait();

         synchronouslock.lock();

         m_happeningNewMessage.reset_happening();

      }

   }

}


int_bool message_queue::peek_message(LPMESSAGE pMsg,oswindow oswindow,unsigned int wMsgFilterMin,unsigned int wMsgFilterMax,unsigned int wRemoveMsg)
{

   if(wMsgFilterMax == 0)
   {

      wMsgFilterMax = (unsigned int)-1;

   }

   synchronous_lock synchronouslock(this->synchronization());

   ::collection::count count = m_messagea.get_count();

   for(int i = 0; i < count; i++)
   {

      MESSAGE & msg = m_messagea[i];

      if((oswindow == nullptr || msg.hwnd == oswindow) && msg.message >= wMsgFilterMin && msg.message <= wMsgFilterMax)
      {

         *pMsg = msg;

         if(wRemoveMsg & PM_REMOVE)
         {

            m_messagea.erase_at(i);

         }

         return true;

      }

   }

   synchronouslock.unlock();

//#if defined(LINUX) // || defined(__ANDROID__)
//
//   if(aura_defer_process_x_message(htask,pMsg,oswindow,!(wRemoveMsg & PM_REMOVE)))
//   {
//
//      return true;
//
//   }
//
//#endif

   return false;

}


//::pointer<message_queue>get_message_queue(itask idthread, bool bCreate)
//{
//
//   ::thread * pthread = ::auraacmesystem()->get_task(idthread);
//
//   if (!pthread)
//   {
//
//      return nullptr;
//
//   }
//
//   if(pthread->m_bClosedMq)
//   {
//
//      string strType = ::type(pthread).name();
//
//      if(string_begins(strType, "multimedia::"))
//      {
//
//         if(strType.contains("wave_player"))
//         {
//
//            informationf("xxCLOSED_MQ xx__get_mq from xxwave_player");
//
//         }
//         else if(strType.case_insensitive_ends("out"))
//         {
//
//            informationf("xxCLOSED_MQ xx__get_mq from xxout");
//
//         }
//         else if(strType.contains("output_thread"))
//         {
//
//            informationf("xxCLOSED_MQ xx__get_mq from xxoutput_thread");
//
//         }
//         else
//         {
//
//            informationf("xxCLOSED_MQ xx__get_mq from xxmultimedia::*");
//
//         }
//
//      }
//
//      return nullptr;
//
//   }
//
//   if(pthread->m_pmq)
//   {
//
//      return pthread->m_pmq;
//
//   }
//
//   if(!bCreate)
//   {
//
//      string strType = ::type(pthread).name();
//
//      if(string_begins(strType, "multimedia::"))
//      {
//
//         if(strType.contains("wave_player"))
//         {
//
//            informationf("notxxbCreate xx__get_mq from xxwave_player");
//
//         }
//         else if(strType.case_insensitive_ends("out"))
//         {
//
//            informationf("notxxbCreate xx__get_mq from xxout");
//
//         }
//         else if(strType.contains("output_thread"))
//         {
//
//            informationf("notxxbCreate xx__get_mq from xxoutput_thread");
//
//         }
//         else
//         {
//
//            informationf("notxxbCreate xx__get_mq from xxmultimedia::*");
//
//         }
//
//      }
//
//      return nullptr;
//
//   }
//
//   pthread->__raw_construct_new(pthread->m_pmq);
//
//   pthread->m_pmq->m_itask = idthread;
//
//   return pthread->m_pmq;
//
//}


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
//      return false;
//
//   }
//
//   itask idthread = pinteraction->m_pthreadUserInteraction->get_os_int();
//
//   auto pmq = ::get_message_queue(idthread, message.message != e_message_quit);
//
//   if(pmq == nullptr)
//   {
//
//      return false;
//
//   }
//
//   return pmq->post_message(message);

}


CLASS_DECL_AURA int_bool mq_erase_window_from_all_queues(oswindow oswindow)
{

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
//   itask idthread = pinteraction->get_app()->get_os_int();
//
//   message_queue * pmq = __get_mq(idthread, false);
//
//   if(pmq == nullptr)
//   {
//
//      return false;
//
//   }
//
//   synchronous_lock ml(&pmq->m_pmutex);
//
//   pmq->m_messagea.predicate_erase([=](MESSAGE & item)
//   {
//
//      return item.hwnd == oswindow;
//
//   });

   return true;

}


CLASS_DECL_AURA void mq_clear(class ::task_index & taskindex)
{

   auto pmq = ::get_message_queue(taskindex, false);

   if (pmq == nullptr)
   {

      return;

   }

   synchronous_lock ml(pmq->mutex());

   pmq->m_messagea.erase_all();

}


int_bool mq_post_thread_message(class ::task_index & taskindex, ::enum_message emessage, ::wparam wparam, ::lparam lparam)
{

   auto pmq = get_message_queue(taskindex, true);

   if (::is_null(pmq))
   {

      return false;

   }

   return pmq->post_message(nullptr, message, wparam, lparam);

}


CLASS_DECL_AURA int_bool message_queue_post(oswindow oswindow, ::enum_message emessage, ::wparam wparam, ::lparam lparam)
{

   ::user::interaction* pinteraction = oswindow_interaction(oswindow);

   if (pinteraction == nullptr)
   {

      return false;

   }

   auto pmq = pinteraction->m_pthreadUserInteraction->get_message_queue();

   if (!pmq)
   {

      return false;

   }

   if (!pmq->post_message(oswindow, message, wparam, lparam))
   {

      return false;

   }

   return true;

}


//CLASS_DECL_AURA int_bool mq_peek_message(LPMESSAGE pMsg, oswindow oswindow, unsigned int wMsgFilterMin, unsigned int wMsgFilterMax, unsigned int wRemoveMsg)
//{
//
//   auto pmq = ::get_message_queue(::current_itask(), false);
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


CLASS_DECL_AURA int_bool mq_get_message(LPMESSAGE pMsg, oswindow oswindow, unsigned int wMsgFilterMin, unsigned int wMsgFilterMax)
{

   auto pmq = ::get_message_queue(::current_itask(), true);

   if (pmq == nullptr)
   {

      return false;

   }

   if (::failed(pmq->get_message(pMsg, oswindow, wMsgFilterMin, wMsgFilterMax)))
   {

      return false;

   }

   return true;

}



