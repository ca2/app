#include "framework.h"
#ifdef LINUX
#include "acme/os/linux/_linux.h"
#include "acme/node/linux/_linux.h"
#endif
/*
class sys_message_queue
{
public:


   simple_event                     m_event;
   ::mutex                     m_mutex;
   ::ref_array < MESSAGE >           m_msgptra;


   int_bool GetMessage(MESSAGE * pmsg);


};








int_bool sys_message_queue::GetMessage(MESSAGE * pmsg)
{
   single_lock lockMutex(m_mutex, false);
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


   single_lock lockMutex(m_mutex, false);


   for(i32 i = 0; i < m_threadptra.get_count(); i++)
   {
      if(m_threadptra[i]->m_pthread == pthread)
         return m_threadptra[i];

   }

   m_threadptra.add(new sys_thread(pthread));

   return m_threadptra[m_threadptra.get_count() - 1];
}


*/



void _c_simple_message_loop()
{

   MESSAGE msg;

   while (mq_get_message(&msg, nullptr, 0, 0))
   {

      TranslateMessage(&msg);

      DispatchMessage(&msg);

   }


}

int_bool(*g_pfnTranslateMessage)(const MESSAGE * pmessage) = nullptr;



void set_TranslateMessage(int_bool(*pfn)(const MESSAGE * pmessage))

{

   g_pfnTranslateMessage = pfn;

}

LRESULT(*g_pfnDispatchMessage)(const MESSAGE * pmessage) = nullptr;


void set_DispatchMessage(LRESULT(*pfn)(const MESSAGE * pmessage))

{

   g_pfnDispatchMessage = pfn;

}


int_bool TranslateMessage(const MESSAGE * pmessage)

{

   if (g_pfnTranslateMessage == nullptr)
      return true;

   return (*g_pfnTranslateMessage)(pmessage);


}


LRESULT DispatchMessage(const MESSAGE * pmessage)

{

   if (g_pfnDispatchMessage == nullptr)
      return 0;

   return (*g_pfnDispatchMessage)(pmessage);


}



// int_bool axis_TranslateMessage(const MESSAGE * pmessage)

// {

//    UNREFERENCED_PARAMETER(pmessage);


//    return true;

// }


// LRESULT axis_DispatchMessage(const MESSAGE * pmessage)

// {

//    if (pmessage->hwnd == nullptr)

//       return false;
//    //
//    //   if(pmessage->message == e_message_mouse_move)

//    //   {
//    //
//    //      auto tickNow = ::tick::now();
//    //
//    //      if(tickNow - pmessage->hwnd->m_tickLastMouseMove <= 5)

//    //      {
//    //
//    //         return 0;
//    //
//    //      }
//    //
//    //      pmessage->hwnd->m_tickLastMouseMove = tickNow;

//    //
//    //   }
//    //   else if(pmessage->message == WM_LBUTTONDOWN)

//    //   {
//    //
//    //      auto tickNow = ::tick::now();
//    //
//    //   }

//    if (pmessage->hwnd->m_pimpl == nullptr)
//    {

//       return false;

//    }

//    return pmessage->hwnd->m_pimpl->m_puserinteraction->message_handler((LPMESSAGE)pmessage);

// }



