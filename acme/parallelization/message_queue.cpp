#include "framework.h"
#include "acme/operating_system.h"
#include "message_queue.h"


#ifdef PARALLELIZATION_PTHREAD


#include "acme/operating_system/ansi/_pthread.h"


#endif


#define WM_KICKIDLE         0x036A  // (params unused) causes idles to kick in
#if defined(LINUX) // || defined(ANDROID)


bool apex_defer_process_x_message(htask_t htask,MESSAGE * pMsg,::windowing::window * pwindow,bool bPeek);


#endif


message_queue::message_queue()
{

   m_bQuit = false;

   //m_bKickIdle = false;

   defer_create_mutex();

}


message_queue::~message_queue()
{

}


void message_queue::post_message(oswindow oswindow, const ::atom & atom, wparam wparam, lparam lparam)
{

   if (m_bQuit)
   {

      return;
      //return false;

   }

   MESSAGE message;

   message.m_atom = atom;
   message.oswindow = oswindow;
   message.wParam = wparam;
   message.lParam = lparam;
   message.pt.x = 0x80000000;
   message.pt.y = 0x80000000;

   /* return */ post_message(message);

}


void message_queue::post_message(const MESSAGE & message)
{

   if(m_bQuit)
   {

      //return false;

      return;

   }

   if (message.m_atom == e_message_quit)
   {

      ::output_debug_string("message_queue::post_message e_message_quit\n");

   }

   _synchronous_lock synchronouslock(mutex());

   m_messagea.add(message);

   m_eventNewMessage.set_event();

   //return true;

}


void message_queue::kick_idle()
{

   //_synchronous_lock synchronouslock(mutex());

   //m_bKickIdle = true;

   //m_eventNewMessage.set_event();

   post_message(nullptr, e_message_kick_idle, 0, 0);

}


void message_queue::get_message(MESSAGE * pmessage, oswindow oswindow, ::u32 wMsgFilterMin, ::u32 wMsgFilterMax, const ::duration & duration)
{

   if (wMsgFilterMax == 0)
   {

      wMsgFilterMax = 0xffffffffu;

   }

   _synchronous_lock synchronouslock(mutex());

   while (true)
   {

      for (::index i = 0; i < m_messagea.get_count();)
      {

         auto & message = m_messagea[i];

         if (message.m_atom == e_message_quit)
         {

            m_bQuit = true;

            // 2021-07-22 15:03 BRT Changed from this
            //m_messagea.erase_at(i);

            // 2021-07-22 15:03 BRT ... to this
            // 2021-07-22 15:03 BRT quit message would be last message and empty message queue?
            m_messagea.erase_all();

            return;

         }

         auto iMessage = message.m_atom.i64();

         if ((oswindow == nullptr || message.oswindow == oswindow) && iMessage >= wMsgFilterMin && iMessage <= wMsgFilterMax)
         {

            *pmessage = message;

            m_messagea.erase_at(i);

            //m_bKickIdle = false;

            return;

         }

         i++;

      }

      //if (m_bKickIdle)
      //{

      //   m_bKickIdle = false;

      //   return status_kick_idle;

      //}

      {

         synchronouslock.unlock();

         m_eventNewMessage.wait(duration);
         //{

         //   return error_wait_timeout;

         //}

         synchronouslock.lock();

         m_eventNewMessage.ResetEvent();


      }

   }

}


bool message_queue::peek_message(MESSAGE * pMsg, oswindow oswindow,::u32 wMsgFilterMin,::u32 wMsgFilterMax,::u32 wRemoveMsg)
{

   if(wMsgFilterMax == 0)
   {

      wMsgFilterMax = (::u32)-1;

   }

   _synchronous_lock synchronouslock(mutex());

   ::count count = m_messagea.get_count();

   for(i32 i = 0; i < count; i++)
   {

      MESSAGE & msg = m_messagea[i];

      if((oswindow == nullptr || msg.oswindow == oswindow) && msg.m_atom.i64() >= wMsgFilterMin && msg.m_atom.i64() <= wMsgFilterMax)
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


