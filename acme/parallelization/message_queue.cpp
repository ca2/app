#include "framework.h"
#include "message_queue.h"
#include "acme/constant/message.h"
#include "acme/operating_system/message.h"
#include "acme/parallelization/synchronous_lock.h"
#include "acme/platform/scoped_restore.h"
//#include "acme/_operating_system.h"


#ifdef PARALLELIZATION_PTHREAD


#include "acme/operating_system/ansi/_pthread.h"


#endif


//#define e_message_kick_idle         0x036A  // (params unused) causes idles to kick in
#if defined(LINUX) // || defined(ANDROID)


bool apex_defer_process_x_message(htask htask,MESSAGE * pMsg,::windowing::window * pwindow,bool bPeek);


#endif


message_queue::message_queue()
{

   __raw_construct_new(m_phappeningNewMessage);

   m_bQuit = false;

   //m_bKickIdle = false;

}


message_queue::~message_queue()
{

}


void message_queue::on_initialize_particle()
{

   defer_create_synchronization();

}


void message_queue::post_message(oswindow oswindow, ::enum_message emessage, ::wparam wparam, ::lparam lparam)
{

   if (m_bQuit)
   {

      return;
      //return false;

   }

   MESSAGE message;

   message.m_oswindow = oswindow;
   message.m_emessage = emessage;
   message.m_wparam = wparam;
   message.m_lparam = lparam;
   message.m_point.x() = I32_MINIMUM;
   message.m_point.y() = I32_MINIMUM;

   /* return */ post_message(message);

}


void message_queue::post_message(const MESSAGE & message)
{

   if(m_bQuit)
   {

      //return false;

      return;

   }

   if (message.m_emessage == e_message_quit)
   {

      informationf("message_queue::post_message e_message_quit\n");

   }

   _synchronous_lock synchronouslock(this->synchronization());

   m_messagea.add(message);
   
   if(m_messagea.size() > 100)
   {
      
      information() << "Why m_messagea.size() > 100, let's figure out...";
      
   }

   if(m_eflagElement & (1ll << 36))
   {
      
      //printf("test123");
   }

   m_phappeningNewMessage->set_happening();

   //return true;

}


void message_queue::kick_idle()
{

   //synchronous_lock synchronouslock(this->synchronization());

   //m_bKickIdle = true;

   //m_happeningNewMessage.set_happening();

   post_message(nullptr, e_message_kick_idle, {}, {});

}


::e_status message_queue::get_message(MESSAGE * pmessage, oswindow oswindow, unsigned int wMsgFilterMin, unsigned int wMsgFilterMax, const class time & time)
{

   long long iFilterMinimum = wMsgFilterMin;

   if (iFilterMinimum == 0)
   {

      ::minimum(iFilterMinimum);

   }

   long long iFilterMaximum = wMsgFilterMax;

   if (iFilterMaximum == 0)
   {

      ::maximum(iFilterMaximum);

   }

   _synchronous_lock synchronouslock(this->synchronization());

   if(m_eflagElement & (::enum_flag) (1ll <<37))
   {
      
      return error_threading;
      
   }
   
   m_eflagElement |= (::enum_flag) (1ll <<37);

   at_end_of_scope
   {
      
      if(!synchronouslock.is_locked())
      {
       
         synchronouslock._lock();
         
      }
   
      m_eflagElement &= (::enum_flag) ~(1ll <<37);
      
   };
 
   while (true)
   {

      for (::collection::index i = 0; i < m_messagea.get_count();)
      {

         auto & message = m_messagea[i];

         if (message.m_emessage == e_message_quit)
         {

            m_bQuit = true;

            // 2021-07-22 15:03 BRT Changed from this
            //m_messagea.erase_at(i);

            // 2021-07-22 15:03 BRT ... to this
            // 2021-07-22 15:03 BRT quit message would be last message and empty message queue?
            m_messagea.erase_all();

            return status_quit;

         }

         auto emessage = message.m_emessage;

         if ((oswindow == nullptr || message.m_oswindow == oswindow) && emessage >= iFilterMinimum && emessage <= iFilterMaximum)
         {

            *pmessage = message;
            
            if(m_eflagElement & (1ll << 36))
            {
             
               //printf("test123");
               
            }

            m_messagea.erase_at(i);

            return success;

         }

         i++;

      }

      {

         m_phappeningNewMessage->reset_happening();

         synchronouslock.unlock();

         auto bAcquired = m_phappeningNewMessage->_wait(time);

         if(m_eflagElement & (1ll << 36))
         {
          
            //printf("test123");
            
         }
         if(!bAcquired)
         {

            return error_wait_timeout;

         }

         synchronouslock._lock();

      }

   }

}


bool message_queue::peek_message(MESSAGE * pMsg, oswindow oswindow,unsigned int wMsgFilterMin,unsigned int wMsgFilterMax, bool bRemoveMessage)
{

   if(wMsgFilterMax == 0)
   {

      wMsgFilterMax = U32_MAXIMUM;

   }

   _synchronous_lock synchronouslock(this->synchronization());

   if(m_eflagElement & (::enum_flag) (1ll <<37))
   {
      
      throw ::exception(error_threading);
      
   }
   
   m_eflagElement |= (::enum_flag) (1ll <<37);

   at_end_of_scope
   {
      
      if(!synchronouslock.is_locked())
      {
       
         synchronouslock._lock();
         
      }
   
      m_eflagElement &= (::enum_flag) ~(1ll <<37);
      
   };

   ::collection::count count = m_messagea.get_count();

   for(int i = 0; i < count; i++)
   {

      MESSAGE & msg = m_messagea[i];

      if((oswindow == nullptr || msg.m_oswindow == oswindow) && msg.m_emessage >= wMsgFilterMin && msg.m_emessage <= wMsgFilterMax)
      {

         *pMsg = msg;

         if(bRemoveMessage)
         {

            if(m_eflagElement & (1ll << 36))
            {
             
               //printf("test123");
               
            }
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


