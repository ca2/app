#include "framework.h"

/*
class sys_message_queue
{
public:


   simple_event                     m_event;
   simple_mutex                     m_mutex;
   simple_array < MESSAGE * >           m_msgptra;


   WINBOOL GetMessage(MESSAGE * pmsg);


};





WINBOOL sys_message_queue::GetMessage(MESSAGE * pmsg)
{
   mutex_lock lockMutex(m_mutex, false);
   while(true)
   {
      lockMutex.lock();
      if(m_msgptra.get_count() <= 0)
      {
         lockMutex.unlock();
         m_event.wait();
      }
      else
      {
         *pmsg = *m_msgptra[0];
         m_msgptra.remove_at(0);
         if(pmsg->message == 0xffff)
         {
            return FALSE;
         }
         else
         {
            return TRUE;
         }

      }
   }
}


sys_thread::sys_thread(pthread_t pthread) :
   m_pthread(pthread)
{
}

WINBOOL sys_thread::GetMessage(MESSAGE * pmsg)
{
      return m_messagequeue.GetMessage(pmsg);
}







sys_thread * sys_thread_pool::get_current()
{
   return get(pthread_self());
}

sys_thread * sys_thread_pool::get(pthread_t pthread)
{


   mutex_lock lockMutex(m_mutex, false);


   for(i32 i = 0; i < m_threadptra.get_count(); i++)
   {
      if(m_threadptra[i]->m_pthread == pthread)
         return m_threadptra[i];

   }

   m_threadptra.add(new sys_thread(pthread));

   return m_threadptra[m_threadptra.get_count() - 1];
}


*/


bool TranslateMessage(LPMESSAGE lpmessage)
{

   UNREFERENCED_PARAMETER(lpmessage);

   return true;

}


LRESULT DispatchMessage(LPMESSAGE lpmessage)
{

   if(lpmessage->hwnd == nullptr)
      return false;

   return lpmessage->hwnd->get_user_interaction_base()->message_handler(lpmessage);

}


