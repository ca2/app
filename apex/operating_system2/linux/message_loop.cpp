#include "framework.h"
#include "_user.h"
#include "acme/parallelization/message_queue.h"


/*
class sys_message_queue
{
public:


   simple_event                     m_happening;
   ::pointer < ::mutex >                     m_pmutex;
   ::array < MESSAGE * >           m_msgptra;


   int_bool GetMessage(MESSAGE * pmsg);


};





int_bool sys_message_queue::GetMessage(MESSAGE * pmsg)
{
   single_lock lockMutex(m_pmutex, false);
   while(true)
   {
      lockMutex.lock();
      if(m_msgptra.get_count() <= 0)
      {
         lockMutex.unlock();
         m_happening.wait();
      }
      else
      {
         *pmsg = *m_msgptra[0];
         m_msgptra.erase_at(0);
         if(pmsg->message == 0xffff)
         {
            return false;
         }
         else
         {
            return true;
         }

      }
   }
}


sys_thread::sys_thread(pthread_t pthread) :
   m_pthread(pthread)
{
}

int_bool sys_thread::GetMessage(MESSAGE * pmsg)
{
      return m_messagequeue.GetMessage(pmsg);
}







sys_thread * sys_thread_pool::get_current()
{
   return get(pthread_self());
}

sys_thread * sys_thread_pool::get(pthread_t pthread)
{


   single_lock lockMutex(m_pmutex, false);


   for(int i = 0; i < m_threadptra.get_count(); i++)
   {
      if(m_threadptra[i]->m_pthread == pthread)
         return m_threadptra[i];

   }

   m_threadptra.add(___new sys_thread(pthread));

   return m_threadptra[m_threadptra.get_count() - 1];
}


*/



//
//int_bool post_message(oswindow oswindow, ::enum_message emessage, ::wparam wparam, ::lparam lparam)
//{
//
//   return message_queue_post(oswindow, message, wparam, lparam);
//
//}
//
