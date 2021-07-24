#include "framework.h"
#include "acme/operating_system.h"
#include "message_queue.h"


#ifdef PARALLELIZATION_PTHREAD


#include "acme/os/ansios/_pthread.h"


#endif


#define WM_KICKIDLE         0x036A  // (params unused) causes idles to kick in
#if defined(LINUX) // || defined(ANDROID)


bool apex_defer_process_x_message(htask_t htask,MESSAGE * pMsg,::windowing::window * pwindow,bool bPeek);


#endif


message_queue::message_queue()
{

   m_bQuit = false;

   m_bKickIdle = false;

   defer_create_mutex();

}


message_queue::~message_queue()
{

}


int_bool message_queue::post_message(oswindow oswindow, const ::id & id, wparam wparam, lparam lparam)
{

   if (m_bQuit)
   {

      return false;

   }

   MESSAGE message;

   message.m_id = id;
   message.oswindow = oswindow;
   message.wParam = wparam;
   message.lParam = lparam;
   message.pt.x = 0x80000000;
   message.pt.y = 0x80000000;

   return post_message(message);

}


int_bool message_queue::post_message(const MESSAGE & message)
{

   if(m_bQuit)
   {

      return false;

   }

   if (message.m_id == e_message_quit)
   {

      ::output_debug_string("message_queue::post_message e_message_quit\n");

   }

   synchronous_lock synchronouslock(mutex());

   m_messagea.add(message);

   m_eventNewMessage.set_event();

   return true;

}


int_bool message_queue::get_message(MESSAGE * pMsg, oswindow oswindow, ::u32 wMsgFilterMin, ::u32 wMsgFilterMax, const ::duration & duration)
{

   if (wMsgFilterMax == 0)
   {

      wMsgFilterMax = (::u32)-1;

   }

   ::i64 iMessage = -1;

   synchronous_lock synchronouslock(mutex());

   while (true)
   {

      for (i32 i = 0; i < m_messagea.get_count();)
      {

         auto & msg = m_messagea[i];

         if (msg.m_id == e_message_quit)
         {

            m_bQuit = true;

            // 2021-07-22 15:03 BRT Changed from this
            //m_messagea.erase_at(i);

            // 2021-07-22 15:03 BRT ... to this
            // 2021-07-22 15:03 BRT quit message would be last message and empty message queue?
            m_messagea.erase_all();

            break;

         }

         iMessage = msg.m_id.i64();

         if ((oswindow == nullptr || msg.oswindow == oswindow) && iMessage >= wMsgFilterMin && iMessage <= wMsgFilterMax)
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

         pMsg->oswindow = nullptr;
         pMsg->m_id = (enum_message) WM_KICKIDLE;
         pMsg->wParam = 0;
         pMsg->lParam = 0;
         pMsg->pt.x = INT_MIN;
         pMsg->pt.y = INT_MIN;
         pMsg->time = 0;

         return true;

      }

      {

         synchronouslock.unlock();

         if(!m_eventNewMessage.wait(duration).succeeded())
         {

            return -1;

         }

         synchronouslock.lock();

         m_eventNewMessage.ResetEvent();

      }

   }

}


int_bool message_queue::peek_message(MESSAGE * pMsg, oswindow oswindow,::u32 wMsgFilterMin,::u32 wMsgFilterMax,::u32 wRemoveMsg)
{

   if(wMsgFilterMax == 0)
   {

      wMsgFilterMax = (::u32)-1;

   }

   synchronous_lock synchronouslock(mutex());

   ::count count = m_messagea.get_count();

   for(i32 i = 0; i < count; i++)
   {

      MESSAGE & msg = m_messagea[i];

      if((oswindow == nullptr || msg.oswindow == oswindow) && msg.m_id.i64() >= wMsgFilterMin && msg.m_id.i64() <= wMsgFilterMax)
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

//#if defined(LINUX) // || defined(ANDROID)
//
//   if(apex_defer_process_x_message(htask,pMsg,oswindow,!(wRemoveMsg & PM_REMOVE)))
//   {
//
//      return true;
//
//   }
//
//#endif

   return false;

}


